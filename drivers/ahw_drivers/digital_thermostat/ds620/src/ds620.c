/**
 * @file ads7828.c
 *
 * @brief This file contains the driver function of digital thermostat DS620
 *
 *  @copyright Copyright 2023 Antaris, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ds620.h"


static float arr[4]={0.0625,0.125,0.25,0.5};
static uint8_t cont_conv_sts=0;
static double conv_temp_get(s_ds620_drv_cb_ptr ds620_hdl, int16_t data);
static int16_t conv_temp_set(s_ds620_drv_cb_ptr ds620_hdl, double temperature);

/*!
 *  @brief This API checks the NULL pointer
 */
static e_ds620_err null_ptr_check(const s_ds620_drv_cb_ptr dev)
{
    e_ds620_err rslt;

    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL))
    {
        rslt = NULL_PTR_ERR;
    }
    else
    {

        rslt = DS620_SCS;
    }

    return rslt;
}

/*!
 *  @brief This API writes the 16bit data
 */
static e_ds620_err ds620_write16(s_ds620_drv_cb_ptr ds620_hdl, uint8_t reg, int16_t data)
{
    e_ds620_err sts;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        uint8_t array[2];
        array[1]=data & 0xff;
        array[0]=(data >> 8);
        sts=ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,reg,array,2);
    }
    return(sts);
}

/*!
 *  @brief This API reads 16 bit data
 */
static e_ds620_err ds620_read16(s_ds620_drv_cb_ptr ds620_hdl, uint8_t reg, int16_t* data)
{
    e_ds620_err sts=DS620_ERR;
    uint8_t lsb,msb;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts=ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,reg,&msb,1);
        reg++;
        sts=ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,reg,&lsb,1);
        *data=lsb|msb<<8;
    }
    return(sts);
}

/*!
 *  @brief This API converts the register data into temperature in celsius
 */
static double conv_temp_get(s_ds620_drv_cb_ptr ds620_hdl, int16_t data)
{
    uint8_t temp_lsb;
    int16_t temp_data;
    double sum=0;
    temp_data=(data>>7);
    temp_lsb=data;
    temp_lsb=temp_lsb & 0x7F;
    switch(ds620_hdl->resolution)
    {
        case BIT_13:
            temp_lsb=temp_lsb >> 3;
            break;
        case BIT_12:
            temp_lsb=temp_lsb >> 4;
            break;
        case BIT_11:
            temp_lsb=temp_lsb >> 5;
            break;
        case BIT_10:
            temp_lsb=temp_lsb >> 6;
            break;
        default:
            break;
    }
    for(int i=0;i<4;i++)
    {
        sum=sum+((double)(temp_lsb & 0x01)*arr[i]);
        temp_lsb=temp_lsb>>1;
    }
    sum=sum+(double)temp_data;
    return(sum);
}

/*!
 *  @brief This API converts the temperature in celsius (double) into 16 bit signed integer register format
 */
static int16_t conv_temp_set(s_ds620_drv_cb_ptr ds620_hdl, double temperature)
{
    double int_val, frac;
    int16_t c_int_val;
    int16_t temp=0;
    int16_t retval=0;
    uint8_t flag=0;
    frac = modf(temperature,&int_val);
    c_int_val=(int)int_val;
    uint8_t bit_count=0;
    if(frac < 0)
    {
        frac=fabs(frac);
        c_int_val=c_int_val-1;
        flag++;
    }
    retval=(c_int_val<<7);
    while (frac > 0 && bit_count<MAX_COUNT)
    {
        frac*=2;
        frac = modf(frac,&int_val);
        temp=temp|(int)int_val;
        temp=temp<<1;
        bit_count++;
    }
    temp=temp<<6;
    retval=retval|temp>>(bit_count);
    if(flag!=0)
    {
        temp=(~temp);
        temp=0x0078 & temp;
        temp=temp+(0x0008);
        retval=retval|temp;
    }
    return retval;
}

/*!
 *  @brief This API initalizes the DS620 and allocates the memory
 */
e_ds620_err ds620_init (s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts = DS620_ERR;
    sts = null_ptr_check(ds620_hdl);
    if(sts==DS620_SCS)
    {
        ds620_reset(ds620_hdl);
        sts = ds620_config(ds620_hdl);
        ds620_start_conversion(ds620_hdl);
    }
    else
    {

    }
    return (sts);
}

/*!
 *  @brief This API release the control block memory of ds620 instance
 */
e_ds620_err ds620_deinit (s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts = DS620_ERR;

    sts = null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        ds620_stop_conversion(ds620_hdl);
        sts=DS620_SCS;
    }
    else
    {   sts=DS620_ERR;
    }
    return (sts);
}

/*!
 *  @brief This API set the high temperature threshold of DS620 for thermostat operation
 */
e_ds620_err ds620_set_temperature_high_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double high_temp_thrshd)
{
    e_ds620_err sts=DS620_ERR;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else if(high_temp_thrshd > MAX_TEMP_VAL || high_temp_thrshd < MIN_TEMP_VAL)
    {
        sts = DS620_INVLD_ARG;
    }
    else
    {
        int16_t data_temp=conv_temp_set(ds620_hdl,high_temp_thrshd);
        sts = ds620_write16(ds620_hdl, TEMP_TH_MSB_REG, data_temp);
    }
    return(sts);
}

/*!
 *  @brief This API set the low temperature threshold of DS620 for thermostat operation
 */
e_ds620_err ds620_set_temperature_low_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double low_temp_thrshd)
{
    e_ds620_err sts=DS620_ERR;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else if(low_temp_thrshd > MAX_TEMP_VAL || low_temp_thrshd < MIN_TEMP_VAL)
    {
        sts = DS620_INVLD_ARG;
    }
    else
    {
        int16_t data_temp=conv_temp_set(ds620_hdl,low_temp_thrshd);
        sts = ds620_write16(ds620_hdl, TEMP_TL_MSB_REG, data_temp);
    }
    return(sts);
}

/*!
 *  @brief This API set the high temperature threshold of DS620 for thermostat operation
 */
e_ds620_err ds620_get_temperature_high_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double* high_temp_thrshd)
{
    e_ds620_err sts=DS620_ERR;
    int16_t data_temp;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts = ds620_read16(ds620_hdl, TEMP_TH_MSB_REG,&data_temp);
        *high_temp_thrshd = conv_temp_get(ds620_hdl,data_temp);
    }
    return(sts);
}

/*!
 *  @brief This API set the low temperature threshold of DS620 for thermostat operation
 */
e_ds620_err ds620_get_temperature_low_thrshd (s_ds620_drv_cb_ptr ds620_hdl, double* low_temp_thrshd)
{
    e_ds620_err sts=DS620_ERR;
    int16_t data_temp;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts = ds620_read16(ds620_hdl, TEMP_TL_MSB_REG,&data_temp);
        *low_temp_thrshd = conv_temp_get(ds620_hdl,data_temp);
    }
    return(sts);
}

/*!
 *  @brief This API reads temperature and returns it
 */
e_ds620_err ds620_get_temperature (s_ds620_drv_cb_ptr ds620_hdl, double* temperature)
{
    e_ds620_err sts= DS620_ERR;

    sts=null_ptr_check(ds620_hdl);
    int16_t temp_val=0;
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        if(cont_conv_sts==0)
        {
            ds620_start_conversion(ds620_hdl);
            ds620_hdl->delay_ms(DS620_DELAY);
        }
        sts = ds620_read16(ds620_hdl,TEMP_MSB_REG,&temp_val);
        *temperature = conv_temp_get(ds620_hdl,temp_val);
    }
    return(sts);
}

/*!
 *  @brief This API writes the temperature value in the temperature register, It will be use to auto test the thermostat
 */
e_ds620_err ds620_set_temperature (s_ds620_drv_cb_ptr ds620_hdl, double temperature)
{
    e_ds620_err sts= DS620_ERR;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else if(temperature>125 || temperature<(-55))
    {
        sts = DS620_INVLD_ARG;
    }
    else
    {
        int16_t data_temp=conv_temp_set(ds620_hdl,temperature);
        sts = ds620_write16(ds620_hdl, TEMP_MSB_REG, data_temp);
    }
    return(sts);
}

/*!
 *  @brief This API configures the DS620 with initial configuration values
 */
e_ds620_err ds620_config (s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts;
    uint8_t temp_data[2];
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else if(ds620_hdl->temp_low_thrshd>125 || ds620_hdl->temp_low_thrshd<(-55) || ds620_hdl->temp_high_thrshd>125 || ds620_hdl->temp_high_thrshd<(-55))
    {
        sts = DS620_INVLD_ARG;
    }
    else
    {
        sts=ds620_hdl->read(ds620_hdl->intf_hdl, ds620_hdl->slv_addr, CONFIG_MSB_REG, temp_data,2);
        temp_data[0]=temp_data[0] & 0xF0;
        temp_data[0] = temp_data[0] | ((0x0C & ds620_hdl->resolution ) | (0x01 & ds620_hdl->mode) | (0x02 &ds620_hdl->conv_type));

        temp_data[1]= (temp_data[1] & (~0xC0)) ;
        temp_data[1]=	temp_data[1] | ((0xC0)&(ds620_hdl->po_level_type));

        sts=ds620_hdl->write(ds620_hdl->intf_hdl, ds620_hdl->slv_addr, CONFIG_MSB_REG, temp_data,2);
        sts=ds620_set_temperature_high_thrshd(ds620_hdl,ds620_hdl->temp_high_thrshd);
        sts=ds620_set_temperature_low_thrshd(ds620_hdl,ds620_hdl->temp_low_thrshd);
    }
    return(sts);
}

/*!
 *  @brief This API sets the ADC resolution of the DS620
 */
e_ds620_err ds620_set_resolution (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_res res)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t temp_data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl, ds620_hdl->slv_addr,CONFIG_MSB_REG,&temp_data,1);
        temp_data=(temp_data & (~0x0C)) | res;
        sts=ds620_hdl->write(ds620_hdl->intf_hdl, ds620_hdl->slv_addr,CONFIG_MSB_REG,&temp_data,1);
    }
    return(sts);
}

/*!
 *  @brief This API gets the ADC resolution of the DS620
 */
e_ds620_err ds620_get_resolution(s_ds620_drv_cb_ptr ds620_hdl, e_ds620_res *res)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t resolution;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts=ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_MSB_REG,&resolution,1);
        *res=(e_ds620_res)(resolution & 0x0C);
    }
    return(sts);
}

/*!
 *  @brief This API sets the conversion mode of DS620
 */
e_ds620_err ds620_set_conv_mode(s_ds620_drv_cb_ptr ds620_hdl,e_ds620_mode mode)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t temp_data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_MSB_REG,&temp_data,1);
        temp_data=(temp_data & (~0x01)) | mode;
        sts=ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_MSB_REG,&temp_data,1);
    }
    return(sts);
}

/*!
 *  @brief This API sets the operating mode of DS620, the value can be ONESHOT_CONV or continuous conversion
 */
e_ds620_err ds620_get_mode(s_ds620_drv_cb_ptr ds620_hdl,e_ds620_mode* mode)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t temp_data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_MSB_REG,&temp_data,1);
        *mode=(temp_data & (0x01));
    }
    return(sts);
}

/*!
 *  @brief This API set the PO pin level type, the values can be high, low and force low
 */
e_ds620_err ds620_set_po_lvl (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl lvl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t temp_data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr, CONFIG_LSB_REG,&temp_data,1);
        temp_data=(temp_data & (~0xC0)) | lvl;
        sts=ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_LSB_REG,&temp_data,1);
    }
    return(sts);
}

/*!
 *  @brief This API get the PO pin level alert status
 */
e_ds620_err ds620_get_po_lvl_alert_sts (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl* alert_sts)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr, CONFIG_MSB_REG,&data,1);
        data=(data & (~0xCF))>>4;
        *alert_sts = data;
    }
    return(sts);
}

/*!
 *  @brief This API get the PO pin level type, the values can be high, low and force low
 */
e_ds620_err ds620_get_po_lvl (s_ds620_drv_cb_ptr ds620_hdl, e_ds620_po_lvl* lvl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t temp_data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr, CONFIG_LSB_REG,&temp_data,1);
        *lvl =(temp_data & (0xC0));
    }
    return(sts);
}

/*!
 *  @brief This API resets the DS620
 */
e_ds620_err ds620_reset(s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t data =SOFTWARE_POR;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts = ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,data,NULL,1);
    }
    return(sts);
}

/*!
 *  @brief This API start the conversion
 */
e_ds620_err ds620_start_conversion(s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t data =START_CMD;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts = ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,data,NULL,1);
        if(ds620_hdl->mode!=ONESHOT_CONV)
        {
            cont_conv_sts=1;
        }
    }
    return(sts);
}

/*!
 *  @brief This API stop the conversion
 */
e_ds620_err ds620_stop_conversion(s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t data =STOP_CMD;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        sts = ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,data,NULL,1);
        cont_conv_sts=0;
    }
    return(sts);
}

/*!
 *  @brief This API resets alert flag
 */
e_ds620_err ds620_reset_alert_flag(s_ds620_drv_cb_ptr ds620_hdl)
{
    e_ds620_err sts= DS620_ERR;
    uint8_t data;
    sts=null_ptr_check(ds620_hdl);
    if(sts!=DS620_SCS)
    {
        sts=NULL_PTR_ERR;
    }
    else
    {
        ds620_hdl->read(ds620_hdl->intf_hdl,ds620_hdl->slv_addr, CONFIG_MSB_REG,&data,1);
        data=data & 0XCF;
        sts = ds620_hdl->write(ds620_hdl->intf_hdl,ds620_hdl->slv_addr,CONFIG_MSB_REG,&data,1);
    }
    return(sts);
}

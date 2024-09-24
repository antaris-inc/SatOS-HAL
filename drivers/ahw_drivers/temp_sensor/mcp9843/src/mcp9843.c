/**
 * @file mcp9843.c
 *
 *  @brief This file contains the driver function of temperature sensor MCP9843
 *
 *  @copyright Copyright 2024 Antaris, Inc.
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

#include"mcp9843.h"

/*********************************************************************/
/* Static function declarations */
/**
 * @brief validate the device structure pointer
 * This API is used to validate the device structure pointer for null conditions.
 * @param[in] ina230_hdl         : Structure instance of psm_ina230.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
static  int8_t  null_ptr_check(mcp9843_dev_ptr_t mcp9843_hdl);

/**
 * @brief validate the device structure pointer
 * This API is used to process the task to retrieve the ambient temperature from the MCP9843 device.
 * It then formats the returned value into a signed 16-bit value returned via the ref mcp9843_get_manufacture public function.
 * @param[in] mcp9843_hdl - pointer to a mcp9843_dev_ptr_t structure
 * @param[in] temperature - variable used to store, and return read temperature
 * return Signed temperature value representing celsius value measured by MCP9843.
 * @retval cal, Formated representation of ambient temperature.
 */
static e_temp_sensor_sts mcp9843_temperature_calculation(mcp9843_dev_ptr_t mcp9843_hdl,float* temperature);

static int16_t conv_temp_set(double temperature);
static float conv_temp_get(int16_t data);
static float arr[4]={0.0625,0.125,0.25,0.5};

/**
 * @brief  Write access to MCP9843 register
 */
e_temp_sensor_sts mcp9843_writereg(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t reg, int16_t data)
{
    e_temp_sensor_sts sts;
    uint8_t dt[2];
    dt[0] = data >> 8;
    dt[1] = data & 0xff;
    sts=mcp9843_hdl->write(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,reg,dt,2);
    return(sts);
}

/*!
 *  @brief This API converts the temperature in celsius (double) into 16 bit signed integer register format
 */
static int16_t conv_temp_set(double temperature)
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
    while (frac > 0 && bit_count<4)
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
    retval=(retval>>3);
    return retval;
}

/*!
 *  @brief This API converts the register data into temperature in celsius
 */
static float conv_temp_get(int16_t data)
{
    uint8_t temp_lsb;
    int16_t temp_data;
    float sum=0;
    temp_data = data & 0x1FFF;
    temp_data=(temp_data>>4);
    temp_lsb=data;
    temp_lsb=temp_lsb & 0x0F;
    for(int i=0;i<4;i++)
    {
        sum=sum+((float)(temp_lsb & 0x01)*arr[i]);
        temp_lsb=temp_lsb>>1;
    }
    sum=sum + (float)temp_data;
    return(sum);
}

/**
 * @brief  Read access to MCP9843 register
 */
e_temp_sensor_sts mcp9843_readreg(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t reg, int16_t* data)
{
    e_temp_sensor_sts sts=MCP9843_ERR;
    sts=null_ptr_check(mcp9843_hdl);
    if(sts!=MCP9843_OK)
    {
        sts=MCP9843_E_NULL_PTR;
    }
    else
    {
        uint8_t dt[2];
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,reg,dt,2);
        *data = (dt[1] | (dt[0]<<8));
    }
    return(sts);
}

/**
 * @brief  Initialize the MCP9843 and configure the needed hardware resources
 */
e_temp_sensor_sts mcp9843_init(mcp9843_dev_ptr_t mcp9843_hdl)
{
    e_temp_sensor_sts sts;
    int16_t temp=1;
    sts = null_ptr_check(mcp9843_hdl);
    if(sts==MCP9843_OK)
    {
        sts=mcp9843_readreg(mcp9843_hdl, MCP9843_DVE_ID_REG_ADRR,&temp);
        if(sts==MCP9843_SCS)
        {
            sts = mcp9843_config(mcp9843_hdl);
        }
    }
    else
    {
        sts=MCP9843_E_DEV_NOT_FOUND;
    }
    return (sts);
}

/**
 * @brief  De-Initialize the MCP9843
 */
e_temp_sensor_sts mcp9843_deinit(mcp9843_dev_ptr_t mcp9843_hdl)
{
    e_temp_sensor_sts sts= MCP9843_ERR;

    sts=null_ptr_check(mcp9843_hdl);
    if(sts!=MCP9843_OK)
    {
        sts=MCP9843_E_NULL_PTR;
    }
    else
    {

    }
    return sts;
}

/**
 * @brief MCP9843 get event status
 */
e_temp_sensor_sts   mcp9843_get_event_sts (mcp9843_dev_ptr_t mcp9843_hdl, uint8_t* evnt_sts)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data[2];
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,temp_data,2);
        temp_data[1]=temp_data[1] & 0x10;
        *evnt_sts = temp_data[1]>>4;
    }
    return (sts);

}

/**
 * @brief configure the needed hardware resources for MCP9843
 */
e_temp_sensor_sts mcp9843_config (mcp9843_dev_ptr_t mcp9843_hdl)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data[2];
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CAPA_REG,temp_data,2);
        temp_data[1]=temp_data[1] | 0x03;
        sts=mcp9843_hdl->write(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address, MCP9843_CAPA_REG, temp_data,2);
        mcp9843_set_temp_high_threshold (mcp9843_hdl,mcp9843_hdl->high_temp_threshold);
        mcp9843_set_temp_low_threshold (mcp9843_hdl,mcp9843_hdl->low_temp_threshold);
        mcp9843_set_temp_critical_threshold (mcp9843_hdl,mcp9843_hdl->critical_temp_threshold);
        mcp9843_set_event_output_mode(mcp9843_hdl,mcp9843_hdl->event_mode);
    }
    return (sts);
}

/**
 * @brief Setting MCP9843 event_output_mode
 */
e_temp_sensor_sts mcp9843_set_event_output_mode(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_event_output_mode_t event_mode)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data[2];
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,temp_data,2);
        if(sts==MCP9843_OK)
        {
            if(event_mode==MCP9843_EVENT_NONE)
            {
                temp_data[1]=(temp_data[1] & (0xF7));
            }
            else
            {
                temp_data[1]=(temp_data[1] & (0xF0));
                temp_data[1]=(temp_data[1] | (event_mode));
            }
            sts= mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,temp_data,2);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return(sts);
}

/**
 * @brief Setting MCP9843 mode of operation
 */
e_temp_sensor_sts mcp9843_set_mode(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_mode_t mode)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data;
    sts = null_ptr_check(mcp9843_hdl);// Null-pointer check
    if (sts != MCP9843_OK)
    {
        sts = MCP9843_E_NULL_PTR;
    }
    else
    {
        mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        if(sts==MCP9843_OK)
        {
            temp_data=(temp_data & (0xEF));
            temp_data=(temp_data | (mode));
            if(temp_data<MCP9843_MODE_MAX)
            {
                sts= mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
            }
            else
            {
                sts=MCP9843_ERR;
            }
        }
    }
    return(sts);
}

/**
 * @brief Setting MCP9843 intrupt_clear bit if shutdown mode is enabled
 */
e_temp_sensor_sts mcp9843_interrupt_clear(mcp9843_dev_ptr_t mcp9843_hdl, uint8_t interrupt_clear)
{
    e_temp_sensor_sts sts;
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        interrupt_clear=(interrupt_clear & (0xFA));
        interrupt_clear=(interrupt_clear | MCP9843_INT_CLEAR_BIT_05 );
        sts=mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,&interrupt_clear,1);
    }
    return(sts);
}

/**
 * @brief Setting MCP9843 event_polarity
 */
e_temp_sensor_sts mcp9843_set_event_polarity(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_event_polarity_t polarity)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data;
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        if(sts==MCP9843_OK)
        {
            temp_data=(temp_data & (0xFD));
            temp_data=(temp_data | (polarity));
            sts= mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return(sts);
}

/**
 * @brief Setting MCP9843_win_lock_bit (bit 6)
 */
e_temp_sensor_sts mcp9843_set_win_lockbit(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_win_lock_t win_lock)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data;
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        if(sts==MCP9843_OK)
        {
            temp_data=(temp_data & (0xF9));
            temp_data=(temp_data | (win_lock));
            sts= mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return(sts);
}

/**
 * @brief Setting MCP9843_crit_lock_bit (bit 7)
 */
e_temp_sensor_sts mcp9843_set_crit_lockbit(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_crit_lock_t crit_lock)
{
    e_temp_sensor_sts sts;
    uint8_t temp_data;
    sts = null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        if(sts==MCP9843_OK)
        {
            temp_data=(temp_data & (0xF8));
            temp_data=(temp_data | (crit_lock));
            sts= mcp9843_hdl->write( mcp9843_hdl->io_intf_hdle, mcp9843_hdl->slave_address,MCP9843_CONF_REG,&temp_data,2);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return(sts);
}

/**
 * @brief Setting MCP9843 high temperature threshold
 */
e_temp_sensor_sts mcp9843_set_temp_high_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float high_temp_threshold)
{
    e_temp_sensor_sts sts;
    int16_t reg_data;
    sts=null_ptr_check(mcp9843_hdl);

    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        reg_data=conv_temp_set((double)high_temp_threshold);
        sts = mcp9843_writereg (mcp9843_hdl,MCP9843_T_UPPER,reg_data);
    }
    return (sts);
}

/**
 * @brief Setting MCP9843 low temperature threshold
 */
e_temp_sensor_sts mcp9843_set_temp_low_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float low_temp_threshold)
{
    e_temp_sensor_sts sts;
    int16_t reg_data;
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        reg_data=conv_temp_set((double)low_temp_threshold);
        sts= mcp9843_writereg(mcp9843_hdl,MCP9843_T_LOWER,reg_data);
    }
    return (sts);
}

/**
 * @brief Setting MCP9843 critical temperature threshold
 */
e_temp_sensor_sts mcp9843_set_temp_critical_threshold (mcp9843_dev_ptr_t mcp9843_hdl, float critical_temp_threshold)
{
    e_temp_sensor_sts sts;
    int16_t reg_data;
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        reg_data=conv_temp_set((double)critical_temp_threshold);
        sts= mcp9843_writereg(mcp9843_hdl, MCP9843_T_CRITICAL,reg_data);
    }
    return (sts);
}

/*!
 * @brief  This API is used to process the task to retrieve the ambient temperature from the MCP9843 device.
 * It then formats the returned value into a signed 16-bit value returned via the ref mcp9843_get_manufacture public function.
 */
static e_temp_sensor_sts mcp9843_temperature_calculation(mcp9843_dev_ptr_t mcp9843_hdl,float* temperature)
{
    e_temp_sensor_sts cal=null_ptr_check(mcp9843_hdl);
    if (cal != MCP9843_OK)
    {
        cal =MCP9843_E_NULL_PTR;
    }
    else
    {
        uint8_t temp_data[2];
        int16_t temp_data16;
        mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_TEMP_REG,(uint8_t*)&temp_data,2);
        temp_data16 = temp_data[1] | temp_data[0]<<8;
        *temperature=conv_temp_get(temp_data16);
        cal =  MCP9843_OK;

    }
    return (cal);
}

/*!
 * @brief Returns the current temperature;
 */
e_temp_sensor_sts mcp9843_gettemperature(mcp9843_dev_ptr_t mcp9843_hdl,float *temperature)
{
    e_temp_sensor_sts status;

    status = mcp9843_temperature_calculation(mcp9843_hdl,temperature);

    return (status);
}

/**
 * @brief MCP9843 temperature alarm alert
 */
e_temp_sensor_sts mcp9843_temperature_alarm_alert(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_alarm_alert_t alarm)
{
    e_temp_sensor_sts sts;
    uint8_t alarm_alert;
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CAPA_REG,&alarm_alert,2);
        if(sts==MCP9843_OK)
        {
            alarm_alert=(mcp9843_alarm_alert_t)(alarm_alert & 0x03);
            sts=mcp9843_hdl->write(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CAPA_REG,&alarm_alert,2);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return (sts);
}

/**
 * @brief setting MCP9843 temperature hysteresis
 */
e_temp_sensor_sts mcp9843_set_hysteresis(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_hyst_t hysteresis)
{
    e_temp_sensor_sts sts;
    /*null pointer check*/
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts= mcp9843_writereg (mcp9843_hdl,MCP9843_CONF_REG ,hysteresis);
    }
    return(sts);
}

/**
 * @brief  Read MCP9843 temperature hysteresis
 */
e_temp_sensor_sts mcp9843_get_hysteresis(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_hyst_t *hysteresis)
{
    e_temp_sensor_sts sts;
    uint8_t hsyt;

    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_CONF_REG,&hsyt,2);
        if(sts==MCP9843_OK)
        {
            *hysteresis=(mcp9843_hyst_t)(hsyt & 0x06);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return(sts);
}

/**
 * @brief setting MCP9843 temperature resolution.
 */
e_temp_sensor_sts mcp9843_set_resolution(mcp9843_dev_ptr_t mcp9843_hdl, mcp9843_res_t resolution)
{
    e_temp_sensor_sts sts;
    uint8_t res;
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        res=resolution;
        sts=mcp9843_hdl->write(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_RESO_REG,&res,1);
    }
    return (sts);
}

/**
 * @brief  Read MCP9843 temperature resolution.
 */
e_temp_sensor_sts mcp9843_get_resolution(mcp9843_dev_ptr_t mcp9843_hdl,mcp9843_res_t *res)
{
    e_temp_sensor_sts  sts;
    uint8_t resolution;
    sts=null_ptr_check(mcp9843_hdl);
    if (sts != MCP9843_OK)
    {
        sts =MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_RESO_REG,&resolution,1);
        if(sts==MCP9843_OK)
        {
            *res=(mcp9843_res_t)(resolution & 0x03);
        }
        else
        {
            sts=MCP9843_READ_FAIL;
        }
    }
    return (sts);
}

/**
 * @brief  Read MCP9843 temperature in fahrenheit.
 */
e_temp_sensor_sts mcp9843_get_fahrenheit(mcp9843_dev_ptr_t mcp9843_hdl,float *temp_value)
{
    e_temp_sensor_sts sts;
    sts=mcp9843_gettemperature( mcp9843_hdl,temp_value);
    if(sts==MCP9843_OK)
    {
        sts=MCP9843_OK;
    }
    else
    {
        sts=MCP9843_READ_FAIL;
    }
    return sts ;
}

/**
 * @brief  Read MCP9843 temperature in celsius.
 */
e_temp_sensor_sts mcp9843_get_celsius(mcp9843_dev_ptr_t mcp9843_hdl,float *temp_value)
{
    uint16_t sts;
    sts= mcp9843_gettemperature( mcp9843_hdl,temp_value);
    return sts ;
}

/*!
 * @brief This API is used to validate the device structure pointer for null conditions.
 */
static  int8_t null_ptr_check(mcp9843_dev_ptr_t mcp9843_hdl)
{
    int8_t sts;
    if ((mcp9843_hdl == NULL) || (mcp9843_hdl->read == NULL) || (mcp9843_hdl->write == NULL))
    {
        sts=MCP9843_E_NULL_PTR;
    }
    else
    {
        sts=MCP9843_OK;
    }
    return sts;
}

/*!
 * @brief This API validates request the Manufacture ID value from the MCP9843 Register
 * and return 16-bit hex value representing the temperature data from the MCP9843 register.
 */
uint16_t mcp9843_read_manufacture_id(mcp9843_dev_ptr_t mcp9843_hdl,int16_t* temperature)
{

    *temperature=100;
    uint8_t temp=mcp9843_hdl->read(mcp9843_hdl->io_intf_hdle,mcp9843_hdl->slave_address,MCP9843_MANUFACTURE_ID_REG,&temp,2);
    return (temp);
}

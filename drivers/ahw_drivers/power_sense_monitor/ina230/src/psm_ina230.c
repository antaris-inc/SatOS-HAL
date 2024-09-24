/**
 * @file psm_ina230.c
 *
 *  @brief This file contains the driver function of power sense monitor INA230
 *
 *	@copyright Copyright 2024 Antaris, Inc.
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

#include "psm_ina230.h"
#include <stdio.h>


/*********************************************************************/
/* Static function declarations */
/**
 * @brief validate the device structure pointer
 * This API is used to validate the device structure pointer for null conditions.
 * @param[in] ina230_hdl         : Structure instance of psm_ina230.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
static  int8_t null_ptr_check_ina230(ina230_dev_ptr_t ina230_hdl);

/**
 * @brief  Write access to INA230 register.
 */
e_ina230_sts ina230_writereg(ina230_dev_ptr_t ina230_hdl, uint8_t reg, uint16_t data)
{
    e_ina230_sts rslt;
    uint8_t dt[2];
    dt[0] = data >> 8;
    dt[1] = data & 0xff;
    rslt=ina230_hdl->write(ina230_hdl->io_intf_hdle,ina230_hdl->slave_address,reg,dt,2);
    return(rslt);
}

/**
 * @brief  Read access to INA230 register.
 */
e_ina230_sts ina230_readreg(ina230_dev_ptr_t ina230_hdl, uint8_t reg, uint16_t* data)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint8_t dt[2];
        ina230_hdl->read(ina230_hdl->io_intf_hdle,ina230_hdl->slave_address,reg,dt,2);
        if(rslt==INA230_SCS)
        {
            (*data) = (uint16_t)((dt[0] << 8) | dt[1]);
            rslt=INA230_SCS;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return rslt;
}

/**
 * @brief  Initialize the INA230 and configure the needed hardware resources.
 */
e_ina230_sts ina230_init(ina230_dev_ptr_t ina230_hdl,ina230_Cfg_ptr_t ina230_cfg)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t cfg = 0;

        rslt=ina230_reset(ina230_hdl);

        cfg = (cfg & ((uint16_t)~(INA230_REG_CFG_VSHUNTCT_Msk))) | (ina230_cfg->shunt_tc<< INA230_REG_CFG_VSHUNTCT_Pos);
        cfg = (cfg & ((uint16_t)~(INA230_REG_CFG_VBUSCT_Msk))) | (ina230_cfg->bus_tc << INA230_REG_CFG_VBUSCT_Pos);
        cfg = (cfg & ((uint16_t)~(INA230_REG_CFG_AVG_Msk))) | (ina230_cfg->averaging_mode << INA230_REG_CFG_AVG_Pos);

        ina230_set_calibration(ina230_hdl,DEF_CALIB);

    }
    return (rslt);
}

/**
 * @brief  De-Initialize the INA230 and configure the needed hardware resources
 */
e_ina230_sts ina230_deinit(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        rslt=ina230_reset(ina230_hdl);
    }
    return (rslt);
}

/**
 * @brief  Read the INA230 die identifier
 */
uint16_t ina230_read_id(ina230_dev_ptr_t ina230_hdl)
{
    uint16_t device_id;
    device_id=ina230_readreg(ina230_hdl, INA230_REG_ID,&device_id);
    return device_id;
}

/**
 * @brief  Enable/Disable the ALERT interrupt
 */
static uint8_t ina230_int(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t apol;

        apol = (ina230_readreg(ina230_hdl,INA230_REG_MASK_ENABLE,&apol) & INA230_REG_MASK_ENABLE_APOL_Msk);
        if(rslt==INA230_SCS)
        {
            if (apol == INA230_REG_MASK_ENABLE_APOL)
            {

                uint8_t active_high=0x01;
                uint8_t alert;
                alert=(alert & (0xFE));
                alert=(alert | (active_high));

                rslt=ina230_hdl->write(ina230_hdl->io_intf_hdle,ina230_hdl->slave_address,INA230_REG_MASK_ENABLE,&alert,1); //ALERT pin is active high
            }
            else
            {

                uint8_t active_low=0;
                uint8_t alert;
                alert=(alert & (0xFF));
                alert=(alert | (active_low));
                rslt=ina230_hdl->write(ina230_hdl->io_intf_hdle,ina230_hdl->slave_address,INA230_REG_MASK_ENABLE,&alert,1); //ALERT pin is active LOW (default)
            }
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Generate a system reset
 */
e_ina230_sts ina230_reset(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t cfg = 0;

        cfg |= INA230_REG_CFG_RESET;
        rslt=ina230_writereg(ina230_hdl, INA230_REG_CONFIG, cfg);
    }
    return rslt;
}

/**
 * @brief  Program the INA230 calibration register
 */
e_ina230_sts ina230_set_calibration(ina230_dev_ptr_t ina230_hdl, uint16_t calibration)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {

        rslt = ina230_writereg(ina230_hdl, INA230_REG_CALIBRATION, calibration);
    }

    return rslt;
}

/**
 * @brief  Read programmed calibration value
 */
uint16_t ina230_get_calibration(ina230_dev_ptr_t ina230_hdl)
{
    uint16_t calibration;

    calibration = null_ptr_check_ina230(ina230_hdl);
    if (calibration != INA230_OK)
    {
        calibration = INA230_E_NULL_PTR;
    }
    else
    {

        ina230_readreg(ina230_hdl, INA230_REG_CALIBRATION,&calibration);
    }
    return (calibration);
}

/**
 *  @brief  Configure the Alert pin behavior
 */
e_ina230_sts ina230_alert_pinconfig(ina230_dev_ptr_t ina230_hdl,ina230_alert_pinconfig_ptr_t alert_pin_cfg_vd)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t mask_en;

        mask_en = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&mask_en);
        if(rslt==INA230_SCS)
        {

            mask_en = (mask_en & ((uint16_t)~(INA230_REG_MASK_ENABLE_APOL_Msk))) | (alert_pin_cfg_vd->polarity<< INA230_REG_MASK_ENABLE_APOL_Pos);
            mask_en = (mask_en & ((uint16_t)~(INA230_REG_MASK_ENABLE_LEN_Msk))) | (alert_pin_cfg_vd->latch_enable << INA230_REG_MASK_ENABLE_LEN_Pos);
            rslt = ina230_writereg(ina230_hdl, INA230_REG_MASK_ENABLE, mask_en);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return rslt;
}

/**
 * @brief  Set the alert function
 */
e_ina230_sts ina230_set_alertfunction(ina230_dev_ptr_t ina230_hdl, ina230_af_t alertfunction)
{
    e_ina230_sts rslt;
    uint16_t mask_en;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt!= INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {

        mask_en = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&mask_en);
        if(rslt==INA230_SCS)
        {

            switch(alertfunction)
            {
                case ALERT_FUNCTION_NONE:
                    mask_en = (mask_en & (0x041F));
                    break;
                case ALERT_FUNCTION_SOL:
                    mask_en =(mask_en & (0x041F)) | 0x8000;
                    break;
                case ALERT_FUNCTION_SUL:
                    mask_en =(mask_en & (0x041F)) | 0x4000;
                    break;
                case ALERT_FUNCTION_BOL:
                    mask_en =(mask_en & (0x041F)) | 0x2000;
                    break;
                case ALERT_FUNCTION_BUL:
                    mask_en =(mask_en & (0x041F))  | 0x1000;
                    break;
                case ALERT_FUNCTION_POL:
                    mask_en =(mask_en & (0x041F))  | 0x0800;
                    break;
                default:
                    break;
            }
            rslt= ina230_writereg(ina230_hdl, INA230_REG_MASK_ENABLE, mask_en);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return rslt;
}

/**
 * @brief  Get the programmed alert function
 */
e_ina230_sts ina230_get_alertfunction(ina230_dev_ptr_t ina230_hdl,ina230_af_t alert_function)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt!= INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t mask_en;

        mask_en = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&mask_en);
        if(rslt==INA230_SCS)
        {
            if ((mask_en & INA230_REG_MASK_ENABLE_POL) == INA230_REG_MASK_ENABLE_POL)
            {
                alert_function = ALERT_FUNCTION_POL;
            }
            else if ((mask_en & INA230_REG_MASK_ENABLE_BUL) == INA230_REG_MASK_ENABLE_BUL)
            {
                alert_function = ALERT_FUNCTION_BUL;
            }
            else if ((mask_en & INA230_REG_MASK_ENABLE_BOL) == INA230_REG_MASK_ENABLE_BOL)
            {
                alert_function = ALERT_FUNCTION_BOL;
            }
            else if ((mask_en & INA230_REG_MASK_ENABLE_SUL) == INA230_REG_MASK_ENABLE_SUL)
            {
                alert_function = ALERT_FUNCTION_SUL;
            }
            else if ((mask_en & INA230_REG_MASK_ENABLE_SOL) == INA230_REG_MASK_ENABLE_SOL)
            {
                alert_function = ALERT_FUNCTION_SOL;
            }
            else
            {
                alert_function = ALERT_FUNCTION_NONE;
            }
            rslt=alert_function;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Program the VBus threshold
 */
e_ina230_sts ina230_setvbusthreshold(ina230_dev_ptr_t ina230_hdl, float vbusthreshold)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        val = vbusthreshold / BUS_VOLTAGE_LSB;
        rslt=ina230_writereg(ina230_hdl, INA230_REG_ALERT_LIMIT,val);
    }
    return (rslt);
}

/**
 * @brief  Get the VBUS threshold
 */
uint16_t ina230_getvbusthreshold(ina230_dev_ptr_t ina230_hdl)
{

    uint16_t  rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        uint32_t vbus_threshold;
        ina230_readreg(ina230_hdl, INA230_REG_ALERT_LIMIT,&val);
        if(rslt==INA230_SCS)
        {
            vbus_threshold = (val * BUS_VOLTAGE_LSB);
            vbus_threshold = DIV_ROUND_CLOSEST(vbus_threshold, 1000);
            rslt=(uint16_t)vbus_threshold;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  set the current threshold
 */
e_ina230_sts ina230_set_current_threshold(ina230_dev_ptr_t ina230_hdl, float current)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        val = (current*RSHUNT)/VSHUNT_DIV;
        rslt=ina230_writereg(ina230_hdl, INA230_REG_ALERT_LIMIT, val);
    }
    return (rslt);
}

/**
 * @brief  Program the VShunt threshold
 */
e_ina230_sts ina230_setvshuntthreshold(ina230_dev_ptr_t ina230_hdl, float vshuntthreshold)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        val = vshuntthreshold / VSHUNT_DIV;
        rslt=ina230_writereg(ina230_hdl, INA230_REG_ALERT_LIMIT, val);
    }
    return (rslt);
}

/**
 * @brief  Get the VShunt threshold
 */
int16_t ina230_getshuntthreshold(ina230_dev_ptr_t ina230_hdl)
{

    int16_t rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        uint16_t vshunt_threshold;
        val = ina230_readreg(ina230_hdl, INA230_REG_ALERT_LIMIT,&val);
        if(rslt==INA230_SCS)
        {
            vshunt_threshold = DIV_ROUND_CLOSEST(val, VSHUNT_DIV);
            rslt= vshunt_threshold;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Program the Power threshold
 */
e_ina230_sts ina230_setpowerthreshold(ina230_dev_ptr_t ina230_hdl, uint32_t powerthreshold)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;

        val = powerthreshold / POWER_LSB;
        rslt=ina230_writereg(ina230_hdl, INA230_REG_ALERT_LIMIT, val);
    }
    return (rslt);

}

/**
 * @brief  Get the Power threshold
 */
uint32_t ina230_getpowerthreshold(ina230_dev_ptr_t ina230_hdl)
{

    uint32_t rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        uint32_t power_threshold;
        ina230_readreg(ina230_hdl, INA230_REG_ALERT_LIMIT,&val);
        if(rslt==INA230_SCS)
        {
            power_threshold = (uint32_t)(val *POWER_LSB);
            rslt=power_threshold;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Enable the Voltage/Power threshold interrupt
 */
e_ina230_sts ina230_alert_threshold_enable_it(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        rslt=ina230_int(ina230_hdl);
    }
    return (rslt);
}

/**
 * @brief  Disable the Voltage/Power threshold interrupt
 */
e_ina230_sts ina230_alert_threshold_disable_it(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;

    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        rslt=ina230_int(ina230_hdl);
    }
    return (rslt);
}

/**
 * @brief  Enable the Conversion ready interrupt
 */
e_ina230_sts ina230_conversion_ready_enable_it(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t mask_en;
        mask_en = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&mask_en);
        if(rslt==INA230_SCS)
        {
            ina230_int(ina230_hdl);
            mask_en |= INA230_REG_MASK_ENABLE_CNVR;
            rslt=ina230_writereg(ina230_hdl, INA230_REG_MASK_ENABLE, mask_en);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Disable the Conversion ready interrupt
 */
e_ina230_sts ina230_conversion_ready_disable_it(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t mask_en;
        mask_en = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&mask_en);
        if(rslt==INA230_SCS)
        {
            mask_en &= ~INA230_REG_MASK_ENABLE_CNVR;
            rslt=ina230_writereg(ina230_hdl, INA230_REG_MASK_ENABLE, mask_en);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Stop the conversion on the selected voltage input
 */
e_ina230_sts ina230_stopconversion(ina230_dev_ptr_t ina230_hdl)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t cfg = 0;
        cfg = ina230_readreg(ina230_hdl, INA230_REG_CONFIG,&cfg);
        if(rslt==INA230_SCS)
        {
            cfg = (cfg & ((uint16_t)~(INA230_REG_CFG_MODE_Msk)));
            rslt=ina230_writereg(ina230_hdl, INA230_REG_CONFIG, cfg);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Read the bus voltage
 */
float ina230_get_vbus(ina230_dev_ptr_t ina230_hdl)
{
    uint8_t rslt;
    float vbus=0;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t val;
        rslt = ina230_readreg(ina230_hdl, INA230_REG_VBUS,&val);
        if(rslt==INA230_SCS)
        {
            vbus = (val * BUS_VOLTAGE_LSB);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (vbus);
}

/**
 * @brief  Read the shunt voltage
 */
float ina230_get_vshunt(ina230_dev_ptr_t ina230_hdl)
{
    uint16_t rslt;
    float vshunt=0;
    uint16_t val;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        rslt = ina230_readreg(ina230_hdl, INA230_REG_VSHUNT,&val);
        if(rslt==INA230_SCS)
        {
            vshunt =val* VSHUNT_DIV;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return vshunt;
}

/**
 * @brief  Read the power value
 */
uint32_t ina230_get_power(ina230_dev_ptr_t ina230_hdl)
{
    uint32_t rslt;
    uint16_t val;
    uint32_t power=0;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        rslt = ina230_readreg(ina230_hdl, INA230_REG_PWR,&val);
        if(rslt==INA230_SCS)
        {
            power = val * POWER_LSB;
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return power;
}

/**
 * @brief  Read the current value
 */
float ina230_get_current(ina230_dev_ptr_t ina230_hdl)
{
    float current=0;
    uint16_t temp;
    uint8_t sts;
    sts = null_ptr_check_ina230(ina230_hdl);
    if (sts != INA230_OK)
    {
        sts = INA230_E_NULL_PTR;
    }
    else
    {
        ina230_readreg(ina230_hdl, INA230_REG_CURRENT,&temp);
        current = ((temp*CURR_MULTIPLIER)/1000);
    }
    return current;
}

static const uint16_t aMode[INA230_OPERATING_MODE_MAX][INA230_VOLTAGE_INPUT_MAX] = {
    {
        INA230_MODE_TRIGGERED_VSHUNT,
        INA230_MODE_TRIGGERED_VBUS,
        INA230_MODE_TRIGGERED_ALL
    },
    {
        INA230_MODE_CONTINOUS_VSHUNT,
        INA230_MODE_CONTINOUS_VBUS,
        INA230_MODE_CONTINOUS_ALL
    }
};

static const uint16_t aflags[INA230_FLAG_MAX] =
{
    INA230_REG_MASK_ENABLE_AFF,
    INA230_REG_MASK_ENABLE_CVRF,
    INA230_REG_MASK_ENABLE_OVF
};

/**
 * @brief  Launch the conversion on the selected voltage input
 */
e_ina230_sts ina230_startconversion(ina230_dev_ptr_t ina230_hdl, ina230_inputsignal_t inputsignal, ina230_operatingmode_t mode)
{
    e_ina230_sts rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t cfg = 0;
        cfg = ina230_readreg(ina230_hdl, INA230_REG_CONFIG,&cfg);
        if(rslt==INA230_SCS)
        {
            cfg = (cfg & ((uint16_t)~(INA230_REG_CFG_MODE_Msk))) | aMode[mode][inputsignal];
            rslt=ina230_writereg(ina230_hdl, INA230_REG_CONFIG, cfg);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return (rslt);
}

/**
 * @brief  Read the designed flag value
 */
uint8_t ina230_get_flag(ina230_dev_ptr_t ina230_hdl, ina230_flag_t flag)
{
    uint8_t rslt;
    rslt = null_ptr_check_ina230(ina230_hdl);
    if (rslt != INA230_OK)
    {
        rslt = INA230_E_NULL_PTR;
    }
    else
    {
        uint16_t flags;
        flags = ina230_readreg(ina230_hdl, INA230_REG_MASK_ENABLE,&flags) & REG_MASK_ENABLE_FLAGS_Msk;
        if(rslt==INA230_SCS)
        {
            rslt= ((aflags[flag] & flags) == aflags[flag]);
        }
        else
        {
            rslt=INA230_E_READ_FAIL;
        }
    }
    return rslt;
}

/**
 * @brief This API is used to validate the device structure pointer for null conditions.
 */
static  int8_t null_ptr_check_ina230(ina230_dev_ptr_t ina230_hdl)
{
    int8_t rslt;
    if ((ina230_hdl == NULL) || (ina230_hdl->read == NULL) || (ina230_hdl->write == NULL))
    {
        rslt=INA230_E_NULL_PTR;
    }
    else
    {
        rslt=INA230_OK;
    }
    return rslt;
}


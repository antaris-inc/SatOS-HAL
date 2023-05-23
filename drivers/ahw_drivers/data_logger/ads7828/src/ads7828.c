/**
 * @file ads7828.c
 *
 * @brief This file has the driver function of data acquisition device ADS7828
 *
 * @copyright Copyright (c) 2023 Antaris, Inc.
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

#include "ads7828.h"

/*!
 * @brief This API is used to check null pointer
 */
static e_ads7828_err ads7828_null_ptr_check(const s_ads7828* dev)
{
    e_ads7828_err ret;

    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL))
    {
        ret = ADS7828_NULL_PTR;
    }
    else
    {
        ret = ADS7828_SCS;
    }
    return ret;
}

/*!
 * @brief This API is used to get the data from specified channel number
 */
e_ads7828_err ads7828_get_data(s_ads7828* ads7828_hdl,e_ads7828_chnl chnl,e_ads7828_pd_sel pd_opt,uint16_t* data)
{
    e_ads7828_err ret =ADS7828_ERR;
    if(ads7828_null_ptr_check(ads7828_hdl)!=ADS7828_NULL_PTR)
    {
        uint8_t cmd=0;
        uint8_t response[2]={0};
        if(chnl<ADS7828_CH_MAX)
        {
            cmd=((uint8_t)chnl<<4) | ((uint8_t)pd_opt<<2);
            if(ads7828_hdl->write(ads7828_hdl->intf_hdl,ads7828_hdl->slv_addr,&cmd,1) == ADS7828_SCS)
            {
                if(ads7828_hdl->read(ads7828_hdl->intf_hdl,ads7828_hdl->slv_addr,response,2) == ADS7828_SCS)
                {
                    *data = response[1]|response[0];
                }
            }
            else
            {

                ret =ADS7828_COM_ERR;
            }
        }
        else
        {
            ret =ADS7828_INVLD_ARG;
        }
    }
    else
    {
        ret=ADS7828_NULL_PTR;
    }

    return ret;

}


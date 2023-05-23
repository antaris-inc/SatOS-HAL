/**
 * @file exo_ahdlsd.c
 *
 * @brief This file contains function definition for
 * device discovery management of application hardware
 *
 * @copyright Copyright 2023 Antaris, Inc.
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

#include "exo_ahdlsd.h"
#include <stdlib.h>
#include <string.h>

ahdlsd_info_s ahdlsd_info;

//TODO application id registration has to be managed by coreos and notification has to be managed by coreos
//discovery module will notify only to coreos

/**
 * @brief This API update the application hardware discovery state
 */
hal_ret_sts ahdlsd_updt_ah_state(ahw_inst_id_t ah_type, hal_ah_disc_state state)
{
    hal_ret_sts sts = HAL_MAX_ERR;
    if(ah_type < MAX_AH_INST_ID)
    {
        ahdlsd_info.ah_disc_info[ah_type].id = ah_type;
        ahdlsd_info.ah_disc_info[ah_type].state = state;
        sts = HAL_SCS;
        if(AH_ERROR == state)
        {
            sts = ahdlsd_snd_ntf(&(ahdlsd_info.ah_disc_info[ah_type]));
        }
    }
    else
    {
        sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief This API send the IPC incase of device discovery
 */
hal_ret_sts ahdlsd_snd_ntf(ah_disc_info_s *ah_disc_info)
{
    hal_ret_sts sts = HAL_MAX_ERR;
    ah_disc_info_s *pld;
    uint32 pld_len = sizeof(ah_disc_info_s);
    pld = malloc(pld_len);
    if(NULL != pld)
    {
        memcpy((void*)pld, (const void *)ah_disc_info, pld_len);

        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_MEM_ALLOC_ERR;
    }
    return sts;
}

/**
 * @brief This API get the application hardware discovery state
 */
hal_ret_sts ahdlsd_get_ah_sts(ah_disc_info_s *ah_disc_info)
{
    hal_ret_sts sts = HAL_MAX_ERR;
    ahw_inst_id_t ah_id = ah_disc_info->id;
    if(ah_id < MAX_AH_INST_ID)
    {
        ah_disc_info->state = ahdlsd_info.ah_disc_info[ah_id].state;
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_AH_INVLD_INST_ID;
    }
    return sts;
}

/**
 * @brief This API gets the application hardware list
 */
hal_ret_sts ahdlsd_get_cplt_ah_list(void)
{
    hal_ret_sts sts = HAL_MAX_ERR;
    ahdlsd_info_s *pld;
    uint32 pld_len = sizeof(ahdlsd_info_s);
    pld = malloc(pld_len);
    if(NULL != pld)
    {
        memcpy((void *)pld,(const void *)&ahdlsd_info,pld_len);
        sts = HAL_SCS;
    }
    else
    {
        sts = HAL_MEM_ALLOC_ERR;
    }
    return sts;
}

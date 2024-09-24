/*
 * @file csp_if.c
 *
 * @brief This file contains CSP interface initialization
 *
 * @copyright Copyright 2024 Antaris, Inc.
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
 *
 */

#include "csp_if.h"
#include "csp_comms.h"
#include "csp_if_sltcp.h"
#include "csp_if_sludp.h"
#include <errno.h>

/**
 * @brief This function handle CSP respected interface initialization
 */
int csp_intf_init(io_intf_type intf_type, void* intf_instance_ptr, csp_iface_t** iface)
{
    int ret=0;
    if(intf_instance_ptr==NULL)
    {
        ret =-1;
    }
    else
    {
        switch(intf_type)
        {

            case UART:
            {
                int error = csp_usart_open_and_add_kiss_interface(intf_instance_ptr,CSP_IF_KISS_DEFAULT_NAME,iface);
                if (error != CSP_ERR_NONE)
                {
                    DEBUG_CPRINT(("failed to add KISS interface - %d\n", error));
                    ret =-1;
                }
                else
                {
                    ret=0;
                }

                break;
            }
#ifdef CSP_FREERTOS
            case CAN:
            {
                *iface =csp_can_init("can_intf",intf_instance_ptr);
                if(iface!=NULL)
                {
                    ret=0;
                }
                else
                {
                    ret=-1;
                    break;
                }

                break;
            }
#endif

            case ETHERNET:
            {
                uint8_t opt = 0;
                memcpy(&opt, intf_instance_ptr,sizeof(uint8_t));

                switch(opt)
                {
                    case S2_DEFAULT_BK:
                    {
#ifndef GSOBC_TCP_EN
                        DEBUG_CPRINT(("Ethernet currently handled using UDP\n"));
                        //csp_sludp_init("eno1", NULL, iface);
#else

                        DEBUG_CPRINT(("Ethernet currently handled using TCP %d\n", opt));
                        DEBUG_CPRINT(("bk init \n"));
                        //csp_sltcp_init_gs2("eno1", NULL, iface);
#endif
                    }
                    break;

//#ifdef LINUX_TEMP_PORT
                    case S3_UHF_HWIL_GS3:
                    {
                        DEBUG_CPRINT(("S3 init \n"));
                        csp_sltcp_init_uhf("eno1", NULL, iface);

                        DEBUG_CPRINT(("Ethernet currently handled using TCP\n"));
                        //csp_sludp_init("eno1", NULL, iface);
                    }
                    break;
//#endif
                }
            }
            break;

            default:
            {
                DEBUG_CPRINT(("check interface type %d \n", intf_type));
                ret=-1;
            }
            break;

        }
    }
    return (ret);
}



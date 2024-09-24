/*
 * csp_if.h
 *
 *  Created on: 29-Aug-2022
 *      Author: Build_usr
 */

#ifndef EXO_STACK_LIBCSP_INCLUDE_CSP_INTERFACES_CSP_IF_H_
#define EXO_STACK_LIBCSP_INCLUDE_CSP_INTERFACES_CSP_IF_H_

#include "csp_types.h"
#include "csp.h"
//#include "csp_init.h"
#include "usart.h"
#include "csp_if_kiss.h"
#include "csp_can.h"
//#include "csp_conn.h"
#include "csp_if_zmqhub.h"
#include "csp_thread.h"

/**
* @brief  Initializes a CSP interface
* 
* This function initializes a CSP interface based on the provided interface 
* type, instance pointer, and interface pointer.
*
* @param[in]  intf_type - The type of interface to initialize (UART, CAN, Ethernet, etc)
* @param[in]  intf_instance_ptr - Pointer to the interface instance 
* @param[out] iface - Pointer to the CSP interface handle to initialize
* 
* @retval ret - 0 on success, negative value on failure
*/
int csp_intf_init(io_intf_type intf_type, void* intf_instance_ptr, csp_iface_t ** iface);

#endif /* EXO_STACK_LIBCSP_INCLUDE_CSP_INTERFACES_CSP_IF_H_ */

/**
 * @file mcp23008_gpio_expander.h
 *
 * @brief This file contains declaration of API's,enumerations,structure
 *  definition and macros of GPIO expander MCP23008
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
 */

#ifndef DRIVERS_AHW_DRIVERS_GPIO_EXPANDER_MCP23008_INC_MCP23008_GPIO_EXPANDER_H_
#define DRIVERS_AHW_DRIVERS_GPIO_EXPANDER_MCP23008_INC_MCP23008_GPIO_EXPANDER_H_

/*Includes --------------------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>

#define IODIR    	0x00      ///< I/O DIRECTION (IODIR) REGISTER
#define IPOL     	0x01      ///< INPUT POLARITY (IPOL) REGISTER
#define GPINTEN  	0x02      ///< INTERRUPT-ON-CHANGE CONTROL (GPINTEN) REGISTER
#define DEFVAL   	0x03      ///< DEFAULT COMPARE (DEFVAL) REGISTER FOR INTERRUPT-ONCHANGE
#define INTCON   	0x04      ///< INTERRUPT CONTROL (INTCON) REGISTER
#define IOCON    	0x05      ///< CONFIGURATION (IOCON) REGISTER
#define GPPU     	0x06      ///< PULL-UP RESISTOR CONFIGURATION (GPPU)REGISTER
#define INTF     	0x07      ///< INTERRUPT FLAG (INTF)REGISTER
#define INTCAP   	0x08      ///< INTERRUPT CAPTURE (INTCAP) REGISTER
#define GPIO_PORT  	0x09      ///< PORT (GPIO) REGISTER
#define OLAT     	0x0A      ///< OUTPUT LATCH REGISTER (OLAT)


/**
 * @brief  read API function pointer
 */
typedef int8_t (*mcp23008_read_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief  write API function pointer
 */
typedef int8_t (*mcp23008_write_fptr_t)(void* intf_hdl, uint16_t slv_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief  Interrupt callback function pointer
 */
typedef void (*mcp23008_cb_fptr_t)(void* args);


/**
 * @brief  mcp23008 error status enumeration
 */
typedef enum
{
    MCP23008_SCS        =  0,				///< mcp23008 success
    MCP23008_ERR        = -1,				///< mcp23008 error
    MCP23008_INVLD_ARG  = -2,				///< mcp23008 invalid argument
    MCP23008_ALRDY_USD  = -3,				///< mcp23008 already used
    MCP23008_COM_ERR    = -4,				///< mcp23008 communication error
    MCP23008_NULL_PTR   = -5,				///< mcp23008 NULL pointer
    MCP23008_ERR_MAX    = -6

}e_mcp23008_err;

/**
 * @brief  mcp23008 interrupt control block
 */
typedef struct
{
    mcp23008_cb_fptr_t callback_func;  /*!< Interrupt callback function pointer */
    void* cb_func_args;             /*!< Interrupt callback function argument*/
}s_mcp23008_intr_info;

/**
 * @brief  mcp23008  control block structure definition
 */
typedef struct
{
    void* intf_hdl;					/*!< IO interface handle pointer		*/
    uint16_t slv_addr;				/*!< slave address						*/
    uint8_t intr_pin_plrty;			/*!< polarity of interrupt pin 	        */
    mcp23008_read_fptr_t read;      /*!< Read API function pointer          */
    mcp23008_write_fptr_t write;    /*!< Write API function pointer         */
    s_mcp23008_intr_info callback_func_info[8];/*!< Interrupt callback function pointer array  */
}s_mcp23008;


/**
 * @brief  mcp23008 gpio mode enumeration
 */
typedef enum
{
    MCP23008_GPIO_MODE_INPUT,
    MCP23008_GPIO_MODE_OUTPUT,
    MCP23008_GPIO_MODE_IT_RISING,
    MCP23008_GPIO_MODE_IT_FALLING,
    MCP23008_GPIO_MODE_IT_RISING_FALLING,
    MCP23008_GPIO_MODE_MAX
}mcp23008_gpio_mode;

/**
 * @brief  mcp23008 gpio pin enumeration
 */
typedef enum
{
    MCP23008_GPIO_O = 0b00000001,					///< mcp23008 gpio pin 0
    MCP23008_GPIO_1 = 0b00000010,					///< mcp23008 gpio pin 1
    MCP23008_GPIO_2 = 0b00000100,					///< mcp23008 gpio pin 2
    MCP23008_GPIO_3 = 0b00001000,					///< mcp23008 gpio pin 3
    MCP23008_GPIO_4 = 0b00010000,					///< mcp23008 gpio pin 4
    MCP23008_GPIO_5 = 0b00100000,					///< mcp23008 gpio pin 5
    MCP23008_GPIO_6 = 0b01000000,					///< mcp23008 gpio pin 6
    MCP23008_GPIO_7 = 0b10000000,					///< mcp23008 gpio pin 7
    MCP23008_GPIO_MAX = 0b11111111,
}e_gpio_num;

/**
 * @brief  mcp23008 gpio direction enumeration
 */
typedef enum
{
    MCP23008_GPIO_INPUT,				///< mcp23008 gpio pin input
    MCP23008_GPIO_OUTPUT,				///< mcp23008 gpio pin output
    MCP23008_GPIO_DIR_MAX
}e_gpio_dir;

/**
 * @brief  mcp23008  gpio configuration structure definition
 */
typedef struct
{
    uint8_t gpio_bit_msk;				/*!< gpio bit masking			*/
    uint8_t gpio_state;					/*!< gpio pin state		    	*/
    uint8_t mode;					/*!< gpio mode of the pin	*/
    uint8_t pull_up_sts;				/*!< gpio pin pullup status		*/
    mcp23008_cb_fptr_t cb_func;        /*!< gspio interrupt type		*/
    void* cb_func_args;
}s_gpio_config;

/**
 * @brief  mcp23008  gpio pin state enumeration
 */
typedef enum
{
    MCP23008_GPIO_LOW,							///< mcp23008 gpio pin low
    MCP23008_GPIO_HIGH,							///< mcp23008 gpio pin high
    MCP23008_GPIO_STE_MAX
}e_gpio_pin_ste;

/**
 * @brief  mcp23008  gpio pin pullup status enumeration
 */
typedef enum
{
    MCP23008_PULLUP_ENABLE,						///< mcp23008 gpio pin enable
    MCP23008_PULLUP_DISABLE,					///< mcp23008 gpio pin disable
    MCP23008_PULLUP_MAX
}e_gpio_pullup_sts;

/**
 * @brief  mcp23008 interrupt pin polarity enumeration
 */
typedef enum
{
    MCP23008_INT_ACT_LOW,						///< mcp23008 interrupt pin low
    MCP23008_INT_ACT_HIGH,						///< mcp23008 interrupt pin high
    MCP23008_INT_HIGH_IMPEDANCE,				///< mcp23008 interrupt pin high impedance
    MCP23008_INT_PLRTY_MAX
}e_int_pin_plrty;

/**
 * @brief  mcp23008  gpio interrupt type
 */
typedef enum
{
    MCP23008_GPIO_INTR_DISABLE,							///< mcp23008 gpio interrupt disable
    MCP23008_GPIO_INTR_RISING_FALLING,						///< mcp23008 gpio pin change interrupt
    MCP23008_GPIO_INTR_RISING,							///< mcp23008 gpio interrupt rising
    MCP23008_GPIO_INTR_FALLING,							///< mcp23008 gpio interrupt falling
    MCP23008_GPIO_INTR_MAX
}e_gpio_intr_typ;

/**
 * @brief This function is used to check the interrupt status
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[out] intr_sts - data gets updated in intr_sts
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_check_intr_sts (s_mcp23008* mcp23008_hdl, uint8_t* intr_sts);

/**
 * @brief This function configure the interrupt
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @param[in] intr_typ - interrupt type to be configured to gpio pin
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_interrupt_cfg (s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_intr_typ intr_typ);

/**
 * @brief This function is used to enable the pullup configuration
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_pullup_enable (s_mcp23008* mcp23008_hdl, uint8_t gpio_pin);

/**
 * @brief This function is used to disable the pullup configuration
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_pullup_disable (s_mcp23008* mcp23008_hdl, uint8_t gpio_pin);
/**
 * @brief This function is used to set the GPIO direction
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @param[in] gpio_dir - direction of the gpio pin to be set
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_set_direction (s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_dir gpio_dir);

/**
 * @brief This function is used to write the GPIO with specified state
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @param[in] gpio_ste - gpio pin state
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_write_pin(s_mcp23008* mcp23008_hdl, uint8_t gpio_pin, e_gpio_pin_ste gpio_ste);

/**
 * @brief This function is used to read the GPIO
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @retval e_mcp23008_err - returns the success or error code
 */
e_gpio_pin_ste mcp23008_read_pin (s_mcp23008* mcp23008_hdl, e_gpio_num gpio_pin);

/**
 * @brief This function is used to read to write and read data to validate gpio expender
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_self_test(s_mcp23008* mcp23008_hdl);
/**
 * @brief This function is used to toggle the GPIO
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - gpio pin number
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_toggle_pin (s_mcp23008* mcp23008_hdl, uint8_t gpio_pin);

/**
 * @brief This function is used to configure the pin
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] gpio_pin - pointer of gpio pin configuration
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_config_pin(s_mcp23008* mcp23008_hdl, s_gpio_config* gpio_pin);

/**
 * @brief This function is used to set the input pin polarity
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @param[in] polarity - polarity to be set
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_int_pin_polarity_cfg(s_mcp23008* mcp23008_hdl,e_int_pin_plrty polarity);

/**
 * @brief This function is used to clear the interrupt
 * @param[in] mcp23008_hdl - instance pointer of mcp23008
 * @retval e_mcp23008_err - returns the success or error code
 */
e_mcp23008_err mcp23008_clear_interrupt(s_mcp23008* mcp23008_hdl);

#endif /* DRIVERS_AHW_DRIVERS_GPIO_EXPANDER_MCP23008_INC_MCP23008_GPIO_EXPANDER_H_ */

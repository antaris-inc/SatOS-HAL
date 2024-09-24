/**
 * @file pcal6408a_gpio_expander.h
 *
 * @brief This file contains function prototypes ,macros,enumeration and
 * structure definition of PCAL6408 GPIO expander
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

#ifndef GPIO_EXP_PCAL6408A_H_
#define GPIO_EXP_PCAL6408A_H_

#include <stdint.h>
#include <string.h>

/// Error code definitions
#define PCAL6408A_OK                          INT8_C(0)     ///< Success return value
#define PCAL6408A_E_NULL_PTR                  INT8_C(-1)    ///< Null pointer return value
#define PCAL6408A_E_READ_WRITE_LENGTH_INVALID INT8_C(-2)    ///< Invalid read write length return value
#define PCAL6408A_E_OUT_OF_RANGE              INT8_C(-3)    ///< out of range return value
#define PCAL6408A_E_COM_FAIL				  INT8_C(-4)	///< INA230 communication fail

/// Register address
#define PCAL6408_REG_INPUT                    UINT8_C(0x00) ///< Input port register
#define PCAL6408_REG_OUTPUT                   UINT8_C(0x01) ///< Output port register
#define PCAL6408_REG_POLARITY_INVERSION       UINT8_C(0x02) ///< Polarity inversion register
#define PCAL6408_REG_CONFIG                   UINT8_C(0x03) ///< Configuration register
#define PCAL6408_REG_OUT_STRENGTH0            UINT8_C(0x40) ///< Output drive strength register 1
#define PCAL6408_REG_OUT_STRENGTH1            UINT8_C(0x41) ///< Output drive strength register 2
#define PCAL6408_REG_INPUT_LATCH              UINT8_C(0x42) ///< Input latch register
#define PCAL6408_REG_PULL_ENABLE              UINT8_C(0x43) ///< Pull-up/pull-down enable register
#define PCAL6408_REG_PULL_UP_DOWN             UINT8_C(0x44) ///< Pull-up/pull-down selection register
#define PCAL6408_REG_INT_MASK                 UINT8_C(0x45) ///< Interrupt mask register
#define PCAL6408_REG_INT_STATUS               UINT8_C(0x46) ///< Interrupt status register
#define PCAL6408_REG_OUT_CONFIG               UINT8_C(0x4f) ///< Output port configuration register


#define PCAL6408_REG_OUT_STRENGTH_MASK        UINT8_C(0x3) ///< Output strength mask

/**@}*/
/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL                                      0
#else
#define NULL                                      ((void *) 0)
#endif
#endif

/*****************************************************************************/
/** 
 * @brief  GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
    PIN_RESET = 0,           ///< Pin state is zero
    PIN_SET                  ///< Pin state is one
}pcal6408a_gpio_pinstate;

/** 
 * @brief  Interrupt state status enumeration
 */
typedef enum
{
    SOURCE_FALSE = 0,             ///< Pin is not the source of the interrupt
    SOURCE_TRUE                   ///< Pin is the source of the interrupt
}pcal6408a_gpio_intrstate;

/** 
 * @brief  Pin polarity status enumeration
 */
typedef enum
{
    ORIGINAL = 0,                ///< Polarity is in the original state
    INVERTED                     ///< Polarity is in the inverted state
}pcal6408a_pin_pol;

/** 
 * @brief  latch status enumeration
 */
typedef enum
{
    NO_LATCH = 0,                ///< latch is not enabled
    LATCH                        ///< pin is latched
}pcal6408a_pin_lat;

/** 
 * @brief  pull enable status enumeration
 */
typedef enum
{
    PULL_DISABLED = 0,           ///< pull configuration is disabled
    PULL_ENABLED                 ///< pull configuration is enabled
}pcal6408a_pin_pull;

/** 
 * @brief  pull up - pull down status enumeration
 */
typedef enum
{
    PULL_DOWN = 0,          ///< pin is configured for pull down
    PULL_UP,                ///< pin is configured for pull up
    NO_PULL                 ///< pin is configured for no pull
}pcal6408a_pin_up_dwn;

/** 
 * @brief  Interrupt status enumeration
 */
typedef enum
{
    INTRUPT_RISING = 0,     ///< Interrupt on rising edge
    INTRUPT_FALLING,        ///< Interrupt on falling edge
    INTRUPT_ANY_EDGE,       ///< Interrupt on any edge
    INTRUPT_DISABLE         ///< Interrupt disable
}pcal6408a_intr_mode;

/** 
 * @brief  port configuration status enumeration
 */
typedef enum
{
    PUSH_PULL = 0,           ///< Pin is configured as push pull
    OPEN_DRAIN               ///< Pin is configured as open drain
}pcal6408a_port_cfg;

/** 
 * @brief  Expander gpio pin enumeration
 */
typedef enum
{
    PCAL6408A_GPIO_0 = 0b00000001,        ///< Expander gpio pin 0
    PCAL6408A_GPIO_1 = 0b00000010,        ///< Expander gpio pin 1
    PCAL6408A_GPIO_2 = 0b00000100,        ///< Expander gpio pin 2
    PCAL6408A_GPIO_3 = 0b00001000,        ///< Expander gpio pin 3
    PCAL6408A_GPIO_4 = 0b00010000,        ///< Expander gpio pin 4
    PCAL6408A_GPIO_5 = 0b00100000,        ///< Expander gpio pin 5
    PCAL6408A_GPIO_6 = 0b01000000,        ///< Expander gpio pin 6
    PCAL6408A_GPIO_7 = 0b10000000,        ///< Expander gpio pin 7
    PCAL6408A_GPIO_MAX = 0b11111111,
}pcal6408a_gpio_pin;

/** 
 * @brief  Expander gpio pin enumeration
 */
typedef enum{
    OUTPUT,                ///< Pin output state
    INPUT                  ///< Pin input state
}pcal6408a_pin_dir;

/** 
 * @brief   Output drive strength enumeration
 */
typedef enum{
    C25LEVEL,                 ///< 0.25 of drive capability of the I/O
    C50LEVEL,                 ///< 0.50 of drive capability of the I/O
    C75LEVEL,                 ///< 0.75 of drive capability of the I/O
    C100LEVEL                 ///< same drive capability of the I/O
}pcal6408a_pin_strgth;

/**
 * @brief  mcp23008 gpio mode enumeration
 */
typedef enum
{
    PCAL6408A_GPIO_MODE_INPUT,
    PCAL6408A_GPIO_MODE_OUTPUT,
    PCAL6408A_GPIO_MODE_IT_RISING,
    PCAL6408A_GPIO_MODE_IT_FALLING,
    PCAL6408A_GPIO_MODE_IT_RISING_FALLING,
    PCAL6408A_GPIO_MODE_MAX
}pcal6408a_gpio_mode;

/**
 * @brief Bus communication function pointer which should be mapped to
 * the platform specific read functions of the user
 */
typedef uint8_t (*pcal6408a_read_fptr_t)(void *hi2c, uint16_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
 * @brief Bus communication function pointer which should be mapped to
 * the platform specific write functions of the user
 */
typedef uint8_t (*pcal6408a_write_fptr_t)(void *hi2c, uint16_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);

/**
 * @brief Bus communication function pointer which should be mapped to
 * the platform specific delay functions of the user
 */
typedef void (*pcal6408a_delay_fptr_t)(uint32_t period);

/**
 * @brief  Interrupt callback function pointer
 */
typedef void (*pcal6408a_cb_fptr_t)(void* args);

/*************************** Data structures *********************************/

/**
 * @brief  pcal6408a interrupt control block
 */
typedef struct
{
    uint8_t intr_typ;                   /*!< Interrupt type */
    pcal6408a_cb_fptr_t callback_func;  /*!< Interrupt callback function pointer */
    void* cb_func_args;                 /*!< Interrupt callback function argument*/
}pcal6408a_intr_info;

/**
 * @brief pcal6408a expander device structure definition
 *
 */
typedef struct _pcal6408a_dev
{
    uint8_t  slave_addr;               /*!< Chip address 					*/
    void  *io_intf_hdle;               /*!< 0 - I2C Instance handle pointer */
    pcal6408a_read_fptr_t  read;       /*!< Read function pointer 			*/
    pcal6408a_write_fptr_t write;      /*!< Write function pointer 			*/
    pcal6408a_intr_info intr_info[8];  /*!< Interrupt information structure array  	*/
} pcal6408a_dev;

/**
 * @brief pcal6408a expander gpio configuration structure definition
 */
typedef struct __pcal6408a_gpio_cfg
{
    uint8_t pin_num ;         	  /*!< gpio pin number 							*/
    uint8_t mode;                 /*!< gpio mode 				        */
    uint8_t strength;             /*!< gpio pin strength 						*/
    uint8_t polarity_inv;         /*!< gpio pin polarity inversion 				*/
    uint8_t latch;                /*!< gpio pin latch status 					*/
    uint8_t pull_sts;             /*!< gpio pin pull enable status 				*/
    pcal6408a_cb_fptr_t cb_func;  /*!< gpio interrupt callback function		*/
    void* cb_func_args;           /*!< gpio interrupt callback fuction argument pointer		*/
}pcal6408a_gpio_cfg;

/**
 * @brief This API initializes the gpio pin as per the gpio_config. This api
 * needs to be called for all the gpio expander pins.
 * @param[in] hdev        : Structure instance of pcal6408a_dev.
 * @param[in] gpio_config : configuration of the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_gpio_init(pcal6408a_dev *hdev);

/**
 * @brief This API used to read data from register and write  to validate GPIO expender
 * @param[in] hdev        : Structure instance of pcal6408a_dev.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_self_test(pcal6408a_dev *hdev);

/**
 * @brief This API is used to read the pcal6408a registers through i2c interface
 * @param[in] hdev   : Structure instance of pcal6408a_dev.
 * @param[in] reg    : Address of the register that needs to be read
 * @param[out] data  : Data that is read from the register
 * @param[in] len    : size of data to be read
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_read(pcal6408a_dev *hdev, uint8_t reg, uint8_t *data, uint16_t len);

/**
 * @brief This API is used to write the pcal6408a registers through i2c interface
 * @param[in] hdev   : Structure instance of pcal6408a_dev.
 * @param[in] reg    : Address of the register that needs to be written
 * @param[in] data   : Data to be written to the register
 * @param[in] len    : size of data to be written
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_write(pcal6408a_dev *hdev, uint8_t reg, uint8_t *data, uint16_t len);

/**
 * @brief This API is used to read the state of the gpio pin
 * @param[in] hdev    : Structure instance of pcal6408a_dev.
 * @param[in] pin     : pin whose state needs to be read
 * @param[out] state  : state of the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_readpin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_gpio_pinstate *state);

/**
 * @brief This API is used to write the state of the gpio pin
 * @param[in] hdev    : Structure instance of pcal6408a_dev.
 * @param[in] pin     : pin whose state needs to be changed
 * @param[in] state   : state of the gpio pin that will be set to the gpio pin
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_writepin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_gpio_pinstate state);

/**
 * @brief This API is used to toggle the state of the gpio pin
 * @param[in] hdev    : Structure instance of pcal6408a_dev.
 * @param[in] pin     : pin whose state needs to be toggled
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_togglepin(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin);

/**
 * @brief This API configures the gpio pin to be either input (dir = 0) or
 * output (dir = 1)
 * @param[in] hdev  : Structure instance of pcal6408a_dev.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] dir   : direction to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_dir(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_dir dir);

/**
 * @brief This API configures the output drive level of the GPIO pin.
 * The output drive level of the GPIO can be programmed 00b = 0.25x, 01b = 0.5x,
 * 10b = 0.75x or 11b = 1x of the drive capability of the I/O. 
 * @param[in] hdev  : Structure instance of pcal6408a_dev.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] strength   : strength to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_strength(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_strgth strength);

/**
 * @brief This API configures the polarity inversion of pins defined as 
 * inputs. Invoking this api with polarity = INVERTED will invert the 
 * pin's polarity to be inverted and polarity = ORIGINAL will retain the
 * original polarity.
 * @param[in] hdev     : Structure instance of pcal6408a_dev.
 * @param[in] pin      : gpio pin to be configured.
 * @param[in] polarity : polarity to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_pol_inv(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_pol polarity);

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin. This is effective only when the pin is configured as an INPUT.
 * Invoking this api with latch = NO_LATCH will set the corresponding input
 * pin state as not latched and latch = LATCH ,will the corresponding input 
 * pin state as latched.
 * @param[in] hdev  : Structure instance of pcal6408a_dev.
 * @param[in] pin   : gpio pin to be configured.
 * @param[in] latch : latch to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_input_latch(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_lat latch);

/**
 * @brief This API enables or disables pull-up/pull-down resistors on the
 * corresponding gpio. Setting the flag to PULL_ENABLED enables the
 * selection of pull-up/pull-down the flag to PULL_DISABLED disconnects
 * the pull-up/pull-down resistors from the corresponding gpio pin. Also, the
 * resistors are disconnected when the outputs are configured as open-drain outputs
 * @param[in] hdev : Structure instance of pcal6408a_dev.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull enable or disable to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_enable_pull(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_pull flag);

/**
 * @brief This API configures the gpio to have pull-up or pull-down resistor by
 * programming the pull-up/pull-down selection register. Setting the flag to
 * PULL_UP selects a 100 kohm pull-up resistor for that I/O pin. Setting the
 * flag to PULL_DOWN selects a 100 kohm pull-down resistor for that I/O pin.
 * If the pull-up/down feature is disconnected, writing to this register has
 * no effect on I/O pin.
 * @param[in] hdev : Structure instance of pcal6408a_dev.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : pull up or pull down to be assigned to the gpio pin.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_pull_up_dwn(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_pin_up_dwn flag);

/**
 * @brief This API configures the output port as push-pull or open-drain.
 * Setting the flag as PUSH_PULL will configure the pin as as push-pull
 * Setting the flag as OPEN_DRAIN will configure the pin as open-drain
 * and the recommended command sequence is to call this api before
 *  the pcal6408a_set_dir sets the port pins as outputs
 * @param[in] hdev : Structure instance of pcal6408a_dev.
 * @param[in] pin  : gpio pin to be configured.
 * @param[in] flag : sets the gpio pin as PUSH_PULL or OPEN_DRAIN.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_set_port_cfg(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin, pcal6408a_port_cfg flag);

/**
 * @brief This API is used to identify the source of an interrupt.
 * state = SOURCE_TRUE indicates that the corresponding input pin 
 * was the source of the interrupt. state = SOURCE_FALSE indicates
 * that the input pin is not the source of an interrupt. When a corresponding
 * bit in the interrupt mask register is set to 1 (masked), the interrupt
 * state will be set to SOURCE_FALSE
 * @param[in] hdev   : Structure instance of pcal6408a_dev.
 * @param[in] intr_flg    : pointer to isr flag.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_read_intr_sts(pcal6408a_dev *hdev, uint8_t* intr_flg);

/**
 * @brief This API is used to get the configurations parameters of the gpio pin.
 * @param[in] pin          : gpio pin whose configuration is needed.
 * @param[out] gpio_config : Structure instance of pcal6408a_gpio_cfg to which 
 *                           the configuration parameters will be copied.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_get_gpio_cfg(pcal6408a_gpio_pin pin, pcal6408a_gpio_cfg *gpio_config);

/**
 * @brief This API enables or disables the input latch of the corresponding
 * gpio pin. This is effective only when the pin is configured as an INPUT
 * @param[out] hdev          : gpio input pin latch
 * @param[in] pin : Structure instance of pcal6408a_gpio_cfg to which 
 *                           the configuration parameters will be copied.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
pcal6408a_pin_lat pcal6408a_get_input_latch(pcal6408a_dev *hdev, pcal6408a_gpio_pin pin);

/**
 * @brief This API is used to get the configurations parameters of the gpio pin.
 * @param[in] hdev          : gpio pin whose configuration is needed.
 * @param[in] gpio_config : Structure instance of pcal6408a_gpio_cfg to which 
 *                           the configuration parameters will be copied.
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t pcal6408a_gpio_pin_cfg(pcal6408a_dev *hdev, pcal6408a_gpio_cfg *gpio_config);

#endif /*GPIO_EXP_PCAL6408A_H_ */

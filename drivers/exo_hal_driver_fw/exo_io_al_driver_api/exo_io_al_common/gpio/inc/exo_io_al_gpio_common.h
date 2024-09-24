/**
 * @file exo_io_al_gpio_common.h
 *
 * @brief This file contains structures,enumerations
 * and function declaration for IOAL common GPIO.
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

#ifndef _IO_HAL_GPIO_COMMON_H_
#define _IO_HAL_GPIO_COMMON_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define EXTI_INTF_ENB
#define GPIO_INTF_ENB

/**
 * @brief Enumeration for GPIO modes.
 *
 * This enumeration defines the different modes for configuring GPIO pins.
 */
typedef enum
{
    IOAL_GPIO_MODE_INPUT,           ///< GPIO pin configured as input.
    IOAL_GPIO_MODE_OUTPUT_PP,       ///< GPIO pin configured as push-pull output.
    IOAL_GPIO_MODE_OUTPUT_OD,       ///< GPIO pin configured as open-drain output.
    IOAL_GPIO_MODE_IT_RISING,       ///< GPIO pin configured to trigger an interrupt on a rising edge.
    IOAL_GPIO_MODE_IT_FALLING,      ///< GPIO pin configured to trigger an interrupt on a falling edge.
    IOAL_GPIO_MODE_IT_RISING_FALLING, ///< GPIO pin configured to trigger an interrupt on both rising and falling edges.
    IOAL_GPIO_MODE_MAX              ///< Maximum value for GPIO modes; used for validation.
} ioal_gpio_mode;

/**
 * @brief Enumeration for GPIO pull configurations.
 *
 * This enumeration defines the different pull-up/pull-down configurations for GPIO pins.
 */
typedef enum
{
    IOAL_GPIO_NOPULL,               ///< GPIO pin with no pull-up or pull-down resistor.
    IOAL_GPIO_PULLUP,               ///< GPIO pin with pull-up resistor.
    IOAL_GPIO_PULLDOWN,             ///< GPIO pin with pull-down resistor.
    IOAL_PULL_MAX                   ///< Maximum value for pull configurations; used for validation.
} ioal_pull_cfg;

/**
 * @brief Enumeration for GPIO pin numbers.
 *
 * This enumeration defines the available GPIO pin numbers on the device.
 */
typedef enum
{
    IOAL_GPIO_PIN_1,                ///< GPIO pin 1
    IOAL_GPIO_PIN_2,                ///< GPIO pin 2
    IOAL_GPIO_PIN_3,                ///< GPIO pin 3
    IOAL_GPIO_PIN_4,                ///< GPIO pin 4
    IOAL_GPIO_PIN_5,                ///< GPIO pin 5
    IOAL_GPIO_PIN_6,                ///< GPIO pin 6
    IOAL_GPIO_PIN_7,                ///< GPIO pin 7
    IOAL_GPIO_PIN_8,                ///< GPIO pin 8
    IOAL_GPIO_PIN_9,                ///< GPIO pin 9
    IOAL_GPIO_PIN_10,               ///< GPIO pin 10
    IOAL_GPIO_PIN_11,               ///< GPIO pin 11
    IOAL_GPIO_PIN_12,               ///< GPIO pin 12
    IOAL_GPIO_PIN_13,               ///< GPIO pin 13
    IOAL_GPIO_PIN_14,               ///< GPIO pin 14
    IOAL_GPIO_PIN_15,               ///< GPIO pin 15
    IOAL_GPIO_PIN_16,               ///< GPIO pin 16
    IOAL_GPIO_PIN_17,               ///< GPIO pin 17
    IOAL_GPIO_PIN_18,               ///< GPIO pin 18
    IOAL_GPIO_PIN_19,               ///< GPIO pin 19
    IOAL_GPIO_PIN_20,               ///< GPIO pin 20
    IOAL_GPIO_PIN_21,               ///< GPIO pin 21
    IOAL_GPIO_PIN_22,               ///< GPIO pin 22
    IOAL_GPIO_PIN_23,               ///< GPIO pin 23
    IOAL_GPIO_PIN_24,               ///< GPIO pin 24
    IOAL_GPIO_PIN_25,               ///< GPIO pin 25
    IOAL_GPIO_PIN_26,               ///< GPIO pin 26
    IOAL_GPIO_PIN_27,               ///< GPIO pin 27
    IOAL_GPIO_PIN_28,               ///< GPIO pin 28
    IOAL_GPIO_PIN_29,               ///< GPIO pin 29
    IOAL_GPIO_PIN_30,               ///< GPIO pin 30
    IOAL_GPIO_PIN_31,               ///< GPIO pin 31
    IOAL_GPIO_PIN_32,               ///< GPIO pin 32
    IOAL_GPIO_PIN_33,               ///< GPIO pin 33
    IOAL_GPIO_PIN_34,               ///< GPIO pin 34
    IOAL_GPIO_PIN_35,               ///< GPIO pin 35
    IOAL_GPIO_PIN_36,               ///< GPIO pin 36
    IOAL_GPIO_PIN_37,               ///< GPIO pin 37
    IOAL_GPIO_PIN_38,               ///< GPIO pin 38
    IOAL_GPIO_PIN_39,               ///< GPIO pin 39
    IOAL_GPIO_PIN_40,               ///< GPIO pin 40
    IOAL_GPIO_PIN_41,               ///< GPIO pin 41
    IOAL_GPIO_PIN_42,               ///< GPIO pin 42
    IOAL_GPIO_PIN_43,               ///< GPIO pin 43
    IOAL_GPIO_PIN_44,               ///< GPIO pin 44
    IOAL_GPIO_PIN_45,               ///< GPIO pin 45
    IOAL_GPIO_PIN_46,               ///< GPIO pin 46
    IOAL_GPIO_PIN_47,               ///< GPIO pin 47
    IOAL_GPIO_PIN_48,               ///< GPIO pin 48
    IOAL_GPIO_PIN_49,               ///< GPIO pin 49
    IOAL_GPIO_PIN_50,               ///< GPIO pin 50
    IOAL_GPIO_PIN_51,               ///< GPIO pin 51
    IOAL_GPIO_PIN_52,               ///< GPIO pin 52
    IOAL_GPIO_PIN_53,               ///< GPIO pin 53
    IOAL_GPIO_PIN_54,               ///< GPIO pin 54
    IOAL_GPIO_PIN_55,               ///< GPIO pin 55
    IOAL_GPIO_PIN_56,               ///< GPIO pin 56
    IOAL_GPIO_PIN_57,               ///< GPIO pin 57
    IOAL_GPIO_PIN_58,               ///< GPIO pin 58
    IOAL_GPIO_PIN_59,               ///< GPIO pin 59
    IOAL_GPIO_PIN_60,               ///< GPIO pin 60
    IOAL_GPIO_PIN_61,               ///< GPIO pin 61
    IOAL_GPIO_PIN_62,               ///< GPIO pin 62
    IOAL_GPIO_PIN_63,               ///< GPIO pin 63
    IOAL_GPIO_PIN_64,               ///< GPIO pin 64
    IOAL_GPIO_PIN_65,               ///< GPIO pin 65
    IOAL_GPIO_PIN_66,               ///< GPIO pin 66
    IOAL_GPIO_PIN_67,               ///< GPIO pin 67
    IOAL_GPIO_PIN_68,               ///< GPIO pin 68
    IOAL_GPIO_PIN_69,               ///< GPIO pin 69
    IOAL_GPIO_PIN_70,               ///< GPIO pin 70
    IOAL_GPIO_PIN_71,               ///< GPIO pin 71
    IOAL_GPIO_PIN_72,               ///< GPIO pin 72
    IOAL_GPIO_PIN_73,               ///< GPIO pin 73
    IOAL_GPIO_PIN_74,               ///< GPIO pin 74
    IOAL_GPIO_PIN_75,               ///< GPIO pin 75
    IOAL_GPIO_PIN_76,               ///< GPIO pin 76
    IOAL_GPIO_PIN_77,               ///< GPIO pin 77
    IOAL_GPIO_PIN_78,               ///< GPIO pin 78
    IOAL_GPIO_PIN_79,               ///< GPIO pin 79
    IOAL_GPIO_PIN_80,               ///< GPIO pin 80
    IOAL_GPIO_PIN_81,               ///< GPIO pin 81
    IOAL_GPIO_PIN_82,               ///< GPIO pin 82
    IOAL_GPIO_PIN_83,               ///< GPIO pin 83
    IOAL_GPIO_PIN_84,               ///< GPIO pin 84
    IOAL_GPIO_PIN_85,               ///< GPIO pin 85
    IOAL_GPIO_PIN_86,               ///< GPIO pin 86
    IOAL_GPIO_PIN_87,               ///< GPIO pin 87
    IOAL_GPIO_PIN_88,               ///< GPIO pin 88
    IOAL_GPIO_PIN_89,               ///< GPIO pin 89
    IOAL_GPIO_PIN_90,               ///< GPIO pin 90
    IOAL_GPIO_PIN_91,               ///< GPIO pin 91
    IOAL_GPIO_PIN_92,               ///< GPIO pin 92
    IOAL_GPIO_PIN_93,               ///< GPIO pin 93
    IOAL_GPIO_PIN_94,               ///< GPIO pin 94
    IOAL_GPIO_PIN_95,               ///< GPIO pin 95
    IOAL_GPIO_PIN_96,               ///< GPIO pin 96
    IOAL_GPIO_PIN_97,               ///< GPIO pin 97
    IOAL_GPIO_PIN_98,               ///< GPIO pin 98
    IOAL_GPIO_PIN_99,               ///< GPIO pin 99
    IOAL_GPIO_PIN_100,              ///< GPIO pin 100
    IOAL_GPIO_PIN_101,              ///< GPIO pin 101
    IOAL_GPIO_PIN_102,              ///< GPIO pin 102
    IOAL_GPIO_PIN_103,              ///< GPIO pin 103
    IOAL_GPIO_PIN_104,              ///< GPIO pin 104
    IOAL_GPIO_PIN_105,              ///< GPIO pin 105
    IOAL_GPIO_PIN_106,              ///< GPIO pin 106
    IOAL_GPIO_PIN_107,              ///< GPIO pin 107
    IOAL_GPIO_PIN_108,              ///< GPIO pin 108
    IOAL_GPIO_PIN_109,              ///< GPIO pin 109
    IOAL_GPIO_PIN_110,              ///< GPIO pin 110
    IOAL_GPIO_PIN_111,              ///< GPIO pin 111
    IOAL_GPIO_PIN_112,              ///< GPIO pin 112
    IOAL_GPIO_PIN_113,              ///< GPIO pin 113
    IOAL_GPIO_PIN_114,              ///< GPIO pin 114
    IOAL_GPIO_PIN_115,              ///< GPIO pin 115
    IOAL_GPIO_PIN_116,              ///< GPIO pin 116
    IOAL_GPIO_PIN_117,              ///< GPIO pin 117
    IOAL_GPIO_PIN_118,              ///< GPIO pin 118
    IOAL_GPIO_PIN_119,              ///< GPIO pin 119
    IOAL_GPIO_PIN_120,              ///< GPIO pin 120
    IOAL_GPIO_PIN_121,              ///< GPIO pin 121
    IOAL_GPIO_PIN_122,              ///< GPIO pin 122
    IOAL_GPIO_PIN_123,              ///< GPIO pin 123
    IOAL_GPIO_PIN_124,              ///< GPIO pin 124
    IOAL_GPIO_PIN_125,              ///< GPIO pin 125
    IOAL_GPIO_PIN_126,              ///< GPIO pin 126
    IOAL_GPIO_PIN_127,              ///< GPIO pin 127
    IOAL_GPIO_PIN_128,              ///< GPIO pin 128
    IOAL_GPIO_PIN_129,              ///< GPIO pin 129
    IOAL_GPIO_PIN_130,              ///< GPIO pin 130
    IOAL_GPIO_PIN_131,              ///< GPIO pin 131
    IOAL_GPIO_PIN_132,              ///< GPIO pin 132
    IOAL_GPIO_PIN_133,              ///< GPIO pin 133
    IOAL_GPIO_PIN_134,              ///< GPIO pin 134
    IOAL_GPIO_PIN_135,              ///< GPIO pin 135
    IOAL_GPIO_PIN_136,              ///< GPIO pin 136
    IOAL_GPIO_PIN_137,              ///< GPIO pin 137
    IOAL_GPIO_PIN_138,              ///< GPIO pin 138
    IOAL_GPIO_PIN_139,              ///< GPIO pin 139
    IOAL_GPIO_PIN_140,              ///< GPIO pin 140
    IOAL_GPIO_PIN_141,              ///< GPIO pin 141
    IOAL_GPIO_PIN_142,              ///< GPIO pin 142
    IOAL_GPIO_PIN_143,              ///< GPIO pin 143
    IOAL_GPIO_PIN_144,              ///< GPIO pin 144
    IOAL_GPIO_PIN_145,              ///< GPIO pin 145
    IOAL_GPIO_PIN_146,              ///< GPIO pin 146
    IOAL_GPIO_PIN_147,              ///< GPIO pin 147
    IOAL_GPIO_PIN_148,              ///< GPIO pin 148
    IOAL_GPIO_PIN_149,              ///< GPIO pin 149
    IOAL_GPIO_PIN_150,              ///< GPIO pin 150
    IOAL_GPIO_PIN_151,              ///< GPIO pin 151
    IOAL_GPIO_PIN_152,              ///< GPIO pin 152
    IOAL_GPIO_PIN_153,              ///< GPIO pin 153
    IOAL_GPIO_PIN_154,              ///< GPIO pin 154
    IOAL_GPIO_PIN_155,              ///< GPIO pin 155
    IOAL_GPIO_PIN_156,              ///< GPIO pin 156
    IOAL_GPIO_PIN_157,              ///< GPIO pin 157
    IOAL_GPIO_PIN_158,              ///< GPIO pin 158
    IOAL_GPIO_PIN_159,              ///< GPIO pin 159
    IOAL_GPIO_PIN_160,              ///< GPIO pin 160
    IOAL_GPIO_PIN_161,              ///< GPIO pin 161
    IOAL_GPIO_PIN_162,              ///< GPIO pin 162
    IOAL_GPIO_PIN_163,              ///< GPIO pin 163
    IOAL_GPIO_PIN_164,              ///< GPIO pin 164
    IOAL_GPIO_PIN_165,              ///< GPIO pin 165
    IOAL_GPIO_PIN_166,              ///< GPIO pin 166
    IOAL_GPIO_PIN_167,              ///< GPIO pin 167
    IOAL_MAX_GPIO_PIN               ///< Maximum value for GPIO pin numbers; used for validation.
} ioal_gpio_pin_num;

/*!
 * @brief GPIO output logic can be used in iohal_gpio_writepin()
 */
#define GPIO_DRIVE_LOW 0
#define GPIO_DRIVE_HIGH 1

/**
 * @brief ISR_handler function pointer
 */
typedef void (*exti_isr_handler_fptr_t)(void *);

/**
 * @brief External interrupt pointer table structure.
 */
typedef struct
{
    exti_isr_handler_fptr_t isr_handler;              /*!< call back function to be called when interrupt invoked*/
    void *isr_args;						/*!< interface handle of Application hardware drivers*/
} exti_handler_details_t;

/*!
 * @brief GPIO input configuration structure
 */
typedef struct
{
    uint32_t pin_number;       /*!< Specifies the GPIO pins to be configured.
                               This parameter can be any value of @ref GPIO_pins_define */
    uint32_t speed;
    uint32_t mode;          /*!< Specifies the External Interrupt Mode with Input/Rising/Falling edge trigger detection  */
    uint32_t pull_sts;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                               This parameter can be a value of @ref GPIO_pull_define */

    exti_handler_details_t external_int;     /*!< call back function to be called when interrupt invoked*/

}ioal_gpio_config;

/**
 * @brief GPIO speed configuration enumeration.
 */
typedef enum
{
    IOAL_GPIO_SPEED_FREQ_LOW,    ///< Low speed configuration.
    IOAL_GPIO_SPEED_FREQ_MEDIUM, ///< Medium speed configuration.
    IOAL_GPIO_SPEED_FREQ_HIGH,   ///< High speed configuration.
    IOAL_GPIO_SPEED_FREQ_VERY_HIGH, ///< Very high speed configuration.
    IOAL_GPIO_SPEED_FREQ_MAX      ///< Maximum value for GPIO speed configuration.
} ioal_gpio_speed;

/**
 * @brief GPIO pin state enumeration.
 */
typedef enum
{
    IOAL_GPIO_PIN_RESET = 0x0u,  ///< GPIO pin is in the reset (low) state.
    IOAL_GPIO_PIN_SET,           ///< GPIO pin is in the set (high) state.
    IOAL_INVLD_GPIO_PIN_STE   ///< Invalid GPIO pin state.
} ioal_gpio_pinstate;

/**
 * @brief GPIO pin configuration enumeration.
 */
typedef enum
{
    IOAL_GPIO_INPUT_CFG = 0x0u,  ///< GPIO pin is configured as an input.
    IOAL_GPIO_OUTPUT_CFG,        ///< GPIO pin is configured as an output.
    IOAL_GPIO_INTERRUPT_CFG      ///< GPIO pin is configured for interrupt functionality.
} ioal_gpio_pinconfig;

/**
 * @brief Extracted configuration pin deatils structure.
 */
typedef struct _gpio_port_details
{
    uint16_t port_name;				   /* Contains the port name (i.e) PORTA PORTB... */
    uint16_t port_pin_number;   	   /* Contains the port pin number  (i.e) PIN0, PIN1,,, */
}gpio_port_details;

typedef gpio_port_details* gpio_port_details_hdl;

/*!
 * @brief GPIO pointer table structure
 */
typedef struct _ioal_gpio_gen_info
{
    ioal_gpio_pinconfig mode;         /* operating mode of the GPIO */
    gpio_port_details port;           /* Contains the gpio pin and port details */
}ioal_gpio_gen_info;


/**
 * @brief Initializes the GPIO hardware according to the provided configuration.
 *
 * @param[in] gpio_cfg : Pointer to the GPIO configuration structure.
 */
void io_hal_gpio_init(ioal_gpio_config* gpio_cfg);

/**
 * @brief This function resets the specified GPIO pin to its default
 * state and disables any associated functionalities.
 * @param[in] pin_number : The number of the GPIO pin to deinitialize.
 */
void io_hal_gpio_deinit(uint32_t pin_number);

/**
 * @brief This function sets the state of the specified GPIO
 * pin to the given logic level.
 * @param[in] pin_number : The number of the GPIO pin to write to.
 * @param[in] drive_logic : The logic level to set the pin
 * to (typically 0 for low and 1 for high).
 */
void io_hal_gpio_writepin(uint32_t pin_number, uint32_t drive_logic);

/**
 * @brief This function retrieves the current state of the specified GPIO pin.
 * @param[in] pin_number : The number of the GPIO pin to read from.
 *
 * @return The current state of the GPIO pin.
 */
ioal_gpio_pinstate io_hal_gpio_readpin(uint32_t pin_number);

/**
 * @brief This function changes the state of the specified GPIO pin
 * from high to low or from low to high.
 * @param[in] pin_number : The number of the GPIO pin to toggle.
 */
void io_hal_gpio_togglepin(uint32_t pin_number);

/**
 * @brief Initializes the GPIO pointer table.
 */
void io_hal_gpio_ptr_table_init(void);

#endif /* _IO_HAL_GPIO_COMMON_H_ */

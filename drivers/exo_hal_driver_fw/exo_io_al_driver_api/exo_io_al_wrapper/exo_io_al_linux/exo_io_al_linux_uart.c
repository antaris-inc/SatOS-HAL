/**
 * @file exo_io_al_linux_uart.c
 *
 * @brief This file contains linux wrapper functions for IO interface
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "exo_io_al_linux_uart.h"
#include "exo_io_al_uart_common.h"
#include "exo_hal_io_al_common.h"
#include "exo_common.h"


int uart1_fd; ///< UART1 FD
int uart4_fd; ///< UART4 FD
int uart5_fd; ///< UART5 FD
int uart6_fd; ///< UART6 FD

extern char *lnx_uart_com_port; // UART COM PORT to communicate UHF board in Linux environment

/**
 * @brief IO-HAL UART1 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart1_init(ioal_uart_hdle *ioal_huart1)
{
    hal_ret_sts ret = HAL_IO_INIT_ERR; 
    struct termios tty;
    char *uart_dev = "/dev/ttyUSB1";  // Replace with your UART device

    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    uart1_fd = open(uart_dev, O_RDWR | O_NOCTTY);
    if (uart1_fd == -1) {
        perror("Unable to open UART");
    }
    else
    {
        // Read in existing settings, and handle any error
        if(tcgetattr(uart1_fd, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }
        else
        {
            tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
            tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
            tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
            tty.c_cflag |= CS8; // 8 bits per byte (most common)
            tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
            tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO; // Disable echo
            tty.c_lflag &= ~ECHOE; // Disable erasure
            tty.c_lflag &= ~ECHONL; // Disable new-line echo
            tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
            tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
            tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

            tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
            tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

            tty.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
            tty.c_cc[VMIN] = 0;

            // Set in/out baud rate to be 9600
            cfsetispeed(&tty, B115200);
            cfsetospeed(&tty, B115200);

            // Save tty settings, also checking for error
            if (tcsetattr(uart1_fd, TCSANOW, &tty) != 0) {
                printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            }
            else
            {
                ioal_huart1->intf_gen_info.vdp_intf_inst_hdle = (void*)&uart1_fd;
                ioal_huart1->intf_gen_info.state = IO_FREE_STATE;
                ret= HAL_SCS; 
            }
        }
    }
    return ret;
}

/**
 * @brief IO-HAL UART1 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart6_init(ioal_uart_hdle *ioal_huart6)
{
    hal_ret_sts ret = HAL_IO_INIT_ERR; 
    struct termios tty;
    char *uart_dev = lnx_uart_com_port;  // Replace with your UART device
    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    uart6_fd = open(uart_dev, O_RDWR | O_NOCTTY);
    if (uart6_fd == -1) {
        perror("Unable to open UART");
    }
    else
    {
        // Read in existing settings, and handle any error
        if(tcgetattr(uart6_fd, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }
        else
        {
            tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
            tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
            tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
            tty.c_cflag |= CS8; // 8 bits per byte (most common)
            tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
            tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO; // Disable echo
            tty.c_lflag &= ~ECHOE; // Disable erasure
            tty.c_lflag &= ~ECHONL; // Disable new-line echo
            tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
            tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
            tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

            tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
            tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

            tty.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
            tty.c_cc[VMIN] = 0;

            // Set in/out baud rate to be 9600
            cfsetispeed(&tty, B115200);
            cfsetospeed(&tty, B115200);

            // Save tty settings, also checking for error
            if (tcsetattr(uart6_fd, TCSANOW, &tty) != 0) {
                printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            }
            else
            {
                ioal_huart6->intf_gen_info.vdp_intf_inst_hdle = (void*)&uart6_fd;
                ioal_huart6->intf_gen_info.state = IO_FREE_STATE;
                ret= HAL_SCS; 
            }
        }
    }
    return ret;
}
/**
 * @brief IO-HAL UART1 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart4_init(ioal_uart_hdle *ioal_huart4)
{
    hal_ret_sts ret = HAL_IO_INIT_ERR; 
    struct termios tty;
    char *uart_dev = "/dev/ttyUSB4";  // Replace with your UART device

    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    uart4_fd = open(uart_dev, O_RDWR | O_NOCTTY);
    if (uart4_fd == -1) {
        perror("Unable to open UART");
    }
    else
    {
        // Read in existing settings, and handle any error
        if(tcgetattr(uart4_fd, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }
        else
        {
            tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
            tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
            tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
            tty.c_cflag |= CS8; // 8 bits per byte (most common)
            tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
            tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO; // Disable echo
            tty.c_lflag &= ~ECHOE; // Disable erasure
            tty.c_lflag &= ~ECHONL; // Disable new-line echo
            tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
            tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
            tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

            tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
            tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

            tty.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
            tty.c_cc[VMIN] = 0;

            // Set in/out baud rate to be 9600
            cfsetispeed(&tty, B115200);
            cfsetospeed(&tty, B115200);

            // Save tty settings, also checking for error
            if (tcsetattr(uart4_fd, TCSANOW, &tty) != 0) {
                printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            }
            else
            {
                ioal_huart4->intf_gen_info.vdp_intf_inst_hdle = (void*)&uart4_fd;
                ioal_huart4->intf_gen_info.state = IO_FREE_STATE;
                ret= HAL_SCS; 
            }
        }
    }
    return ret;
}
/**
 * @brief IO-HAL UART1 initialization function for linux
 */
hal_ret_sts io_hal_linux_uart5_init(ioal_uart_hdle *ioal_huart5)
{
    hal_ret_sts ret = HAL_IO_INIT_ERR; 
    struct termios tty;
    char *uart_dev = "/dev/ttyUSB";  // Replace with your UART device

    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    uart5_fd = open(uart_dev, O_RDWR | O_NOCTTY);
    if (uart5_fd == -1) {
        perror("Unable to open UART");
    }
    else
    {
        // Read in existing settings, and handle any error
        if(tcgetattr(uart5_fd, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }
        else
        {
            tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
            tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
            tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
            tty.c_cflag |= CS8; // 8 bits per byte (most common)
            tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
            tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO; // Disable echo
            tty.c_lflag &= ~ECHOE; // Disable erasure
            tty.c_lflag &= ~ECHONL; // Disable new-line echo
            tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
            tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
            tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

            tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
            tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

            tty.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
            tty.c_cc[VMIN] = 0;

            // Set in/out baud rate to be 9600
            cfsetispeed(&tty, B115200);
            cfsetospeed(&tty, B115200);

            // Save tty settings, also checking for error
            if (tcsetattr(uart5_fd, TCSANOW, &tty) != 0) {
                printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            }
            else
            {
                ioal_huart5->intf_gen_info.vdp_intf_inst_hdle = (void*)&uart5_fd;
                ioal_huart5->intf_gen_info.state = IO_FREE_STATE;
                ret= HAL_SCS; 
            }
        }
    }
    return ret;
}

/**
 * @brief IO-HAL UART transmit function for linux
 */
hal_ret_sts io_hal_linux_uart_transmit(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    hal_ret_sts sts = HAL_IO_TX_ERR;
    int* u_fd = (int*)ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(u_fd != NULL && u_fd[0] != -1)
    {
            int bytes_written = write(*u_fd, pdata, size);
            if (bytes_written > 0)
            {
                sts = HAL_SCS;
            }
    }
    return sts;
}

/**
 * @brief IO-HAL UART receive function for linux
 */
uint32 io_hal_linux_uart_receive(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size, uint32 timeout)
{
    int* u_fd = (int*)ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    uint32 ret_byte_read = 0;
    if(u_fd != NULL && u_fd[0] != -1)
    {
        int bytes_read = read(*u_fd, pdata, size);
        if(bytes_read > 0 )
        {
            ret_byte_read = bytes_read;
        }
    }
    return ret_byte_read;
}

/**
 * @brief IO-HAL UART get state function for linux
 */
ioal_uart_state io_hal_linux_uart_get_state(ioal_uart_hdle *ioal_huart)
{
    return 0;
}

/**
 * @brief This API de-initialize the UART
 */
hal_ret_sts io_hal_linux_uart_deinit(ioal_uart_hdle *ioal_huart)
{
    return 0;
}

/**
 * @brief This function transmit the data in DMA mode for linux
 */
hal_ret_sts io_hal_linux_uart_transmit_dma(ioal_uart_hdle *ioal_huart, uint8 *pdata, uint16 size)
{
    hal_ret_sts sts = HAL_IO_TX_ERR;
    int* u_fd = (int*)ioal_huart->intf_gen_info.vdp_intf_inst_hdle;
    if(u_fd != NULL && u_fd[0] != -1)
    {
        int bytes_written = write(*u_fd, pdata, size);
        if (bytes_written > 0)
        {
            sts = HAL_SCS;
        }
    }
    return sts;
}

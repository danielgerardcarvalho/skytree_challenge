#ifndef INC_ADXL343_DRIVER_H_
#define INC_ADXL343_DRIVER_H_

/**
 * @file adxl343_driver.h
 * @brief Accelerometer Driver Module Interface
 *
 * @defgroup hal Hardware Abstraction Layer (HAL)
 * @brief Abstracts hardware specifics through a unified API.
 *
 * This module provides an interface for controlling the ADXL343 3-axis accelerometer. It abstracts the lower-level
 * details of hardware interaction, facilitating communication with the accelerometer via the I2C protocol. The module
 * offers functions for initialization, toggling measurement mode, and configuring various parameters such as data rate,
 * measurement range, resolution, and bit order.
 *
 * It also includes functions for reading the acceleration data along each axis (X, Y, Z),
 * as well as retrieving all axes' data simultaneously.
 *
 * @{
 */




// --------------------------------------------------------------------------------------------------------------------
// Include files 
// --------------------------------------------------------------------------------------------------------------------
// Compiler includes
#include <stdint.h>
#include <stddef.h>

// Project includes
#include "FunctionStatus.h"
#include "i2c_driver.h"

// Addresses and registers
#define ADXL343_REG_BW_RATE 0x2C                // Controls devices data rates and power mode
#define ADXL343_REG_POWER_CTL 0x2D              // Controls power and sleep states
#define ADXL343_REG_DATA_FORMAT 0x31            // Controls various device configurations
#define ADXL343_DATA_X_0 0x32                   // LSB of X axis
#define ADXL343_DATA_X_1 0x33                   // MSB of X axis
#define ADXL343_DATA_Y_0 0x34                   // LSB of T axis
#define ADXL343_DATA_Y_1 0x35                   // MSB of Y axis
#define ADXL343_DATA_Z_0 0x36                   // LSB of Z axis
#define ADXL343_DATA_Z_1 0x37                   // MSB of Z axis

#define ADXL343_ADDRESS_I2C 0x53                
#define ADXL343_ADDRESS_I2CWRITE 0xA6
#define ADXL343_ADDRESS_I2CREAD 0xA7

// Predefined values
#define ADXL343_DEFAULT_POWERCTRL 0x00          // link, auto sleep, sleep, measurement - low
#define ADXL343_DEFAULT_RATE 0x0A               // 100 Hz
#define ADXL343_DEFAULT_RANGE 0x00              // +-2g range
#define ADXL343_DEFAULT_RESOLUTION 0x00         // 10-bit (auto adjusting scale factor)
#define ADXL343_DEFAULT_BITORDER 0x00           // Right-Justified - (LSB mode)
#define ADXL343_DEFAULT_TIMEOUT 200             // time in ms, should rather scale with F_CPU

// Settings structure
typedef struct {
    uint8_t measurement_mode;
    uint8_t rate;
    uint8_t range;
    uint8_t resolution;
    uint8_t bit_order;
} ADXL343Settings;

// Functions
FunctionStatus adxl343_init();
FunctionStatus adxl343_start();
FunctionStatus adxl343_stop();
FunctionStatus adxl343_set_rate(uint8_t);
FunctionStatus adxl343_set_range(uint8_t);
FunctionStatus adxl343_set_resolution_fixed();
FunctionStatus adxl343_set_resolution_full();
FunctionStatus adxl343_set_bit_order(uint8_t);
FunctionStatus adxl343_get_X_axis(char *);
FunctionStatus adxl343_get_Y_axis(char *);
FunctionStatus adxl343_get_Z_axis(char *);
FunctionStatus adxl343_get_all_axes(char *);
ADXL343Settings adxl343_get_settings();



/** @} */

#endif /* INC_ADXL343_DRIVER_H_ */
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


// Includes 
// - Compiler includes
#include <stdint.h>
#include <stddef.h>
// - Project includes
#include "FunctionStatus.h"
#include "i2c_driver.h"


// Defines
// - Addresses and registers
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
// - Predefined values
#define ADXL343_DEFAULT_POWERCTRL 0x00          // link, auto sleep, sleep, measurement - low
#define ADXL343_DEFAULT_RATE 0x0A               // 100 Hz
#define ADXL343_DEFAULT_RANGE 0x00              // +-2g range
#define ADXL343_DEFAULT_RESOLUTION 0x00         // 10-bit (auto adjusting scale factor)
#define ADXL343_DEFAULT_BITORDER 0x00           // Right-Justified - (LSB mode)
#define ADXL343_DEFAULT_TIMEOUT 200             // time in ms, should rather scale with F_CPU


// Data structures
// - Settings structure
typedef struct {
    uint8_t measurement_mode;
    uint8_t rate;
    uint8_t range;
    uint8_t resolution;
    uint8_t bit_order;
} ADXL343Settings;


// Functions

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Initializes the ADXL343 accelerometer.
 *
 * This function initializes the ADXL343 accelerometer by configuring its operating parameters to default values.
 * It sets up the accelerometer for subsequent operations. Upon successful initialization, the accelerometer is
 * configured to default in standby mode.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_init();


/** -------------------------------------------------------------------------------------------------------------------
 * @brief Starts the ADXL343 accelerometer.
 *
 * This function starts the ADXL343 accelerometer, enabling it to begin measuring acceleration data along its
 * three axes. Once started, the accelerometer will continuously measure acceleration until stopped.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_start();

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Stops the ADXL343 accelerometer.
 *
 * This function stops the ADXL343 accelerometer, halting the measurement of acceleration data along its three axes.
 * Once stopped, the accelerometer ceases to measure acceleration until started again.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_stop();

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Sets the data rate of the ADXL343 accelerometer.
 *
 * This function sets the data rate of the ADXL343 accelerometer to the specified value.
 *
 * @param rate  The desired data rate value to set for the accelerometer.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_set_rate(uint8_t);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Sets the measurement range of the ADXL343 accelerometer.
 *
 * This function sets the measurement range of the ADXL343 accelerometer to the specified value. The measurement
 * range determines the maximum acceleration that the accelerometer can measure along each axis.
 *
 * @param range The desired measurement range value to set for the accelerometer.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_set_range(uint8_t);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Sets the resolution of the ADXL343 accelerometer to fixed resolution mode.
 *
 * This function sets the resolution of the ADXL343 accelerometer to fixed resolution mode. In this mode, the
 * accelerometer uses a fixed 10bit resolution for data output.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_set_resolution_fixed();

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Sets the resolution of the ADXL343 accelerometer to full resolution mode.
 *
 * This function sets the resolution of the ADXL343 accelerometer to full resolution mode. In this mode, the
 * accelerometer provides full resolution for data output. Thes resolution varies depending on the configured range.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_set_resolution_full();

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Sets the bit order of the ADXL343 accelerometer.
 *
 * This function sets the bit order of the ADXL343 accelerometer to the specified value. The bit order determines
 * the order in which the accelerometer outputs bits of data. 0 is right-justified (LSB) and 1 is left-justified (MSB).
 * Note the sign extension when right-justified
 *
 * @param bit_order The desired bit order value to set for the accelerometer.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_set_bit_order(uint8_t bit_order);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the acceleration data along the X-axis from the ADXL343 accelerometer.
 *
 * This function retrieves the acceleration data along the X-axis from the ADXL343 accelerometer and stores it
 * in the provided buffer.
 *
 * @param data A pointer to a buffer where the X-axis acceleration data will be stored.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_get_X_axis(char * data);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the acceleration data along the Y-axis from the ADXL343 accelerometer.
 *
 * This function retrieves the acceleration data along the Y-axis from the ADXL343 accelerometer and stores it
 * in the provided buffer.
 *
 * @param data A pointer to a buffer where the Y-axis acceleration data will be stored.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_get_Y_axis(char * data);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the acceleration data along the Z-axis from the ADXL343 accelerometer.
 *
 * This function retrieves the acceleration data along the Z-axis from the ADXL343 accelerometer and stores it
 * in the provided buffer.
 *
 * @param data A pointer to a buffer where the Z-axis acceleration data will be stored.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_get_Z_axis(char *data);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the acceleration data along all axes from the ADXL343 accelerometer.
 *
 * This function retrieves the acceleration data along all axes (X, Y, Z) from the ADXL343 accelerometer and
 * stores it in the provided buffer.
 *
 * @param data A pointer to a buffer where the acceleration data along all axes will be stored.
 *
 * @return FunctionStatus  Returns FUNCTION_STATUS_OK if the transmission was successful.
 *                         Returns FUNCTION_STATUS_ERROR for non-specific errors.
 *                         Returns FUNCTION_STATUS_ARGUMENT_ERROR if null pointers or invalid arguments are passed.
 *                         Returns FUNCTION_STATUS_TIMEOUT if the operation did not complete within the specified timeout period.
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus adxl343_get_all_axes(char *data);

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the current settings of the ADXL343 accelerometer.
 *
 * This function retrieves the current settings of the ADXL343 accelerometer, including measurement mode, data rate,
 * measurement range, resolution, and bit order. The settings are returned in a structure.
 *
 * @return ADXL343Settings  The current settings of the ADXL343 accelerometer.
 * --------------------------------------------------------------------------------------------------------------------
 */
ADXL343Settings adxl343_get_settings();

/** -------------------------------------------------------------------------------------------------------------------
 * @brief Gets the current settings of the ADXL343 accelerometer. Directly from the ADXL343 accelerometer
 *
 * This function retrieves the current settings of the ADXL343 accelerometer via the I2C bus, including measurement 
 * mode, data rate, measurement range, resolution, and bit order. The updated settings are returned in the settings
 * structure.
 *
 * @return ADXL343Settings  The current settings of the ADXL343 accelerometer.
 * --------------------------------------------------------------------------------------------------------------------
 */
ADXL343Settings adxl343_update_settings();

/** @} */

#endif /* INC_ADXL343_DRIVER_H_ */
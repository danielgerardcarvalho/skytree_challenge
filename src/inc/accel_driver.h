#ifndef INC_ACCEL_DRIVER_H_
#define INC_ACCEL_DRIVER_H_

#include "FunctionStatus.h"

// Addresses and registers
#define ADXL343_REG_BW_RATE 0x2C                // Controls devices data rates and power mode
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
#define ADXL343_DEFAULT_BITORDER 0x01           // Left-Justified - (MSB mode)
#define ADXL343_DEFAULT_RANGE 0x00              // +-2g range
#define ADXL343_DEFAULT_RESOLUTION 0x00         // 10-bit (auto adjusting scale factor)
#define ADXL343_DEFAULT_RATE 0x0A               // 100 Hz

// Functions
FunctionStatus adxl343_init();
FunctionStatus adxl343_set_rate();
FunctionStatus adxl343_set_resolution();
FunctionStatus adxl343_set_range();
FunctionStatus adx1343_read();
FunctionStatus adxl343_write();

#endif /* INC_ACCEL_DRIVER_H_ */
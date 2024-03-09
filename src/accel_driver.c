// TODO: Create an object if need be otherwise just throw some functions in here
// - no object - going more functional
// - init - must be default
// - maybe a few configs
// - read and other gets (double check on preference for xyz coords)
// - set things (range, res, maybe others??)

#include "accel_driver.h"

FunctionStatus adxl343_init(){

    // TODO
    // Configure I2C - set in hardware only I think
    // Configure data rate (default) - set in BW_RATE
    // Configure bit order (default) - set in DATA_FORMAT
    // Configure Range (default) - set in DATA_FORMAT
    // Configure Resolution (default) - set in DATA_FORMAT

    return FUNCTION_STATUS_OK;
}

FunctionStatus adx1343_set_rate(){return FUNCTION_STATUS_OK;}
FunctionStatus adxl343_set_resolution(){return FUNCTION_STATUS_OK;}
FunctionStatus adxl343_set_range(){return FUNCTION_STATUS_OK;}
FunctionStatus adx1343_read(){return FUNCTION_STATUS_OK;}
FunctionStatus adxl343_write(){return FUNCTION_STATUS_OK;}


#include "accel_driver.h"
#include <stdio.h>

// Statics

static FunctionStatus _adxl343_read(uint8_t register_address, size_t num_bytes,
                                    char* return_data){
    // TODO: implementation ERROR HANDLING AND COMMENTING AND TESTING
    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
static FunctionStatus _adxl343_write(uint8_t register_address, uint8_t data){
    char dataToWrite [3];
    dataToWrite[0] = ADXL343_ADDRESS_I2CWRITE;
    dataToWrite[1] = register_address;
    dataToWrite[2] = data;

    i2c_write(dataToWrite, sizeof(dataToWrite), ADXL343_DEFAULT_TIMEOUT);

    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_init(){
    // Configure data rate (default) - set in BW_RATE
    adxl343_set_rate(ADXL343_DEFAULT_RATE);
    
    // Configuring DATA_FORMAT register (bit order, range, resolution)
    uint8_t data_format_value = 0x00 |
                                (ADXL343_DEFAULT_RESOLUTION << 3) |
                                (ADXL343_DEFAULT_BITORDER << 2) |
                                (ADXL343_DEFAULT_RANGE);
    _adxl343_write(ADXL343_REG_DATA_FORMAT, data_format_value);

    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_set_rate(uint8_t rate){
    // Writing to ADXL343
    _adxl343_write(ADXL343_REG_BW_RATE, rate);

    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_set_range(uint8_t range){
    uint8_t reg_mask = 0xFC;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    // Updating data_format register value to include the new range
    register_value = (register_value & reg_mask) | range;
    // Send packet to ADXL343
    _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);

    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_set_resolution_fixed(){
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    // Updated data_format register value to the set 10bit fixed resolution mode
    register_value = register_value & reg_mask | (0 << 0x8);
    // Send packet to ADXL343
    _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);
    
    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_set_resolution_full(){
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    // Updating data_format register value to set full resolution mode
    register_value = register_value & reg_mask | (1 << 0x8);
    // Send packet to ADXL343
    _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);

    return FUNCTION_STATUS_OK;
}

// TODO: ERROR HANDLING AND COMMENTING AND TESTING
FunctionStatus adxl343_set_bit_order(uint8_t bit_order){
    uint8_t reg_mask = 0xFB;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    // Updating data_format register value to set bit order
    register_value = register_value & reg_mask | (bit_order << 0x4);
    // Send packet to ADXL343
    _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);

    return FUNCTION_STATUS_OK;
}

FunctionStatus adxl343_get_X_axis(char* data){
    // TODO: Implementation ERROR HANDLING COMMENTING AND TESTING
    _adxl343_read(ADXL343_DATA_X_0, 2, data);
}

FunctionStatus adxl343_get_Y_axis(char* data){
    // TODO: Implementation ERROR HANDLING COMMENTING AND TESTING
}

FunctionStatus adxl343_get_Z_axis(char* data){
    // TODO: Implementation ERROR HANDLING COMMENTING AND TESTING
}

FunctionStatus adxl343_get_all_axes(char* data){
    // TODO: Implementation ERROR HANDLING COMMENTING AND TESTING
}




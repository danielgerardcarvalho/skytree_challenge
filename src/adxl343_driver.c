#include "adxl343_driver.h"
#include <stdio.h>

#ifdef UNITTEST
#define i2c_write mock_i2c_write
#define i2c_read mock_i2c_read
#endif

// Statics
static ADXL343Settings adxl343_settings;

// TODO: COMMENTING AND TESTING
static FunctionStatus _adxl343_read(uint8_t register_address, size_t num_bytes,
                                    char* return_data){
    FunctionStatus result;

    // Initialise read process
    char dataToWrite [2];
    dataToWrite[0] = ADXL343_ADDRESS_I2CWRITE;
    dataToWrite[1] = register_address;
    result = i2c_write(dataToWrite, sizeof(dataToWrite), ADXL343_DEFAULT_TIMEOUT); 
    if (result != FUNCTION_STATUS_OK){return result;}

    // Start read of data
    char dataToRead [1];
    dataToRead [0] = ADXL343_ADDRESS_I2CREAD;
    result = i2c_write(dataToWrite, sizeof(dataToRead), ADXL343_DEFAULT_TIMEOUT);
    if (result != FUNCTION_STATUS_OK){return result;}

    // Receive data into the return_data buffer
    result = i2c_read(return_data, num_bytes, ADXL343_DEFAULT_TIMEOUT * num_bytes);
    
    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
static FunctionStatus _adxl343_write(uint8_t register_address, uint8_t data){
    char dataToWrite [3];
    dataToWrite[0] = ADXL343_ADDRESS_I2CWRITE;
    dataToWrite[1] = register_address;
    dataToWrite[2] = data;

    return i2c_write(dataToWrite, sizeof(dataToWrite), ADXL343_DEFAULT_TIMEOUT);
}

static void _clean_accelerometer_data(char* data){
    // Finding resolution in number of bits
    uint16_t cleaned_data;
    uint8_t resolution = 10;
    uint8_t resolution_mask = 1;
    if (adxl343_settings.resolution == 0x01){
        resolution += adxl343_settings.range;
    }
    for (int i = 0; i < resolution; i++){
        resolution_mask *= 2;
    }

    // Ordering data to match bit-order
    if (adxl343_settings.bit_order == 0x00){
        // Data is right justified (note data is signed)
        cleaned_data = (uint16_t) ((((resolution_mask >> 8) & data[1]) << 8) | data[0]);
    } else {
        // Data is left justified
        cleaned_data = (uint16_t) (((data[1] << 8) | data[0]) >> (16 - resolution));
    }

    data[0] = (char) (cleaned_data & 0xFF);
    data[1] = (char) (cleaned_data >> 8);
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_init(){
    FunctionStatus result;

    // Apply default settings to settings structure
    adxl343_settings.measurement_mode = 0x00;
    adxl343_settings.rate = ADXL343_DEFAULT_RATE;
    adxl343_settings.range = ADXL343_DEFAULT_RANGE;
    adxl343_settings.resolution = ADXL343_DEFAULT_RESOLUTION;
    adxl343_settings.bit_order = ADXL343_DEFAULT_BITORDER;

    // Configure data rate (default) - set in BW_RATE
    result = adxl343_set_rate(ADXL343_DEFAULT_RATE);
    if (result != FUNCTION_STATUS_OK){return result;}

    // Configure power control modes - sleep, measurement, auto_sleep
    result = _adxl343_write(ADXL343_REG_POWER_CTL, ADXL343_DEFAULT_POWERCTRL);
    if (result != FUNCTION_STATUS_OK){return result;}
    
    // Configuring DATA_FORMAT register (bit order, range, resolution)
    uint8_t data_format_value = 0x00 |
                                (ADXL343_DEFAULT_RESOLUTION << 3) |
                                (ADXL343_DEFAULT_BITORDER << 2) |
                                (ADXL343_DEFAULT_RANGE);
    result = _adxl343_write(ADXL343_REG_DATA_FORMAT, data_format_value);
    if (result != FUNCTION_STATUS_OK){return result;}

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_start(){
    FunctionStatus result;
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (POWER_CTL) value
    result = _adxl343_read(ADXL343_REG_POWER_CTL, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}

    // Updating power_ctl register value to set measurement mode to active
    register_value = (register_value & reg_mask) | (1 << 0x08);
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_POWER_CTL, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}

    adxl343_settings.measurement_mode = 0x01;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_stop(){
    FunctionStatus result;
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (POWER_CTL) value
    result = _adxl343_read(ADXL343_REG_POWER_CTL, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Updating power_ctl register value to set measurement mode to standby
    register_value = (register_value & reg_mask) | (0 << 0x08);
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_POWER_CTL, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    
    adxl343_settings.measurement_mode = 0x00;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_set_rate(uint8_t rate){
    FunctionStatus result;
    // Writing to ADXL343
    result = _adxl343_write(ADXL343_REG_BW_RATE, rate);
    if (result != FUNCTION_STATUS_OK){return result;}

    adxl343_settings.rate = rate;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_set_range(uint8_t range){
    FunctionStatus result;
    uint8_t reg_mask = 0xFC;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    result = _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Updating data_format register value to include the new range
    register_value = (register_value & reg_mask) | range;
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    adxl343_settings.range = range;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_set_resolution_fixed(){
    FunctionStatus result;
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    result = _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Updated data_format register value to the set 10bit fixed resolution mode
    register_value = register_value & reg_mask | (0 << 0x8);
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    adxl343_settings.resolution = 0x00;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_set_resolution_full(){
    FunctionStatus result;
    uint8_t reg_mask = 0xF7;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    result = _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Updating data_format register value to set full resolution mode
    register_value = register_value & reg_mask | (1 << 0x8);
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    adxl343_settings.resolution = 0x01;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_set_bit_order(uint8_t bit_order){
    FunctionStatus result;
    uint8_t reg_mask = 0xFB;
    uint8_t register_value;
    // Get current register (DATA_FORMAT) value
    result = _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Updating data_format register value to set bit order
    register_value = register_value & reg_mask | (bit_order << 0x4);
    // Send packet to ADXL343
    result = _adxl343_write(ADXL343_REG_DATA_FORMAT, register_value);
    if (result != FUNCTION_STATUS_OK){return result;}
    adxl343_settings.bit_order = bit_order;

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_get_X_axis(char* data){
    FunctionStatus result;
    // Read in values from the X axis 
    result = _adxl343_read(ADXL343_DATA_X_0, 2, data);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Clean the data according to device settings
    _clean_accelerometer_data(data);

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_get_Y_axis(char* data){
    FunctionStatus result;
    // Read in values from the Y axis 
    result = _adxl343_read(ADXL343_DATA_Y_0, 2, data);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Clean the data according to device settings
    _clean_accelerometer_data(data);
    
    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_get_Z_axis(char* data){
    FunctionStatus result;
    // Read in values from the Z axis 
    result = _adxl343_read(ADXL343_DATA_Z_0, 2, data);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Clean the data according to device settings
    _clean_accelerometer_data(data);

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AND TESTING
FunctionStatus adxl343_get_all_axes(char* data){
    FunctionStatus result;
    // Read in values from the X axis 
    result = _adxl343_read(ADXL343_DATA_X_0, 6, data);
    if (result != FUNCTION_STATUS_OK){return result;}
    // Clean the data according to device settings
    char x_data []= {data[0], data[1]};
    _clean_accelerometer_data(x_data);
    char y_data [] = {data[2], data[3]};
    _clean_accelerometer_data(y_data);
    char z_data [] = {data[4], data[5]};
    _clean_accelerometer_data(z_data);
    data[0] = x_data[0];
    data[1] = x_data[1];
    data[2] = y_data[0];
    data[3] = y_data[1];
    data[4] = z_data[0];
    data[5] = z_data[1];

    return FUNCTION_STATUS_OK;
}

// TODO: COMMENTING AN TESTING
ADXL343Settings adxl343_get_settings(){
    char temp_reader;

    // Updating measurement mode
    _adxl343_read(ADXL343_REG_POWER_CTL, 1, &temp_reader);
    adxl343_settings.measurement_mode = temp_reader & 0x08;
    // Updating rate
    _adxl343_read(ADXL343_REG_BW_RATE, 1, &temp_reader);
    adxl343_settings.rate = temp_reader & 0xF;
    // Updating range
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &temp_reader);
    adxl343_settings.range = temp_reader & 0x3;
    // Updating resolution
    _adxl343_read(ADXL343_REG_DATA_FORMAT, 1, &temp_reader);
    adxl343_settings.resolution = temp_reader & 0x08;
    // Updating bit_order
    _adxl343_read(ADXL343_REG_BW_RATE, 1, &temp_reader);
    adxl343_settings.bit_order = temp_reader & 0x04;

    return adxl343_settings;
}


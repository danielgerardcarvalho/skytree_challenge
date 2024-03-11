// --------------------------------------------------------------------------------------------------------------------
/// \file  test_adxl343_driver.c
/// \brief unittester for adxl343_driver
// --------------------------------------------------------------------------------------------------------------------


#ifdef UNITTEST
#define i2c_write mock_i2c_write
#define i2c_read mock_i2c_read
#endif

#include <stdio.h>

#include "adxl343_driver.h"
#include "FunctionStatus.h"
#include "unity.h"

// Mocks
FunctionStatus mock_i2c_write(const char* dataToWrite, size_t length, uint32_t timeout){
    return FUNCTION_STATUS_OK;
}
FunctionStatus mock_i2c_read(char* dataToRead, size_t length, uint32_t timeout) {
    dataToRead[0] = (uint8_t) 0xEA;
    dataToRead[1] = (uint8_t) 0x1D;
    return FUNCTION_STATUS_OK;
}


void setUp(void){}

// Test cases
void test_testing_temp(){
    // TODO: remove when dev is completed
    adxl343_init();
    adxl343_set_range(0b10);

    adxl343_get_settings();
    // TEST_ASSERT_EQUAL(0xE, return_val);
}

void test_adxl343_init_noerror(){
    FunctionStatus result = adxl343_init();
    ADXL343Settings settings = adxl343_get_settings();
    
    TEST_ASSERT_EQUAL(result, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(settings.measurement_mode, 0x00);
    TEST_ASSERT_EQUAL(settings.rate, ADXL343_DEFAULT_RATE);
    TEST_ASSERT_EQUAL(settings.range, ADXL343_DEFAULT_RANGE);
    TEST_ASSERT_EQUAL(settings.resolution, ADXL343_DEFAULT_RESOLUTION);
    TEST_ASSERT_EQUAL(settings.bit_order, ADXL343_DEFAULT_BITORDER);
}

void test_adxl343_init_error(){
}

void test_adxl343_get_X_axis_noerror(){
    char x_axis_buffer [2] = {0, 0};
    FunctionStatus result = adxl343_get_X_axis(x_axis_buffer);
    TEST_ASSERT_EQUAL(result, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL((uint8_t) x_axis_buffer[0], 0b11101010);
    TEST_ASSERT_EQUAL((uint8_t) x_axis_buffer[1], 0b01);
    result = adxl343_set_bit_order(0x01);
    TEST_ASSERT_EQUAL(result, FUNCTION_STATUS_OK);
    result = adxl343_get_X_axis(x_axis_buffer);
    TEST_ASSERT_EQUAL((uint8_t) x_axis_buffer[0], 0b01110111);
    TEST_ASSERT_EQUAL((uint8_t) x_axis_buffer[1], 0b00000000);
}

/** 
 * ... and many more tests all following a similar layout. Ideally there would be multiple 
 * 'noerror' (good weather) tests and multiple (bad weather) 'error' tests per function if 
 * neccessary. The naming convention for the tests would be some akin to 
 * 
 * test_SUT_scenario/func_expectedresult.
 * 
 * I didnt get around to configuring cmock with unity to really test things as time was a bit
 * short and I'm relatively new to the framework. Hence the ifdef TEST macro. Ideally cmock
 * would be used to automatically create mocks and allow for direct interfacing with them.
 */ 

void tearDown(void){

}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_adxl343_init_noerror);
    RUN_TEST(test_adxl343_init_error);
    RUN_TEST(test_adxl343_get_X_axis_noerror);

    return UNITY_END();
}
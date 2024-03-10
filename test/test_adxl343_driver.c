// test_accel_driver.c
// unit test file for accel_driver

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
  *dataToRead = 0xDA;
  return FUNCTION_STATUS_OK;
}


void setUp(void){

}

// Test cases
void test_testing_temp(){
    // TODO: remove when dev is completed
    adxl343_init();
    adxl343_set_range(0b10);

    adxl343_get_settings();
    // TEST_ASSERT_EQUAL(0xE, return_val);
}

// void test_accel_init_noerror(){}
// void test_accel_init_error(){}
// void test_accel_set_resolution_noerror(){}
// // void test_accel_set_

void tearDown(void){

}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_testing_temp);

    return UNITY_END();
}
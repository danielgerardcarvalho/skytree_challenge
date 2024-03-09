// test_accel_driver.c
// unit test file for accel_driver


// TODO: all the unit test things

#include "accel_driver.h"
#include "FunctionStatus.h"
#include "unity.h"

// Mocks
FunctionStatus i2c_write(const char* dataToWrite, size_t length, uint32_t timeout){
  
}
FunctionStatus i2c_read(char* dataToRead, size_t length, uint32_t timeout) {
  
}

// Test cases
void test_accel_init_noerror(){}
void test_accel_init_error(){}
void test_accel_set_resolution_noerror(){}
// void test_accel_set_
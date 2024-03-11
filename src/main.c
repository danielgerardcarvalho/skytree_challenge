// --------------------------------------------------------------------------------------------------------------------
/// \file  main.c
/// \brief Description
// --------------------------------------------------------------------------------------------------------------------

#include "FunctionStatus.h"
#include "adxl343_driver.h"

int main(){
    // Configuring micro
    // - just imagine
    // Configuring i2c
    // - pretend its just majestic things here as well
    
    // Initialise Accelerometer
    if (adxl343_init() != FUNCTION_STATUS_OK){
        // Sad :(
    }
    
    // Using the Accelerometer
    adxl343_set_resolution_full();
    adxl343_set_bit_order(0x01);
    adxl343_start();
    
    return 0;
}
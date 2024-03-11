# Readme

# Project for Skytree interview

\
**General** \
The driver is feature complete, ran short on time to implement the unittesting framework completely. It is functional although a work around for the mocks was made as I didnt manage to implement cmock in time. More info in the test/test_adxl343_driver.c file. Additionally the code is mostly commented, I would have mirrorered the provided i2c_drivers comment style to keep things consistant but for this delivery i believe what I did do should be sufficient.

I decided not to make a structure or some form of object to instantise the sensor driver. Instead all interfacing with the device is done through the functions in the driver directly. I feel it fits better with relatively simple nature of the driver, and I believe this approach is fairly standard as well. There are some internal only classes (statics). This was just to add another layer of abstraction between i2c and the drivers functions.
Additionally there is a struct to reduce the amount of I2C traffic. This structure stores the settings of the device locally to reduce the additional reads that would be needed when cleaning up the x,y,z axes data. Although the values in the structure are always updated when related values are changed, there is a chance that they may not be. For example in the case an error occurs when writing values to the device, with error handling escaping before the update can occur. In this case there exists an update function to re-sync the struct values with the actual value on the accelerometer. Therefore, this function is made primarily with error handling in mind.

Everything else is fairly standard, other than the _clean_accelerometer_data function. This implementation mirrors what I would prefer to work with if I had to guess, obviously the desired order of the bits would differ depending on the implementation. Perhaps additional functionality to choose between this would be ideal. Currently whether the bit order is right or left justified, the _clean_accelerometer_data function is able to correctly rework the data to be right justified. That is in the case of 10bit mode for example the bits are filled from LSByte_LSBit first for 10bits (left to right, LSBit to MSBit).

With all that said, thanks for the opportunity. Actually enjoyed making this, so thanks for that too. Notes on my assumptions as well as how toos are below. Cheers!

\
**How to Run**
- Clone the repository to you device
- Make sure all dependancies are met, especially if the included test files are to be used, make sure Unity is present in the location specified in the dependancy section.
- Running the code can be done via the makefile, the binaries and objects can be found within the bld directory. If one does not exist it will be created when the first run is done.
    - <code> make run </code>   - builds and runs the code
    - <code> make test </code>  - builds and runs the unittests
    - <code> make clean </code> - clears the builds by deleting the bld directory


\
**Assumptions:**
- General wiring and connections of micro and ADXL343. Specific hardware pins related to the 
    configuration of I2C and reading/writing are mentioned in more detail below.
- I2C default configuration:
    - the CS pin \
        There is no default state if the pin is left floating (no pullup/downs). This needs to 
        set to set high though in order to enable I2C.
    - the ALT ADDRESS pin \
        There is no default state if the pin is left floating so I'm going with grounded. This
        means that the addresses for I2C, R/W are:
        - I2C address - 0x53
        - Read - 0xA7
        - Write - 0xA6
    - i2c_write and i2c_read functions handle ack replies from the device.


\
**Requirements/Dependencies:**
- Makefile
    - configured for gcc
    - configured for gdb
    - configured for Unity (unittesting) \
        - https://github.com/ThrowTheSwitch/Unity
        - Be sure to add the Unity directory to the correct location. \
        relative path: <code>lib/</code> 
        - The relative path to the <code>unity.h</code>/<code>unity.c</code> files should be <code>lib/Unity/src</code>.
        
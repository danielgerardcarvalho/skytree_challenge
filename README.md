# Readme

# Project for Skytree interview

**Task List:**
- see the todo log
- implement the accel_driver file
    - init first
    - maybe the config next and finish off with the read
- unittesting
- double check linking and add comments where needed
- error handling routines if not already done.

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
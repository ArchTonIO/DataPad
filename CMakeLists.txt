# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/antonio/Progetti/picoProjects/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Data_pad C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Data_pad Data_pad.c Joystick.c Buttons.c Serial.c Libraries/PicoRGB/PicoRGB.c Libraries/PicoOled/PicoOled.c RGBkeypad.c Internal_routines.c)

pico_generate_pio_header(Data_pad ${CMAKE_CURRENT_LIST_DIR}/Libraries/PicoRGB/ws2812.pio)

pico_set_program_name(Data_pad "Data_pad")
pico_set_program_version(Data_pad "0.1")

pico_enable_stdio_uart(Data_pad 0)
pico_enable_stdio_usb(Data_pad 1)

# Add the standard library to the build
target_link_libraries(Data_pad pico_stdlib)
target_link_libraries(Data_pad pico_stdlib pico_multicore)
target_link_libraries(Data_pad pico_stdlib hardware_gpio)
target_link_libraries(Data_pad pico_stdlib hardware_adc)
target_link_libraries(Data_pad pico_stdlib hardware_pio)
target_link_libraries(Data_pad pico_stdlib hardware_i2c)

pico_add_extra_outputs(Data_pad)


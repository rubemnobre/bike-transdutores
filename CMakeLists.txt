cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(projeto
  accel.cpp
  main.cpp
)

pico_add_extra_outputs(projeto)

target_link_libraries(projeto
    pico_stdlib
    pico_time
    hardware_spi
    hardware_i2c
)

pico_enable_stdio_usb(projeto 1) 
pico_enable_stdio_uart(projeto 0) 
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(ws2812b C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(ws2812b ws2812b.c )

pico_set_program_name(ws2812b "ws2812b")
pico_set_program_version(ws2812b "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(ws2812b 1)
pico_enable_stdio_usb(ws2812b 1)

#Converte o .pio para .h
pico_generate_pio_header(ws2812b ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

target_sources(ws2812b PRIVATE ws2812b.c)

# Add the standard library to the build
target_link_libraries(ws2812b
        pico_stdlib
        pico_bootrom
        hardware_pio)

# Add the standard include files to the build
target_include_directories(ws2812b PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(ws2812b 
        
        )

pico_add_extra_outputs(ws2812b)


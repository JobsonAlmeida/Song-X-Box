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
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(SongExpBox C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(SongExpBox 
               SongExpBox.c
               peripherals/I2C_Display/ssd1306_i2c.c
               peripherals/ADC_DMA/ADC_DMA_functions.c
               screens/screen0.c
               screens/screen1.c
               screens/screen2.c
               screens/screen3.c
               peripherals/GPIO_BUTTONS_A_B/GPIO_BUTTONS_A_B.c
               sound/sound.c
               peripherals/MATRIZ_RGB/matriz_rgb.c              
)

pico_set_program_name(SongExpBox "SongExpBox")
pico_set_program_version(SongExpBox "0.1")

# Generate PIO header
pico_generate_pio_header(SongExpBox ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(SongExpBox 0)
pico_enable_stdio_usb(SongExpBox 1)

# Add the standard library to the build
target_link_libraries(SongExpBox
        pico_stdlib
        hardware_i2c 
        hardware_pwm
        hardware_adc
        hardware_dma
        hardware_gpio   
        hardware_rtc
        hardware_timer    
        pico_rand 
        hardware_pio
        hardware_clocks        
)

# Add the standard include files to the build
target_include_directories(SongExpBox PRIVATE
        ########## Passo 1 ###############  ${CMAKE_CURRENT_LIST_DIR}/headers
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
# target_link_libraries(SongExpBox 
#         hardware_i2c
#         )

pico_add_extra_outputs(SongExpBox)


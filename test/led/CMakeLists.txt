cmake_minimum_required(VERSION 3.10)

set(TEST_NAME led_test)

set(INCLUDE_DIRS
    ../../led
    
)
set(SRCS
    ../../led/led.c
    led_test.c
)

add_executable(${TEST_NAME} ${SRCS})

target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIRS})


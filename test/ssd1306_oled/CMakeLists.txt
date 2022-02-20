cmake_minimum_required(VERSION 3.10)

set(TEST_NAME ssd1306_oled_buffer_test)

set(INCLUDE_DIRS
    ../../ssd1306_oled
    support
)
set(SRCS
    ../../ssd1306_oled/SSD1306_oled.c
    support/buffer_oled_expect.c
    support/mock_i2c.c
    ${TEST_NAME}.c
)
add_definitions(-DTEST)
add_executable(${TEST_NAME} ${SRCS})

target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIRS})

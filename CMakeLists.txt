cmake_minimum_required(VERSION 3.0.0)
project(my_libs VERSION 0.1.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/exe)
set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_BUILD_TYPE Debug)

set(GLOBAL_DEFINES
    
)
add_definitions(${GLOBAL_DEFINES})

add_subdirectory(utility/unity unity)
link_libraries(unity)

add_subdirectory(test/led led_test)
add_subdirectory(test/ssd1306_oled ssd1306_oled_test)



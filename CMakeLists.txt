cmake_minimum_required(VERSION 3.0.0)
project(my_libs VERSION 0.1.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/exe)
set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(utility/unity unity)


link_directories(unity)

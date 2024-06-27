cmake_minimum_required(VERSION 3.5.0)
project(LRAM, VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(LRAM src/main.cpp)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/raylib/")
target_link_libraries(LRAM raylib)

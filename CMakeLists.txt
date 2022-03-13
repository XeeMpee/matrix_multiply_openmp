cmake_minimum_required(VERSION 3.10)
project(prir_02 VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules/)
find_package(OpenMP REQUIRED)

add_subdirectory(libs)
add_subdirectory(src)
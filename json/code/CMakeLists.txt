cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(json-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(json-test main.cpp)

target_include_directories(json-test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
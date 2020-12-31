cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(spdlog_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(spdlog_test main.cpp)

target_include_directories(spdlog_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_link_libraries(spdlog_test PRIVATE pthread)
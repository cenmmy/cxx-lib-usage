cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(yaml-test)

find_package(yaml-cpp CONFIG REQUIRED)

# message(STATUS ${YAML_CPP_INCLUDE_DIR})

add_executable(yaml-test main.cpp)

target_include_directories(yaml-test PRIVATE ${YAML_CPP_INCLUDE_DIR})

target_link_libraries(yaml-test ${YAML_CPP_LIBRARIES})
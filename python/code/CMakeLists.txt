cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(example LANGUAGES CXX)

add_subdirectory("extern/pybind11")

pybind11_add_module(example pybind11_test.cpp)

add_executable(pythonlibs-test pythonlibs-test.cpp)
target_include_directories(pythonlibs-test PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(pythonlibs-test PRIVATE ${PYTHON_LIBRARIES})

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/cmy-test.py
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/cmy-test.py ${CMAKE_CURRENT_BINARY_DIR}/cmy-test.py
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/cmy-test.py  
)

# 将cmy-test.py设置为目标依赖的资源，以便目标在编译时能够调用该命令。
target_sources(pythonlibs-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cmy-test.py)
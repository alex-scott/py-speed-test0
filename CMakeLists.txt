cmake_minimum_required(VERSION 3.25)
project(py_speed_test0)

find_package(Python COMPONENTS Interpreter Development )

set(CMAKE_CXX_STANDARD 11)

add_executable(py_speed_test0 main.cpp )

target_link_libraries(py_speed_test0  ${Python_LIBRARIES})
target_include_directories(py_speed_test0 PRIVATE ${Python_INCLUDE_DIRS})


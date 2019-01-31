cmake_minimum_required(VERSION 2.8.12)
project(cmake_example)

include_directories(${cmake_example_SOURCE_DIR}/arugula)
add_subdirectory(arugula)
add_subdirectory(pybind11)

pybind11_add_module(cmake_example src/main.cpp MODULE)
target_link_libraries(cmake_example PUBLIC arugula)

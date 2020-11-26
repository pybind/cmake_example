cmake_minimum_required(VERSION 3.4...3.18)
project(cmake_example)

find_package(Eigen3 CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(pybind11)
pybind11_add_module(cmake_example src/main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cmake_example PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

target_compile_features(cmake_example INTERFACE cxx_std_11)
target_link_libraries(cmake_example PRIVATE Eigen3::Eigen)

cmake_minimum_required(VERSION 3.4...3.18)
PROJECT(
    _phik_simulation
    VERSION 0.1.0
    DESCRIPTION "C++ bindings for simulation RXC tables"
    LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 14)
ADD_SUBDIRECTORY(pybind11)
INCLUDE(${PROJECT_SOURCE_DIR}/python/phik/simcore/CMakeLists.txt)

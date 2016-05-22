## Building pybind11 modules with CMake

An example of building a Python extension using [pybind11](https://github.com/pybind/pybind11) and CMake.
This is useful for C++ codebases that already have an existing CMake-based build system.

### Install

1. Make sure CMake >= 2.8.12 is installed on your system
2. Clone this repository
3. `pip install ./pybind11_cmake_example`

### Test

```python
import cmake_example
cmake_example.add(1, 2)
```

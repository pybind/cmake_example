# cmake_example for pybind11

[![Gitter][gitter-badge]][gitter-link]

|      CI              | status |
|----------------------|--------|
| MSVC 2015            | [![AppVeyor][appveyor-badge]][appveyor-link] |
| conda.recipe         | [![Conda Actions Status][actions-conda-badge]][actions-conda-link] |
| pip builds           | [![Pip Actions Status][actions-pip-badge]][actions-pip-link] |
| [`cibuildwheel`][]   | [![Wheels Actions Status][actions-wheels-badge]][actions-wheels-link] |

[gitter-badge]:            https://badges.gitter.im/pybind/Lobby.svg
[gitter-link]:             https://gitter.im/pybind/Lobby
[actions-badge]:           https://github.com/pybind/cmake_example/workflows/Tests/badge.svg
[actions-conda-link]:      https://github.com/pybind/cmake_example/actions?query=workflow%3A%22Conda
[actions-conda-badge]:     https://github.com/pybind/cmake_example/workflows/Conda/badge.svg
[actions-pip-link]:        https://github.com/pybind/cmake_example/actions?query=workflow%3A%22Pip
[actions-pip-badge]:       https://github.com/pybind/cmake_example/workflows/Pip/badge.svg
[actions-wheels-link]:     https://github.com/pybind/cmake_example/actions?query=workflow%3AWheels
[actions-wheels-badge]:    https://github.com/pybind/cmake_example/workflows/Wheels/badge.svg
[appveyor-link]:           https://ci.appveyor.com/project/dean0x7d/cmake-example/branch/master
[appveyor-badge]:          https://ci.appveyor.com/api/projects/status/57nnxfm4subeug43/branch/master?svg=true

An example [pybind11](https://github.com/pybind/pybind11) module built with a
CMake-based build system. This is useful for C++ codebases that have an
existing CMake project structure. This is in many cases superseded by
[`scikit_build_example`](https://github.com/pybind/scikit_build_example), which uses
[scikit-build][], a tool from the makers of CMake designed to allow Python
packages to be driven from CMake. However, there are still cases where you
might want full control over the CMake run; and both of these approaches have
some trade-offs not present in a pure setuptools build (see
[`python_example`](https://github.com/pybind/python_example)). Python 3.6+ required;
see the commit history for older versions of Python.

## Prerequisites

* A compiler with C++11 support
* Pip 10+ or CMake >= 3.4 (or 3.8+ on Windows, which was the first version to support VS 2015)
* Ninja or Pip 10+


## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/pybind/cmake_example.git
pip install ./cmake_example
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.



## Building the documentation

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd cmake_example/docs`
 - `make html`


## License

Pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.


## Test call

```python
import cmake_example
cmake_example.add(1, 2)
```

[`cibuildwheel`]:          https://cibuildwheel.readthedocs.io
[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
[scikit-build]: https://scikit-build.readthedocs.io/en/latest/

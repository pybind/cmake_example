import os
import re
import sys
import platform
import subprocess

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(["cmake", "--version"])
        except OSError:
            exts = ", ".join(e.name for e in self.extensions)
            msg = (
                "CMake must be installed to build the following extensions: {}".format(
                    exts
                )
            )
            raise RuntimeError(msg)

        build_ext.run(self)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # Using Ninja-build since it a) is available as a wheel and b) multithreads automatically
        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extdir),
            "-DPYTHON_EXECUTABLE={}".format(sys.executable),
        ]

        cfg = "Debug" if self.debug else "Release"

        if self.compiler.compiler_type == "msvc":
            from distutils.msvc9compiler import VERSION, query_vcvarsall, PLAT_TO_VCVARS, get_platform
            if not self.compiler.initialized:
                self.compiler.initialize(self.plat_name)

            plat_name = self.plat_name
            if plat_name == get_platform() or plat_name == 'win32':
                # native build or cross-compile to win32
                plat_spec = PLAT_TO_VCVARS[plat_name]
            else:
                # cross compile from win32 -> some 64bit
                plat_spec = PLAT_TO_VCVARS[get_platform()] + '_' + \
                            PLAT_TO_VCVARS[plat_name]

            vc_env = query_vcvarsall(VERSION, plat_spec)
            for key in vc_env:
                os.environ[key] = vc_env[key]

            print("INFO:", vc_env)

            cc = self.compiler.cc.replace("\\", "/")
            rc = self.compiler.rc.replace("\\", "/")
            mc = self.compiler.mc.replace("\\", "/")
            linker = self.compiler.linker.replace("\\", "/")
            cmake_args += [
                "-DCMAKE_C_COMPILER={}".format(cc),
                "-DCMAKE_CXX_COMPILER={}".format(cc),
                "-DCMAKE_LINKER={}".format(linker),
                "-DCMAKE_RC_COMPILER={}".format(rc),
                "-DCMAKE_MC_COMPILER={}".format(mc),
            ]

        cmake_args += [
            "-GNinja",
            "-DCMAKE_BUILD_TYPE={}".format(cfg),
            "-DEXAMPLE_VERSION_INFO={}".format(self.distribution.get_version()),
        ]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp, env=os.environ
        )
        subprocess.check_call(["cmake", "--build", "."], cwd=self.build_temp)


setup(
    name="cmake_example",
    version="0.0.1",
    author="Dean Moldovan",
    author_email="dean0x7d@gmail.com",
    description="A test project using pybind11 and CMake",
    long_description="",
    ext_modules=[CMakeExtension("cmake_example")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False,
)

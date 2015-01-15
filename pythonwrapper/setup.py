#!/usr/bin/env python
from sys import argv
lib_path = argv.pop(2)

from distutils.core import setup
from distutils.extension import Extension

setup(name="pyblockzor",
      ext_modules=[
        Extension("pyblockzor", ["pythonwrapper.cpp"],
        libraries = ["boost_python", "boost_numpy", "pyblockzor"],
        library_dirs=[lib_path, "/usr/local/lib"],
        include_dirs=['../include'])
     ])

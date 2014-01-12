from setuptools import setup, Extension
from Cython.Distutils import build_ext
import numpy as np

NAME = "fharvest"
VERSION = "0.2.1"
DESCR = "Small module for simulating robots on the pacific seafloor. Lots faster than doing it python."
URL = "https://github.com/Rentier/harvest-logic"
REQUIRES = ['numpy', 'cython']

AUTHOR = "Jan-Christoph Klie"
EMAIL = "git@mrklie.com"

LICENSE = "Apache 2.0"

SRC_DIR = "fharvest"
PACKAGES = [SRC_DIR]

LANGUAGE = "c++"

ext = Extension(
					SRC_DIR + ".logic",
					[
						"fharvest/logic.pyx",
						SRC_DIR + "/lib/Point.cpp",
						SRC_DIR + "/lib/Harvester.cpp",
						SRC_DIR + "/lib/Array3D.cpp",
						SRC_DIR + "/lib/Direction.cpp",
						SRC_DIR + "/lib/Mission.cpp",
					],
					language="c++",
					include_dirs=[					
						SRC_DIR,						
						SRC_DIR + "/lib",
						np.get_include(),
					],
					libraries=[],
					extra_compile_args=["-m32", "-O3"],
					extra_link_args=[]
				)


EXTENSIONS = [ext]

if __name__ == "__main__":
	setup(
			install_requires=REQUIRES,
			packages=PACKAGES,
			zip_safe=False,
			name=NAME,
			version=VERSION,
			description=DESCR,
			author=AUTHOR,
			author_email=EMAIL,
			url=URL,
			license=LICENSE,
			cmdclass={"build_ext": build_ext},
			ext_modules=EXTENSIONS,

		)
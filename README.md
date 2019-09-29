# Ogonek

Ogonek is mostly the result of me playing around with Unicode. Currently the
library is still in alpha stages, so I don't recommend using it for anything
serious, mainly because not all APIs are stabilised. You are welcome to play
around with it for any non-serious purposes, though.

## Status

The latest version, 0.5.0, implements most of the important stuff. The next
version, 0.6.0, will be a thorough refactoring of the code in order to enable
more type-safety and faster development.

## Setup

Ogonek is mostly header-only. The only part that needs compilation is the data
in the Unicode Character Database. Currently I am translating the database to
C++ source as static initializers, but I may change this in the future.

You can compile that data by running `scons dist` from the command line
(requires SCons to be installed, for obvious reasons). This will create a zip
file in the dist/ directory with both the headers and the library files
necessary to use ogonek. By default, a static library is built. To build a
shared library (DLL), add `lib=shared` to the command-line when building.

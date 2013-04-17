# Ogonek

Ogonek is mostly the result of me playing around with Unicode. Currently the
library is still in alpha stages, so I don't recommend using it for anything
serious, mainly because not all APIs are stabilised. You are welcome to play
around with it for any non-serious purposes, though.

Check out the [documentation] for more detailed information.

 [documentation]: http://flamingdangerzone.com/ogonek

## Status

[![Build Status](https://travis-ci.org/rmartinho/ogonek.png?branch=master)](https://travis-ci.org/rmartinho/ogonek)

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

Currently only compilation with 4.8.0 is being supported, but support for both
GCC 4.7.2 and Clang 3.2 is planned. Visual Studio 2012 may become a supported
target, depending on the quality of C++11 support when the previously announced
update is released.

## Helping out

Any feedback is appreciated. I am still designing and fleshing out some parts of
the APIs, so I appreciate any bug reports or design suggestions.

I often discuss my design in the [C++ Lounge][lounge] on Stack Overflow. Feel
free to join me there.

Pull requests are welcome too! There is a list of tasks I want done for 1.0.0 in
the [issue tracker]. Feel free to pick one to tackle!

 [lounge]: http://chat.stackoverflow.com/rooms/10/loungec
 [issue tracker]: https://github.com/rmartinho/ogonek/issues?state=open


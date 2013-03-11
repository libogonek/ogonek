Ogonek is mostly the result of me playing around with Unicode. Currently the
library is still in alpha stages, so I don't recommend using it for anything
serious, mainly because not all APIs are stabilised. You are welcome to play
around with it for any non-serious purposes, though.

Check out the [documentation] for more detailed information.

# Setup

Ogonek is mostly header-only. The only part that needs compilation is the data
in the Unicode Character Database. Currently I am translating the database to
C++ source as static initializers (I am aware of benefits and drawbacks of this
and other approaches and may or may not change in future versions).

You can compile that data by running `scons dist` from the command line
(requires SCons to be installed, for obvious reasons). This will create a zip
file in the dist/ directory with both the headers and the library files
necessary to use ogonek. By default, a static library is built. To build a
shared library (DLL), add `lib=shared` to the command-line when building.

Note that as of this writing only compilation with GCC 4.7.2 and clang 3.2 has
been tested. MSVC will only be considered as a target after the big C++11
update to VS 2012.

# Helping out

Any feedback is appreciated. I am still designing and fleshing out some parts of
the APIs, so I appreciate any bug reports or design suggestions.

I often discuss my design in the [C++ Lounge][lounge] on Stack Overflow. Feel
free to join me there. 

Pull requests are welcome too! There is a list of tasks I want done for 1.0.0 in
the [issue tracker]. Feel free to pick one to tackle!

 [documentation]: http://flamingdangerzone.com/ogonek
 [lounge]: http://chat.stackoverflow.com/rooms/10/loungec
 [issue tracker]: https://github.com/rmartinho/ogonek/issues?state=open


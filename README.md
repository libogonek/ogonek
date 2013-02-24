Ogonek is mostly the result of me playing around with Unicode. Currently the
library is still in alpha stages, so I don't recommend using it for anything
serious.

Check out the [documentation] for more detailed information.

# Setup

Ogonek is mostly header-only. The only part that needs compilation is the data
in the Unicode Character Database. Currently I am translating the database to
C++ source as static initializers (I am aware of the benefits and drawbacks of
this and other approaches and may or may not change in future versions). If
you want to get started quickly, you can find pre-generated source code for
various versions of the database in the [downloads] page. If you want to make
your own version of the database, you can find a translator from the XML UCD in
the `tools` folder.

Once you have source code for the UCD, you can compile the whole shebang by
running `scons dist` from the command line (requires SCons to be installed, for
obvious reasons). This will create a zip file in the dist/ directory with both
the headers and the library files necessary to use ogonek. By default, a static
library is built. To build a shared library (DLL), add `lib=shared` to the
command-line when building.

# Helping out

Any feedback is appreciated. I am still designing and fleshing out some parts of
the APIs, so I appreciate any bug reports or design suggestions.

I often discuss my design in the [C++ Lounge][lounge] on Stack Overflow. Feel
free to join me there. 

Pull requests are welcome too! There is a list of tasks I want done for 1.0.0 in
the [issue tracker]. Feel free to pick one to tackle!

 [documentation]: http://flamingdangerzone.com/ogonek
 [downloads]: http://bitbucket.org/martinhofernandes/ogonek/downloads
 [lounge]: http://chat.stackoverflow.com/rooms/10/loungec
 [issue tracker]: https://github.com/rmartinho/ogonek/issues?sort=created&state=open


# Ogonek

Ogonek is mostly the result of me playing around with Unicode. Currently the
library is still in alpha stages, so I don't recommend using it for anything
serious, mainly because not all APIs are stabilised. You are welcome to play
around with it for any non-serious purposes, though.

Check out the [documentation] for more detailed information.

 [documentation]: http://flamingdangerzone.com/ogonek

## Status

The latest version, 0.5.0, implements most of the important stuff. The next
version, 0.6.0, will be a thorough refactoring of the code in order to enable
more type-safety and faster development.

## Setup

Ogonek is mostly header-only. The only part that needs compilation is the data
in the Unicode Character Database. Currently I am translating the database to
C++ source as static initializers, but I may change this in the future.

<!-- to be written -->

## Helping out

Any feedback is appreciated. I am still designing and fleshing out some parts of
the APIs, so I appreciate any [bug reports][issue tracker] or design suggestions.

I often discuss my design in the [C++ Lounge][lounge] on Stack Overflow. Feel
free to join me there.

Pull requests are welcome too! There is a list of tasks I want done for 1.0.0 in
the [issue tracker]. Feel free to pick one to tackle!

 [lounge]: http://chat.stackoverflow.com/rooms/10/loungec
 [issue tracker]: http://bugs.flamingdangerzone.com/youtrack/issues?q=project%3A+Ogonek


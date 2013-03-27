// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Version info boilerplate

#ifndef OGONEK_VERSION_HPP
#define OGONEK_VERSION_HPP

#define OGONEK_VERSION (\
    OGONEK_VERSION_MAJOR * 10000 +\
    OGONEK_VERSION_MINOR * 100 +\
    OGONEK_VERSION_REVISION)

#define OGONEK_VERSION_STRINGIZE(X) #X
#define OGONEK_VERSION_STRING \
    OGONEK_VERSION_STRINGIZE(OGONEK_VERSION_MAJOR) \
    "." \
    OGONEK_VERSION_STRINGIZE(OGONEK_VERSION_MINOR) \
    "." \
    OGONEK_VERSION_STRINGIZE(OGONEK_VERSION_REVISION) \
    "-" \
    OGONEK_VERSION_STRINGIZE(OGONEK_VERSION_EXTRA) \

#endif // OGONEK_VERSION_HPP

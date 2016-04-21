// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Library visibility boilerplate

#ifndef OGONEK_VISIBILITY_HPP
#define OGONEK_VISIBILITY_HPP

#if defined _WIN32 || defined __CYGWIN__
  #define OGONEK_ATTRIBUTE_IMPORT __declspec(dllimport)
  #define OGONEK_ATTRIBUTE_EXPORT __declspec(dllexport)
  #define OGONEK_ATTRIBUTE_INTERNAL
#else
  #if __GNUC__ >= 4
    #define OGONEK_ATTRIBUTE_IMPORT __attribute__ ((visibility("default")))
    #define OGONEK_ATTRIBUTE_EXPORT __attribute__ ((visibility("default")))
    #define OGONEK_ATTRIBUTE_INTERNAL __attribute__ ((visibility("hidden")))
  #else
    #define OGONEK_ATTRIBUTE_IMPORT
    #define OGONEK_ATTRIBUTE_EXPORT
    #define OGONEK_ATTRIBUTE_INTERNAL
  #endif
#endif

#ifdef OGONEK_SHARED // shared library
  #ifdef OGONEK_BUILD // Compiling
    #define OGONEK_PUBLIC OGONEK_ATTRIBUTE_EXPORT
  #else // Linking
    #define OGONEK_PUBLIC OGONEK_ATTRIBUTE_IMPORT
  #endif
  #define OGONEK_INTERNAL OGONEK_ATTRIBUTE_INTERNAL
#else // static library
  #define OGONEK_PUBLIC
  #define OGONEK_INTERNAL
#endif

#endif // OGONEK_VISIBILITY_HPP


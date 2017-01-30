// Ogonek
//
// Written in 2016 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Ogonek core types

#ifndef OGONEK_TYPES_HPP
#define OGONEK_TYPES_HPP

#include <cstddef>

namespace ogonek {
    //! A code point.
    using code_point = char32_t;

    namespace detail {
        struct fraction { long num, den; };
        struct trinary { int value; };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_TYPES_HPP

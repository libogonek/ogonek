// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Fundamental types

#ifndef OGONEK_TYPES_HPP
#define OGONEK_TYPES_HPP

namespace ogonek {
    using byte = unsigned char;
    using code_point = char32_t;

    namespace literal {
        constexpr byte operator"" _b(unsigned long long n) { return static_cast<byte>(n); }
    } // namespace literal
} // namespace ogonek

#endif // OGONEK_TYPES_HPP

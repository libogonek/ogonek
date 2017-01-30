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

// This file was automatically generated.

// Unicode character database - ASCII_Hex_Digit property

#include <ogonek/ucd/ascii_hex_digit.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            ascii_hex_digit_properties const ascii_hex_digit_data_raw[] {
                { 0x0, false },
                { 0x30, true },
                { 0x3A, false },
                { 0x41, true },
                { 0x47, false },
                { 0x61, true },
                { 0x67, false },
            };
        } // namespace
        inline namespace abiv0 {
            ascii_hex_digit_properties const* ascii_hex_digit_data = ascii_hex_digit_data_raw;
            std::size_t ascii_hex_digit_data_size = detail::size(ascii_hex_digit_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

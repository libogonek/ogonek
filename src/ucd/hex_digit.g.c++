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

// Unicode character database - Hex_Digit property

#include <ogonek/ucd/hex_digit.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            hex_digit_properties const hex_digit_data_raw[] {
                { 0x0, false },
                { 0x30, true },
                { 0x3A, false },
                { 0x41, true },
                { 0x47, false },
                { 0x61, true },
                { 0x67, false },
                { 0xFF10, true },
                { 0xFF1A, false },
                { 0xFF21, true },
                { 0xFF27, false },
                { 0xFF41, true },
                { 0xFF47, false },
            };
        } // namespace
        inline namespace abiv0 {
            hex_digit_properties const* hex_digit_data = hex_digit_data_raw;
            std::size_t hex_digit_data_size = detail::size(hex_digit_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

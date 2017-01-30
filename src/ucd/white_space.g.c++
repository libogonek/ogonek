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

// Unicode character database - White_Space property

#include <ogonek/ucd/white_space.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            white_space_properties const white_space_data_raw[] {
                { 0x0, false },
                { 0x9, true },
                { 0xE, false },
                { 0x20, true },
                { 0x21, false },
                { 0x85, true },
                { 0x86, false },
                { 0xA0, true },
                { 0xA1, false },
                { 0x1680, true },
                { 0x1681, false },
                { 0x2000, true },
                { 0x200B, false },
                { 0x2028, true },
                { 0x202A, false },
                { 0x202F, true },
                { 0x2030, false },
                { 0x205F, true },
                { 0x2060, false },
                { 0x3000, true },
                { 0x3001, false },
            };
        } // namespace
        inline namespace abiv0 {
            white_space_properties const* white_space_data = white_space_data_raw;
            std::size_t white_space_data_size = detail::size(white_space_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

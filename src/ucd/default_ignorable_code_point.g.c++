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

// Unicode character database - Default_Ignorable_Code_Point property

#include <ogonek/ucd/default_ignorable_code_point.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            default_ignorable_code_point_properties const default_ignorable_code_point_data_raw[] {
                { 0x0, false },
                { 0xAD, true },
                { 0xAE, false },
                { 0x34F, true },
                { 0x350, false },
                { 0x61C, true },
                { 0x61D, false },
                { 0x115F, true },
                { 0x1161, false },
                { 0x17B4, true },
                { 0x17B6, false },
                { 0x180B, true },
                { 0x180F, false },
                { 0x200B, true },
                { 0x2010, false },
                { 0x202A, true },
                { 0x202F, false },
                { 0x2060, true },
                { 0x2070, false },
                { 0x3164, true },
                { 0x3165, false },
                { 0xFE00, true },
                { 0xFE10, false },
                { 0xFEFF, true },
                { 0xFF00, false },
                { 0xFFA0, true },
                { 0xFFA1, false },
                { 0xFFF0, true },
                { 0xFFF9, false },
                { 0x1BCA0, true },
                { 0x1BCA4, false },
                { 0x1D173, true },
                { 0x1D17B, false },
                { 0xE0000, true },
                { 0xE1000, false },
            };
        } // namespace
        inline namespace abiv0 {
            default_ignorable_code_point_properties const* default_ignorable_code_point_data = default_ignorable_code_point_data_raw;
            std::size_t default_ignorable_code_point_data_size = detail::size(default_ignorable_code_point_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

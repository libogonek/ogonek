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

// Unicode character database - Pattern_White_Space property

#include <ogonek/ucd/pattern_white_space.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            pattern_white_space_properties const pattern_white_space_data_raw[] {
                { 0x0, false },
                { 0x9, true },
                { 0xE, false },
                { 0x20, true },
                { 0x21, false },
                { 0x85, true },
                { 0x86, false },
                { 0x200E, true },
                { 0x2010, false },
                { 0x2028, true },
                { 0x202A, false },
            };
        } // namespace
        inline namespace abiv0 {
            pattern_white_space_properties const* pattern_white_space_data = pattern_white_space_data_raw;
            std::size_t pattern_white_space_data_size = detail::size(pattern_white_space_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

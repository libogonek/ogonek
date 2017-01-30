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

// Unicode character database - Ideographic property

#include <ogonek/ucd/ideographic.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            ideographic_properties const ideographic_data_raw[] {
                { 0x0, false },
                { 0x3006, true },
                { 0x3008, false },
                { 0x3021, true },
                { 0x302A, false },
                { 0x3038, true },
                { 0x303B, false },
                { 0x3400, true },
                { 0x4DB6, false },
                { 0x4E00, true },
                { 0x9FD6, false },
                { 0xF900, true },
                { 0xFA6E, false },
                { 0xFA70, true },
                { 0xFADA, false },
                { 0x17000, true },
                { 0x187ED, false },
                { 0x18800, true },
                { 0x18AF3, false },
                { 0x20000, true },
                { 0x2A6D7, false },
                { 0x2A700, true },
                { 0x2B735, false },
                { 0x2B740, true },
                { 0x2B81E, false },
                { 0x2B820, true },
                { 0x2CEA2, false },
                { 0x2F800, true },
                { 0x2FA1E, false },
            };
        } // namespace
        inline namespace abiv0 {
            ideographic_properties const* ideographic_data = ideographic_data_raw;
            std::size_t ideographic_data_size = detail::size(ideographic_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

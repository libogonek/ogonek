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

// Unicode character database - Bidi_Control property

#include <ogonek/ucd/bidi_control.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            bidi_control_properties const bidi_control_data_raw[] {
                { 0x0, false },
                { 0x61C, true },
                { 0x61D, false },
                { 0x200E, true },
                { 0x2010, false },
                { 0x202A, true },
                { 0x202F, false },
                { 0x2066, true },
                { 0x206A, false },
            };
        } // namespace
        inline namespace abiv0 {
            bidi_control_properties const* bidi_control_data = bidi_control_data_raw;
            std::size_t bidi_control_data_size = detail::size(bidi_control_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

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

// Unicode character database - Variation_Selector property

#include <ogonek/ucd/variation_selector.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            variation_selector_properties const variation_selector_data_raw[] {
                { 0x0, false },
                { 0x180B, true },
                { 0x180E, false },
                { 0xFE00, true },
                { 0xFE10, false },
                { 0xE0100, true },
                { 0xE01F0, false },
            };
        } // namespace
        inline namespace abiv0 {
            variation_selector_properties const* variation_selector_data = variation_selector_data_raw;
            std::size_t variation_selector_data_size = detail::size(variation_selector_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

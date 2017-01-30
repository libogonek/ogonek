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

// Unicode character database - Radical property

#include <ogonek/ucd/radical.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            radical_properties const radical_data_raw[] {
                { 0x0, false },
                { 0x2E80, true },
                { 0x2E9A, false },
                { 0x2E9B, true },
                { 0x2EF4, false },
                { 0x2F00, true },
                { 0x2FD6, false },
            };
        } // namespace
        inline namespace abiv0 {
            radical_properties const* radical_data = radical_data_raw;
            std::size_t radical_data_size = detail::size(radical_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

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

// This file was automatically generated on 2016-04-18T17:07:59.174867Z

// Unicode character database - Deprecated property

#include <ogonek/ucd/deprecated.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            deprecated_properties const deprecated_data_raw[] {
                { 0x0, false },
                { 0x149, true },
                { 0x14A, false },
                { 0x673, true },
                { 0x674, false },
                { 0xF77, true },
                { 0xF78, false },
                { 0xF79, true },
                { 0xF7A, false },
                { 0x17A3, true },
                { 0x17A5, false },
                { 0x206A, true },
                { 0x2070, false },
                { 0x2329, true },
                { 0x232B, false },
                { 0xE0001, true },
                { 0xE0002, false },
                { 0xE007F, true },
                { 0xE0080, false },
            };
        } // namespace
        namespace abiv0 {
            deprecated_properties const* deprecated_data = deprecated_data_raw;
            std::size_t deprecated_data_size = detail::size(deprecated_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

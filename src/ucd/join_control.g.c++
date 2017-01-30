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

// Unicode character database - Join_Control property

#include <ogonek/ucd/join_control.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            join_control_properties const join_control_data_raw[] {
                { 0x0, false },
                { 0x200C, true },
                { 0x200E, false },
            };
        } // namespace
        inline namespace abiv0 {
            join_control_properties const* join_control_data = join_control_data_raw;
            std::size_t join_control_data_size = detail::size(join_control_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

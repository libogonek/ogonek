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

// Unicode character database - IDS_Binary_Operator property

#include <ogonek/ucd/ids_binary_operator.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            ids_binary_operator_properties const ids_binary_operator_data_raw[] {
                { 0x0, false },
                { 0x2FF0, true },
                { 0x2FF2, false },
                { 0x2FF4, true },
                { 0x2FFC, false },
            };
        } // namespace
        inline namespace abiv0 {
            ids_binary_operator_properties const* ids_binary_operator_data = ids_binary_operator_data_raw;
            std::size_t ids_binary_operator_data_size = detail::size(ids_binary_operator_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

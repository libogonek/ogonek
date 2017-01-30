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

// Unicode character database - Simple_Lowercase_Mapping property

#ifndef OGONEK_UCD_SIMPLE_LOWERCASE_MAPPING_HPP
#define OGONEK_UCD_SIMPLE_LOWERCASE_MAPPING_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            

            struct simple_lowercase_mapping_properties {
                code_point start;
                code_point value;
            };

            extern OGONEK_PUBLIC simple_lowercase_mapping_properties const* simple_lowercase_mapping_data;
            extern OGONEK_PUBLIC std::size_t simple_lowercase_mapping_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_SIMPLE_LOWERCASE_MAPPING_HPP

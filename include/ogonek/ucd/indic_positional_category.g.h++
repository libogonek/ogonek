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

// This file was automatically generated on 2016-09-05T11:29:13.385291Z

// Unicode character database - Indic_Positional_Category property

#ifndef OGONEK_UCD_INDIC_POSITIONAL_CATEGORY_HPP
#define OGONEK_UCD_INDIC_POSITIONAL_CATEGORY_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class indic_positional_category {
                bottom,
                bottom_and_right,
                left,
                left_and_right,
                na,
                overstruck,
                right,
                top,
                top_and_bottom,
                top_and_bottom_and_right,
                top_and_left,
                top_and_left_and_right,
                top_and_right,
                visual_order_left,
            };

            struct indic_positional_category_properties {
                code_point start;
                indic_positional_category value;
            };

            extern OGONEK_PUBLIC indic_positional_category_properties const* indic_positional_category_data;
            extern OGONEK_PUBLIC std::size_t indic_positional_category_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_INDIC_POSITIONAL_CATEGORY_HPP

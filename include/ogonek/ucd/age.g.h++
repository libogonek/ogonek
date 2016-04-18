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

// This file was automatically generated on 2016-04-18T15:55:59.291865Z

// Unicode character database - Age property

#ifndef OGONEK_UCD_AGE_HPP
#define OGONEK_UCD_AGE_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class version {
                _1_1,
                _2_0,
                _2_1,
                _3_0,
                _3_1,
                _3_2,
                _4_0,
                _4_1,
                _5_0,
                _5_1,
                _5_2,
                _6_0,
                _6_1,
                _6_2,
                _6_3,
                _7_0,
                _8_0,
                na,
                v1_1 = _1_1,
                v2_0 = _2_0,
                v2_1 = _2_1,
                v3_0 = _3_0,
                v3_1 = _3_1,
                v3_2 = _3_2,
                v4_0 = _4_0,
                v4_1 = _4_1,
                v5_0 = _5_0,
                v5_1 = _5_1,
                v5_2 = _5_2,
                v6_0 = _6_0,
                v6_1 = _6_1,
                v6_2 = _6_2,
                v6_3 = _6_3,
                v7_0 = _7_0,
                v8_0 = _8_0,
                unassigned = na,
            };

            struct age_properties {
                code_point start;
                version value;
            };

            extern OGONEK_PUBLIC age_properties const* age_data;
            extern OGONEK_PUBLIC std::size_t age_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_AGE_HPP

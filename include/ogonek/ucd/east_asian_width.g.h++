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

// This file was automatically generated on 2016-09-05T11:29:13.166909Z

// Unicode character database - East_Asian_Width property

#ifndef OGONEK_UCD_EAST_ASIAN_WIDTH_HPP
#define OGONEK_UCD_EAST_ASIAN_WIDTH_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class east_asian_width {
                a,
                f,
                h,
                n,
                na,
                w,
                ambiguous = a,
                fullwidth = f,
                halfwidth = h,
                neutral = n,
                narrow = na,
                wide = w,
            };

            struct east_asian_width_properties {
                code_point start;
                east_asian_width value;
            };

            extern OGONEK_PUBLIC east_asian_width_properties const* east_asian_width_data;
            extern OGONEK_PUBLIC std::size_t east_asian_width_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_EAST_ASIAN_WIDTH_HPP

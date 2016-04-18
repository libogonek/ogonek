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

// This file was automatically generated on 2016-04-18T17:07:59.416561Z

// Unicode character database - Joining_Type property

#ifndef OGONEK_UCD_JOINING_TYPE_HPP
#define OGONEK_UCD_JOINING_TYPE_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class joining_type {
                c,
                d,
                l,
                r,
                t,
                u,
                join_causing = c,
                dual_joining = d,
                left_joining = l,
                right_joining = r,
                transparent = t,
                non_joining = u,
            };

            struct joining_type_properties {
                code_point start;
                joining_type value;
            };

            extern OGONEK_PUBLIC joining_type_properties const* joining_type_data;
            extern OGONEK_PUBLIC std::size_t joining_type_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_JOINING_TYPE_HPP

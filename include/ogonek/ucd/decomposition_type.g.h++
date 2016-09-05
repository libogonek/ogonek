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

// This file was automatically generated on 2016-09-05T11:29:13.142124Z

// Unicode character database - Decomposition_Type property

#ifndef OGONEK_UCD_DECOMPOSITION_TYPE_HPP
#define OGONEK_UCD_DECOMPOSITION_TYPE_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class decomposition_type {
                can,
                com,
                enc,
                fin,
                font,
                fra,
                init,
                iso,
                med,
                nar,
                nb,
                none,
                sml,
                sqr,
                sub,
                sup,
                vert,
                wide,
                canonical = can,
                compat = com,
                circle = enc,
                final = fin,
                fraction = fra,
                initial = init,
                isolated = iso,
                medial = med,
                narrow = nar,
                nobreak = nb,
                small = sml,
                square = sqr,
                super = sup,
                vertical = vert,
            };

            struct decomposition_type_properties {
                code_point start;
                decomposition_type value;
            };

            extern OGONEK_PUBLIC decomposition_type_properties const* decomposition_type_data;
            extern OGONEK_PUBLIC std::size_t decomposition_type_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_DECOMPOSITION_TYPE_HPP

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

// Unicode character database - Grapheme_Cluster_Break property

#ifndef OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP
#define OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class grapheme_cluster_break {
                cn,
                cr,
                eb,
                ebg,
                em,
                ex,
                gaz,
                l,
                lf,
                lv,
                lvt,
                pp,
                ri,
                sm,
                t,
                v,
                xx,
                zwj,
                control = cn,
                e_base = eb,
                e_base_gaz = ebg,
                e_modifier = em,
                extend = ex,
                glue_after_zwj = gaz,
                prepend = pp,
                regional_indicator = ri,
                spacing_mark = sm,
                other = xx,
            };

            struct grapheme_cluster_break_properties {
                code_point start;
                grapheme_cluster_break value;
            };

            extern OGONEK_PUBLIC grapheme_cluster_break_properties const* grapheme_cluster_break_data;
            extern OGONEK_PUBLIC std::size_t grapheme_cluster_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_GRAPHEME_CLUSTER_BREAK_HPP

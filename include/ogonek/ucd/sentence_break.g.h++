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

// Unicode character database - Sentence_Break property

#ifndef OGONEK_UCD_SENTENCE_BREAK_HPP
#define OGONEK_UCD_SENTENCE_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class sentence_break {
                at,
                cl,
                cr,
                ex,
                fo,
                le,
                lf,
                lo,
                nu,
                sc,
                se,
                sp,
                st,
                up,
                xx,
                aterm = at,
                close = cl,
                extend = ex,
                format = fo,
                oletter = le,
                lower = lo,
                numeric = nu,
                scontinue = sc,
                sep = se,
                sterm = st,
                upper = up,
                other = xx,
            };

            struct sentence_break_properties {
                code_point start;
                sentence_break value;
            };

            extern OGONEK_PUBLIC sentence_break_properties const* sentence_break_data;
            extern OGONEK_PUBLIC std::size_t sentence_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_SENTENCE_BREAK_HPP

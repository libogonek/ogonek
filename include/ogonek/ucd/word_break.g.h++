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

// This file was automatically generated on 2016-04-18T17:08:00.165153Z

// Unicode character database - Word_Break property

#ifndef OGONEK_UCD_WORD_BREAK_HPP
#define OGONEK_UCD_WORD_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class word_break {
                cr,
                dq,
                ex,
                extend,
                fo,
                hl,
                ka,
                le,
                lf,
                mb,
                ml,
                mn,
                nl,
                nu,
                ri,
                sq,
                xx,
                double_quote = dq,
                extend_num_let = ex,
                format = fo,
                hebrew_letter = hl,
                katakana = ka,
                aletter = le,
                mid_num_let = mb,
                mid_letter = ml,
                mid_num = mn,
                newline = nl,
                numeric = nu,
                regional_indicator = ri,
                single_quote = sq,
                other = xx,
            };

            struct word_break_properties {
                code_point start;
                word_break value;
            };

            extern OGONEK_PUBLIC word_break_properties const* word_break_data;
            extern OGONEK_PUBLIC std::size_t word_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_WORD_BREAK_HPP

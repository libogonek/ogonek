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

// Unicode character database - Line_Break property

#ifndef OGONEK_UCD_LINE_BREAK_HPP
#define OGONEK_UCD_LINE_BREAK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class line_break {
                ai,
                al,
                b2,
                ba,
                bb,
                bk,
                cb,
                cj,
                cl,
                cm,
                cp,
                cr,
                eb,
                em,
                ex,
                gl,
                h2,
                h3,
                hl,
                hy,
                id,
                in,
                is,
                jl,
                jt,
                jv,
                lf,
                nl,
                ns,
                nu,
                op,
                po,
                pr,
                qu,
                ri,
                sa,
                sg,
                sp,
                sy,
                wj,
                xx,
                zw,
                zwj,
                ambiguous = ai,
                alphabetic = al,
                break_both = b2,
                break_after = ba,
                break_before = bb,
                mandatory_break = bk,
                contingent_break = cb,
                conditional_japanese_starter = cj,
                close_punctuation = cl,
                combining_mark = cm,
                close_parenthesis = cp,
                carriage_return = cr,
                e_base = eb,
                e_modifier = em,
                exclamation = ex,
                glue = gl,
                hebrew_letter = hl,
                hyphen = hy,
                ideographic = id,
                inseparable = in,
                inseperable = in,
                infix_numeric = is,
                line_feed = lf,
                next_line = nl,
                nonstarter = ns,
                numeric = nu,
                open_punctuation = op,
                postfix_numeric = po,
                prefix_numeric = pr,
                quotation = qu,
                regional_indicator = ri,
                complex_context = sa,
                surrogate = sg,
                space = sp,
                break_symbols = sy,
                word_joiner = wj,
                unknown = xx,
                zwspace = zw,
            };

            struct line_break_properties {
                code_point start;
                line_break value;
            };

            extern OGONEK_PUBLIC line_break_properties const* line_break_data;
            extern OGONEK_PUBLIC std::size_t line_break_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_LINE_BREAK_HPP

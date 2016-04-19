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

// This file was automatically generated on 2016-04-18T17:07:58.864735Z

// Unicode character database - Bidi_Class property

#ifndef OGONEK_UCD_BIDI_CLASS_HPP
#define OGONEK_UCD_BIDI_CLASS_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class bidi_class {
                al,
                an,
                b,
                bn,
                cs,
                en,
                es,
                et,
                fsi,
                l,
                lre,
                lri,
                lro,
                nsm,
                on,
                pdf,
                pdi,
                r,
                rle,
                rli,
                rlo,
                s,
                ws,
                arabic_letter = al,
                arabic_number = an,
                paragraph_separator = b,
                boundary_neutral = bn,
                common_separator = cs,
                european_number = en,
                european_separator = es,
                european_terminator = et,
                first_strong_isolate = fsi,
                left_to_right = l,
                left_to_right_embedding = lre,
                left_to_right_isolate = lri,
                left_to_right_override = lro,
                nonspacing_mark = nsm,
                other_neutral = on,
                pop_directional_format = pdf,
                pop_directional_isolate = pdi,
                right_to_left = r,
                right_to_left_embedding = rle,
                right_to_left_isolate = rli,
                right_to_left_override = rlo,
                segment_separator = s,
                white_space = ws,
            };

            struct bidi_class_properties {
                code_point start;
                bidi_class value;
            };

            extern OGONEK_PUBLIC bidi_class_properties const* bidi_class_data;
            extern OGONEK_PUBLIC std::size_t bidi_class_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_BIDI_CLASS_HPP

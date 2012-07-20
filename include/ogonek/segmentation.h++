// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode character database data structures

#ifndef OGONEK_SEGMENTATION_HPP
#define OGONEK_SEGMENTATION_HPP

#include "types.h++"
#include "ucd.h++"

#include <type_traits>

namespace ogonek {
    namespace detail {
        using gcb = ucd::grapheme_cluster_break;
        struct grapheme_cluster_rule {
            gcb before;
            bool is_break;
            gcb after;
        };
        constexpr gcb operator|(gcb l, gcb r) {
            using underlying = std::underlying_type<gcb>::type;
            return static_cast<gcb>(static_cast<underlying>(l), static_cast<underlying>(r));
        }
        constexpr gcb any = static_cast<gcb>(0xFFFFFFFFu);
        constexpr grapheme_cluster_rule operator*(gcb l, gcb r) { return { l, false, r }; }
        constexpr grapheme_cluster_rule operator/(gcb l, gcb r) { return { l, true, r }; }

        grapheme_cluster_rule rules[] = {
            // Break at the start and end of text.
            // GB1. sot ÷
            // GB2.     ÷ eot
            // These are handled specially

            // Do not break between a CR and LF. Otherwise, break before and after controls.
            gcb::CR * gcb::LF,                   // GB3.	CR	×	LF
            (gcb::CN | gcb::CR | gcb::LF) / any, // GB4.	( Control | CR | LF )	÷	 
            any / (gcb::CN | gcb::CR | gcb::LF)  // GB5.		÷	( Control | CR | LF )

            // Do not break Hangul syllable sequences.
            gcb::L * (gcb::L | gcb::V | gcb::LV | gcb::LVT), // GB6.	L	×	( L | V | LV | LVT )
            (gcb::LV | gcb::V) * (gcb::V | gcb::T),          // GB7.	( LV | V )	×	( V | T )
            (gcb::LVT | gcb::T) * gcb::T,                    // GB8.	( LVT | T)	×	T

            // Do not break before extending characters.
            any * gcb::XX, // GB9.	 	×	Extend

            // Do not break before SpacingMarks, or after Prepend characters.
            any * gcb::SM, // GB9a.	 	×	SpacingMark
            gcb::PP * any, // GB9b.	Prepend	×	 

            // Otherwise, break everywhere.
            any / any, // GB10.	Any	÷ Any
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP


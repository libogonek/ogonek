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

// This file was automatically generated on 2016-04-18T15:55:59.351870Z

// Unicode character database - Bidi_Paired_Bracket property

#ifndef OGONEK_UCD_BIDI_PAIRED_BRACKET_HPP
#define OGONEK_UCD_BIDI_PAIRED_BRACKET_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            

            struct bidi_paired_bracket_properties {
                code_point start;
                code_point value;
            };

            extern OGONEK_PUBLIC bidi_paired_bracket_properties const* bidi_paired_bracket_data;
            extern OGONEK_PUBLIC std::size_t bidi_paired_bracket_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_BIDI_PAIRED_BRACKET_HPP

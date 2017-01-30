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

// Unicode character database - Hangul_Syllable_Type property

#ifndef OGONEK_UCD_HANGUL_SYLLABLE_TYPE_HPP
#define OGONEK_UCD_HANGUL_SYLLABLE_TYPE_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class hangul_syllable_type {
                l,
                lv,
                lvt,
                na,
                t,
                v,
                leading_jamo = l,
                lv_syllable = lv,
                lvt_syllable = lvt,
                not_applicable = na,
                trailing_jamo = t,
                vowel_jamo = v,
            };

            struct hangul_syllable_type_properties {
                code_point start;
                hangul_syllable_type value;
            };

            extern OGONEK_PUBLIC hangul_syllable_type_properties const* hangul_syllable_type_data;
            extern OGONEK_PUBLIC std::size_t hangul_syllable_type_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HANGUL_SYLLABLE_TYPE_HPP

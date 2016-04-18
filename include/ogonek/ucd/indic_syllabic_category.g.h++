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

// This file was automatically generated on 2016-04-18T15:55:59.852057Z

// Unicode character database - Indic_Syllabic_Category property

#ifndef OGONEK_UCD_INDIC_SYLLABIC_CATEGORY_HPP
#define OGONEK_UCD_INDIC_SYLLABIC_CATEGORY_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class indic_syllabic_category {
                avagraha,
                bindu,
                brahmi_joining_number,
                cantillation_mark,
                consonant,
                consonant_dead,
                consonant_final,
                consonant_head_letter,
                consonant_killer,
                consonant_medial,
                consonant_placeholder,
                consonant_preceding_repha,
                consonant_prefixed,
                consonant_subjoined,
                consonant_succeeding_repha,
                consonant_with_stacker,
                gemination_mark,
                invisible_stacker,
                joiner,
                modifying_letter,
                non_joiner,
                nukta,
                number,
                number_joiner,
                other,
                pure_killer,
                register_shifter,
                syllable_modifier,
                tone_letter,
                tone_mark,
                virama,
                visarga,
                vowel,
                vowel_dependent,
                vowel_independent,
            };

            struct indic_syllabic_category_properties {
                code_point start;
                indic_syllabic_category value;
            };

            extern OGONEK_PUBLIC indic_syllabic_category_properties const* indic_syllabic_category_data;
            extern OGONEK_PUBLIC std::size_t indic_syllabic_category_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_INDIC_SYLLABIC_CATEGORY_HPP

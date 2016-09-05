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

// This file was automatically generated on 2016-09-05T11:29:12.871581Z

// Unicode character database - Block property

#ifndef OGONEK_UCD_BLOCK_HPP
#define OGONEK_UCD_BLOCK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class block {
                adlam,
                aegean_numbers,
                ahom,
                alchemical,
                alphabetic_pf,
                anatolian_hieroglyphs,
                ancient_greek_music,
                ancient_greek_numbers,
                ancient_symbols,
                arabic,
                arabic_ext_a,
                arabic_math,
                arabic_pf_a,
                arabic_pf_b,
                arabic_sup,
                armenian,
                arrows,
                ascii,
                avestan,
                balinese,
                bamum,
                bamum_sup,
                bassa_vah,
                batak,
                bengali,
                bhaiksuki,
                block_elements,
                bopomofo,
                bopomofo_ext,
                box_drawing,
                brahmi,
                braille,
                buginese,
                buhid,
                byzantine_music,
                carian,
                caucasian_albanian,
                chakma,
                cham,
                cherokee,
                cherokee_sup,
                cjk,
                cjk_compat,
                cjk_compat_forms,
                cjk_compat_ideographs,
                cjk_compat_ideographs_sup,
                cjk_ext_a,
                cjk_ext_b,
                cjk_ext_c,
                cjk_ext_d,
                cjk_ext_e,
                cjk_radicals_sup,
                cjk_strokes,
                cjk_symbols,
                compat_jamo,
                control_pictures,
                coptic,
                coptic_epact_numbers,
                counting_rod,
                cuneiform,
                cuneiform_numbers,
                currency_symbols,
                cypriot_syllabary,
                cyrillic,
                cyrillic_ext_a,
                cyrillic_ext_b,
                cyrillic_ext_c,
                cyrillic_sup,
                deseret,
                devanagari,
                devanagari_ext,
                diacriticals,
                diacriticals_ext,
                diacriticals_for_symbols,
                diacriticals_sup,
                dingbats,
                domino,
                duployan,
                early_dynastic_cuneiform,
                egyptian_hieroglyphs,
                elbasan,
                emoticons,
                enclosed_alphanum,
                enclosed_alphanum_sup,
                enclosed_cjk,
                enclosed_ideographic_sup,
                ethiopic,
                ethiopic_ext,
                ethiopic_ext_a,
                ethiopic_sup,
                geometric_shapes,
                geometric_shapes_ext,
                georgian,
                georgian_sup,
                glagolitic,
                glagolitic_sup,
                gothic,
                grantha,
                greek,
                greek_ext,
                gujarati,
                gurmukhi,
                half_and_full_forms,
                half_marks,
                hangul,
                hanunoo,
                hatran,
                hebrew,
                high_pu_surrogates,
                high_surrogates,
                hiragana,
                idc,
                ideographic_symbols,
                imperial_aramaic,
                indic_number_forms,
                inscriptional_pahlavi,
                inscriptional_parthian,
                ipa_ext,
                jamo,
                jamo_ext_a,
                jamo_ext_b,
                javanese,
                kaithi,
                kana_sup,
                kanbun,
                kangxi,
                kannada,
                katakana,
                katakana_ext,
                kayah_li,
                kharoshthi,
                khmer,
                khmer_symbols,
                khojki,
                khudawadi,
                lao,
                latin_1_sup,
                latin_ext_a,
                latin_ext_additional,
                latin_ext_b,
                latin_ext_c,
                latin_ext_d,
                latin_ext_e,
                lepcha,
                letterlike_symbols,
                limbu,
                linear_a,
                linear_b_ideograms,
                linear_b_syllabary,
                lisu,
                low_surrogates,
                lycian,
                lydian,
                mahajani,
                mahjong,
                malayalam,
                mandaic,
                manichaean,
                marchen,
                math_alphanum,
                math_operators,
                meetei_mayek,
                meetei_mayek_ext,
                mende_kikakui,
                meroitic_cursive,
                meroitic_hieroglyphs,
                miao,
                misc_arrows,
                misc_math_symbols_a,
                misc_math_symbols_b,
                misc_pictographs,
                misc_symbols,
                misc_technical,
                modi,
                modifier_letters,
                modifier_tone_letters,
                mongolian,
                mongolian_sup,
                mro,
                multani,
                music,
                myanmar,
                myanmar_ext_a,
                myanmar_ext_b,
                nabataean,
                nb,
                new_tai_lue,
                newa,
                nko,
                number_forms,
                ocr,
                ogham,
                ol_chiki,
                old_hungarian,
                old_italic,
                old_north_arabian,
                old_permic,
                old_persian,
                old_south_arabian,
                old_turkic,
                oriya,
                ornamental_dingbats,
                osage,
                osmanya,
                pahawh_hmong,
                palmyrene,
                pau_cin_hau,
                phags_pa,
                phaistos,
                phoenician,
                phonetic_ext,
                phonetic_ext_sup,
                playing_cards,
                psalter_pahlavi,
                pua,
                punctuation,
                rejang,
                rumi,
                runic,
                samaritan,
                saurashtra,
                sharada,
                shavian,
                shorthand_format_controls,
                siddham,
                sinhala,
                sinhala_archaic_numbers,
                small_forms,
                sora_sompeng,
                specials,
                sundanese,
                sundanese_sup,
                sup_arrows_a,
                sup_arrows_b,
                sup_arrows_c,
                sup_math_operators,
                sup_pua_a,
                sup_pua_b,
                sup_punctuation,
                sup_symbols_and_pictographs,
                super_and_sub,
                sutton_sign_writing,
                syloti_nagri,
                syriac,
                tagalog,
                tagbanwa,
                tags,
                tai_le,
                tai_tham,
                tai_viet,
                tai_xuan_jing,
                takri,
                tamil,
                tangut,
                tangut_components,
                telugu,
                thaana,
                thai,
                tibetan,
                tifinagh,
                tirhuta,
                transport_and_map,
                ucas,
                ucas_ext,
                ugaritic,
                vai,
                vedic_ext,
                vertical_forms,
                vs,
                vs_sup,
                warang_citi,
                yi_radicals,
                yi_syllables,
                yijing,
                alchemical_symbols = alchemical,
                alphabetic_presentation_forms = alphabetic_pf,
                ancient_greek_musical_notation = ancient_greek_music,
                arabic_extended_a = arabic_ext_a,
                arabic_mathematical_alphabetic_symbols = arabic_math,
                arabic_presentation_forms_a = arabic_pf_a,
                arabic_presentation_forms_b = arabic_pf_b,
                arabic_supplement = arabic_sup,
                basic_latin = ascii,
                bamum_supplement = bamum_sup,
                bopomofo_extended = bopomofo_ext,
                braille_patterns = braille,
                byzantine_musical_symbols = byzantine_music,
                cherokee_supplement = cherokee_sup,
                cjk_unified_ideographs = cjk,
                cjk_compatibility = cjk_compat,
                cjk_compatibility_forms = cjk_compat_forms,
                cjk_compatibility_ideographs = cjk_compat_ideographs,
                cjk_compatibility_ideographs_supplement = cjk_compat_ideographs_sup,
                cjk_unified_ideographs_extension_a = cjk_ext_a,
                cjk_unified_ideographs_extension_b = cjk_ext_b,
                cjk_unified_ideographs_extension_c = cjk_ext_c,
                cjk_unified_ideographs_extension_d = cjk_ext_d,
                cjk_unified_ideographs_extension_e = cjk_ext_e,
                cjk_radicals_supplement = cjk_radicals_sup,
                cjk_symbols_and_punctuation = cjk_symbols,
                hangul_compatibility_jamo = compat_jamo,
                counting_rod_numerals = counting_rod,
                cuneiform_numbers_and_punctuation = cuneiform_numbers,
                cyrillic_extended_a = cyrillic_ext_a,
                cyrillic_extended_b = cyrillic_ext_b,
                cyrillic_extended_c = cyrillic_ext_c,
                cyrillic_supplement = cyrillic_sup,
                cyrillic_supplementary = cyrillic_sup,
                devanagari_extended = devanagari_ext,
                combining_diacritical_marks = diacriticals,
                combining_diacritical_marks_extended = diacriticals_ext,
                combining_diacritical_marks_for_symbols = diacriticals_for_symbols,
                combining_marks_for_symbols = diacriticals_for_symbols,
                combining_diacritical_marks_supplement = diacriticals_sup,
                domino_tiles = domino,
                enclosed_alphanumerics = enclosed_alphanum,
                enclosed_alphanumeric_supplement = enclosed_alphanum_sup,
                enclosed_cjk_letters_and_months = enclosed_cjk,
                enclosed_ideographic_supplement = enclosed_ideographic_sup,
                ethiopic_extended = ethiopic_ext,
                ethiopic_extended_a = ethiopic_ext_a,
                ethiopic_supplement = ethiopic_sup,
                geometric_shapes_extended = geometric_shapes_ext,
                georgian_supplement = georgian_sup,
                glagolitic_supplement = glagolitic_sup,
                greek_and_coptic = greek,
                greek_extended = greek_ext,
                halfwidth_and_fullwidth_forms = half_and_full_forms,
                combining_half_marks = half_marks,
                hangul_syllables = hangul,
                high_private_use_surrogates = high_pu_surrogates,
                ideographic_description_characters = idc,
                ideographic_symbols_and_punctuation = ideographic_symbols,
                common_indic_number_forms = indic_number_forms,
                ipa_extensions = ipa_ext,
                hangul_jamo = jamo,
                hangul_jamo_extended_a = jamo_ext_a,
                hangul_jamo_extended_b = jamo_ext_b,
                kana_supplement = kana_sup,
                kangxi_radicals = kangxi,
                katakana_phonetic_extensions = katakana_ext,
                latin_1_supplement = latin_1_sup,
                latin_1 = latin_1_sup,
                latin_extended_a = latin_ext_a,
                latin_extended_additional = latin_ext_additional,
                latin_extended_b = latin_ext_b,
                latin_extended_c = latin_ext_c,
                latin_extended_d = latin_ext_d,
                latin_extended_e = latin_ext_e,
                mahjong_tiles = mahjong,
                mathematical_alphanumeric_symbols = math_alphanum,
                mathematical_operators = math_operators,
                meetei_mayek_extensions = meetei_mayek_ext,
                miscellaneous_symbols_and_arrows = misc_arrows,
                miscellaneous_mathematical_symbols_a = misc_math_symbols_a,
                miscellaneous_mathematical_symbols_b = misc_math_symbols_b,
                miscellaneous_symbols_and_pictographs = misc_pictographs,
                miscellaneous_symbols = misc_symbols,
                miscellaneous_technical = misc_technical,
                spacing_modifier_letters = modifier_letters,
                mongolian_supplement = mongolian_sup,
                musical_symbols = music,
                myanmar_extended_a = myanmar_ext_a,
                myanmar_extended_b = myanmar_ext_b,
                no_block = nb,
                optical_character_recognition = ocr,
                phaistos_disc = phaistos,
                phonetic_extensions = phonetic_ext,
                phonetic_extensions_supplement = phonetic_ext_sup,
                private_use_area = pua,
                private_use = pua,
                general_punctuation = punctuation,
                rumi_numeral_symbols = rumi,
                small_form_variants = small_forms,
                sundanese_supplement = sundanese_sup,
                supplemental_arrows_a = sup_arrows_a,
                supplemental_arrows_b = sup_arrows_b,
                supplemental_arrows_c = sup_arrows_c,
                supplemental_mathematical_operators = sup_math_operators,
                supplementary_private_use_area_a = sup_pua_a,
                supplementary_private_use_area_b = sup_pua_b,
                supplemental_punctuation = sup_punctuation,
                supplemental_symbols_and_pictographs = sup_symbols_and_pictographs,
                superscripts_and_subscripts = super_and_sub,
                tai_xuan_jing_symbols = tai_xuan_jing,
                transport_and_map_symbols = transport_and_map,
                unified_canadian_aboriginal_syllabics = ucas,
                canadian_syllabics = ucas,
                unified_canadian_aboriginal_syllabics_extended = ucas_ext,
                vedic_extensions = vedic_ext,
                variation_selectors = vs,
                variation_selectors_supplement = vs_sup,
                yijing_hexagram_symbols = yijing,
            };

            struct block_properties {
                code_point start;
                block value;
            };

            extern OGONEK_PUBLIC block_properties const* block_data;
            extern OGONEK_PUBLIC std::size_t block_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_BLOCK_HPP

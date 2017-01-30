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

// Unicode character database

#ifndef OGONEK_UCD_HPP
#define OGONEK_UCD_HPP

#include <ogonek/ucd/ucd_all.g.h++>

#include <ogonek/types.h++>

#include <boost/logic/tribool.hpp>
#include <boost/optional.hpp>
#include <boost/rational.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>

#include <cstddef>
#include <cstring>

namespace ogonek {
    //! An alternative name for ``boost::indeterminate``.
    BOOST_TRIBOOL_THIRD_STATE(maybe)

    namespace ucd {
        namespace detail {
            inline boost::tribool to_tribool(ogonek::detail::trinary t) {
                switch(t.value) {
                    case -1:
                        return maybe;
                    default:
                        return t.value;
                }
            }
            inline boost::optional<boost::rational<long>> to_rational(ogonek::detail::fraction f) {
                if(f.den == 0) return boost::none;
                else return boost::rational<long>(f.num, f.den);
            }

            template <typename It>
            std::reverse_iterator<It> make_reverse(It it) {
                return std::reverse_iterator<It>(it);
            }
            struct property_group_comparer {
                template <typename T>
                bool operator()(code_point u, T const& g) const {
                    return u >= g.start;
                }
            };
            template <typename T>
            T const& find_property_group(T const* first, std::size_t size, code_point u) {
                return *std::upper_bound(make_reverse(first + size), make_reverse(first), u, property_group_comparer{});
            }

            inline void add_hex(code_point u, std::string& s) {
                char const hex[] = "0123456789ABCDEF";
                int factor;
                if(u > 0xFFFFF) factor = 0x100000;
                else if(u > 0xFFFF) factor = 0x10000;
                else factor = 0x1000;
                for(; factor > 0; u %= factor, factor /= 0x10) {
                    s.push_back(hex[u / factor]);
                }
            }
            template <std::size_t N>
            std::string make_ideograph_name(code_point u, char const (&base)[N]) {
                std::string result;
                result.reserve(N + 5);
                result = base;
                add_hex(u, result);
                return result;
            }
            inline char const* get_jamo_short_name(code_point u) {
                return detail::find_property_group(jamo_short_name_data, jamo_short_name_data_size, u).value;
            }
            template <std::size_t N>
            std::string make_hangul_syllable_name(code_point u, char const (&base)[N]) {
                const int sbase = 0xAC00;
                const int lbase = 0x1100;
                const int vbase = 0x1161;
                const int tbase = 0x11A7;
                const int tcount = 28;
                const int ncount = 588;

                auto sindex = u - sbase;
                auto lindex = sindex / ncount;
                auto vindex = (sindex % ncount) / tcount;
                auto tindex = sindex % tcount;
                auto lpart = lbase + lindex;
                auto vpart = vbase + vindex;
                auto tpart = tbase + tindex;

                std::string result;
                result.reserve(N + 9);
                result += base;
                result += detail::get_jamo_short_name(lpart);
                result += detail::get_jamo_short_name(vpart);
                if(tindex > 0) result += detail::get_jamo_short_name(tpart);
                return result;
            }
        } // namespace detail

#define OGONEK_UCD_QUERY(type, name, query) \
        inline type query(code_point u) {\
            return detail::find_property_group(name##_data, name##_data_size, u).value;\
        }\
        static_assert(true, "")
#define OGONEK_UCD_GETTER(type, name) OGONEK_UCD_QUERY(type, name, get_##name)
#define OGONEK_UCD_TESTER(name) OGONEK_UCD_QUERY(bool, name, is_##name)
#define OGONEK_UCD_TESTER3(name) \
        inline boost::tribool get_##name(code_point u) {\
            auto value = detail::find_property_group(name##_data, name##_data_size, u).value;\
            return detail::to_tribool(value);\
        }\
        static_assert(true, "")
#define OGONEK_UCD_CODE_POINT_GETTER(name) \
        inline code_point get_##name(code_point u) {\
            auto value = detail::find_property_group(name##_data, name##_data_size, u).value;\
            if(value == code_point(-1)) return u;\
            else return value;\
        }\
        static_assert(true, "")

        //! Retrieves a code point's ``Age`` property
        OGONEK_UCD_GETTER(version, age);

        //! Retrieves a code point's ``Name`` property
        inline std::string get_name(code_point u) {
            auto value = detail::find_property_group(name_data, name_data_size, u).value;
            if(value[0] != '<') return value;

            if(std::strcmp(value, "<CJK Ideograph>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension A>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension B>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension C>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension D>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension E>") == 0) {
                return detail::make_ideograph_name(u, "CJK UNIFIED IDEOGRAPH-");
            }
            if(std::strcmp(value, "<Hangul Syllable>") == 0) {
                return detail::make_hangul_syllable_name(u, "HANGUL SYLLABLE ");
            }
            return {};
        }

        //! Retrieves a code point's ``Block`` property
        OGONEK_UCD_GETTER(block, block);
        //! Retrieves a code point's ``General_Category`` property
        OGONEK_UCD_GETTER(general_category, general_category);
        //! Retrieves a code point's ``Canonical_Combining_Class`` property
        OGONEK_UCD_GETTER(combining_class, canonical_combining_class);
        //! Retrieves a code point's ``Bidi_Class`` property
        OGONEK_UCD_GETTER(bidi_class, bidi_class);
        //! Retrieves a code point's ``Bidi_Mirrored`` property
        OGONEK_UCD_TESTER(bidi_mirrored);
        //! Retrieves a code point's ``Bidi_Mirroring_Glyph`` property
        OGONEK_UCD_CODE_POINT_GETTER(bidi_mirroring_glyph);
        //! Retrieves a code point's ``Bidi_Control`` property
        OGONEK_UCD_TESTER(bidi_control);
        //! Retrieves a code point's ``Bidi_Paired_Bracket`` property
        OGONEK_UCD_CODE_POINT_GETTER(bidi_paired_bracket);
        //! Retrieves a code point's ``Bidi_Paired_Bracket_Type`` property
        OGONEK_UCD_GETTER(bracket_type, bidi_paired_bracket_type);
        //! Retrieves a code point's ``Decomposition_Type`` property
        OGONEK_UCD_GETTER(decomposition_type, decomposition_type);

        //! Retrieves a code point's ``Decomposition_Mapping`` property
        inline std::u32string get_decomposition_mapping(code_point u) {
            auto value = detail::find_property_group(decomposition_mapping_data, decomposition_mapping_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, u);
        }

        //! Retrieves a code point's ``Full_Composition_Exclusion`` property
        OGONEK_UCD_QUERY(bool, full_composition_exclusion, is_excluded_from_composition);
        //! Retrieves a code point's ``NFC_Quick_Check`` property
        OGONEK_UCD_TESTER3(nfc_quick_check);
        //! Retrieves a code point's ``NFD_Quick_Check`` property
        OGONEK_UCD_GETTER(bool, nfd_quick_check);
        //! Retrieves a code point's ``NFKC_Quick_Check`` property
        OGONEK_UCD_TESTER3(nfkc_quick_check);
        //! Retrieves a code point's ``NFKD_Quick_Check`` property
        OGONEK_UCD_GETTER(bool, nfkd_quick_check);
        //! Retrieves a code point's ``Numeric_Type`` property
        OGONEK_UCD_GETTER(numeric_type, numeric_type);

        //! Retrieves a code point's ``Numeric_Value`` property
        inline boost::optional<boost::rational<long>> get_numeric_value(code_point u) {
            auto value = detail::find_property_group(numeric_value_data, numeric_value_data_size, u).value;
            return detail::to_rational(value);
        }

        //! Retrieves a code point's ``Joining_Type`` property
        OGONEK_UCD_GETTER(joining_type, joining_type);
        //! Retrieves a code point's ``Joining_Group`` property
        OGONEK_UCD_GETTER(joining_group, joining_group);
        //! Retrieves a code point's ``Join_Control`` property
        OGONEK_UCD_TESTER(join_control);
        //! Retrieves a code point's ``Line_Break`` property
        OGONEK_UCD_GETTER(line_break, line_break);
        //! Retrieves a code point's ``East_Asian_Width`` property
        OGONEK_UCD_GETTER(east_asian_width, east_asian_width);
        //! Retrieves a code point's ``Uppercase`` property
        OGONEK_UCD_TESTER(uppercase);
        //! Retrieves a code point's ``Lowercase`` property
        OGONEK_UCD_TESTER(lowercase);
        //! Retrieves a code point's ``Simple_Uppercase_Mapping`` property
        OGONEK_UCD_CODE_POINT_GETTER(simple_uppercase_mapping);
        //! Retrieves a code point's ``Simple_Lowercase_Mapping`` property
        OGONEK_UCD_CODE_POINT_GETTER(simple_lowercase_mapping);
        //! Retrieves a code point's ``Simple_Titlecase_Mapping`` property
        OGONEK_UCD_CODE_POINT_GETTER(simple_titlecase_mapping);

        //! Retrieves a code point's ``Uppercase_Mapping`` property
        inline std::u32string get_uppercase_mapping(code_point u) {
            auto value = detail::find_property_group(uppercase_mapping_data, uppercase_mapping_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, get_simple_uppercase_mapping(u));
        }
        //! Retrieves a code point's ``Lowercase_Mapping`` property
        inline std::u32string get_lowercase_mapping(code_point u) {
            auto value = detail::find_property_group(lowercase_mapping_data, lowercase_mapping_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, get_simple_lowercase_mapping(u));
        }
        //! Retrieves a code point's ``Titlecase_Mapping`` property
        inline std::u32string get_titlecase_mapping(code_point u) {
            auto value = detail::find_property_group(titlecase_mapping_data, titlecase_mapping_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, get_simple_titlecase_mapping(u));
        }

        //! Retrieves a code point's ``Simple_Case_Folding`` property
        OGONEK_UCD_CODE_POINT_GETTER(simple_case_folding);

        //! Retrieves a code point's ``Case_Folding`` property
        inline std::u32string get_case_folding(code_point u) {
            auto value = detail::find_property_group(case_folding_data, case_folding_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, get_simple_case_folding(u));
        }

        //! Retrieves a code point's ``Case_Ignorable`` property
        OGONEK_UCD_TESTER(case_ignorable);
        //! Retrieves a code point's ``Cased`` property
        OGONEK_UCD_TESTER(cased);
        //! Retrieves a code point's ``Changes_When_Lowercased`` property
        OGONEK_UCD_QUERY(bool, changes_when_lowercased, changes_when_lowercased);
        //! Retrieves a code point's ``Changes_When_Uppercased`` property
        OGONEK_UCD_QUERY(bool, changes_when_uppercased, changes_when_uppercased);
        //! Retrieves a code point's ``Changes_When_Titlecased`` property
        OGONEK_UCD_QUERY(bool, changes_when_titlecased, changes_when_titlecased);
        //! Retrieves a code point's ``Changes_When_Casefolded`` property
        OGONEK_UCD_QUERY(bool, changes_when_casefolded, changes_when_casefolded);
        //! Retrieves a code point's ``Changes_When_Casemapped`` property
        OGONEK_UCD_QUERY(bool, changes_when_casemapped, changes_when_casemapped);
        //! Retrieves a code point's ``Changes_When_NFKC_Casefolded`` property
        OGONEK_UCD_QUERY(bool, changes_when_nfkc_casefolded, changes_when_nfkc_casefolded);

        //! Retrieves a code point's ``NFKC_Casefold`` property
        inline std::u32string get_nfkc_casefold(code_point u) {
            auto value = detail::find_property_group(nfkc_casefold_data, nfkc_casefold_data_size, u).value;
            if(value) return value;
            else return std::u32string(1, u);
        }

        //! Retrieves a code point's ``Script`` property
        OGONEK_UCD_GETTER(script, script);
        //! Retrieves a code point's ``Hangul_Syllable_Type`` property
        OGONEK_UCD_GETTER(hangul_syllable_type, hangul_syllable_type);

        //! Retrieves a code point's ``Jamo_Short_Name`` property
        inline std::string get_jamo_short_name(code_point u) { return detail::get_jamo_short_name(u); }

        //! Retrieves a code point's ``Indic_Positional_Category`` property
        OGONEK_UCD_GETTER(indic_positional_category, indic_positional_category);
        //! Retrieves a code point's ``Indic_Syllabic_Category`` property
        OGONEK_UCD_GETTER(indic_syllabic_category, indic_syllabic_category);
        //! Retrieves a code point's ``ID_Start`` property
        OGONEK_UCD_TESTER(id_start);
        //! Retrieves a code point's ``ID_Continue`` property
        OGONEK_UCD_TESTER(id_continue);
        //! Retrieves a code point's ``XID_Start`` property
        OGONEK_UCD_TESTER(xid_start);
        //! Retrieves a code point's ``XID_Continue`` property
        OGONEK_UCD_TESTER(xid_continue);
        //! Retrieves a code point's ``Pattern_Syntax`` property
        OGONEK_UCD_TESTER(pattern_syntax);
        //! Retrieves a code point's ``Pattern_White_Space`` property
        OGONEK_UCD_TESTER(pattern_white_space);
        //! Retrieves a code point's ``Dash`` property
        OGONEK_UCD_TESTER(dash);
        //! Retrieves a code point's ``Quotation_Mark`` property
        OGONEK_UCD_TESTER(quotation_mark);
        //! Retrieves a code point's ``Terminal_Punctuation`` property
        OGONEK_UCD_TESTER(terminal_punctuation);
        //! Retrieves a code point's ``STerm`` property
        OGONEK_UCD_TESTER(sterm);
        //! Retrieves a code point's ``Diacritic`` property
        OGONEK_UCD_TESTER(diacritic);
        //! Retrieves a code point's ``Extender`` property
        OGONEK_UCD_TESTER(extender);
        //! Retrieves a code point's ``Soft_Dotted`` property
        OGONEK_UCD_TESTER(soft_dotted);
        //! Retrieves a code point's ``Hex_Digit`` property
        OGONEK_UCD_TESTER(hex_digit);
        //! Retrieves a code point's ``ASCII_Hex_Digit`` property
        OGONEK_UCD_TESTER(ascii_hex_digit);
        //! Retrieves a code point's ``Logical_Order_Exception`` property
        OGONEK_UCD_TESTER(logical_order_exception);
        //! Retrieves a code point's ``White_Space`` property
        OGONEK_UCD_TESTER(white_space);
        //! Retrieves a code point's ``Variation_Selector`` property
        OGONEK_UCD_TESTER(variation_selector);
        //! Retrieves a code point's ``Alphabetic`` property
        OGONEK_UCD_TESTER(alphabetic);
        //! Retrieves a code point's ``Math`` property
        OGONEK_UCD_TESTER(math);
        //! Retrieves a code point's ``Default_Ignorable_Code_Point`` property
        OGONEK_UCD_TESTER(default_ignorable_code_point);
        //! Retrieves a code point's ``Grapheme_Base`` property
        OGONEK_UCD_TESTER(grapheme_base);
        //! Retrieves a code point's ``Grapheme_Extend`` property
        OGONEK_UCD_TESTER(grapheme_extend);
        //! Retrieves a code point's ``Grapheme_Cluster_Break`` property
        OGONEK_UCD_GETTER(grapheme_cluster_break, grapheme_cluster_break);
        //! Retrieves a code point's ``Word_Break`` property
        OGONEK_UCD_GETTER(word_break, word_break);
        //! Retrieves a code point's ``Sentence_Break`` property
        OGONEK_UCD_GETTER(sentence_break, sentence_break);
        //! Retrieves a code point's ``Ideographic`` property
        OGONEK_UCD_TESTER(ideographic);
        //! Retrieves a code point's ``Unified_Ideograph`` property
        OGONEK_UCD_TESTER(unified_ideograph);
        //! Retrieves a code point's ``IDS_Binary_Operator`` property
        OGONEK_UCD_TESTER(ids_binary_operator);
        //! Retrieves a code point's ``IDS_Trinary_Operator`` property
        OGONEK_UCD_TESTER(ids_trinary_operator);
        //! Retrieves a code point's ``Radical`` property
        OGONEK_UCD_TESTER(radical);
        //! Retrieves a code point's ``Deprecated`` property
        OGONEK_UCD_TESTER(deprecated);
        //! Retrieves a code point's ``Noncharacter_Code_Point`` property
        OGONEK_UCD_TESTER(noncharacter_code_point);

#undef OGONEK_UCD_CODE_POINT_GETTER
#undef OGONEK_UCD_TESTER3
#undef OGONEK_UCD_TESTER
#undef OGONEK_UCD_GETTER
#undef OGONEK_UCD_QUERY
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HPP


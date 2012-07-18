// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
//
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode character database

#include <ogonek/ucd.h++>
#include <ogonek/detail/properties.h++>
#include <ogonek/types.h++>

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

namespace ogonek {
    namespace ucd {
        extern version_properties const* version_data;
        extern std::size_t version_data_size;
        extern name_properties const* name_data;
        extern std::size_t name_data_size;
        extern name_properties const* v1name_data;
        extern std::size_t v1name_data_size;
        extern alias_properties const* aliases_data;
        extern std::size_t aliases_data_size;
        extern block_properties const* block_data;
        extern std::size_t block_data_size;
        extern category_properties const* category_data;
        extern std::size_t category_data_size;
        extern combining_class_properties const* combining_class_data;
        extern std::size_t combining_class_data_size;
        extern bidi_properties const* bidi_data;
        extern std::size_t bidi_data_size;
        extern decomposition_properties const* decomposition_data;
        extern std::size_t decomposition_data_size;
        extern numeric_properties const* numeric_data;
        extern std::size_t numeric_data_size;
        extern joining_properties const* joining_data;
        extern std::size_t joining_data_size;
        extern linebreak_properties const* linebreak_data;
        extern std::size_t linebreak_data_size;
        extern east_asian_properties const* east_asian_data;
        extern std::size_t east_asian_data_size;
        extern case_properties const* case_data;
        extern std::size_t case_data_size;
        extern script_properties const* script_data;
        extern std::size_t script_data_size;
        extern iso_comment_properties const* iso_comment_data;
        extern std::size_t iso_comment_data_size;
        extern hangul_properties const* hangul_data;
        extern std::size_t hangul_data_size;
        extern indic_properties const* indic_data;
        extern std::size_t indic_data_size;
        extern identifier_properties const* identifier_data;
        extern std::size_t identifier_data_size;
        extern pattern_properties const* pattern_data;
        extern std::size_t pattern_data_size;
        extern function_properties const* function_data;
        extern std::size_t function_data_size;
        extern boundary_properties const* boundary_data;
        extern std::size_t boundary_data_size;
        extern ideograph_properties const* ideograph_data;
        extern std::size_t ideograph_data_size;
        extern miscellaneous_properties const* miscellaneous_data;
        extern std::size_t miscellaneous_data_size;

        namespace {
            struct property_group_locator {
                template <typename T>
                bool operator()(codepoint u, T const& g) const {
                    return u >= g.start;
                }
            };
            template <typename It>
            std::reverse_iterator<It> make_reverse(It it) {
                return std::reverse_iterator<It> { it };
            }
            template <typename T>
            T const& find_property_group(T const* first, std::size_t size, codepoint target) {
                return *std::upper_bound(make_reverse(first+size), make_reverse(first), target, property_group_locator{});
            }
            boost::tribool to_tribool(yes_no_maybe ynm) {
                if(ynm == yes_no_maybe::y) return true;
                else if(ynm == yes_no_maybe::n) return false;
                else return boost::indeterminate;
            }
        } // namespace

        version get_age(codepoint u) {
            return find_property_group(version_data, version_data_size, u).data;
        }
        block get_block(codepoint u) {
            return find_property_group(block_data, block_data_size, u).data;
        }
        category get_general_category(codepoint u) {
            return find_property_group(category_data, category_data_size, u).data;
        }
        int get_combining_class(codepoint u) {
            return find_property_group(combining_class_data, combining_class_data_size, u).data;
        }
        bidi_category get_bidi_category(codepoint u) {
            return find_property_group(bidi_data, bidi_data_size, u).category;
        }
        bool is_bidi_mirrored(codepoint u) {
            return find_property_group(bidi_data, bidi_data_size, u).mirrored;
        }
        codepoint get_bidi_mirrored_glyph(codepoint u) {
            auto glyph = find_property_group(bidi_data, bidi_data_size, u).mirrored_glyph;
            if(glyph == static_cast<char32_t>(-1)) return u;
            else return glyph;
        }
        bool is_bidi_control(codepoint u) {
            return find_property_group(bidi_data, bidi_data_size, u).control;
        }
        decomposition_type get_decomposition_type(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).type;
        }
        std::vector<codepoint> get_decomposition_mapping(codepoint u) {
            auto group = find_property_group(decomposition_data, decomposition_data_size, u);
            auto mapping = group.mapping;
            if(mapping) return std::vector<codepoint>(mapping, mapping + std::char_traits<codepoint>::length(mapping));
            else return std::vector<codepoint>(1, u);
        }
        bool is_excluded_from_composition(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).full_composition_exclusion;
        }
        boost::tribool is_nfc_quick_check(codepoint u) {
            return to_tribool(find_property_group(decomposition_data, decomposition_data_size, u).nfc_quick_check);
        }
        bool is_nfd_quick_check(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).nfd_quick_check;
        }
        boost::tribool is_nfkc_quick_check(codepoint u) {
            return to_tribool(find_property_group(decomposition_data, decomposition_data_size, u).nfkc_quick_check);
        }
        bool is_nfkd_quick_check(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).nfkd_quick_check;
        }
        //[[deprecated("since 6.0")]]
        bool expands_on_nfc(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfc;
        }
        //[[deprecated("since 6.0")]]
        bool expands_on_nfd(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfd;
        }
        //[[deprecated("since 6.0")]]
        bool expands_on_nfkc(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfkc;
        }
        //[[deprecated("since 6.0")]]
        bool expands_on_nfkd(codepoint u) {
            return find_property_group(decomposition_data, decomposition_data_size, u).expands_on_nfkd;
        }
        //[[deprecated("since 6.0")]]
        detail::array_slice<codepoint const> get_fc_nfkc_closure(codepoint u) {
            auto closure = find_property_group(decomposition_data, decomposition_data_size, u).fc_nfkc_closure;
            return { closure, closure + std::char_traits<codepoint>::length(closure) };
        }
        numeric_type get_numeric_type(codepoint u) {
            return find_property_group(numeric_data, numeric_data_size, u).type;
        }
        double get_numeric_value(codepoint u) {
            return find_property_group(numeric_data, numeric_data_size, u).value;
        }
        joining_class get_joining_class(codepoint u) {
            return find_property_group(joining_data, joining_data_size, u).class_;
        }
        joining_group get_joining_group(codepoint u) {
            return find_property_group(joining_data, joining_data_size, u).group;
        }
        bool is_join_control(codepoint u) {
            return find_property_group(joining_data, joining_data_size, u).control;
        }
        linebreak get_linebreak_type(codepoint u) {
            return find_property_group(linebreak_data, linebreak_data_size, u).data;
        }
        east_asian_width get_east_asian_width_type(codepoint u) {
            return find_property_group(east_asian_data, east_asian_data_size, u).data;
        }
        bool is_uppercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).is_uppercase;
        }
        bool is_lowercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).is_lowercase;
        }
        bool is_other_uppercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).other_uppercase;
        }
        bool is_other_lowercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).other_lowercase;
        }
        codepoint get_simple_uppercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).simple_uppercase;
        }
        codepoint get_simple_lowercase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).simple_lowercase;
        }
        codepoint get_simple_titlecase(codepoint u) {
            return find_property_group(case_data, case_data_size, u).simple_titlecase;
        }
        detail::array_slice<codepoint const> get_uppercase(codepoint u) {
            auto result = find_property_group(case_data, case_data_size, u).uppercase;
            return { result, result + std::char_traits<codepoint>::length(result) };
        }
        detail::array_slice<codepoint const> get_lowercase(codepoint u) {
            auto result = find_property_group(case_data, case_data_size, u).lowercase;
            return { result, result + std::char_traits<codepoint>::length(result) };
        }
        detail::array_slice<codepoint const> get_titlecase(codepoint u) {
            auto result = find_property_group(case_data, case_data_size, u).titlecase;
            return { result, result + std::char_traits<codepoint>::length(result) };
        }
        codepoint get_simple_case_folding(codepoint u) {
            return find_property_group(case_data, case_data_size, u).simple_case_folding;
        }
        detail::array_slice<codepoint const> get_case_folding(codepoint u) {
            auto result = find_property_group(case_data, case_data_size, u).case_folding;
            return { result, result + std::char_traits<codepoint>::length(result) };
        }
        bool is_case_ignorable(codepoint u) {
            return find_property_group(case_data, case_data_size, u).case_ignorable;
        }
        bool is_cased(codepoint u) {
            return find_property_group(case_data, case_data_size, u).cased;
        }
        bool changes_when_casefolded(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_casefolded;
        }
        bool changes_when_casemapped(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_casemapped;
        }
        bool changes_when_lowercased(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_lowercased;
        }
        bool changes_when_nfkc_casefolded(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_nfkc_casefolded;
        }
        bool changes_when_titlecased(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_titlecased;
        }
        bool changes_when_uppercased(codepoint u) {
            return find_property_group(case_data, case_data_size, u).changes_when_uppercased;
        }
        detail::array_slice<codepoint const> get_nfkc_casefold(codepoint u) {
            auto result = find_property_group(case_data, case_data_size, u).nfkc_casefold;
            return { result, result + std::char_traits<codepoint>::length(result) };
        }
        script get_script(codepoint u) {
            return find_property_group(script_data, script_data_size, u).script;
        }
        detail::array_slice<script const> get_script_extension(codepoint u) {
            auto& prop = find_property_group(script_data, script_data_size, u);
            return { prop.first_script_extension, prop.first_script_extension + prop.script_extension_count };
        }
        // text get_iso_comment(codepoint u) {
        hangul_syllable_type get_hangul_syllable_type(codepoint u) {
            return find_property_group(hangul_data, hangul_data_size, u).syllable_type;
        }
        // text get_jamo_short_name(codepoint u) {
        indic_syllable_category get_indic_syllable_category(codepoint u) {
            return find_property_group(indic_data, indic_data_size, u).syllable_category;
        }
        indic_matra_category get_indic_matra_category(codepoint u) {
            return find_property_group(indic_data, indic_data_size, u).matra_category;
        }
        bool is_id_start(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).id_start;
        }
        bool is_other_id_start(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).other_id_start;
        }
        bool is_xid_start(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).xid_start;
        }
        bool is_id_continue(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).id_continue;
        }
        bool is_other_id_continue(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).other_id_continue;
        }
        bool is_xid_continue(codepoint u) {
            return find_property_group(identifier_data, identifier_data_size, u).xid_continue;
        }
        bool is_pattern_syntax(codepoint u) {
            return find_property_group(pattern_data, pattern_data_size, u).syntax;
        }
        bool is_pattern_white_space(codepoint u) {
            return find_property_group(pattern_data, pattern_data_size, u).white_space;
        }
        bool is_dash(codepoint u) {
            return find_property_group(function_data, function_data_size, u).dash;
        }
        bool is_hyphen(codepoint u) {
            return find_property_group(function_data, function_data_size, u).hyphen;
        }
        bool is_quotation_mark(codepoint u) {
            return find_property_group(function_data, function_data_size, u).quotation_mark;
        }
        bool is_terminal_punctuation(codepoint u) {
            return find_property_group(function_data, function_data_size, u).terminal_punctuation;
        }
        bool is_sentence_terminal(codepoint u) {
            return find_property_group(function_data, function_data_size, u).sterm;
        }
        bool is_diacritic(codepoint u) {
            return find_property_group(function_data, function_data_size, u).diacritic;
        }
        bool is_extender(codepoint u) {
            return find_property_group(function_data, function_data_size, u).extender;
        }
        bool is_soft_dotted(codepoint u) {
            return find_property_group(function_data, function_data_size, u).soft_dotted;
        }
        bool is_alphabetic(codepoint u) {
            return find_property_group(function_data, function_data_size, u).alphabetic;
        }
        bool is_other_alphabetic(codepoint u) {
            return find_property_group(function_data, function_data_size, u).other_alphabetic;
        }
        bool is_math(codepoint u) {
            return find_property_group(function_data, function_data_size, u).math;
        }
        bool is_other_math(codepoint u) {
            return find_property_group(function_data, function_data_size, u).other_math;
        }
        bool is_hex_digit(codepoint u) {
            return find_property_group(function_data, function_data_size, u).hex_digit;
        }
        bool is_ascii_hex_digit(codepoint u) {
            return find_property_group(function_data, function_data_size, u).ascii_hex_digit;
        }
        bool is_default_ignorable(codepoint u) {
            return find_property_group(function_data, function_data_size, u).default_ignorable;
        }
        bool is_other_default_ignorable(codepoint u) {
            return find_property_group(function_data, function_data_size, u).other_default_ignorable;
        }
        bool is_logical_order_exception(codepoint u) {
            return find_property_group(function_data, function_data_size, u).logical_order_exception;
        }
        bool is_white_space(codepoint u) {
            return find_property_group(function_data, function_data_size, u).white_space;
        }
        bool is_grapheme_base(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).grapheme_base;
        }
        //[[deprecated("since 5.0")]]
        bool is_grapheme_extend(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).grapheme_link;
        }
        bool is_other_grapheme_extend(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).other_grapheme_extend;
        }
        bool is_grapheme_link(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).grapheme_link;
        }
        grapheme_cluster_break get_grapheme_cluster_break(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).grapheme_cluster_break;
        }
        word_break get_word_break(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).word_break;
        }
        sentence_break get_sentence_break(codepoint u) {
            return find_property_group(boundary_data, boundary_data_size, u).sentence_break;
        }
        bool is_ideographic(codepoint u) {
            return find_property_group(ideograph_data, ideograph_data_size, u).ideographic;
        }
        bool is_unified_ideograph(codepoint u) {
            return find_property_group(ideograph_data, ideograph_data_size, u).unified_ideograph;
        }
        bool is_ids_binary_operator(codepoint u) {
            return find_property_group(ideograph_data, ideograph_data_size, u).ids_binary_operator;
        }
        bool is_ids_trinary_operator(codepoint u) {
            return find_property_group(ideograph_data, ideograph_data_size, u).ids_trinary_operator;
        }
        bool is_radical(codepoint u) {
            return find_property_group(ideograph_data, ideograph_data_size, u).radical;
        }
        bool is_deprecated(codepoint u) {
            return find_property_group(miscellaneous_data, miscellaneous_data_size, u).deprecated;
        }
        bool is_variant_selector(codepoint u) {
            return find_property_group(miscellaneous_data, miscellaneous_data_size, u).variant_selector;
        }
        bool is_noncharacter(codepoint u) {
            return find_property_group(miscellaneous_data, miscellaneous_data_size, u).noncharacter;
        }
    } // namespace ucd
} // namespace ogonek


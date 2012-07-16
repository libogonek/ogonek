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

// Unicode character database - data structures

#ifndef OGONEK_DETAIL_PROPERTIES_HPP
#define OGONEK_DETAIL_PROPERTIES_HPP

#include "../ucd.h++"

namespace ogonek {
    namespace ucd {
        template <typename T>
        struct simple_properties {
            codepoint start;
            T data;
        };
        using version_properties = simple_properties<version>;
        struct name_properties {
            codepoint start;
            bool variable;
            char const* name;
        };
        struct alias_properties {
            codepoint start;
            alias const* first;
            int count;
        };
        using block_properties = simple_properties<block>;
        using category_properties = simple_properties<category>;
        using combining_class_properties = simple_properties<int>;
        struct bidi_properties {
            codepoint start;
            bidi_category category;
            bool mirrored;
            codepoint mirrored_glyph;
            bool control;
        };
        struct decomposition_properties {
            codepoint start;
            decomposition_type type;
            codepoint const* mapping;
            bool composition_exclusion;
            bool full_composition_exclusion;
            yes_no_maybe nfc_quick_check;
            bool nfd_quick_check;
            yes_no_maybe nfkc_quick_check;
            bool nfkd_quick_check;
            bool expands_on_nfc;
            bool expands_on_nfd;
            bool expands_on_nfkc;
            bool expands_on_nfkd;
            codepoint const* fc_nfkc_closure;
        };
        struct numeric_properties {
            codepoint start;
            numeric_type type;
            double value;
        };
        struct joining_properties {
            codepoint start;
            joining_class class_;
            joining_group group;
            bool control;
        };
        using linebreak_properties = simple_properties<linebreak>;
        using east_asian_properties = simple_properties<east_asian_width>;
        struct case_properties {
            codepoint start;
            bool is_uppercase, is_lowercase, other_uppercase, other_lowercase;
            codepoint simple_uppercase, simple_lowercase, simple_titlecase;
            codepoint const* uppercase;
            codepoint const* lowercase;
            codepoint const* titlecase;
            codepoint simple_case_folding;
            codepoint const* case_folding;
            bool case_ignorable;
            bool cased;
            bool changes_when_casefolded, changes_when_casemapped, changes_when_lowercased,
                 changes_when_nfkc_casefolded, changes_when_titlecased, changes_when_uppercased;
            codepoint const* nfkc_casefold;
        };
        struct script_properties {
            codepoint start;
            ucd::script script;
            ucd::script const* first_script_extension;
            int script_extension_count;
        };
        using iso_comment_properties = simple_properties<codepoint const*>;
        struct hangul_properties {
            codepoint start;
            hangul_syllable_type syllable_type;
            char const jamo_short_name[4];
        };
        struct indic_properties {
            codepoint start;
            indic_syllable_category syllable_category;
            indic_matra_category matra_category;
        };
        struct identifier_properties {
            codepoint start;
            bool id_start, other_id_start, xid_start;
            bool id_continue, other_id_continue, xid_continue;
        };
        struct pattern_properties {
            codepoint start;
            bool syntax;
            bool white_space;
        };
        struct function_properties {
            codepoint start;
            bool dash, hyphen, quotation_mark, terminal_punctuation, sterm, diacritic,
                 extender, soft_dotted, alphabetic, other_alphabetic, math, other_math,
                 hex_digit, ascii_hex_digit, default_ignorable, other_default_ignorable,
                 logical_order_exception, white_space;
        };
        struct boundary_properties {
            codepoint start;
            bool grapheme_base, grapheme_extend, other_grapheme_extend, grapheme_link;
            ucd::grapheme_cluster_break grapheme_cluster_break;
            ucd::word_break word_break;
            ucd::sentence_break sentence_break;
        };
        struct ideograph_properties {
            codepoint start;
            bool ideographic;
            bool unified_ideograph;
            bool ids_binary_operator;
            bool ids_trinary_operator;
            bool radical;
        };
        struct miscellaneous_properties {
            codepoint start;
            bool deprecated;
            bool variant_selector;
            bool noncharacter;
        };
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_DETAIL_PROPERTIES_HPP


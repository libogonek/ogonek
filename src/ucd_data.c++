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

// Unicode character database - raw data

#include <ogonek/ucd.h++>
#include <ogonek/types.h++>

#include <cstddef>
#include <limits>

namespace ogonek {
    namespace ucd {
        namespace {
            using namespace ogonek::literal;
            version_properties const version_data_raw[] {
                #include "ucd/age.g.inl"
            };
            name_properties const name_data_raw[] {
                #include "ucd/name.g.inl"
            };
            name_properties const v1name_data_raw[] {
                #include "ucd/v1name.g.inl"
            };
            alias const aliases[] {
                #include "ucd/aliases.g.inl"
            };
            alias_properties const aliases_data_raw[] {
                #include "ucd/alias_map.g.inl"
            };
            block_properties const block_data_raw[] {
                #include "ucd/block.g.inl"
            };
            category_properties const category_data_raw[] {
                #include "ucd/category.g.inl"
            };
            combining_class_properties const combining_class_data_raw[] {
                #include "ucd/combining.g.inl"
            };
            bidi_properties const bidi_data_raw[] {
                #include "ucd/bidi.g.inl"
            };
            composition_properties const composition_data_raw[] {
                #include "ucd/composition.g.inl"
            };
            decomposition_properties const decomposition_data_raw[] {
                #include "ucd/decomposition.g.inl"
            };
            numeric_properties const numeric_data_raw[] {
                #include "ucd/numeric.g.inl"
            };
            joining_properties const joining_data_raw[] {
                #include "ucd/joining.g.inl"
            };
            linebreak_properties const linebreak_data_raw[] {
                #include "ucd/linebreak.g.inl"
            };
            east_asian_properties const east_asian_data_raw[] {
                #include "ucd/east_asian.g.inl"
            };
            case_properties const case_data_raw[] {
                #include "ucd/case.g.inl"
            };
            script const script_ext[] {
                #include "ucd/script_ext.g.inl"
            };
            script_properties const script_data_raw[] {
                #include "ucd/script.g.inl"
            };
            iso_comment_properties const iso_comment_data_raw[] {
                #include "ucd/iso_comment.g.inl"
            };
            hangul_properties const hangul_data_raw[] {
                #include "ucd/hangul.g.inl"
            };
            indic_properties const indic_data_raw[] {
                #include "ucd/indic.g.inl"
            };
            identifier_properties const identifier_data_raw[] {
                #include "ucd/identifier.g.inl"
            };
            pattern_properties const pattern_data_raw[] {
                #include "ucd/pattern.g.inl"
            };
            function_properties const function_data_raw[] {
                #include "ucd/function.g.inl"
            };
            boundary_properties const boundary_data_raw[] {
                #include "ucd/boundary.g.inl"
            };
            ideograph_properties const ideograph_data_raw[] {
                #include "ucd/ideograph.g.inl"
            };
            miscellaneous_properties const miscellaneous_data_raw[] {
                #include "ucd/misc.g.inl"
            };

            template <typename T, std::size_t N>
            constexpr std::size_t size(T(&)[N]) { return N; }
        } // namespace
        version_properties const* version_data = version_data_raw;
        std::size_t version_data_size = size(version_data_raw);
        name_properties const* name_data = name_data_raw;
        std::size_t name_data_size = size(name_data_raw);
        name_properties const* v1name_data = v1name_data_raw;
        std::size_t v1name_data_size = size(v1name_data_raw);
        alias_properties const* aliases_data = aliases_data_raw;
        std::size_t aliases_data_size = size(aliases_data_raw);
        block_properties const* block_data = block_data_raw;
        std::size_t block_data_size = size(block_data_raw);
        category_properties const* category_data = category_data_raw;
        std::size_t category_data_size = size(category_data_raw);
        combining_class_properties const* combining_class_data = combining_class_data_raw;
        std::size_t combining_class_data_size = size(combining_class_data_raw);
        bidi_properties const* bidi_data = bidi_data_raw;
        std::size_t bidi_data_size = size(bidi_data_raw);
        composition_properties const* composition_data = composition_data_raw;
        std::size_t composition_data_size = size(composition_data_raw);
        decomposition_properties const* decomposition_data = decomposition_data_raw;
        std::size_t decomposition_data_size = size(decomposition_data_raw);
        numeric_properties const* numeric_data = numeric_data_raw;
        std::size_t numeric_data_size = size(numeric_data_raw);
        joining_properties const* joining_data = joining_data_raw;
        std::size_t joining_data_size = size(joining_data_raw);
        linebreak_properties const* linebreak_data = linebreak_data_raw;
        std::size_t linebreak_data_size = size(linebreak_data_raw);
        east_asian_properties const* east_asian_data = east_asian_data_raw;
        std::size_t east_asian_data_size = size(east_asian_data_raw);
        case_properties const* case_data = case_data_raw;
        std::size_t case_data_size = size(case_data_raw);
        script_properties const* script_data = script_data_raw;
        std::size_t script_data_size = size(script_data_raw);
        iso_comment_properties const* iso_comment_data = iso_comment_data_raw;
        std::size_t iso_comment_data_size = size(iso_comment_data_raw);
        hangul_properties const* hangul_data = hangul_data_raw;
        std::size_t hangul_data_size = size(hangul_data_raw);
        indic_properties const* indic_data = indic_data_raw;
        std::size_t indic_data_size = size(indic_data_raw);
        identifier_properties const* identifier_data = identifier_data_raw;
        std::size_t identifier_data_size = size(identifier_data_raw);
        pattern_properties const* pattern_data = pattern_data_raw;
        std::size_t pattern_data_size = size(pattern_data_raw);
        function_properties const* function_data = function_data_raw;
        std::size_t function_data_size = size(function_data_raw);
        boundary_properties const* boundary_data = boundary_data_raw;
        std::size_t boundary_data_size = size(boundary_data_raw);
        ideograph_properties const* ideograph_data = ideograph_data_raw;
        std::size_t ideograph_data_size = size(ideograph_data_raw);
        miscellaneous_properties const* miscellaneous_data = miscellaneous_data_raw;
        std::size_t miscellaneous_data_size = size(miscellaneous_data_raw);
    } // namespace ucd
} // namespace ogonek



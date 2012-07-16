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

// Unicode character database

#include <ogonek/ucd.h++>
#include <ogonek/detail/properties.h++>
#include <ogonek/types.h++>

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <limits>

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
    } // namespace ucd
} // namespace ogonek


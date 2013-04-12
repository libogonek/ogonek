// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Grapheme iterator

#ifndef OGONEK_DETAIL_GRAPHEME_ITERATOR_HPP
#define OGONEK_DETAIL_GRAPHEME_ITERATOR_HPP

#include <ogonek/types.h++>
#include <ogonek/data/ucd.h++>

#include <wheels/enums.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace ogonek {
    namespace detail {
        using gb = ucd::grapheme_cluster_break;
        struct grapheme_rule {
            gb before;
            bool is_break;
            gb after;

            bool matches(code_point before, code_point after) const;
        };
    } // namespace detail
} // namespace ogonek

namespace wheels {
    template <>
    struct is_flags<ogonek::detail::gb> : std::true_type {};
} // namespace wheels

namespace ogonek {
    namespace detail {
        constexpr gb gb_any = static_cast<gb>(0xFFFFFFFFu);
        constexpr grapheme_rule operator*(gb l, gb r) { return { l, false, r }; }
        constexpr grapheme_rule operator/(gb l, gb r) { return { l, true, r }; }

        // TODO: switch to a pair table instead
        constexpr grapheme_rule grapheme_rules[] = {
            // Break at the start and end of text.
            // * Handled specially
            // Do not break between a CR and LF. Otherwise, break before and after controls.
            /* GB3. */                     gb::CR * gb::LF,
            /* GB4. */ (gb::CN | gb::CR | gb::LF) / gb_any,
            /* GB5. */                     gb_any / (gb::CN | gb::CR | gb::LF),
            // Do not break Hangul syllable sequences.
            /* GB6. */                      gb::L * (gb::L | gb::V | gb::LV | gb::LVT),
            /* GB7. */           (gb::LV | gb::V) * (gb::V | gb::T),
            /* GB8. */          (gb::LVT | gb::T) * gb::T,
            // Do not break between regional indicator symbols.
            /* GB8a. */                    gb::RI * gb::RI,
            // Do not break before extending characters.
            /* GB9. */                     gb_any * gb::EX,
            // Do not break before SpacingMarks, or after Prepend characters.
            /* GB9a. */                    gb_any * gb::SM,
            /* GB9b. */                    gb::PP * gb_any,
            // Otherwise, break everywhere.
            /* GB10. */                    gb_any / gb_any,
        };
        inline bool grapheme_rule::matches(code_point before, code_point after) const {
            const gb none = static_cast<gb>(0);
            return (ucd::get_grapheme_cluster_break(before) & this->before) != none
                && (ucd::get_grapheme_cluster_break(after) & this->after) != none;
        }
        inline bool is_grapheme_boundary(code_point before, code_point after) {
            return std::find_if(std::begin(grapheme_rules), std::end(grapheme_rules),
                                [before, after](grapheme_rule const& rule) {
                                    return rule.matches(before, after);
                                })
                   ->is_break;
        }

        template <typename CodePointIterator>
        struct grapheme_iterator
        : boost::iterator_facade<
            grapheme_iterator<CodePointIterator>,
            boost::iterator_range<CodePointIterator>,
            std::forward_iterator_tag, // TODO
            boost::iterator_range<CodePointIterator>>
        {
        public:
            grapheme_iterator(CodePointIterator first, CodePointIterator last)
            : first(first), last(last) {}

        private:
            friend class boost::iterator_core_access;

            boost::iterator_range<CodePointIterator> dereference() const {
                auto begin = first;
                auto it = first;
                auto before = *it++;
                do {
                    auto after = *it;
                    if(detail::is_grapheme_boundary(before, after)) break;
                    ++it;
                    if(it == last) break;
                    before = after;
                } while(true);
                return { begin, it };
            }
            void increment() {
                first = dereference().end();
            }
            bool equal(grapheme_iterator const& that) const {
                return first == that.first;
            }

            CodePointIterator first;
            CodePointIterator last;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_GRAPHEME_ITERATOR_HPP

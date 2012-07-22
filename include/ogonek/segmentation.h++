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

// Unicode text segmentation algorithms (UAX #29)

#ifndef OGONEK_SEGMENTATION_HPP
#define OGONEK_SEGMENTATION_HPP

#include "types.h++"
#include "ucd.h++"

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits>

namespace ogonek {
    namespace detail {
        using gcb = ucd::grapheme_cluster_break;
        struct grapheme_cluster_rule {
            gcb before;
            bool is_break;
            gcb after;

            bool matches(codepoint before, codepoint after) const;
        };
        constexpr gcb any = static_cast<gcb>(0xFFFFFFFFu);
        constexpr gcb operator|(gcb l, gcb r) {
            using underlying = std::underlying_type<gcb>::type;
            return static_cast<gcb>(static_cast<underlying>(l) | static_cast<underlying>(r));
        }
        constexpr gcb operator&(gcb l, gcb r) {
            using underlying = std::underlying_type<gcb>::type;
            return static_cast<gcb>(static_cast<underlying>(l) & static_cast<underlying>(r));
        }
        constexpr grapheme_cluster_rule operator*(gcb l, gcb r) { return { l, false, r }; }
        constexpr grapheme_cluster_rule operator/(gcb l, gcb r) { return { l, true, r }; }

        // TODO: switch to a pair table instead
        constexpr grapheme_cluster_rule grapheme_cluster_rules[] = {
            // Break at the start and end of text.
            // * Handled specially
            // Do not break between a CR and LF. Otherwise, break before and after controls.
            /* GB3. */                       gcb::CR * gcb::LF,
            /* GB4. */ (gcb::CN | gcb::CR | gcb::LF) / any,
            /* GB5. */                           any / (gcb::CN | gcb::CR | gcb::LF),
            // Do not break Hangul syllable sequences.
            /* GB6. */                        gcb::L * (gcb::L | gcb::V | gcb::LV | gcb::LVT),
            /* GB7. */            (gcb::LV | gcb::V) * (gcb::V | gcb::T),
            /* GB8. */           (gcb::LVT | gcb::T) * gcb::T,
            // Do not break before extending characters.
            /* GB9. */                           any * gcb::EX,
            // Do not break before SpacingMarks, or after Prepend characters.
            /* GB9a. */                          any * gcb::SM,
            /* GB9b. */                      gcb::PP * any,
            // Otherwise, break everywhere.
            /* GB10. */                          any / any,
        };
        inline bool grapheme_cluster_rule::matches(codepoint before, codepoint after) const {
            const gcb none = static_cast<gcb>(0);
            return (ucd::get_grapheme_cluster_break(before) & this->before) != none
                && (ucd::get_grapheme_cluster_break(after) & this->after) != none;
        }
        struct grapheme_cluster_boundary {
            bool operator()(codepoint before, codepoint after) const {
                using namespace std::placeholders;
                return std::find_if(std::begin(detail::grapheme_cluster_rules), std::end(detail::grapheme_cluster_rules),
                                    std::bind(&grapheme_cluster_rule::matches, _1, before, after))
                       ->is_break;
            }
        };
    } // namespace detail

    template <typename BoundaryCondition, typename CodepointIterator>
    struct break_iterator
    : boost::iterator_facade<
        break_iterator<BoundaryCondition, CodepointIterator>,
        boost::iterator_range<CodepointIterator>,
        typename std::iterator_traits<CodepointIterator>::iterator_category,
        boost::iterator_range<CodepointIterator>>
    {
    public:
        break_iterator(CodepointIterator first, CodepointIterator last)
        : first(first), last(last) {}

    private:
        friend class boost::iterator_core_access;

        boost::iterator_range<CodepointIterator> dereference() const {
            auto begin = first;
            auto it = first;
            auto before = *it++;
            do {
                auto after = *it;
                if(BoundaryCondition{}(before, after)) break;
                ++it;
                if(it == last) break;
                before = after;
            } while(true);
            return boost::iterator_range<CodepointIterator> { begin, it };
        }
        void increment() {
            first = dereference().end();
        }
        bool equal(break_iterator const& that) const {
            return first == that.first;
        }

        CodepointIterator first;
        CodepointIterator last;
    };
    template <typename CodepointIterator>
    using grapheme_cluster_iterator = break_iterator<detail::grapheme_cluster_boundary, CodepointIterator>;

    template <typename SinglePassRange>
    boost::iterator_range<grapheme_cluster_iterator<typename boost::range_const_iterator<SinglePassRange>::type>> grapheme_clusters(SinglePassRange const& range) {
        using iterator = grapheme_cluster_iterator<typename boost::range_const_iterator<SinglePassRange>::type>;
        return { iterator { range.begin(), range.end() }, iterator { range.end(), range.end() } };
    }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP


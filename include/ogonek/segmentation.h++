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
        inline grapheme_cluster_rule const& find_applicable_rule(codepoint before, codepoint after) {
            using namespace std::placeholders;
            return *std::find_if(std::begin(detail::grapheme_cluster_rules), std::end(detail::grapheme_cluster_rules),
                                 std::bind(&grapheme_cluster_rule::matches, _1, before, after));
        }

        inline bool grapheme_cluster_rule::matches(codepoint before, codepoint after) const {
            const gcb none = static_cast<gcb>(0);
            return (ucd::get_grapheme_cluster_break(before) & this->before) != none
                && (ucd::get_grapheme_cluster_break(after) & this->after) != none;
        }
    } // namespace detail

    template <typename Iterator>
    struct grapheme_cluster_iterator
    : boost::iterator_facade<
        grapheme_cluster_iterator<Iterator>,
        boost::iterator_range<Iterator>,
        std::forward_iterator_tag,
        boost::iterator_range<Iterator>>
    {
    public:
        grapheme_cluster_iterator(Iterator first, Iterator last)
        : first(first), last(last) {}

    private:
        friend class boost::iterator_core_access;
        boost::iterator_range<Iterator> dereference() const {
            auto begin = first;
            auto it = first;
            auto before = *it++;
            do {
                auto after = *it;
                if(detail::find_applicable_rule(before, after).is_break) break;
                ++it;
                if(it == last) break;
                before = after;
            } while(true);
            return boost::iterator_range<Iterator> { begin, it };
        }
        void increment() {
            first = dereference().end();
        }
        bool equal(grapheme_cluster_iterator const& that) const {
            return first == that.first;
        }

        Iterator first;
        Iterator last;
    };
    template <typename SinglePassRange>
    boost::iterator_range<grapheme_cluster_iterator<typename boost::range_const_iterator<SinglePassRange>::type>> grapheme_clusters(SinglePassRange const& range) {
        using iterator = grapheme_cluster_iterator<typename boost::range_const_iterator<SinglePassRange>::type>;
        return { iterator { range.begin(), range.end() }, iterator { range.end(), range.end() } };
    }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_HPP


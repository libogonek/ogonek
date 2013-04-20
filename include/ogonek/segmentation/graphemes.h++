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

// Grapheme segmentation

#ifndef OGONEK_SEGMENTATION_GRAPHEMES_HPP
#define OGONEK_SEGMENTATION_GRAPHEMES_HPP

#include <ogonek/error/assume_valid.h++>
#include <ogonek/segmentation/detail/grapheme_iterator.h++> // TODO uncrapify this one

#include <taussig/primitives.h++>

#include <wheels/meta.h++>

#include <utility>

namespace ogonek {
    namespace detail {
        template <typename Sequence>
        struct grapheme_sequence_impl : detail::ogonek_sequence<> {
        public:
            template <typename SequenceF,
                      wheels::DisableIf<wheels::is_related<grapheme_sequence_impl<Sequence>, SequenceF>>...>
            explicit grapheme_sequence_impl(SequenceF&& s) : s(std::forward<SequenceF>(s)) {}

            using value_type = Sequence;
            using reference = value_type;

            bool empty() const { return seq::empty(s); }
            reference front() const {
                return seq::before(s, skip_grapheme());
            }
            void pop_front() {
                s = skip_grapheme();
            }
            grapheme_sequence_impl save() const { return *this; }
            grapheme_sequence_impl before(grapheme_sequence_impl const& that) const { return { s.before(that.s) }; }

        private:
            Sequence s;

            Sequence skip_grapheme() const {
                auto remaining = s;
                auto before = seq::front(remaining);
                seq::pop_front(remaining);
                do {
                    auto after = seq::front(remaining);
                if(detail::is_grapheme_boundary(before, after)) break;
                    seq::pop_front(remaining);
                    before = after;
                } while(!seq::empty(remaining));
                return remaining;
            }
        };
        static_assert(seq::is_true_sequence<grapheme_sequence_impl<std::pair<char const*, char const*>>>(), "");
    } // namespace detail

    template <typename Sequence>
    using grapheme_sequence = detail::grapheme_sequence_impl<wheels::Decay<Sequence>>;

    template <typename Sequence,
              wheels::EnableIf<detail::is_well_formed<Sequence>>...>
    grapheme_sequence<Sequence> graphemes_ex(Sequence&& s) {
        return grapheme_sequence<Sequence>(std::forward<Sequence>(s));
    }
} // namespace ogonek

// ---- CRAP BELOW THIS LINE
#include <ogonek/detail/ranges.h++>

#include <boost/range/iterator_range.hpp>

namespace ogonek {
    template <typename UnicodeSequence, // TODO use UnicodeSequenceIterator
              typename Iterator = detail::grapheme_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> graphemes(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, assume_valid));
    }
} // namespace ogonek

#endif // OGONEK_SEGMENTATION_GRAPHEMES_HPP

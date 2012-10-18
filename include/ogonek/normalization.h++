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

// Unicode normalization (UAX #15)

#ifndef OGONEK_NORMALIZATION_HPP
#define OGONEK_NORMALIZATION_HPP

#include "ucd.h++"

namespace ogonek {
    namespace detail {
        template <typename Iterator>
        struct decomposing_iterator
        : boost::iterator_facade<
            decomposing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
        public:
            decomposing_iterator(Iterator first)
            : first(std::move(first)) {
                increment();
            }

            codepoint dereference() const {
                return current[position];
            }
            bool equal(decomposing_iterator const& that) const {
                return first == that.first && position == that.position;
            }
            void increment() {
                ++position;
                if(position == current.size()) {
                    auto u = *first++;
                    auto type = ucd::get_decomposition_type(u);
                    if(type == ucd::decomposition_type::can) {
                        current = ucd::get_decomposition_mapping(u);
                    } else {
                        current = { u };
                    }
                    position = 0;
                }
            }

        private:
            Iterator first;
            unsigned position = -1;
            std::vector<codepoint> current;
        };

        template <typename Iterator>
        class composing_iterator;
    } // namespace detail

    template <typename SinglePassRange,
              typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
              typename DecomposingIterator = detail::decomposing_iterator<Iterator>>
    boost::iterator_range<DecomposingIterator> decompose(SinglePassRange const& r) {
        return boost::make_iterator_range(
                DecomposingIterator { boost::begin(r) },
                DecomposingIterator { boost::end(r) });
    }

    class nfc {};
    class nfd {};
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP


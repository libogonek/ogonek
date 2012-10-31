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
        struct ordered_decomposing_iterator;

        template <typename Iterator>
        struct decomposing_iterator
        : boost::iterator_facade<
            decomposing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
        public:
            decomposing_iterator(Iterator first, Iterator last)
            : first(std::move(first)), last(std::move(last)) {
                if(this->first != this->last) {
                    increment();
                }
            }

            codepoint dereference() const {
                return current[position];
            }
            bool equal(decomposing_iterator const& that) const {
                return (first == that.first && position == that.position)
                    || (exhausted() && that.exhausted());
            }
            void increment() {
                ++position;
                if(unsigned(position) < current.size()) return;

                if(first == last) {
                    current = {};
                    position = -1;
                    return;
                }
                auto u = *first++;
                auto type = ucd::get_decomposition_type(u);
                if(type == ucd::decomposition_type::can) {
                    current = ucd::get_decomposition_mapping(u);
                } else {
                    current = { u };
                }
                position = 0;
            }

        private:
            friend class ordered_decomposing_iterator<Iterator>;

            bool exhausted() const {
                return position == -1;
            }

            Iterator first, last;
            int position = -1;
            std::vector<codepoint> current;
        };

        template <typename Iterator>
        struct ordered_decomposing_iterator
        : boost::iterator_facade<
            ordered_decomposing_iterator<Iterator>,
            codepoint,
            std::input_iterator_tag, // TODO
            codepoint
          > {
        public:
            ordered_decomposing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)) {}

            codepoint dereference() const {
                return current[position];
            }
            bool equal(ordered_decomposing_iterator const& that) const {
                return it.equal(that.it) && position == that.position;
            }
            void increment() {
                ++position;
                if(position < current.size()) return;
                if(it.exhausted()) {
                    position = -1u;
                    return;
                }

                if(ucd::get_combining_class(*it) == 0) {
                    current = { *it++ };
                } else {
                    current.clear();
                    while(!it.exhausted() && ucd::get_combining_class(*it) != 0) {
                        current.push_back(*it++);
                    }
                    std::sort(current.begin(), current.end(),
                              [](codepoint a, codepoint b) {
                                  return ucd::get_combining_class(a) < ucd::get_combining_class(b);
                              });
                }
                position = 0;
            }

        private:
            decomposing_iterator<Iterator> it;
            unsigned position = -1u;
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
                DecomposingIterator { boost::begin(r), boost::end(r) },
                DecomposingIterator { boost::end(r), boost::end(r) });
    }

    template <typename SinglePassRange,
              typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
              typename OrderedDecomposingIterator = detail::ordered_decomposing_iterator<Iterator>>
    boost::iterator_range<OrderedDecomposingIterator> decompose_ordered(SinglePassRange const& r) {
        return boost::make_iterator_range(
                OrderedDecomposingIterator { boost::begin(r), boost::end(r) },
                OrderedDecomposingIterator { boost::end(r), boost::end(r) });
    }

    class nfc {};
    class nfd {};
} // namespace ogonek

#endif // OGONEK_NORMALIZATION_HPP


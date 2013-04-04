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

// Decomposing iterator

#ifndef OGONEK_DETAIL_DECOMPOSING_ITERATOR_HPP
#define OGONEK_DETAIL_DECOMPOSING_ITERATOR_HPP

#include <ogonek/data/ucd.h++>
#include <ogonek/types.h++>
#include <ogonek/detail/small_vector.h++>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>
#include <utility>
#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        using vector_type = detail::small_vector<T, N>; 

        template <typename Iterator, bool Compatibility = false>
        struct ordered_decomposing_iterator;

        template <typename Iterator, bool Compatibility = false>
        struct decomposing_iterator
        : boost::iterator_facade<
            decomposing_iterator<Iterator, Compatibility>,
            code_point,
            std::input_iterator_tag, // TODO
            code_point
          > {
        public:
            decomposing_iterator(Iterator first, Iterator last)
            : first(std::move(first)), last(std::move(last)) {
                if(this->first != this->last) {
                    increment();
                }
            }

            code_point dereference() const {
                return current[position];
            }
            bool equal(decomposing_iterator const& that) const {
                return (first == that.first && position == that.position)
                    || (exhausted() && that.exhausted());
            }
            void increment() {
                ++position;
                if(static_cast<unsigned>(position) < current.size()) return;

                if(first == last) {
                    current = {};
                    position = depleted;
                    return;
                }
                auto u = *first++;
                if(Compatibility) {
                    current = ucd::get_compatibility_decomposition_mapping(u);
                } else if(ucd::get_decomposition_type(u) == ucd::decomposition_type::can) {
                    current = ucd::get_canonical_decomposition_mapping(u);
                } else {
                    current = { u };
                }
                position = 0;
            }

        private:
            friend class ordered_decomposing_iterator<Iterator, Compatibility>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            Iterator first, last;
            int position = depleted;
            vector_type<code_point, 4> current;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_DECOMPOSING_ITERATOR_HPP


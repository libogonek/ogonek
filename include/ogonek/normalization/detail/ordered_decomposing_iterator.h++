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

// Ordered decomposing iterator

#ifndef OGONEK_DETAIL_ORDERED_DECOMPOSING_ITERATOR_HPP
#define OGONEK_DETAIL_ORDERED_DECOMPOSING_ITERATOR_HPP

#include <ogonek/character/ucd.h++>
#include <ogonek/types.h++>
#include <ogonek/normalization/detail/decomposing_iterator.h++>

#include <boost/iterator/iterator_facade.hpp>

#include <algorithm>
#include <iterator>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename Iterator, bool Compatibility = false>
        struct composing_iterator;

        template <typename Iterator, bool Compatibility>
        struct ordered_decomposing_iterator
        : boost::iterator_facade<
            ordered_decomposing_iterator<Iterator, Compatibility>,
            code_point,
            std::forward_iterator_tag, // TODO
            code_point
          > {
        public:
            ordered_decomposing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)) {
                if(!it.exhausted()) {
                    increment();
                }
            }

            code_point dereference() const {
                return current[position];
            }
            bool equal(ordered_decomposing_iterator const& that) const {
                return it.equal(that.it) && position == that.position;
            }
            void increment() {
                ++position;
                if(static_cast<unsigned>(position) < current.size()) return;
                if(it.exhausted()) {
                    current = {};
                    position = depleted;
                    return;
                }

                current.clear();
                if(ucd::get_combining_class(*it) == 0) {
                    current = it.current;
                    std::advance(it, current.size());
                }
                while(!it.exhausted() && ucd::get_combining_class(*it) != 0) {
                    current.push_back(*it++);
                }
                auto is_starter = [](code_point u) { return ucd::get_combining_class(u) == 0; };
                auto by_combining_class = [](code_point a, code_point b) {
                    return ucd::get_combining_class(a) < ucd::get_combining_class(b);
                };
                auto l = current.begin();
                for(auto r = l; r != current.end(); l = r) {
                    r = std::find_if(r+1, current.end(), is_starter);
                    std::sort(l, r, by_combining_class);
                }
                position = 0;
            }

        private:
            friend class composing_iterator<Iterator, Compatibility>;

            static constexpr int depleted = -1;

            bool exhausted() const {
                return position == depleted;
            }

            decomposing_iterator<Iterator, Compatibility> it;
            int position = depleted;
            vector_type<code_point, 4> current;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_ORDERED_DECOMPOSING_ITERATOR_HPP

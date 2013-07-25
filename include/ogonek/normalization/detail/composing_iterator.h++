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

// Composing iterators

#ifndef OGONEK_DETAIL_COMPOSING_ITERATOR_HPP
#define OGONEK_DETAIL_COMPOSING_ITERATOR_HPP

#include <ogonek/character/ucd.h++>
#include <ogonek/types.h++>
#include <ogonek/normalization/detail/ordered_decomposing_iterator.h++>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename Iterator, bool Compatibility>
        struct composing_iterator
        : boost::iterator_facade<
            composing_iterator<Iterator, Compatibility>,
            code_point,
            std::forward_iterator_tag, // TODO
            code_point
          > {
            composing_iterator(Iterator first, Iterator last)
            : it(std::move(first), std::move(last)), exhausted(it.exhausted()) {
                if(!exhausted) {
                    increment();
                }
            }

            code_point dereference() const {
                return current;
            }
            bool equal(composing_iterator const& that) const {
                return it.equal(that.it) && exhausted == that.exhausted;
            }
            void increment() {
                if(it.exhausted()) {
                    exhausted = true;
                    return;
                }

                if(it.position == 0) {
                    compose(it.current);
                }
                current = *it++;
            }

        private:
            static void compose(vector_type<code_point, 4>& sequence) {
                auto is_blocked = [](code_point u, int last_ccc) {
                    return last_ccc != -1 && (last_ccc == 0 || last_ccc >= ucd::get_combining_class(u));
                };
                for(auto l = sequence.begin(); l != sequence.end(); ++l) {
                    if(ucd::is_excluded_from_composition(*l) || !ucd::can_compose(*l)) continue;
                    auto last_ccc = -1;
                    for(auto r = std::next(l); r != sequence.end();) {
                        if(!is_blocked(*r, last_ccc) && ucd::can_compose(*l, *r)) {
                            *l = ucd::compose(*l, *r);
                            r = sequence.erase(r);
                        } else {
                            last_ccc = ucd::get_combining_class(*r);
                            ++r;
                        }
                    }
                }
            }

            ordered_decomposing_iterator<Iterator, Compatibility> it;
            bool exhausted;
            code_point current;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_COMPOSING_ITERATOR_HPP

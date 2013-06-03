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

// Decomposing sequence

#ifndef OGONEK_DETAIL_DECOMPOSING_SEQUENCE_HPP
#define OGONEK_DETAIL_DECOMPOSING_SEQUENCE_HPP

#include <ogonek/types.h++>
#include <ogonek/character/ucd.h++>
#include <ogonek/detail/container/small_vector.h++>

#include <taussig/primitives.h++>

#include <utility>

namespace ogonek {
    namespace detail {
        /*
        template <typename Iterator, bool Compatibility = false>
        struct ordered_decomposing_iterator;
        */

        template <typename Sequence, bool Compatibility = false>
        struct decomposing_sequence : ogonek_sequence<detail::well_formed> {
        public:
            template <typename SequenceF>
            decomposing_sequence(SequenceF&& source) : source(std::forward<SequenceF>(source)) {
                decompose_next();
            }

            using value_type = detail::small_vector<code_point, 4>;
            bool empty() const { return depleted; }
            value_type front() const { return current; }
            void pop_front() { decompose_next(); }
            decomposing_sequence before(decomposing_sequence const& that) const {
                return { source.before(that.source), depleted, current };
            }

        private:
            decomposing_sequence(Sequence const& source, bool depleted, value_type const& current)
            : source(source), depleted(depleted), current(current) {}

            void decompose_next() {
                if(seq::empty(source)) {
                    depleted = true;
                } else {
                    auto&& u = seq::front(s);
                    if(Compatibility) {
                        current = ucd::get_compatibility_decomposition_mapping(u);
                    } else if(ucd::get_decomposition_type(u) == ucd::decomposition_type::can) {
                        current = ucd::get_canonical_decomposition_mapping(u);
                    } else {
                        current = { u };
                    }
                    seq::pop_front(s);
                }
            }

            Sequence source;
            bool depleted = false;
            value_type current;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_DECOMPOSING_SEQUENCE_HPP

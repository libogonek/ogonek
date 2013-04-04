// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Normalization-based equivalence relations

#ifndef OGONEK_DETAIL_NORMALIZED_EQUIVALENCE_HPP
#define OGONEK_DETAIL_NORMALIZED_EQUIVALENCE_HPP

#include <ogonek/normalization/normalize.h++>
#include <ogonek/detail/boost_hash_unicode.h++>

#include <boost/range/algorithm/equal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/functional/hash.hpp>

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename NormalForm>
        struct normalized_equivalence {
            template <typename UnicodeSequence1, typename UnicodeSequence2>
            bool operator()(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) const {
                return boost::equal(normalize<NormalForm>(sequence1), normalize<NormalForm>(sequence2));
            }
        };

        template <typename NormalForm, typename UnicodeSequence1, typename UnicodeSequence2>
        bool normalized_equivalent(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) {
            return normalized_equivalence<NormalForm>{}(sequence1, sequence2);
        }

        template <typename NormalForm>
        struct normalized_hash {
        public:
            template <typename UnicodeSequence>
            std::size_t operator()(UnicodeSequence const& sequence) const {
                return hash_normalized(normalize<NormalForm>(sequence));
            }
        private:
            template <typename NormalizedSequence>
            std::size_t hash_normalized(NormalizedSequence const& sequence) const {
                return boost::hash_range(boost::begin(sequence), boost::end(sequence));
            }
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_NORMALIZED_EQUIVALENCE_HPP

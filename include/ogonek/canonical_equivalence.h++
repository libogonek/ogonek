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

// Canonical equivalence relation

#ifndef OGONEK_CANONICAL_EQUIVALENCE_HPP
#define OGONEK_CANONICAL_EQUIVALENCE_HPP

#include <ogonek/nfd.h++>
#include <ogonek/detail/normalized_equivalence.h++>

namespace ogonek {
    using canonical_equivalence = detail::normalized_equivalence<nfd>;

    template <typename UnicodeSequence1, typename UnicodeSequence2>
    bool canonically_equivalent(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) {
        return detail::normalized_equivalent<nfd>(sequence1, sequence2);
    }

    using canonical_hash = detail::normalized_hash<nfd>;
} // namespace ogonek

#endif // OGONEK_CANONICAL_EQUIVALENCE_HPP

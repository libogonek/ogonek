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

// Compatibility equivalence relation

#ifndef OGONEK_COMPATIBILITY_EQUIVALENCE_HPP
#define OGONEK_COMPATIBILITY_EQUIVALENCE_HPP

#include <ogonek/nfkd.h++>
#include <ogonek/detail/normalized_equivalence.h++>

namespace ogonek {
    using compatibility_equivalence = detail::normalized_equivalence<nfkd>;

    template <typename UnicodeSequence1, typename UnicodeSequence2>
    bool compatibility_equivalent(UnicodeSequence1 const& sequence1, UnicodeSequence2 const& sequence2) {
        return detail::normalized_equivalent<nfkd>(sequence1, sequence2);
    }

    using compatibility_hash = detail::normalized_hash<nfkd>;
} // namespace ogonek

#endif // OGONEK_COMPATIBILITY_EQUIVALENCE_HPP

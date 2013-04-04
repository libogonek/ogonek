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

// text equivalence operators

#ifndef OGONEK_TEXT_EQUIVALENCE_HPP
#define OGONEK_TEXT_EQUIVALENCE_HPP

#include <ogonek/text/text_core.h++>
#include <ogonek/normalization/canonical_equivalence.h++>

#include <functional>

namespace ogonek {
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator==(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator!=(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return !(lhs == rhs);
    }
} // namespace ogonek

namespace std {
    template <typename EncodingForm, typename Container>
    struct hash< ::ogonek::text<EncodingForm, Container>> : ::ogonek::canonical_hash {};
} //namespace std

#endif // OGONEK_TEXT_EQUIVALENCE_HPP

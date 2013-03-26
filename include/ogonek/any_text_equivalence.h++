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

// any_text equivalence operators

#ifndef OGONEK_ANY_TEXT_EQUIVALENCE_HPP
#define OGONEK_ANY_TEXT_EQUIVALENCE_HPP

#include <ogonek/any_text.h++>
#include <ogonek/text_core.h++>
#include <ogonek/canonical_equivalence.h++>

#include <functional>

namespace ogonek {
    template <typename Encoding, typename Container>
    bool operator==(any_text const& lhs, text<Encoding, Container> const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding, typename Container>
    bool operator!=(any_text const& lhs, text<Encoding, Container> const& rhs) {
        return !(lhs == rhs);
    }
    template <typename Encoding, typename Container>
    bool operator==(text<Encoding, Container> const& lhs, any_text const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding, typename Container>
    bool operator!=(text<Encoding, Container> const& lhs, any_text const& rhs) {
        return !(lhs == rhs);
    }
    inline bool operator==(any_text const& lhs, any_text const& rhs) {
        return canonically_equivalent<any_text, any_text>(lhs, rhs);
    }
    inline bool operator!=(any_text const& lhs, any_text const& rhs) {
        return !(lhs == rhs);
    }
} // namespace ogonek

namespace std {
    template <>
    struct hash< ::ogonek::any_text> : ::ogonek::canonical_hash {};
} //namespace std

#endif // OGONEK_TEXT_EQUIVALENCE_HPP

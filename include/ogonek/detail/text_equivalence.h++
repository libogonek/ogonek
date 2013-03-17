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

// Unicode text string - equivalence operators

#ifndef OGONEK_DETAIL_TEXT_EQUIVALENCE_HPP
#define OGONEK_DETAIL_TEXT_EQUIVALENCE_HPP

#include <ogonek/detail/text_core.h++>
#include <ogonek/normalization.h++>

namespace ogonek {
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator==(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return canonically_equivalent(lhs, rhs);
    }
    template <typename Encoding1, typename Container1, typename Encoding2, typename Container2>
    bool operator!=(text<Encoding1, Container1> const& lhs, text<Encoding2, Container2> const& rhs) {
        return !(lhs == rhs);
    }
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
    template <typename EncodingForm, typename Container>
    struct hash< ::ogonek::text<EncodingForm, Container>> : ::ogonek::canonical_hash {};
    template <>
    struct hash< ::ogonek::any_text> : ::ogonek::canonical_hash {};
} //namespace std

#endif // OGONEK_DETAIL_TEXT_CORE_HPP

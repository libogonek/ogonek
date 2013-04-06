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

// Sequence concept tools

#ifndef OGONEK_DETAIL_SEQUENCE_HPP
#define OGONEK_DETAIL_SEQUENCE_HPP

namespace ogonek {
    namespace detail {
        template <typename S>
        struct sequence_traits {
            using value_type = SequenceValueType<S>;
            using reference = SequenceReferenceType<S>;

            static bool empty(S const&);
            static reference front(S const&);
            static void pop_front(S&);
            static std::size_t size(S const&);
            static reference back(S const&);
            static void pop_back(S&);
            static reference operator[](S const&, std::ptrdiff_t);
            static S slice(S const&, std::ptrdiff_t, std::ptrdiff_t);
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SEQUENCE_HPP

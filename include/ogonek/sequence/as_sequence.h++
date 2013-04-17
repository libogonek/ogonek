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

// Obtaining sequences

#ifndef OGONEK_SEQUENCE_AS_SEQUENCE_HPP
#define OGONEK_SEQUENCE_AS_SEQUENCE_HPP

#include <ogonek/sequence/seq.h++>
#include <ogonek/detail/meta/character.h++>
#include <ogonek/detail/meta/iterator.h++>

#include <wheels/meta.h++>

#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <cstddef>

namespace ogonek {
    namespace detail {
        struct native_sequence_tag { using type = native_sequence_tag; };
        struct iterable_tag { using type = iterable_tag; };
        struct iterator_pair_tag { using type = iterator_pair_tag; };
        struct null_terminated_tag { using type = null_terminated_tag; };
        template <typename T,
                  bool = is_native_sequence<wheels::Unqualified<T>>(),
                  bool = has_begin_end<T, std::forward_iterator_tag>(),
                  bool = is_iterator_pair<T>(),
                  bool = is_null_terminated_string<wheels::Unqualified<T>>()>
        struct source_type_of : wheels::identity<void> {};
        template <typename T>
        using SourceTypeOf = wheels::Invoke<source_type_of<T>>;

        template <typename T, bool I, bool P, bool Z>
        struct source_type_of<T, true, I, P, Z> : native_sequence_tag {};
        template <typename T, bool P>
        struct source_type_of<T, false, true, P, true> : null_terminated_tag {};
        template <typename T, bool P>
        struct source_type_of<T, false, true, P, false> : iterable_tag {};
        template <typename T, bool Z>
        struct source_type_of<T, false, false, true, Z> : iterator_pair_tag {};
        template <typename T>
        struct source_type_of<T, false, false, false, true> : null_terminated_tag {};

        //! {traits}
        //! *Note*: implementation backend for [function:as_sequence]
        //          and [metafunction:result_of::as_sequence].
        template <typename T,
                  typename Type = SourceTypeOf<T>>
        struct as_sequence_impl {};

        template <typename S>
        struct as_sequence_impl<S, native_sequence_tag> {
            using result = S;
            static result forward(S&& s) { return std::forward<S>(s); }
        };

        template <typename Iterable>
        struct as_sequence_impl<Iterable, iterable_tag> {
        private:
            using iterator = ConstIteratorOf<Iterable>;
        public:
            using result = std::pair<iterator, iterator>;
            static result forward(Iterable const& r) { return { std::begin(r), std::end(r) }; }
        };

        template <typename Pair>
        struct as_sequence_impl<Pair, iterator_pair_tag> {
            using result = Pair;
            static result forward(Pair&& p) { return std::forward<Pair>(p); }
        };

        template <typename Char, std::size_t N>
        struct as_sequence_impl<Char[N], null_terminated_tag> {
            using result = std::pair<Char const*, Char const*>;
            static result forward(Char(&str)[N]) { return { str, str+N-1 }; }
        };
        template <typename Char, std::size_t N>
        struct as_sequence_impl<Char(&)[N], null_terminated_tag>
        : as_sequence_impl<Char[N], null_terminated_tag> {};
        template <typename Char>
        struct as_sequence_impl<Char*, null_terminated_tag> {
        private:
            using char_type = wheels::Unqualified<Char>;
        public:
            using result = std::pair<Char const*, Char const*>;
            static result forward(Char* p) { return { p, p + std::char_traits<char_type>::length(p) }; }
        };
        template <typename Char>
        struct as_sequence_impl<Char, null_terminated_tag>
        : as_sequence_impl<wheels::Unqualified<Char>, null_terminated_tag> {};
    } // namespace detail

    namespace result_of {
        //! {metafunction}
        //! *Requires*: `T` is a model of [concept:SequenceSource] [soft].
        //! *Effects*: computes the result type for [function:ogonek::as_sequence].
        //! *Returns*: `T` if `T` is a [concept:Sequence] type or a reference to one;
        //!            `U const(&)[N]` if `T` is a reference to an array of non-character type `U[N]`;
        //!            `Char const*` if `T` is a pointer `Char*` to a possibly `const` character type,
        //!              or if `T` is a reference to an array of character type `Char[N]`.
        template <typename T>
        using as_sequence = typename detail::as_sequence_impl<T>::result;
    } // namespace result_of

    //! {function}
    //! *Requires*: `T` is a model of [concept:SequenceSource] [soft];
    //!             if `T` is a pointer type, `t` is a valid pointer to the first element of a null-terminated string [undefined].
    //! *Effects*: forwards a sequence with the normalized interface, possibly using a wrapper.
    template <typename T>
    result_of::as_sequence<T> as_sequence(T&& t) {
        return detail::as_sequence_impl<T>::forward(std::forward<T>(t));
    }
} // namespace ogonek

#endif // OGONEK_SEQUENCE_FORWARD_SEQUENCE_HPP

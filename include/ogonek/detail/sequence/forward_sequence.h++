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

// Sequence forwarding

#ifndef OGONEK_DETAIL_SEQUENCE_FORWARD_SEQUENCE_HPP
#define OGONEK_DETAIL_SEQUENCE_FORWARD_SEQUENCE_HPP

#include <ogonek/detail/meta/character.h++>
#include <ogonek/detail/meta/iterator.h++>
#include <ogonek/detail/sequence/traits.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <iterator>
#include <utility>
#include <cstddef>

namespace ogonek {
    namespace detail {
        //! {traits}
        //! *Note*: implementation backend for [function:forward_sequence]
        //          and [metafunction:result_of::forward_sequence].
        template <typename T,
                    bool = is_simple_sequence<wheels::Unqualified<T>>(),
                    bool = has_begin_end<T, std::forward_iterator_tag>(),
                    bool = is_null_terminated_string<wheels::Unqualified<T>>()>
        struct forward_sequence_impl {};

        template <typename S, bool Ignore0, bool Ignore1>
        struct forward_sequence_impl<S, true, Ignore0, Ignore1> {
            using result = S;
            static result forward(S&& s) { return std::forward<result>(s); }
        };

        template <typename Range, bool Ignore>
        struct forward_sequence_impl<Range, false, true, Ignore> {
        private:
            using iterator = ConstIteratorOf<Range>;
        public:
            using result = std::pair<iterator, iterator>;
            static result forward(Range const& r) { return { std::begin(r), std::end(r) }; }
        };

        template <typename Char, std::size_t N>
        struct forward_sequence_impl<Char(&)[N], false, true, true> : forward_sequence_impl<Char*> {};
        template <typename Ptr>
        struct forward_sequence_impl<Ptr const&, false, false, true> : forward_sequence_impl<Ptr> {};
        template <typename Ptr>
        struct forward_sequence_impl<Ptr&, false, false, true> : forward_sequence_impl<Ptr> {};
        template <typename Char>
        struct forward_sequence_impl<Char*, false, false, true> {
            using result = Char const*;
            static result forward(Char* p) { return std::forward<result>(p); }
        };

        namespace result_of {
            //! {metafunction}
            //! *Requires*: `T` is a model of [concept:SequenceSource] [soft].
            //! *Effects*: computes the result type for [function:ogonek::detail::forward_sequence].
            //! *Returns*: `T` if `T` is a [concept:Sequence] type or a reference to one;
            //!            `U const(&)[N]` if `T` is a reference to an array of non-character type `U[N]`;
            //!            `Char const*` if `T` is a pointer `Char*` to a possibly `const` character type,
            //!              or a reference to an array of character type `Char[N]`.
            template <typename T>
            using forward_sequence = typename forward_sequence_impl<T>::result;
        } // namespace result_of

        //! {function}
        //! *Requires*: `T` is a model of [concept:SequenceSource] [soft];
        //!             this function was called with an lvalue [hard] TODO is it hard?;
        //!             if `T` is a pointer type, `t` is a valid pointer to the first element of a null-terminated string [undefined].
        //! *Effects*: forwards a sequence with the normalized interface, possibly using a wrapper.
        template <typename T>
        result_of::forward_sequence<T const&> forward_sequence(T const& t) {
            return forward_sequence_impl<T const&>::forward(t);
        }
        //! {overload}
        template <typename T>
        result_of::forward_sequence<T&> forward_sequence(T& t) {
            return forward_sequence_impl<T&>::forward(t);
        }

        //! {overload}
        //! *Note*: this overload causes a hard error when an rvalue is passed.
        template <typename Invalid,
                  wheels::EnableIf<std::is_rvalue_reference<Invalid&&>>...>
        void forward_sequence(Invalid&&) = delete;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SEQUENCE_FORWARD_SEQUENCE_HPP

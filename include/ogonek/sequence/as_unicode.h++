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

// Forwarding sequences of code points

#ifndef OGONEK_SEQUENCE_AS_UNICODE_HPP
#define OGONEK_SEQUENCE_AS_UNICODE_HPP

#include <ogonek/encoding.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/seq.h++>
#include <ogonek/sequence/as_sequence.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/error/error_handler.h++>

#include <wheels/meta.h++>

namespace ogonek {
    namespace detail {
        //! {traits}
        //! *Note*: implementation backend for [function:as_unicode]
        //          and [metafunction:result_of::as_unicode].
        template <typename S, typename E,
                  bool = is_error_handler<E>(),
                  typename Value = wheels::Invoke<
                                    wheels::Conditional<is_sequence<S>,
                                        seq::value<S>,
                                        wheels::identity<void>>>>
        struct as_unicode_impl {};

        template <typename U32, typename E>
        struct as_unicode_impl<U32, E, true, char32_t> {
            using result = ogonek::result_of::decode_ex<utf32, U32 const&, E>;
            static result forward(U32&& s, E&& e) {
                return decode_ex<utf32>(std::forward<U32>(s), std::forward<E>(e));
            }
        };
        template <typename U16, typename E>
        struct as_unicode_impl<U16, E, true, char16_t> {
            using result = ogonek::result_of::decode_ex<utf16, U16 const&, E>;
            static result forward(U16&& s, E&& e) {
                return decode_ex<utf16>(std::forward<U16>(s), std::forward<E>(e));
            }
        };
    } // namespace detail

    namespace result_of {
        //! {metafunction}
        //! *Requires*: `S` is a model of [concept:SequenceSource] [soft]; and
        //!             `E` is a model of [concept:ErrorHandler] [soft].
        //! *Effects*: computes the result type for [function:ogonek::detail::as_unicode].
        //! *Returns*: a [concept:Sequence] type for lazily decoding `S` according to `E`.
        //! *Remarks*: the result type is statically known well-formed.
        template <typename S, typename E>
        using as_unicode = typename detail::as_unicode_impl<as_sequence<S>, E>::result;
    } // namespace result_of

    //! {function}
    //! *Requires*: `S` is a model of [concept:SequenceSource] [soft].
    //! *Returns*: a [concept:Sequence] of code points from `s`.
    //! *Remarks*: the result is statically known well-formed.
    template <typename S, typename E>
    result_of::as_unicode<S, E> as_unicode(S&& s, E&& e) {
        return detail::as_unicode_impl<result_of::as_sequence<S>, E>::forward(as_sequence(std::forward<S>(s)), std::forward<E>(e));
    }
} // namespace ogonek

#endif // OGONEK_SEQUENCE_AS_UNICODE_HPP

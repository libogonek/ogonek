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

#ifndef OGONEK_SEQUENCE_FORWARD_CODE_POINTS_HPP
#define OGONEK_SEQUENCE_FORWARD_CODE_POINTS_HPP

#include <ogonek/encoding.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/sequence/traits.h++>
#include <ogonek/sequence/forward_sequence.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/error/error_handler.h++>

#include <wheels/meta.h++>

namespace ogonek {
    namespace detail {
        //! {traits}
        //! *Note*: implementation backend for [function:forward_code_points]
        //          and [metafunction:result_of::forward_code_points].
        template <typename S, typename E,
                  bool = is_error_handler<E>(),
                  typename Value = wheels::Invoke<
                                    wheels::Conditional<is_sequence<S>,
                                        seq::value<S>,
                                        wheels::identity<void>>>>
        struct forward_code_points_impl {};

        template <typename U32, typename E>
        struct forward_code_points_impl<U32, E, true, char32_t> {
            using result = ogonek::result_of::decode<utf32, U32 const&, E>;
            static result forward(U32 const& s, E&& e) {
                return decode<utf32>(s, std::forward<E>(e));
            }
        };
        template <typename U16, typename E>
        struct forward_code_points_impl<U16, E, true, char16_t> {
            using result = ogonek::result_of::decode<utf16, U16 const&, E>;
            static result forward(U16 const& s, E&& e) {
                return decode<utf16>(s, std::forward<E>(e));
            }
        };
    } // namespace detail

    namespace result_of {
        //! {metafunction}
        //! *Requires*: `S` is a model of [concept:SequenceSource] [soft]; and
        //!             `E` is a model of [concept:ErrorHandler] [soft].
        //! *Effects*: computes the result type for [function:ogonek::detail::forward_code_points].
        //! *Returns*: a [concept:Sequence] type that lazily decodes `S` according to `E`.
        //! *Remarks*: the result type is statically known well-formed.
        template <typename S, typename E>
        using forward_code_points =
            typename detail::forward_code_points_impl<wheels::Unqualified<forward_sequence<S>>, E>::result;
    } // namespace result_of

    //! {function}
    //! *Requires*: `S` is a model of [concept:SequenceSource].
    //! *Returns*: a [concept:Sequence] of code points from `s`.
    //! *Remarks*: the result is statically known well-formed.
    template <typename S, typename E>
    result_of::forward_code_points<S const&, E> forward_code_points(S const& s, E&& e) {
        return detail::forward_code_points_impl<S const&, E>::forward(s, std::forward<E>(e));
    }
} // namespace ogonek

#endif // OGONEK_SEQUENCE_FORWARD_CODE_POINTS_HPP

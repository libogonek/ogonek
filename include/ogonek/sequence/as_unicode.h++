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
#include <ogonek/error/assume_valid.h++>
#include <ogonek/error/error_handler.h++>

#include <taussig/primitives.h++>

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    namespace detail {
        //! {traits}
        //! *Note*: implementation backend for [function:as_unicode]
        //          and [metafunction:result_of::as_unicode].
        template <typename S, typename E,
                  bool = is_error_handler<E>(),
                  typename Value = wheels::meta::Invoke<
                                    wheels::meta::If<seq::is_sequence<S>,
                                        seq::value_type<S>,
                                        wheels::meta::id<void>>>>
        struct as_unicode_impl {};

        template <typename U32, typename E>
        struct as_unicode_impl<U32, E, true, char32_t> {
            using result = ogonek::result_of::decode<utf32, U32, E>;
            static result forward(U32&& s, E&& e) {
                return decode<utf32>(std::forward<U32>(s), std::forward<E>(e));
            }
        };
        template <typename U16, typename E>
        struct as_unicode_impl<U16, E, true, char16_t> {
            using result = ogonek::result_of::decode<utf16, U16, E>;
            static result forward(U16&& s, E&& e) {
                return decode<utf16>(std::forward<U16>(s), std::forward<E>(e));
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
        using as_unicode = typename detail::as_unicode_impl<seq::result_of::as_sequence<S>, E>::result;
    } // namespace result_of

    namespace detail {
        struct is_unicode_source_test {
            template <typename T, typename E>
            wheels::meta::DependOn<wheels::meta::True, ogonek::result_of::as_unicode<T, E>> static test(int);
            template <typename...>
            std::false_type static test(...);
        };
    } // namespace detail
    template <typename T, typename E = default_error_handler_t>
    struct is_unicode_source : wheels::meta::TraitOf<detail::is_unicode_source_test, wheels::meta::Unqual<T>, E> {};

    //! {function}
    //! *Requires*: `S` is a model of [concept:SequenceSource] [soft].
    //! *Returns*: a [concept:Sequence] of code points from `s`.
    //! *Remarks*: the result is statically known well-formed.
    template <typename S, typename E,
              wheels::meta::EnableIf<is_unicode_source<S, E>>...>
    result_of::as_unicode<S, E> as_unicode(S&& s, E&& e) {
        return detail::as_unicode_impl<seq::result_of::as_sequence<S>, E>::forward(seq::as_sequence(std::forward<S>(s)), std::forward<E>(e));
    }
    // TODO single argument version
} // namespace ogonek

#endif // OGONEK_SEQUENCE_AS_UNICODE_HPP

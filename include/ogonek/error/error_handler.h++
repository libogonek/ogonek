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

// Base error handler marker

#ifndef OGONEK_ERROR_HANDLER_HPP
#define OGONEK_ERROR_HANDLER_HPP

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    //! {concept}
    //! An error handler strategy for encoding/decoding.
    // concept ErrorHandler : ogonek::error_handler
    // requires Movable {
        //! {function}
        //! TODO handles encoding error
        // ?? apply_decode(??) const;

        //! {function}
        //! TODO handles decoding error
        // ?? apply_encode(??) const;
    // };

    namespace detail {
        struct error_handler_test {
            template <typename T>
            typename wheels::Unqualified<T>::is_error_handler static test(int);
            template <typename...>
            std::false_type static test(...);
        };
    } // namespace detail

    //! {trait}
    //! *Returns*: `true` is `T` is a model of [concept:ErrorHandler].
    template <typename T>
    using is_error_handler = wheels::TraitOf<detail::error_handler_test, T>;

    //! {tag}
    //! A tag type to mark error handlers.
    struct error_handler {
        struct is_error_handler : std::true_type {};
    };
} // namespace ogonek

#endif // OGONEK_ERROR_HANDLER_HPP

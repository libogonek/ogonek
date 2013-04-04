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
    namespace detail {
        struct error_handler {
            struct is_error_handler : std::true_type {};
        };
        
        struct error_handler_tester {
            template <typename T, typename = typename T::is_error_handler>
            std::true_type static test(int);
            template <typename T>
            std::false_type static test(...);
        };
    } // namespace detail
    template <typename T>
    using is_error_handler = wheels::TraitOf<detail::error_handler_tester, T>;
} // namespace ogonek

#endif // OGONEK_ERROR_HANDLER_HPP


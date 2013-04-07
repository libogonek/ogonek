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

// Default error handlers

#ifndef OGONEK_ERROR_DEFAULT_ERROR_HANDLER_HPP
#define OGONEK_ERROR_DEFAULT_ERROR_HANDLER_HPP

#include <ogonek/error/throw_error.h++>

namespace ogonek {
    //! {callable}
    //! Default error handling policy.
    using default_error_handler_t = throw_error_t;

    //! {object}
    //! A default instance of [function:default_error_handler_t].
    constexpr default_error_handler_t default_error_handler = {};
} // namespace ogonek

#endif // OGONEK_ERROR_DEFAULT_ERROR_HANDLER_HPP

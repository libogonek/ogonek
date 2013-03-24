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

#ifndef OGONEK_DEFAULT_ERROR_HANDLER_HPP
#define OGONEK_DEFAULT_ERROR_HANDLER_HPP

#include <ogonek/throw_error.h++>

namespace ogonek {
    constexpr auto default_error_handler = throw_error;
    using default_error_handler_t = throw_error_t;
} // namespace ogonek

#endif // OGONEK_DEFAULT_ERROR_HANDLER_HPP


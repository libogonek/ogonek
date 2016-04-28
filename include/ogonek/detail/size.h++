// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Array size function

#ifndef OGONEK_DETAIL_SIZE_HPP
#define OGONEK_DETAIL_SIZE_HPP

#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        constexpr std::size_t size(T(&)[N]) { return N; }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SIZE_HPP


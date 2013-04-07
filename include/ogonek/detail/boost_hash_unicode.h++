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

// Workaround for Boost.Hash's lack of support for char16_t and char32_t

#ifndef OGONEK_DETAIL_BOOST_HASH_UNICODE_HPP
#define OGONEK_DETAIL_BOOST_HASH_UNICODE_HPP

#include <boost/functional/hash.hpp>

// hack for char32_t and char16_t hashing
namespace boost {
    namespace hash_detail {
        template <> struct basic_numbers<char16_t>
        : boost::hash_detail::enable_hash_value {};
        template <> struct basic_numbers<char32_t>
        : boost::hash_detail::enable_hash_value {};
    } // namespace hash_detail
} // namespace boost

#endif // OGONEK_DETAIL_BOOST_HASH_UNICODE_HPP

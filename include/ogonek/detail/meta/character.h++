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

// Character related traits

#ifndef OGONEK_DETAIL_META_CHARACTERS_HPP
#define OGONEK_DETAIL_META_CHARACTERS_HPP

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    namespace detail {
        //! {trait}
        //! *Returns*: `true` if `T` is a character type; `false` otherwise.
        template <typename T>
        struct is_character : std::false_type {};
        template <>
        struct is_character<char> : std::true_type {};
        template <>
        struct is_character<signed char> : std::true_type {};
        template <>
        struct is_character<unsigned char> : std::true_type {};
        template <>
        struct is_character<wchar_t> : std::true_type {};
        template <>
        struct is_character<char16_t> : std::true_type {};
        template <>
        struct is_character<char32_t> : std::true_type {};

        //! {trait}
        //! *Returns*: true if `T` is a null-terminated string type, i.e., a pointer or array of a character type.
        template <typename T>
        struct is_null_terminated_string
        : wheels::All<
            std::is_pointer<wheels::Decay<T>>,
            is_character<wheels::RemoveCv<wheels::RemovePointer<wheels::Decay<T>>>>
        > {};
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_META_CHARACTERS_HPP

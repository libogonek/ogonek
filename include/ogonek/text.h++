// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode text class

#ifndef OGONEK_TEXT_HPP
#define OGONEK_TEXT_HPP

#include "types.h++"

#include <wheels/iterator.h++>
#include <wheels/meta.h++>

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <string>
#include <vector>

namespace ogonek {
    namespace detail {
        template <typename T>
        struct is_byte_impl : wheels::Bool<false> {};
        template <>
        struct is_byte_impl<char> : wheels::Bool<true> {};
        template <>
        struct is_byte_impl<unsigned char> : wheels::Bool<true> {};
        template <>
        struct is_byte_impl<signed char> : wheels::Bool<true> {};

        template <typename T>
        struct is_byte : is_byte_impl<wheels::RemoveCv<T>> {};

        template <typename T>
        struct is_codepoint : std::is_same<codepoint, wheels::RemoveCv<T>> {};

        template <typename Container, typename InputIterator>
        void reserve_if_random_access(Container& c, InputIterator first, InputIterator last, std::random_access_iterator_tag) {
            c.reserve(last-first);
        }

        template <typename Container, typename InputIterator>
        void reserve_if_random_access(Container& c, InputIterator first, InputIterator last, std::input_iterator_tag) {}

        template <typename Container, typename InputIterator>
        void reserve_if_random_access(Container& c, InputIterator first, InputIterator last) {
            reserve_if_random_access(c, first, last, wheels::IteratorCategory<InputIterator>{});
        }
    } // namespace detail 

    template <typename Codec, template <typename...> class Container = std::vector>
    class text {
    private:
        using code_unit = typename Codec::code_unit;

        Container<code_unit> codepoints;

        using size_type = typename Container<code_unit>::size_type;
        using difference_type = typename Container<code_unit>::difference_type;
        using reference = typename Container<code_unit>::reference;
        using const_reference = typename Container<code_unit>::const_reference;

        using iterator = typename Container<code_unit>::const_iterator;
        using const_iterator = typename Container<code_unit>::const_iterator;
        using reverse_iterator = typename Container<code_unit>::reverse_iterator;
        using const_reverse_iterator = typename Container<code_unit>::const_reverse_iterator;

    public:
        text() = default;
        //TODO: what about convertible thingies?
        template <typename InputIterator,
                  wheels::EnableIf<detail::is_codepoint<wheels::ValueType<InputIterator>>>...>
        text(InputIterator first, InputIterator last) : codepoints(first, last) {}

        template <typename Codec, typename InputIterator,
                  wheels::EnableIf<detail::is_byte<wheels::ValueType<InputIterator>>>...>
        text(InputIterator first, InputIterator last, Codec c) {
            detail::reserve_if_random_access(codepoints, first, last);
            c.decode(first, last, std::back_inserter(codepoints));
        }

        text(std::string const& str, Codec c)
        : text(str.begin(), str.end(), c) {}
        text(char const* str, Codec c)
        : text(str, str + std::char_traits<char>::length(str), c) {}
        text(std::initializer_list<char> l, Codec c)
        : text(l.begin(), l.end(), c) {}
        text(std::u16string const& str);
        //: text(str.begin(), str.end(), coded::utf16) {} TODO: convert from code units
        text(char16_t const* str);
        //: text(str, str + std::char_traits<char16_t>::length(str), coded::utf16) {} TODO: convert from code units
        text(std::initializer_list<char16_t> l);
        //: text(l.begin(), l.end(), coded::utf16) {} TODO: convert from code units
        text(std::u32string const& str);
        //: text(str.begin(), str.end(), coded::utf32) {} TODO: convert from code units
        text(char32_t const* str);
        //: text(str, str + std::char_traits<char32_t>::length(str), coded::utf32) {} TODO: convert from code units
        text(std::initializer_list<char32_t> l);
        //: text(l.begin(), l.end(), coded::utf32) {} TODO: convert from code units

        text& operator=(std::string const& str);
        text& operator=(char const* str);
        text& operator=(std::initializer_list<char> l);
        text& operator=(std::u16string const& str);
        text& operator=(char16_t const* str);
        text& operator=(std::initializer_list<char16_t> l);
        text& operator=(std::u32string const& str);
        text& operator=(char32_t const* str);
        text& operator=(std::initializer_list<char32_t> l);

        codepoint const* data() const noexcept { return codepoints.data(); }
    };
} // namespace ogonek

#endif // OGONEK_TEXT_HPP


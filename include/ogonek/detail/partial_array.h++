// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
//
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Vector like container backed by a fixed size array (fixed capacity)

#ifndef OGONEK_DETAIL_PARTIAL_ARRAY_HPP
#define OGONEK_DETAIL_PARTIAL_ARRAY_HPP

#include <algorithm>
#include <array>
#include <initializer_list>
#include <cstddef>

namespace ogonek {
    namespace detail {
        template <typename T, std::size_t N>
        struct partial_array {
            static_assert(std::is_pod<T>::value, "T must be POD");
        public:
            partial_array() = default;
            template <typename U>
            partial_array(partial_array<U, N> const& that)
            : count{ that.count } {
                std::copy(that.begin(), that.end(), array.begin());
            }
            partial_array(std::array<T, N> const& array, std::size_t count)
            : count{ count }, array(array) {}
            partial_array(std::initializer_list<T> list)
            : count{ list.size() } {
                std::copy(list.begin(), list.end(), array.begin());
            }
            template <typename Iterator>
            partial_array(Iterator first, Iterator last)
            : count(last - first) {
                std::copy(first, last, array.begin());
            }

            void push_back(T const& item) { array[count++] = item; }
            void clear() { count = 0; }

            using iterator = typename std::array<T, N>::iterator;
            using const_iterator = typename std::array<T, N>::const_iterator;

            iterator begin() { return array.begin(); }
            const_iterator begin() const { return array.begin(); }
            iterator end() { return array.begin() + count; }
            const_iterator end() const { return array.begin() + count; }

            std::size_t size() const { return count; }

            T& operator[](std::ptrdiff_t index) { return array[index]; }
            T const& operator[](std::ptrdiff_t index) const { return array[index]; }

        private:
            std::size_t count = 0;
            std::array<T, N> array;
        };

        template <typename Encoding>
        using coded_character = partial_array<typename Encoding::code_unit, Encoding::max_width>;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_ARRAY_SLICE_HPP


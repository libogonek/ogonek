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

// Encoding/decoding iterators

#ifndef OGONEK_ENCODING_ITERATOR_HPP
#define OGONEK_ENCODING_ITERATOR_HPP

#include "../traits.h++"
#include "../types.h++"
#include "../validation.h++"

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <initializer_list>
#include <array>
#include <algorithm>

namespace ogonek {
    template <typename T, std::size_t N>
    struct partial_array {
    public:
        template <typename U>
        partial_array(partial_array<U, N> const& that)
        : count(that.count) {
            std::copy(that.begin(), that.end(), array.begin());
        }
        partial_array(std::array<T, N> array, std::size_t count)
        : count(count), array(array) {}
        partial_array(std::initializer_list<T> list)
        : count { list.size() } {
            std::copy(list.begin(), list.end(), array.begin());
        }

        using iterator = typename std::array<T, N>::const_iterator;
        using const_iterator = typename std::array<T, N>::const_iterator;

        iterator begin() { return array.begin(); }
        iterator begin() const { return array.begin(); }
        iterator end() { return array.begin() + count; }
        iterator end() const { return array.begin() + count; }

        std::size_t size() const { return count; }

        T& operator[](std::ptrdiff_t index) { return array[index]; }
        T const& operator[](std::ptrdiff_t index) const { return array[index]; }

    private:
        std::size_t count;
        std::array<T, N> array;
    };

    inline void validate(codepoint&, decltype(skip_validation)) {}
    inline bool is_surrogate(codepoint u) { return u >= 0xD800 && u <= 0xDFFF; }
    template <typename Callback>
    void validate(codepoint& u, Callback&& callback) {
        auto list = { u };
        if(u > 0x10FFFF || is_surrogate(u)) {
            callback(validation_result::illegal, boost::sub_range<decltype(list)>(list), u); // TODO: how to use the result?
        }
    }

    template <typename EncodingForm, typename Iterator, typename ValidationCallback>
    struct encoding_iterator
    : boost::iterator_facade<
        encoding_iterator<EncodingForm, Iterator, ValidationCallback>,
        CodeUnit<EncodingForm>,
        std::input_iterator_tag, // TODO
        CodeUnit<EncodingForm>
      > {
    public:
        encoding_iterator(Iterator first, Iterator last, ValidationCallback callback)
        : first(first), last(last), callback(std::forward<ValidationCallback>(callback)) {
            encode_next();
        }

        CodeUnit<EncodingForm> dereference() const {
            return encoded[current];
        }
        bool equal(encoding_iterator const& that) const {
            return (first == that.first && current == that.current)
                || (first == last && that.first == that.last
                    && current == -1 && that.current == -1);
        }
        void increment() {
            ++current;
            if(current == static_cast<int>(encoded.size())) {
                encode_next();
            }
        }

    private:
        void encode_next() {
            if(first != last) {
                auto u = *first++;
                validate(u, callback);
                encoded = EncodingForm::encode_one(u, state);
                current = 0;
            } else {
                current = -1;
            }
        }

        Iterator first, last;
        typename std::decay<ValidationCallback>::type callback;
        typename EncodingForm::state state {};
        partial_array<CodeUnit<EncodingForm>, EncodingForm::max_width> encoded {};
        int current;
    };

    template <typename EncodingForm, typename Iterator, typename ValidationCallback>
    struct decoding_iterator
    : boost::iterator_facade<
        decoding_iterator<EncodingForm, Iterator, ValidationCallback>,
        codepoint,
        std::input_iterator_tag, // TODO
        codepoint
      > {
    public:
        using range = boost::iterator_range<Iterator>;

        decoding_iterator(Iterator first, Iterator last, ValidationCallback callback)
        : first(first), last(last), callback(std::forward<ValidationCallback>(callback)) {}

        codepoint dereference() const {
            codepoint u;
            auto s = state;
            EncodingForm::decode_one(boost::sub_range<range>(first, last), u, s, callback);
            return u;
        }
        bool equal(decoding_iterator const& that) const {
            return first == that.first || (first == last && that.first == that.last);
        }
        void increment() {
            codepoint dummy;
            first = EncodingForm::decode_one(boost::sub_range<range>(first, last), dummy, state, callback).begin();
        }

    private:
        Iterator first, last;
        typename std::decay<ValidationCallback>::type callback;
        typename EncodingForm::state state {};
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


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
        partial_array(std::array<T, N> array, std::size_t count)
        : count(count), array(array) {}
        partial_array(std::initializer_list<T> list)
        : count { list.size() } {
            std::copy(list.begin(), list.end(), array.begin());
        }

        using iterator = typename std::array<T, N>::iterator;
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

    template <typename EncodingForm, typename SinglePassRange>
    struct encoding_iterator
    : boost::iterator_facade<
        encoding_iterator<EncodingForm, SinglePassRange>,
        CodeUnit<EncodingForm>,
        std::input_iterator_tag, // TODO
        CodeUnit<EncodingForm>
      > {
    public:
        using iterator = typename boost::range_iterator<SinglePassRange>::type;

        encoding_iterator(iterator first, iterator last)
        : first(first), last(last) {
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
                encoded = EncodingForm::encode_one(*first++, state);
                current = 0;
            } else {
                current = -1;
            }
        }

        iterator first, last;
        typename EncodingForm::state state {};
        partial_array<CodeUnit<EncodingForm>, EncodingForm::max_width> encoded {};
        int current;
    };

    template <typename EncodingForm, typename SinglePassRange, typename ValidationCallback = void>
    struct decoding_iterator
    : boost::iterator_facade<
        decoding_iterator<EncodingForm, SinglePassRange, ValidationCallback>,
        codepoint,
        std::input_iterator_tag, // TODO
        codepoint
      > {
    public:
        using iterator = typename boost::range_iterator<SinglePassRange>::type;

        decoding_iterator(iterator first, iterator last, ValidationCallback callback)
        : first(first), last(last), callback(std::forward<ValidationCallback>(callback)) {}

        codepoint dereference() const {
            codepoint u;
            auto s(state);
            EncodingForm::decode_one(boost::sub_range<SinglePassRange>(first, last), u, s, callback);
            return u;
        }
        bool equal(decoding_iterator const& that) const {
            return first == that.first || (first == last && that.first == that.last);
        }
        void increment() {
            codepoint dummy;
            first = EncodingForm::decode_one(boost::sub_range<SinglePassRange>(first, last), dummy, state, callback).begin();
        }

    private:
        iterator first, last;
        typename std::decay<ValidationCallback>::type callback;
        typename EncodingForm::state state {};
    };

    template <typename EncodingForm, typename SinglePassRange>
    struct decoding_iterator<EncodingForm, SinglePassRange, void>
    : boost::iterator_facade<
        decoding_iterator<EncodingForm, SinglePassRange>,
        codepoint,
        std::input_iterator_tag, // TODO
        codepoint
      > {
    public:
        using iterator = typename boost::range_iterator<SinglePassRange>::type;

        decoding_iterator(iterator first, iterator last)
        : first(first), last(last), state{} {}

        codepoint dereference() const {
            codepoint u;
            auto s(state);
            EncodingForm::decode_one(boost::sub_range<SinglePassRange>(first, last), u, s);
            return u;
        }
        bool equal(decoding_iterator const& that) const {
            return first == that.first || (first == last && that.first == that.last);
        }
        void increment() {
            codepoint dummy;
            first = EncodingForm::decode_one(boost::sub_range<SinglePassRange>(first, last), dummy, state).begin();
        }

    private:
        iterator first, last;
        typename EncodingForm::state state;
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


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

// UTF-8 encoding form

#ifndef OGONEK_ENCODING_UTF8_HPP
#define OGONEK_ENCODING_UTF8_HPP

#include "../types.h++"
#include "../validation.h++"

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>

namespace ogonek {
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
        : first(first), last(last), callback(std::forward<ValidationCallback>(callback)), state{} {}

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
        typename EncodingForm::state state;
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

    struct utf8 {
        using code_unit = char;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 4;
        static constexpr bool is_self_synchronizing = true;
        struct state {};

        /*
        template <typename SinglePassRange>
        static boost::iterator_range<encoding_iterator<SinglePassRange>> encode(SinglePassRange const& r) {
            // TODO
        }
        */
        template <typename SinglePassRange>
        static boost::iterator_range<decoding_iterator<utf8, SinglePassRange>> decode(SinglePassRange const& r) {
            return boost::make_iterator_range(
                    decoding_iterator<utf8, SinglePassRange> { boost::begin(r), boost::end(r) },
                    decoding_iterator<utf8, SinglePassRange> { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename ValidationCallback>
        static boost::iterator_range<decoding_iterator<utf8, SinglePassRange, ValidationCallback>> decode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    decoding_iterator<utf8, SinglePassRange, ValidationCallback> { boost::begin(r), boost::end(r), callback },
                    decoding_iterator<utf8, SinglePassRange, ValidationCallback> { boost::end(r), boost::end(r), callback });
        }

        template <typename T, std::size_t N>
        struct partial_array {
        public:
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

        private:
            std::size_t count;
            std::array<T, N> array;
        };

        static partial_array<code_unit, 4> encode_one(codepoint u, state&) {
            if(u <= 0x7F) {
                return { static_cast<code_unit>(u & 0x7F) };
            } else if(u <= 0x7FF) {
                return {
                    static_cast<code_unit>(0xC0 | ((u & 0x3C0) >> 6)),
                    static_cast<code_unit>(0x80 | (u & 0x3F)),
                };
            } else if(u <= 0xFFFF) {
                return {
                    static_cast<code_unit>(0xE0 | ((u & 0xF000) >> 12)),
                    static_cast<code_unit>(0x80 | ((u & 0xFC0) >> 6)),
                    static_cast<code_unit>(0x80 | (u & 0x3F)),
                };
            }
            return {
                static_cast<code_unit>(0xF0 | ((u & 0x1C0000) >> 18)),
                static_cast<code_unit>(0x80 | ((u & 0x3F000) >> 12)),
                static_cast<code_unit>(0x80 | ((u & 0xFC0) >> 6)),
                static_cast<code_unit>(0x80 | (u & 0x3F)),
            };
        }

        static constexpr int sequence_length(byte b) {
            return (b & 0x80) == 0? 1
                 : (b & 0xE0) != 0xE0? 2
                 : (b & 0xF0) != 0xF0? 3
                 : 4;
        }
        static constexpr bool is_continuation(byte b) {
            return (b & 0xC0) == 0x80;
        }

        static constexpr codepoint decode(byte b0, byte b1) {
            return ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        }
        static constexpr codepoint decode(byte b0, byte b1, byte b2) {
            return ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        }
        static constexpr codepoint decode(byte b0, byte b1, byte b2, byte b3) {
            return ((b0 & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&) {
            auto first = boost::begin(r);
            byte b0 = *first++;
            auto length = sequence_length(b0);
            if(length == 1) {
                out = b0;
                return { first, boost::end(r) };
            }
            byte b1 = *first++;
            if(length == 2) {
                out = decode(b0, b1);
                return { first, boost::end(r) };
            }
            byte b2 = *first++;
            if(length == 3) {
                out = decode(b0, b1, b2);
                return { first, boost::end(r) };
            }
            byte b3 = *first++;
            out = decode(b0, b1, b2, b3);
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange, typename ValidationCallback>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, ValidationCallback&& callback) {
            auto first = boost::begin(r);
            byte b0 = *first++;
            auto length = sequence_length(b0);

            if(length == 1) {
                out = b0;
                return { first, boost::end(r) };
            }

            auto is_invalid = [](byte b) { return b == 0xC0 || b == 0xC1 || b > 0xF4; };

            if(is_invalid(b0) || is_continuation(b0)) {
                return std::forward<ValidationCallback>(callback)(validation_result::illegal, r, out);
            }

            std::array<byte, 4> b = {{ b0, }};
            for(int i = 1; i < length; ++i) {
                b[i] = *first++;
                if(!is_continuation(b[i])) {
                    return std::forward<ValidationCallback>(callback)(validation_result::illegal, r, out);
                }
            }

            if(length == 2) {
                out = decode(b[0], b[1]);
            } else if(length == 3) {
                out = decode(b[0], b[1], b[2]);
            } else {
                out = decode(b[0], b[1], b[2], b[3]);
            }

            auto is_overlong = [](codepoint u, int bytes) {
                return u <= 0x7F || (u <= 0x7FF && bytes > 2) || (u <= 0xFFFF && bytes > 3);
            };
            if(is_overlong(out, length)) {
                return std::forward<ValidationCallback>(callback)(validation_result::illegal, r, out);
            }
            auto is_surrogate = [](codepoint u) { return u >= 0xD800 && u <= 0xDFFF; };
            if(is_surrogate(out) || out > 0x10FFFF) {
                return std::forward<ValidationCallback>(callback)(validation_result::irregular, r, out);
            }
            return { first, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF8_HPP


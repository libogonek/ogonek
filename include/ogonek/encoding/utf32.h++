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

// UTF-32 encoding form

#ifndef OGONEK_ENCODING_UTF32_HPP
#define OGONEK_ENCODING_UTF32_HPP

#include "../types.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <utility>

namespace ogonek {
    struct utf32 {
        using code_unit = char32_t;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        struct state {};

        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator encode(SinglePassRange const& r, OutputIterator out) {
            for(auto u : r) {
                *out++ = u;
            }
            return out;
        }
        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out) {
            for(auto c : r) {
                *out++ = c;
            }
            return out;
        }

        template <typename SinglePassRange, typename OutputIterator, typename ValidationCallback>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out, ValidationCallback&& callback) {
            for(auto c : r) {
                auto range = { c };
                auto result = validate_one(range);
                if(result == validation_result::valid) {
                    *out++ = c;
                } else {
                    std::forward<ValidationCallback>(callback)(result, range, out);
                }
            }
            return out;
        }

        template <typename SinglePassRange>
        static validation_result validate_one(SinglePassRange const& r, state&) {
            return validate_one(r);
        }
        template <typename SinglePassRange>
        static validation_result validate_one(SinglePassRange const& r) {
            auto first = boost::begin(r);
            codepoint u0 = *first++;
            if(u0 > 0x10FFFF) return validation_result::irregular;

            return validation_result::valid;
        }

        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out) {
            *out++ = u;
            return out;
        }
        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out, state&) { return encode_one(u, out); }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&) {
            return decode_one(r, out);
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF32_HPP


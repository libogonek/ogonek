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

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>

namespace ogonek {
    struct utf8 {
        using code_unit = byte;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 4;
        static constexpr bool is_self_synchronizing = true;
        struct state {};

        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator encode(SinglePassRange const& r, OutputIterator out) {
            for(auto u : r) {
                out = encode_one(u, out);
            }
            return out;
        }
        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out) {
            for(boost::sub_range<SinglePassRange> slice { r }; !boost::empty(slice); ) {
                codepoint c;
                slice = decode_one(slice, c);
                *out++ = c;
            }
            return out;
        }

        template <typename SinglePassRange, typename OutputIterator, typename ValidationCallback>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out, ValidationCallback&& callback) {
            for(boost::sub_range<SinglePassRange> slice { r }; !boost::empty(slice); ) {
                codepoint c;
                auto result = validate_one(slice);
                if(result == validation_result::valid) {
                    slice = decode_one(slice, c);
                    *out++ = c;
                } else {
                    slice = std::forward<ValidationCallback>(callback)(result, slice, out);
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
            if(u0 < 0x80) return validation_result::valid; // early exit for ASCII

            auto is_invalid = [](codepoint u) { return u == 0xC0 || u == 0xC1 || u > 0xF4; };
            auto is_continuation = [](codepoint u) { return (u & 0xC0) == 0x80; };

            if(is_invalid(u0) || is_continuation(u0)) return validation_result::illegal;

            int bytes = (u0 & 0xF0) == 0xC0? 2
                        : (u0 & 0xF0) == 0xE0? 3
                        : 4;
            std::array<codepoint, 4> us = {{ u0, }};
            for(int i = 1; i < bytes; ++i) {
                us[i] = *first++;
                if(!is_continuation(us[i])) return validation_result::illegal;
            }

            if(bytes == 2) {
                u0 = ((us[0] & 0x1F) << 6) |
                      (us[1] & 0x3F);
            } else if(bytes == 3) {
                u0 = ((us[0] & 0x0F) << 12) |
                     ((us[1] & 0x3F) << 6) |
                      (us[2] & 0x3F);
            } else {
                u0 = ((us[0] & 0x07) << 18) |
                     ((us[1] & 0x3F) << 12) |
                     ((us[2] & 0x3F) << 6) |
                      (us[3] & 0x3F);
            }

            auto is_overlong = [](codepoint u, int b) {
                return u <= 0x7F
                   || (u <= 0x7FF && b > 2)
                   || (u <= 0xFFFF && b > 3);
            };
            if(is_overlong(u0, bytes)) {
                return validation_result::illegal;
            }
            auto is_surrogate = [](codepoint u) { return u >= 0xD800 && u <= 0xDFFF; };
            if(is_surrogate(u0) || u0 > 0x10FFFF) {
                return validation_result::irregular;
            }
            return validation_result::valid;
        }

        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out) {
            if(u <= 0x7F) {
                *out++ = u & 0x7F;
            } else if(u <= 0x7FF) {
                *out++ = 0xC0 | ((u & 0x3C0) >> 6);
                *out++ = 0x80 | (u & 0x3F);
            } else if(u <= 0xFFFF) {
                *out++ = 0xE0 | ((u & 0xF000) >> 12);
                *out++ = 0x80 | ((u & 0xFC0) >> 6);
                *out++ = 0x80 | (u & 0x3F);
            } else {
                *out++ = 0xF0 | ((u & 0x1C0000) >> 18);
                *out++ = 0x80 | ((u & 0x3F000) >> 12);
                *out++ = 0x80 | ((u & 0xFC0) >> 6);
                *out++ = 0x80 | (u & 0x3F);
            }
            return out;
        }
        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out, state&) { return encode_one(u, out); }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out) {
            auto first = boost::begin(r);
            codepoint u0 = *first++;
            if((u0 & 0x80) == 0) {
                out = u0;
                return { first, boost::end(r) };
            }
            codepoint u1 = *first++;
            if((u0 & 0xE0) != 0xE0) {
                out = ((u0 & 0x1F) << 6) |
                      (u1 & 0x3F);
                return { first, boost::end(r) };
            }
            codepoint u2 = *first++;
            if((u0 & 0xF0) != 0xF0) {
                out = ((u0 & 0x0F) << 12) |
                      ((u1 & 0x3F) << 6) |
                      (u2 & 0x3F);
                return { first, boost::end(r) };
            }
            codepoint u3 = *first++;
            out = ((u0 & 0x07) << 18) |
                  ((u1 & 0x3F) << 12) |
                  ((u2 & 0x3F) << 6) |
                  (u3 & 0x3F);
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&) {
            return decode_one(r, out);
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF8_HPP


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

// UTF-16 encoding form

#ifndef OGONEK_ENCODING_UTF16_HPP
#define OGONEK_ENCODING_UTF16_HPP

#include "../types.h++"
#include "../validation.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>

namespace ogonek {
    struct utf16 {
        using code_unit = char16_t;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 2;
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
                    slice = callback(result, slice, out);
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

            auto is_lead_surrogate = [](codepoint u) { return u >= 0xD800 && u <= 0xDBFF; };
            auto is_trail_surrogate = [](codepoint u) { return u >= 0xDC00 && u <= 0xDFFF; };
            auto is_surrogate = [&is_lead_surrogate, &is_trail_surrogate](codepoint u) {
                return is_lead_surrogate(u) || is_trail_surrogate(u);
            };

            if(!is_surrogate(u0)) return validation_result::valid;
            if(!is_lead_surrogate(u0)) return validation_result::illegal;

            codepoint u1 = *first++;
            if(!is_trail_surrogate(u1)) return validation_result::illegal;

            return validation_result::valid;
        }


        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out) {
            if(u <= 0xFFFF) {
                *out++ = u;
            } else {
                auto normal = u - 0x10000;
                auto lead = 0xD800 + ((normal & 0xFFC00) >> 10);
                auto trail = 0xDC00 + (normal & 0x3FF);
                *out++ = lead;
                *out++ = trail;
            }
            return out;
        }
        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out, state&) { return encode_one(u, out); }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out) {
            auto first = boost::begin(r);
            auto lead = *first++;
            if(lead < 0xD800 || lead > 0xDFFF) {
                out = lead;
            } else {
                auto trail = *first++;
                auto hi = lead - 0xD800;
                auto lo = trail - 0xDC00;
                out = 0x10000 + ((hi << 10) | lo);
            }
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&) {
            return decode_one(r, out);
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF16_HPP



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

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

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



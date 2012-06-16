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

// UTF-16 codecs

#ifndef OGONEK_CODEC_UTF16_HPP
#define OGONEK_CODEC_UTF16_HPP

#include "common.h++"
#include "../types.h++"

#include <cassert>
#include <cstddef>
#include <array>

namespace ogonek {
    namespace codec {
        namespace utf16_detail {
            template <byte_order ByteOrder>
            struct endian;
            template <>
            struct endian<byte_order::big_endian> {
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b) {
                    *out++ = a;
                    *out++ = b;
                }
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b, byte c, byte d) {
                    *out++ = a;
                    *out++ = b;
                    *out++ = c;
                    *out++ = d;
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    return (t[0] << 8) | t[1];
                }
            };
            template <>
            struct endian<byte_order::little_endian> {
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b) {
                    *out++ = b;
                    *out++ = a;
                }
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b, byte c, byte d) {
                    *out++ = b;
                    *out++ = a;
                    *out++ = d;
                    *out++ = c;
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    return (t[1] << 8) | t[0];
                }
            };
        } // namespace utf16_detail

        template <byte_order ByteOrder>
        struct utf16 : detail::codec_base<utf16<ByteOrder>> {
            static constexpr bool is_fixed_width = false;
            static constexpr std::size_t max_width = 4;
            struct state {};

            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out, state = {}) {
                assert(c < 0x200000); // TODO: invalids are UB?
                if(c < 0x10000) {
                    utf16_detail::endian<ByteOrder>::output(out,
                        (c & 0xFF00) >> 8, c & 0xFF);
                } else {
                    auto normal = c - 0x10000;
                    auto lead = 0xD800 + ((normal & 0xFFC00) >> 10);
                    auto trail = 0xDC00 + (normal & 0x3FF);
                    utf16_detail::endian<ByteOrder>::output(out,
                        (lead & 0xFF00) >> 8, lead & 0xFF,
                        (trail & 0xFF00) >> 8, trail & 0xFF);
                }
            }
            template <typename InputIterator>
            codepoint decode_one(InputIterator& first, InputIterator /*TODO: use last*/, state = {}) {
                std::array<byte, 2> leads { { *first++, *first++ } };
                auto lead = utf16_detail::endian<ByteOrder>::make_code_unit(leads);
                if(lead < 0xD800 || lead > 0xDFFF) {
                    return lead;
                } else {
                    std::array<byte, 2> trails { { *first++, *first++ } };
                    auto trail = utf16_detail::endian<ByteOrder>::make_code_unit(trails);
                    auto top = lead - 0xD800;
                    auto low = trail - 0xDC00;
                    return 0x10000 + ((top << 10) | low);
                }
            }
        };
        using utf16be = utf16<byte_order::big_endian>;
        using utf16le = utf16<byte_order::little_endian>;
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP



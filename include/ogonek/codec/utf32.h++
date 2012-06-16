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

// UTF-32 codecs

#ifndef OGONEK_CODEC_UTF32_HPP
#define OGONEK_CODEC_UTF32_HPP

#include "common.h++"
#include "../types.h++"

#include <cassert>
#include <cstddef>
#include <array>

namespace ogonek {
    namespace codec {
        namespace utf32_detail {
            template <byte_order ByteOrder>
            struct endian;
            template <>
            struct endian<byte_order::big_endian> {
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b, byte c, byte d) {
                    *out++ = a;
                    *out++ = b;
                    *out++ = c;
                    *out++ = d;
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    codepoint result = 0;
                    for(int i = 0; i < 4; ++i) {
                        result <<= 8;
                        result |= t[i];
                    }
                    return result;
                }
            };
            template <>
            struct endian<byte_order::little_endian> {
                template <typename OutputIterator>
                static void output(OutputIterator& out, byte a, byte b, byte c, byte d) {
                    *out++ = d;
                    *out++ = c;
                    *out++ = b;
                    *out++ = a;
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    codepoint result = 0;
                    for(int i = 0; i < 4; ++i) {
                        result <<= 8;
                        result |= t[3-i];
                    }
                    return result;
                }
            };
        } // namespace utf32_detail

        template <byte_order ByteOrder>
        struct utf32 : detail::codec_base<utf32<ByteOrder>> {
            static constexpr bool is_fixed_width = true;
            static constexpr std::size_t max_width = 4;
            struct state {};

            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out, state = {}) {
                assert(c < 0x200000); // TODO: invalids are UB?
                return utf32_detail::endian<ByteOrder>::output(out,
                         0, (c & 0x1F0000) >> 16, (c & 0xFF00) >> 8, c & 0xFF);
            }
            template <typename InputIterator>
            codepoint decode_one(InputIterator& first, InputIterator /*TODO use last*/, state = {}) {
                std::array<byte, 4> bytes { { *first++, *first++, *first++, *first++ } };
                return utf32_detail::endian<ByteOrder>::make_code_unit(bytes);
            }
        };
        using utf32be = utf32<byte_order::big_endian>;
        using utf32le = utf32<byte_order::little_endian>;
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP



// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode encoder/decoder

// # Codec concept
// Assume C is a Codec type, codec is an instance of C, u is a codepoint, b is
// a byte, [bb, be) is a range of input iterators on bytes, [cb, ce) is a range
// of input iterators on codepoints, o is an output iterator on bytes.
//    C::is_fixed_width        | constexpr bool        | true iff is fixed width
//    C::max_width             | constexpr size_t      | maximum width
//    C codec;                 | C                     | creates a new codec
//    C()                      | C                     | creates a new codec
//    codec.encode_one(c, o)   | void                  | encodes one codepoint
//    codec.decode_one(bb, be) | codepoint             | decodes codepoints
//    codec.encode(cb, ce)     | a range of bytes      | encodes codepoints
//    codec.decode(bb, be)     | a range of codepoints | decodes codepoints
//TODO: bytes vs code units?

#ifndef OGONEK_CODEC_HPP
#define OGONEK_CODEC_HPP

#include "types.h++"

#include <cassert>
#include <cstddef>
#include <array>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

namespace ogonek {
    namespace codec {
        namespace detail {
            template <typename Derived>
            struct codec_base {
                template <typename InputIterator>
                std::vector<byte> encode(InputIterator first, InputIterator last) {
                    //TODO: optimizations for better iterators
                    std::vector<byte> result;
                    for(auto out = std::back_inserter(result); first != last; ++first) {
                        static_cast<Derived*>(this)->encode_one(*first, out);
                    }
                    return result;
                }
                template <typename InputIterator>
                std::vector<codepoint> decode(InputIterator& first, InputIterator last) {
                    //TODO: return text instead
                    std::vector<codepoint> result;
                    while(first != last) {
                        result.push_back(static_cast<Derived*>(this)->decode_one(first, last));
                    }
                    return result;
                }
            };
        } // namespace detail

        enum class byte_order {
            big_endian,
            little_endian
        };

        struct utf8 : detail::codec_base<utf8> {
            static constexpr bool is_fixed_width = false;
            static constexpr std::size_t max_width = 4;
            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out) {
                assert(c < 0x200000); // TODO: invalids are UB?
                if(c < 0x80) {
                    *out++ = byte(c & 0x7F);
                } else if(c < 0x800) {
                    *out++ = 0xC0 | ((c & 0x3C0) >> 6);
                    *out++ = 0x80 | (c & 0x3F);
                } else if(c < 0x10000) {
                    *out++ = 0xE0 | ((c & 0xF000) >> 12);
                    *out++ = 0x80 | ((c & 0xFC0) >> 6);
                    *out++ = 0x80 | (c & 0x3F);
                } else {
                    *out++ = 0xF0 | ((c & 0x1C0000) >> 18);
                    *out++ = 0x80 | ((c & 0x3F000) >> 12);
                    *out++ = 0x80 | ((c & 0xFC0) >> 6);
                    *out++ = 0x80 | (c & 0x3F);
                }
            }
            template <typename InputIterator>
            codepoint decode_one(InputIterator& first, InputIterator /*TODO test last*/) {
                codepoint u0 = *first++;
                if((u0 & 0x80) == 0) {
                    return u0;
                }
                codepoint u1 = *first++;
                if((u0 & 0xE0) != 0xE0) {
                    return ((u0 & 0x1F) << 6) |
                           (u1 & 0x3F);
                }
                codepoint u2 = *first++;
                if((u0 & 0xF0) != 0xF0) {
                    return ((u0 & 0x0F) << 12) |
                           ((u1 & 0x3F) << 6) |
                           (u2 & 0x3F);
                }
                codepoint u3 = *first++;
                return ((u0 & 0x07) << 18) |
                       ((u1 & 0x3F) << 12) |
                       ((u2 & 0x3F) << 6) |
                       (u3 & 0x3F);
            }
        };
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
            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out) {
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
            codepoint decode_one(InputIterator& first, InputIterator /*TODO: use last*/) {
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
            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out) {
                assert(c < 0x200000); // TODO: invalids are UB?
                return utf32_detail::endian<ByteOrder>::output(out,
                         0, (c & 0x1F0000) >> 16, (c & 0xFF00) >> 8, c & 0xFF);
            }
            template <typename InputIterator>
            codepoint decode_one(InputIterator& first, InputIterator /*TODO use last*/) {
                std::array<byte, 4> bytes { { *first++, *first++, *first++, *first++ } };
                return utf32_detail::endian<ByteOrder>::make_code_unit(bytes);
            }
        };
        using utf32be = utf32<byte_order::big_endian>;
        using utf32le = utf32<byte_order::little_endian>;
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP


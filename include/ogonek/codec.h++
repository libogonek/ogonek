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
// of input iterators on codepoints, bo is an output iterator on bytes, and co
// is an output iterator on codepoints.
//    C::is_fixed_width        | constexpr bool        | true iff is fixed width
//    C::max_width             | constexpr size_t      | maximum width
//    C::is_reusable           | constexpr bool        | true iff is the codec can be reused
//    C codec;                 | C                     | creates a new codec
//    C()                      | C                     | creates a new codec
//    codec.encode_one(c, bo)  | void                  | encodes one codepoint (optional)
//    codec.decode_one(bb, be) | codepoint             | decodes one codepoint (optional)
//    codec.encode(cb, ce, bo) | output iterator       | encodes codepoints
//    codec.decode(bb, be, co) | output iterator       | decodes codepoints
//TODO: bytes vs code units?

#ifndef OGONEK_CODEC_HPP
#define OGONEK_CODEC_HPP

#include "types.h++"

#include <cassert>
#include <cstddef>
#include <array>
#include <tuple>
#include <utility>

namespace ogonek {
    namespace codec {
        namespace detail {
            template <typename Derived>
            struct codec_base {
                template <typename InputIterator, typename OutputIterator>
                OutputIterator encode(InputIterator first, InputIterator last, OutputIterator out) {
                    for(; first != last; ++first) {
                        static_cast<Derived*>(this)->encode_one(*first, out);
                    }
                    return out;
                }
                template <typename InputIterator, typename OutputIterator>
                OutputIterator decode(InputIterator first, InputIterator last, OutputIterator out) {
                    while(first != last) {
                        *out++ = static_cast<Derived*>(this)->decode_one(first, last);
                    }
                    return out;
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
            static constexpr bool is_reusable = true;
            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out) {
                assert(c < 0x200000); // TODO: invalids are UB?
                if(c < 0x80) {
                    *out++ = c & 0x7F;
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
            static constexpr bool is_reusable = true;
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
            static constexpr bool is_reusable = true;
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

        namespace detail {
            constexpr char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            unsigned rev_base64(char c) {
                return std::find(std::begin(base64), std::end(base64), c) - std::begin(base64);
            }
        } // namespace detail
        struct utf7 {
            static constexpr bool is_fixed_width = true;
            static constexpr std::size_t max_width = 4;
            static constexpr bool is_reusable = false;
        private:
            bool in_unicode = false;

            template <typename OutputIterator>
            void enter_ascii(OutputIterator& out) {
                if(in_unicode) {
                    flush(out);
                    *out++ = '-';
                    in_unicode = false;
                }
            }
            template <typename OutputIterator>
            void enter_unicode(OutputIterator& out) {
                if(!in_unicode) {
                    flush(out);
                    *out++ = '+';
                    in_unicode = true;
                }
            }

            std::uint16_t state = 0;
            int state_bits = 0;
            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out) {
                if(c == '+') {
                    enter_ascii(out);
                    *out++ = '+';
                    *out++ = '-';
                } else  if((c >= 0x20 && c <= 0x7E && c != '~' && c != '\\')
                           || (c == '\t' || c == '\r' || c == '\n')) {
                    // NOTE: all optional direct characters considered
                    enter_ascii(out);
                    *out++ = c;
                } else {
                    enter_unicode(out);
                    utf16be u16codec;
                    auto src = { c };
                    std::array<byte, 4> u16;
                    auto end = u16codec.encode(src.begin(), src.end(), u16.begin());
                    for(auto it = u16.begin(); it != end; ++it) {
                        auto unit = *it;
                        state_bits += 2;
                        *out++ = detail::base64[state | (unit >> state_bits)];
                        state = (unit & (0x3F >> (6-state_bits))) << (6-state_bits);
                        if(state_bits == 6) {
                            *out++ = detail::base64[state];
                            state = 0;
                        }
                        state_bits %= 6;
                    }
                }
            }
            template <typename OutputIterator>
            void flush(OutputIterator& out) {
                if(state_bits != 0) {
                    *out++ = detail::base64[state];
                    state = 0;
                    state_bits = 0;
                }
            }
            template <typename InputIterator>
            codepoint get_unit(byte& c, InputIterator& first, InputIterator /*TODO use last*/) {
                state |= c << (10-state_bits);
                state_bits += 6;
                for(; state_bits < 10; state_bits += 6) {
                    c = detail::rev_base64(*first++);
                    state |= c << (10-state_bits);
                }
                c = detail::rev_base64(*first++);
                codepoint result = state | (c >> (state_bits-10));
                state = c << (16-(state_bits-10));
                state_bits -= 10;
                return result;
            }
            template <typename InputIterator>
            codepoint decode_one(InputIterator& first, InputIterator last) {
                auto c = *first++;
                if(in_unicode && c == '-') {
                    if(first == last) return -1;
                    c = *first++;
                    in_unicode = false;
                } else if(!in_unicode && c == '+') {
                    c = *first++;
                    if(c == '-') return '+';
                    in_unicode = true;
                    state = 0;
                    state_bits = 0;
                }
                if(!in_unicode) return c;
                c = detail::rev_base64(c);
                auto lead = get_unit(c, first, last);
                if(lead >= 0xD800 && lead < 0xDC00) {
                    auto trail = get_unit(c, first, last);
                    auto units = { byte((lead & 0xFF00) >> 8), byte(lead & 0xFF),
                                   byte((trail & 0xFF00) >> 8), byte(trail & 0xFF) };
                    utf16be codec;
                    auto it = units.begin();
                    return codec.decode_one(it, units.end());
                } else {
                    return lead;
                }
            }
        public:
            template <typename InputIterator, typename OutputIterator>
            OutputIterator encode(InputIterator first, InputIterator last, OutputIterator out) {
                for(; first != last; ++first) {
                    encode_one(*first, out);
                }
                flush(out);
                if(in_unicode) *out++ = '-';
                return out;
            }
            template <typename InputIterator, typename OutputIterator>
            OutputIterator decode(InputIterator first, InputIterator last, OutputIterator out) {
                while(first != last) {
                    auto c = decode_one(first, last);
                    if(c == -1u) continue;
                    *out++ = c;
                }
                return out;
            }
        };
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP


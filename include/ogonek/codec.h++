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
// Assume C is a Codec, codec is an instance of C, u is a codepoint, b is a single byte, it is an input iterator
//    C::is_fixed_width | constexpr bool   | true iff is fixed width
//    C::max_width      | constexpr size_t | maximum width
//    C codec;          | C                | creates a new codec
//    C()               | C                | creates a new codec
//    codec.encode(c)   | a range of bytes | encodes a codepoint
//    codec.decode(it)  | codepoint        | decodes a codepoint
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
            template <typename T, std::size_t N>
            struct partial_array_range {
            public:
                template <typename... U>
                partial_array_range(U&&... u)
                : inner {{ std::forward<U>(u)... }}
                , used { sizeof...(U) } {}

                using iterator = typename std::array<T, N>::iterator;
                using const_iterator = typename std::array<T, N>::const_iterator;
                iterator begin() { return inner.begin(); }
                const_iterator begin() const { return inner.begin(); }
                iterator end() { return inner.end(); }
                const_iterator end() const { return inner.end(); }

                T& operator[](std::ptrdiff_t i) { return inner[i]; }
                T const& operator[](std::ptrdiff_t i) const { return inner[i]; }

                std::size_t size() const { return used; }

            private:
                std::array<T, N> inner;
                std::size_t used;
            };
        } // namespace detail

        enum class byte_order {
            big_endian,
            little_endian
        };

        struct utf8 {
            static constexpr bool is_fixed_width = false;
            static constexpr std::size_t max_width = 4;
            detail::partial_array_range<byte, max_width> encode(codepoint c) {
                assert(c < 0x200000); // TODO: invalids are UB?
                if(c < 0x80) {
                    return { byte(c & 0x7F) };
                } else if(c < 0x800) {
                    return { byte(0xC0 | ((c & 0x3C0) >> 6)),
                             byte(0x80 | (c & 0x3F)) };
                } else if(c < 0x10000) {
                    return { byte(0xE0 | ((c & 0xF000) >> 12)),
                             byte(0x80 | ((c & 0xFC0) >> 6)),
                             byte(0x80 | (c & 0x3F)) };
                } else {
                    return { byte(0xF0 | ((c & 0x1C0000) >> 18)),
                             byte(0x80 | ((c & 0x3F000) >> 12)),
                             byte(0x80 | ((c & 0xFC0) >> 6)),
                             byte(0x80 | (c & 0x3F)) };
                }
            }
            template <typename InputIterator>
            codepoint decode(InputIterator& first) {
                codepoint u0 = *first++;
                if((u0 & 0x80) == 0) {
                    return u0;
                } else {
                    codepoint u1 = *first++;
                    if((u0 & 0xE0) != 0xE0) {
                        return ((u0 & 0x1F) << 6) |
                               (u1 & 0x3F);
                    } else {
                        codepoint u2 = *first++;
                        if((u0 & 0xF0) != 0xF0) {
                            return ((u0 & 0x0F) << 12) |
                                   ((u1 & 0x3F) << 6) |
                                   (u2 & 0x3F);
                        } else {
                            codepoint u3 = *first++;
                            return ((u0 & 0x07) << 18) |
                                   ((u1 & 0x3F) << 12) |
                                   ((u2 & 0x3F) << 6) |
                                   (u3 & 0x3F);
                        }
                    }
                } 
            }
        };
        namespace utf16_detail {
            template <byte_order ByteOrder>
            struct endian;
            template <>
            struct endian<byte_order::big_endian> {
                template <typename Array = detail::partial_array_range<byte, 4>>
                static Array make_array(byte a, byte b) {
                    return Array { a, b };
                }
                template <typename Array = detail::partial_array_range<byte, 4>>
                static Array make_array(byte a, byte b, byte c, byte d) {
                    return Array { a, b, c, d };
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    return (t[0] << 8) | t[1];
                }
            };
            template <>
            struct endian<byte_order::little_endian> {
                template <typename Array = detail::partial_array_range<byte, 4>>
                static Array make_array(byte a, byte b) {
                    return Array { b, a };
                }
                template <typename Array = detail::partial_array_range<byte, 4>>
                static Array make_array(byte a, byte b, byte c, byte d) {
                    return Array { b, a, d, c };
                }
                template <typename Array>
                static codepoint make_code_unit(Array t) {
                    return (t[1] << 8) | t[0];
                }
            };
        } // namespace utf16_detail

        template <byte_order ByteOrder>
        struct utf16 {
            static constexpr bool is_fixed_width = false;
            static constexpr std::size_t max_width = 4;
            detail::partial_array_range<byte, max_width> encode(codepoint c) {
                using Array = detail::partial_array_range<byte, max_width>;
                assert(c < 0x200000); // TODO: invalids are UB?
                if(c < 0x10000) {
                    return utf16_detail::endian<ByteOrder>::make_array(
                             (c & 0xFF00) >> 8,
                             c & 0xFF);
                } else {
                    auto normal = c - 0x10000;
                    auto lead = 0xD800 + ((normal & 0xFFC00) >> 10);
                    auto trail = 0xDC00 + (normal & 0x3FF);
                    return utf16_detail::endian<ByteOrder>::make_array(
                             (lead & 0xFF00) >> 8,
                             lead & 0xFF,
                             (trail & 0xFF00) >> 8,
                             trail & 0xFF);
                }
            }
            template <typename InputIterator>
            codepoint decode(InputIterator& first) {
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
                template <typename Array = std::array<byte, 4>>
                static Array make_array(byte a, byte b, byte c, byte d) {
                    return Array {{ a, b, c, d }};
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
                template <typename Array = std::array<byte, 4>>
                static Array make_array(byte a, byte b, byte c, byte d) {
                    return Array {{ d, c, b, a }};
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
        struct utf32 {
            static constexpr bool is_fixed_width = true;
            static constexpr std::size_t max_width = 4;
            std::array<byte, max_width> encode(codepoint c) {
                using Array = std::array<byte, max_width>;
                assert(c < 0x200000); // TODO: invalids are UB?
                return utf32_detail::endian<ByteOrder>::make_array(
                         0,
                         (c & 0x1F0000) >> 16,
                         (c & 0xFF00) >> 8,
                         c & 0xFF);
            }
            template <typename InputIterator>
            codepoint decode(InputIterator& first) {
                std::array<byte, 4> bytes { { *first++, *first++, *first++, *first++ } };
                return utf32_detail::endian<ByteOrder>::make_code_unit(bytes);
            }
        };
        using utf32be = utf32<byte_order::big_endian>;
        using utf32le = utf32<byte_order::little_endian>;
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP


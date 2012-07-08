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

// Models of the ByteOrder concept

#include <cstdint>
#include <array>
#include <type_traits>

#include "types.h++"

namespace ogonek {
    struct big_endian {
    public:
        static std::array<byte, 2> map(std::uint16_t u16) {
            return std::array<byte, 2> {{
                byte((u16 & 0xFF00) >> 8),
                byte((u16 & 0x00FF) >> 0),
            }};
        }
        static std::array<byte, 4> map(std::uint32_t u32) {
            return std::array<byte, 4> {{
                byte((u32 & 0xFF000000) >> 24),
                byte((u32 & 0x00FF0000) >> 16),
                byte((u32 & 0x0000FF00) >> 8),
                byte((u32 & 0x000000FF) >> 0),
            }};
        }
        template <typename DoNotConvert>
        static void map(DoNotConvert) = delete;

    private:
        template <int N>
        struct reader;

    public:
        template <int N, typename InputIterator>
        static typename reader<N>::type unmap(InputIterator it) {
            static_assert(N == 2 || N == 4, "Unmapped type must be have 2 or 4 bytes");
            return reader<N>::read(it);
        }
    };

    template <>
    struct big_endian::reader<2> {
        using type = std::uint16_t;
        template <typename InputIterator>
        static type read(InputIterator it) {
            type b0 = *it++;
            type b1 = *it++;
            return (b0 << 8) | b1;
        }
    };
    template <>
    struct big_endian::reader<4> {
        using type = std::uint32_t;
        template <typename InputIterator>
        static type read(InputIterator it) {
            type b0 = *it++;
            type b1 = *it++;
            type b2 = *it++;
            type b3 = *it++;
            return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        }
    };

    struct little_endian {
    public:
        static std::array<byte, 2> map(std::uint16_t u16) {
            return std::array<byte, 2> {{
                byte((u16 & 0x00FF) >> 0),
                byte((u16 & 0xFF00) >> 8),
            }};
        }
        static std::array<byte, 4> map(std::uint32_t u32) {
            return std::array<byte, 4> {{
                byte((u32 & 0x000000FF) >> 0),
                byte((u32 & 0x0000FF00) >> 8),
                byte((u32 & 0x00FF0000) >> 16),
                byte((u32 & 0xFF000000) >> 24),
            }};
        }
        template <typename DoNotConvert>
        static void map(DoNotConvert) = delete;

    private:
        template <int N>
        struct reader;

    public:
        template <int N, typename InputIterator>
        static typename reader<N>::type unmap(InputIterator it) {
            static_assert(N == 2 || N == 4, "Unmapped type must be have 2 or 4 bytes");
            return reader<N>::read(it);
        }
    };

    template <>
    struct little_endian::reader<2> {
        using type = std::uint16_t;
        template <typename InputIterator>
        static type read(InputIterator it) {
            type b0 = *it++;
            type b1 = *it++;
            return (b1 << 8) | b0;
        }
    };
    template <>
    struct little_endian::reader<4> {
        using type = std::uint32_t;
        template <typename InputIterator>
        static type read(InputIterator it) {
            type b0 = *it++;
            type b1 = *it++;
            type b2 = *it++;
            type b3 = *it++;
            return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
        }
    };
}


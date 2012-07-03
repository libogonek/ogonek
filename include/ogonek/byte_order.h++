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
#include <type_traits>

namespace ogonek {
    struct big_endian {
    public:
        template <typename OutputIterator>
        static void write(OutputIterator&& out, std::uint16_t u16) {
            *out++ = (u16 & 0xFF00) >> 8;
            *out++ = (u16 & 0x00FF) >> 0;
        }
        template <typename OutputIterator>
        static void write(OutputIterator&& out, std::uint32_t u32) {
            *out++ = (u32 & 0xFF000000) >> 24;
            *out++ = (u32 & 0x00FF0000) >> 16;
            *out++ = (u32 & 0x0000FF00) >> 8;
            *out++ = (u32 & 0x000000FF) >> 0;
        }
        template <typename OutputIterator, typename DoNotConvert>
        static void write(OutputIterator, DoNotConvert) = delete;

    private:
        template <typename T>
        struct reader;

    public:
        template <typename T, typename InputIterator>
        static T read(InputIterator&& it) {
            static_assert(std::is_same<T, std::uint16_t>::value || std::is_same<T, std::uint32_t>::value,
                          "Return type must be an unsigned 16- or 32-bit integer");
            return reader<T>::read(it);
        }
    };

    template <>
    struct big_endian::reader<std::uint16_t> {
        template <typename InputIterator>
        static std::uint16_t read(InputIterator& it) {
            std::uint16_t b0 = *it++;
            std::uint16_t b1 = *it++;
            return (b0 << 8) | b1;
        }
    };
    template <>
    struct big_endian::reader<std::uint32_t> {
        template <typename InputIterator>
        static std::uint32_t read(InputIterator& it) {
            std::uint32_t b0 = *it++;
            std::uint32_t b1 = *it++;
            std::uint32_t b2 = *it++;
            std::uint32_t b3 = *it++;
            return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
        }
    };

    struct little_endian {
    public:
        template <typename OutputIterator>
        static void write(OutputIterator&& out, std::uint16_t u16) {
            *out++ = (u16 & 0x00FF) >> 0;
            *out++ = (u16 & 0xFF00) >> 8;
        }
        template <typename OutputIterator>
        static void write(OutputIterator&& out, std::uint32_t u32) {
            *out++ = (u32 & 0x000000FF) >> 0;
            *out++ = (u32 & 0x0000FF00) >> 8;
            *out++ = (u32 & 0x00FF0000) >> 16;
            *out++ = (u32 & 0xFF000000) >> 24;
        }
        template <typename OutputIterator, typename DoNotConvert>
        static void write(OutputIterator, DoNotConvert) = delete;

    private:
        template <typename T>
        struct reader;

    public:
        template <typename T, typename InputIterator>
        static T read(InputIterator&& it) {
            static_assert(std::is_same<T, std::uint16_t>::value || std::is_same<T, std::uint32_t>::value,
                          "Return type must be an unsigned 16- or 32-bit integer");
            return reader<T>::read(it);
        }
    };

    template <>
    struct little_endian::reader<std::uint16_t> {
        template <typename InputIterator>
        static std::uint16_t read(InputIterator& it) {
            std::uint16_t b0 = *it++;
            std::uint16_t b1 = *it++;
            return (b1 << 8) | b0;
        }
    };
    template <>
    struct little_endian::reader<std::uint32_t> {
        template <typename InputIterator>
        static std::uint32_t read(InputIterator& it) {
            std::uint32_t b0 = *it++;
            std::uint32_t b1 = *it++;
            std::uint32_t b2 = *it++;
            std::uint32_t b3 = *it++;
            return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
        }
    };
}


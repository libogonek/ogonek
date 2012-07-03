#include <cstdint>

namespace ogonek {
    struct big_endian {
    public:
        template <typename OutputIterator>
        void write(OutputIterator& out, std::uint16_t u16) {
            *out++ = (u16 & 0xFF00) >> 8;
            *out++ = (u16 & 0x00FF) >> 0;
        }
        template <typename OutputIterator>
        void write(OutputIterator& out, std::uint32_t u32) {
            *out++ = (u32 & 0xFF000000) >> 24;
            *out++ = (u32 & 0x00FF0000) >> 16;
            *out++ = (u32 & 0x0000FF00) >> 8;
            *out++ = (u32 & 0x000000FF) >> 0;
        }
        template <typename OutputIterator, typename DoNotConvert>
        void write(OutputIterator&, DoNotConvert) = delete;

    private:
        template <typename T>
        struct reader;
        template <>
        struct reader<std::uint16_t> {
            template <typename InputIterator>
            static std::uint16_t read(InputIterator& it) {
                std::uint16_t b0 = *it++;
                std::uint16_t b1 = *it++;
                return (b0 << 8) | b1;
            }
        };
        template <>
        struct reader<std::uint32_t> {
            template <typename InputIterator>
            static std::uint32_t read(InputIterator& it) {
                std::uint32_t b0 = *it++;
                std::uint32_t b1 = *it++;
                std::uint32_t b2 = *it++;
                std::uint32_t b3 = *it++;
                return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
            }
        };

    public:
        template <typename T, typename InputIterator>
        T read(InputIterator& it) {
            static_assert(std::is_same<T, std::uint16_t>::value || std::is_same<T, std::uint32_t>::value,
                          "Return type must be an unsigned 16- or 32-bit integer");
            return reader<T>::read(it);
        }
    };

    using codepoint = char32_t;
    using byte = std::uint8_t;
}


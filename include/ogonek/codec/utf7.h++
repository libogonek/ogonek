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

// UTF-7 codec

#ifndef OGONEK_CODEC_UTF7_HPP
#define OGONEK_CODEC_UTF7_HPP

#include "common.h++"
#include "../types.h++"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <iterator>

namespace ogonek {
    namespace codec {
        namespace utf7_detail {
            constexpr char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            unsigned rev_base64(char c) {
                return std::find(std::begin(base64), std::end(base64), c) - std::begin(base64);
            }
        } // namespace detail
        struct utf7 {
            static constexpr bool is_fixed_width = true;
            static constexpr std::size_t max_width = 4;
            static constexpr bool is_stateless = true;
        private:
            struct state {
                bool in_unicode = false;

                template <typename OutputIterator>
                void enter_ascii(OutputIterator& out) {
                    using namespace ogonek::literal;
                    if(in_unicode) {
                        flush(out);
                        *out++ = '-'_u;
                        in_unicode = false;
                    }
                }
                template <typename OutputIterator>
                void enter_unicode(OutputIterator& out) {
                    using namespace ogonek::literal;
                    if(!in_unicode) {
                        flush(out);
                        *out++ = '+'_u;
                        in_unicode = true;
                    }
                }

                std::uint16_t state = 0;
                int state_bits = 0;
                template <typename OutputIterator>
                void encode_one(codepoint c, OutputIterator& out) {
                    using namespace ogonek::literal;
                    if(c == '+'_u) {
                        enter_ascii(out);
                        *out++ = '+'_u;
                        *out++ = '-'_u;
                    } else  if((c >= 0x20_u && c <= 0x7E_u && c != '~'_u && c != '\\'_u)
                               || (c == '\t'_u || c == '\r'_u || c == '\n'_u)) {
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
                            *out++ = utf7_detail::base64[state | (unit >> state_bits)];
                            state = (unit & (0x3F >> (6-state_bits))) << (6-state_bits);
                            if(state_bits == 6) {
                                *out++ = utf7_detail::base64[state];
                                state = 0;
                            }
                            state_bits %= 6;
                        }
                    }
                }
                template <typename OutputIterator>
                void flush(OutputIterator& out) {
                    if(state_bits != 0) {
                        *out++ = utf7_detail::base64[state];
                        state = 0;
                        state_bits = 0;
                    }
                }
                template <typename InputIterator>
                codepoint get_unit(byte& c, InputIterator& first, InputIterator /*TODO use last*/) {
                    state |= c << (10-state_bits);
                    state_bits += 6;
                    for(; state_bits < 10; state_bits += 6) {
                        c = utf7_detail::rev_base64(*first++);
                        state |= c << (10-state_bits);
                    }
                    c = utf7_detail::rev_base64(*first++);
                    codepoint result = state | (c >> (state_bits-10));
                    state = c << (16-(state_bits-10));
                    state_bits -= 10;
                    return result;
                }
                template <typename InputIterator>
                codepoint decode_one(InputIterator& first, InputIterator last) {
                    using namespace ogonek::literal;
                    auto c = *first++;
                    if(in_unicode && c == '-'_u) {
                        if(first == last) return -1;
                        c = *first++;
                        in_unicode = false;
                    } else if(!in_unicode && c == '+'_u) {
                        c = *first++;
                        if(c == '-'_u) return '+'_u;
                        in_unicode = true;
                        state = 0;
                        state_bits = 0;
                    }
                    if(!in_unicode) return c;
                    c = utf7_detail::rev_base64(c);
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
            };
        public:
            template <typename InputIterator, typename OutputIterator>
            OutputIterator encode(InputIterator first, InputIterator last, OutputIterator out) {
                using namespace ogonek::literal;
                state s;
                for(; first != last; ++first) {
                    s.encode_one(*first, out);
                }
                s.flush(out);
                if(s.in_unicode) *out++ = '-'_u;
                return out;
            }
            template <typename InputIterator, typename OutputIterator>
            OutputIterator decode(InputIterator first, InputIterator last, OutputIterator out) {
                state s;
                while(first != last) {
                    auto c = s.decode_one(first, last);
                    if(c == -1u) continue;
                    *out++ = c;
                }
                return out;
            }
        };
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP


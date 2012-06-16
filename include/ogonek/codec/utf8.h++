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

// UTF-8 codec

#ifndef OGONEK_CODEC_UTF8_HPP
#define OGONEK_CODEC_UTF8_HPP

#include "common.h++"
#include "../types.h++"

#include <cassert>
#include <cstddef>
#include <array>

namespace ogonek {
    namespace codec {
        struct utf8 : detail::codec_base<utf8> {
            static constexpr bool is_fixed_width = false;
            static constexpr std::size_t max_width = 4;
            struct state {};

            template <typename OutputIterator>
            void encode_one(codepoint c, OutputIterator& out, state = {}) {
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
            codepoint decode_one(InputIterator& first, InputIterator /*TODO test last*/, state = {}) {
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
    } // namespace codec
} // namespace ogonek

#endif // OGONEK_CODEC_HPP



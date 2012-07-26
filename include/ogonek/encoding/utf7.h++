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

// UTF-7 encoding form

#ifndef OGONEK_ENCODING_UTF7_HPP
#define OGONEK_ENCODING_UTF7_HPP

#include "../types.h++"
#include "utf16.h++"
#include "encoding_scheme.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

namespace ogonek {
    namespace utf7_detail {
        constexpr char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        inline unsigned rev_base64(char c) {
            return std::find(std::begin(base64), std::end(base64), c) - std::begin(base64);
        }
    } // namespace utf7_detail
    struct utf7 {
        using code_unit = byte;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 4; // TODO really four?
        static constexpr bool is_self_synchronizing = false;

        class state {
            friend class utf7;

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
            // TODO: fix weird legacy interface
            template <typename OutputIterator>
            void encode_one(codepoint u, OutputIterator& out) {
                using namespace ogonek::literal;
                if(u == '+'_u) {
                    enter_ascii(out);
                    *out++ = '+'_u;
                    *out++ = '-'_u;
                } else  if((u >= 0x20_u && u <= 0x7E_u && u != '~'_u && u != '\\'_u)
                           || (u == '\t'_u || u == '\r'_u || u == '\n'_u)) {
                    // NOTE: all optional direct characters considered
                    enter_ascii(out);
                    *out++ = u;
                } else {
                    enter_unicode(out);
                    auto src = { u };
                    std::array<byte, 4> u16;
                    auto end = utf16be::encode(src, u16.begin());
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
                    codepoint result;
                    utf16be::decode_one(units, result);
                    return result;
                } else {
                    return lead;
                }
            }
        };

        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator encode(SinglePassRange const& r, OutputIterator out) {
            using namespace ogonek::literal;
            state s {};
            for(auto u : r) {
                s.encode_one(u, out);
            }
            s.flush(out);
            if(s.in_unicode) *out++ = '-'_u;
            return out;
        }
        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out) {
            state s {};
            auto first = boost::begin(r);
            auto last = boost::end(r);
            while(first != last) {
                auto u = s.decode_one(first, last);
                if(u == -1u) continue;
                *out++ = u;
            }
            return out;
        }

        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out, state& s) {
            s.encode_one(u, out);
            return out;
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s) {
            auto it = boost::begin(r);
            out = s.decode_one(it, boost::end(r));
            return it;
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF7_HPP



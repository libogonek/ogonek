// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Encoding/decoding iterators

#ifndef OGONEK_CONSTANTS_HPP
#define OGONEK_CONSTANTS_HPP

namespace ogonek {
    namespace detail {
        constexpr codepoint last_codepoint = 0x10FFFF;

        constexpr codepoint first_lead_surrogate = 0xD800;
        constexpr codepoint last_lead_surrogate = 0xDBFF;

        constexpr codepoint first_trail_surrogate = 0xDC00;
        constexpr codepoint last_trail_surrogate = 0xDFFF;

        constexpr codepoint first_surrogate = first_lead_surrogate;
        constexpr codepoint last_surrogate = last_trail_surrogate;

        constexpr bool is_lead_surrogate(codepoint u) {
            return u >= first_lead_surrogate && u <= last_lead_surrogate;
        }
        constexpr bool is_trail_surrogate(codepoint u) {
            return u >= first_trail_surrogate && u <= last_trail_surrogate;
        }
        constexpr bool is_surrogate(codepoint u) {
            return u >= first_surrogate && u <= last_surrogate;
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_CONSTANTS_HPP


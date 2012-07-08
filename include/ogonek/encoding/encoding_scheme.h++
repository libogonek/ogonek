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

// Generic encoding scheme

#ifndef OGONEK_ENCODING_ENCODING_SCHEME_HPP
#define OGONEK_ENCODING_ENCODING_SCHEME_HPP

#include "../byte_order.h++"
#include "../types.h++"

#include <boost/range/sub_range.hpp>

namespace ogonek {
    template <typename EncodingForm, typename ByteOrder>
    struct encoding_scheme {
        static constexpr bool is_fixed_width = EncodingForm::is_fixed_width;
        static constexpr std::size_t max_width = EncodingForm::max_width * sizeof(EncodingForm::code_unit);
        using state = typename EncodingForm::state;

        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator encode(SinglePassRange const& r, OutputIterator out) {
            state s {};
            for(auto u : r) {
                out = encode_one(u, out, s);
            }
            return out;
        }
        template <typename SinglePassRange, typename OutputIterator>
        static OutputIterator decode(SinglePassRange const& r, OutputIterator out) {
        }

        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out) {
            state s {};
            return encode_one(u, out, s);
        }
        template <typename OutputIterator>
        static OutputIterator encode_one(codepoint u, OutputIterator out, state& s) {
            std::array<typename EncodingForm::code_unit, EncodingForm::max_width> units;
            auto end = EncodingForm::encode_one(*first, units.begin(), s);
            return std::copy(units.begin(), end, out);
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out) {
            state s {};
            return decode_one(first, last, out, s);
        }
        template <typename InputIterator>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s) {
            // TODO
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ENCODING_SCHEME_HPP


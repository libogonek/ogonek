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

// UTF-32 encoding form

#ifndef OGONEK_ENCODING_UTF32_HPP
#define OGONEK_ENCODING_UTF32_HPP

#include "../types.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <utility>

namespace ogonek {
    struct utf32 {
        using code_unit = char32_t;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        struct state {};

        template <typename SinglePassRange>
        static boost::iterator_range<encoding_iterator<utf32, SinglePassRange>> encode(SinglePassRange const& r) {
            return boost::make_iterator_range(
                    encoding_iterator<utf32, SinglePassRange> { boost::begin(r), boost::end(r) },
                    encoding_iterator<utf32, SinglePassRange> { boost::end(r), boost::end(r) });
        }
        template <typename SinglePassRange>
        static boost::iterator_range<decoding_iterator<utf32, SinglePassRange>> decode(SinglePassRange const& r) {
            return boost::make_iterator_range(
                    decoding_iterator<utf32, SinglePassRange> { boost::begin(r), boost::end(r) },
                    decoding_iterator<utf32, SinglePassRange> { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename ValidationCallback>
        static boost::iterator_range<decoding_iterator<utf32, SinglePassRange, ValidationCallback>> decode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    decoding_iterator<utf32, SinglePassRange, ValidationCallback> { boost::begin(r), boost::end(r), callback },
                    decoding_iterator<utf32, SinglePassRange, ValidationCallback> { boost::end(r), boost::end(r), callback });
        }

        static partial_array<code_unit, max_width> encode_one(codepoint u, state&) {
            return {{ u }};
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange, typename ValidationCallback>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, ValidationCallback&& callback) {
            auto first = boost::begin(r);
            auto u = *first++;

            auto is_surrogate = [](codepoint u) { return u >= 0xD800 && u <= 0xDFFF; };

            if(u > 0x10FFFF || is_surrogate(u)) {
                return std::forward<ValidationCallback>(callback)(validation_result::irregular, r, out);
            }

            out = u;
            return { first, boost::begin(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF32_HPP


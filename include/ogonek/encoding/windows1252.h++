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

// Windows-1252 encoding form

#ifndef OGONEK_ENCODING_WINDOWS1252_HPP
#define OGONEK_ENCODING_WINDOWS1252_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/types.h++>
#include <ogonek/validation.h++>
#include <ogonek/detail/partial_array.h++>

#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>

namespace ogonek {
    struct windows1252 {
        using code_unit = char;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        static constexpr codepoint replacement_character = U'?';
        struct state {};

        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<windows1252, Iterator, ValidationPolicy>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }
        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<windows1252, Iterator, ValidationPolicy>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        static constexpr byte first_difference_latin1 = 0x80;
        static constexpr byte last_difference_latin1 = 0x9F;
        static constexpr byte number_difference_latin1 = last_difference_latin1 - first_difference_latin1 + 1;
        static constexpr codepoint difference_latin1_mapping[] = {
            0x20AC,    -1u, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
            0x02C6, 0x2030, 0x0160, 0x2039, 0x0152,    -1u, 0x017D,    -1u,
               -1u, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
            0x02DC, 0x2122, 0x0161, 0x203A, 0x0153,    -1u, 0x017E, 0x0178,
        };
        static bool is_different_from_latin1(byte b) {
            return b >= first_difference_latin1 && b <= last_difference_latin1;
        }
        static codepoint get_encoded(byte b) {
            if(is_different_from_latin1(b)) {
                return difference_latin1_mapping[b - first_difference_latin1];
            } else {
                return b;
            }
        }
        static byte find_decoded(codepoint u) {
            auto begin = std::begin(difference_latin1_mapping);
            auto end = std::end(difference_latin1_mapping);
            auto it = std::find(begin, end, u);
            if(it == end) {
                return static_cast<byte>(-1);
            }
            return it - begin + first_difference_latin1;
        }

        static detail::coded_character<windows1252> encode_one(codepoint u, state&, skip_validation_t) {
            if(u <= 0xFF && !is_different_from_latin1(u)) {
                return { static_cast<code_unit>(u & 0xFF) };
            } else {
                auto b = find_decoded(u);
                return { static_cast<code_unit>(b) };
            }
        }

        template <typename ValidationPolicy>
        static detail::coded_character<windows1252> encode_one(codepoint u, state& s, ValidationPolicy) {
            if(u <= 0xFF && !is_different_from_latin1(u)) {
                return { static_cast<code_unit>(u & 0xFF) };
            } else {
                auto b = find_decoded(u);
                if(b != static_cast<byte>(-1)) {
                    return { static_cast<code_unit>(b) };
                }
            }
            return ValidationPolicy::template apply_encode<windows1252>(u, s);
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, skip_validation_t) {
            auto first = boost::begin(r);
            out = get_encoded(*first++);
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange, typename ValidationPolicy>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, ValidationPolicy) {
            auto first = boost::begin(r);
            byte b = *first++;
            auto u = get_encoded(b);
            if(u == -1u) {
                return ValidationPolicy::template apply_decode<windows1252>(r, s, out);
            }
            out = u;
            return { first, boost::end(r) };
        }
    };
    constexpr codepoint windows1252::difference_latin1_mapping[windows1252::number_difference_latin1];
} // namespace ogonek

#endif // OGONEK_ENCODING_WINDOWS1252_HPP



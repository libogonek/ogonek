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

// ASCII encoding form

#ifndef OGONEK_ENCODING_ASCII_HPP
#define OGONEK_ENCODING_ASCII_HPP

#include "iterator.h++"
#include "../types.h++"
#include "../validation.h++"

#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>

namespace ogonek {
    struct ascii {
        using code_unit = char;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        struct state {};

        template <typename SinglePassRange, typename ValidationCallback,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<ascii, Iterator, ValidationCallback>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r), callback },
                    EncodingIterator { boost::end(r), boost::end(r), callback });
        }
        template <typename SinglePassRange, typename ValidationCallback,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<ascii, Iterator, ValidationCallback>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r), callback },
                    DecodingIterator { boost::end(r), boost::end(r), callback });
        }

        static partial_array<code_unit, max_width> encode_one(codepoint u, state&) {
            if(u <= 0x7F) {
                return { static_cast<code_unit>(u & 0x7F) };
            } else {
                return {};
            }
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, decltype(skip_validation)) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange, typename ValidationCallback>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, ValidationCallback&& callback) {
            auto first = boost::begin(r);
            byte b = *first++;
            if(b > 0x7F) {
                return std::forward<ValidationCallback>(callback)(validation_result::illegal, r, out);
            }
            out = b;
            return { first, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF8_HPP



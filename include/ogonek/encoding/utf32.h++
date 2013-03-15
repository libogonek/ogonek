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

// UTF-32 encoding form

#ifndef OGONEK_ENCODING_UTF32_HPP
#define OGONEK_ENCODING_UTF32_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/types.h++>
#include <ogonek/error.h++>
#include <ogonek/detail/partial_array.h++>
#include <ogonek/detail/constants.h++>

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

        template <typename SinglePassRange, typename ErrorHandler,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<utf32, Iterator, ErrorHandler>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ErrorHandler) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename ErrorHandler,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<utf32, Iterator, ErrorHandler>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ErrorHandler) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename ErrorHandler>
        static detail::coded_character<utf32> encode_one(code_point u, state&, ErrorHandler) {
            return { u };
        }
        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, code_point& out, state&, skip_validation_t) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
        template <typename SinglePassRange, typename ErrorHandler>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, code_point& out, state& s, ErrorHandler) {
            auto first = boost::begin(r);
            auto u = *first++;

            if(u > detail::last_code_point || detail::is_surrogate(u)) {
                return ErrorHandler::template apply_decode<utf32>(r, s, out);
            }

            out = u;
            return { first, boost::begin(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF32_HPP


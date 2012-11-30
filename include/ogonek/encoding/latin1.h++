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

// ISO-8859-1 encoding form

#ifndef OGONEK_ENCODING_LATIN1_HPP
#define OGONEK_ENCODING_LATIN1_HPP

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
    struct latin1 {
        using code_unit = char;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        static constexpr codepoint replacement_character = U'?';
        struct state {};

        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<latin1, Iterator, ValidationPolicy>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }
        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<latin1, Iterator, ValidationPolicy>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        static detail::coded_character<latin1> encode_one(codepoint u, state&, skip_validation_t) {
            if(u < 0xFF) {
                return { static_cast<code_unit>(u & 0xFF) };
            } else {
                return {};
            }
        }

	template <typename ValidationPolicy>
        static detail::coded_character<latin1> encode_one(codepoint u, state& s, ValidationPolicy) {
            if(u <= 0xFF) {
                return { static_cast<code_unit>(u & 0xFF) };
            } else {
                return ValidationPolicy::template apply_encode<latin1>(u, s);
            }
        }

        template <typename SinglePassRange, typename ValidationPolicy>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, ValidationPolicy) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_LATIN1_HPP


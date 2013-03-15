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

// Narrow encoding form

#ifndef OGONEK_ENCODING_NARROW_HPP
#define OGONEK_ENCODING_NARROW_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/types.h++>
#include <ogonek/validation.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <cwchar>
#include <cuchar>
#include <array>
#include <utility>
#include <cstddef>

namespace ogonek {
    struct narrow {
    private:
        static constexpr std::size_t error = -1;
        static constexpr std::size_t incomplete = -2;

    public:
        using code_unit = char;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 4;
        static constexpr bool is_self_synchronizing = false;
        using state = std::mbstate_t;

        template <typename SinglePassRange, typename ErrorHandler,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<narrow, Iterator, ErrorHandler>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ErrorHandler) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename ErrorHandler,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<narrow, Iterator, ErrorHandler>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ErrorHandler) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        static partial_array<code_unit, max_width> encode_one(codepoint u, state& s) {
            std::array<code_unit, max_width> units;
            auto r = std::c32rtomb(units.data(), u, &s);
            if(r != error) {
                return { units, r };
            } else {
                throw validation_error();
                // TODO FFS, else what?
            }
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, skip_validation_t) {
            auto it = boost::begin(r);
            std::array<code_unit, max_width> units = { *it++, };
            int n = 1;
            int r;
            while((r = mbrtoc32(&out, units.data(), n, &s)) == incomplete) {
                units[n++] = *it++;
            }
            return { it, boost::end(r) };
        }
        template <typename SinglePassRange, typename ErrorHandler>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, ErrorHandler&& callback) {
            auto it = boost::begin(r);
            std::array<code_unit, max_width> units = { *it++, };
            int n = 1;
            int r;
            while((r = mbrtoc32(&out, units.data(), n, &s)) == incomplete) {
                units[n++] = *it++;
            }
            if(r == error) {
                return ErrorHandler::template apply_decode<narrow>(r, s, out);
            }
            return { it, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_NARROW_HPP


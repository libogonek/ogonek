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

// UTF-16 encoding form

#ifndef OGONEK_ENCODING_NARROW_HPP
#define OGONEK_ENCODING_NARROW_HPP

#include "iterator.h++"
#include "../types.h++"
#include "../validation.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <cwchar>
#include <cuchar>
#include <array>
#include <utility>

namespace ogonek {
    struct narrow {
        using code_unit = char;
        static constexpr bool is_fixed_width = false;
        static constexpr std::size_t max_width = 4;
        static constexpr bool is_self_synchronizing = false;
        using state = std::mbstate_t;

        template <typename SinglePassRange, typename ValidationCallback,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<utf16, Iterator, ValidationCallback>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r), callback },
                    EncodingIterator { boost::end(r), boost::end(r), callback });
        }

        template <typename SinglePassRange, typename ValidationCallback,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<utf16, Iterator, ValidationCallback>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationCallback&& callback) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r), callback },
                    DecodingIterator { boost::end(r), boost::end(r), callback });
        }

        static partial_array<code_unit, max_width> encode_one(codepoint u, state& s) {
            std::array<code_unit, max_width> units;
            auto r = std::c32rtomb(units.data(), u, &s);
            if(r != -1) {
                return { units, r };
            } else {
                throw validation_error();
                // FFS, else what?
            }
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, decltype(skip_validation)) {
            auto it = boost::begin(r);
            std::array<code_unit, max_width> units = { *it++, };
            int n = 1;
            int r;
            while((r = mbrtoc32(&out, units.data(), n, &s)) == -2) {
                units[n++] = *it++;
            }
            return { it, boost::end(r) };
        }
        template <typename SinglePassRange, typename ValidationCallback>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, ValidationCallback&& callback) {
            auto it = boost::begin(r);
            std::array<code_unit, max_width> units = { *it++, };
            int n = 1;
            int r;
            while((r = mbrtoc32(&out, units.data(), n, &s)) == -2) {
                units[n++] = *it++;
            }
            if(r == -1) {
                return std::forward<ValidationCallback>(callback)(validation_result::illegal, r, out);
            }
            return { it, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_NARROW_HPP


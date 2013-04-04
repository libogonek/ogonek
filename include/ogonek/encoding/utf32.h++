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
#include <ogonek/detail/ranges.h++>
#include <ogonek/detail/partial_array.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/encoding/detail/encoded_character.h++>

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

        template <typename ErrorHandler>
        static detail::encoded_character<utf32> encode_one(code_point u, state&, ErrorHandler) {
            return { u };
        }
        template <typename Range>
        static boost::sub_range<Range> decode_one(Range const& r, code_point& out, state&, assume_valid_t) {
            auto first = boost::begin(r);
            out = *first++;
            return { first, boost::end(r) };
        }
        template <typename Range, typename ErrorHandler>
        static boost::sub_range<Range> decode_one(Range const& r, code_point& out, state& s, ErrorHandler) {
            auto first = boost::begin(r);
            auto u = *first++;

            if(u > detail::last_code_point || detail::is_surrogate(u)) {
                return ErrorHandler::template apply_decode<utf32>(r, s, out);
            }

            out = u;
            return { first, boost::begin(r) };
        }
    };
    
    namespace detail {
        inline null_terminated_range<char32_t const> as_code_point_range(char32_t const* sequence, assume_valid_t) {
            return { sequence, {} };
        }

        template <typename ErrorHandler>
        null_terminated_utf32<ErrorHandler> as_code_point_range(char32_t const* sequence, ErrorHandler) {
            using source_iterator = null_terminated_range_iterator<char32_t const>;
            using result_iterator = decoding_iterator<utf32, source_iterator, ErrorHandler>;
            return {
                result_iterator(source_iterator(sequence), source_iterator()),
                result_iterator(source_iterator(), source_iterator())
            };
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_ENCODING_UTF32_HPP


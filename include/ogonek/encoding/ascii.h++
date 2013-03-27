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

// ASCII encoding form

#ifndef OGONEK_ENCODING_ASCII_HPP
#define OGONEK_ENCODING_ASCII_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/types.h++>
#include <ogonek/error.h++>
#include <ogonek/detail/ranges.h++>
#include <ogonek/detail/partial_array.h++>
#include <ogonek/detail/encoded_character.h++>

#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>

namespace ogonek {
    struct ascii {
    private:
        static constexpr auto last_ascii_value = 0x7Fu;

    public:
        using code_unit = char;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        static constexpr code_point replacement_character = U'?';
        struct state {};

        static detail::encoded_character<ascii> encode_one(code_point u, state&, assume_valid_t) {
            return { static_cast<code_unit>(u) };
        }

        template <typename ErrorHandler>
        static detail::encoded_character<ascii> encode_one(code_point u, state& s, ErrorHandler) {
            if(u <= last_ascii_value) {
                return { static_cast<code_unit>(u) };
            } else {
                return ErrorHandler::template apply_encode<ascii>(u, s);
            }
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
            byte b = *first++;
            if(b > last_ascii_value) {
                return  ErrorHandler::template apply_decode<ascii>(r, s, out);
            }
            out = b;
            return { first, boost::end(r) };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ASCII_HPP



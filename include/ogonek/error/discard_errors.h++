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

// Error handler that discards bad data

#ifndef OGONEK_DISCARD_ERRORS_HPP
#define OGONEK_DISCARD_ERRORS_HPP

#include <ogonek/error/error_handler.h++>
#include <ogonek/types.h++>
#include <ogonek/traits.h++>
#include <ogonek/encoding/detail/encoded_character.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <iterator>

namespace ogonek {
    // Strategy for discarding erroneous data
    struct discard_errors_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, EncodingState<EncodingForm>&, code_point&) {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::encoded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>&) {
            return {};
        }
    } constexpr discard_errors = {};
} // namespace ogonek

#endif // OGONEK_DISCARD_ERRORS_HPP


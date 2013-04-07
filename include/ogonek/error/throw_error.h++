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

// Error handler that throws

#ifndef OGONEK_ERROR_THROW_ERROR_HPP
#define OGONEK_ERROR_THROW_ERROR_HPP

#include <ogonek/error/error_handler.h++>
#include <ogonek/error/unicode_error.h++>
#include <ogonek/types.h++>
#include <ogonek/encoding/traits.h++>
#include <ogonek/detail/container/encoded_character.h++>
#include <ogonek/detail/container/optional.h++>

#include <boost/range/sub_range.hpp>

namespace ogonek {
    //! {callable}
    //! Error handler that throws upon discovering invalid data
    struct throw_error_t : error_handler {
        template <typename Sequence, typename EncodingForm>
        decode_correction<Sequence> handle(decode_error<Sequence, EncodingForm> const& error) {
            throw error;
        }

        template <typename Sequence, typename EncodingForm>
        encode_correction<Sequence, EncodingForm> handle(encode_error<Sequence, EncodingForm> const& error) {
            throw error;
        }

        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const&, EncodingState<EncodingForm>&, code_point&) {
            throw unicode_error();
        }
        template <typename EncodingForm>
        static detail::encoded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>&) {
            throw unicode_error();
        }
    };
    //! {object}
    //! A default instance of [function:throw_error_t].
    constexpr throw_error_t throw_error = {};
} // namespace ogonek

#endif // OGONEK_ERROR_THROW_ERROR_HPP

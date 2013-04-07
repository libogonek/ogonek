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

// Error handler that uses a replacement character

#ifndef OGONEK_ERROR_REPLACE_ERRORS_HPP
#define OGONEK_ERROR_REPLACE_ERRORS_HPP

#include <ogonek/error/error_handler.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/types.h++>
#include <ogonek/encoding/traits.h++>

#include <wheels/meta.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <iterator>
#include <type_traits>

namespace ogonek {
    //! {callable}
    //! Error handler that replaces invalid data with a replacement character
    struct replace_errors_t : error_handler {
        template <typename Sequence, typename EncodingForm>
        decode_correction<Sequence> handle(decode_error<Sequence, EncodingForm> const& error) {
            error.source.pop_front();
            return { error.source, U'\xFFFD' };
        }

        template <typename Sequence, typename EncodingForm>
        encode_correction<Sequence, EncodingForm> handle(encode_error<Sequence, EncodingForm> const& error) {
            auto replacement = EncodingForm::encode_one(replacement_character<EncodingForm>(), error.state, assume_valid);
            return { error.source, replacement };
        }

        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, EncodingState<EncodingForm>&, code_point& out) {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::encoded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>& s) {
            return EncodingForm::encode_one(replacement_character<EncodingForm>(), s, assume_valid);
        }
    };
    //! {object}
    //! A default instance of [function:replace_errors_t].
    constexpr replace_errors_t replace_errors = {};
} // namespace ogonek

#endif // OGONEK_ERROR_REPLACE_ERRORS_HPP

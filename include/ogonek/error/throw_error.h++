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

#ifndef OGONEK_THROW_ERROR_HPP
#define OGONEK_THROW_ERROR_HPP

#include <ogonek/error/error_handler.h++>
#include <ogonek/types.h++>
#include <ogonek/traits.h++>
#include <ogonek/encoding/detail/encoded_character.h++>

#include <boost/range/sub_range.hpp>

#include <stdexcept>

namespace ogonek {
    //! Exception that is thrown when validation fails
    struct unicode_error : std::exception { // TODO Boost.Exception
        char const* what() const throw() override {
            return "Unicode validation failed";
        }
    };

    //! Strategy for throwing upon discovering invalid data
    struct throw_error_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const&, EncodingState<EncodingForm>&, code_point&) {
            throw unicode_error();
        }
        template <typename EncodingForm>
        static detail::encoded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>&) {
            throw unicode_error();
        }
    } constexpr throw_error = {};
} // namespace ogonek

#endif // OGONEK_THROW_ERROR_HPP


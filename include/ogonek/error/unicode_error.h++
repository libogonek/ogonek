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

// Exception for Unicode errors

#ifndef OGONEK_ERROR_UNICODE_ERROR_HPP
#define OGONEK_ERROR_UNICODE_ERROR_HPP

#include <ogonek/encoding/traits.h++>

#ifdef OGONEK_BOOST_EXCEPTION
#include <boost/exception/exception.hpp>
#endif // OGONEK_BOOST_EXCEPTION

#include <stdexcept>

namespace ogonek {
    //! {exception}
    //! *Thrown*: when validation fails during an encoding/decoding operation
    struct unicode_error
    : virtual std::exception
#ifdef OGONEK_BOOST_EXCEPTION
    , virtual boost::exception
#endif // OGONEK_BOOST_EXCEPTION
    {
        //! {function}
        //! *Returns*: a UTF-8 string describing the error.
        char const* what() const throw() override {
            return u8"ill-formed Unicode string";
        }
    };

    template <typename Sequence, typename EncodingForm>
    struct encode_error : virtual unicode_error {
        encode_error(Sequence source, EncodingState<EncodingForm> state)
        : source(std::move(source)), state(state) {}

        Sequence source;
        EncodingState<EncodingForm> state;
    };

    template <typename Sequence, typename EncodingForm>
    struct decode_error : virtual unicode_error {
        decode_error(Sequence source, EncodingState<EncodingForm> state)
        : source(std::move(source)), state(state) {}

        Sequence source;
        EncodingState<EncodingForm> state;
    };
} // namespace ogonek

#endif // OGONEK_ERROR_UNICODE_ERROR_HPP

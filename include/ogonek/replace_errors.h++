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

#ifndef OGONEK_REPLACE_ERRORS_HPP
#define OGONEK_REPLACE_ERRORS_HPP

#include <ogonek/error_handler.h++>
#include <ogonek/types.h++>
#include <ogonek/detail/encoded_character.h++>

#include <wheels/meta.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <iterator>
#include <type_traits>

namespace ogonek {
    namespace detail {
        struct has_custom_replacement_character_impl {
            template <typename EncodingForm>
            wheels::Bool<true, decltype(EncodingForm::replacement_character)> static test(int);
            template <typename>
            std::false_type static test(...);
        };
        template <typename EncodingForm>
        using has_custom_replacement_character = wheels::TraitOf<has_custom_replacement_character_impl, EncodingForm>;

        template <typename EncodingForm, bool Custom = has_custom_replacement_character<EncodingForm>::value>
        struct replacement_character
        : std::integral_constant<code_point, U'\xFFFD'> {};
        template <typename EncodingForm>
        struct replacement_character<EncodingForm, true>
        : std::integral_constant<code_point, EncodingForm::replacement_character> {};
    } // namespace detail

    //! Strategy for replacing invalid data with a replacement character
    struct replace_errors_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, EncodingState<EncodingForm>&, code_point& out) {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::encoded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>& s) {
            return EncodingForm::encode_one(detail::replacement_character<EncodingForm>(), s, assume_valid);
        }
    } constexpr replace_errors = {};
} // namespace ogonek

#endif // OGONEK_REPLACE_ERRORS_HPP


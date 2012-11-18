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

// Validation

#ifndef OGONEK_VALIDATION_HPP
#define OGONEK_VALIDATION_HPP

#include "detail/partial_array.h++"

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <cstdint>
#include <iterator>
#include <type_traits>

namespace ogonek {
    struct validation_error : std::exception { // TODO Boost.Exception
        char const* what() const throw() override {
            return "Unicode validation failed";
        }
    };

    struct skip_validation_t {} constexpr skip_validation = {};

    struct {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const&, typename EncodingForm::state&, codepoint&) {
            throw validation_error();
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(codepoint, typename EncodingForm::state&) {
            throw validation_error();
        }
    } constexpr throw_validation_error = {};

    namespace detail {
        template <typename T>
        struct sfinae_true : std::true_type {};
        struct has_custom_replacement_character_impl {
            template <typename EncodingForm>
            sfinae_true<decltype(EncodingForm::replacement_character)> test(int);
            template <typename>
            std::false_type test(...);
        };
        template <typename EncodingForm>
        using has_custom_replacement_character = decltype(has_custom_replacement_character_impl::test<EncodingForm>(0));

        template <typename EncodingForm, bool Custom = has_custom_replacement_character<EncodingForm>::value>
        struct replacement_character {
            static constexpr codepoint value = U'\xFFFD';
        };
        template <typename EncodingForm>
        struct replacement_character<EncodingForm, true> {
            static constexpr codepoint value = EncodingForm::replacement_character;
        };
    } // namespace detail

    struct {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, typename EncodingForm::state&, codepoint& out) {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(codepoint u, typename EncodingForm::state& s) {
            return EncodingForm::encode_one(detail::replacement_character<EncodingForm>::value, s, skip_validation);
        }
    } constexpr use_replacement_character = {};

    struct {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, typename EncodingForm::state&, codepoint&) {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(codepoint, typename EncodingForm::state&) {
            return {};
        }
    } constexpr ignore_errors = {};
} // namespace ogonek

#endif // OGONEK_VALIDATION_HPP


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

// Validation

#ifndef OGONEK_VALIDATION_HPP
#define OGONEK_VALIDATION_HPP

#include <ogonek/detail/partial_array.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <cstdint>
#include <iterator>
#include <type_traits>

namespace ogonek {
    //! Exception that is thrown when validation fails
    struct validation_error : std::exception { // TODO Boost.Exception
        char const* what() const throw() override {
            return "Unicode validation failed";
        }
    };
    
    namespace detail {
        struct validation_strategy {
            struct is_validation_strategy : std::true_type {};
        };
        template <typename T>
        using is_validation_strategy = typename T::is_validation_strategy;
    } // namespace detail

    //! Policy for skipping validation
    struct skip_validation_t : detail::validation_strategy {} constexpr skip_validation = {};

    //! Policy for throwing upon discovering invalid data
    struct throw_validation_error_t : detail::validation_strategy {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const&, typename EncodingForm::state&, code_point&) {
            throw validation_error();
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, typename EncodingForm::state&) {
            throw validation_error();
        }
    } constexpr throw_validation_error = {};

    namespace detail {
        template <typename T>
        struct sfinae_true : std::true_type {};
        struct has_custom_replacement_character_impl {
            template <typename EncodingForm>
            sfinae_true<decltype(EncodingForm::replacement_character)> static test(int);
            template <typename>
            std::false_type static test(...);
        };
        template <typename EncodingForm>
        using has_custom_replacement_character = decltype(has_custom_replacement_character_impl::test<EncodingForm>(0));

        template <typename EncodingForm, bool Custom = has_custom_replacement_character<EncodingForm>::value>
        struct replacement_character {
            static constexpr code_point value = U'\xFFFD';
        };
        template <typename EncodingForm>
        struct replacement_character<EncodingForm, true> {
            static constexpr code_point value = EncodingForm::replacement_character;
        };
    } // namespace detail

    //! Policy for replacing invalid data with a replacement character
    struct use_replacement_character_t : detail::validation_strategy {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, typename EncodingForm::state&, code_point& out) {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, typename EncodingForm::state& s) {
            return EncodingForm::encode_one(detail::replacement_character<EncodingForm>::value, s, skip_validation);
        }
    } constexpr use_replacement_character = {};

    // Policy for discarding erroneous data
    struct discard_errors_t : detail::validation_strategy {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, typename EncodingForm::state&, code_point&) {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, typename EncodingForm::state&) {
            return {};
        }
    } constexpr discard_errors = {};

    constexpr auto default_validation = throw_validation_error;
} // namespace ogonek

#endif // OGONEK_VALIDATION_HPP


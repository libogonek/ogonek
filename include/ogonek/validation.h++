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

#include <ogonek/traits.h++>
#include <ogonek/detail/partial_array.h++>

#include <wheels/meta.h++>

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <cstdint>
#include <iterator>
#include <type_traits>

namespace ogonek {
    //! Exception that is thrown when validation fails
    struct unicode_error : std::exception { // TODO Boost.Exception
        char const* what() const throw() override {
            return "Unicode validation failed";
        }
    };
    
    namespace detail {
        struct error_handler {
            struct is_error_handler : std::true_type {};
        };
        
        struct error_handler_tester {
            template <typename T, typename = typename T::is_error_handler>
            std::true_type static test(int);
            template <typename T>
            std::false_type static test(...);
        };
        template <typename T>
        using is_error_handler = wheels::TraitOf<error_handler_tester, T>;
    } // namespace detail

    //! Strategy for skipping validation
    struct skip_validation_t : detail::error_handler {} constexpr skip_validation = {};

    //! Strategy for throwing upon discovering invalid data
    struct throw_error_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const&, EncodingState<EncodingForm>&, code_point&) {
            throw unicode_error();
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>&) {
            throw unicode_error();
        }
    } constexpr throw_error = {};

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

    //! Strategy for replacing invalid data with a replacement character
    struct use_replacement_character_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, EncodingState<EncodingForm>&, code_point& out) {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>& s) {
            return EncodingForm::encode_one(detail::replacement_character<EncodingForm>::value, s, skip_validation);
        }
    } constexpr use_replacement_character = {};

    // Strategy for discarding erroneous data
    struct discard_errors_t : detail::error_handler {
        template <typename EncodingForm, typename Range>
        static boost::sub_range<Range> apply_decode(boost::sub_range<Range> const& source, EncodingState<EncodingForm>&, code_point&) {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
        template <typename EncodingForm>
        static detail::coded_character<EncodingForm> apply_encode(code_point, EncodingState<EncodingForm>&) {
            return {};
        }
    } constexpr discard_errors = {};

    constexpr auto default_error_handler = throw_error;
} // namespace ogonek

#endif // OGONEK_VALIDATION_HPP


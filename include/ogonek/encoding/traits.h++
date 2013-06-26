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

// Encoding traits

#ifndef OGONEK_ENCODING_TRAITS_HPP
#define OGONEK_ENCODING_TRAITS_HPP

#include <ogonek/types.h++>

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    template <typename EncodingForm>
    using CodeUnit = typename EncodingForm::code_unit;
    template <typename EncodingForm>
    using EncodingState = typename EncodingForm::state;
    template <typename EncodingForm>
    using is_stateless = std::is_empty<EncodingState<EncodingForm>>;

    namespace detail {
        struct has_custom_replacement_character_impl {
            template <typename EncodingForm>
            wheels::meta::DependOn<wheels::meta::True, decltype(EncodingForm::replacement_character)> static test(int);
            template <typename>
            std::false_type static test(...);
        };
        template <typename EncodingForm>
        using has_custom_replacement_character = wheels::meta::TraitOf<has_custom_replacement_character_impl, EncodingForm>;
    } // namespace detail

    template <typename EncodingForm,
              bool Custom = detail::has_custom_replacement_character<EncodingForm>::value>
    struct replacement_character : std::integral_constant<code_point, U'\xFFFD'> {};

    template <typename EncodingForm>
    struct replacement_character<EncodingForm, true>
    : std::integral_constant<code_point, EncodingForm::replacement_character> {};
} // namespace ogonek

#endif // OGONEK_ENCODING_TRAITS_HPP


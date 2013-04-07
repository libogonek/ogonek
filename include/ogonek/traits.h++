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

// Trait classes

#ifndef OGONEK_TRAITS_HPP
#define OGONEK_TRAITS_HPP

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    namespace detail {
        struct always_validated_tester {
            template <typename UnicodeSequence>
            wheels::Bool<UnicodeSequence::validated> static test(int);
            template <typename UnicodeSequence>
            wheels::Bool<false> static test(...);
        };
    } // namespace detail
    template <typename T>
    using always_validated = wheels::TraitOf<detail::always_validated_tester, T>;

    namespace detail {
        template <typename NormalForm>
        struct always_normalized_tester {
            template <typename UnicodeSequence>
            std::is_same<typename UnicodeSequence::normal_form, NormalForm> static test(int);
            template <typename UnicodeSequence>
            wheels::Bool<false> static test(...);
        };
    } // namespace detail
    template <typename NormalForm, typename T>
    using always_normalized = wheels::TraitOf<detail::always_normalized_tester<NormalForm>, T>;

    namespace detail {
        struct always_casefolded_tester {
            template <typename UnicodeSequence>
            wheels::Bool<UnicodeSequence::casefolded> static test(int);
            template <typename UnicodeSequence>
            wheels::Bool<false> static test(...);
        };
    } // namespace detail
    template <typename T>
    using always_casefolded = wheels::TraitOf<detail::always_casefolded_tester, T>;
} // namespace ogonek

#endif // OGONEK_TRAITS_HPP

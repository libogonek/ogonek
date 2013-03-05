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

#ifndef OGONEK_TRAITS_HPP
#define OGONEK_TRAITS_HPP

#include <type_traits>

namespace ogonek {
    template <typename EncodingForm>
    using CodeUnit = typename EncodingForm::code_unit;
    template <typename EncodingForm>
    using EncodingState = typename EncodingForm::state;
    template <typename EncodingForm>
    using is_stateless = std::is_empty<EncodingState<EncodingForm>>;
} // namespace ogonek

#endif // OGONEK_TRAITS_HPP

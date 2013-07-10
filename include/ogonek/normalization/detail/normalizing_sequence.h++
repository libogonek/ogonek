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

// Normalizing sequences

#ifndef OGONEK_DETAIL_NORMALIZING_SEQUENCE_HPP
#define OGONEK_DETAIL_NORMALIZING_SEQUENCE_HPP

#include <wheels/meta/invoke.h++>

namespace ogonek {
    namespace detail {
        template <typename NormalizationForm, typename Iterator>
        class normalizing_sequence_impl;

        template <typename NormalizationForm, typename Iterator>
        using normalizing_sequence = wheels::meta::Invoke<normalizing_sequence_impl<NormalizationForm, Iterator>>;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_NORMALIZING_ITERATOR_HPP


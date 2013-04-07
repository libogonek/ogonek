// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Trait that tests if a type is already decayed

#ifndef OGONEK_DETAIL_META_IS_DECAYED_HPP
#define OGONEK_DETAIL_META_IS_DECAYED_HPP

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    namespace detail {
        //! {trait}
        //! *Returns*: `true` if decaying `T` yields `T`.
        template <typename T>
        struct is_decayed : std::is_same<wheels::Decay<T>, T> {};
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_META_IS_DECAYED_HPP

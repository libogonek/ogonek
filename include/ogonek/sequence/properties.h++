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

// Static sequence property set

#ifndef OGONEK_SEQUENCE_PROPERTY_SET_HPP
#define OGONEK_SEQUENCE_PROPERTY_SET_HPP

#include <wheels/meta.h++>

#include <type_traits>

namespace ogonek {
    namespace detail {
        struct well_formed : std::true_type {};

        template <typename WellFormed = std::false_type,
                  typename... Tail // TODO add more properties
                 >
        struct properties {
            using type = properties<WellFormed, Tail...>;

            using is_well_formed = WellFormed;
        };

        template <typename Props>
        struct is_well_formed : Props::is_well_formed {};

        template <typename Props, typename P>
        struct set_property;
        template <typename Props, typename P>
        using SetProperty = typename set_property<P, Props>::type;

        template <typename Old, typename... T>
        struct set_property<well_formed, properties<Old, T...>> {
            using type = properties<well_formed, T...>;
        };

        template <typename Props, typename... New>
        struct set_properties { using type = Props; };
        template <typename Props, typename H, typename... T>
        struct set_properties<Props, H, T...> : set_properties<SetProperty<H, Props>, T...> {};
        template <typename Props, typename... New>
        using SetProperties = typename set_properties<Props, New...>::type;

        struct sequence_properties_impl {
            template <typename T>
            typename T::sequence_properties static test(int);
            template <typename...>
            properties<> static test(...);
        };
        template <typename T>
        struct sequence_properties : wheels::TraitOf<sequence_properties_impl, T> {};

        template <typename T>
        using SequenceProperties = wheels::Invoke<sequence_properties<T>>;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_SEQUENCE_PROPERTY_SET_HPP

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

// Static sequence properties

#ifndef OGONEK_SEQUENCE_PROPERTIES_HPP
#define OGONEK_SEQUENCE_PROPERTIES_HPP

#include <taussig/primitives.h++>
#include <taussig/traits.h++>

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

            using has_well_formed = WellFormed;
        };

        template <typename Props>
        struct has_well_formed : wheels::Unqualified<Props>::has_well_formed {};

        template <typename Props, typename P>
        struct set_property;
        template <typename Props, typename P>
        using SetProperty = typename set_property<P, Props>::type;

        template <typename Old, typename... T>
        struct set_property<properties<Old, T...>, well_formed> {
            using type = properties<well_formed, T...>;
        };

        template <typename Props, typename... New>
        struct set_properties { using type = Props; };
        template <typename Props, typename H, typename... T>
        struct set_properties<Props, H, T...> : set_properties<SetProperty<H, Props>, T...> {};
        template <typename Props, typename... New>
        using SetProperties = typename set_properties<Props, New...>::type;

        template <typename... Props>
        using MakeProperties = SetProperties<properties<>, Props...>;

        struct sequence_properties_impl {
            template <typename T>
            typename T::sequence_properties static test(int);
            template <typename...>
            properties<> static test(...);
        };
        template <typename T>
        struct sequence_properties : wheels::TraitOf<sequence_properties_impl, wheels::Unqualified<T>> {};

        template <typename T>
        using SequenceProperties = wheels::Invoke<sequence_properties<T>>;

        template<typename... Props>
        struct ogonek_sequence : seq::true_sequence {
            using sequence_properties = MakeProperties<Props...>;
        };

        template <typename Sequence>
        struct is_well_formed : has_well_formed<SequenceProperties<Sequence>> {};
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_SEQUENCE_PROPERTIES_HPP

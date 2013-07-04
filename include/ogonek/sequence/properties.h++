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
        // Property storage: note how possible properties are bounded
        template <typename WellFormed = wheels::meta::False,
                  typename... Tail // TODO add more properties
                 >
        struct properties {
            using type = properties<WellFormed, Tail...>;

            using has_well_formed = WellFormed;
        };

        // Set a single property
        template <typename Props, typename P>
        struct set_property;
        template <typename Props, typename P>
        using SetProperty = wheels::meta::Invoke<set_property<Props, P>>;

        // well-formed
        struct well_formed : wheels::meta::True {};
        template <typename Old, typename... T>
        struct set_property<properties<Old, T...>, well_formed> {
            using type = properties<well_formed, T...>;
        };

        // ill-formed (removes the well-formed property when set)
        struct ill_formed : wheels::meta::False {};
        template <typename Old, typename... T>
        struct set_property<properties<Old, T...>, ill_formed> {
            using type = properties<ill_formed, T...>;
        };

        //Set many properties at once
        template <typename Props, typename... New>
        struct set_properties { using type = Props; };
        template <typename Props, typename H, typename... T>
        struct set_properties<Props, H, T...> : set_properties<SetProperty<Props, H>, T...> {};
        template <typename Props, typename... H, typename... T>
        struct set_properties<Props, properties<H...>, T...> : set_properties<Props, H..., T...> {};
        template <typename Props, typename... New>
        using SetProperties = typename set_properties<Props, New...>::type;

        // Make a new property storage from the give properties
        template <typename... Props>
        using MakeProperties = SetProperties<properties<>, Props...>;

        // Retrieve the properties of a sequence (defaults to no properties if no advertisement present)
        struct sequence_properties_impl {
            template <typename T>
            typename T::sequence_properties static test(int);
            template <typename...>
            properties<> static test(...);
        };
        template <typename T>
        struct sequence_properties : wheels::meta::TraitOf<sequence_properties_impl, wheels::meta::Unqual<T>> {};
        template <typename T>
        using SequenceProperties = wheels::meta::Invoke<sequence_properties<T>>;

        template <typename Sequence>
        struct is_well_formed : SequenceProperties<Sequence>::has_well_formed {};

        // TODO delete me
        template <typename... Props>
        struct ogonek_sequence_old : seq::true_sequence {
            using sequence_properties = MakeProperties<Props...>;
        };

        // Sequence tagged with ogonek properties
        template <typename Seq, typename Props>
        struct ogonek_sequence : seq::true_sequence, Seq {
            ogonek_sequence() = default;
            template <typename SeqF,
                      wheels::meta::DisableIf<wheels::meta::is_related<ogonek_sequence<Seq, Props>, SeqF>>...>
            ogonek_sequence(SeqF&& s) : Seq(std::forward<SeqF>(s)) {}

            using sequence_properties = Props;
        };

        // Remove all properties from a sequence (also unwraps if ogonek_sequence)
        template <typename Seq>
        Seq&& remove_properties(Seq&& s) {
            return std::forward<Seq>(s);
        }
        template <typename Seq, typename Props>
        Seq remove_properties(ogonek_sequence<Seq, Props> const& s) {
            return s;
        }
        template <typename Seq, typename Props>
        Seq remove_properties(ogonek_sequence<Seq, Props>&& s) {
            return std::move(s);
        }

        // Add properties to a sequence (wrap in ogonek_sequence if foreign)
        template <typename... Props, typename Seq,
                  typename ExistingProps = SequenceProperties<Seq>,
                  typename NewProps = SetProperties<ExistingProps, Props...>,
                  typename Result = ogonek_sequence<wheels::meta::Unqual<Seq>, NewProps>>
        Result add_properties(Seq&& s) {
            return { remove_properties(std::forward<Seq>(s)) };
        }
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_SEQUENCE_PROPERTIES_HPP

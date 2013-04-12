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

// Additional iterator-related traits

#ifndef OGONEK_DETAIL_META_ITERATOR_HPP
#define OGONEK_DETAIL_META_ITERATOR_HPP

#include <wheels/meta.h++>

#include <iterator>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ogonek {
    namespace detail {
        //! {metafunction}
        //! *Requires*: `T` is a model of [concept:Iterator] [soft].
        //! *Returns*: the iterator category of `T`.
        template <typename T>
        using IteratorCategory = typename std::iterator_traits<T>::iterator_category;

        struct is_iterator_test {
            template <typename T, typename Cat>
            std::is_base_of<Cat, IteratorCategory<T>> static test(int);
            template <typename...>
            std::false_type static test(...);
        };
        //! {trait}
        //! *Returns*: `true` if `T` is a model of [concept:Iterator] with category `Cat`;
        //             `false` otherwise.
        template <typename T, typename Cat = std::input_iterator_tag>
        struct is_iterator : wheels::TraitOf<is_iterator_test, T, Cat> {};

        namespace result_of {
            template <typename T>
            using begin = decltype(std::begin(std::declval<T>()));
            template <typename T>
            using end = decltype(std::end(std::declval<T>()));
        } // namespace result_of

        struct has_begin_end_test {
            template <typename T, typename Cat>
            wheels::All<
                std::is_same<result_of::begin<T>, result_of::end<T>>,
                is_iterator<result_of::begin<T>, Cat>
            > static test(int);
            template <typename...>
            std::false_type static test(...);
        };
        //! {trait}
        //! *Returns*: `true` if `T` has `begin()` and `end()` member functions
        //             that return the same model of [concept:Iterator] with category `Cat`;
        //             `false` otherwise.
        template <typename T, typename Cat = std::input_iterator_tag>
        struct has_begin_end : wheels::TraitOf<has_begin_end_test, T, Cat> {};

        template <typename T, typename Cat>
        struct is_iterator_pair_impl : std::false_type {};

        template <typename I, typename Cat>
        struct is_iterator_pair_impl<std::pair<I, I>, Cat> : is_iterator<I, Cat> {};

        template <typename T, typename Cat = std::input_iterator_tag>
        struct is_iterator_pair : is_iterator_pair_impl<wheels::Unqualified<T>, Cat> {};

        //! {metafunction}
        //! *Requires*: `std::begin` can be called with `T&` [soft].
        //! *Returns*: the type returned by calling `std::begin` with `T&`.
        template <typename T>
        using IteratorOf = result_of::begin<T&>;
        //! {metafunction}
        //! *Requires*: `std::begin` can be called with `T const&` [soft].
        //! *Returns*: the type returned by calling `std::begin` with `T const&`.
        template <typename T>
        using ConstIteratorOf = IteratorOf<T const&>;
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_META_ITERATOR_HPP



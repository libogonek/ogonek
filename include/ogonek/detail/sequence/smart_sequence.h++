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

// Smart sequences

#ifndef OGONEK_DETAIL_SEQUENCE_SMART_SEQUENCE_HPP
#define OGONEK_DETAIL_SEQUENCE_SMART_SEQUENCE_HPP

#include <wheels/meta.h++>

#include <type_traits>
#include <cstddef>

namespace ogonek {
    namespace detail {
        //! {concept}
        //! A sequence with a smart interface based on Andrei Alexandrescu's ideas.
        // concept SmartSequence : std::smart_sequence
        // requires Copyable {
            //! {trait}
            //! The type of values in this sequence.
            // typename value_type;

            //! {trait}
            //! The type of references to this sequence.
            //! *Note*: this type may not be a reference if the sequence is not persistent.
            //     typename reference;

            //! {function}
            //! *Returns*: `true` if the sequence `s` has no elements.
            // bool empty() const;

            //! {function}
            //! *Requires*: `!empty()`.
            //! *Returns*: the first element of this sequence.
            // reference front() const;

            //! {function}
            //! *Requires*: `!empty()`.
            //! *Effects*: skips the first element in this sequence.
            // void pop_front();

            //! {function}
            //! *Returns*: a sequence in the current state of this sequence.
            // SmartSequence save() const;
        // };

        //! {tag}
        //! *Effects*: marks a derived type as a [concept:SmartSequence].
        struct smart_sequence {};

        //! {trait}
        //! *Returns*: `true` if `S` is a [concept:SmartSequence]; `false` otherwise.
        template <typename S>
        struct is_smart_sequence : std::is_base_of<smart_sequence, wheels::Unqualified<S>> {};
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_DETAIL_SEQUENCE_SMART_SEQUENCE_HPP

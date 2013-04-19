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

// Decoding sequences

#ifndef OGONEK_ENCODING_DECODE_HPP
#define OGONEK_ENCODING_DECODE_HPP

#include <ogonek/sequence/properties.h++>
#include <ogonek/encoding/traits.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/meta/is_decayed.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <taussig/primitive.h++>
#include <taussig/as_sequence.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <tuple>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        struct decoding_sequence_impl : detail::ogonek_sequence<detail::well_formed> {
            using value_type = code_point;
            using reference = value_type;

            template <typename SequenceF, typename ErrorHandlerF>
            decoding_sequence_impl(SequenceF&& s, ErrorHandlerF&& handler)
            : s(std::forward<SequenceF>(s)), handler(std::forward<ErrorHandlerF>(handler)) {}

            bool empty() const { return seq::empty(s); }
            reference front() const {
                code_point u;
                auto st = state;
                std::tie(std::ignore, u) = EncodingForm::decode_one_ex(seq::save(s), st, handler);
                return u;
            }
            decoding_sequence_impl save() const {
                return *this;
            }
            void pop_front() {
                std::tie(s, std::ignore) = EncodingForm::decode_one_ex(seq::save(s), state, handler);
            }
            decoding_sequence_impl before(decoding_sequence_impl const& other) const {
                return { seq::before(s, other.s), state, handler };
            }

        private:
            template <typename SequenceF, typename ErrorHandlerF>
            decoding_sequence_impl(SequenceF&& s, EncodingState<EncodingForm> state, ErrorHandlerF&& handler)
            : s(std::forward<SequenceF>(s)), state(state), handler(std::forward<ErrorHandlerF>(handler)) {}

            Sequence s;
            EncodingState<EncodingForm> state {};
            ErrorHandler handler;
        };
        static_assert(seq::detail::is_native_sequence<decoding_sequence_impl<utf32, std::pair<char const*, char const*>, int>>(), "decoding sequence is a native sequence");
    } // namespace detail
    //! {class}
    //! A sequence wrapper that lazily decodes the underlying sequence
    template <typename EncodingForm, typename Sequence, typename ErrorHandler>
    using decoding_sequence = detail::decoding_sequence_impl<EncodingForm, wheels::Decay<Sequence>, wheels::Decay<ErrorHandler>>;

    namespace result_of {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        using decode = wheels::Conditional<detail::is_well_formed<Sequence>,
                            Sequence,
                            decoding_sequence<EncodingForm, seq::result_of::as_sequence<Sequence>, ErrorHandler>
                          >;
    } // namespace result_of

    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler,
              wheels::DisableIf<detail::is_well_formed<Sequence>>...>
    result_of::decode<EncodingForm, Sequence, ErrorHandler> decode(Sequence&& s, ErrorHandler&& h) {
        return { seq::as_sequence(std::forward<Sequence>(s)), std::forward<ErrorHandler>(h) };
    }
    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler,
              wheels::EnableIf<detail::is_well_formed<Sequence>>...>
    Sequence decode(Sequence&& s, ErrorHandler&&) {
        return std::forward<Sequence>(s);
    }
} // namespace ogonek

#endif // OGONEK_ENCODING_DECODE_HPP

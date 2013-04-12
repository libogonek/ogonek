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

// Encoding sequences

#ifndef OGONEK_ENCODING_ENCODE_HPP
#define OGONEK_ENCODING_ENCODE_HPP

#include <ogonek/sequence/seq.h++>
#include <ogonek/sequence/properties.h++>
#include <ogonek/encoding/traits.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/meta/is_decayed.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <tuple>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename Sequence, typename EncodingForm, typename ErrorHandler>
        struct encoding_sequence_impl : detail::native_sequence<detail::well_formed> {
            using value_type = CodeUnit<EncodingForm>;
            using reference = value_type;

            template <typename SequenceF, typename ErrorHandlerF>
            encoding_sequence_impl(SequenceF&& s, ErrorHandlerF&& handler)
            : s(std::forward<SequenceF>(s)), handler(std::forward<ErrorHandlerF>(handler)) {
                encode_next();
            }

            bool empty() const { return seq::empty(s) && is_depleted(); }
            reference front() const { return encoded[current]; }
            void pop_front() { if(++current == encoded.size()) encode_next(); }

        private:
            Sequence s;
            EncodingState<EncodingForm> state {};
            detail::encoded_character<EncodingForm> encoded {};
            ErrorHandler handler;
            std::size_t current;

            static constexpr auto depleted = -1u;
            bool is_depleted() const { return current == depleted; }

            void encode_next() {
                if(seq::empty(s)) {
                    current = depleted;
                } else {
                    auto&& u = seq::front(s);
                    encoded = encode_validated(u, ErrorHandler{});
                    seq::pop_front(s);
                    current = 0;
                }
            }

            detail::encoded_character<EncodingForm> encode_validated(code_point u, assume_valid_t) {
                return EncodingForm::encode_one(u, state, assume_valid);
            }

            template <typename ErrorHandler1>
            detail::encoded_character<EncodingForm> encode_validated(code_point u, ErrorHandler1) {
                if(u > detail::last_code_point || detail::is_surrogate(u)) {
                    encode_error<Sequence, EncodingForm> error { s, state };
                    detail::encoded_character<EncodingForm> result;
                    std::tie(s, result) = handler.handle(error);
                    return result;
                } else {
                    return EncodingForm::encode_one(u, state, ErrorHandler1{});
                }
            }
        };
    } // namespace detail

    //! {class}
    //! A sequence wrapper that lazily encodes the underlying sequence
    template <typename Sequence, typename EncodingForm, typename ErrorHandler>
    using encoding_sequence = detail::encoding_sequence_impl<wheels::Decay<Sequence>, EncodingForm, wheels::Decay<ErrorHandler>>;

    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler,
              wheels::DisableIf<detail::is_well_formed<Sequence>>...>
    encoding_sequence<Sequence, EncodingForm, ErrorHandler> encode_ex(Sequence&& s, ErrorHandler&& h) {
        return { std::forward<Sequence>(s), std::forward<ErrorHandler>(h) };
    }
    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler,
              wheels::EnableIf<detail::is_well_formed<Sequence>>...>
    Sequence encode_ex(Sequence&& s, ErrorHandler&&) {
        return std::forward<Sequence>(s);
    }
    namespace result_of {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        using encode_ex = decltype((encode_ex<EncodingForm>)(std::declval<Sequence>(), std::declval<ErrorHandler>()));
    } // namespace result_of
} // namespace ogonek

#endif // OGONEK_ENCODING_ENCODE_HPP

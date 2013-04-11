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

// Encoding/decoding sequences

#ifndef OGONEK_ENCODING_SEQUENCE_HPP
#define OGONEK_ENCODING_SEQUENCE_HPP

#include <ogonek/sequence/traits.h++>
#include <ogonek/sequence/properties.h++>
#include <ogonek/encoding/traits.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/meta/is_decayed.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <wheels/meta.h++>

#include <type_traits>
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

    namespace result_of {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        using encode_ex = encoding_sequence<Sequence, EncodingForm, ErrorHandler>;
    } // namespace result_of
    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler>
    result_of::encode_ex<EncodingForm, Sequence, ErrorHandler> encode_ex(Sequence&& s, ErrorHandler&& h) {
        return { std::forward<Sequence>(s), std::forward<ErrorHandler>(h) };
    }

    namespace detail {
        template <typename Sequence, typename EncodingForm, typename ErrorHandler>
        struct decoding_sequence_impl : detail::native_sequence<detail::well_formed> {
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
            void pop_front() {
                std::tie(s, std::ignore) = EncodingForm::decode_one_ex(seq::save(s), state, handler);
            }

            Sequence s;
            EncodingState<EncodingForm> state {};
            ErrorHandler handler;
        };
    } // namespace detail
    //! {class}
    //! A sequence wrapper that lazily decodes the underlying sequence
    template <typename Sequence, typename EncodingForm, typename ErrorHandler>
    using decoding_sequence = detail::decoding_sequence_impl<wheels::Decay<Sequence>, EncodingForm, wheels::Decay<ErrorHandler>>;


    namespace result_of {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        using decode_ex = decoding_sequence<Sequence, EncodingForm, ErrorHandler>;
    } // namespace result_of
    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler>
    result_of::decode_ex<EncodingForm, Sequence, ErrorHandler> decode_ex(Sequence s, ErrorHandler h) {
        return { std::forward<Sequence>(s), std::forward<ErrorHandler>(h) };
    }
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


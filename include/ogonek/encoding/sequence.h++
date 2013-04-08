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
#include <ogonek/encoding/traits.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/meta/is_decayed.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <utility>

namespace ogonek {
    //! {class}
    //! A sequence wrapper that lazily encodes the underlying sequence
    template <typename Sequence, typename EncodingForm, typename ErrorHandler>
    struct encoding_sequence : detail::simple_sequence {
        static_assert(detail::is_decayed<Sequence>(), "Sequence must be a decayed type");

        using value_type = CodeUnit<EncodingForm>;
        using reference = value_type;

        encoding_sequence(Sequence s, ErrorHandler handler)
        : s(std::move(s)), handler(std::move(handler)) {
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

    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler>
    encoding_sequence<Sequence, EncodingForm, ErrorHandler> encode_ex(Sequence s, ErrorHandler h) {
        return { s, h };
    }

    template <typename Sequence, typename EncodingForm, typename ErrorHandler>
    struct decoding_sequence : detail::simple_sequence {
        static_assert(detail::is_decayed<Sequence>(), "Sequence must be a decayed type");

        using value_type = code_point;
        using reference = value_type;

        decoding_sequence(Sequence s, ErrorHandler handler)
        : s(std::move(s)), handler(std::move(handler)) {}

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

    template <typename EncodingForm,
              typename Sequence, typename ErrorHandler>
    decoding_sequence<Sequence, EncodingForm, ErrorHandler> decode_ex(Sequence s, ErrorHandler h) {
        return { s, h };
    }
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


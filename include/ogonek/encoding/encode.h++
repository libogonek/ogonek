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

#include <taussig/primitive.h++>
#include <taussig/as_sequence.h++>

#include <ogonek/sequence/properties.h++>

#include <ogonek/encoding/traits.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/error/default_error_handler.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <wheels/meta.h++>

#include <type_traits>
#include <tuple>
#include <utility>

namespace ogonek {
    namespace detail {
        template <typename EncodingForm, typename Sequence, typename ErrorHandler>
        struct encoding_sequence_impl : detail::ogonek_sequence<detail::well_formed> {
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
            encoding_sequence_impl save() const { return *this; }
            encoding_sequence_impl before(encoding_sequence_impl const& other) const {
                return *this; // TODO ahahah
            }

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
                    std::tie(s, state, result) = handler.handle(error);
                    return result;
                } else {
                    return EncodingForm::encode_one(u, state, ErrorHandler1{});
                }
            }
        };
        static_assert(seq::is_native_sequence<encoding_sequence_impl<utf32, std::pair<char const*, char const*>, int>>(), "encoding sequence is a native sequence");
    } // namespace detail

    //! {class}
    //! A sequence wrapper that lazily encodes the underlying sequence
    template <typename EncodingForm, typename Sequence, typename ErrorHandler>
    using encoding_sequence = detail::encoding_sequence_impl<EncodingForm, wheels::Decay<Sequence>, wheels::Decay<ErrorHandler>>;

    namespace result_of {
        template <typename EncodingForm, typename Source, typename ErrorHandler = default_error_handler_t>
        using encode = encoding_sequence<EncodingForm, seq::result_of::as_sequence<Source>, ErrorHandler>;
    } // namespace result_of

    // TODO optimisations
    template <typename EncodingForm,
              typename Source, typename ErrorHandler>
    result_of::encode<EncodingForm, Source, ErrorHandler> encode(Source&& s, ErrorHandler&& h) {
        return { seq::as_sequence(std::forward<Source>(s)), std::forward<ErrorHandler>(h) };
    }

    template <typename EncodingForm,
              typename Source>
    result_of::encode<EncodingForm, Source> encode(Source&& s) {
        return (encode<EncodingForm>)(std::forward<Source>(s), default_error_handler);
    }
} // namespace ogonek

#endif // OGONEK_ENCODING_ENCODE_HPP

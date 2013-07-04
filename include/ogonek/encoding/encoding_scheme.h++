// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Generic encoding scheme

#ifndef OGONEK_ENCODING_ENCODING_SCHEME_HPP
#define OGONEK_ENCODING_ENCODING_SCHEME_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/sequence/properties.h++>
#include <ogonek/types.h++>
#include <ogonek/detail/ranges.h++>
#include <ogonek/detail/container/partial_array.h++>
#include <ogonek/detail/container/encoded_character.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <cstdint>
#include <iterator>
#include <type_traits>

namespace ogonek {
    class little_endian;
    namespace detail {
        template <typename T, std::size_t N = sizeof(T)>
        struct uint;
        template <typename T>
        struct uint<T, 1> { using type = std::uint8_t; };
        template <typename T>
        struct uint<T, 2> { using type = std::uint16_t; };
        template <typename T>
        struct uint<T, 4> { using type = std::uint32_t; };
        template <typename T>
        struct uint<T, 8> { using type = std::uint64_t; };
        template <typename T>
        using Uint = typename uint<T>::type;

        template <typename ByteOrder, typename Integer, typename Sequence>
        struct ordered_byte_sequence : ogonek_sequence_old<> {
            using value_type = Integer;
            using reference = value_type;

            bool empty() const { return seq::empty(inner); };
            Integer front() const {
                Integer i;
                ByteOrder::unmap(inner, i);
                return i;
            }
            void pop_front() {
                Integer dummy;
                inner = ByteOrder::unmap(inner, dummy);
            }
            ordered_byte_sequence before(ordered_byte_sequence const& that) const {
                return inner.before(that.inner);
            }

            ordered_byte_sequence save() const { return *this; }

            ordered_byte_sequence(Sequence const& seq) : inner(seq) {}
            ordered_byte_sequence(Sequence&& seq) : inner(std::move(seq)) {}

            Sequence inner;
        };
        static_assert(seq::is_true_sequence<ordered_byte_sequence<little_endian, unsigned, std::pair<char const*, char const*>>>(), "");
    } // namespace detail

    template <typename EncodingForm, typename ByteOrder>
    struct encoding_scheme {
        static constexpr bool is_fixed_width = EncodingForm::is_fixed_width;
        static constexpr std::size_t max_width = EncodingForm::max_width * sizeof(typename EncodingForm::code_unit);
        using state = typename EncodingForm::state;
        using code_unit = ogonek::byte;

        template <typename ErrorHandler>
        static detail::encoded_character<encoding_scheme<EncodingForm, ByteOrder>> encode_one(code_point u, state& s, ErrorHandler) {
            std::array<byte, max_width> result;
            auto encoded = EncodingForm::encode_one(u, s, ErrorHandler{});
            auto out = result.begin();
            for(auto it = encoded.begin(); it != encoded.end(); ++it) {
                auto bytes = ByteOrder::map(static_cast<detail::Uint<CodeUnit<EncodingForm>>>(*it));
                out = std::copy(bytes.begin(), bytes.end(), out);
            }
            return { result, std::size_t(out - result.begin()) };
        }
        template <typename Sequence, typename ErrorHandler>
        static std::pair<Sequence, code_point> decode_one_ex(Sequence s, state& state, ErrorHandler&& handler) {
            using code_unit_sequence = detail::ordered_byte_sequence<ByteOrder, CodeUnit<EncodingForm>, Sequence>;
            code_unit_sequence seq { s };
            auto result = EncodingForm::decode_one_ex(seq, state, std::forward<ErrorHandler>(handler));
            return { result.first.inner, result.second };
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ENCODING_SCHEME_HPP

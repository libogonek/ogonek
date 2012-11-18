// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
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

#include "iterator.h++"
#include "../byte_order.h++"
#include "../types.h++"
#include "../detail/partial_array.h++"

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
    namespace encoding_scheme_detail {
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

        template <typename ByteOrder, typename Integer, typename Iterator>
        struct byte_ordered_iterator // TODO: support input iterators
        : boost::iterator_facade<
            byte_ordered_iterator<ByteOrder, Integer, Iterator>,
            Integer,
            std::input_iterator_tag,
            Integer
        > {
            byte_ordered_iterator(Iterator it) : it(it) {}
            Integer dereference() const {
                Integer i;
                ByteOrder::unmap(it, i);
                return i;
            }
            bool equal(byte_ordered_iterator const& that) const {
                return it == that.it;
            }
            void increment() {
                Integer dummy;
                it = ByteOrder::unmap(it, dummy);
            }

            Iterator it;
        };

        template <typename ByteOrder, typename Integer, typename SinglePassRange>
        using byte_ordered_range = boost::iterator_range<
                                       byte_ordered_iterator<
                                           ByteOrder,
                                           Integer,
                                           typename boost::range_iterator<SinglePassRange>::type>>;
    } // namespace encoding_scheme_detail

    template <typename EncodingForm, typename ByteOrder>
    struct encoding_scheme {
        static constexpr bool is_fixed_width = EncodingForm::is_fixed_width;
        static constexpr std::size_t max_width = EncodingForm::max_width * sizeof(typename EncodingForm::code_unit);
        using state = typename EncodingForm::state;
        using code_unit = ogonek::byte;

        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<encoding_scheme<EncodingForm, ByteOrder>, Iterator, ValidationPolicy>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<encoding_scheme<EncodingForm, ByteOrder>, Iterator, ValidationPolicy>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename ValidationPolicy>
        static detail::coded_character<encoding_scheme<EncodingForm, ByteOrder>> encode_one(codepoint u, state& s, ValidationPolicy) {
            std::array<byte, max_width> result;
            auto encoded = EncodingForm::encode_one(u, s, ValidationPolicy{});
            auto out = result.begin();
            for(auto it = encoded.begin(); it != encoded.end(); ++it) {
                auto bytes = ByteOrder::map(static_cast<encoding_scheme_detail::Uint<CodeUnit<EncodingForm>>>(*it));
                out = std::copy(bytes.begin(), bytes.end(), out);
            }
            return { result, std::size_t(out - result.begin()) };
        }
        template <typename SinglePassRange, typename ValidationPolicy>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, ValidationPolicy) {
            using code_unit_range = encoding_scheme_detail::byte_ordered_range<ByteOrder, typename EncodingForm::code_unit, SinglePassRange>;
            using iterator = typename boost::range_iterator<code_unit_range>::type;
            code_unit_range range {
                iterator { boost::begin(r) }, iterator { boost::end(r) }
            };
            auto remaining = EncodingForm::decode_one(range, out, s, ValidationPolicy{});
            return { remaining.begin().it, r.end() };
        }
    };
    class utf16;
    class utf32;
    using utf16be = encoding_scheme<utf16, big_endian>;
    using utf16le = encoding_scheme<utf16, little_endian>;
    using utf32be = encoding_scheme<utf32, big_endian>;
    using utf32le = encoding_scheme<utf32, little_endian>;
} // namespace ogonek

#endif // OGONEK_ENCODING_ENCODING_SCHEME_HPP


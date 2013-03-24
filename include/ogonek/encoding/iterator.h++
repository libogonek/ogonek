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

// Encoding/decoding iterators

#ifndef OGONEK_ENCODING_ITERATOR_HPP
#define OGONEK_ENCODING_ITERATOR_HPP

#include <ogonek/traits.h++>
#include <ogonek/types.h++>
#include <ogonek/error.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/partial_array.h++>
#include <ogonek/detail/encoded_character.h++>
#include <ogonek/detail/ranges.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <array>
#include <initializer_list>
#include <cstddef>

namespace ogonek {
    namespace detail {
        class decoding_iterator_access;
    } // namespace detail
    
    template <typename EncodingForm, typename Iterator, typename ErrorHandler>
    struct encoding_iterator
    : boost::iterator_facade<
        encoding_iterator<EncodingForm, Iterator, ErrorHandler>,
        CodeUnit<EncodingForm>,
        std::input_iterator_tag, // TODO
        CodeUnit<EncodingForm>
      > {
    public:
        encoding_iterator(Iterator first, Iterator last)
        : first(std::move(first)), last(std::move(last)) { encode_next(); }

        CodeUnit<EncodingForm> dereference() const {
            return encoded[current];
        }
        bool equal(encoding_iterator const& that) const {
            return (first == that.first && current == that.current)
                || (first == last && that.first == that.last
                    && current == depleted && that.current == depleted);
        }
        void increment() {
            ++current;
            if(current == encoded.size()) {
                encode_next();
            }
        }

    private:
        static constexpr std::size_t depleted = -1;
        void encode_next() {
            if(first != last) {
                auto u = *first++;
                encoded = encode_validated(u, ErrorHandler{});
                current = 0;
            } else {
                current = depleted;
            }
        }

        detail::encoded_character<EncodingForm> encode_validated(code_point u, assume_valid_t) {
            return EncodingForm::encode_one(u, state, assume_valid);
        }

        template <typename ErrorHandler1>
        detail::encoded_character<EncodingForm> encode_validated(code_point u, ErrorHandler1) {
            if(u > detail::last_code_point || detail::is_surrogate(u)) {
                return ErrorHandler1::template apply_encode<EncodingForm>(u, state);
            } else {
                return EncodingForm::encode_one(u, state, ErrorHandler1{});
            }
        }

        Iterator first, last;
        EncodingState<EncodingForm> state {};
        detail::encoded_character<EncodingForm> encoded {};
        std::size_t current;
    };

    template <typename EncodingForm, typename Iterator, typename ErrorHandler>
    struct decoding_iterator
    : boost::iterator_facade<
        decoding_iterator<EncodingForm, Iterator, ErrorHandler>,
        code_point,
        std::input_iterator_tag, // TODO
        code_point
      > {
    public:
        decoding_iterator(Iterator first, Iterator last)
        : first(std::move(first)), last(std::move(last)) {}

        code_point dereference() const {
            code_point u;
            auto s = state;
            EncodingForm::decode_one(boost::sub_range<range>(first, last), u, s, ErrorHandler{});
            return u;
        }
        bool equal(decoding_iterator const& that) const {
            return first == that.first || (first == last && that.first == that.last);
        }
        void increment() {
            code_point dummy;
            first = EncodingForm::decode_one(boost::sub_range<range>(first, last), dummy, state, ErrorHandler{}).begin();
        }

    private:
        using range = boost::iterator_range<Iterator>;

        friend class detail::decoding_iterator_access;
        
        Iterator first, last;
        EncodingState<EncodingForm> state {};
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


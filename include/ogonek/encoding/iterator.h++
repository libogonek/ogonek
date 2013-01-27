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
#include <ogonek/validation.h++>
#include <ogonek/detail/constants.h++>
#include <ogonek/detail/partial_array.h++>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <array>
#include <initializer_list>
#include <cstddef>

namespace ogonek {
    template <typename EncodingForm, typename Iterator, typename ValidationPolicy>
    struct encoding_iterator
    : boost::iterator_facade<
        encoding_iterator<EncodingForm, Iterator, ValidationPolicy>,
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
                encoded = encode_validated(u, ValidationPolicy{});
                current = 0;
            } else {
                current = depleted;
            }
        }

        detail::coded_character<EncodingForm> encode_validated(codepoint u, skip_validation_t) {
            return EncodingForm::encode_one(u, state, skip_validation);
        }

        template <typename ValidationPolicy1>
        detail::coded_character<EncodingForm> encode_validated(codepoint u, ValidationPolicy1) {
            if(u > detail::last_codepoint || detail::is_surrogate(u)) {
                return ValidationPolicy1::template apply_encode<EncodingForm>(u, state);
            } else {
                return EncodingForm::encode_one(u, state, ValidationPolicy1{});
            }
        }

        Iterator first, last;
        typename EncodingForm::state state {};
        detail::coded_character<EncodingForm> encoded {};
        std::size_t current;
    };

    template <typename EncodingForm, typename Iterator, typename ValidationPolicy>
    struct decoding_iterator
    : boost::iterator_facade<
        decoding_iterator<EncodingForm, Iterator, ValidationPolicy>,
        codepoint,
        std::input_iterator_tag, // TODO
        codepoint
      > {
    public:
        decoding_iterator(Iterator first, Iterator last)
        : first(std::move(first)), last(std::move(last)) {}

        codepoint dereference() const {
            codepoint u;
            auto s = state;
            EncodingForm::decode_one(boost::sub_range<range>(first, last), u, s, ValidationPolicy{});
            return u;
        }
        bool equal(decoding_iterator const& that) const {
            return first == that.first || (first == last && that.first == that.last);
        }
        void increment() {
            codepoint dummy;
            first = EncodingForm::decode_one(boost::sub_range<range>(first, last), dummy, state, ValidationPolicy{}).begin();
        }

    private:
        using range = boost::iterator_range<Iterator>;

        Iterator first, last;
        typename EncodingForm::state state {};
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


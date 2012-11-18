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

// Encoding/decoding iterators

#ifndef OGONEK_ENCODING_ITERATOR_HPP
#define OGONEK_ENCODING_ITERATOR_HPP

#include "../traits.h++"
#include "../types.h++"
#include "../validation.h++"
#include "../detail/constants.h++"
#include "../detail/partial_array.h++"

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>

#include <initializer_list>
#include <array>
#include <algorithm>

namespace ogonek {
    namespace detail {
        inline bool is_surrogate(codepoint u) { return u >= first_surrogate && u <= last_surrogate; } // TODO pull out
    } // namespace detail

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
        : first(first), last(last) { encode_next(); }

        CodeUnit<EncodingForm> dereference() const {
            return encoded[current];
        }
        bool equal(encoding_iterator const& that) const {
            return (first == that.first && current == that.current)
                || (first == last && that.first == that.last
                    && current == -1 && that.current == -1);
        }
        void increment() {
            ++current;
            if(current == static_cast<int>(encoded.size())) {
                encode_next();
            }
        }

    private:
        void encode_next() {
            if(first != last) {
                auto u = *first++;
                encode_validated(u, ValidationPolicy{});
                current = 0;
            } else {
                current = -1;
            }
        }

        void encode_validated(codepoint u, skip_validation_t const&) {
            encoded = EncodingForm::encode_one(u, state, skip_validation);
        }

        template <typename ValidationPolicy1>
        void encode_validated(codepoint u, ValidationPolicy1 const&) {
            if(u > detail::last_codepoint || detail::is_surrogate(u)) {
                encoded = ValidationPolicy1::template apply_encode<EncodingForm>(u, state);
            } else {
                encoded = EncodingForm::encode_one(u, state, ValidationPolicy1{});
            }
        }

        Iterator first, last;
        typename EncodingForm::state state {};
        detail::coded_character<EncodingForm> encoded {};
        int current;
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
        using range = boost::iterator_range<Iterator>;

        decoding_iterator(Iterator first, Iterator last)
        : first(first), last(last) {}

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
        Iterator first, last;
        typename EncodingForm::state state {};
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_ITERATOR_HPP


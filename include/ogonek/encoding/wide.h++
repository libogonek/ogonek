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

// Wide encoding form

#ifndef OGONEK_ENCODING_WIDE_HPP
#define OGONEK_ENCODING_WIDE_HPP

#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <type_traits>

namespace ogonek {
    struct wide {
    private:
        using encoding = std::conditional<sizeof(wchar_t)==2, utf16, utf32>::type;

    public: 
        using code_unit = wchar_t;
        static constexpr bool is_fixed_width = encoding::is_fixed_width;
        static constexpr std::size_t max_width = encoding::max_width;
        static constexpr bool is_self_synchronizing = encoding::is_self_synchronizing;
        using state = encoding::state;

        template <typename SinglePassRange, typename Validation,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<wide, Iterator, Validation>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, Validation) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }

        template <typename SinglePassRange, typename Validation,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<wide, Iterator, Validation>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, Validation) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        static partial_array<code_unit, max_width> encode_one(codepoint u, state& s) {
            return encoding::encode_one(u, s);
        }

        template <typename SinglePassRange, typename Validation>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, Validation) {
            return encoding::decode_one(r, out, s, Validation{});
        }
    };
} // namespace ogonek

#endif // OGONEK_ENCODING_WIDE_HPP



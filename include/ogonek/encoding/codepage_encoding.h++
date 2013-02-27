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

// Generic codepage encoding

#ifndef OGONEK_CODEPAGE_ENCODING_HPP
#define OGONEK_CODEPAGE_ENCODING_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/types.h++>
#include <ogonek/validation.h++>
#include <ogonek/detail/partial_array.h++>

#include <boost/range/iterator_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <array>
#include <utility>
#include <algorithm>

namespace ogonek {
    struct codepage_entry {
        char encoded;
        code_point decoded;
    };
    
    template <typename Codepage>
    struct codepage_encoding {
    private:
        static codepage_entry const* find_codepage_entry(code_point u) {
            return std::lower_bound(std::begin(Codepage::from_unicode), std::end(Codepage::from_unicode), u,
                 [](codepage_entry const& entry, code_point u) { return entry.decoded < u; });
        }

    public:
        using code_unit = char;
        static constexpr bool is_fixed_width = true;
        static constexpr std::size_t max_width = 1;
        static constexpr bool is_self_synchronizing = true;
        static constexpr codepoint replacement_character = U'?';
        struct state {};
        
        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename EncodingIterator = encoding_iterator<codepage_encoding<Codepage>, Iterator, ValidationPolicy>>
        static boost::iterator_range<EncodingIterator> encode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    EncodingIterator { boost::begin(r), boost::end(r) },
                    EncodingIterator { boost::end(r), boost::end(r) });
        }
        template <typename SinglePassRange, typename ValidationPolicy,
                  typename Iterator = typename boost::range_const_iterator<SinglePassRange>::type,
                  typename DecodingIterator = decoding_iterator<codepage_encoding<Codepage>, Iterator, ValidationPolicy>>
        static boost::iterator_range<DecodingIterator> decode(SinglePassRange const& r, ValidationPolicy) {
            return boost::make_iterator_range(
                    DecodingIterator { boost::begin(r), boost::end(r) },
                    DecodingIterator { boost::end(r), boost::end(r) });
        }

        static detail::coded_character<codepage_encoding<Codepage>> encode_one(codepoint u, state&, skip_validation_t) {
            return { find_codepage_entry(u)->encoded };
        }

        template <typename ValidationPolicy>
        static detail::coded_character<codepage_encoding<Codepage>> encode_one(codepoint u, state& s, ValidationPolicy) {
            auto it = find_codepage_entry(u);
            if(it == std::end(Codepage::from_unicode) || it->decoded != u) {
                return ValidationPolicy::template apply_encode<codepage_encoding<Codepage>>(u, s);
            } else {
                return { it->encoded };
            }
        }

        template <typename SinglePassRange>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state&, skip_validation_t) {
            auto first = boost::begin(r);
            out = Codepage::to_unicode[*first++];
            return { first, boost::end(r) };
        }
        
        template <typename SinglePassRange, typename ValidationPolicy>
        static boost::sub_range<SinglePassRange> decode_one(SinglePassRange const& r, codepoint& out, state& s, ValidationPolicy) {
            auto first = boost::begin(r);
            auto decoded = Codepage::to_unicode[*first++];
            if(decoded == code_point(-1)) {
                return ValidationPolicy::template apply_decode<codepage_encoding<Codepage>>(r, s, out);
            } else {
                out = decoded;
                return { first, boost::end(r) };
            }
        }
    };
} // namespace ogonek

#endif // OGONEK_CODEPAGE_ENCODING_HPP


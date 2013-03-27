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
#include <ogonek/error.h++>
#include <ogonek/detail/ranges.h++>
#include <ogonek/detail/encoded_character.h++>

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
        static constexpr code_point replacement_character = U'?';
        struct state {};
        
        static detail::encoded_character<codepage_encoding<Codepage>> encode_one(code_point u, state&, assume_valid_t) {
            return { find_codepage_entry(u)->encoded };
        }

        template <typename ErrorHandler>
        static detail::encoded_character<codepage_encoding<Codepage>> encode_one(code_point u, state& s, ErrorHandler) {
            auto it = find_codepage_entry(u);
            if(it == std::end(Codepage::from_unicode) || it->decoded != u) {
                return ErrorHandler::template apply_encode<codepage_encoding<Codepage>>(u, s);
            } else {
                return { it->encoded };
            }
        }

        template <typename Range>
        static boost::sub_range<Range> decode_one(Range const& r, code_point& out, state&, assume_valid_t) {
            auto first = boost::begin(r);
            out = Codepage::to_unicode[*first++];
            return { first, boost::end(r) };
        }
        
        template <typename Range, typename ErrorHandler>
        static boost::sub_range<Range> decode_one(Range const& r, code_point& out, state& s, ErrorHandler) {
            auto first = boost::begin(r);
            auto decoded = Codepage::to_unicode[*first++];
            if(decoded == code_point(-1)) {
                return ErrorHandler::template apply_decode<codepage_encoding<Codepage>>(r, s, out);
            } else {
                out = decoded;
                return { first, boost::end(r) };
            }
        }
    };
} // namespace ogonek

#endif // OGONEK_CODEPAGE_ENCODING_HPP


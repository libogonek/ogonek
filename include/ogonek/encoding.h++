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

// Generic encoding and decoding functions

#ifndef OGONEK_ENCODING_HPP
#define OGONEK_ENCODING_HPP

#include <ogonek/encoding/iterator.h++>
#include <ogonek/detail/ranges.h++>

#include <boost/range/iterator_range.hpp>

namespace ogonek {
    template <typename EncodingForm,
              typename Range, typename ErrorHandler,
              typename Iterator = detail::RangeConstIterator<Range>,
              typename DecodingIterator = decoding_iterator<EncodingForm, Iterator, ErrorHandler>,
              typename DecodingRange = detail::tagged_iterator_range<DecodingIterator, detail::validated_tag>>
    DecodingRange decode(Range const& r, ErrorHandler) {
        return detail::wrap_tagged_range<DecodingIterator, detail::validated_tag>(r);
    }
} // namespace ogonek

#endif // OGONEK_ENCODING_HPP

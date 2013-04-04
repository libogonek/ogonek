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

// Grapheme segmentation

#ifndef OGONEK_GRAPHEMES_HPP
#define OGONEK_GRAPHEMES_HPP

#include <ogonek/segmentation/detail/grapheme_iterator.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/detail/ranges.h++>

#include <boost/range/iterator_range.hpp>

namespace ogonek {
    template <typename UnicodeSequence, // TODO use UnicodeSequenceIterator
              typename Iterator = detail::grapheme_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> graphemes(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, assume_valid));
    }
} // namespace ogonek

#endif // OGONEK_GRAPHEMES_HPP

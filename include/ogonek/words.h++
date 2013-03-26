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

// Word segmentation

#ifndef OGONEK_WORDS_HPP
#define OGONEK_WORDS_HPP

#include <ogonek/detail/word_iterator.h++>
#include <ogonek/detail/ranges.h++>
#include <ogonek/assume_valid.h++>

#include <boost/range/iterator_range.hpp>

namespace ogonek {
    template <typename UnicodeSequence, // TODO use UnicodeSequenceIterator
              typename Iterator = detail::word_iterator<detail::RangeConstIterator<UnicodeSequence>>>
    boost::iterator_range<Iterator> words(UnicodeSequence const& sequence) {
        return detail::wrap_range<Iterator>(detail::as_code_point_range(sequence, assume_valid));
    }
} // namespace ogonek

#endif // OGONEK_WORDS_HPP

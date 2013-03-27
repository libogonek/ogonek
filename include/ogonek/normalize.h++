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

// Normalization function

#ifndef OGONEK_NORMALIZE_HPP
#define OGONEK_NORMALIZE_HPP

#include <ogonek/detail/ranges.h++>
#include <ogonek/detail/normalizing_iterator.h++>

#include <boost/range/iterator_range.hpp>

namespace ogonek {
    template <typename NormalForm,
              typename UnicodeSequence,
              typename Iterator = detail::UnicodeSequenceIterator<UnicodeSequence, assume_valid_t>,
              typename NormalizingIterator = detail::normalizing_iterator<NormalForm, Iterator>,
              typename NormalizingRange = boost::iterator_range<NormalizingIterator>>
              //typename NormalizingRange = detail::tagged_iterator_range<NormalizingIterator, detail::normalized_tag<NormalForm>>>
    NormalizingRange normalize(UnicodeSequence const& sequence) {
        return detail::wrap_range<NormalizingIterator>(detail::as_code_point_range(sequence, assume_valid));
    }
} // namespace ogonek

#endif // OGONEK_NORMALIZE_HPP

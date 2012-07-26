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

// Validation

#ifndef OGONEK_VALIDATION_HPP
#define OGONEK_VALIDATION_HPP

#include <boost/range/sub_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <cstdint>
#include <iterator>

namespace ogonek {
    enum class validation_result {
        valid, unassigned, illegal, irregular,
    };

    struct {
        template <typename Range, typename OutputIterator>
        boost::sub_range<Range> operator()(validation_result, boost::sub_range<Range> const& source, OutputIterator& out) const {
            *out++ = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
    } constexpr use_replacement_character = {};

    struct {
        template <typename Range, typename OutputIterator>
        boost::sub_range<Range> operator()(validation_result, boost::sub_range<Range> const& source, OutputIterator&) const {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
    } constexpr ignore_errors = {};
} // namespace ogonek

#endif // OGONEK_VALIDATION_HPP


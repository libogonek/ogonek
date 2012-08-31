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

    struct validation_error : std::exception { // TODO Boost.Exception
        char const* what() const throw() override {
            return "Unicode validation failed";
        }
    };

    constexpr struct {
        template <typename Range>
        boost::sub_range<Range> operator()(validation_result, boost::sub_range<Range> const&, codepoint&) const {
            throw validation_error();
        }
    } throw_validation_error = {};

    constexpr struct {
        template <typename Range>
        boost::sub_range<Range> operator()(validation_result, boost::sub_range<Range> const& source, codepoint& out) const {
            out = U'\xFFFD';
            return { std::next(boost::begin(source)), boost::end(source) };
        }
    } use_replacement_character = {};

    constexpr struct {
        template <typename Range>
        boost::sub_range<Range> operator()(validation_result, boost::sub_range<Range> const& source, codepoint&) const {
            return { std::next(boost::begin(source)), boost::end(source) };
        }
    } ignore_errors = {};

    constexpr struct skip_validation_t {} skip_validation = {};
} // namespace ogonek

#endif // OGONEK_VALIDATION_HPP


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

// Normalization tests

#ifndef OGONEK_IS_NORMALIZED_HPP
#define OGONEK_IS_NORMALIZED_HPP

#include <ogonek/data/ucd.h++>
#include <ogonek/detail/ranges.h++>

#include <boost/logic/tribool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/equal.hpp>

namespace ogonek {
    template <typename NormalForm, typename UnicodeSequence,
              typename Result = decltype(NormalForm::quick_check(0))>
    Result is_normalized_quick(UnicodeSequence const& sequence) {
        for(auto u : detail::as_code_point_range(sequence, assume_valid)) {
            auto quick_check = NormalForm::quick_check(u);
            if(quick_check) continue; // this looks weird, but consider boost::indeterminate
            else return quick_check;
        }
        return true;
    }

    template <typename NormalForm, typename UnicodeSequence>
    bool is_normalized(UnicodeSequence const& sequence) {
        auto&& range = detail::as_code_point_range(sequence, assume_valid);
        auto last_starter = boost::begin(range);
        for(auto it = boost::begin(range); it != boost::end(range); ++it) {
            auto quick_check = NormalForm::quick_check(*it);
            if(!quick_check) return false;
            if(boost::indeterminate(quick_check)) {
                auto indeterminate_range = boost::make_iterator_range(last_starter, std::next(it));
                if(!boost::equal(indeterminate_range, normalize<NormalForm>(indeterminate_range))) {
                    return false;
                }
            }
            if(ucd::get_combining_class(*it) == 0) {
                last_starter = it;
            }
        }
        return true;
    }
} // namespace ogonek

#endif // OGONEK_IS_NORMALIZED_HPP

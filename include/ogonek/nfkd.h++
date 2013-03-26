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

// Normalization Form Compatibility D

#ifndef OGONEK_NFKD_HPP
#define OGONEK_NFKD_HPP

#include <ogonek/types.h++>
#include <ogonek/ucd.h++>
#include <ogonek/detail/ordered_decomposing_iterator.h++>

namespace ogonek {
    struct nfkd {
        static bool quick_check(code_point u) {
            return ucd::is_nfkd_quick_check(u);
        }
    };

    namespace detail {
        template <typename Iterator>
        struct normalizing_iterator_impl<nfkd, Iterator> {
            using type = ordered_decomposing_iterator<Iterator, true>;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_NFKD_HPP

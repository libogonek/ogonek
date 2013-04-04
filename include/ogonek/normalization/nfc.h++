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

// Normalization Form C

#ifndef OGONEK_NFC_HPP
#define OGONEK_NFC_HPP

#include <ogonek/types.h++>
#include <ogonek/data/ucd.h++>
#include <ogonek/normalization/detail/composing_iterator.h++>

namespace ogonek {
    struct nfc {
        static boost::tribool quick_check(code_point u) {
            return ucd::is_nfc_quick_check(u);
        }
    };

    namespace detail {
        template <typename Iterator>
        struct normalizing_iterator_impl<nfc, Iterator> {
            using type = composing_iterator<Iterator>;
        };
    } // namespace detail
} // namespace ogonek

#endif // OGONEK_NFC_HPP

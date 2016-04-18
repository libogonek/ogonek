// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on 2016-04-18T17:07:59.772860Z

// Unicode character database - NFC_Quick_Check property

#ifndef OGONEK_UCD_NFC_QUICK_CHECK_HPP
#define OGONEK_UCD_NFC_QUICK_CHECK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            

            struct nfc_quick_check_properties {
                code_point start;
                detail::trinary value;
            };

            extern OGONEK_PUBLIC nfc_quick_check_properties const* nfc_quick_check_data;
            extern OGONEK_PUBLIC std::size_t nfc_quick_check_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_NFC_QUICK_CHECK_HPP

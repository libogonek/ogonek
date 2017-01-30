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

// This file was automatically generated.

// Unicode character database - Quotation_Mark property

#ifndef OGONEK_UCD_QUOTATION_MARK_HPP
#define OGONEK_UCD_QUOTATION_MARK_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            

            struct quotation_mark_properties {
                code_point start;
                bool value;
            };

            extern OGONEK_PUBLIC quotation_mark_properties const* quotation_mark_data;
            extern OGONEK_PUBLIC std::size_t quotation_mark_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_QUOTATION_MARK_HPP

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

#include <ogonek/ucd/quotation_mark.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            quotation_mark_properties const quotation_mark_data_raw[] {
                { 0x0, false },
                { 0x22, true },
                { 0x23, false },
                { 0x27, true },
                { 0x28, false },
                { 0xAB, true },
                { 0xAC, false },
                { 0xBB, true },
                { 0xBC, false },
                { 0x2018, true },
                { 0x2020, false },
                { 0x2039, true },
                { 0x203B, false },
                { 0x2E42, true },
                { 0x2E43, false },
                { 0x300C, true },
                { 0x3010, false },
                { 0x301D, true },
                { 0x3020, false },
                { 0xFE41, true },
                { 0xFE45, false },
                { 0xFF02, true },
                { 0xFF03, false },
                { 0xFF07, true },
                { 0xFF08, false },
                { 0xFF62, true },
                { 0xFF64, false },
            };
        } // namespace
        inline namespace abiv0 {
            quotation_mark_properties const* quotation_mark_data = quotation_mark_data_raw;
            std::size_t quotation_mark_data_size = detail::size(quotation_mark_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

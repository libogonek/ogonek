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

// Unicode character database - $Turkic_Case_Folding property

#include <ogonek/ucd/turkic_case_folding.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            turkic_case_folding_properties const turkic_case_folding_data_raw[] {
                { 0x0, nullptr },
                { 0x49, U"\x131" },
                { 0x4A, nullptr },
                { 0x130, U"\x69" },
                { 0x131, nullptr },
            };
        } // namespace
        inline namespace abiv0 {
            turkic_case_folding_properties const* turkic_case_folding_data = turkic_case_folding_data_raw;
            std::size_t turkic_case_folding_data_size = detail::size(turkic_case_folding_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

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

// This file was automatically generated on 2016-04-18T17:07:59.228507Z

// Unicode character database - General_Category property

#ifndef OGONEK_UCD_GENERAL_CATEGORY_HPP
#define OGONEK_UCD_GENERAL_CATEGORY_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class general_category : unsigned long long {
                cc = 0x4,
                cf = 0x8,
                cn = 0x10,
                co = 0x20,
                cs = 0x40,
                lc = 0x80,
                ll = 0x100,
                lm = 0x200,
                lo = 0x400,
                lt = 0x800,
                lu = 0x1000,
                mc = 0x2000,
                me = 0x4000,
                mn = 0x8000,
                nd = 0x10000,
                nl = 0x20000,
                no = 0x40000,
                pc = 0x80000,
                pd = 0x100000,
                pe = 0x200000,
                pf = 0x400000,
                pi = 0x800000,
                po = 0x1000000,
                ps = 0x2000000,
                sc = 0x4000000,
                sk = 0x8000000,
                sm = 0x10000000,
                so = 0x20000000,
                zl = 0x40000000,
                zp = 0x80000000,
                zs = 0x100000000,
                c = cc | cf | cn | co | cs,
                m = mc | me | mn,
                l = lc | ll | lm | lo | lt | lu,
                n = nd | nl | no,
                p = pc | pd | pe | pf | pi | po | ps,
                s = sc | sk | sm | so,
                z = zl | zp | zs,
                other = c,
                control = cc,
                cntrl = cc,
                format = cf,
                unassigned = cn,
                private_use = co,
                surrogate = cs,
                letter = l,
                cased_letter = lc,
                lowercase_letter = ll,
                modifier_letter = lm,
                other_letter = lo,
                titlecase_letter = lt,
                uppercase_letter = lu,
                mark = m,
                combining_mark = m,
                spacing_mark = mc,
                enclosing_mark = me,
                nonspacing_mark = mn,
                number = n,
                decimal_number = nd,
                digit = nd,
                letter_number = nl,
                other_number = no,
                punctuation = p,
                punct = p,
                connector_punctuation = pc,
                dash_punctuation = pd,
                close_punctuation = pe,
                final_punctuation = pf,
                initial_punctuation = pi,
                other_punctuation = po,
                open_punctuation = ps,
                symbol = s,
                currency_symbol = sc,
                modifier_symbol = sk,
                math_symbol = sm,
                other_symbol = so,
                separator = z,
                line_separator = zl,
                paragraph_separator = zp,
                space_separator = zs,
            };

            struct general_category_properties {
                code_point start;
                general_category value;
            };

            extern OGONEK_PUBLIC general_category_properties const* general_category_data;
            extern OGONEK_PUBLIC std::size_t general_category_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_GENERAL_CATEGORY_HPP

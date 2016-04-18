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

// This file was automatically generated on 2016-04-18T17:07:58.939116Z

// Unicode character database - Canonical_Combining_Class property

#ifndef OGONEK_UCD_CANONICAL_COMBINING_CLASS_HPP
#define OGONEK_UCD_CANONICAL_COMBINING_CLASS_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum combining_class {
                nr = 0,
                not_reordered = nr,
                ov = 1,
                overlay = ov,
                ccc130 = 130,
                ccc132 = 132,
                ccc133 = 133,
                nk = 7,
                nukta = nk,
                kv = 8,
                kana_voicing = kv,
                vr = 9,
                virama = vr,
                ccc10 = 10,
                ccc11 = 11,
                ccc12 = 12,
                ccc13 = 13,
                ccc14 = 14,
                ccc15 = 15,
                ccc16 = 16,
                ccc17 = 17,
                ccc18 = 18,
                ccc19 = 19,
                ccc20 = 20,
                ccc21 = 21,
                ccc22 = 22,
                ccc23 = 23,
                ccc24 = 24,
                ccc25 = 25,
                ccc26 = 26,
                ccc27 = 27,
                ccc28 = 28,
                ccc29 = 29,
                ccc30 = 30,
                ccc31 = 31,
                ccc32 = 32,
                ccc33 = 33,
                ccc34 = 34,
                ccc35 = 35,
                ccc36 = 36,
                ccc129 = 129,
                atbl = 200,
                attached_below_left = atbl,
                atb = 202,
                attached_below = atb,
                ccc84 = 84,
                ata = 214,
                attached_above = ata,
                atar = 216,
                attached_above_right = atar,
                bl = 218,
                below_left = bl,
                ccc91 = 91,
                b = 220,
                below = b,
                br = 222,
                below_right = br,
                l = 224,
                left = l,
                r = 226,
                right = r,
                al = 228,
                above_left = al,
                a = 230,
                above = a,
                ccc103 = 103,
                ar = 232,
                above_right = ar,
                db = 233,
                double_below = db,
                da = 234,
                double_above = da,
                ccc107 = 107,
                is = 240,
                iota_subscript = is,
                ccc118 = 118,
                ccc122 = 122,
            };

            struct canonical_combining_class_properties {
                code_point start;
                combining_class value;
            };

            extern OGONEK_PUBLIC canonical_combining_class_properties const* canonical_combining_class_data;
            extern OGONEK_PUBLIC std::size_t canonical_combining_class_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_CANONICAL_COMBINING_CLASS_HPP

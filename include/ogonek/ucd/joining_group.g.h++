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

// This file was automatically generated on 2016-04-18T17:07:59.406869Z

// Unicode character database - Joining_Group property

#ifndef OGONEK_UCD_JOINING_GROUP_HPP
#define OGONEK_UCD_JOINING_GROUP_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class joining_group {
                ain,
                alaph,
                alef,
                beh,
                beth,
                burushaski_yeh_barree,
                dal,
                dalath_rish,
                e,
                farsi_yeh,
                fe,
                feh,
                final_semkath,
                gaf,
                gamal,
                hah,
                he,
                heh,
                heh_goal,
                heth,
                kaf,
                kaph,
                khaph,
                knotted_heh,
                lam,
                lamadh,
                manichaean_aleph,
                manichaean_ayin,
                manichaean_beth,
                manichaean_daleth,
                manichaean_dhamedh,
                manichaean_five,
                manichaean_gimel,
                manichaean_heth,
                manichaean_hundred,
                manichaean_kaph,
                manichaean_lamedh,
                manichaean_mem,
                manichaean_nun,
                manichaean_one,
                manichaean_pe,
                manichaean_qoph,
                manichaean_resh,
                manichaean_sadhe,
                manichaean_samekh,
                manichaean_taw,
                manichaean_ten,
                manichaean_teth,
                manichaean_thamedh,
                manichaean_twenty,
                manichaean_waw,
                manichaean_yodh,
                manichaean_zayin,
                meem,
                mim,
                no_joining_group,
                noon,
                nun,
                nya,
                pe,
                qaf,
                qaph,
                reh,
                reversed_pe,
                rohingya_yeh,
                sad,
                sadhe,
                seen,
                semkath,
                shin,
                straight_waw,
                swash_kaf,
                syriac_waw,
                tah,
                taw,
                teh_marbuta,
                teh_marbuta_goal,
                teth,
                waw,
                yeh,
                yeh_barree,
                yeh_with_tail,
                yudh,
                yudh_he,
                zain,
                zhain,
                hamza_on_heh_goal = teh_marbuta_goal,
            };

            struct joining_group_properties {
                code_point start;
                joining_group value;
            };

            extern OGONEK_PUBLIC joining_group_properties const* joining_group_data;
            extern OGONEK_PUBLIC std::size_t joining_group_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_JOINING_GROUP_HPP

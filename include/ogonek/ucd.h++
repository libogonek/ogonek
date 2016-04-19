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

// Unicode character database

#ifndef OGONEK_UCD_HPP
#define OGONEK_UCD_HPP

#include <ogonek/ucd/ucd_all.g.h++>

#include <ogonek/encoding/ascii.h++>
#include <ogonek/text.h++>
#include <ogonek/types.h++>

#include <boost/logic/tribool.hpp>
#include <boost/rational.hpp>

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>

#include <cstddef>
#include <cstring>

namespace ogonek {
    BOOST_TRIBOOL_THIRD_STATE(maybe)

    namespace ucd {
        namespace detail {
            inline boost::tribool to_tribool(ogonek::detail::trinary t) {
                switch(t.value) {
                    case -1:
                        return maybe;
                    default:
                        return t.value;
                }
            }
            inline boost::rational<long> to_rational(ogonek::detail::fraction f) {
                return boost::rational<long>(f.num, f.den);
            }

            template <typename It>
            std::reverse_iterator<It> make_reverse(It it) {
                return std::reverse_iterator<It>(it);
            }
            struct property_group_comparer {
                template <typename T>
                bool operator()(code_point u, T const& g) const {
                    return u >= g.start;
                }
            };
            template <typename T>
            T const& find_property_group(T const* first, std::size_t size, code_point u) {
                return *std::upper_bound(make_reverse(first + size), make_reverse(first), u, property_group_comparer{});
            }

            using ascii_text = text<ascii, std::string>;

            inline void add_hex(code_point u, std::string& s) {
                char const hex[] = "0123456789ABCDEF";
                int factor;
                if(u > 0xFFFFF) factor = 0x100000;
                else if(u > 0xFFFF) factor = 0x10000;
                else factor = 0x1000;
                for(; factor > 0; u %= factor, factor /= 0x10) {
                    s.push_back(hex[u / factor]);
                }
            }
            template <std::size_t N>
            std::string make_ideograph_name(code_point u, char const (&base)[N]) {
                std::string result;
                result.reserve(N + 5);
                result = base;
                add_hex(u, result);
                return result;
            }
            inline char const* get_jamo_short_name(code_point u) {
                return detail::find_property_group(jamo_short_name_data, jamo_short_name_data_size, u).value;
            }
        } // namespace detail

        inline hangul_syllable_type get_hangul_syllable_type(code_point u) {
            return detail::find_property_group(hangul_syllable_type_data, hangul_syllable_type_data_size, u).value;
        }
        inline detail::ascii_text get_name(code_point u) {
            auto value = detail::find_property_group(name_data, name_data_size, u).value;
            if(value[0] != '<') return detail::ascii_text(value);

            if(std::strcmp(value, "<CJK Ideograph>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension A>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension B>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension C>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension D>") == 0
            || std::strcmp(value, "<CJK Ideograph Extension E>") == 0) {
                return detail::ascii_text(detail::make_ideograph_name(u, "CJK UNIFIED IDEOGRAPH-"));
            }
            if(std::strcmp(value, "<Hangul Syllable>") == 0) {
                const int sbase = 0xAC00;
                const int lbase = 0x1100;
                const int vbase = 0x1161;
                const int tbase = 0x11A7;
                const int tcount = 28;
                const int ncount = 588;

                auto sindex = u - sbase;
                auto lindex = sindex / ncount;
                auto vindex = (sindex % ncount) / tcount;
                auto tindex = sindex % tcount;
                auto lpart = lbase + lindex;
                auto vpart = vbase + vindex;
                auto tpart = tbase + tindex;

                char const base[] = "HANGUL SYLLABLE ";
                std::string result;
                result.reserve(sizeof(base) + 9);
                result += base;
                result += detail::get_jamo_short_name(lpart);
                result += detail::get_jamo_short_name(vpart);
                if(tindex > 0) result += detail::get_jamo_short_name(tpart);
                return detail::ascii_text(result);
            }
            return detail::ascii_text();
        }
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_HPP


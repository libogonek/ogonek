// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Unicode character property queries

#ifndef OGONEK_PROPERTIES_HPP
#define OGONEK_PROPERTIES_HPP

#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/data/ucd.h++>

#include <wheels/enums.h++>

#include <algorithm>
#include <type_traits>

namespace wheels {
    template <>
    struct is_flags< ::ogonek::ucd::category> : std::true_type {};
}

namespace ogonek {
    inline bool is_numeric(code_point u) {
        return ucd::get_numeric_type(u) != ucd::numeric_type::None;
    }
    inline double numeric_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    inline bool is_digit(code_point u) {
        auto type = ucd::get_numeric_type(u);
        return type == ucd::numeric_type::Di || type == ucd::numeric_type::De;
    }
    inline int digit_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    inline bool is_decimal(code_point u) {
        return ucd::get_numeric_type(u) == ucd::numeric_type::De;
    }
    inline int decimal_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    inline bool is_uppercase(code_point u) {
        return ucd::is_uppercase(u);
    }
    inline ucd::vector_type<code_point, 4> uppercase(code_point u) {
        return ucd::get_uppercase(u);
    }

    inline bool is_lowercase(code_point u) {
        return ucd::is_lowercase(u);
    }
    inline ucd::vector_type<code_point, 4> lowercase(code_point u) {
        return ucd::get_lowercase(u);
    }

    inline ucd::vector_type<code_point, 4> titlecase(code_point u) {
        return ucd::get_titlecase(u);
    }

    using ucd::is_alphabetic;
    using ucd::is_ideographic;
    using ucd::is_unified_ideograph;
    using ucd::is_white_space;
    using ucd::is_hex_digit;
    using ucd::is_ascii_hex_digit;
    using ucd::is_quotation_mark;
    using ucd::is_dash;
    using ucd::is_diacritic;
    inline bool is_mathematical(code_point u) {
        return ucd::is_math(u);
    }
    
    inline bool is_graphic(code_point u) {
        constexpr auto graphic = ucd::category::L
                               | ucd::category::M
                               | ucd::category::N
                               | ucd::category::P
                               | ucd::category::S
                               | ucd::category::Zs;
        return wheels::has_flag(graphic, ucd::get_general_category(u));
    }
    inline bool is_format(code_point u) {
        constexpr auto format = ucd::category::Cf
                              | ucd::category::Zl
                              | ucd::category::Zp;
        return wheels::has_flag(format, ucd::get_general_category(u));
    }
    inline bool is_control(code_point u) {
        return ucd::get_general_category(u) == ucd::category::Cc;
    }
    inline bool is_private_use(code_point u) {
        return ucd::get_general_category(u) == ucd::category::Co;
    }
    inline bool is_surrogate(code_point u) {
        return ucd::get_general_category(u) == ucd::category::Cs;
    }
    using ucd::is_noncharacter;
    inline bool is_reserved(code_point u) {
        return !is_noncharacter(u) && ucd::get_general_category(u) == ucd::category::Cn;
    }

    inline bool is_defined(code_point u) {
        return ucd::get_age(u) != ucd::version::unassigned;
    } 
} // namespace ogonek

#endif // OGONEK_PROPERTIES_HPP

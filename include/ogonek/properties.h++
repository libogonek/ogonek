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
#include <ogonek/ucd.h++>

#include <wheels/enums.h++>

#include <type_traits>

namespace wheels {
    template <>
    struct is_flags< ::ogonek::ucd::category> : std::true_type {};
}

namespace ogonek {
    text<utf8> name(code_point u) {
        return ucd::get_name(u);
    }

    bool is_numeric(code_point u) {
        return ucd::get_numeric_type(u) != ucd::numeric_type::None;
    }
    double numeric_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    bool is_digit(code_point u) {
        auto type = ucd::get_numeric_type(u);
        return type == ucd::numeric_type::Di || type == ucd::numeric_type::De;
    }
    int digit_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    bool is_decimal(code_point u) {
        return ucd::get_numeric_type(u) == ucd::numeric_type::De;
    }
    int decimal_value(code_point u) {
        return ucd::get_numeric_value(u);
    }

    bool is_uppercase(code_point u) {
        return ucd::is_uppercase(u);
    }
    ucd::vector_type<code_point, 4> uppercase(code_point u) {
        return ucd::get_uppercase(u);
    }

    bool is_lowercase(code_point u) {
        return ucd::is_lowercase(u);
    }
    ucd::vector_type<code_point, 4> lowercase(code_point u) {
        return ucd::get_lowercase(u);
    }

    ucd::vector_type<code_point, 4> titlecase(code_point u) {
        return ucd::get_titlecase(u);
    }

    using ucd::is_alphabetic;
    using ucd::is_white_space;
    bool is_control(code_point u) {
        return ucd::get_general_category(u) == ucd::category::Cc;
    }
    using ucd::is_hex_digit;
    using ucd::is_ascii_hex_digit;
    bool is_letter(code_point u) {
        return wheels::has_flag(ucd::category::L, ucd::get_general_category(u));
    }
    bool is_punctuation(code_point u) {
        return wheels::has_flag(ucd::category::P, ucd::get_general_category(u));
    }
    bool is_separator(code_point u) {
        return wheels::has_flag(ucd::category::Z, ucd::get_general_category(u));
    }
    bool is_symbol(code_point u) {
        return wheels::has_flag(ucd::category::S, ucd::get_general_category(u));
    }
    using ucd::is_quotation_mark;
    using ucd::is_dash;
    using ucd::is_diacritic;
    bool is_mathematical(code_point u) {
        return ucd::is_math(u);
    }
    using ucd::is_ideographic;
    using ucd::is_unified_ideograph;
    
    using ucd::is_noncharacter;

    bool is_private_use(code_point u) {
        return ucd::get_general_category(u) == ucd::category::Co;
    }
    bool is_defined(code_point u) {
        return ucd::get_age(u) == ucd::age::unassigned;
    }
} // namespace ogonek

#endif // OGONEK_PROPERTIES_HPP

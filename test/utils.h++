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

// Tests utils

#ifndef OGONEK_TEST_UTILS_HPP
#define OGONEK_TEST_UTILS_HPP

#include <ogonek/types.h++>
#include <ogonek/traits.h++>
#include <ogonek/text.h++>
#include <ogonek/encoding/utf32.h++>

#include <wheels/meta.h++>

#include <string>
#include <ostream>
#include <sstream>
#include <cstddef>

namespace test {
    struct code_point_output_traits : std::char_traits<ogonek::code_point> {};

    using ustring = std::basic_string<ogonek::code_point, code_point_output_traits>;
    using utext = ogonek::text<ogonek::utf32, ustring>;
    namespace literal {
        inline ustring operator"" _u(char32_t const* literal, std::size_t size) {
            return { literal, size };
        }
    } // namespace literal

    inline std::ostream& operator<<(std::ostream& os, ustring const& str) {
        auto format_code_point = [](ogonek::code_point u) -> std::string {
            std::stringstream ss;
            ss << "U+";
            ss.width(4);
            ss.fill('0');
            ss << std::hex << std::uppercase << u;
            return ss.str();
        };
        bool is_first = true;
        os << '<';
        for(auto u : str) {
            if(!is_first) os << ' ';
            os << format_code_point(u);
            is_first = false;
        }
        os << '>';
        return os;
    }

    template <typename Encoding>
    struct code_unit_output_traits : std::char_traits<ogonek::CodeUnit<Encoding>> {};

    template <typename Encoding>
    using string = std::basic_string<ogonek::CodeUnit<Encoding>, code_unit_output_traits<Encoding>>;
    template <typename Encoding>
    using text = ogonek::text<Encoding, string<Encoding>>;

    template <typename CodeUnit>
    std::string format_code_unit(CodeUnit c) {
        std::stringstream ss;
        ss.width(2*sizeof(CodeUnit));
        ss.fill('0');
        ss << std::hex << std::uppercase
            << static_cast<unsigned long long>(static_cast<wheels::MakeUnsigned<CodeUnit>>(c));
        return ss.str();
    }
    template <typename Encoding>
    inline std::ostream& operator<<(std::ostream& os, string<Encoding> const& str) {
        bool is_first = true;
        os << '[';
        for(auto c : str) {
            if(!is_first) os << ' ';
            os << format_code_unit(c);
            is_first = false;
        }
        os << ']';
        return os;
    }

    template <typename Encoding, typename Container>
    inline std::ostream& operator<<(std::ostream& os, ogonek::text<Encoding, Container> const& t) {
        return os << t.storage();
    }

    struct byte_output_traits : std::char_traits<ogonek::byte> {};
    using byte_string = std::basic_string<ogonek::byte, byte_output_traits>;
    namespace literal {
        inline byte_string operator"" _b(char const* literal, std::size_t size) {
            return { reinterpret_cast<unsigned char const*>(literal), size };
        }
    } // namespace literal

    inline std::ostream& operator<<(std::ostream& os, byte_string const& str) {
        bool is_first = true;
        os << '[';
        for(auto c : str) {
            if(!is_first) os << ' ';
            os << format_code_unit(c);
            is_first = false;
        }
        os << ']';
        return os;
    }
} // namespace test

#endif // OGONEK_TEST_UTILS_HPP


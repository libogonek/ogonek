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

// Tests utilities

#include <ogonek/types.h++>

#include <catch.hpp>

#include <sstream>
#include <vector>

namespace test {
    namespace detail {
        template <typename T>
        void format_code_unit(std::ostream& os, T u) {
            os.width(4);
            os.fill('0');
            os << std::hex << std::uppercase << static_cast<unsigned long long>(u);
        }
        template <typename T>
        void format_code_point(std::ostream& os, T u) {
            os << "U+";
            format_code_unit(os, u);
        }
        template <typename T>
        std::string convert_string(std::vector<T> const& str, void (*formatter)(std::ostream&, T)) {
            std::stringstream ss;
            bool is_first = true;
            ss << '<';
            for(auto u : str) {
                if(!is_first) ss << ' ';
                formatter(ss, u);
                is_first = false;
            }
            ss << '>';
            return ss.str();
        }
        template <typename T>
        struct code_unit_converter {
            static std::string convert(std::vector<T> const& str) {
                return convert_string(str, format_code_unit);
            }
        };
    } // namespace detail
} // namespace test

namespace Catch {
    template <>
    struct StringMaker<std::vector<char32_t>> : test::detail::code_unit_converter<char32_t> {};
    template <>
    struct StringMaker<std::vector<char16_t>> : test::detail::code_unit_converter<char16_t> {};
    template <>
    struct StringMaker<std::vector<char>> : test::detail::code_unit_converter<char> {};
} // namespace Catch


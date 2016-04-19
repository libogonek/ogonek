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

#include <catch.hpp>

#include <sstream>
#include <string>

namespace Catch {
    template <>
    struct StringMaker<std::u32string> {
        static std::string convert(std::u32string const& str) {
            std::stringstream ss;
            auto format_code_point = [](std::ostream& os, ogonek::code_point u) {
                os << "U+";
                os.width(4);
                os.fill('0');
                os << std::hex << std::uppercase << u;
            };
            bool is_first = true;
            ss << '<';
            for(auto u : str) {
                if(!is_first) ss << ' ';
                format_code_point(ss, u);
                is_first = false;
            }
            ss << '>';
            return ss.str();
        }
    };
} // namespace Catch


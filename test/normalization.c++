// Ogonek
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for <ogonek/normalization.h++>

#include <ogonek/normalization.h++>

#include <ogonek/encoding/utf32.h++>
#include <ogonek/text.h++>

#include <catch.h++>

namespace std {
std::ostream& operator<<(std::ostream& os, std::u32string const& u32) {
    os << std::hex;
    for(auto u : u32) {
        os << "\\x" << static_cast<int>(u);
    }
    return os;
}
}

TEST_CASE("decompose", "Decomposition") {
    using test_text = ogonek::basic_text<ogonek::utf32>;
    test_text in { U"ABC\x00C5\x00F4\x1E69\x1E0B\x0323\x0071\x0307\x0323" };
    test_text out { ogonek::decompose(in) };
    REQUIRE(out.storage() == std::u32string { U"ABC\x0041\x030A\x006F\x0302\x0073\x0323\x0307\x0064\x0307\x0323\x0071\x0307\x0323" });
}
/*

TEST_CASE("canonical ordering", "Decomposition + canonical ordering") {
    using test_text = ogonek::basic_text<ogonek::utf32>;
    test_text in { U"\x1E69\x1E0B\x0323\x0071\x0307\x0323" };
    for(auto u : ogonek::decompose_ordered(in)) {
        std::cout << std::hex << int(u) << '\n';
    }
    //test_text out { ogonek::decompose_ordered(in) };
    //REQUIRE(out.storage() == std::u32string { U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307" });
}
*/

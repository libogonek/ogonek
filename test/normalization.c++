// Ogonek
//
// Written in 2012-2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
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
    using test_text = ogonek::text<ogonek::utf32>;
    test_text in { U"ABC\x00C5\x00F4\x1E69\x1E0B\x0323\x0071\x0307\x0323" };
    test_text out { ogonek::decompose(in) };
    REQUIRE(out.storage() == std::u32string { U"ABC\x0041\x030A\x006F\x0302\x0073\x0323\x0307\x0064\x0307\x0323\x0071\x0307\x0323" });
}

TEST_CASE("canonical ordering", "Decomposition + canonical ordering") {
    using test_text = ogonek::text<ogonek::utf32>;
    test_text in { U"\x1E69\x1E0B\x0323\x0071\x0307\x0323" };
    test_text out { ogonek::decompose_ordered(in) };
    REQUIRE(out.storage() == std::u32string { U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307" });
}

TEST_CASE("nfd", "Normalization Form D") {
    using test_text = ogonek::text<ogonek::utf32>;
    std::u32string input = U"\x1E69\x1E0B\x0323\x0071\x0307\x0323";
    std::u32string normalized = U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307";

    test_text out { ogonek::normalize<ogonek::nfd>(input) };
    REQUIRE(out.storage() == normalized);
}

TEST_CASE("nfc", "Normalization Form C") {
    using test_text = ogonek::text<ogonek::utf32>;
    SECTION("test1", "") {
        std::u32string input = U"\x1E69\x1E0B\x0323\x0071\x0307\x0323";
        std::u32string normalized = U"\x1E69\x1E0D\x0307\x0071\x0323\x0307";

        test_text out { ogonek::normalize<ogonek::nfc>(input) };
        REQUIRE(out.storage() == normalized);
    }

    SECTION("madness", "") {
        std::u32string input = U"2";
        input.reserve(10004);
        for(int i = 0; i < 10000; ++i) {
            input += U"\x0308";
        }
        input += U"\x0323";
        input += U"3";

        std::u32string normalized = U"2";
        normalized.reserve(10004);
        normalized += U"\x0323";
        for(int i = 0; i < 10000; ++i) {
            normalized += U"\x0308";
        }
        normalized += U"3";

        test_text out { ogonek::normalize<ogonek::nfc>(input) };
        REQUIRE(out.storage() == normalized);
    }
}

TEST_CASE("canonical equivalence", "Canonical equivalence") {
    std::u32string a = U"\x1E69\x1E0B\x0323\x0071\x0307\x0323";
    std::u32string b = U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307";
    std::u32string c = U"\x0073\x0307\x0323\x0064\x0323\x0307\x0071\x0323\x0307";
    std::u32string d = U"\x0074\x0307\x0323\x0064\x0323\x0307\x0071\x0323\x0307";

    REQUIRE(ogonek::canonically_equivalent(a, a));
    REQUIRE(ogonek::canonically_equivalent(a, b));
    REQUIRE(ogonek::canonically_equivalent(a, c));
    REQUIRE(!ogonek::canonically_equivalent(a, d));

    REQUIRE(ogonek::canonically_equivalent(b, a));
    REQUIRE(ogonek::canonically_equivalent(b, b));
    REQUIRE(ogonek::canonically_equivalent(b, c));
    REQUIRE(!ogonek::canonically_equivalent(b, d));

    REQUIRE(ogonek::canonically_equivalent(c, a));
    REQUIRE(ogonek::canonically_equivalent(c, b));
    REQUIRE(ogonek::canonically_equivalent(c, c));
    REQUIRE(!ogonek::canonically_equivalent(c, d));

    REQUIRE(!ogonek::canonically_equivalent(d, a));
    REQUIRE(!ogonek::canonically_equivalent(d, b));
    REQUIRE(!ogonek::canonically_equivalent(d, c));
    REQUIRE(ogonek::canonically_equivalent(d, d));
}


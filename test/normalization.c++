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

namespace {
    struct normalization_test {
        char32_t const* input;
        char32_t const* nfc;
        char32_t const* nfd;
    };
    
    normalization_test normalization_test_data[] = {
        #include "normalization_test.g.inl"
    };
    void test_norm(normalization_test const& test) {
        using test_text = ogonek::text<ogonek::utf32>;
        std::u32string input { test.input };
        std::u32string nfc_expected { test.nfc };
        std::u32string nfd_expected { test.nfd };
        
        test_text nfc { ogonek::normalize<ogonek::nfc>(input) };
        CHECK(nfc.storage() == nfc_expected);
        
        test_text nfd { ogonek::normalize<ogonek::nfd>(input) };
        CHECK(nfd.storage() == nfd_expected);
    }
}

TEST_CASE("normalization", "Normalization tests") {
    SECTION("official", "official normalization tests") {
        for(auto&& test : normalization_test_data) {
            test_norm(test);
        }
    }
    SECTION("madness", "crazy test with ten thousand umlauts") {
        using test_text = ogonek::text<ogonek::utf32>;
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


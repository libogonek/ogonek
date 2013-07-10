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

#include "utils.h++"
#include <catch.h++>

namespace {
    struct normalization_test {
        ogonek::code_point const* input;
        ogonek::code_point const* nfc;
        ogonek::code_point const* nfd;
        ogonek::code_point const* nfkc;
        ogonek::code_point const* nfkd;
    };

    normalization_test normalization_test_data[] = {
        #include "normalization_test.g.inl"
    };
    void test_norm(normalization_test const& test) {
        test::ustring input { test.input };
        test::ustring nfc_expected { test.nfc };
        test::ustring nfd_expected { test.nfd };
        test::ustring nfkc_expected { test.nfkc };
        test::ustring nfkd_expected { test.nfkd };

        test::utext nfc { ogonek::normalize<ogonek::nfc>(input) };
        REQUIRE(nfc.storage() == nfc_expected);
        REQUIRE(ogonek::is_normalized<ogonek::nfc>(nfc));
        REQUIRE_FALSE(bool(!ogonek::is_normalized_quick<ogonek::nfc>(nfc)));

        test::utext nfd { ogonek::normalize<ogonek::nfd>(input) };
        REQUIRE(nfd.storage() == nfd_expected);
        REQUIRE(ogonek::is_normalized<ogonek::nfd>(nfd));
        REQUIRE(ogonek::is_normalized_quick<ogonek::nfd>(nfd));

        test::utext nfkc { ogonek::normalize<ogonek::nfkc>(input) };
        REQUIRE(nfkc.storage() == nfkc_expected);
        REQUIRE(ogonek::is_normalized<ogonek::nfkc>(nfkc));
        REQUIRE_FALSE(bool(!ogonek::is_normalized_quick<ogonek::nfkc>(nfkc)));

        test::utext nfkd { ogonek::normalize<ogonek::nfkd>(input) };
        REQUIRE(nfkd.storage() == nfkd_expected);
        REQUIRE(ogonek::is_normalized<ogonek::nfkd>(nfkd));
        REQUIRE(ogonek::is_normalized_quick<ogonek::nfkd>(nfkd));
    }
}

TEST_CASE("normalization", "Normalization tests") {
    SECTION("official", "official normalization tests") {
        for(auto&& test : normalization_test_data) {
            test_norm(test);
        }
    }
    SECTION("query", "Normalization query tests") {
        std::u32string a = U"bla\u0328h";
        REQUIRE_FALSE(ogonek::is_normalized<ogonek::nfc>(a));
        REQUIRE_FALSE(ogonek::is_normalized<ogonek::nfkc>(a));
        REQUIRE_FALSE(bool(ogonek::is_normalized_quick<ogonek::nfc>(a)));
        REQUIRE_FALSE(bool(ogonek::is_normalized_quick<ogonek::nfkc>(a)));

        std::u32string b = U"bl\u00e4h";
        REQUIRE_FALSE(ogonek::is_normalized<ogonek::nfd>(b));
        REQUIRE_FALSE(ogonek::is_normalized<ogonek::nfkd>(b));
        REQUIRE_FALSE(ogonek::is_normalized_quick<ogonek::nfd>(b));
        REQUIRE_FALSE(ogonek::is_normalized_quick<ogonek::nfkd>(b));
    }
    SECTION("madness", "crazy test with ten thousand umlauts") {
        test::ustring input = U"2";
        input.reserve(10004);
        for(int i = 0; i < 10000; ++i) {
            input += U"\x0308";
        }
        input += U"\x0323";
        input += U"3";

        test::ustring normalized = U"2";
        normalized.reserve(10004);
        normalized += U"\x0323";
        for(int i = 0; i < 10000; ++i) {
            normalized += U"\x0308";
        }
        normalized += U"3";

        test::utext out { ogonek::normalize<ogonek::nfc>(input) };
        REQUIRE(out.storage() == normalized);
    }
}
TEST_CASE("whatever", "") {
    test::ustring a = U"\x0073\x0323\x0307\x0064\x0307\x0323\x0071\x0307\x0323";

    auto b = seq::as_sequence(a);
    auto s = seq::flat_map(ogonek::detail::combining_class_order{}, seq::generate(ogonek::detail::collect_before_starter<decltype(b)>(b)));
    test::ustring v = seq::materialize(s);
    test::ustring expected = U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307";

    REQUIRE(v == expected);
}

TEST_CASE("canonical equivalence", "Canonical equivalence") {
    test::ustring a = U"\x1E69\x1E0B\x0323\x0071\x0307\x0323";
    test::ustring b = U"\x0073\x0323\x0307\x0064\x0323\x0307\x0071\x0323\x0307";
    test::ustring c = U"\x0073\x0307\x0323\x0064\x0323\x0307\x0071\x0323\x0307";
    test::ustring d = U"\x0074\x0307\x0323\x0064\x0323\x0307\x0071\x0323\x0307";

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


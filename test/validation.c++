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

// Tests for validation in <ogonek/encoding/utf?.h++>

#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>

#include "utils.h++"
#include <catch.h++>

namespace seq = ogonek::seq;
using namespace test::literal;
using utf8_string = test::string<ogonek::utf8>;
using utf16_string = test::string<ogonek::utf16>;
using utf32_string = test::string<ogonek::utf32>;

namespace {
    utf8_string operator"" _s(char const* literal, std::size_t size) { return { literal, size }; }
    utf16_string operator"" _s(char16_t const* literal, std::size_t size) { return { literal, size }; }
    utf32_string operator"" _s(char32_t const* literal, std::size_t size) { return { literal, size }; }
} // namespace

TEST_CASE("utf8-validation", "Validation of UTF-8") {
    SECTION("valid", "Accepting valid bytes") {
        auto encoded = u8"\u0041\u00C5\u1EA0\U0001F4A9"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
    SECTION("invalid", "Rejecting invalid bytes") {
        auto encoded = u8"\u0041\xC0\u00C5\xC1\xF5"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\uFFFD\u00C5\uFFFD\uFFFD"_u);
    }
    SECTION("unexpected continuation", "Rejecting unexpected continuation bytes") {
        auto encoded = "\u0041\u00C5\x84\u0042"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\uFFFD\u0042"_u);
    }
    SECTION("not enough continuation", "Rejecting start bytes not followed by enough continuation bytes") {
        auto encoded = "\u0041\xF3\x85\u00C5\u0042"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\uFFFD\u00C5\u0042"_u);
    }
    SECTION("overlong", "Rejecting overlong forms") {
        auto encoded = "\u0041\xC0\x80\u00C5\u0042"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\uFFFD\uFFFD\u00C5\u0042"_u);
    }
    SECTION("invalid code_point", "Rejecting sequences that decode to values above 0x10FFFF or surrogates") {
        auto encoded = "\u0041\xF4\x90\x80\x80\u0042\xED\xA0\x80"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\uFFFD\u0042\uFFFD"_u);
    }
}

TEST_CASE("utf16-validation", "Validation of UTF-16") {
    SECTION("valid", "Accepting valid sequences") {
        auto encoded = u"\u0041\u00C5\u1EA0\U0001F4A9"_s;
        auto range = ogonek::decode<ogonek::utf16>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
    SECTION("unpaired surrogates", "Rejecting unpaired surrogates") {
        auto encoded = u"\u0041\xD83D\u00C5\xDCA9\u1EA0"_s;
        auto range = ogonek::decode<ogonek::utf16>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\uFFFD\u00C5\uFFFD\u1EA0"_u);
    }
    SECTION("inverted surrogates", "Rejecting inverted surrogates") {
        auto encoded = u"\u0041\u00C5\xDCA9\xD83D\u1EA0"_s;
        auto range = ogonek::decode<ogonek::utf16>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\uFFFD\uFFFD\u1EA0"_u);
    }
}

TEST_CASE("utf32-validation", "Validation of UTF-32") {
    SECTION("valid", "Accepting valid sequences") {
        auto encoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::decode<ogonek::utf32>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
    SECTION("invalid", "Rejecting code_points above U+10FFFF") {
        auto encoded = U"\u0041\u00C5\x21F4A9"_s;
        auto range = ogonek::decode<ogonek::utf32>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\uFFFD"_u);
    }
    SECTION("surrogates", "Rejecting surrogates") {
        auto encoded = U"\u0041\u00C5\xD932\xDC43"_s;
        auto range = ogonek::decode<ogonek::utf32>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\uFFFD\uFFFD"_u);
    }
}


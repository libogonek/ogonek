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

// Tests for <ogonek/encoding/utf?.h++>

#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>

#include <taussig/interop.h++>

#include "utils.h++"
#include <catch.h++>

using namespace test::literal;
using utf8_string = test::string<ogonek::utf8>;
using utf16_string = test::string<ogonek::utf16>;
using utf32_string = test::string<ogonek::utf32>;

namespace {
    utf8_string operator"" _s(char const* literal, std::size_t size) { return { literal, size }; }
    utf16_string operator"" _s(char16_t const* literal, std::size_t size) { return { literal, size }; }
    utf32_string operator"" _s(char32_t const* literal, std::size_t size) { return { literal, size }; }
} // namespace

TEST_CASE("utf8", "UTF-8 encoding form") {
    SECTION("encode", "Encoding UTF-8") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf8>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<utf8_string>(range);
        REQUIRE(encoded == u8"\u0041\u00C5\u1EA0\U0001F4A9"_s);
    }
    SECTION("decode", "Decoding UTF-8") {
        auto encoded = u8"\u0041\u00C5\u1EA0\U0001F4A9"_s;
        auto range = ogonek::decode<ogonek::utf8>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}

TEST_CASE("utf16", "UTF-16 encoding form") {
    SECTION("encode", "Encoding UTF-16") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf16>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<utf16_string>(range);
        REQUIRE(encoded == u"\u0041\u00C5\u1EA0\U0001F4A9"_s);
    }
    SECTION("decode", "Decoding UTF-16") {
        auto encoded = u"\u0041\u00C5\u1EA0\U0001F4A9"_s;
        auto range = ogonek::decode<ogonek::utf16>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}

TEST_CASE("utf32", "UTF-32 encoding form") {
    SECTION("encode", "Encoding UTF-32") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf32>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<utf32_string>(range);
        REQUIRE(encoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_s);
    }
    SECTION("decode", "Decoding UTF-32") {
        auto encoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_s;
        auto range = ogonek::decode<ogonek::utf32>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}


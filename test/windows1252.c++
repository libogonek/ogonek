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

// Tests for <ogonek/encoding/windows1252.h++>

#include <ogonek/encoding/windows1252.h++>

#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>

#include <taussig/interop.h++>

#include "utils.h++"
#include <catch.h++>

using namespace test::literal;
using windows1252_string = test::string<ogonek::windows1252>;

namespace {
    windows1252_string operator"" _s(char const* literal, std::size_t size) { return { literal, size }; }
} // namespace

TEST_CASE("windows1252", "Windows-1252 encoding form") {
    SECTION("encode", "Encoding Windows-1252") {
        auto decoded = U"\u0041\u20AC"_u;
        auto range = ogonek::encode<ogonek::windows1252>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<windows1252_string>(range);
        REQUIRE(encoded == "\x41\x80"_s);
    }
    SECTION("decode", "Decoding Windows-1252") {
        auto encoded = "\x41\x80"_s;
        auto range = ogonek::decode<ogonek::windows1252>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u20AC"_u);
    }
    SECTION("validation", "Validating Windows-1252") {
        auto encoded = "\x41\x80\x81"_s;
        auto range = ogonek::decode<ogonek::windows1252>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u20AC\uFFFD"_u);
    }
    SECTION("replacement", "Windows-1252's custom replacement character (?)") {
        auto decoded = U"\u0041\u20AC\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::windows1252>(decoded, ogonek::replace_errors);
        auto encoded = seq::materialize<windows1252_string>(range);
        REQUIRE(encoded == "\x41\x80\x3F"_s);
    }
}

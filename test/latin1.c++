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

// Tests for <ogonek/encoding/latin1.h++>

#include <ogonek/encoding/latin1.h++>

#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>

#include "utils.h++"
#include <catch.h++>

namespace seq = ogonek::seq;
using namespace test::literal;
using latin1_string = test::string<ogonek::latin1>;

namespace {
    latin1_string operator"" _s(char const* literal, std::size_t size) { return { literal, size }; }
} // namespace

TEST_CASE("latin1", "ISO-8859-1 encoding form") {
    SECTION("encode", "Encoding ISO-8859-1") {
        auto decoded = U"\u0041\u0082"_u;
        auto range = ogonek::encode<ogonek::latin1>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<latin1_string>(range);
        REQUIRE(encoded == "\x41\x82"_s);
    }
    SECTION("decode", "Decoding ISO-8859-1") {
        auto encoded = "\x41\x82"_s;
        auto range = ogonek::decode<ogonek::latin1>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u0082"_u);
    }
    SECTION("validation", "Validating ISO-8859-1") {
        auto encoded = "\x41\x82\xFF"_s;
        auto range = ogonek::decode<ogonek::latin1>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u0082\u00FF"_u);
    }
    SECTION("replacement", "ISO-8859-1's custom replacement character (?)") {
        auto decoded = U"\u0041\u0032\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::latin1>(decoded, ogonek::replace_errors);
        auto encoded = seq::materialize<latin1_string>(range);
        REQUIRE(encoded == "\x41\x32\x3F"_s);
    }
}

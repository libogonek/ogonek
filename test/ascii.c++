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

// Tests for <ogonek/encoding/ascii.h++>

#include <ogonek/encoding/ascii.h++>

#include <ogonek/encoding/encode.h++>
#include <ogonek/error/assume_valid.h++>
#include <ogonek/error/replace_errors.h++>

#include <taussig/primitives.h++>
#include <taussig/interop.h++>

#include <cstddef>

#include "utils.h++"
#include <catch.h++>

using namespace test::literal;
using ascii_string = test::string<ogonek::ascii>;

namespace {
    ascii_string operator"" _s(char const* literal, std::size_t size) { return { literal, size }; }
} // namespace

TEST_CASE("ascii", "ASCII encoding form") {
    SECTION("encode", "Encoding ASCII") {
        auto decoded = U"\u0041\u0032"_u;
        auto range = ogonek::encode<ogonek::ascii>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<ascii_string>(range);
        REQUIRE(encoded == "\x41\x32"_s);
    }
    SECTION("decode", "Decoding ASCII") {
        auto encoded = "\x41\x32"_s;
        auto range = ogonek::decode<ogonek::ascii>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u0032"_u);
    }
    SECTION("validation", "Validating ASCII") {
        auto encoded = "\x41\x32\x80"_s;
        auto range = ogonek::decode<ogonek::ascii>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u0032\uFFFD"_u);
    }
    SECTION("replacement", "ASCII's custom replacement character (?)") {
        auto decoded = U"\u0041\u0032\u0080"_u;
        auto range = ogonek::encode<ogonek::ascii>(decoded, ogonek::replace_errors);
        auto encoded = seq::materialize<ascii_string>(range);
        REQUIRE(encoded == "\x41\x32\x3F"_s);
    }
}

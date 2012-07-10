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

// Tests for <ogonek/encoding/utf?.h++>

//#include <ogonek/encoding/utf8.h++>
//#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/types.h++>

#include <catch.h++>

TEST_CASE("utf32", "UTF-32 encoding form") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<char32_t> encoded;
        ogonek::utf32::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 4);
        CHECK(encoded[0] == 0x0041);
        CHECK(encoded[1] == 0x00C5);
        CHECK(encoded[2] == 0x1EA0);
        CHECK(encoded[3] == 0x1F4A9);
    }
    SECTION("decode", "Decoding UTF-32") {
        std::initializer_list<char32_t> encoded = { 0x0041, 0x00C5, 0x1EA0, 0x1F4A9 };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == 0x0041_u);
        CHECK(decoded[1] == 0x00C5_u);
        CHECK(decoded[2] == 0x1EA0_u);
        CHECK(decoded[3] == 0x1F4A9_u);
    }
}


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

// Tests for <ogonek/encoding/encoding_scheme.h++>

#include <ogonek/encoding/encoding_scheme.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/types.h++>

#include <catch.h++>

TEST_CASE("utf16le", "UTF-16LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16LE") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<ogonek::byte> encoded;
        ogonek::utf16le::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 10);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0x00_b);
        CHECK(encoded[2] == 0xC5_b);
        CHECK(encoded[3] == 0x00_b);
        CHECK(encoded[4] == 0xA0_b);
        CHECK(encoded[5] == 0x1E_b);
        CHECK(encoded[6] == 0x3D_b);
        CHECK(encoded[7] == 0xD8_b);
        CHECK(encoded[8] == 0xA9_b);
        CHECK(encoded[9] == 0xDC_b);
    }
    SECTION("decode", "Decoding UTF-16LE") {
        auto encoded = { 0x41_b, 0x00_b, 0xC5_b, 0x00_b, 0xA0_b,
                         0x1E_b, 0x3D_b, 0xD8_b, 0xA9_b, 0xDC_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16le::decode(encoded, std::back_inserter(decoded));
        CHECK(decoded.size() == 4);
        CHECK(decoded[0] == 0x0041_u);
        CHECK(decoded[1] == 0x00C5_u);
        CHECK(decoded[2] == 0x1EA0_u);
        CHECK(decoded[3] == 0x1F4A9_u);
    }
}

TEST_CASE("utf16be", "UTF-16BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16BE") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<ogonek::byte> encoded;
        ogonek::utf16be::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 10);
        CHECK(encoded[0] == 0x00_b);
        CHECK(encoded[1] == 0x41_b);
        CHECK(encoded[2] == 0x00_b);
        CHECK(encoded[3] == 0xC5_b);
        CHECK(encoded[4] == 0x1E_b);
        CHECK(encoded[5] == 0xA0_b);
        CHECK(encoded[6] == 0xD8_b);
        CHECK(encoded[7] == 0x3D_b);
        CHECK(encoded[8] == 0xDC_b);
        CHECK(encoded[9] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-16BE") {
        auto encoded = { 0x00_b, 0x41_b, 0x00_b, 0xC5_b, 0x1E_b,
                         0xA0_b, 0xD8_b, 0x3D_b, 0xDC_b, 0xA9_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16be::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == 0x0041_u);
        CHECK(decoded[1] == 0x00C5_u);
        CHECK(decoded[2] == 0x1EA0_u);
        CHECK(decoded[3] == 0x1F4A9_u);
    }
}

TEST_CASE("utf32le", "UTF-32LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32LE") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<ogonek::byte> encoded;
        ogonek::utf32le::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 16);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0x00_b);
        CHECK(encoded[2] == 0x00_b);
        CHECK(encoded[3] == 0x00_b);
        CHECK(encoded[4] == 0xC5_b);
        CHECK(encoded[5] == 0x00_b);
        CHECK(encoded[6] == 0x00_b);
        CHECK(encoded[7] == 0x00_b);
        CHECK(encoded[8] == 0xA0_b);
        CHECK(encoded[9] == 0x1E_b);
        CHECK(encoded[10] == 0x00_b);
        CHECK(encoded[11] == 0x00_b);
        CHECK(encoded[12] == 0xA9_b);
        CHECK(encoded[13] == 0xF4_b);
        CHECK(encoded[14] == 0x01_b);
        CHECK(encoded[15] == 0x00_b);
    }
    SECTION("decode", "Decoding UTF-32LE") {
        auto encoded = { 0x41_b, 0x00_b, 0x00_b, 0x00_b,
                         0xC5_b, 0x00_b, 0x00_b, 0x00_b,
                         0xA0_b, 0x1E_b, 0x00_b, 0x00_b,
                         0xA9_b, 0xF4_b, 0x01_b, 0x00_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32le::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == 0x0041_u);
        CHECK(decoded[1] == 0x00C5_u);
        CHECK(decoded[2] == 0x1EA0_u);
        CHECK(decoded[3] == 0x1F4A9_u);
    }
}


TEST_CASE("utf32be", "UTF-32BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32BE") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<ogonek::byte> encoded;
        ogonek::utf32be::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 16);
        CHECK(encoded[0] == 0x00_b);
        CHECK(encoded[1] == 0x00_b);
        CHECK(encoded[2] == 0x00_b);
        CHECK(encoded[3] == 0x41_b);
        CHECK(encoded[4] == 0x00_b);
        CHECK(encoded[5] == 0x00_b);
        CHECK(encoded[6] == 0x00_b);
        CHECK(encoded[7] == 0xC5_b);
        CHECK(encoded[8] == 0x00_b);
        CHECK(encoded[9] == 0x00_b);
        CHECK(encoded[10] == 0x1E_b);
        CHECK(encoded[11] == 0xA0_b);
        CHECK(encoded[12] == 0x00_b);
        CHECK(encoded[13] == 0x01_b);
        CHECK(encoded[14] == 0xF4_b);
        CHECK(encoded[15] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-32BE") {
        auto encoded = { 0x00_b, 0x00_b, 0x00_b, 0x41_b,
                         0x00_b, 0x00_b, 0x00_b, 0xC5_b,
                         0x00_b, 0x00_b, 0x1E_b, 0xA0_b,
                         0x00_b, 0x01_b, 0xF4_b, 0xA9_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32be::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == 0x0041_u);
        CHECK(decoded[1] == 0x00C5_u);
        CHECK(decoded[2] == 0x1EA0_u);
        CHECK(decoded[3] == 0x1F4A9_u);
    }
}


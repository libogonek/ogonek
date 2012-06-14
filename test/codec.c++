// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for <ogonek/codec.h++>

#include <catch.h++>

#include <ogonek/codec.h++>

#include <initializer_list>

TEST_CASE("utf8", "UTF-8 codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-8") {
        ogonek::codec::utf8 codec;

        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 10);
        REQUIRE(encoded[0] == 0x41_b);
        REQUIRE(encoded[1] == 0xC3_b);
        REQUIRE(encoded[2] == 0x85_b);
        REQUIRE(encoded[3] == 0xE1_b);
        REQUIRE(encoded[4] == 0xBA_b);
        REQUIRE(encoded[5] == 0xA0_b);
        REQUIRE(encoded[6] == 0xF0_b);
        REQUIRE(encoded[7] == 0x9F_b);
        REQUIRE(encoded[8] == 0x92_b);
        REQUIRE(encoded[9] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-8") {
        ogonek::codec::utf8 codec;

        auto encoded = { 0x41_b, 0xC3_b, 0x85_b, 0xE1_b, 0xBA_b,
                         0xA0_b, 0xF0_b, 0x9F_b, 0x92_b, 0xA9_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it, encoded.end());
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 4);
        REQUIRE(decoded[0] == 0x0041_u);
        REQUIRE(decoded[1] == 0x00C5_u);
        REQUIRE(decoded[2] == 0x1EA0_u);
        REQUIRE(decoded[3] == 0x1F4A9_u);
    }
}

TEST_CASE("utf16le", "UTF-16LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16LE") {
        ogonek::codec::utf16le codec;

        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 10);
        REQUIRE(encoded[0] == 0x41_b);
        REQUIRE(encoded[1] == 0x00_b);
        REQUIRE(encoded[2] == 0xC5_b);
        REQUIRE(encoded[3] == 0x00_b);
        REQUIRE(encoded[4] == 0xA0_b);
        REQUIRE(encoded[5] == 0x1E_b);
        REQUIRE(encoded[6] == 0x3D_b);
        REQUIRE(encoded[7] == 0xD8_b);
        REQUIRE(encoded[8] == 0xA9_b);
        REQUIRE(encoded[9] == 0xDC_b);
    }
    SECTION("decode", "Decoding UTF-16LE") {
        ogonek::codec::utf16le codec;

        auto encoded = { 0x41_b, 0x00_b, 0xC5_b, 0x00_b, 0xA0_b,
                         0x1E_b, 0x3D_b, 0xD8_b, 0xA9_b, 0xDC_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it, encoded.end());
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 4);
        REQUIRE(decoded[0] == 0x0041_u);
        REQUIRE(decoded[1] == 0x00C5_u);
        REQUIRE(decoded[2] == 0x1EA0_u);
        REQUIRE(decoded[3] == 0x1F4A9_u);
    }
}

TEST_CASE("utf16be", "UTF-16BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16BE") {
        ogonek::codec::utf16be codec;

        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 10);
        REQUIRE(encoded[0] == 0x00_b);
        REQUIRE(encoded[1] == 0x41_b);
        REQUIRE(encoded[2] == 0x00_b);
        REQUIRE(encoded[3] == 0xC5_b);
        REQUIRE(encoded[4] == 0x1E_b);
        REQUIRE(encoded[5] == 0xA0_b);
        REQUIRE(encoded[6] == 0xD8_b);
        REQUIRE(encoded[7] == 0x3D_b);
        REQUIRE(encoded[8] == 0xDC_b);
        REQUIRE(encoded[9] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-16BE") {
        ogonek::codec::utf16be codec;

        auto encoded = { 0x00_b, 0x41_b, 0x00_b, 0xC5_b, 0x1E_b,
                         0xA0_b, 0xD8_b, 0x3D_b, 0xDC_b, 0xA9_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it, encoded.end());
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 4);
        REQUIRE(decoded[0] == 0x0041_u);
        REQUIRE(decoded[1] == 0x00C5_u);
        REQUIRE(decoded[2] == 0x1EA0_u);
        REQUIRE(decoded[3] == 0x1F4A9_u);
    }
}

TEST_CASE("utf32le", "UTF-32LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32LE") {
        ogonek::codec::utf32le codec;

        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 16);
        REQUIRE(encoded[0] == 0x41_b);
        REQUIRE(encoded[1] == 0x00_b);
        REQUIRE(encoded[2] == 0x00_b);
        REQUIRE(encoded[3] == 0x00_b);
        REQUIRE(encoded[4] == 0xC5_b);
        REQUIRE(encoded[5] == 0x00_b);
        REQUIRE(encoded[6] == 0x00_b);
        REQUIRE(encoded[7] == 0x00_b);
        REQUIRE(encoded[8] == 0xA0_b);
        REQUIRE(encoded[9] == 0x1E_b);
        REQUIRE(encoded[10] == 0x00_b);
        REQUIRE(encoded[11] == 0x00_b);
        REQUIRE(encoded[12] == 0xA9_b);
        REQUIRE(encoded[13] == 0xF4_b);
        REQUIRE(encoded[14] == 0x01_b);
        REQUIRE(encoded[15] == 0x00_b);
    }
    SECTION("decode", "Decoding UTF-32LE") {
        ogonek::codec::utf32le codec;

        auto encoded = { 0x41_b, 0x00_b, 0x00_b, 0x00_b,
                         0xC5_b, 0x00_b, 0x00_b, 0x00_b,
                         0xA0_b, 0x1E_b, 0x00_b, 0x00_b,
                         0xA9_b, 0xF4_b, 0x01_b, 0x00_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it, encoded.end());
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 4);
    }
}


TEST_CASE("utf32be", "UTF-32BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32BE") {
        ogonek::codec::utf32be codec;

        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 16);
        REQUIRE(encoded[0] == 0x00_b);
        REQUIRE(encoded[1] == 0x00_b);
        REQUIRE(encoded[2] == 0x00_b);
        REQUIRE(encoded[3] == 0x41_b);
        REQUIRE(encoded[4] == 0x00_b);
        REQUIRE(encoded[5] == 0x00_b);
        REQUIRE(encoded[6] == 0x00_b);
        REQUIRE(encoded[7] == 0xC5_b);
        REQUIRE(encoded[8] == 0x00_b);
        REQUIRE(encoded[9] == 0x00_b);
        REQUIRE(encoded[10] == 0x1E_b);
        REQUIRE(encoded[11] == 0xA0_b);
        REQUIRE(encoded[12] == 0x00_b);
        REQUIRE(encoded[13] == 0x01_b);
        REQUIRE(encoded[14] == 0xF4_b);
        REQUIRE(encoded[15] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-32BE") {
        ogonek::codec::utf32be codec;

        auto encoded = { 0x00_b, 0x00_b, 0x00_b, 0x41_b,
                         0x00_b, 0x00_b, 0x00_b, 0xC5_b,
                         0x00_b, 0x00_b, 0x1E_b, 0xA0_b,
                         0x00_b, 0x01_b, 0xF4_b, 0xA9_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it, encoded.end());
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 4);
        REQUIRE(decoded[0] == 0x0041_u);
        REQUIRE(decoded[1] == 0x00C5_u);
        REQUIRE(decoded[2] == 0x1EA0_u);
        REQUIRE(decoded[3] == 0x1F4A9_u);
    }
}

#if 0
TEST_CASE("utf7", "UTF-7 codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32BE") {
        ogonek::codec::utf7 codec;

        auto decoded = { 0xA3_u, 0x2020_u, 0x31_u, 0x34_u, 0x66_u, 0x1E99_u }
        auto encoded = codec.encode(decoded.begin(), decoded.end());
        REQUIRE(encoded.size() == 16);
        REQUIRE(encoded[0] == 0x2B_b);
        REQUIRE(encoded[1] == 0x41_b);
        REQUIRE(encoded[2] == 0x4B_b);
        REQUIRE(encoded[3] == 0x4D_b);
        REQUIRE(encoded[4] == 0x67_b);
        REQUIRE(encoded[5] == 0x49_b);
        REQUIRE(encoded[6] == 0x41_b);
        REQUIRE(encoded[7] == 0x2D_b);
        REQUIRE(encoded[8] == 0x31_b);
        REQUIRE(encoded[9] == 0x34_b);
        REQUIRE(encoded[10] == 0x66_b);
        REQUIRE(encoded[11] == 0x2B_b);
        REQUIRE(encoded[12] == 0x48_b);
        REQUIRE(encoded[13] == 0x70_b);
        REQUIRE(encoded[14] == 0x6B_b);
        REQUIRE(encoded[15] == 0x2D_b);
    }
    SECTION("decode", "Decoding UTF-32BE") {
        ogonek::codec::utf7 codec;

        auto encoded = { 0x2B_b, 0x41_b, 0x4B_b, 0x4D_b,
                         0x67_b, 0x49_b, 0x41_b, 0x2D_b,
                         0x31_b, 0x34_b, 0x66_b, 0x2B_b,
                         0x48_b, 0x70_b, 0x6B_b, 0x2D_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it);
        REQUIRE(it == encoded.end());
        REQUIRE(decoded.size() == 6);
        auto decoded = { 0xA3_u, 0x2020_u, 0x31_u, 0x34_u, 0x66_u, 0x1E99_u }
        REQUIRE(decoded[0] == 0xA3_u);
        REQUIRE(decoded[1] == 0x2020_u);
        REQUIRE(decoded[2] == 0x31_u);
        REQUIRE(decoded[3] == 0x34_u);
        REQUIRE(decoded[4] == 0x66_u);
        REQUIRE(decoded[5] == 0x1E99_u);
    }
}
#endif


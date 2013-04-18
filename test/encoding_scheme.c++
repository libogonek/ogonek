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

// Tests for <ogonek/encoding/encoding_scheme.h++>

#include <ogonek/encoding.h++>
#include <ogonek/types.h++>
#include <ogonek/error.h++>

#include <ogonek/encoding/utf16le.h++>
#include <ogonek/encoding/utf16be.h++>
#include <ogonek/encoding/utf32le.h++>
#include <ogonek/encoding/utf32be.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>

#include <vector>

#include <catch.h++>

TEST_CASE("utf16le", "UTF-16LE codec") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-16LE") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf16le>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
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
        auto range = ogonek::decode<ogonek::utf16le>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        CHECK(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

TEST_CASE("utf16be", "UTF-16BE codec") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-16BE") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf16be>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
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
        auto range = ogonek::decode<ogonek::utf16be>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

TEST_CASE("utf32le", "UTF-32LE codec") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-32LE") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf32le>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
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
        auto range = ogonek::decode<ogonek::utf32le>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}


TEST_CASE("utf32be", "UTF-32BE codec") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-32BE") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf32be>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
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
        auto range = ogonek::decode<ogonek::utf32be>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}


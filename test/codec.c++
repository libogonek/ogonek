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

        auto decoded1 = 0x0041_u;
        auto encoded1 = codec.encode(decoded1);
        REQUIRE(encoded1.size() == 1);
        REQUIRE(encoded1.begin()[0] == 0x41_b);

        auto decoded2 = 0x00C5_u;
        auto encoded2 = codec.encode(decoded2);
        REQUIRE(encoded2.size() == 2);
        REQUIRE(encoded2.begin()[0] == 0xC3_b);
        REQUIRE(encoded2.begin()[1] == 0x85_b);

        auto decoded3 = 0x1EA0_u;
        auto encoded3 = codec.encode(decoded3);
        REQUIRE(encoded3.size() == 3);
        REQUIRE(encoded3.begin()[0] == 0xE1_b);
        REQUIRE(encoded3.begin()[1] == 0xBA_b);
        REQUIRE(encoded3.begin()[2] == 0xA0_b);

        auto decoded4 = 0x1F4A9_u;
        auto encoded4 = codec.encode(decoded4);
        REQUIRE(encoded4.size() == 4);
        REQUIRE(encoded4.begin()[0] == 0xF0_b);
        REQUIRE(encoded4.begin()[1] == 0x9F_b);
        REQUIRE(encoded4.begin()[2] == 0x92_b);
        REQUIRE(encoded4.begin()[3] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-8") {
        ogonek::codec::utf8 codec;

        auto encoded1 = { 0x41_b };
        auto it1 = encoded1.begin();
        auto decoded1 = codec.decode(it1);
        REQUIRE(it1 == encoded1.end());
        REQUIRE(decoded1 == 0x0041_u);

        auto encoded2 = { 0xC3_b, 0x85_b };
        auto it2 = encoded2.begin();
        auto decoded2 = codec.decode(it2);
        REQUIRE(it2 == encoded2.end());
        REQUIRE(decoded2 == 0x00C5_u);

        auto encoded3 = { 0xE1_b, 0xBA_b, 0xA0_b };
        auto it3 = encoded3.begin();
        auto decoded3 = codec.decode(it3);
        REQUIRE(it3 == encoded3.end());
        REQUIRE(decoded3 == 0x1EA0_u);

        auto encoded4 = { 0xF0_b, 0x9F_b, 0x92_b, 0xA9_b };
        auto it4 = encoded4.begin();
        auto decoded4 = codec.decode(it4);
        REQUIRE(it4 == encoded4.end());
        REQUIRE(decoded4 == 0x1F4A9_u);
    }
}

TEST_CASE("utf16le", "UTF-16LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16LE") {
        ogonek::codec::utf16le codec;

        auto decoded1 = 0x1EA0_u;
        auto encoded1 = codec.encode(decoded1);
        REQUIRE(encoded1.size() == 2);
        REQUIRE(encoded1.begin()[0] == 0xA0_b);
        REQUIRE(encoded1.begin()[1] == 0x1E_b);

        auto decoded2 = 0x1F4A9_u;
        auto encoded2 = codec.encode(decoded2);
        REQUIRE(encoded2.size() == 4);
        REQUIRE(encoded2.begin()[0] == 0x3D_b);
        REQUIRE(encoded2.begin()[1] == 0xD8_b);
        REQUIRE(encoded2.begin()[2] == 0xA9_b);
        REQUIRE(encoded2.begin()[3] == 0xDC_b);
    }
    SECTION("decode", "Decoding UTF-16LE") {
        ogonek::codec::utf16le codec;

        auto encoded1 = { 0xA0_b, 0x1E_b };
        auto it1 = encoded1.begin();
        auto decoded1 = codec.decode(it1);
        REQUIRE(it1 == encoded1.end());
        REQUIRE(decoded1 == 0x1EA0_u);

        auto encoded2 = { 0x3D_b, 0xD8_b, 0xA9_b, 0xDC_b };
        auto it2 = encoded2.begin();
        auto decoded2 = codec.decode(it2);
        REQUIRE(it2 == encoded2.end());
        REQUIRE(decoded2 == 0x1F4A9_u);
    }
}

TEST_CASE("utf16be", "UTF-16BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16BE") {
        ogonek::codec::utf16be codec;

        auto decoded1 = 0x1EA0_u;
        auto encoded1 = codec.encode(decoded1);
        REQUIRE(encoded1.size() == 2);
        REQUIRE(encoded1.begin()[0] == 0x1E_b);
        REQUIRE(encoded1.begin()[1] == 0xA0_b);

        auto decoded2 = 0x1F4A9_u;
        auto encoded2 = codec.encode(decoded2);
        REQUIRE(encoded2.size() == 4);
        REQUIRE(encoded2.begin()[0] == 0xD8_b);
        REQUIRE(encoded2.begin()[1] == 0x3D_b);
        REQUIRE(encoded2.begin()[2] == 0xDC_b);
        REQUIRE(encoded2.begin()[3] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-16BE") {
        ogonek::codec::utf16be codec;

        auto encoded1 = { 0x1E_b, 0xA0_b };
        auto it1 = encoded1.begin();
        auto decoded1 = codec.decode(it1);
        REQUIRE(it1 == encoded1.end());
        REQUIRE(decoded1 == 0x1EA0_u);

        auto encoded2 = { 0xD8_b, 0x3D_b, 0xDC_b, 0xA9_b };
        auto it2 = encoded2.begin();
        auto decoded2 = codec.decode(it2);
        REQUIRE(it2 == encoded2.end());
        REQUIRE(decoded2 == 0x1F4A9_u);
    }
}

TEST_CASE("utf32le", "UTF-32LE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32LE") {
        ogonek::codec::utf32le codec;

        auto decoded = 0x1F4A9_u;
        auto encoded = codec.encode(decoded);
        REQUIRE(encoded.size() == 4);
        REQUIRE(encoded.begin()[0] == 0xA9_b);
        REQUIRE(encoded.begin()[1] == 0xF4_b);
        REQUIRE(encoded.begin()[2] == 0x01_b);
        REQUIRE(encoded.begin()[3] == 0x00_b);
    }
    SECTION("decode", "Decoding UTF-32LE") {
        ogonek::codec::utf32le codec;

        auto encoded = { 0xA9_b, 0xF4_b, 0x01_b, 0x00_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it);
        REQUIRE(it == encoded.end());
        REQUIRE(decoded == 0x1F4A9_u);
    }
}


TEST_CASE("utf32be", "UTF-32BE codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-32BE") {
        ogonek::codec::utf32be codec;

        auto decoded = 0x1F4A9_u;
        auto encoded = codec.encode(decoded);
        REQUIRE(encoded.size() == 4);
        REQUIRE(encoded.begin()[0] == 0x00_b);
        REQUIRE(encoded.begin()[1] == 0x01_b);
        REQUIRE(encoded.begin()[2] == 0xF4_b);
        REQUIRE(encoded.begin()[3] == 0xA9_b);
    }
    SECTION("decode", "Decoding UTF-32BE") {
        ogonek::codec::utf32be codec;

        auto encoded = { 0x00_b, 0x01_b, 0xF4_b, 0xA9_b };
        auto it = encoded.begin();
        auto decoded = codec.decode(it);
        REQUIRE(it == encoded.end());
        REQUIRE(decoded == 0x1F4A9_u);
    }
}


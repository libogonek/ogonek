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

#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/encoding/utf7.h++>
#include <ogonek/types.h++>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <catch.h++>

TEST_CASE("utf8", "UTF-8 encoding form") {
    using namespace ogonek::literal;

    /*
    SECTION("encode", "Encoding UTF-8") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        auto range = ogonek::utf8::encode(decoded);
        std::vector<ogonek::byte> encoded(boost::begin(range), boost::end(range));
        REQUIRE(encoded.size() == 10);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0xC3_b);
        CHECK(encoded[2] == 0x85_b);
        CHECK(encoded[3] == 0xE1_b);
        CHECK(encoded[4] == 0xBA_b);
        CHECK(encoded[5] == 0xA0_b);
        CHECK(encoded[6] == 0xF0_b);
        CHECK(encoded[7] == 0x9F_b);
        CHECK(encoded[8] == 0x92_b);
        CHECK(encoded[9] == 0xA9_b);
    }
    */
    SECTION("decode", "Decoding UTF-8") {
        auto encoded = { 0x41_b, 0xC3_b, 0x85_b, 0xE1_b, 0xBA_b,
                         0xA0_b, 0xF0_b, 0x9F_b, 0x92_b, 0xA9_b };
        auto range = ogonek::utf8::decode(encoded);
        std::vector<ogonek::codepoint> decoded(boost::begin(range), boost::end(range));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

TEST_CASE("utf16", "UTF-16 encoding form") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-16") {
        auto decoded = { 0x0041_u, 0x00C5_u, 0x1EA0_u, 0x1F4A9_u };
        std::vector<char16_t> encoded;
        ogonek::utf16::encode(decoded, std::back_inserter(encoded));
        REQUIRE(encoded.size() == 5);
        CHECK(encoded[0] == u'\x0041');
        CHECK(encoded[1] == u'\x00C5');
        CHECK(encoded[2] == u'\x1EA0');
        CHECK(encoded[3] == u'\xD83D');
        CHECK(encoded[4] == u'\xDCA9');
    }
    SECTION("decode", "Decoding UTF-16") {
        std::initializer_list<char16_t> encoded = { 0x0041, 0x00C5, 0x1EA0, 0xD83D, 0xDCA9 };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

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

TEST_CASE("utf7", "UTF-7 codec") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding UTF-7") {
        auto decoded = { 0xA3_u, 0x2020_u, 0x31_u, 0x34_u, 0x66_u, 0x1E99_u };
        std::vector<ogonek::byte> encoded;
        ogonek::utf7::encode(decoded, std::back_inserter(encoded));
        CHECK(encoded.size() == 16);
        CHECK(encoded[0] == 0x2B_b);
        CHECK(encoded[1] == 0x41_b);
        CHECK(encoded[2] == 0x4B_b);
        CHECK(encoded[3] == 0x4D_b);
        CHECK(encoded[4] == 0x67_b);
        CHECK(encoded[5] == 0x49_b);
        CHECK(encoded[6] == 0x41_b);
        CHECK(encoded[7] == 0x2D_b);
        CHECK(encoded[8] == 0x31_b);
        CHECK(encoded[9] == 0x34_b);
        CHECK(encoded[10] == 0x66_b);
        CHECK(encoded[11] == 0x2B_b);
        CHECK(encoded[12] == 0x48_b);
        CHECK(encoded[13] == 0x70_b);
        CHECK(encoded[14] == 0x6B_b);
        CHECK(encoded[15] == 0x2D_b);
    }
    SECTION("decode", "Decoding UTF-7") {
        auto encoded = { 0x2B_b, 0x41_b, 0x4B_b, 0x4D_b,
                         0x67_b, 0x49_b, 0x41_b, 0x2D_b,
                         0x31_b, 0x34_b, 0x66_b, 0x2B_b,
                         0x48_b, 0x70_b, 0x6B_b, 0x2D_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf7::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 6);
        CHECK(decoded[0] == 0xA3_u);
        CHECK(decoded[1] == 0x2020_u);
        CHECK(decoded[2] == 0x31_u);
        CHECK(decoded[3] == 0x34_u);
        CHECK(decoded[4] == 0x66_u);
        CHECK(decoded[5] == 0x1E99_u);
    }
}


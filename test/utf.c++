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

#include <ogonek/encoding.h++>
#include <ogonek/types.h++>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>

#include <vector>

#include <catch.h++>

TEST_CASE("utf8", "UTF-8 encoding form") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-8") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf8>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector<ogonek::byte>>(range);
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
    SECTION("decode", "Decoding UTF-8") {
        auto encoded = { 0x41_b, 0xC3_b, 0x85_b, 0xE1_b, 0xBA_b,
                         0xA0_b, 0xF0_b, 0x9F_b, 0x92_b, 0xA9_b };
        auto range = ogonek::decode_ex<ogonek::utf8>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

TEST_CASE("utf16", "UTF-16 encoding form") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-16") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf16>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
        REQUIRE(encoded.size() == 5);
        CHECK(encoded[0] == u'\x0041');
        CHECK(encoded[1] == u'\x00C5');
        CHECK(encoded[2] == u'\x1EA0');
        CHECK(encoded[3] == u'\xD83D');
        CHECK(encoded[4] == u'\xDCA9');
    }
    SECTION("decode", "Decoding UTF-16") {
        std::initializer_list<char16_t> encoded = { 0x0041, 0x00C5, 0x1EA0, 0xD83D, 0xDCA9 };
        auto range = ogonek::decode_ex<ogonek::utf16>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}

TEST_CASE("utf32", "UTF-32 encoding form") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding UTF-32") {
        auto decoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::utf32>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
        REQUIRE(encoded.size() == 4);
        CHECK(encoded[0] == 0x0041);
        CHECK(encoded[1] == 0x00C5);
        CHECK(encoded[2] == 0x1EA0);
        CHECK(encoded[3] == 0x1F4A9);
    }
    SECTION("decode", "Decoding UTF-32") {
        std::initializer_list<char32_t> encoded = { 0x0041, 0x00C5, 0x1EA0, 0x1F4A9 };
        auto range = ogonek::decode_ex<ogonek::utf32>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
}


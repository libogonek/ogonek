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

#include <ogonek/encoding/encoding_scheme.h++>
#include <ogonek/encoding/utf16le.h++>
#include <ogonek/encoding/utf16be.h++>
#include <ogonek/encoding/utf32le.h++>
#include <ogonek/encoding/utf32be.h++>

#include <ogonek/error/assume_valid.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>

#include <taussig/interop.h++>

#include "utils.h++"
#include <catch.hpp>

using namespace test::literal;

TEST_CASE("utf16le", "UTF-16LE codec") {
    SECTION("encode", "Encoding UTF-16LE") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf16le>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<test::byte_string>(range);
        REQUIRE(encoded == "\x41\x00\xC5\x00\xA0\x1E\x3D\xD8\xA9\xDC"_b);
    }
    SECTION("decode", "Decoding UTF-16LE") {
        auto encoded = "\x41\x00\xC5\x00\xA0\x1E\x3D\xD8\xA9\xDC"_b;
        auto range = ogonek::decode<ogonek::utf16le>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}

TEST_CASE("utf16be", "UTF-16BE codec") {
    SECTION("encode", "Encoding UTF-16BE") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf16be>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<test::byte_string>(range);
        REQUIRE(encoded == "\x00\x41\x00\xC5\x1E\xA0\xD8\x3D\xDC\xA9"_b);
    }
    SECTION("decode", "Decoding UTF-16BE") {
        auto encoded = "\x00\x41\x00\xC5\x1E\xA0\xD8\x3D\xDC\xA9"_b;
        auto range = ogonek::decode<ogonek::utf16be>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}

TEST_CASE("utf32le", "UTF-32LE codec") {
    SECTION("encode", "Encoding UTF-32LE") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf32le>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<test::byte_string>(range);
        REQUIRE(encoded == "\x41\x00\x00\x00\xC5\x00\x00\x00\xA0\x1E\x00\x00\xA9\xF4\x01\x00"_b);
    }
    SECTION("decode", "Decoding UTF-32LE") {
        auto encoded = "\x41\x00\x00\x00\xC5\x00\x00\x00\xA0\x1E\x00\x00\xA9\xF4\x01\x00"_b;
        auto range = ogonek::decode<ogonek::utf32le>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}

TEST_CASE("utf32be", "UTF-32BE codec") {
    SECTION("encode", "Encoding UTF-32BE") {
        auto decoded = U"\u0041\u00C5\u1EA0\U0001F4A9"_u;
        auto range = ogonek::encode<ogonek::utf32be>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<test::byte_string>(range);
        REQUIRE(encoded == "\x00\x00\x00\x41\x00\x00\x00\xC5\x00\x00\x1E\xA0\x00\x01\xF4\xA9"_b);
    }
    SECTION("decode", "Decoding UTF-32BE") {
        auto encoded = "\x00\x00\x00\x41\x00\x00\x00\xC5\x00\x00\x1E\xA0\x00\x01\xF4\xA9"_b;
        auto range = ogonek::decode<ogonek::utf32be>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<test::ustring>(range);
        REQUIRE(decoded == U"\u0041\u00C5\u1EA0\U0001F4A9"_u);
    }
}


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

// Tests for <ogonek/encoding/windows1252.h++>

#include <ogonek/encoding.h++>
#include <ogonek/types.h++>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <ogonek/encoding/windows1252.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>

#include <vector>

#include <catch.h++>

TEST_CASE("windows1252", "Windows-1252 encoding form") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding Windows-1252") {
        auto decoded = { U'\x0041', U'\x20AC' };
        auto range = ogonek::encode<ogonek::windows1252>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector<ogonek::byte>>(range);
        REQUIRE(encoded.size() == 2);
        CHECK(int(encoded[0]) == int(0x41_b));
        CHECK(int(encoded[1]) == int(0x80_b));
    }
    SECTION("decode", "Decoding Windows-1252") {
        auto encoded = { 0x41_b, 0x80_b };
        auto range = ogonek::decode<ogonek::windows1252>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 2);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x20AC');
    }
    SECTION("validation", "Validating Windows-1252") {
        auto encoded = { 0x41_b, 0x80_b, 0x81_b };
        auto range = ogonek::decode<ogonek::windows1252>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 3);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x20AC');
        CHECK(decoded[2] == U'\xFFFD');
    }
    SECTION("replacement", "Windows-1252's custom replacement character (?)") {
        auto decoded = { U'\x0041', U'\x20AC', U'\x1F4A9' };
        auto range = ogonek::encode<ogonek::windows1252>(decoded, ogonek::replace_errors);
        auto encoded = seq::materialize<std::vector>(range);
        REQUIRE(encoded.size() == 3);
        CHECK(encoded[0] == 0x41_b);
        CHECK(ogonek::byte(encoded[1]) == 0x80_b);
        CHECK(encoded[2] == '?');
    }
}

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

#include <ogonek/encoding.h++>
#include <ogonek/types.h++>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <catch.h++>

#include <ogonek/encoding/ascii.h++>
#include <ogonek/encoding/encode.h++>
#include <ogonek/encoding/decode.h++>
#include <ogonek/sequence/interop.h++>
#include <ogonek/sequence/as_sequence.h++>

#include <vector>

TEST_CASE("ascii", "ASCII encoding form") {
    using namespace ogonek::literal;
    namespace seq = ogonek::seq;

    SECTION("encode", "Encoding ASCII") {
        auto decoded = { U'\x0041', U'\x0032' };
        static_assert(ogonek::is_sequence<decltype(ogonek::as_sequence(decoded))>(), "");
        auto range = ogonek::encode<ogonek::ascii>(decoded, ogonek::assume_valid);
        auto encoded = seq::materialize<std::vector>(range);
        REQUIRE(encoded.size() == 2);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0x32_b);
    }
    SECTION("decode", "Decoding ASCII") {
        auto encoded = { 0x41_b, 0x32_b };
        auto range = ogonek::decode<ogonek::ascii>(encoded, ogonek::assume_valid);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 2);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x0032');
    }
    SECTION("validation", "Validating ASCII") {
        auto encoded = { 0x41_b, 0x32_b, 0x80_b };
        auto range = ogonek::decode<ogonek::ascii>(encoded, ogonek::replace_errors);
        auto decoded = seq::materialize<std::vector>(range);
        REQUIRE(decoded.size() == 3);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x0032');
        CHECK(decoded[2] == U'\xFFFD');
    }
    SECTION("replacement", "ASCII's custom replacement character (?)") {
        auto decoded = { U'\x41', U'\x32', U'\x80' };
        auto range = ogonek::encode<ogonek::ascii>(decoded, ogonek::replace_errors);
        auto encoded = seq::materialize<std::vector>(range);
        REQUIRE(encoded.size() == 3);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0x32_b);
        CHECK(encoded[2] == '?');
    }
}

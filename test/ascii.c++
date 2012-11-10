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

// Tests for <ogonek/encoding/ascii.h++>

#include <ogonek/encoding/ascii.h++>
#include <ogonek/types.h++>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <catch.h++>

TEST_CASE("ascii", "ASCII encoding form") {
    using namespace ogonek::literal;

    SECTION("encode", "Encoding ASCII") {
        auto decoded = { 0x0041_u, 0x0032_u };
        auto range = ogonek::ascii::encode(decoded, ogonek::skip_validation);
        std::vector<ogonek::byte> encoded(boost::begin(range), boost::end(range));
        REQUIRE(encoded.size() == 2);
        CHECK(encoded[0] == 0x41_b);
        CHECK(encoded[1] == 0x32_b);
    }
    SECTION("decode", "Decoding ASCII") {
        auto encoded = { 0x41_b, 0x32_b };
        auto range = ogonek::ascii::decode(encoded, ogonek::skip_validation);
        std::vector<ogonek::codepoint> decoded(boost::begin(range), boost::end(range));
        REQUIRE(decoded.size() == 2);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x0032');
    }
    SECTION("validation", "Validating ASCII") {
    }
}



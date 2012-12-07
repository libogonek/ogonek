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

// Tests for issue #13

#include <catch.h++>

#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/segmentation.h++>
#include <ogonek/validation.h++>

TEST_CASE("issue13", "Tests for issue #13") {
    using text8 = ogonek::basic_text<ogonek::utf8>;

    SECTION("original", "Original test, shortened") {
        std::string s = u8"\u043f\u0440\u0438\u0432\u0435\u0442";
        text8 t { s };

        std::vector<text8> result;
        for(auto character : ogonek::grapheme_clusters(t)) {
            result.emplace_back(character);
        }

        REQUIRE(result.size() == 6);
        CHECK(result[0].storage() == u8"\u043f");
        CHECK(result[1].storage() == u8"\u0440");
        CHECK(result[2].storage() == u8"\u0438");
        CHECK(result[3].storage() == u8"\u0432");
        CHECK(result[4].storage() == u8"\u0435");
        CHECK(result[5].storage() == u8"\u0442");
    }
    SECTION("zeroed in", "found out the issue is with UTF-8 encoding") {
        ogonek::utf8::state s {};
        auto encoded = ogonek::utf8::encode_one(U'\x0440', s, ogonek::throw_validation_error);
        REQUIRE(encoded.size() == 2);
        CHECK(int(encoded[0]) == int(char(0xD1)));
        CHECK(int(encoded[1]) == int(char(0x80)));
    }
}


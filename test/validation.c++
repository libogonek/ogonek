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

// Tests for validation in <ogonek/encoding/utf?.h++>

#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/encoding/utf7.h++>
#include <ogonek/types.h++>

#include <catch.h++>

TEST_CASE("utf8-validation", "Validation of UTF-8") {
    using namespace ogonek::literal;

    SECTION("valid", "Accepting valid bytes") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xC3_b, 0x85_b, 0xE1_b, 0xBA_b,
                                                        0xA0_b, 0xF0_b, 0x9F_b, 0x92_b, 0xA9_b };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
    SECTION("invalid", "Rejecting invalid bytes") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xC0_b, 0xC3_b, 0x85_b, 0xC1_b, 0xF5_b };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 5);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\xFFFD');
        CHECK(decoded[2] == U'\x00C5');
        CHECK(decoded[3] == U'\xFFFD');
        CHECK(decoded[4] == U'\xFFFD');
    }
    SECTION("unexpected continuation", "Rejecting unexpected continuation bytes") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xC3_b, 0x85_b, 0x84_b, 0x42_b };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\x0042');
    }
    SECTION("not enough continuation", "Rejecting start bytes not followed by enough continuation bytes") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xF3_b, 0x85_b, 0xC3_b, 0x85_b, 0x42_b,  };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 5);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\xFFFD');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\x00C5');
        CHECK(decoded[4] == U'\x0042');
    }
    SECTION("overlong", "Rejecting overlong forms") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xC0_b, 0x80_b, 0xC3_b, 0x85_b, 0x42_b,  };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 5);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\xFFFD');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\x00C5');
        CHECK(decoded[4] == U'\x0042');
    }
    SECTION("invalid codepoint", "Rejecting sequences that decode to values above 0x10FFFF or surrogates") {
        std::initializer_list<ogonek::byte> encoded = { 0x41_b, 0xF4_b, 0x90_b, 0x80_b, 0x80_b, 0x42_b,
                                                        0xED_b, 0xA0_b, 0x80_b };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf8::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 9);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\xFFFD');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\xFFFD');
        CHECK(decoded[4] == U'\xFFFD');
        CHECK(decoded[5] == U'\x0042');
        CHECK(decoded[6] == U'\xFFFD');
        CHECK(decoded[7] == U'\xFFFD');
        CHECK(decoded[8] == U'\xFFFD');
    }
}

TEST_CASE("utf16-validation", "Validation of UTF-16") {
    using namespace ogonek::literal;

    SECTION("valid", "Accepting valid sequences") {
        std::initializer_list<char16_t> encoded = { 0x0041, 0x00C5, 0x1EA0, 0xD83D, 0xDCA9 };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
    SECTION("unpaired surrogates", "Rejecting unpaired surrogates") {
        std::initializer_list<char16_t> encoded = { u'\x0041', u'\xD83D', u'\x00C5', u'\xDCA9', u'\x1EA0', };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 5);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\xFFFD');
        CHECK(decoded[2] == U'\x00C5');
        CHECK(decoded[3] == U'\xFFFD');
        CHECK(decoded[4] == U'\x1EA0');
    }
    SECTION("inverted surrogates", "Rejecting inverted surrogates") {
        std::initializer_list<char16_t> encoded = { u'\x0041', u'\x00C5', u'\xDCA9', u'\xD83D', u'\x1EA0', };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf16::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 5);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\xFFFD');
        CHECK(decoded[4] == U'\x1EA0');
    }
}

TEST_CASE("utf32-validation", "Validation of UTF-32") {
    using namespace ogonek::literal;

    SECTION("valid", "Accepting valid sequences") {
        std::initializer_list<char32_t> encoded = { U'\x0041', U'\x00C5', U'\x1EA0', U'\x1F4A9', };
        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32::decode(encoded, std::back_inserter(decoded));
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\x1EA0');
        CHECK(decoded[3] == U'\x1F4A9');
    }
    SECTION("invalid", "Rejecting codepoints above U+10FFFF") {
        std::initializer_list<char32_t> encoded = { U'\x0041', U'\x00C5', U'\x21F4A9', };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 3);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\xFFFD');
    }
    SECTION("surrogates", "Rejecting surrogates") {
        std::initializer_list<char32_t> encoded = { U'\x0041', U'\x00C5', U'\xD932', U'\xDC43', };

        std::vector<ogonek::codepoint> decoded;
        ogonek::utf32::decode(encoded, std::back_inserter(decoded), ogonek::use_replacement_character);
        REQUIRE(decoded.size() == 4);
        CHECK(decoded[0] == U'\x0041');
        CHECK(decoded[1] == U'\x00C5');
        CHECK(decoded[2] == U'\xFFFD');
        CHECK(decoded[3] == U'\xFFFD');
    }
}


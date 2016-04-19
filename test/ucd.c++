// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for <ogonek/ucd.h++>

#include <ogonek/ucd.h++>

#include <catch.hpp>

TEST_CASE("query", "UCD property queries") {
    namespace ucd = ogonek::ucd;
    SECTION("name", "Querying name") {
        SECTION("explicit", "some characters have explicit names") {
            CHECK(ucd::get_name(U'\x0041').storage() == u8"LATIN CAPITAL LETTER A");
            CHECK(ucd::get_name(U'\x00C5').storage() == u8"LATIN CAPITAL LETTER A WITH RING ABOVE");
            CHECK(ucd::get_name(U'\x1EA0').storage() == u8"LATIN CAPITAL LETTER A WITH DOT BELOW");
            CHECK(ucd::get_name(U'\x1F4A9').storage() == u8"PILE OF POO");
        }
        SECTION("control", "control characters have empty names") {
            CHECK(ucd::get_name(U'\x000A').storage() == u8"");
            CHECK(ucd::get_name(U'\x0083').storage() == u8"");
        }
        SECTION("private use", "private use characters have empty names") {
            CHECK(ucd::get_name(U'\xE042').storage() == u8"");
            CHECK(ucd::get_name(U'\xF0042').storage() == u8"");
            CHECK(ucd::get_name(U'\x100042').storage() == u8"");
        }
        SECTION("ideograph", "ideographs have generated names") {
            CHECK(ucd::get_name(U'\x3442').storage() == u8"CJK UNIFIED IDEOGRAPH-3442");
            CHECK(ucd::get_name(U'\x4E42').storage() == u8"CJK UNIFIED IDEOGRAPH-4E42");
            CHECK(ucd::get_name(U'\x20042').storage() == u8"CJK UNIFIED IDEOGRAPH-20042");
            CHECK(ucd::get_name(U'\x2A742').storage() == u8"CJK UNIFIED IDEOGRAPH-2A742");
            CHECK(ucd::get_name(U'\x2B742').storage() == u8"CJK UNIFIED IDEOGRAPH-2B742");
            CHECK(ucd::get_name(U'\x2B842').storage() == u8"CJK UNIFIED IDEOGRAPH-2B842");
            CHECK(ucd::get_name(U'\x2F842').storage() == u8"CJK COMPATIBILITY IDEOGRAPH-2F842");
        }
        SECTION("hangul", "hangul syllables have generated names") {
            CHECK(ucd::get_name(U'\xAC00').storage() == u8"HANGUL SYLLABLE GA");
            CHECK(ucd::get_name(U'\xAC42').storage() == u8"HANGUL SYLLABLE GYALM");
            CHECK(ucd::get_name(U'\xD7A3').storage() == u8"HANGUL SYLLABLE HIH");
        }
    }
}


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

// Tests for <ogonek/ucd.h++>

#include <ogonek/ucd.h++>
#include <ogonek/types.h++>

#include <catch.h++>

namespace ogonek { namespace ucd {
    std::ostream& operator<<(std::ostream& os, block b) {
        return os << "block::" << (int)b;
    }
} }

namespace ogonek { namespace ucd {
    std::ostream& operator<<(std::ostream& os, category c) {
        return os << "category::" << (int)c;
    }
} }
TEST_CASE("query", "UCD property queries") {
    using namespace ogonek::literal;
    namespace ucd = ogonek::ucd;
    SECTION("age", "Querying age") {
        CHECK(ucd::get_age(0x0041_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x00C5_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x1EA0_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x1F4A9_u) == ucd::version::v6_0);
    }
    /*
    SECTION("name", "Querying name") {
        REQUIRE(ucd::get_name(0x0041_u) == U"LATIN CAPITAL LETTER A");
        REQUIRE(ucd::get_name(0x00C5_u) == U"LATIN CAPITAL LETTER A WITH RING ABOVE");
        REQUIRE(ucd::get_name(0x1EA0_u) == U"LATIN CAPITAL LETTER A WITH DOT BELOW");
        REQUIRE(ucd::get_name(0x1F4A9_u) == U"PILE OF POO");
    }
    */
    SECTION("block", "Querying block") {
        CHECK(ucd::get_block(0x0041_u) == ucd::block::ASCII);
        CHECK(ucd::get_block(0x00C5_u) == ucd::block::Latin_1_Sup);
        CHECK(ucd::get_block(0x1EA0_u) == ucd::block::Latin_Ext_Additional);
        CHECK(ucd::get_block(0x1F4A9_u) == ucd::block::Misc_Pictographs);
    }
    SECTION("category", "Querying general category") {
        CHECK(ucd::get_general_category(0x0041_u) == ucd::category::Lu);
        CHECK(ucd::get_general_category(0x00C5_u) == ucd::category::Lu);
        CHECK(ucd::get_general_category(0x1EA0_u) == ucd::category::Lu);
        CHECK(ucd::get_general_category(0x1F4A9_u) == ucd::category::So);
    }
    SECTION("combining class", "Querying combining class") {
        CHECK(ucd::get_combining_class(0x0041_u) == 0);
        CHECK(ucd::get_combining_class(0x0300_u) == 230);
        CHECK(ucd::get_combining_class(0x0334_u) == 1);
        CHECK(ucd::get_combining_class(0x0618_u) == 30);
    }
    SECTION("bidi_category", "Querying bidirectional category") {
        CHECK(ucd::get_bidi_category(0x0041_u) == ucd::bidi_category::L);
        CHECK(ucd::get_bidi_category(0x0600_u) == ucd::bidi_category::AN);
        CHECK(ucd::get_bidi_category(0x0610_u) == ucd::bidi_category::NSM);
        CHECK(ucd::get_bidi_category(0x1F4A9_u) == ucd::bidi_category::ON);
    }
}


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
#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>

#include <catch.h++>

#include <boost/range/algorithm/equal.hpp>

#include <cmath>
#include <initializer_list>

TEST_CASE("query", "UCD property queries") {
    using namespace ogonek::literal;
    namespace ucd = ogonek::ucd;
    SECTION("age", "Querying age") {
        CHECK(ucd::get_age(0x0041_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x00C5_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x1EA0_u) == ucd::version::v1_1);
        CHECK(ucd::get_age(0x1F4A9_u) == ucd::version::v6_0);
    }
    SECTION("name", "Querying name") {
        REQUIRE(ucd::get_name(0x0041_u).storage() == u8"LATIN CAPITAL LETTER A");
        REQUIRE(ucd::get_name(0x00C5_u).storage() == u8"LATIN CAPITAL LETTER A WITH RING ABOVE");
        REQUIRE(ucd::get_name(0x1EA0_u).storage() == u8"LATIN CAPITAL LETTER A WITH DOT BELOW");
        REQUIRE(ucd::get_name(0x1F4A9_u).storage() == u8"PILE OF POO");
        REQUIRE(ucd::get_name(0x3442_u).storage() == u8"CJK UNIFIED IDEOGRAPH-3442");
        REQUIRE(ucd::get_name(0x2F823_u).storage() == u8"CJK COMPATIBILITY IDEOGRAPH-2F823");
    }
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
    SECTION("bidi_mirrored", "Querying bidirectional mirrored") {
        CHECK(ucd::is_bidi_mirrored(0x0041_u) == false);
        CHECK(ucd::is_bidi_mirrored(0x0F3A_u) == true);
        CHECK(ucd::is_bidi_mirrored(0x222B_u) == true);
        CHECK(ucd::is_bidi_mirrored(0x1F4A9_u) == false);
    }
    SECTION("bidi_mirrored_glyph", "Querying bidirectional mirrored glyph") {
        CHECK(ucd::get_bidi_mirrored_glyph(0x0041_u) == 0x0041_u);
        CHECK(ucd::get_bidi_mirrored_glyph(0x222B_u) == 0x222B_u);
        CHECK(ucd::get_bidi_mirrored_glyph(0x223C_u) == 0x223D_u);
        CHECK(ucd::get_bidi_mirrored_glyph(0xFF63_u) == 0xFF62_u);
    }
    SECTION("bidi_control", "Querying bidirectional control") {
        CHECK(ucd::is_bidi_control(U'\x0041') == false);
        CHECK(ucd::is_bidi_control(U'\x00C5') == false);
        CHECK(ucd::is_bidi_control(U'\x200E') == true);
        CHECK(ucd::is_bidi_control(U'\x202E') == true);
    }
    SECTION("decomposition_type", "Querying decomposition type") {
        CHECK(ucd::get_decomposition_type(U'\x0041') == ucd::decomposition_type::none);
        CHECK(ucd::get_decomposition_type(U'\x00C5') == ucd::decomposition_type::can);
        CHECK(ucd::get_decomposition_type(U'\x1EA0') == ucd::decomposition_type::can);
        CHECK(ucd::get_decomposition_type(U'\x3000') == ucd::decomposition_type::wide);
    }
    using codepoint_list = std::initializer_list<ogonek::codepoint>;
    SECTION("decomposition_mapping", "Querying decomposition mapping") {
        CHECK(boost::equal(ucd::get_decomposition_mapping(U'\x0041'), codepoint_list{ U'\x0041' }));
        CHECK(boost::equal(ucd::get_decomposition_mapping(U'\x00C5'), codepoint_list{ U'\x0041', U'\x030A' }));
        CHECK(boost::equal(ucd::get_decomposition_mapping(U'\x1EA0'), codepoint_list{ U'\x0041', U'\x0323' }));
        CHECK(boost::equal(ucd::get_decomposition_mapping(U'\x3000'), codepoint_list{ U'\x0020' }));
    }
    SECTION("full_composition_exclusion", "Querying composition exclusion") {
        CHECK(ucd::is_excluded_from_composition(U'\x0041') == false);
        CHECK(ucd::is_excluded_from_composition(U'\x0344') == true);
        CHECK(ucd::is_excluded_from_composition(U'\x0958') == true);
        CHECK(ucd::is_excluded_from_composition(U'\x2ADC') == true);
        CHECK(ucd::is_excluded_from_composition(U'\x2126') == true);
    }
    SECTION("nfc_quick_check", "Querying NFC quick check") {
        CHECK((ucd::is_nfc_quick_check(U'\x0041') == true)); // TODO: extra parens to compile. Report Catch bug
        CHECK(boost::indeterminate(ucd::is_nfc_quick_check(U'\x0300')));
        CHECK((ucd::is_nfc_quick_check(U'\x0340') == false));
        CHECK((ucd::is_nfc_quick_check(U'\x1F4A9') == true));
    }
    SECTION("nfd_quick_check", "Querying NFD quick check") {
        CHECK(ucd::is_nfd_quick_check(U'\x0041') == true);
        CHECK(ucd::is_nfd_quick_check(U'\x00C5') == false);
        CHECK(ucd::is_nfd_quick_check(U'\x2F801') == false);
        CHECK(ucd::is_nfd_quick_check(U'\x1F4A9') == true);
    }
    SECTION("nfkc_quick_check", "Querying NFKC quick check") {
        CHECK((ucd::is_nfkc_quick_check(U'\x0041') == true)); // TODO: extra parens to compile. Report Catch bug
        CHECK(boost::indeterminate(ucd::is_nfkc_quick_check(U'\x0300')));
        CHECK((ucd::is_nfkc_quick_check(U'\x0340') == false));
        CHECK((ucd::is_nfkc_quick_check(U'\x1F4A9') == true));
    }
    SECTION("nfkd_quick_check", "Querying NFKD quick check") {
        CHECK(ucd::is_nfkd_quick_check(U'\x0041') == true);
        CHECK(ucd::is_nfkd_quick_check(U'\x00C5') == false);
        CHECK(ucd::is_nfkd_quick_check(U'\x013F') == false);
        CHECK(ucd::is_nfkd_quick_check(U'\x1F4A9') == true);
    }
    SECTION("numeric_type", "Querying numeric type") {
        CHECK(ucd::get_numeric_type(U'\x0041') == ucd::numeric_type::None);
        CHECK(ucd::get_numeric_type(U'\xA621') == ucd::numeric_type::De);
        CHECK(ucd::get_numeric_type(U'\x00B2') == ucd::numeric_type::Di);
        CHECK(ucd::get_numeric_type(U'\xA831') == ucd::numeric_type::Nu);
    }
    SECTION("numeric_value", "Querying numeric value") {
        CHECK(std::isnan(ucd::get_numeric_value(U'\x0041')));
        CHECK(ucd::get_numeric_value(U'\xA621') == 1);
        CHECK(ucd::get_numeric_value(U'\x00B2') == 2);
        CHECK(ucd::get_numeric_value(U'\xA831') == 0.5);
    }
    SECTION("joining_class", "Querying joining class") {
        CHECK(ucd::get_joining_class(U'\x0041') == ucd::joining_class::U);
        CHECK(ucd::get_joining_class(U'\x0648') == ucd::joining_class::R);
        CHECK(ucd::get_joining_class(U'\x064B') == ucd::joining_class::T);
        CHECK(ucd::get_joining_class(U'\x066E') == ucd::joining_class::D);
    }
    SECTION("joining_group", "Querying joining group") {
        CHECK(ucd::get_joining_group(U'\x0041') == ucd::joining_group::No_Joining_Group);
        CHECK(ucd::get_joining_group(U'\x0648') == ucd::joining_group::Waw);
        CHECK(ucd::get_joining_group(U'\x064B') == ucd::joining_group::No_Joining_Group);
        CHECK(ucd::get_joining_group(U'\x066E') == ucd::joining_group::Beh);
    }
    SECTION("join_control", "Querying join control") {
        CHECK(ucd::is_join_control(U'\x0041') == false);
        CHECK(ucd::is_join_control(U'\x200C') == true);
        CHECK(ucd::is_join_control(U'\x200D') == true);
        CHECK(ucd::is_join_control(U'\x1F4A9') == false);
    }
    SECTION("linebreak", "Querying linebreak") {
        CHECK(ucd::get_linebreak_type(U'\x000A') == ucd::linebreak::LF);
        CHECK(ucd::get_linebreak_type(U'\x000D') == ucd::linebreak::CR);
        CHECK(ucd::get_linebreak_type(U'\x0041') == ucd::linebreak::AL);
        CHECK(ucd::get_linebreak_type(U'\x2028') == ucd::linebreak::BK);
    }
    SECTION("east_asian_width", "Querying East Asian width") {
        CHECK(ucd::get_linebreak_type(U'\x000A') == ucd::linebreak::LF);
        CHECK(ucd::get_linebreak_type(U'\x000D') == ucd::linebreak::CR);
        CHECK(ucd::get_linebreak_type(U'\x0041') == ucd::linebreak::AL);
        CHECK(ucd::get_linebreak_type(U'\x2028') == ucd::linebreak::BK);
    }
    SECTION("is_uppercase", "Querying uppercase") {
        CHECK(ucd::is_uppercase(U'\x0041') == true);
        CHECK(ucd::is_uppercase(U'\x0061') == false);
        CHECK(ucd::is_uppercase(U'\x1EA0') == true);
        CHECK(ucd::is_uppercase(U'\x1F4A9') == false);
    }
    SECTION("is_lowercase", "Querying lowercase") {
        CHECK(ucd::is_lowercase(U'\x0041') == false);
        CHECK(ucd::is_lowercase(U'\x0061') == true);
        CHECK(ucd::is_lowercase(U'\x1EA0') == false);
        CHECK(ucd::is_lowercase(U'\x1F4A9') == false);
    }
    SECTION("simple_uppercase", "Querying simple uppercase") {
        CHECK(ucd::get_simple_uppercase(U'\x0041') == U'\x0041');
        CHECK(ucd::get_simple_uppercase(U'\x00C5') == U'\x00C5');
        CHECK(ucd::get_simple_uppercase(U'\x1EA0') == U'\x1EA0');
        CHECK(ucd::get_simple_uppercase(U'\x0061') == U'\x0041');
        CHECK(ucd::get_simple_uppercase(U'\x00E5') == U'\x00C5');
        CHECK(ucd::get_simple_uppercase(U'\x1EA1') == U'\x1EA0');
        CHECK(ucd::get_simple_uppercase(U'\x1F4A9') == U'\x1F4A9');
    }
    SECTION("simple_lowercase", "Querying simple lowercase") {
        CHECK(ucd::get_simple_lowercase(U'\x0061') == U'\x0061');
        CHECK(ucd::get_simple_lowercase(U'\x00E5') == U'\x00E5');
        CHECK(ucd::get_simple_lowercase(U'\x1EA1') == U'\x1EA1');
        CHECK(ucd::get_simple_lowercase(U'\x0041') == U'\x0061');
        CHECK(ucd::get_simple_lowercase(U'\x00C5') == U'\x00E5');
        CHECK(ucd::get_simple_lowercase(U'\x1EA0') == U'\x1EA1');
        CHECK(ucd::get_simple_lowercase(U'\x1F4A9') == U'\x1F4A9');
    }
    SECTION("simple_titlecase", "Querying simple titlecase") {
        CHECK(ucd::get_simple_titlecase(U'\x0041') == U'\x0041');
        CHECK(ucd::get_simple_titlecase(U'\x0061') == U'\x0041');
        CHECK(ucd::get_simple_titlecase(U'\x00C5') == U'\x00C5');
        CHECK(ucd::get_simple_titlecase(U'\x00E5') == U'\x00C5');
        CHECK(ucd::get_simple_titlecase(U'\x1EA0') == U'\x1EA0');
        CHECK(ucd::get_simple_titlecase(U'\x1EA1') == U'\x1EA0');
        CHECK(ucd::get_simple_titlecase(U'\x1F4A9') == U'\x1F4A9');
    }
    SECTION("uppercase", "Querying uppercase") {
        CHECK(boost::equal(ucd::get_uppercase(U'\x0041'), codepoint_list{ U'\x0041' }));
        CHECK(boost::equal(ucd::get_uppercase(U'\x0061'), codepoint_list{ U'\x0041' }));
        CHECK(boost::equal(ucd::get_uppercase(U'\x00DF'), codepoint_list{ U'\x0053', U'\x0053' }));
        CHECK(boost::equal(ucd::get_uppercase(U'\x1E96'), codepoint_list{ U'\x0048', U'\x0331' }));
        CHECK(boost::equal(ucd::get_uppercase(U'\x1F4A9'), codepoint_list{ U'\x1F4A9' }));
    }
    SECTION("lowercase", "Querying lowercase") {
        CHECK(boost::equal(ucd::get_lowercase(U'\x0041'), codepoint_list{ U'\x0061' }));
        CHECK(boost::equal(ucd::get_lowercase(U'\x0061'), codepoint_list{ U'\x0061' }));
        CHECK(boost::equal(ucd::get_lowercase(U'\x0130'), codepoint_list{ U'\x0069', U'\x0307' }));
        CHECK(boost::equal(ucd::get_lowercase(U'\x1E96'), codepoint_list{ U'\x1E96' }));
        CHECK(boost::equal(ucd::get_lowercase(U'\x1F4A9'), codepoint_list{ U'\x1F4A9' }));
    }
    SECTION("titlecase", "Querying titlecase") {
        CHECK(boost::equal(ucd::get_titlecase(U'\x0041'), codepoint_list{ U'\x0041' }));
        CHECK(boost::equal(ucd::get_titlecase(U'\x0061'), codepoint_list{ U'\x0041' }));
        CHECK(boost::equal(ucd::get_titlecase(U'\x00DF'), codepoint_list{ U'\x0053', U'\x0073' }));
        CHECK(boost::equal(ucd::get_titlecase(U'\x1E96'), codepoint_list{ U'\x0048', U'\x0331' }));
        CHECK(boost::equal(ucd::get_titlecase(U'\x1F4A9'), codepoint_list{ U'\x1F4A9' }));
    }
    SECTION("simple_case_folding", "Querying simple case folding") {
        CHECK(ucd::get_simple_case_folding(U'\x0041') == U'\x0061');
        CHECK(ucd::get_simple_case_folding(U'\x0061') == U'\x0061');
        CHECK(ucd::get_simple_case_folding(U'\x00DF') == U'\x00DF');
        CHECK(ucd::get_simple_case_folding(U'\x1EA0') == U'\x1EA1');
        CHECK(ucd::get_simple_case_folding(U'\x1EA1') == U'\x1EA1');
        CHECK(ucd::get_simple_case_folding(U'\x1F4A9') == U'\x1F4A9');
    }
    SECTION("case_folding", "Querying case folding") {
        CHECK(boost::equal(ucd::get_case_folding(U'\x0041'), codepoint_list{ U'\x0061' }));
        CHECK(boost::equal(ucd::get_case_folding(U'\x0061'), codepoint_list{ U'\x0061' }));
        CHECK(boost::equal(ucd::get_case_folding(U'\x00DF'), codepoint_list{ U'\x0073', U'\x0073' }));
        CHECK(boost::equal(ucd::get_case_folding(U'\x1E96'), codepoint_list{ U'\x0068', U'\x0331' }));
        CHECK(boost::equal(ucd::get_case_folding(U'\x1F4A9'), codepoint_list{ U'\x1F4A9' }));
    }
    SECTION("is_case_ignorable", "Querying case ignorable") {
        CHECK(ucd::is_case_ignorable(U'\x0041') == false);
        CHECK(ucd::is_case_ignorable(U'\x0061') == false);
        CHECK(ucd::is_case_ignorable(U'\x0027') == true);
        CHECK(ucd::is_case_ignorable(U'\x002E') == true);
        CHECK(ucd::is_case_ignorable(U'\x1F4A9') == false);
    }
    SECTION("is_cased", "Querying cased") {
        CHECK(ucd::is_cased(U'\x0027') == false);
        CHECK(ucd::is_cased(U'\x002E') == false);
        CHECK(ucd::is_cased(U'\x0041') == true);
        CHECK(ucd::is_cased(U'\x0061') == true);
        CHECK(ucd::is_cased(U'\x00DF') == true);
        CHECK(ucd::is_cased(U'\x1F4A9') == false);
    }
}


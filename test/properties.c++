// Ogonek
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for <ogonek/properties.h++>

#include <ogonek/character/properties.h++>

#include "utils.h++"
#include <catch.h++>

TEST_CASE("properties", "user-facing property queries") {
    SECTION("numeric", "numeric properties") {
        REQUIRE_FALSE(ogonek::is_numeric(U'A'));
        REQUIRE(ogonek::is_numeric(U'0')); // DIGIT ZERO
        REQUIRE(ogonek::is_numeric(0xB2)); // SUPERSCRIPT TWO
        REQUIRE(ogonek::is_numeric(0xBC)); // VULGAR FRACTION ONE QUARTER

        REQUIRE(ogonek::numeric_value(U'0') == 0); // DIGIT ZERO
        REQUIRE(ogonek::numeric_value(0xB2) == 2); // SUPERSCRIPT TWO
        REQUIRE(ogonek::numeric_value(0xBC) == 0.25); // VULGAR FRACTION ONE QUARTER
        
        REQUIRE_FALSE(ogonek::is_digit(U'A'));
        REQUIRE(ogonek::is_digit(U'0')); // DIGIT ZERO
        REQUIRE(ogonek::is_digit(0xB2)); // SUPERSCRIPT TWO
        REQUIRE_FALSE(ogonek::is_digit(0xBC)); // VULGAR FRACTION ONE QUARTER

        REQUIRE(ogonek::digit_value(U'0') == 0); // DIGIT ZERO
        REQUIRE(ogonek::digit_value(0xB2) == 2); // SUPERSCRIPT TWO
        
        REQUIRE_FALSE(ogonek::is_decimal(U'A'));
        REQUIRE(ogonek::is_decimal(U'0')); // DIGIT ZERO
        REQUIRE_FALSE(ogonek::is_decimal(0xB2)); // SUPERSCRIPT TWO
        REQUIRE_FALSE(ogonek::is_decimal(0xBC)); // VULGAR FRACTION ONE QUARTER

        REQUIRE(ogonek::decimal_value(U'0') == 0); // DIGIT ZERO
    }
    
    SECTION("casing", "casing properties") {
        REQUIRE(ogonek::is_uppercase(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_uppercase(U'a')); // LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_uppercase(U'0')); // DIGIT ZERO
        REQUIRE_FALSE(ogonek::is_uppercase(0x00DF)); // LATIN SMALL LETTER SHARP S
        REQUIRE(ogonek::is_uppercase(0x1E9E)); // LATIN CAPITAL LETTER SHARP S
        REQUIRE(ogonek::is_uppercase(0x03A3)); // GREEK CAPITAL LETTER SIGMA
        REQUIRE_FALSE(ogonek::is_uppercase(0x03C3)); // GREEK SMALL LETTER SIGMA
        REQUIRE_FALSE(ogonek::is_uppercase(0x03C2)); // GREEK SMALL LETTER FINAL SIGMA
        REQUIRE(ogonek::is_uppercase(0x01F1)); // LATIN CAPITAL LETTER DZ
        REQUIRE_FALSE(ogonek::is_uppercase(0x01F2)); // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
        REQUIRE_FALSE(ogonek::is_uppercase(0x01F3)); // LATIN SMALL LETTER DZ
        
        REQUIRE(test::utext{ogonek::uppercase(U'A')} == test::utext{U"A"});
        REQUIRE(test::utext{ogonek::uppercase(U'a')} == test::utext{U"A"});
        REQUIRE(test::utext{ogonek::uppercase(U'0')} == test::utext{U"0"});
        REQUIRE(test::utext{ogonek::uppercase(0x00DF)} == test::utext{U"SS"});
        REQUIRE(test::utext{ogonek::uppercase(0x1E9E)} == test::utext{U"\x1E9E"});
        REQUIRE(test::utext{ogonek::uppercase(0x03A3)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::uppercase(0x03C3)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::uppercase(0x03C2)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::uppercase(0x01F1)} == test::utext{U"\x01F1"});
        REQUIRE(test::utext{ogonek::uppercase(0x01F2)} == test::utext{U"\x01F1"});
        REQUIRE(test::utext{ogonek::uppercase(0x01F3)} == test::utext{U"\x01F1"});
        
        REQUIRE_FALSE(ogonek::is_lowercase(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_lowercase(U'a')); // LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_lowercase(U'0')); // DIGIT ZERO
        REQUIRE(ogonek::is_lowercase(0x00DF)); // LATIN SMALL LETTER SHARP S
        REQUIRE_FALSE(ogonek::is_lowercase(0x1E9E)); // LATIN CAPITAL LETTER SHARP S
        REQUIRE_FALSE(ogonek::is_lowercase(0x03A3)); // GREEK CAPITAL LETTER SIGMA
        REQUIRE(ogonek::is_lowercase(0x03C3)); // GREEK SMALL LETTER SIGMA
        REQUIRE(ogonek::is_lowercase(0x03C2)); // GREEK SMALL LETTER FINAL SIGMA
        REQUIRE_FALSE(ogonek::is_lowercase(0x01F1)); // LATIN CAPITAL LETTER DZ
        REQUIRE_FALSE(ogonek::is_lowercase(0x01F2)); // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
        REQUIRE(ogonek::is_lowercase(0x01F3)); // LATIN SMALL LETTER DZ
        
        REQUIRE(test::utext{ogonek::lowercase(U'A')} == test::utext{U"a"});
        REQUIRE(test::utext{ogonek::lowercase(U'a')} == test::utext{U"a"});
        REQUIRE(test::utext{ogonek::lowercase(U'0')} == test::utext{U"0"});
        REQUIRE(test::utext{ogonek::lowercase(0x00DF)} == test::utext{U"\x00DF"});
        REQUIRE(test::utext{ogonek::lowercase(0x1E9E)} == test::utext{U"\x00DF"});
        REQUIRE(test::utext{ogonek::lowercase(0x03A3)} == test::utext{U"\x03C3"});
        REQUIRE(test::utext{ogonek::lowercase(0x03C3)} == test::utext{U"\x03C3"});
        REQUIRE(test::utext{ogonek::lowercase(0x03C2)} == test::utext{U"\x03C2"});
        REQUIRE(test::utext{ogonek::lowercase(0x01F1)} == test::utext{U"\x01F3"});
        REQUIRE(test::utext{ogonek::lowercase(0x01F2)} == test::utext{U"\x01F3"});
        REQUIRE(test::utext{ogonek::lowercase(0x01F3)} == test::utext{U"\x01F3"});
        
        REQUIRE(test::utext{ogonek::titlecase(U'A')} == test::utext{U"A"});
        REQUIRE(test::utext{ogonek::titlecase(U'a')} == test::utext{U"A"});
        REQUIRE(test::utext{ogonek::titlecase(U'0')} == test::utext{U"0"});
        REQUIRE(test::utext{ogonek::titlecase(0x00DF)} == test::utext{U"Ss"});
        REQUIRE(test::utext{ogonek::titlecase(0x1E9E)} == test::utext{U"\x1E9E"});
        REQUIRE(test::utext{ogonek::titlecase(0x03A3)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::titlecase(0x03C3)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::titlecase(0x03C2)} == test::utext{U"\x03A3"});
        REQUIRE(test::utext{ogonek::titlecase(0x01F1)} == test::utext{U"\x01F2"});
        REQUIRE(test::utext{ogonek::titlecase(0x01F2)} == test::utext{U"\x01F2"});
        REQUIRE(test::utext{ogonek::titlecase(0x01F3)} == test::utext{U"\x01F2"});
    }
    SECTION("classification", "character classification and categorization") {
        REQUIRE(ogonek::is_alphabetic(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_alphabetic(U'0')); // DIGIT ZERO
        REQUIRE_FALSE(ogonek::is_alphabetic(0x1F34C)); // BANANA
        
        REQUIRE(ogonek::is_white_space(U' ')); // SPACE
        REQUIRE_FALSE(ogonek::is_white_space(U'A')); // LATIN CAPITAL LETTER A
        
        REQUIRE(ogonek::is_control(U'\n')); // LINE FEED
        REQUIRE_FALSE(ogonek::is_control(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_control(0x0082)); // BREAK PERMITTED HERE
        
        REQUIRE(ogonek::is_hex_digit(U'0')); // DIGIT ZERO
        REQUIRE(ogonek::is_hex_digit(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_hex_digit(U'a')); // LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_hex_digit(U'G')); // LATIN CAPITAL LETTER G
        REQUIRE_FALSE(ogonek::is_hex_digit(U'g')); // LATIN SMALL LETTER G
        REQUIRE(ogonek::is_hex_digit(0xFF10)); // FULLWIDTH DIGIT ZERO
        REQUIRE(ogonek::is_hex_digit(0xFF21)); // FULLWIDTH LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_hex_digit(0xFF41)); // FULLWIDTH LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_hex_digit(0xFF27)); // FULLWIDTH LATIN CAPITAL LETTER G
        REQUIRE_FALSE(ogonek::is_hex_digit(0xFF47)); // FULLWIDTH LATIN SMALL LETTER G
        
        REQUIRE(ogonek::is_ascii_hex_digit(U'0')); // DIGIT ZERO
        REQUIRE(ogonek::is_ascii_hex_digit(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_ascii_hex_digit(U'a')); // LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(U'G')); // LATIN CAPITAL LETTER G
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(U'g')); // LATIN SMALL LETTER G
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(0xFF10)); // FULLWIDTH DIGIT ZERO
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(0xFF21)); // FULLWIDTH LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(0xFF41)); // FULLWIDTH LATIN SMALL LETTER A
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(0xFF27)); // FULLWIDTH LATIN CAPITAL LETTER G
        REQUIRE_FALSE(ogonek::is_ascii_hex_digit(0xFF47)); // FULLWIDTH LATIN SMALL LETTER G
        
        REQUIRE_FALSE(ogonek::is_quotation_mark(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_quotation_mark(U'\'')); // APOSTROPHE
        REQUIRE(ogonek::is_quotation_mark(U'"')); // QUOTATION MARK
        REQUIRE(ogonek::is_quotation_mark(0x2018)); // LEFT SINGLE QUOTATION MARK
        REQUIRE(ogonek::is_quotation_mark(0x2019)); // RIGHT SINGLE QUOTATION MARK
        REQUIRE(ogonek::is_quotation_mark(0x201C)); // LEFT DOUBLE QUOTATION MARK
        REQUIRE(ogonek::is_quotation_mark(0x201D)); // RIGHT DOUBLE QUOTATION MARK
        REQUIRE_FALSE(ogonek::is_quotation_mark(0x1F34C)); // BANANA
        
        REQUIRE_FALSE(ogonek::is_dash(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_dash(U'-')); // HYPHEN-MINUS
        REQUIRE(ogonek::is_dash(0x2013)); // EM DASH
        REQUIRE(ogonek::is_dash(0x2014)); // EM DASH
        REQUIRE_FALSE(ogonek::is_dash(0x1F34C)); // BANANA
        
        REQUIRE_FALSE(ogonek::is_diacritic(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_diacritic(0x0328)); // COMBINING OGONEK
        REQUIRE(ogonek::is_diacritic(0x02DB)); // OGONEK
        REQUIRE_FALSE(ogonek::is_diacritic(0x093F)); // DEVANAGARI VOWEL SIGN I
        REQUIRE_FALSE(ogonek::is_diacritic(0x1F34C)); // BANANA
        
        REQUIRE_FALSE(ogonek::is_mathematical(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_mathematical(U'-')); // HYPHEN-MINUS
        REQUIRE(ogonek::is_mathematical(U'+')); // PLUS SIGN
        REQUIRE(ogonek::is_mathematical(0x2212)); // MINUS SIGN
        REQUIRE(ogonek::is_mathematical(0x2063)); // INVISIBLE SEPARATOR
        REQUIRE_FALSE(ogonek::is_mathematical(0x1F34C)); // BANANA

        REQUIRE_FALSE(ogonek::is_ideographic(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_ideographic(0xF9E5)); // CJK COMPATIBILITY IDEOGRAPH-F9E5
        REQUIRE(ogonek::is_ideographic(0x3401)); // CJK UNIFIED IDEOGRAPH-3401
        REQUIRE_FALSE(ogonek::is_ideographic(0x1F34C)); // BANANA

        REQUIRE_FALSE(ogonek::is_unified_ideograph(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_unified_ideograph(0xF9E5)); // CJK COMPATIBILITY IDEOGRAPH-F9E5
        REQUIRE(ogonek::is_unified_ideograph(0x3401)); // CJK UNIFIED IDEOGRAPH-3401
        REQUIRE_FALSE(ogonek::is_unified_ideograph(0x1F34C)); // BANANA

        REQUIRE_FALSE(ogonek::is_noncharacter(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_noncharacter(0xFDCF));
        for(char32_t u = 0xFDD0; u < 0xFDEF; ++u) {
            REQUIRE(ogonek::is_noncharacter(u)); // 32 extra noncharacters
        }
        REQUIRE_FALSE(ogonek::is_noncharacter(0xFDF0));
        for(char32_t u = 0xFFFE; u < 0x10FFFF; u += 0x10000) {
            REQUIRE(ogonek::is_noncharacter(u)); // FFFEs
        }
        for(char32_t u = 0xFFFF; u < 0x10FFFF; u += 0x10000) {
            REQUIRE(ogonek::is_noncharacter(u)); // FFFFs
        }
        REQUIRE_FALSE(ogonek::is_noncharacter(0x1F34C)); // BANANA

        REQUIRE_FALSE(ogonek::is_private_use(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE_FALSE(ogonek::is_private_use(0xDFFF));
        for(char32_t u = 0xE000; u < 0xF8FF; ++u) {
            REQUIRE(ogonek::is_private_use(u)); // Private Use Area
        }
        REQUIRE_FALSE(ogonek::is_private_use(0xF900));
        REQUIRE_FALSE(ogonek::is_private_use(0x1F34C)); // BANANA
        REQUIRE_FALSE(ogonek::is_private_use(0xEFFFF));
        REQUIRE(ogonek::is_private_use(0xF0000)); // Supplemental Private Use Area-A
        REQUIRE(ogonek::is_private_use(0xFFFFD)); // Supplemental Private Use Area-A
        REQUIRE_FALSE(ogonek::is_private_use(0xFFFFE));
        REQUIRE_FALSE(ogonek::is_private_use(0xEFFFF));
        REQUIRE(ogonek::is_private_use(0x100000)); // Supplemental Private Use Area-B
        REQUIRE(ogonek::is_private_use(0x10FFFD)); // Supplemental Private Use Area-B
        REQUIRE_FALSE(ogonek::is_private_use(0x10FFFE));
        
        REQUIRE(ogonek::is_defined(U'A')); // LATIN CAPITAL LETTER A
        REQUIRE(ogonek::is_defined(0x1F34C)); // BANANA
        REQUIRE(ogonek::is_defined(0xFFFF)); // noncharacter
        REQUIRE(ogonek::is_defined(0xF1234)); // private use character
        REQUIRE_FALSE(ogonek::is_defined(0x31234)); // character in Tertiary Ideographic Plane
    }
}


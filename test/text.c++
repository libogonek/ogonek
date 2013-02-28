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

// Tests for <ogonek/text.h++>

#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>
#include <ogonek/encoding/ascii.h++>

#include "utils.h++"
#include <catch.h++>

TEST_CASE("text", "text tests") {
    using text8 = test::text<ogonek::utf8>;
    using text16 = test::text<ogonek::utf16>;
    using text32 = test::text<ogonek::utf32>;
    using text_ascii = test::text<ogonek::ascii>;
    
    using string8 = test::string<ogonek::utf8>;
    using string16 = test::string<ogonek::utf16>;
    using string32 = test::string<ogonek::utf32>;
    using string_ascii = test::string<ogonek::ascii>;

    SECTION("general", "General test") {
        // construct UTF-8 text from a UTF-32 string literal
        text8 a { U"blah\U0001F4A9" };
        REQUIRE(a.storage() == string8(u8"blah\U0001F4A9"));

        // construct UTF-16 text from a UTF-32 string literal
        text16 b { U"blah\U0001F4A9" };
        REQUIRE(b.storage() == string16(u"blah\U0001F4A9"));

        // construct UTF-32 text from a UTF-32 string literal
        text32 c { U"blah\U0001F4A9" };
        REQUIRE(c.storage() == string32(U"blah\U0001F4A9"));

        // construct UTF-16 text from a range of codepoints
        text16 d { string32 { U"blah\U0001F4A9" } };
        REQUIRE(d.storage() == string16(u"blah\U0001F4A9"));

        // copy construct UTF-16 text
        text16 e { d };
        REQUIRE(e.storage() == string16(u"blah\U0001F4A9"));

        // construct UTF-16 text from UTF-8 text (i.e. UTF-8 -> UTF-16 conversion)
        text16 f { a };
        REQUIRE(f.storage() == string16(u"blah\U0001F4A9"));

        text16 g { text8 { U"blah\U0001F4A9" } };
        REQUIRE(g.storage() == string16(u"blah\U0001F4A9"));

        // construct UTF-16 text from UTF-32 text (i.e. UTF-32 -> UTF-16 conversion)
        text16 h { c };
        REQUIRE(h.storage() == string16(u"blah\U0001F4A9"));

        // construct UTF-16 text from UTF-16 string
        text16 i { string16 { u"blah\U0001F4A9" } };
        REQUIRE(d.storage() == string16(u"blah\U0001F4A9"));

        // (fail to) construct UTF-16 text from invalid data
        REQUIRE_THROWS_AS(text16 { U"blah\x200000" }, ogonek::validation_error);

        // construct ASCII text from a range of codepoints
        text_ascii j { string32 { U"blah\U00000032" } };
        REQUIRE(j.storage() == string_ascii("\x62\x6C\x61\x68\x32")); // don't test this on EBCDIC

        // (fail to) construct ASCII text from data not ASCII compatible
        REQUIRE_THROWS_AS(text_ascii { U"blah\x80" }, ogonek::validation_error);
        
        REQUIRE(text8{}.empty());
        
        // Canonical equivalence through ==
        text8 k { string8 { u8"bla\u0308h" } };
        text16 l { string16 { u"bl\u00e4h" } };
        text16 m { string16 { u"blah" } };
        REQUIRE(k == k);
        REQUIRE(k == l);
        REQUIRE(k != m);
        REQUIRE(l == k);
        REQUIRE(l == l);
        REQUIRE(l != m);
        REQUIRE(m != k);
        REQUIRE(m != l);
        REQUIRE(m == m);
        
        // Emptiness
    }
    SECTION("any", "any_text tests") {
        auto foo = text16 { U"foo" };
        ogonek::any_text any = foo; 
        REQUIRE(std::equal(any.begin(), any.end(), foo.begin()));
        REQUIRE(any.get<text16>().storage() == string16(u"foo"));

        auto bar = text8 { U"bar" };
        any = bar;
        REQUIRE(std::equal(any.begin(), any.end(), bar.begin()));
        REQUIRE(any.get<text8>().storage() == string8(u8"bar"));
        
        REQUIRE(ogonek::any_text{text8{}}.empty());
        
        // Canonical equivalence through ==
        ogonek::any_text a = text16 { U"bla\u0308h" };
        ogonek::any_text b = text8 { U"bl\u00e4h" };
        ogonek::any_text c = text32 { U"blah" };
        REQUIRE(a == a);
        REQUIRE(a == b);
        REQUIRE(a != c);
        REQUIRE(b == a);
        REQUIRE(b == b);
        REQUIRE(b != c);
        REQUIRE(c != a);
        REQUIRE(c != b);
        REQUIRE(c == c);
    }
}


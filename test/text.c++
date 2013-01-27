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

#include <catch.h++>

TEST_CASE("text", "text tests") {
    using text8 = ogonek::basic_text<ogonek::utf8>;
    using text16 = ogonek::basic_text<ogonek::utf16>;
    using text32 = ogonek::basic_text<ogonek::utf32>;
    using text_ascii = ogonek::basic_text<ogonek::ascii>;

    SECTION("general", "General test") {
        // construct UTF-8 text from a UTF-32 string literal
        text8 a { U"blah\U0001F4A9" };
        REQUIRE(a.storage() == u8"blah\U0001F4A9");

        // construct UTF-16 text from a UTF-32 string literal
        text16 b { U"blah\U0001F4A9" };
        REQUIRE(b.storage() == u"blah\U0001F4A9");

        // construct UTF-32 text from a UTF-32 string literal
        text32 c { U"blah\U0001F4A9" };
        REQUIRE(c.storage() == U"blah\U0001F4A9");

        // construct UTF-16 text from a range of codepoints
        text16 d { std::u32string { U"blah\U0001F4A9" } };
        REQUIRE(d.storage() == u"blah\U0001F4A9");

        // copy construct UTF-16 text
        text16 e { d };
        REQUIRE(e.storage() == u"blah\U0001F4A9");

        // construct UTF-16 text from UTF-8 text (i.e. UTF-8 -> UTF-16 conversion)
        text16 f { a };
        REQUIRE(f.storage() == u"blah\U0001F4A9");

        text16 g { text8 { U"blah\U0001F4A9" } };
        REQUIRE(g.storage() == u"blah\U0001F4A9");

        // construct UTF-16 text from UTF-32 text (i.e. UTF-32 -> UTF-16 conversion)
        text16 h { c };
        REQUIRE(h.storage() == u"blah\U0001F4A9");

        // construct UTF-16 text from UTF-16 string
        text16 i { std::u16string { u"blah\U0001F4A9" } };
        REQUIRE(d.storage() == u"blah\U0001F4A9");

        // (fail to) construct UTF-16 text from invalid data
        REQUIRE_THROWS_AS(text16 { U"blah\x200000" }, ogonek::validation_error);

        // construct ASCII text from a range of codepoints
        text_ascii j { std::u32string { U"blah\U00000032" } };
        REQUIRE(j.storage() == "blah2"); // don't test this on EBCDIC

        // (fail to) construct ASCII text from data not ASCII compatible
        REQUIRE_THROWS_AS(text_ascii { U"blahß" }, ogonek::validation_error);
    }
    SECTION("any", "any_text tests") {
        auto foo = text16 { U"foo" };
        ogonek::any_text any = foo; 
        REQUIRE(std::equal(any.begin(), any.end(), foo.begin()));
        REQUIRE(any.get<text16>().storage() == u"foo");

        auto bar = text8 { U"bar" };
        any = bar;
        REQUIRE(std::equal(any.begin(), any.end(), bar.begin()));
        REQUIRE(any.get<text8>().storage() == u8"bar");
    }
}


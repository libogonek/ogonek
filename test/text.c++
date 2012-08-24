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

// Tests for <ogonek/text.h++>

#include <ogonek/text.h++>
#include <ogonek/encoding/utf8.h++>
#include <ogonek/encoding/utf16.h++>
#include <ogonek/encoding/utf32.h++>

#include <catch.h++>

TEST_CASE("text", "text tests") {
    SECTION("general", "General test") {
        using text8 = ogonek::basic_text<ogonek::utf8>;
        using text16 = ogonek::basic_text<ogonek::utf16>;
        using text32 = ogonek::basic_text<ogonek::utf32>;

        text8 a { U"blah\U0001F4A9" };
        REQUIRE(a.storage() == u8"blah\U0001F4A9");
        text16 b { U"blah\U0001F4A9" };
        REQUIRE(b.storage() == u"blah\U0001F4A9");
        text32 c { U"blah\U0001F4A9" };
        REQUIRE(c.storage() == U"blah\U0001F4A9");
        std::u32string x = U"blah\U0001F4A9";
        text16 d { x };
        REQUIRE(d.storage() == u"blah\U0001F4A9");
        text16 e { d };
        REQUIRE(e.storage() == u"blah\U0001F4A9");
        text16 f { a };
        REQUIRE(f.storage() == u"blah\U0001F4A9");
        text16 g { c };
        REQUIRE(g.storage() == u"blah\U0001F4A9");
    }
}


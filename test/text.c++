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
#include <ogonek/normalization.h++> // TODO fix includes

#include <unordered_map>

#include "utils.h++"
#include <catch.h++>

using text8 = test::text<ogonek::utf8>;
using text16 = test::text<ogonek::utf16>;
using text32 = test::text<ogonek::utf32>;
using text_ascii = test::text<ogonek::ascii>;

using string8 = test::string<ogonek::utf8>;
using string16 = test::string<ogonek::utf16>;
using string32 = test::string<ogonek::utf32>;
using string_ascii = test::string<ogonek::ascii>;

TEST_CASE("text", "text tests") {
    SECTION("construction", "text constructor tests") {
        text8 x { u"blah\U0001F4A9" };
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
    }
    SECTION("empty", "any_text emptiness query tests") {
        REQUIRE(text8{}.empty());
        REQUIRE(text8{U""}.empty());
        REQUIRE_FALSE(text8{U"foo"}.empty());
    }
    SECTION("op==", "text::op== tests"){
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
    }
    SECTION("append", "text::append tests") {
        text8 foo { U"foo" };
        auto n = foo;
        text16 o { U"bar" };
        n.append(o);
        REQUIRE(n == text8{U"foobar"});

        n = foo;
        string32 p { U"bar" };
        n.append(p);
        REQUIRE(n == text8{U"foobar"});
        
        n = foo;
        n.append(U"bar");
        REQUIRE(n == text8{U"foobar"});
    }
    SECTION("concat", "concat() tests") {
        text8 a { U"a" };
        text8 b { U"b" };
        text8 c { U"c" };
        text16 d { U"d" };
        string32 e { U"e" };
        char32_t const* f = U"f";
        char16_t const* g = u"g";
        string32 bad { U"\xD800" };
        
        auto r0 = ogonek::concat(a, e, b, f, c);
        REQUIRE(r0 == text8{U"aebfc"});
        
        auto r1 = ogonek::concat<ogonek::utf8>(a, b, c, d, e, f, g);
        REQUIRE(r1 == text8{U"abcdefg"});
        
        auto r2 = ogonek::concat(ogonek::use_replacement_character, a, e, bad, b, f, c);
        REQUIRE(r2 == text8{U"ae\uFFFDbfc"});
        
        auto r3 = ogonek::concat<ogonek::utf8>(ogonek::use_replacement_character, a, b, c, d, bad, e, f, g);
        REQUIRE(r3 == text8{U"abcd\uFFFDefg"});
    }
    SECTION("erase", "text::erase tests") {
        text8 t { U"foo\u200bxbar" };
        auto from = std::next(t.begin(), 3);
        auto to = std::next(from, 2);
        t.erase(from, to);
        REQUIRE(t == text8{U"foobar"});
    }
    SECTION("insert", "text::insert tests") {
        text8 t { U"foar" };
        auto at = std::next(t.begin(), 2);
        t.insert(at, U"ob");
        REQUIRE(t == text8{U"foobar"});
    }
    SECTION("replace", "text::replace tests") {
        text8 t { U"fo\u200bar" };
        auto from = std::next(t.begin(), 2);
        auto to = std::next(from);
        t.replace(from, to, U"ob");
        REQUIRE(t == text8{U"foobar"});
    }
    SECTION("hash", "hashing tests") {
        text8 a { U"bla\u0308h" };
        text8 b { U"blah" };
        text8 c { U"bl\u00e4h" };
        std::unordered_map<text8, int> map { { a, 42 } };
        map[b] = 17;
        map[c] = 23;
        REQUIRE(map.size() == 2);
        REQUIRE(map[a] == 23);
        REQUIRE(map[b] == 17);
        REQUIRE(map[c] == 23);
    }
}
TEST_CASE("any", "any_text tests") {
    SECTION("construction", "any_text construction tests") {
        auto foo = text16 { U"foo" };
        ogonek::any_text any = foo; 
        REQUIRE(std::equal(any.begin(), any.end(), foo.begin()));
        REQUIRE(any.get<text16>().storage() == string16(u"foo"));
    }
    SECTION("assignment", "any_text assignment tests") {
        ogonek::any_text any = text16 { U"foo" }; 
        auto bar = text8 { U"bar" };
        any = bar;
        REQUIRE(std::equal(any.begin(), any.end(), bar.begin()));
        REQUIRE(any.get<text8>().storage() == string8(u8"bar"));
    }
    SECTION("empty", "any_text emptiness query tests") {
        REQUIRE(ogonek::any_text{text8{}}.empty());
        REQUIRE(ogonek::any_text{text8{U""}}.empty());
        REQUIRE_FALSE(ogonek::any_text{text8{U"foo"}}.empty());
    }
    SECTION("op==", "any_text::op== tests") {
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


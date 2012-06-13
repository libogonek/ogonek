// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Test runner

#define CATCH_CONFIG_MAIN
#include <catch.h++>

#include <ogonek/codec.h++>

TEST_CASE("foo", "bar") {
    auto x = ogonek::codec::utf8::encode('a');
    REQUIRE(x.size() == 1);
    REQUIRE(*x.begin() == 'a');

    x = ogonek::codec::utf8::encode(U"\U0001f4a9"[0]);
    std::cout << x.size();
    REQUIRE(x.size() == 4);
    REQUIRE(*(x.begin()+0) == 0xF0);
    REQUIRE(*(x.begin()+1) == 0x9F);
    REQUIRE(*(x.begin()+2) == 0x92);
    REQUIRE(*(x.begin()+3) == 0xA9);
}


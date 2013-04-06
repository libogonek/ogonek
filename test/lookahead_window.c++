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

// Tests for <ogonek/detail/container/lookahead_window.h++>

#include <ogonek/detail/container/lookahead_window.h++>

#include <catch.h++>

#include <algorithm>
#include <vector>

TEST_CASE("lookahead", "Tests for lookahead_window") {
    std::vector<int> source(100);
    std::iota(source.begin(), source.end(), 0);

    ogonek::detail::lookahead_window<std::vector<int>::iterator, 2, 2> window(source.begin(), source.end());
    REQUIRE_FALSE(window.exhausted());
    REQUIRE((window.position() - source.begin()) == 1);

    window.advance();
    window.advance();
    window.advance();
    REQUIRE(window[-2] == 2);
    REQUIRE(window[-1] == 3);
    REQUIRE(window[0] == 4);
    REQUIRE(window[1] == 5);
    REQUIRE(window[2] == 6);
    REQUIRE_FALSE(window.exhausted());

    for(int i = 7; i < 100; ++i) {
        window.advance();
    }
    REQUIRE(window[-2] == 95);
    REQUIRE(window[-1] == 96);
    REQUIRE(window[0] == 97);
    REQUIRE(window[1] == 98);
    REQUIRE(window[2] == 99);
    REQUIRE_FALSE(window.exhausted());

    window.advance();
    REQUIRE(window[-2] == 96);
    REQUIRE(window[-1] == 97);
    REQUIRE(window[0] == 98);
    REQUIRE(window[1] == 99);
    REQUIRE(window[2] == -1);
    REQUIRE_FALSE(window.exhausted());

    window.advance();
    REQUIRE(window[-2] == 97);
    REQUIRE(window[-1] == 98);
    REQUIRE(window[0] == 99);
    REQUIRE(window[1] == -1);
    REQUIRE(window[2] == -1);
    REQUIRE_FALSE(window.exhausted());

    window.advance();
    REQUIRE(window[-2] == 98);
    REQUIRE(window[-1] == 99);
    REQUIRE(window[0] == -1);
    REQUIRE(window[1] == -1);
    REQUIRE(window[2] == -1);
    REQUIRE(window.exhausted());
}

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

// Tests for <ogonek/detail/container/small_vector.h++>

#include <ogonek/detail/container/small_vector.h++>

#include <catch.h++>

#include <cstdint>

TEST_CASE("small_vector", "small_vector tests") {
    // cursory tests only for now
    ogonek::detail::small_vector<int, 4> v { 0, 1, 2 };

    CHECK(v.size() == 3);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
    CHECK(v[2] == 2);
    auto origin = &v[0];

    v.push_back(3);
    CHECK(v.size() == 4);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
    CHECK(v[2] == 2);
    CHECK(v[3] == 3);
    CHECK(&v[0] == origin);

    v.push_back(4);
    CHECK(v.size() == 5);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
    CHECK(v[2] == 2);
    CHECK(v[3] == 3);
    CHECK(v[4] == 4);
    CHECK(&v[0] != origin);

    int i = 0;
    for(auto e : v) {
        CHECK(e == i);
        ++i;
    }
}

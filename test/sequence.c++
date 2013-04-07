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

// Tests for <ogonek/detail/sequence.h++>

#include <ogonek/detail/sequence.h++>

#include "utils.h++"
#include <catch.h++>

#include <iterator>

namespace seq = ogonek::detail;

struct counter : seq::smart_sequence {
    counter(int max) : max(max) {}

    using value_type = int;
    using reference = value_type;

    bool empty() const { return cur == max; }
    reference front() const { return cur; }
    void pop_front() { ++cur; }

    int cur = 0;
    int max;
};

TEST_CASE("meta", "sequence meta-programming facilities") {
    counter z = 0;
    auto&& a = seq::forward_as_sequence(z);
    REQUIRE(seq::sequence::empty(a));

    counter c = 2;
    auto&& b = seq::forward_as_sequence(c);
    REQUIRE(!seq::sequence::empty(b));
    REQUIRE(seq::sequence::front(b) == 0);
    seq::sequence::pop_front(b);
    REQUIRE(!seq::sequence::empty(b));
    REQUIRE(seq::sequence::front(b) == 1);
    seq::sequence::pop_front(b);
    REQUIRE(seq::sequence::empty(b));
}


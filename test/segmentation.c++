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

// Tests for <ogonek/segmentation.h++>

#include <ogonek/segmentation.h++>
#include <ogonek/types.h++>

#include <catch.h++>

#include <string>

TEST_CASE("grapheme_clusters", "Extended grapheme cluster ranges") {
    // Example clusters from UAX #29
    std::u32string input = U"\x0067\x0308\xAC01\x1100\x1161\x11A8\x0BA8\x0BBF\x0E40\x0E01\x0E01\x0E33\x0937\x093F";
    // expected result:      | 0067  0308| AC01| 1100  1161  11A8| 0BA8  0BBF| 0E40| 0E01| 0E01  0E33| 0937  093F|
    auto clusters = ogonek::grapheme_clusters(input);
    auto it = clusters.begin();
    CHECK(it->begin() == input.begin());
    CHECK(it->end()   == input.begin() + 2);
    ++it;
    CHECK(it->begin() == input.begin() + 2);
    CHECK(it->end()   == input.begin() + 3);
    ++it;
    CHECK(it->begin() == input.begin() + 3);
    CHECK(it->end()   == input.begin() + 6);
    ++it;
    CHECK(it->begin() == input.begin() + 6);
    CHECK(it->end()   == input.begin() + 8);
    ++it;
    CHECK(it->begin() == input.begin() + 8);
    CHECK(it->end()   == input.begin() + 9);
    ++it;
    CHECK(it->begin() == input.begin() + 9);
    CHECK(it->end()   == input.begin() + 10);
    ++it;
    CHECK(it->begin() == input.begin() + 10);
    CHECK(it->end()   == input.begin() + 12);
    ++it;
    CHECK(it->begin() == input.begin() + 12);
    CHECK(it->end()   == input.end());
    ++it;
    CHECK(it == clusters.end());
}


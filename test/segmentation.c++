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

#include <iterator>
#include <string>
#include <vector>

struct grapheme_cluster_test {
    std::u32string input;
    std::vector<int> breaks;
};

grapheme_cluster_test grapheme_cluster_test_data[] = {
    #include "grapheme_cluster_test.g.inl"
};

TEST_CASE("grapheme_clusters", "Extended grapheme cluster ranges") {
    for(auto&& test : grapheme_cluster_test_data) {
        auto clusters = ogonek::grapheme_clusters(test.input);
        auto it = clusters.begin();
        auto last_break = 0;
        for(auto&& this_break : test.breaks) {
            CHECK(it->begin() == test.input.begin() + last_break);
            CHECK(it->end()   == test.input.begin() + this_break);
            last_break = this_break;
            ++it;
        }
        CHECK(it == clusters.end());
    }
    SECTION("RI", "regional indicator rules") {
        std::u32string no_break = U"\x1F1E6\x1F1E7";
        std::u32string with_break = U"\x1F1E6\x200B\x1F1E7";
        auto no_break_clusters = ogonek::grapheme_clusters(no_break);
        CHECK(no_break_clusters.begin()->begin() == std::begin(no_break));
        CHECK(no_break_clusters.begin()->end() == std::end(no_break));
        CHECK(std::next(no_break_clusters.begin()) == no_break_clusters.end());

        auto with_break_clusters = ogonek::grapheme_clusters(with_break);
        auto it = with_break_clusters.begin();
        CHECK(it->begin() == std::begin(with_break));
        CHECK(it->end() == std::begin(with_break)+1);
        ++it;
        CHECK(it->begin() == std::begin(with_break)+1);
        CHECK(it->end() == std::begin(with_break)+2);
        ++it;
        CHECK(it->begin() == std::begin(with_break)+2);
        CHECK(it->end() == std::end(with_break));
        ++it;
        CHECK(it == with_break_clusters.end());
        CHECK(with_break_clusters.begin()->begin() == std::begin(with_break));
    }
}


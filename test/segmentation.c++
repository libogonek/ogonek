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

// Tests for <ogonek/segmentation.h++>

#include <ogonek/segmentation.h++>
#include <ogonek/types.h++>

#include <catch.h++>

#include <iterator>
#include <string>
#include <vector>

struct break_test {
    std::u32string input;
    std::vector<int> breaks;
};

break_test grapheme_cluster_test_data[] = {
    #include "grapheme_cluster_test.g.inl"
};

TEST_CASE("grapheme_clusters", "Extended grapheme cluster ranges") {
    for(auto&& test : grapheme_cluster_test_data) {
        auto clusters = ogonek::grapheme_clusters(test.input);
        auto it = clusters.begin();
        auto last_break = 0;
        for(auto&& this_break : test.breaks) {
            CHECK((it->begin() - test.input.begin()) == last_break);
            CHECK((it->end()   - test.input.begin()) == this_break);
            last_break = this_break;
            ++it;
        }
        CHECK(it == clusters.end());
    }
}

break_test word_test_data[] = {
    #include "word_test.g.inl"
};

namespace {
    template <typename Fun>
    void test_segmentation(break_test const& test, Fun fun) {
        std::vector<unsigned> v(test.input.begin(), test.input.end());
        auto items = fun(v);
        auto it = items.begin();
        auto last_break = 0;
        for(auto&& this_break : test.breaks) {
            CHECK((it->begin() - v.begin()) == last_break);
            CHECK((it->end()   - v.begin()) == this_break);
            last_break = this_break;
            ++it;
        }
        CHECK(items.end() == it);
    }
} // namespace

struct {
    template <typename ForwardRange>
    auto operator()(ForwardRange const& range) const -> decltype(ogonek::words(range)) {
        return ogonek::words(range);
    }
} break_words;

TEST_CASE("words 25", "Test 25") {
    test_segmentation(word_test_data[25], break_words);
}
TEST_CASE("words 28", "Test 28") {
    test_segmentation(word_test_data[28], break_words);
}
TEST_CASE("words 258", "Test 258") {
    test_segmentation(word_test_data[258], break_words);
}
TEST_CASE("words 718", "Test 718") {
    test_segmentation(word_test_data[718], break_words);
}

TEST_CASE("words", "Word ranges") {
    for(auto&& test : word_test_data) {
        test_segmentation(test, break_words);
    }
}

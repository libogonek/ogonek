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

namespace {
    struct break_test {
        std::u32string input;
        std::vector<int> breaks;
    };

    template <typename Fun>
    void test_segmentation(break_test const& test, Fun fun) {
        auto items = fun(test.input);
        auto it = items.begin();
        auto last_break = 0;
        for(auto&& this_break : test.breaks) {
            CHECK((it->begin() - test.input.begin()) == last_break);
            CHECK((it->end()   - test.input.begin()) == this_break);
            last_break = this_break;
            ++it;
        }
        CHECK(items.end() == it);
    }
} // namespace

namespace {
    break_test grapheme_cluster_test_data[] = {
        #include "grapheme_cluster_test.g.inl"
    };

    struct {
        template <typename ForwardRange>
        auto operator()(ForwardRange const& range) const -> decltype(ogonek::grapheme_clusters(range)) {
            return ogonek::grapheme_clusters(range);
        }
    } break_grapheme_clusters;
} // namespace

TEST_CASE("grapheme_clusters", "Extended grapheme cluster ranges") {
    SECTION("official", "Official grapheme cluster tests") {
        for(auto&& test : grapheme_cluster_test_data) {
            test_segmentation(test, break_grapheme_clusters);
        }
    }
}

namespace {
    break_test word_test_data[] = {
        #include "word_test.g.inl"
    };

    struct {
        template <typename ForwardRange>
        auto operator()(ForwardRange const& range) const -> decltype(ogonek::words(range)) {
            return ogonek::words(range);
        }
    } break_words;
} // namespace

TEST_CASE("words", "Word ranges") {
    SECTION("official", "Official word tests") {
        for(auto&& test : word_test_data) {
            test_segmentation(test, break_words);
        }
    }
}

namespace {
    break_test sentence_test_data[] = {
        #include "sentence_test.g.inl"
    };
} // namespace

namespace {
    break_test line_test_data[] = {
        #include "line_test.g.inl"
    };
} // namespace


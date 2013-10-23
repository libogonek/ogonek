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

#include "segmentation.g.h++"
#include "utils.h++"
#include <catch.h++>

#include <iterator>
#include <string>
#include <vector>

namespace {
    template <typename Fun>
    void test_segmentation(test::break_test const& test, Fun fun) {
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
    struct {
        template <typename ForwardRange>
        auto operator()(ForwardRange const& range) const -> decltype(ogonek::graphemes(range)) {
            return ogonek::graphemes(range);
        }
    } break_graphemes;
} // namespace

TEST_CASE("graphemes", "Extended grapheme ranges") {
    SECTION("official", "Official grapheme tests") {
        for(auto&& test : test::grapheme_test_data) {
            test_segmentation(test, break_graphemes);
        }
    }
}

namespace {
    struct {
        template <typename ForwardRange>
        auto operator()(ForwardRange const& range) const -> decltype(ogonek::words(range)) {
            return ogonek::words(range);
        }
    } break_words;
} // namespace

TEST_CASE("words", "Word ranges") {
    SECTION("official", "Official word tests") {
        for(auto&& test : test::word_test_data) {
            test_segmentation(test, break_words);
        }
    }
    SECTION("issue-0019", "test for issue #19") {
        using text = ogonek::text<ogonek::utf8>;
        std::vector<text> words;
        for(auto word : ogonek::words(test::ustring(U"ABC DEF GREG"))) {
            words.emplace_back(word);
        }
        REQUIRE(words[0].storage() == u8"ABC");
        REQUIRE(words[1].storage() == u8" ");
        REQUIRE(words[2].storage() == u8"DEF");
        REQUIRE(words[3].storage() == u8" ");
        REQUIRE(words[4].storage() == u8"GREG");
    }
}

namespace {
} // namespace

namespace {
} // namespace


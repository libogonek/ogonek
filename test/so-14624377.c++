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

// Tests for Stack Overflow question 14624377

#include <ogonek/segmentation.h++>
#include <ogonek/normalization.h++>

#include <catch.h++>

TEST_CASE("so14624377", "Stack Overflow question 14624377") {
    std::u32string input { U"\u1109\u1165\uc6b8\ud2b9\ubcc4\uc2dc"};
    std::u32string expected[] = { U"\u1109\u1165", U"\uc6b8", U"\ud2b9", U"\ubcc4", U"\uc2dc" };

    SECTION("grapheme clusters", "with segmentation algorithm") {
        int i = 0;
        for(auto cluster : ogonek::grapheme_clusters(input)) {
            std::u32string syllable { cluster.begin(), cluster.end() };
            REQUIRE(syllable == expected[i]);
            ++i;
        }
    }
    SECTION("nfc", "with normalisation") {
        auto norm = ogonek::normalize<ogonek::nfc>(input);
        std::u32string result(norm.begin(), norm.end());
        int i = 0;
        for(auto character : result) {
            std::u32string syllable(1, character);
            REQUIRE(ogonek::canonically_equivalent(syllable, expected[i]));
            ++i;
        }
    }
}

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
    SECTION("grapheme clusters", "with segmentation algorithm") {
        std::u32string s { U"\u1109\u1165\uc6b8\ud2b9\ubcc4\uc2dc"};
        for(auto cluster : ogonek::grapheme_clusters(s)) {
            for(auto c : cluster) {
                std::cout << std::hex << int(c) << ' ';
            }
            std::cout << '\n';
        }
    }
    SECTION("nfc", "with normalisation") {
        std::u32string s { U"\u1109\u1165\uc6b8\ud2b9\ubcc4\uc2dc"};
        auto norm = ogonek::normalize<ogonek::nfc>(s);
        std::u32string result(norm.begin(), norm.end());
        for(auto c : result) {
            std::cout << std::hex << int(c) << ' ';
        }
        std::cout << '\n';
    }
}

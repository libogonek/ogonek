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

// Tests for <ogonek/normalization.h++>

#include <ogonek/normalization.h++>

#include <ogonek/encoding/utf32.h++>
#include <ogonek/text.h++>

#include <catch.h++>

TEST_CASE("decompose", "Decomposition") {
    using test_text = ogonek::basic_text<ogonek::utf32>;
    test_text in { U"ABC\x00C5\x00F4\x1E69\x1E0B\x0323\x0071\x0307\x0323" };
    test_text out { ogonek::decompose(in) };
    REQUIRE(out.storage() == U"ABC\x0041\x030A\x006F\x0302\x0073\x0323\x0307\x0064\x0307\x0323\x0071\x0307\x0323");
}


// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tests for <ogonek/encode.h++>

#include <ogonek/encode.h++>

#include <range/v3/to_container.hpp>
#include <range/v3/view/c_str.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>

#include <vector>

#include <cstddef>
#include <cstdint>

#include "util.h++"
#include <catch.hpp>

namespace test {
    struct one_to_one_encoding {
        using code_unit = char32_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(char32_t u) {
            return { u + 1 };
        }
    };
    struct one_to_many_encoding {
        using code_unit = char16_t;
        static constexpr std::size_t max_width = 1;
        static std::vector<code_unit> encode_one(char32_t u) {
            return { static_cast<code_unit>(u / 0x10000), static_cast<code_unit>(u % 0x10000) };
        }
    };
} // namespace test

TEST_CASE("encode", "Encoding") {
    SECTION("1to1", "Encoding one-to-one") {
        std::u32string base = U"08AF";
        auto str = ogonek::encode<test::one_to_one_encoding>(ranges::view::all(base))
                 | ranges::to_vector;
        CHECK(str == (std::vector<char32_t>{ U'1', U'9', U'B', U'G' }));
    }
    SECTION("1ton", "Encoding one-to-many") {
        std::u32string base = U"08AF\x10017";
        auto str = ogonek::encode<test::one_to_many_encoding>(ranges::view::all(base))
                 | ranges::to_vector;
        CHECK(str == (std::vector<char16_t>{ u'\0', u'0', u'\0', u'8', u'\0', u'A', u'\0', u'F', u'\x1', u'\x17' }));
    }
}


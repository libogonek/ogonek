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

// Tests for <ogonek/byte_order.h++>

#include <ogonek/byte_order.h++>

#include <catch.h++>

#include <array>

TEST_CASE("big_endian", "Big endian byte order") {
    SECTION("write16", "Writing 16-bit values") {
        std::uint16_t x = 0x1234;
        std::array<std::uint8_t, 2> bytes;
        ogonek::big_endian::write(bytes.begin(), x);
        REQUIRE(bytes[0] == 0x12);
        REQUIRE(bytes[1] == 0x34);
    }
    SECTION("write32", "Writing 32-bit values") {
        std::uint32_t x = 0x12345678;
        std::array<std::uint8_t, 4> bytes;
        ogonek::big_endian::write(bytes.begin(), x);
        REQUIRE(bytes[0] == 0x12);
        REQUIRE(bytes[1] == 0x34);
        REQUIRE(bytes[2] == 0x56);
        REQUIRE(bytes[3] == 0x78);
    }
    SECTION("read16", "Reading 16-bit values") {
        std::array<std::uint8_t, 2> bytes {{ 0x12, 0x34 }};
        std::uint16_t x = ogonek::big_endian::read<std::uint16_t>(bytes.begin());
        REQUIRE(x == 0x1234);
    }
    SECTION("read32", "Reading 32-bit values") {
        std::array<std::uint8_t, 4> bytes {{ 0x12, 0x34, 0x56, 0x78 }};
        std::uint32_t x = ogonek::big_endian::read<std::uint32_t>(bytes.begin());
        REQUIRE(x == 0x12345678);
    }
}
TEST_CASE("little_endian", "Little endian byte order") {
    SECTION("write16", "Writing 16-bit values") {
        std::uint16_t x = 0x1234;
        std::array<std::uint8_t, 2> bytes;
        ogonek::little_endian::write(bytes.begin(), x);
        REQUIRE(bytes[0] == 0x34);
        REQUIRE(bytes[1] == 0x12);
    }
    SECTION("write32", "Writing 32-bit values") {
        std::uint32_t x = 0x12345678;
        std::array<std::uint8_t, 4> bytes;
        ogonek::little_endian::write(bytes.begin(), x);
        REQUIRE(bytes[0] == 0x78);
        REQUIRE(bytes[1] == 0x56);
        REQUIRE(bytes[2] == 0x34);
        REQUIRE(bytes[3] == 0x12);
    }
    SECTION("read16", "Reading 16-bit values") {
        std::array<std::uint8_t, 2> bytes {{ 0x34, 0x12 }};
        std::uint16_t x = ogonek::little_endian::read<std::uint16_t>(bytes.begin());
        REQUIRE(x == 0x1234);
    }
    SECTION("read32", "Reading 32-bit values") {
        std::array<std::uint8_t, 4> bytes {{ 0x78, 0x56, 0x34, 0x12 }};
        std::uint32_t x = ogonek::little_endian::read<std::uint32_t>(bytes.begin());
        REQUIRE(x == 0x12345678);
    }
}


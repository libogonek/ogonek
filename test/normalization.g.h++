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

// This file was automatically generated on 2013-11-08T13:46:42.0520590Z

// Unicode normalization test data

#ifndef OGONEK_TEST_NORMALIZATION_HPP
#define OGONEK_TEST_NORMALIZATION_HPP

#include <ogonek/types.h++>

#include "utils.h++"

namespace test {
    struct normalization_test {
        ogonek::code_point const* input;
        ogonek::code_point const* nfc;
        ogonek::code_point const* nfd;
        ogonek::code_point const* nfkc;
        ogonek::code_point const* nfkd;
    };

    extern normalization_test normalization_test_data[18377];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP


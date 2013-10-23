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

// This file was automatically generated on 2013-10-23T01:16:53.2215220Z


// Types for segmentation tests

#ifndef OGONEK_TEST_SEGMENTATION_HPP
#define OGONEK_TEST_SEGMENTATION_HPP

#include "utils.h++"
#include <vector>

namespace test {
    struct break_test {
        test::ustring input;
        std::vector<int> breaks;
    };

    extern break_test grapheme_test_data[402];
    extern break_test word_test_data[1372];
    extern break_test sentence_test_data[495];
    extern break_test line_test_data[6310];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP


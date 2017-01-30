cmake_minimum_required (VERSION 3.2)

set (test_runner runner.c++)

add_executable (ucd_test ${test_runner} ucd.c++)
target_link_libraries (ucd_test ogonek_data Catch)

add_executable (encoding_test ${test_runner} encoded.c++)
target_link_libraries (encoding_test Catch range-v3)

cmake_minimum_required (VERSION 3.2)
project (Ogonek)
include (deps/catch.cmake)
include (deps/range-v3.cmake)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_COMPILER clang++)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories (${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src/ucd)
add_subdirectory (test)

include (test/tests.cmake)

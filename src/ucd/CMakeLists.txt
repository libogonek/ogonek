cmake_minimum_required (VERSION 3.2)

file (GLOB_RECURSE ucd_SRC "*.c++")

set (OGONEK_ABI abiv0)
set (UCD_DIR ${PROJECT_SOURCE_DIR}/data/ucd)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (UCD_SRC_DIR ${PROJECT_SOURCE_DIR}/src/ucd)

add_custom_target(ucd
    COMMAND python ${PROJECT_SOURCE_DIR}/tools/transforms/ucd.py ${OGONEK_ABI} ${UCD_DIR} ${INCLUDE_DIR} ${UCD_SRC_DIR})

add_library (ogonek_data STATIC ${ucd_SRC})

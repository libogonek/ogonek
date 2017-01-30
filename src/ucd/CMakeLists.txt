cmake_minimum_required (VERSION 3.2)

set (OGONEK_ABI abiv0)
set (UCD_DIR ${PROJECT_SOURCE_DIR}/data/ucd)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (UCD_SRC_DIR ${PROJECT_SOURCE_DIR}/src/ucd)
set (UCD_TRANSFORM_TOOL ${PROJECT_SOURCE_DIR}/tools/transforms/ucd.py)

file (GLOB_RECURSE ucd_txt_SRC ${UCD_SRC_DIR}/*)

execute_process (
    COMMAND python ${UCD_TRANSFORM_TOOL} --files ${UCD_SRC_DIR}
    OUTPUT_VARIABLE ucd_gen_SRC)

add_custom_command(
    OUTPUT ${ucd_gen_SRC}
    COMMAND python ${UCD_TRANSFORM_TOOL} ${OGONEK_ABI} ${UCD_DIR} ${INCLUDE_DIR} ${UCD_SRC_DIR}
    DEPENDS ${PROJECT_SOURCE_DIR}/tools/transforms/ucd.py
    COMMENT "Translating UCD...")

add_library (ogonek_data STATIC ${ucd_gen_SRC})

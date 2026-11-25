cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrf_rid_scanner)

zephyr_include_directories(external/librid/include)

zephyr_library_sources(
    src/main.c
    external/librid/src/basic_id.c
    external/librid/src/location.c
    external/librid/src/message.c
    external/librid/src/system.c
    external/librid/src/message_pack.c
    external/librid/src/auth.c
    external/librid/src/auth_page.c
    external/librid/src/operator_id.c
    external/librid/src/self_id.c
    external/librid/src/transport.c
    external/librid/src/version.c
    external/librid/src/json.c
)

set(DRIP_LOCAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/libdrip)
if(EXISTS ${DRIP_LOCAL_DIR}/CMakeLists.txt)
    zephyr_include_directories(${DRIP_LOCAL_DIR}/include)
    zephyr_compile_definitions(RID_HAVE_LIBDRIP)
    zephyr_library_sources(
        ${DRIP_LOCAL_DIR}/src/det.c
        ${DRIP_LOCAL_DIR}/src/error.c
        ${DRIP_LOCAL_DIR}/src/format.c
        ${DRIP_LOCAL_DIR}/src/hash.c
        ${DRIP_LOCAL_DIR}/src/json.c
        ${DRIP_LOCAL_DIR}/src/link.c
        ${DRIP_LOCAL_DIR}/src/manifest.c
        ${DRIP_LOCAL_DIR}/src/wrapper.c
    )
endif()

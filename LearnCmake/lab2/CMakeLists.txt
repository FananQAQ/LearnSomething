cmake_minimum_required(VERSION 3.16)

project(lab2_cmake
    VERSION 1.0.0
    DESCRIPTION "CMake advanced lab: multi-target, install, export"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LAB2_ENABLE_VERBOSE "Enable verbose output in CLI" ON)
option(LAB2_BUILD_SHARED_STATS "Build stats module as SHARED library" ON)
option(LAB2_ENABLE_DEMO_SCALE "Scale demo sample values by 2" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lab2/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/lab2/version.h
    @ONLY
)

include(CTest)
enable_testing()

add_subdirectory(lib)
add_subdirectory(apps)
add_subdirectory(tests)

# ---------------------------------------------------------------------------
# Install rules + CMake package export (find_package(lab2) after install)
# ---------------------------------------------------------------------------
set(LAB2_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/lab2)

install(
    TARGETS lab2_core lab2_config lab2_stats lab2_cli
    EXPORT lab2Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY lib/config/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lab2
    FILES_MATCHING PATTERN "*.h"
)

install(
    DIRECTORY lib/core/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lab2
    FILES_MATCHING PATTERN "*.h"
)

install(
    DIRECTORY lib/stats/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lab2
    FILES_MATCHING PATTERN "*.h"
)

install(
    EXPORT lab2Targets
    FILE lab2Targets.cmake
    NAMESPACE lab2::
    DESTINATION ${LAB2_INSTALL_CMAKEDIR}
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Lab2Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/Lab2Config.cmake
    INSTALL_DESTINATION ${LAB2_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/Lab2ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/Lab2Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Lab2ConfigVersion.cmake
    DESTINATION ${LAB2_INSTALL_CMAKEDIR}
)

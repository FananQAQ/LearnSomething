add_library(lab2_core STATIC
    string_utils.cpp
)
add_library(lab2::core ALIAS lab2_core)

target_include_directories(lab2_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/lab2>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(lab2_core
    PUBLIC
        lab2::config
)

lab2_set_warnings(lab2_core)

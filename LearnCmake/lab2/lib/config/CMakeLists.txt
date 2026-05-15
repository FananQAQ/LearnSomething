add_library(lab2_config INTERFACE)
add_library(lab2::config ALIAS lab2_config)

target_include_directories(lab2_config
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/lab2>
)

target_compile_definitions(lab2_config
    INTERFACE
        LAB2_APP_NAME=\"lab2_cli\"
        LAB2_DEFAULT_DELIMITER=','
)

add_executable(lab2_cli main.cpp)

target_link_libraries(lab2_cli
    PRIVATE
        lab2::core
        lab2::stats
)

if(LAB2_ENABLE_VERBOSE)
    target_compile_definitions(lab2_cli PRIVATE LAB2_ENABLE_VERBOSE=1)
endif()

if(LAB2_ENABLE_DEMO_SCALE)
    target_compile_definitions(lab2_cli PRIVATE LAB2_ENABLE_DEMO_SCALE=1)
endif()

if(LAB2_BUILD_SHARED_STATS)
    target_compile_definitions(lab2_cli PRIVATE LAB2_STATS_SHARED)
endif()

lab2_set_warnings(lab2_cli)

if(LAB2_BUILD_SHARED_STATS AND WIN32)
    add_custom_command(TARGET lab2_cli POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:lab2_stats>
            $<TARGET_FILE_DIR:lab2_cli>
        COMMENT "Copy lab2_stats.dll next to lab2_cli for local runs"
    )
endif()

add_custom_target(run_demo
    COMMAND lab2_cli
    DEPENDS lab2_cli
    WORKING_DIRECTORY $<TARGET_FILE_DIR:lab2_cli>
    COMMENT "Run lab2_cli demo"
)

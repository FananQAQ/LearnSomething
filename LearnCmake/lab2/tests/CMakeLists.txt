include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_string test_string.cpp)
target_link_libraries(test_string PRIVATE lab2::core GTest::gtest_main)
lab2_set_warnings(test_string)

add_executable(test_stats test_stats.cpp)
target_link_libraries(test_stats PRIVATE lab2::stats GTest::gtest_main)
if(LAB2_BUILD_SHARED_STATS)
    target_compile_definitions(test_stats PRIVATE LAB2_STATS_SHARED)
    if(WIN32)
        add_custom_command(TARGET test_stats POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:lab2_stats>
                $<TARGET_FILE_DIR:test_stats>
            COMMENT "Copy lab2_stats.dll next to test_stats"
        )
    endif()
endif()
lab2_set_warnings(test_stats)

include(GoogleTest)
gtest_discover_tests(test_string)
gtest_discover_tests(test_stats)

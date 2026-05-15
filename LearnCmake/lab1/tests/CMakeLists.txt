include(FetchContent)

FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "Force shared crt" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(test_math 
    test_math.cpp
)

target_link_libraries(test_math
    PRIVATE
        math_utils
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_math)

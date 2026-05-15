if(LAB2_BUILD_SHARED_STATS)
    add_library(lab2_stats SHARED stats.cpp)
    target_compile_definitions(lab2_stats PRIVATE LAB2_STATS_BUILD_DLL)
else()
    add_library(lab2_stats STATIC stats.cpp)
endif()

add_library(lab2::stats ALIAS lab2_stats)

target_include_directories(lab2_stats
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/lab2>
)

lab2_set_warnings(lab2_stats)

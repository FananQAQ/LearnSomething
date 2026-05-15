cmake_minimum_required(VERSION 3.16)
project(lab1_cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_VERBOSE_LOG "Enable verbose output in app" OFF)
option(USE_DOUBLE_VALUE "Use double value" OFF)

include(CTest)
enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
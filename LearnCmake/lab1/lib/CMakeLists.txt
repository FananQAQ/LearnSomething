add_library(math_utils
    math_utils.cpp
    )
    
target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
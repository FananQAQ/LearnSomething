add_executable(lab1_app 
    main.cpp
    )

target_link_libraries(lab1_app
    PRIVATE
        math_utils
    )

if(ENABLE_VERBOSE_LOG)
    target_compile_definitions(lab1_app PRIVATE ENABLE_VERBOSE_LOG=1)
endif()

if(USE_DOUBLE_VALUE)
    target_compile_definitions(lab1_app PRIVATE USE_DOUBLE_VALUE=1)
endif()

install(TARGETS lab1_app RUNTIME DESTINATION bin)

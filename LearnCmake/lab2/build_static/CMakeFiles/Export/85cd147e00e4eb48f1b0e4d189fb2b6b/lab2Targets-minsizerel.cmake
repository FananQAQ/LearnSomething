#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lab2::lab2_core" for configuration "MinSizeRel"
set_property(TARGET lab2::lab2_core APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(lab2::lab2_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/lab2_core.lib"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_core )
list(APPEND _cmake_import_check_files_for_lab2::lab2_core "${_IMPORT_PREFIX}/lib/lab2_core.lib" )

# Import target "lab2::lab2_stats" for configuration "MinSizeRel"
set_property(TARGET lab2::lab2_stats APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(lab2::lab2_stats PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/lab2_stats.lib"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_stats )
list(APPEND _cmake_import_check_files_for_lab2::lab2_stats "${_IMPORT_PREFIX}/lib/lab2_stats.lib" )

# Import target "lab2::lab2_cli" for configuration "MinSizeRel"
set_property(TARGET lab2::lab2_cli APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(lab2::lab2_cli PROPERTIES
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/lab2_cli.exe"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_cli )
list(APPEND _cmake_import_check_files_for_lab2::lab2_cli "${_IMPORT_PREFIX}/bin/lab2_cli.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

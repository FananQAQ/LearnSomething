#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lab2::lab2_core" for configuration "Debug"
set_property(TARGET lab2::lab2_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(lab2::lab2_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/lab2_core.lib"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_core )
list(APPEND _cmake_import_check_files_for_lab2::lab2_core "${_IMPORT_PREFIX}/lib/lab2_core.lib" )

# Import target "lab2::lab2_stats" for configuration "Debug"
set_property(TARGET lab2::lab2_stats APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(lab2::lab2_stats PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/lab2_stats.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/lab2_stats.dll"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_stats )
list(APPEND _cmake_import_check_files_for_lab2::lab2_stats "${_IMPORT_PREFIX}/lib/lab2_stats.lib" "${_IMPORT_PREFIX}/bin/lab2_stats.dll" )

# Import target "lab2::lab2_cli" for configuration "Debug"
set_property(TARGET lab2::lab2_cli APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(lab2::lab2_cli PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/lab2_cli.exe"
  )

list(APPEND _cmake_import_check_targets lab2::lab2_cli )
list(APPEND _cmake_import_check_files_for_lab2::lab2_cli "${_IMPORT_PREFIX}/bin/lab2_cli.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "main_comp" for configuration "RelWithDebInfo"
SET_PROPERTY(TARGET main_comp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
SET_TARGET_PROPERTIES(main_comp PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/lib/main_comp.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELWITHDEBINFO "RTC110;coil110;omniORB415_rt;omniDynamic415_rt;omnithread34_rt;advapi32;ws2_32;mswsock"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/bin/main_comp.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS main_comp )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_main_comp "${_IMPORT_PREFIX}/components/lib/main_comp.lib" "${_IMPORT_PREFIX}/components/bin/main_comp.dll" )

# Import target "main_compcomp" for configuration "RelWithDebInfo"
SET_PROPERTY(TARGET main_compcomp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
SET_TARGET_PROPERTIES(main_compcomp PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/components/bin/main_compcomp.exe"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS main_compcomp )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_main_compcomp "${_IMPORT_PREFIX}/components/bin/main_compcomp.exe" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)

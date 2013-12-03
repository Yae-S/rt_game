# Main_comp CMake config file
#
# This file sets the following variables:
# Main_comp_FOUND - Always TRUE.
# Main_comp_INCLUDE_DIRS - Directories containing the Main_comp include files.
# Main_comp_IDL_DIRS - Directories containing the Main_comp IDL files.
# Main_comp_LIBRARIES - Libraries needed to use Main_comp.
# Main_comp_DEFINITIONS - Compiler flags for Main_comp.
# Main_comp_VERSION - The version of Main_comp found.
# Main_comp_VERSION_MAJOR - The major version of Main_comp found.
# Main_comp_VERSION_MINOR - The minor version of Main_comp found.
# Main_comp_VERSION_REVISION - The revision version of Main_comp found.
# Main_comp_VERSION_CANDIDATE - The candidate version of Main_comp found.

message(STATUS "Found Main_comp-2.0.0")
set(Main_comp_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Main_comp_INCLUDE_DIRS
#    "C:/Program Files/Main_comp/include/main_comp-2"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Main_comp_IDL_DIRS
#    "C:/Program Files/Main_comp/include/main_comp-2/idl")
set(Main_comp_INCLUDE_DIRS
    "C:/Program Files/Main_comp/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Main_comp_IDL_DIRS
    "C:/Program Files/Main_comp/include//idl")


if(WIN32)
    set(Main_comp_LIBRARIES
        "C:/Program Files/Main_comp/components/lib/main_comp.lib"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Main_comp_LIBRARIES
        "C:/Program Files/Main_comp/components/lib/main_comp.dll"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Main_comp_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Main_comp_VERSION 2.0.0)
set(Main_comp_VERSION_MAJOR 2)
set(Main_comp_VERSION_MINOR 0)
set(Main_comp_VERSION_REVISION 0)
set(Main_comp_VERSION_CANDIDATE )


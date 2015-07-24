#.rst:
# FindRecast
# ------------
#
# Locate RECAST library
#
# This module defines
#
# ::
#
#   RECAST_LIBRARIES, the library to link against
#   RECAST_FOUND, the libraries needed to use RECAST
#   RECAST_INCLUDE_DIRS, where to find headers.
#

find_path(RECAST_INCLUDE_DIR
	NAMES Recast/Recast.h
	PATH_SUFFIXES include
)

find_library(RECAST_LIBRARY 
	NAMES Recast
	PATH_SUFFIXES lib
)

set(RECAST_INCLUDE_DIRS "${RECAST_INCLUDE_DIR}")
set(RECAST_LIBRARIES "${RECAST_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(RECAST DEFAULT_MSG RECAST_LIBRARIES RECAST_INCLUDE_DIRS)

mark_as_advanced(RECAST_INCLUDE_DIR RECAST_LIBRARY)

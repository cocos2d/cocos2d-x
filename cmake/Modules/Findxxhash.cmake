#.rst:
# Findxxhash
# ------------
#
# Locate xxhash library
#
# This module defines
#
# ::
#
#   XXHASH_LIBRARIES, the library to link against
#   XXHASH_FOUND, the libraries needed to use flatbuffers
#   XXHASH_INCLUDE_DIRS, where to find headers.
#

find_path(XXHASH_INCLUDE_DIR
	NAMES xxhash.h xxhash.h
	PATH_SUFFIXES include include/xxhash
)

find_library(XXHASH_LIBRARY 
	NAMES xxhash
	PATH_SUFFIXES lib
)

set(XXHASH_INCLUDE_DIRS "${XXHASH_INCLUDE_DIR}")
set(XXHASH_LIBRARIES "${XXHASH_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(XXHASH DEFAULT_MSG XXHASH_LIBRARIES XXHASH_INCLUDE_DIRS)

mark_as_advanced(XXHASH_INCLUDE_DIR XXHASH_LIBRARY)

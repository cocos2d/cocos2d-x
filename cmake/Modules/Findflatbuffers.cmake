#.rst:
# Findflatbuffers
# ------------
#
# Locate flatbuffers library
#
# This module defines
#
# ::
#
#   FLATBUFFERS_LIBRARIES, the library to link against
#   FLATBUFFERS_FOUND, the libraries needed to use flatbuffers
#   FLATBUFFERS_INCLUDE_DIRS, where to find headers.
#

find_path(FLATBUFFERS_INCLUDE_DIR
	NAMES flatbuffers.h
	PATH_SUFFIXES include include/flatbuffers
)

find_library(FLATBUFFERS_LIBRARY 
	NAMES flatbuffers
	PATH_SUFFIXES lib
)

set(FLATBUFFERS_INCLUDE_DIRS "${FLATBUFFERS_INCLUDE_DIR}")
set(FLATBUFFERS_LIBRARIES "${FLATBUFFERS_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(FLATBUFFERS DEFAULT_MSG FLATBUFFERS_LIBRARIES FLATBUFFERS_INCLUDE_DIRS)

mark_as_advanced(FLATBUFFERS_INCLUDE_DIR FLATBUFFERS_LIBRARY)

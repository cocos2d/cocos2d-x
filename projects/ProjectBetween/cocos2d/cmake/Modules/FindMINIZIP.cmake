#.rst:
# FindMINIZIP
# ------------
#
# Locate minizip library (from zlib package)
#
# This module defines
#
# ::
#
#   MINIZIP_LIBRARIES, the library to link against
#   MINIZIP_FOUND, if false, do not try to link to fmodex
#   MINIZIP_INCLUDE_DIRS, where to find headers.
#

# Try pkg-config first
if(NOT MINIZIP_LIBRARY AND NOT MINIZIP_INCLUDE_DIR)
  find_package(PkgConfig)
  pkg_search_module(MINIZIP minizip)
  if(MINIZIP_FOUND)
    return()
  endif()
endif()

find_path(MINIZIP_INCLUDE_DIR minizip/unzip.h
  HINTS ENV MINIZIP_DIR
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  )

find_library(MINIZIP_LIBRARY NAMES minizip libminizip
  HINTS ENV MINIZIP_DIR
  PATH_SUFFIXES lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  )

set(MINIZIP_INCLUDE_DIRS "${MINIZIP_INCLUDE_DIR}")
set(MINIZIP_LIBRARIES "${MINIZIP_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(MINIZIP DEFAULT_MSG MINIZIP_LIBRARIES MINIZIP_INCLUDE_DIRS)

mark_as_advanced(MINIZIP_INCLUDE_DIR MINIZIP_LIBRARY)


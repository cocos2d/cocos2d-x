#.rst:
# FindFMODEX
# ------------
#
# Locate FMOD Ex library
#
# This module defines
#
# ::
#
#   FMODEX_LIBRARIES, the library to link against
#   FMODEX_FOUND, if false, do not try to link to fmodex
#   FMODEX_INCLUDE_DIRS, where to find headers.
#

find_path(FMODEX_INCLUDE_DIR fmod.h
  HINTS ENV FMODEX_DIR
  PATH_SUFFIXES include/fmodex include
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

find_library(FMODEX_LIBRARY NAMES fmodex fmodex64
  HINTS ENV FMODEX_DIR
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

set(FMODEX_INCLUDE_DIRS "${FMODEX_INCLUDE_DIR}")
set(FMODEX_LIBRARIES "${FMODEX_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(FMODEX DEFAULT_MSG FMODEX_LIBRARIES FMODEX_INCLUDE_DIRS)

mark_as_advanced(FMODEX_INCLUDE_DIR FMODEX_LIBRARY FMODEX_INCLUDE_DIRS FMODEX_LIBRARIES)


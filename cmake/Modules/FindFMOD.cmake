#.rst:
# FindFMOD
# ------------
#
# Locate FMOD Ex library
#
# This module defines
#
# ::
#
#   FMOD_LIBRARIES, the library to link against
#   FMOD_FOUND, if false, do not try to link to fmodex
#   FMOD_INCLUDE_DIRS, where to find headers.
#

find_path(FMOD_INCLUDE_DIR fmod.hpp
  HINTS ENV FMOD_DIR
  PATH_SUFFIXES include/fmod include
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

find_library(FMOD_LIBRARY NAMES fmod fmod64
  HINTS ENV FMOD_DIR
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

set(FMOD_INCLUDE_DIRS "${FMOD_INCLUDE_DIR}")
set(FMOD_LIBRARIES "${FMOD_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(FMOD DEFAULT_MSG FMOD_LIBRARIES FMOD_INCLUDE_DIRS)

mark_as_advanced(FMOD_INCLUDE_DIR FMOD_LIBRARY FMOD_INCLUDE_DIRS FMOD_LIBRARIES)


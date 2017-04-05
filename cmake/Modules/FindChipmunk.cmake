#.rst:
# FindChipmunk
# ------------
#
# Locate Chipmunk library
#
# This module defines
#
# ::
#
#   CHIPMUNK_LIBRARIES, the library to link against
#   CHIPMUNK_FOUND, if false, do not try to link to Chipmunk 
#   CHIPMUNK_INCLUDE_DIRS, where to find headers.
#   This is the concatenation of the paths:
#   CHIPMUNK_INCLUDE_DIR
#
#=============================================================================
# Copyright 2014-2014 Martell Malone
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(CHIPMUNK_INCLUDE_DIR chipmunk/chipmunk.h
  HINTS
  ENV CHIPMUNK_DIR
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

FIND_LIBRARY(CHIPMUNK_LIBRARY
  NAMES chipmunk libchipmunk
  HINTS
  ENV CHIPMUNK_DIR
  PATH_SUFFIXES lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

set(CHIPMUNK_INCLUDE_DIRS "${CHIPMUNK_INCLUDE_DIR}")

IF(CHIPMUNK_LIBRARY)
  # include the math library for Unix
  IF(UNIX AND NOT APPLE)
    FIND_LIBRARY(CHIPMUNK_MATH_LIBRARY m)
    SET(CHIPMUNK_LIBRARIES "${CHIPMUNK_LIBRARY};${CHIPMUNK_MATH_LIBRARY}" CACHE STRING "Chipmunk Libraries")
  # For Windows and Mac, don't need to explicitly include the math library
  ELSE(UNIX AND NOT APPLE)
    SET( CHIPMUNK_LIBRARIES "${CHIPMUNK_LIBRARY}" CACHE STRING "Chipmunk Libraries")
  ENDIF(UNIX AND NOT APPLE)
ENDIF(CHIPMUNK_LIBRARY)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
# handle the QUIETLY and REQUIRED arguments and set CHIPMUNK_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Chipmunk DEFAULT_MSG CHIPMUNK_LIBRARIES CHIPMUNK_INCLUDE_DIR)

MARK_AS_ADVANCED(CHIPMUNK_INCLUDE_DIR CHIPMUNK_LIBRARIES CHIPMUNK_LIBRARY CHIPMUNK_MATH_LIBRARY)

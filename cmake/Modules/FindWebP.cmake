#.rst:
# FindWebP
# ------------
#
# Locate webp library
#
# This module defines
#
# ::
#
#   WEBP_LIBRARIES, the library to link against
#   WEBP_FOUND, if false, do not try to link to FREETYPE
#   WEBP_INCLUDE_DIRS, where to find headers.
#   This is the concatenation of the paths:
#   WEBP_INCLUDE_DIR
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

FIND_PATH(WEBP_INCLUDE_DIR decode.h
  HINTS
  ENV WEBP_DIR
  PATH_SUFFIXES include/webp include
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

FIND_LIBRARY(WEBP_LIBRARY 
  NAMES webp libwebp
  HINTS
  ENV WEBP_DIR
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

set(WEBP_INCLUDE_DIRS "${WEBP_INCLUDE_DIR}")
set(WEBP_LIBRARIES "${WEBP_LIBRARY}")

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
# handle the QUIETLY and REQUIRED arguments and set WEBP_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(WebP DEFAULT_MSG WEBP_LIBRARIES WEBP_INCLUDE_DIR)

MARK_AS_ADVANCED(WEBP_INCLUDE_DIR WEBP_LIBRARIES WEBP_LIBRARY)

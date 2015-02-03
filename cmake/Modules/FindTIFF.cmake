#.rst:
# FindTIFF
# --------
#
# Find TIFF library
#
# Find the native TIFF includes and library This module defines
#
# ::
#
#   TIFF_INCLUDE_DIR, where to find tiff.h, etc.
#   TIFF_LIBRARIES, libraries to link against to use TIFF.
#   TIFF_FOUND, If false, do not try to use TIFF.
#
# also defined, but not for general use are
#
# ::
#
#   TIFF_LIBRARY, where to find the TIFF library.

#=============================================================================
# Copyright 2002-2009 Kitware, Inc.
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

set(TIFF_NAMES ${TIFF_NAMES} tiff libtiff tiff3 libtiff3)

find_path(TIFF_INCLUDE_DIR tiff.h
    HINTS ENV TIFF_DIR
    PATH_SUFFIXES include/libtiff include
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

find_library(TIFF_LIBRARY
  NAMES ${TIFF_NAMES}
  HINTS ENV TIFF_DIR
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

if(TIFF_INCLUDE_DIR AND EXISTS "${TIFF_INCLUDE_DIR}/tiffvers.h")
    file(STRINGS "${TIFF_INCLUDE_DIR}/tiffvers.h" tiff_version_str
         REGEX "^#define[\t ]+TIFFLIB_VERSION_STR[\t ]+\"LIBTIFF, Version .*")

    string(REGEX REPLACE "^#define[\t ]+TIFFLIB_VERSION_STR[\t ]+\"LIBTIFF, Version +([^ \\n]*).*"
           "\\1" TIFF_VERSION_STRING "${tiff_version_str}")
    unset(tiff_version_str)
endif()

set(TIFF_INCLUDE_DIRS ${TIFF_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set TIFF_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TIFF
  REQUIRED_VARS TIFF_LIBRARY TIFF_INCLUDE_DIRS
  VERSION_VAR TIFF_VERSION_STRING
  )

if(TIFF_FOUND)
  set( TIFF_LIBRARIES ${TIFF_LIBRARY} )
endif()

mark_as_advanced(TIFF_INCLUDE_DIRS TIFF_LIBRARY)

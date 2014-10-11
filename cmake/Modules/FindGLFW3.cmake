#.rst:
# FindGLFW3
# ------------
#
# Locate glfw3 library
#
# This module defines
#
# ::
#
#   GLFW3_LIBRARIES, the library to link against
#   GLFW3_FOUND, if false, do not try to link to FREETYPE
#   GLFW3_INCLUDE_DIRS, where to find headers.
#   This is the concatenation of the paths:
#   GLFW3_INCLUDE_DIR
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

FIND_PATH(GLFW3_INCLUDE_DIR glfw3.h
  HINTS
  ENV GLFW3_DIR
  PATH_SUFFIXES include/GLFW include
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

FIND_LIBRARY(GLFW3_LIBRARY 
  NAMES glfw3 libglfw3 glfw
  HINTS
  ENV GLFW3_DIR
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

set(GLFW3_INCLUDE_DIRS "${GLFW3_INCLUDE_DIR}")
set(GLFW3_LIBRARIES "${GLFW3_LIBRARY}")

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
# handle the QUIETLY and REQUIRED arguments and set GLFW3_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW3 DEFAULT_MSG GLFW3_LIBRARIES GLFW3_INCLUDE_DIR)

MARK_AS_ADVANCED(GLFW3_INCLUDE_DIR GLFW3_LIBRARIES GLFW3_LIBRARY)

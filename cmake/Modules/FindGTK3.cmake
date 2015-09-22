# - Try to find GTK3
#
# $Id: FindGTK3.cmake 39970 2011-11-21 15:39:25Z jmayer $
#
# Once done this will define
#
#  GTK3_FOUND - System has GTK3
#  GTK3_INCLUDE_DIRS - The GTK3 include directory
#  GTK3_LIBRARIES - The libraries needed to use GTK3
#  GTK3_DEFINITIONS - Compiler switches required for using GTK3
#=============================================================================
# Copyright 2011 Duncan Mac-Vicar P. <duncan@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file COPYING-CMAKE-SCRIPTS for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig)
pkg_check_modules(PC_GTK3 gtk+-3.0 QUIET)

# MESSAGE(STATUS "PC_GTK3_LIBRARIES: ${PC_GTK3_LIBRARIES}")
# MESSAGE(STATUS "PC_GTK3_LIBRARY_DIRS: ${PC_GTK3_LIBRARY_DIRS}")
# MESSAGE(STATUS "PC_GTK3_LDFLAGS: ${PC_GTK3_LDFLAGS}")
# MESSAGE(STATUS "PC_GTK3_LDFLAGS_OTHER: ${PC_GTK3_LDFLAGS_OTHER}")

set(GTK3_DEFINITIONS ${PC_GTK3_CFLAGS_OTHER})

#FIND_PATH(GTK3_INCLUDE_DIR NAMES "gtk/gtk.h"
#   HINTS
#   ${PC_GTK3_INCLUDEDIR}
#   ${PC_GTK3_INCLUDE_DIRS}
#   PATH_SUFFIXES "gtk-3.0"
#   )
set(GTK3_INCLUDE_DIRS ${PC_GTK3_INCLUDE_DIRS})

#FIND_LIBRARY(GTK3_LIBRARIES NAMES gtk-3 gtk3
#   HINTS
#   ${PC_GTK3_LIBDIR}
#   ${PC_GTK3_LIBRARY_DIRS}
#   )
set(GTK3_LIBRARIES ${PC_GTK3_LIBRARIES})

# handle the QUIETLY and REQUIRED arguments and set GTK3_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GTK3 DEFAULT_MSG GTK3_LIBRARIES GTK3_INCLUDE_DIRS)

mark_as_advanced(GTK3_INCLUDE_DIRS GTK3_LIBRARIES)

#.rst:
# FindZLIB
# --------
#
# Find zlib
#
# Find the native ZLIB includes and library.  Once done this will define
#
# ::
#
#   ZLIB_INCLUDE_DIRS   - where to find zlib.h, etc.
#   ZLIB_LIBRARIES      - List of libraries when using zlib.
#   ZLIB_FOUND          - True if zlib found.
#
#
#
# ::
#
#   ZLIB_VERSION_STRING - The version of zlib found (x.y.z)
#   ZLIB_VERSION_MAJOR  - The major version of zlib
#   ZLIB_VERSION_MINOR  - The minor version of zlib
#   ZLIB_VERSION_PATCH  - The patch version of zlib
#   ZLIB_VERSION_TWEAK  - The tweak version of zlib
#
#
#
# The following variable are provided for backward compatibility
#
# ::
#
#   ZLIB_MAJOR_VERSION  - The major version of zlib
#   ZLIB_MINOR_VERSION  - The minor version of zlib
#   ZLIB_PATCH_VERSION  - The patch version of zlib
#
#
#
# An includer may set ZLIB_ROOT to a zlib installation root to tell this
# module where to look.

#=============================================================================
# Copyright 2001-2011 Kitware, Inc.
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

set(ZLIB_NAMES z zlib zdll zlib1 zlibd zlibd1)

if(USE_PREBUILT_LIBS)
  set(search PATHS ${COCOS_EXTERNAL_DIR}/zlib ${COCOS_EXTERNAL_DIR}/${ARCH_DIR}-specific/zlib NO_DEFAULT_PATH)
  find_path(ZLIB_INCLUDE_DIR NAMES zlib.h        ${search} PATH_SUFFIXES include/${PLATFORM_FOLDER} include)
  find_library(ZLIB_LIBRARY  NAMES ${ZLIB_NAMES} ${search}
    PATH_SUFFIXES
      prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
      prebuilt/${PLATFORM_FOLDER}
      prebuilt
    )
  # cleanup if not found (prevent from mix prebuilt include paths and system installed libraries)
  if(NOT ZLIB_INCLUDE_DIR OR NOT ZLIB_LIBRARY)
    unset(ZLIB_INCLUDE_DIR CACHE)
    unset(ZLIB_LIBRARY CACHE)
  endif()
endif()

set(_ZLIB_SEARCHES)

# Search ZLIB_ROOT first if it is set.
if(ZLIB_ROOT)
  set(_ZLIB_SEARCH_ROOT PATHS ${ZLIB_ROOT} NO_DEFAULT_PATH)
  list(APPEND _ZLIB_SEARCHES _ZLIB_SEARCH_ROOT)
endif()

# Normal search.
set(_ZLIB_SEARCH_NORMAL
  PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
        "$ENV{PROGRAMFILES}/zlib"
  )
list(APPEND _ZLIB_SEARCHES _ZLIB_SEARCH_NORMAL)

# Try each search configuration.
foreach(search ${_ZLIB_SEARCHES})
  find_path(ZLIB_INCLUDE_DIR NAMES zlib.h        ${${search}} PATH_SUFFIXES include)
  find_library(ZLIB_LIBRARY  NAMES ${ZLIB_NAMES} ${${search}} PATH_SUFFIXES lib)
endforeach()

mark_as_advanced(ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

if(ZLIB_INCLUDE_DIR AND EXISTS "${ZLIB_INCLUDE_DIR}/zlib.h")
    file(STRINGS "${ZLIB_INCLUDE_DIR}/zlib.h" ZLIB_H REGEX "^#define ZLIB_VERSION \"[^\"]*\"$")

    string(REGEX REPLACE "^.*ZLIB_VERSION \"([0-9]+).*$" "\\1" ZLIB_VERSION_MAJOR "${ZLIB_H}")
    string(REGEX REPLACE "^.*ZLIB_VERSION \"[0-9]+\\.([0-9]+).*$" "\\1" ZLIB_VERSION_MINOR  "${ZLIB_H}")
    string(REGEX REPLACE "^.*ZLIB_VERSION \"[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" ZLIB_VERSION_PATCH "${ZLIB_H}")
    set(ZLIB_VERSION_STRING "${ZLIB_VERSION_MAJOR}.${ZLIB_VERSION_MINOR}.${ZLIB_VERSION_PATCH}")

    # only append a TWEAK version if it exists:
    set(ZLIB_VERSION_TWEAK "")
    if( "${ZLIB_H}" MATCHES "^.*ZLIB_VERSION \"[0-9]+\\.[0-9]+\\.[0-9]+\\.([0-9]+).*$")
        set(ZLIB_VERSION_TWEAK "${CMAKE_MATCH_1}")
        set(ZLIB_VERSION_STRING "${ZLIB_VERSION_STRING}.${ZLIB_VERSION_TWEAK}")
    endif()

    set(ZLIB_MAJOR_VERSION "${ZLIB_VERSION_MAJOR}")
    set(ZLIB_MINOR_VERSION "${ZLIB_VERSION_MINOR}")
    set(ZLIB_PATCH_VERSION "${ZLIB_VERSION_PATCH}")
endif()

# handle the QUIETLY and REQUIRED arguments and set ZLIB_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ZLIB REQUIRED_VARS ZLIB_LIBRARY ZLIB_INCLUDE_DIR
                                       VERSION_VAR ZLIB_VERSION_STRING)

if(ZLIB_FOUND)
    set(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIR})
    set(ZLIB_LIBRARIES ${ZLIB_LIBRARY})
endif()


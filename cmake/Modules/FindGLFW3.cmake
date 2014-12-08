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

# glfw has special requirements for linking (from docs: http://www.glfw.org/docs/latest/build.html)
# MINGW or MSVC + static "glfw3" -> link: opengl32, gdi32 (plus glu32 if use GLU)
# MINGW or MSVC + dynamic "glfw3dll" (but this not true ;) -> -DGLFW_DLL link: no
# UNIX + static -> pkg-config --static --libs
# UNIX + dynamic -> pkg-config --libs
# So... if we find dynamic version, no problems, but if we find static, we need to determine deps
#  but cmake can't simply say to us what kind of library it found. So we try to find static version
#  first, and then if nothing found, we repeat search for dynamic

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
  message(STATUS "PkgConfig found")
else()
  message(STATUS "PkgConfig not found, if you have only static glfw library, you build can fail")
endif()

if(PKG_CONFIG_FOUND)
  # Save some global stuff that we change, to revert after work has been done
  set(_saved_PKG_CONFIG_PATH "$ENV{PKG_CONFIG_PATH}")
  set(_saved_CMAKE_FIND_LIBRARY_SUFFIXES "${CMAKE_FIND_LIBRARY_SUFFIXES}")

  # add /usr/local/lib/pkgconfig to pkg-config search path (some linuxes do not do that, but glfw installs to taht prefix by default)
  file(TO_CMAKE_PATH "$ENV{PKG_CONFIG_PATH}" PKG_CONFIG_PATH)
  list(APPEND PKG_CONFIG_PATH "/usr/local/lib/pkgconfig")
  file(TO_NATIVE_PATH "${PKG_CONFIG_PATH}" new_pkg_config_path)
  set(ENV{PKG_CONFIG_PATH} "${new_pkg_config_path}")

  # now try to find glfw with pkg-config
  pkg_check_modules(PC_GLFW3 glfw3)
  if(PC_GLFW3_FOUND)

    # try to find static library
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX})
    find_library(GLFW3_STATIC_LIBRARY NAMES glfw3 libglfw3 PATHS ${PC_GLFW3_LIBRARY_DIRS} NO_DEFAULT_PATH)
    find_library(GLFW3_STATIC_LIBRARY NAMES glfw3 libglfw3 PATHS ${PC_GLFW3_LIBRARY_DIRS})
    # also we include glfw3.h header, not GLFW/glfw3.h :(
    find_path(GLFW3_INCLUDE_DIRS glfw3.h PATH_SUFFIXES GLFW PATHS ${PC_GLFW3_INCLUDE_DIRS} NO_DEFAULT_PATH)
    find_path(GLFW3_INCLUDE_DIRS glfw3.h PATH_SUFFIXES GLFW PATHS ${PC_GLFW3_INCLUDE_DIRS})

    if(GLFW3_STATIC_LIBRARY)
      # glfw3 is static
      set(GLFW3_LIBRARIES ${PC_GLFW3_STATIC_LIBRARIES})
      set(GLFW3_LIBRARY_DIRS ${PC_GLFW3_STATIC_LIBRARY_DIRS})

      # We also need to add any other LDFLAGS, but with additional fixup for Apple frameworks :(
      if(APPLE)
        unset(_is_framework)
        foreach(_arg ${PC_GLFW3_STATIC_LDFLAGS_OTHER})
          if(_is_framework)
            set(var FRAMEWORK_${_arg}_LIBRARY)
            find_library(${var} ${_arg})
            if(${var})
              list(APPEND GLFW3_LIBRARIES ${${var}})
            endif()
            unset(var)
            unset(_is_framework)
          else()
            if(_arg STREQUAL "-framework")
              set(_is_framework 1)
            else()
              list(APPEND GLFW3_LIBRARIES ${_arg})
            endif()
          endif()
        endforeach()
      else(APPLE)
        list(APPEND GLFW3_LIBRARIES ${PC_GLFW3_STATIC_LDFLAGS_OTHER})
      endif(APPLE)

    else()
      # glfw3 is dynamic
      set(GLFW3_DEFINITIONS -DGLFW_DLL)
      set(GLFW3_LIBRARIES ${PC_GLFW3_LIBRARIES})
      set(GLFW3_LIBRARY_DIRS ${PC_GLFW3_LIBRARY_DIRS})

    endif()
    set(GLFW3_FOUND 1)
    
  endif()

  # Restore global stuff
  set(CMAKE_FIND_LIBRARY_SUFFIXES "${_saved_CMAKE_FIND_LIBRARY_SUFFIXES}")
  set(ENV{PKG_CONFIG_PATH} "${_saved_PKG_CONFIG_PATH}")
endif(PKG_CONFIG_FOUND)

# fallback if pkg-config method not work
if(NOT GLFW3_FOUND)

  find_path(GLFW3_INCLUDE_DIR glfw3.h
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

  find_library(GLFW3_LIBRARY 
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

  include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
  find_package_handle_standard_args(GLFW3 DEFAULT_MSG GLFW3_LIBRARIES GLFW3_INCLUDE_DIR)

endif()

mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARIES GLFW3_LIBRARY)

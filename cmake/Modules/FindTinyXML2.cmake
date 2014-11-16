#.rst:
# FindTinyXML2
# ------------
#
# Locate tinyxml2 library
#
# This module defines
#
# ::
#
#   TINYXML2_LIBRARIES, the library to link against
#   TINYXML2_FOUND, if false, do not try to link to tinyxml2
#   TINYXML2_INCLUDE_DIRS, where to find headers.
#

# Try find tinyxml for our arch in external folder
if(USE_PREBUILT_LIBS)
  find_path(TinyXML2_INCLUDE_DIR tinyxml2.h
    PATH_SUFFIXES
      include/tinyxml2
      include
    PATHS ${COCOS_EXTERNAL_DIR}/tinyxml2
    NO_DEFAULT_PATH
    )
  find_library(TinyXML2_LIBRARY NAMES tinyxml2 libtinyxml2
    PATH_SUFFIXES
      prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
      prebuilt/${PLATFORM_FOLDER}
    PATHS ${COCOS_EXTERNAL_DIR}/tinyxml2
    NO_DEFAULT_PATH
    )
  # cleanup if not found (prevent from mix prebuilt include paths and system installed libraries)
  if(NOT TinyXML2_INCLUDE_DIR OR NOT TinyXML2_LIBRARY)
    unset(TinyXML2_INCLUDE_DIR CACHE)
    unset(TinyXML2_LIBRARY CACHE)
  endif()
endif(USE_PREBUILT_LIBS)

find_path(TinyXML2_INCLUDE_DIR tinyxml2.h
  HINTS ENV TinyXML2_DIR
  PATH_SUFFIXES include/tinyxml2 include
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

find_library(TinyXML2_LIBRARY 
  NAMES tinyxml2 libtinyxml2
  HINTS ENV TinyXML2_DIR
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

set(TinyXML2_INCLUDE_DIRS "${TinyXML2_INCLUDE_DIR}")
set(TinyXML2_LIBRARIES "${TinyXML2_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(TinyXML2 DEFAULT_MSG TinyXML2_LIBRARIES TinyXML2_INCLUDE_DIRS)

mark_as_advanced(TinyXML2_INCLUDE_DIRS TinyXML2_LIBRARIES TinyXML2_LIBRARY)

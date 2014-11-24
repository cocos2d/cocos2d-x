#.rst:
# FindWEBSOCKETS
# --------
#
# Find websockets library
#
# ::
#
#   WEBSOCKETS_INCLUDE_DIRS, where to find libwebsockets.h.
#   WEBSOCKETS_LIBRARIES, the libraries needed to use WEBSOCKETS.
#   WEBSOCKETS_FOUND, If false, do not try to use WEBSOCKETS.
#

if(USE_PREBUILT_LIBS)
  find_path(WEBSOCKETS_INCLUDE_DIR libwebsockets.h
    PATH_SUFFIXES include/${PLATFORM_FOLDER} include
    PATHS ${COCOS_EXTERNAL_DIR}/websockets
    NO_DEFAULT_PATH
    )
  find_library(WEBSOCKETS_LIBRARY NAMES websockets libwebsockets
    PATH_SUFFIXES
      prebuilt/${PLATFORM_FOLDER}/${ARCH_DIR}
      prebuilt/${PLATFORM_FOLDER}
    PATHS ${COCOS_EXTERNAL_DIR}/websockets
    NO_DEFAULT_PATH
    )
  # cleanup if not found (prevent from mix prebuilt include paths and system installed libraries)
  if(NOT WEBSOCKETS_INCLUDE_DIR OR NOT WEBSOCKETS_LIBRARY)
    unset(WEBSOCKETS_INCLUDE_DIR CACHE)
    unset(WEBSOCKETS_LIBRARY CACHE)
  endif()
endif()

find_path(WEBSOCKETS_INCLUDE_DIR libwebsockets.h
  HINTS ENV WEBSOCKETS_DIR
  PATH_SUFFIXES include/websockets include/libwebsockets include
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

find_library(WEBSOCKETS_LIBRARY NAMES websockets libwebsockets
  HINTS ENV WEBSOCKETS_DIR
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

set(WEBSOCKETS_INCLUDE_DIRS ${WEBSOCKETS_INCLUDE_DIR})
set(WEBSOCKETS_LIBRARIES ${WEBSOCKETS_LIBRARY})

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(WEBSOCKETS DEFAULT_MSG WEBSOCKETS_LIBRARIES WEBSOCKETS_INCLUDE_DIRS)

mark_as_advanced(WEBSOCKETS_LIBRARIES WEBSOCKETS_INCLUDE_DIRS)

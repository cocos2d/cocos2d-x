include(CMakeParseArguments)

macro(pre_build TARGET_NAME)
  add_custom_target( ${TARGET_NAME}_PRE_BUILD ALL )

  add_custom_command(
    TARGET ${TARGET_NAME}_PRE_BUILD
    ${ARGN}
    PRE_BUILD
    COMMENT "${TARGET_NAME}_PRE_BUILD ..."
    )

  add_custom_target(${TARGET_NAME}_CORE_PRE_BUILD)
  add_dependencies(${TARGET_NAME}_PRE_BUILD ${TARGET_NAME}_CORE_PRE_BUILD)
  add_dependencies(${TARGET_NAME} ${TARGET_NAME}_PRE_BUILD)
endmacro()

function(cocos_mark_resources)
    set(oneValueArgs BASEDIR RESOURCEBASE)
    set(multiValueArgs FILES)
    cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT opt_RESOURCEBASE)
        set(opt_RESOURCEBASE Resources)
    endif()

    get_filename_component(BASEDIR_ABS ${opt_BASEDIR} ABSOLUTE)
    foreach(RES_FILE ${opt_FILES} ${opt_UNPARSED_ARGUMENTS})
        get_filename_component(RES_FILE_ABS ${RES_FILE} ABSOLUTE)
        file(RELATIVE_PATH RES ${BASEDIR_ABS} ${RES_FILE_ABS})
        get_filename_component(RES_LOC ${RES} PATH)
        set_source_files_properties(${RES_FILE} PROPERTIES
            MACOSX_PACKAGE_LOCATION "${opt_RESOURCEBASE}/${RES_LOC}"
            HEADER_FILE_ONLY 1
            )
    endforeach()
endfunction()

# cocos_find_package(pkg args...)
# works same as find_package, but do additional care to properly find
# prebuilt libs for cocos
macro(cocos_find_package pkg_name pkg_prefix)
  if(NOT USE_PREBUILT_LIBS OR NOT ${pkg_prefix}_FOUND)
    find_package(${pkg_name} ${ARGN})
  endif()
  if(NOT ${pkg_prefix}_INCLUDE_DIRS AND ${pkg_prefix}_INCLUDE_DIR)
    set(${pkg_prefix}_INCLUDE_DIRS ${${pkg_prefix}_INCLUDE_DIR})
  endif()
  if(NOT ${pkg_prefix}_LIBRARIES AND ${pkg_prefix}_LIBRARY)
    set(${pkg_prefix}_LIBRARIES ${${pkg_prefix}_LIBRARY})
  endif()

  message(STATUS "${pkg_name} include dirs: ${${pkg_prefix}_INCLUDE_DIRS}")
endmacro()

# cocos_use_pkg(pkg) function.
# This function applies standard package variables (after find_package(pkg) call) to current scope
# Recognized variables: <pkg>_INCLUDE_DIRS, <pkg>_LIBRARIES, <pkg>_LIBRARY_DIRS
# Also if BUILD_SHARED_LIBS variable off, it is try to use <pkg>_STATIC_* vars before
function(cocos_use_pkg target pkg)
  set(prefix ${pkg})
  
  set(_include_dirs)
  if(NOT _include_dirs)
    set(_include_dirs ${${prefix}_INCLUDE_DIRS})
  endif()
  if(NOT _include_dirs)
    # backward compat with old package-find scripts
    set(_include_dirs ${${prefix}_INCLUDE_DIR})
  endif()
  if(_include_dirs)
    include_directories(${_include_dirs})
    message(STATUS "${pkg} add to include_dirs: ${_include_dirs}")
  endif()
  
  set(_library_dirs)
  if(NOT _library_dirs)
    set(_library_dirs ${${prefix}_LIBRARY_DIRS})
  endif()
  if(_library_dirs)
    link_directories(${_library_dirs})
    message(STATUS "${pkg} add to link_dirs: ${_library_dirs}")
  endif()
  
  set(_libs)
  if(NOT _libs)
    set(_libs ${${prefix}_LIBRARIES})
  endif()
  if(NOT _libs)
    set(_libs ${${prefix}_LIBRARY})
  endif()
  if(_libs)
    target_link_libraries(${target} ${_libs})
    message(STATUS "${pkg} libs added to '${target}': ${_libs}")
  endif()
  
  set(_defs)
  if(NOT _defs)
    set(_defs ${${prefix}_DEFINITIONS})
  endif()
  if(_defs)
    add_definitions(${_defs})
    message(STATUS "${pkg} add definitions: ${_defs}")
  endif()
endfunction()

#cmake has some strange defaults, this should help us a lot
#Please use them everywhere

#WINDOWS 	= 	Windows Desktop
#WINRT 		= 	Windows RT
#WP8 	  	= 	Windows Phone 8
#ANDROID    =	Android
#IOS		=	iOS
#MACOSX		=	MacOS X
#LINUX      =   Linux

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  if(WINRT)
    set(SYSTEM_STRING "Windows RT")
  elseif(WP8)
    set(SYSTEM_STRING "Windows Phone 8")
  else()
    set(WINDOWS TRUE)
    set(SYSTEM_STRING "Windows Desktop")
  endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  if(ANDROID)
    set(SYSTEM_STRING "Android")
  else()
    set(LINUX TRUE)
    set(SYSTEM_STRING "Linux")
  endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if(IOS)
    set(SYSTEM_STRING "IOS")
  else()
    set(MACOSX TRUE)
    set(APPLE TRUE)
    set(SYSTEM_STRING "Mac OSX")
  endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(COMPILER_STRING ${CMAKE_CXX_COMPILER_ID})
  set(CLANG TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(MINGW)
    set(COMPILER_STRING "Mingw GCC")
  else()
    set(COMPILER_STRING "GCC")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  set(COMPILER_STRING "${CMAKE_CXX_COMPILER_ID} C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(COMPILER_STRING "Visual Studio C++")
endif()

if(CMAKE_CROSSCOMPILING)
  set(BUILDING_STRING "It appears you are cross compiling for ${SYSTEM_STRING} with ${COMPILER_STRING}")
else()
  set(BUILDING_STRING "It appears you are builing natively for ${SYSTEM_STRING} with ${COMPILER_STRING}")
endif()

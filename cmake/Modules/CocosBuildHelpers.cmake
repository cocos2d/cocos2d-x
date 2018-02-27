include(CMakeParseArguments)

# copy libs to static libs folder
# error function, have bug
function(cocos_put_static_libs lib_target lib_dir)
  add_custom_command(TARGET ${lib_target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${lib_dir}/lib${lib_target}.a ${COCOS_PREBUILT_LIBS_PATH}/lib${lib_target}.a
    COMMENT "${TARGET_NAME} POST_BUILD ..."
    )
endfunction()

# lib_name eg cocos2d/cocos2djs
macro(cocos_find_static_libs lib_name)
  # only search COCOS_PREBUILT_LIBS_PATH
  MESSAGE( STATUS "cocos static library path: ${COCOS_PREBUILT_LIBS_PATH}")
  FIND_LIBRARY(LIB_FOUND ${lib_name} PATHS ${COCOS_PREBUILT_LIBS_PATH} DOC "using cocos static library: lib${lib_name}.a" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
  # set flag
  if(${LIB_FOUND} STREQUAL LIB_FOUND-NOTFOUND)
    set(FIND_COCOS_STATIC_LIBS OFF)
  else()
    set(FIND_COCOS_STATIC_LIBS ON)
    MESSAGE( STATUS "using cocos static library: ${LIB_FOUND}")
  endif()
endmacro()

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

        if(XCODE OR VS)
            string(REPLACE "/" "\\" ide_source_group "${opt_RESOURCEBASE}/${RES_LOC}")
            source_group("${ide_source_group}" FILES ${RES_FILE})
        endif()
    endforeach()
endfunction()

# mark the files in the sub dir of CMAKE_CURRENT_SOURCE_DIR
function(cocos_mark_code_files cocos_target)
  set(oneValueArgs GROUPBASE)
  cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  if(NOT opt_GROUPBASE)
    set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
  else()
    set(root_dir ${opt_GROUPBASE})
    message(STATUS "target ${cocos_target} code group base is: ${root_dir}")
  endif()

  message(STATUS "cocos_mark_code_files: ${cocos_target}")
  set(group_base "Source Files")

  get_property(file_list TARGET ${cocos_target} PROPERTY SOURCES)

  foreach(single_file ${file_list})
    # get relative_path
    get_filename_component(abs_path ${single_file} ABSOLUTE)
    file(RELATIVE_PATH relative_path_with_name ${root_dir} ${abs_path})
    get_filename_component(relative_path ${relative_path_with_name} PATH)
    # set source_group, consider sub source group 
    string(REPLACE "/" "\\" ide_file_group "${group_base}/${relative_path}")
    source_group("${ide_file_group}" FILES ${single_file})

  endforeach()
  
endfunction()

# if cc_variable not set, then set it cc_value
macro(cocos_fake_set cc_variable cc_value)
  if(NOT DEFINED ${cc_variable})
    set(${cc_variable} ${cc_value})
  endif()
endmacro()

# macos package, need review
macro(cocos_pak_xcode cocos_target)
  set(oneValueArgs
    INFO_PLIST 
    BUNDLE_NAME
    BUNDLE_VERSION
    COPYRIGHT
    GUI_IDENTIFIER
    ICON_FILE
    INFO_STRING
    LONG_VERSION_STRING
    SHORT_VERSION_STRING
  )
  set(multiValueArgs)
  cmake_parse_arguments(COCOS_APP "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  # set default value
  cocos_fake_set(COCOS_APP_INFO_PLIST "MacOSXBundleInfo.plist.in")
  cocos_fake_set(COCOS_APP_BUNDLE_NAME "\${PRODUCT_NAME}")
  cocos_fake_set(COCOS_APP_BUNDLE_VERSION "1")
  cocos_fake_set(COCOS_APP_COPYRIGHT "Copyright © 2018. All rights reserved.")
  cocos_fake_set(COCOS_APP_GUI_IDENTIFIER "org.cocos2dx.${APP_NAME}")
  cocos_fake_set(COCOS_APP_ICON_FILE "Icon")
  cocos_fake_set(COCOS_APP_INFO_STRING "cocos2d-x app")
  cocos_fake_set(COCOS_APP_LONG_VERSION_STRING "1.0.0")
  cocos_fake_set(COCOS_APP_SHORT_VERSION_STRING "1.0")
  # set bundle info
  set_target_properties(${cocos_target}
    PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${COCOS_APP_INFO_PLIST}
  )
  set(MACOSX_BUNDLE_BUNDLE_NAME ${COCOS_APP_BUNDLE_NAME})
  set(MACOSX_BUNDLE_BUNDLE_VERSION ${COCOS_APP_BUNDLE_VERSION})
  set(MACOSX_BUNDLE_COPYRIGHT ${COCOS_APP_COPYRIGHT})
  set(MACOSX_BUNDLE_GUI_IDENTIFIER ${COCOS_APP_GUI_IDENTIFIER})
  set(MACOSX_BUNDLE_ICON_FILE ${COCOS_APP_ICON_FILE})
  set(MACOSX_BUNDLE_INFO_STRING ${COCOS_APP_INFO_STRING})
  set(MACOSX_BUNDLE_LONG_VERSION_STRING ${COCOS_APP_LONG_VERSION_STRING})
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${COCOS_APP_SHORT_VERSION_STRING})

  message("cocos package: ${cocos_target}, plist file: ${COCOS_APP_INFO_PLIST}")
endmacro()


# This little macro lets you set any XCode specific property, from ios.toolchain.cmake
macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
	set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
endmacro (set_xcode_property)

# cocos_find_package(pkg args...)
# works same as find_package, but do additional care to properly find
# prebuilt libs for cocos
# need review
macro(cocos_find_package pkg_name pkg_prefix)
  if(NOT USE_EXTERNAL_PREBUILT_LIBS OR NOT ${pkg_prefix}_FOUND)
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


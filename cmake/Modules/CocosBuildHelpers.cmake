include(CMakeParseArguments)

# lib_name eg cocos2d/cocos2djs
function(cocos_find_prebuilt lib_target lib_ret)
  # only search COCOS_PREBUILT_PATH
  set(search_path ${COCOS_PREBUILT_PATH})
  if(XCODE OR VS)
    set(search_path ${COCOS_PREBUILT_PATH}/${CMAKE_BUILD_TYPE})
  endif()
  message(STATUS "search_path cocos prebuilt library: ${search_path}")
  find_library(tmp_lib ${lib_target} PATHS ${search_path} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
  # set flag
  if(tmp_lib)
    message(STATUS "find cocos prebuilt library: ${tmp_lib}")
  else()
    message(STATUS "can't find cocos prebuilt library: ${lib_target}")
  endif()
  set(${lib_ret} ${tmp_lib} PARENT_SCOPE)
  unset(tmp_lib CACHE)
endfunction()

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

# copy res before target build
function(cocos_copy_target_res cocos_target)
  set(oneValueArgs COPY_TO)
  set(multiValueArgs FILES FOLDERS)
  cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    # copy files
  foreach(cc_file ${opt_FILES})
    get_filename_component(file_name ${cc_file} NAME)
    add_custom_command(TARGET ${cocos_target} PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${cc_file}
      "${opt_COPY_TO}/${file_name}"
    )
  endforeach()
  # copy folders
  foreach(cc_folder ${opt_FOLDERS})
    add_custom_command(TARGET ${cocos_target} PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${cc_folder} 
      ${opt_COPY_TO}
    )
  endforeach()
endfunction()

# FILES: files in one dir, not include sub-dir
# FOLDERS: folders need to mark
# RES_TO: pak res to source group of IDE
# res_return: all res files mraked
function(cocos_mark_multi_resources res_return)
  set(oneValueArgs RES_TO)
  set(multiValueArgs FILES FOLDERS)
  cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(tmp_files_ret)
  foreach(cc_file ${opt_FILES})
    get_filename_component(file_dir ${cc_file} DIRECTORY)
    cocos_mark_resources(FILES ${cc_file} BASEDIR ${file_dir} RESOURCEBASE ${opt_RES_TO})
  endforeach()
  list(APPEND tmp_files_ret ${opt_FILES})

  foreach(cc_folder ${opt_FOLDERS})
    file(GLOB_RECURSE folder_files "${cc_folder}/*")
    list(APPEND tmp_files_ret ${folder_files})
    cocos_mark_resources(FILES ${folder_files} BASEDIR ${cc_folder} RESOURCEBASE ${opt_RES_TO})
  endforeach()
  set(${res_return} ${tmp_files_ret} PARENT_SCOPE)
endfunction()

# out var all_depend_dlls_var
function(get_target_depends_ext_dlls cocos_target all_depend_dlls_var)
  set(all_depend_ext_dlls)
  set(targets_prepare_search ${cocos_target})
  # targets_prepare_search, target need find ext libs
  set(have_searched_targets)
  set(need_search_targets)
  while(true)
    foreach(tmp_target ${targets_prepare_search})
      get_target_property(tmp_depend_libs ${tmp_target} LINK_LIBRARIES)
      list(REMOVE_ITEM targets_prepare_search ${tmp_target})
      # target itself use_cocos_pkg
      list(APPEND tmp_depend_libs ${tmp_target})
      foreach(depend_lib ${tmp_depend_libs})
        if(TARGET ${depend_lib})
          get_target_property(tmp_dlls ${depend_lib} DEPEND_DLLS)
          if(tmp_dlls)
            list(APPEND all_depend_ext_dlls ${tmp_dlls})
          endif()
          if(NOT (depend_lib STREQUAL tmp_target))
            list(APPEND targets_prepare_search ${depend_lib})
          endif()
        endif()
      endforeach()
    endforeach()
    list(LENGTH targets_prepare_search targets_prepare_search_size)
    if(targets_prepare_search_size LESS 1)
      break()
    endif()
  endwhile(true)
  
  set(${all_depend_dlls_var} ${all_depend_ext_dlls} PARENT_SCOPE)
endfunction()

# cocos_target: the target app that needed dlls
# COPY_TO: destination dir
function(cocos_copy_target_dll cocos_target)
  set(oneValueArgs COPY_TO)
  cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  get_target_depends_ext_dlls(${cocos_target} all_depend_dlls)
  # remove repeat items
  list(REMOVE_DUPLICATES all_depend_dlls)
  message(STATUS "prepare to copy external dlls for ${cocos_target}:${all_depend_dlls}")
  foreach(single_target_dll ${all_depend_dlls} )
      add_custom_command(TARGET ${cocos_target} PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${all_depend_dlls}
      ${opt_COPY_TO}
    )
  endforeach(single_target_dll)
endfunction()

# find dlls in a dir of LIB_ABS_PATH located, and save the dlls into out_put_dlls
function(cocos_find_dlls_for_lib out_put_dlls)
  set(oneValueArgs LIB_ABS_PATH)
  cmake_parse_arguments(opt "" "${oneValueArgs}"  "${multiValueArgs}" ${ARGN})
  get_filename_component(lib_dir ${opt_LIB_ABS_PATH} DIRECTORY)
  file(GLOB lib_dir_files "${lib_dir}/*")
  set(cc_dlls)
  foreach(dir_file ${lib_dir_files})
    if(${dir_file} MATCHES "dll$")
      list(APPEND cc_dlls ${dir_file})
    endif()
  endforeach()
  set(${out_put_dlls} ${cc_dlls} PARENT_SCOPE)
endfunction()

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

# APP_SRC app needed all src files
# DEPEND_COMMON_LIBS the app needed libs for all platforms
# DEPEND_ANDROID_LIBS the app needed libs only for android platform
macro(cocos_mark_app app_name)
  set(multiValueArgs APP_SRC DEPEND_COMMON_LIBS DEPEND_ANDROID_LIBS COMMON_USE_PKGS LINUX_USE_PKGS)
  cmake_parse_arguments(opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
   
  if(ANDROID)
    add_library(${app_name} SHARED ${opt_APP_SRC})
    foreach(android_lib ${opt_DEPEND_ANDROID_LIBS})
      if(USE_COCOS_PREBUILT)
        target_link_libraries(${app_name} -Wl,-whole-archive "${${_${android_lib}_prefix}_LIBRARIES}" -Wl,-no-whole-archive)
      else()
        target_link_libraries(${app_name} -Wl,-whole-archive ${android_lib} -Wl,-no-whole-archive)
        add_dependencies(${app_name} ${android_lib})
      endif()
    endforeach()
  else()
    add_executable(${app_name} ${opt_APP_SRC})
  endif()
  # set target PROPERTIES, depend different platforms
  if(APPLE)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")
    set_target_properties(${app_name} PROPERTIES MACOSX_BUNDLE 1
    )
  elseif(MSVC)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/$<CONFIG>")
    set(APP_RES_DIR "${APP_BIN_DIR}")
    #Visual Studio Defaults to wrong type
    set_target_properties(${app_name} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
  else(LINUX)
    set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${APP_NAME}")
    set(APP_RES_DIR "${APP_BIN_DIR}/Resources")
  endif()
  set_target_properties(${app_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")
  # link commom libs
  if(USE_COCOS_PREBUILT)
    foreach(common_lib ${opt_DEPEND_COMMON_LIBS})
      message(STATUS "${app_name} prepare to link engine lib: ${common_lib}")
      cocos_use_pkg(${app_name} ${_${common_lib}_prefix})
    endforeach()

    include(CocosUseLibs)
    target_use_cocos2d_depend_libs(${app_name})
  else()
    foreach(common_lib ${opt_DEPEND_COMMON_LIBS})
      target_link_libraries(${app_name} ${common_lib})
      add_dependencies(${app_name} ${common_lib})
    endforeach()
  endif()
  
  if(LINUX)
    foreach(_pkg ${opt_LINUX_USE_PKGS})
      cocos_use_pkg(${app_name} ${_pkg})
    endforeach()
  endif()
  foreach(_pkg ${opt_COMMON_USE_PKGS})
      cocos_use_pkg(${app_name} ${_pkg})
  endforeach()
  # auto mark code files for IDE when mark app
  if(XCODE OR VS)
    cocos_mark_code_files(${APP_NAME})
  endif()
endmacro()

# if cc_variable not set, then set it cc_value
macro(cocos_fake_set cc_variable cc_value)
  if(NOT DEFINED ${cc_variable})
    set(${cc_variable} ${cc_value})
  endif()
endmacro()

# macos package, need review, might improve plist, not use template?
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
macro(cocos_find_package pkg_name pkg_prefix)
  if(NOT USE_EXTERNAL_PREBUILT OR NOT ${pkg_prefix}_FOUND)
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
    # message(STATUS "${pkg} add to include_dirs: ${_include_dirs}")
  endif()
  
  set(_library_dirs)
  if(NOT _library_dirs)
    set(_library_dirs ${${prefix}_LIBRARY_DIRS})
  endif()
  if(_library_dirs)
    link_directories(${_library_dirs})
    # message(STATUS "${pkg} add to link_dirs: ${_library_dirs}")
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
    # message(STATUS "${pkg} libs added to '${target}': ${_libs}")
  endif()
  
  set(_defs)
  if(NOT _defs)
    set(_defs ${${prefix}_DEFINITIONS})
  endif()
  if(_defs)
    add_definitions(${_defs})
    # message(STATUS "${pkg} add definitions: ${_defs}")
  endif()

  set(_dlls)
  if(NOT _dlls)
    set(_dlls ${${prefix}_DLLS})
  endif()
  if(_dlls)
    if(MSVC)
        # message(STATUS "${target} add dll: ${_dlls}")
        get_property(pre_dlls
          TARGET  ${target}
          PROPERTY DEPEND_DLLS)
        if(pre_dlls)
          set(_dlls ${pre_dlls} ${_dlls})
        endif()
        set_property(TARGET ${target}
          PROPERTY
          DEPEND_DLLS ${_dlls}
        )
    endif()
  endif()

endfunction()


if(_COCOS_BUILD_HELPERS_CMAKE)
    return()
endif()
set(_COCOS_BUILD_HELPERS_CMAKE TRUE)

include(CMakeDependentOption)

#===============================================================================
# Judge the target system first of all.

#cmake has some strange defaults, this should help us a lot
#Please use them everywhere
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    if(IOS)
        set(COCOS_TARGET_SYSTEM_IOS "iOS")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_IOS})
    else()
        set(COCOS_TARGET_SYSTEM_MACOSX "Mac OS X")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_MACOSX})
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(WINRT)
        set(COCOS_TARGET_SYSTEM_WINRT "Windows RT")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_WINRT})
    elseif(WP8)
        set(COCOS_TARGET_SYSTEM_WP8 "Windows Phone 8")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_WP8})
    else()
        set(COCOS_TARGET_SYSTEM_WINDOWS "Windows Desktop")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_WINDOWS})
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if(ANDROID)
        set(COCOS_TARGET_SYSTEM_ANDROID "Android")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_ANDROID})
    else()
        set(COCOS_TARGET_SYSTEM_LINUX "Linux")
        set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_LINUX})
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(COCOS_TARGET_SYSTEM_ANDROID "Android")
    set(COCOS_TARGET_SYSTEM ${COCOS_TARGET_SYSTEM_ANDROID})
else()
    message(AUTHOR_WARNING
        "Load ${CMAKE_CURRENT_LIST_FILE} on unsupported system."
        )
endif()

if(CMAKE_CROSSCOMPILING)
    message("Detected cross compiling for '${COCOS_TARGET_SYSTEM}' "
        "with '${CMAKE_CXX_COMPILER_ID}' on host '${CMAKE_HOST_SYSTEM}'."
        )
else()
    message("Detected compiling for '${COCOS_TARGET_SYSTEM}' "
        "with '${CMAKE_CXX_COMPILER_ID}' on host '${CMAKE_HOST_SYSTEM}'."
        )
endif()
#===============================================================================
# Define BUILD_SHARED_LIBS and BUILD_USE_PREBUILT_LIBS options.
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
     # Prebuilt windows libs can't be used with mingw.
    if(NOT MINGW)
        option(BUILD_USE_PREBUILT_LIBS
            "Use prebuilt libraries in external directory"
            ON
            )
    endif()
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # The prebuilt libraries on linux don't support build shared library.
    # if wan't build shared cocos2d project, use '-fPIC' to recompile all
    #     prebuilt libs.
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
    CMAKE_DEPENDENT_OPTION(BUILD_USE_PREBUILT_LIBS
        "Use prebuilt libraries in external directory"
        ON "NOT BUILD_SHARED_LIBS"
        OFF
        )
elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
    set(BUILD_USE_PREBUILT_LIBS TRUE CACHE INTERNAL "")
    set(BUILD_SHARED_LIBS FALSE CACHE INTERNAL "")
else()
    option(BUILD_USE_PREBUILT_LIBS "Use prebuilt libraries in external directory" ON)
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

#===============================================================================
# Compiler settings: definations, compile flags, compile options, link options.
if(APPLE)
    # All cocos2d-x executable compile as app bundle on macosx and ios.
    set(CMAKE_MACOSX_BUNDLE 1 CACHE INTERNAL "")

# Set output directory to build folder, for match the xcode target position.
# The xcode target default build location is: 
#   $(BUILD_DIR)/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)
# But the cmake created xcodeproj's default product path is:
#   $(PROJ_DIR)/build/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)
# cmake issue:http://public.kitware.com/Bug/bug_relationship_graph.php?bug_id=14853&graph=dependency
# It seems there is no way to change the product path, so redirect all target
#   build location to the default product path.
    if(XCODE_VERSION)
        set(_dir "${CMAKE_BINARY_DIR}/build/${CMAKE_CFG_INTDIR}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY                "${_dir}" CACHE PATH "")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${_dir}" CACHE PATH "")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${_dir}" CACHE PATH "")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_dir}" CACHE PATH "")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${_dir}" CACHE PATH "")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY                "${_dir}" CACHE PATH "")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${_dir}" CACHE PATH "")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${_dir}" CACHE PATH "")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_dir}" CACHE PATH "")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     "${_dir}" CACHE PATH "")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY                "${_dir}" CACHE PATH "")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${_dir}" CACHE PATH "")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${_dir}" CACHE PATH "")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_dir}" CACHE PATH "")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${_dir}" CACHE PATH "")
    endif()
endif()

if(MSVC)
    add_definitions(
       -D_CRT_SECURE_NO_WARNINGS
       -D_SCL_SECURE_NO_WARNINGS
       -D_UNICODE -DUNICODE
       -wd4267 -wd4251 -wd4244
        #-wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710 -wd4514 -wd4056 -wd4996 -wd4099
        )
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCOCOS2D_DEBUG=1")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCOCOS2D_DEBUG=1")

else() #GCC and CLANG
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -DCOCOS2D_DEBUG=1")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -DCOCOS2D_DEBUG=1")
    #-std=c99 cause android build cpufeatures failed.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions ") 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
    # if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    #     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    # endif()
endif()

#===============================================================================
# supported target platform specific settings.

if(COCOS_TARGET_SYSTEM_MACOSX)
    # prebuilt libs only support x86_64
    if(BUILD_USE_PREBUILT_LIBS)
        unset(CMAKE_OSX_ARCHITECTURES CACHE)
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
        set(COCOS_ARCH_FOLDER_SUFFIX "x86-64" CACHE INTERNAL "")
    else()
        set(COCOS_ARCH_FOLDER_SUFFIX "universal" CACHE STRING "")
    endif()

elseif(COCOS_TARGET_SYSTEM_WINDOWS)
    # Cocos only support win32.
    if(CMAKE_CL_64)
        message(FATAL_ERROR "Cocos only support i386 architecture on Windows!")
    endif()
    if(BUILD_USE_PREBUILT_LIBS)
        set(COCOS_ARCH_FOLDER_SUFFIX "i386" CACHE INTERNAL "")
    endif()

elseif(COCOS_TARGET_SYSTEM_LINUX)
    # Decide the target system architecture.
    # As default, target system arch same as host system.
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(default_arch "x86_64")
    else()
        set(default_arch "i386")
    endif()

    if(BUILD_USE_PREBUILT_LIBS)
        set(BUILD_TARGET_ARCHITECTURE "x86_64" CACHE INTERNAL "")
    else()
        set(BUILD_TARGET_ARCHITECTURE ${default_arch}
            CACHE STRING "Build project for i386 or x86_64."
            )
    endif()

    # COCOS_ARCH_FOLDER_SUFFIX variable for choose the prebuilt libraries in external.
    if(BUILD_TARGET_ARCHITECTURE MATCHES "x86_64")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        set(COCOS_ARCH_FOLDER_SUFFIX "x86-64")
    elseif(BUILD_TARGET_ARCHITECTURE MATCHES "i386")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        set(COCOS_ARCH_FOLDER_SUFFIX "i386")
    else()
        message(FATAL_ERROR "Unsupported architecture '${BUILD_TARGET_ARCHITECTURE}'!")
    endif()

    add_definitions("-DLINUX")

    # set binaries's default output directory to bin, cocos run need this setting.
    # can be override by command lines's same option.
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib" CACHE PATH "")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib" CACHE PATH "")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin" CACHE PATH "")

elseif(COCOS_TARGET_SYSTEM_IOS)
    # cocos source code ouse macro 'CC_TARGET_OS_IPHONE' to determine is iOS or not.
    add_definitions(-DCC_TARGET_OS_IPHONE)

elseif(COCOS_TARGET_SYSTEM_ANDROID)
    # cocos2d must build on ANDROID_NATIVE_API_LEVEL >= 9
    if(NOT ANDROID_NATIVE_API_LEVEL OR ANDROID_NATIVE_API_LEVEL LESS 9)
        # If set ANDROID_NATIVE_API_LEVEL here, need reconfigure once.
        # Set by cmd argument is better.
        message("Cocos2D-X must build on ANDROID_NATIVE_API_LEVEL >= 9, "
            "please configure again!"
            )
        set(ANDROID_NATIVE_API_LEVEL "9"
            CACHE STRING "Android API level for native code" FORCE
            )
    endif()
    set(COCOS_ARCH_FOLDER_SUFFIX "${ANDROID_ABI}" CACHE INTERNAL "" FORCE)
    include(../AndroidNdkModules)
    android_ndk_import_module_cpufeatures()
else()
    message(FATAL_ERROR
        "${CMAKE_CURRENT_LIST_FILE} build on unsupported target platform!"
        )
endif()

#===============================================================================
# cocos_use_package, find and add a package to a target.
# If BUILD_USE_PREBUILT_LIBS is ON, the needed package will use the prebuilt one
# in the <COCOS_ROOT>/external directory.
# If BUILD_USE_PREBUILT_LIBS is OFF, use the find_package to locate the package.

if(BUILD_USE_PREBUILT_LIBS)
    include(CocosUsePrebuiltLibs)
endif()

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
    set(${pkg_prefix}_INCLUDE_DIRS ${${pkg_prefix}_INCLUDE_DIRS} CACHE STRING "" FORCE)
    mark_as_advanced(${pkg_prefix}_INCLUDE_DIRS)
    if(NOT ${pkg_prefix}_LIBRARIES AND ${pkg_prefix}_LIBRARY)
        set(${pkg_prefix}_LIBRARIES ${${pkg_prefix}_LIBRARY})
    endif()
    set(${pkg_prefix}_LIBRARIES ${${pkg_prefix}_LIBRARIES} CACHE STRING "" FORCE)
    mark_as_advanced(${pkg_prefix}_LIBRARIES)
  
    message(STATUS "cocos find package '${pkg_name}':")
    message(STATUS "    pkg_libs: ${${pkg_prefix}_LIBRARIES}")
    message(STATUS "    inc_dirs: ${${pkg_prefix}_INCLUDE_DIRS}")
endmacro()

# cocos_use_package(pkg) function.
# This function applies standard package variables (after find_package(pkg) call) to current scope
# Recognized variables: <pkg>_INCLUDE_DIRS, <pkg>_LIBRARIES, <pkg>_LIBRARY_DIRS
# Also if BUILD_SHARED_LIBS variable off, it is try to use <pkg>_STATIC_* vars before
function(cocos_use_package target pkg)
    string(TOUPPER "${pkg}" pkg_upper)
    set(pkg_target "")

    # Use prebuilt library if it exists.
    if(TARGET ${pkg_upper}::${pkg_upper})
        set(pkg_target "${pkg_upper}::${pkg_upper}")
    elseif(TARGET ${pkg}::${pkg})
        set(pkg_target "${pkg}::${pkg}")
    endif()
    if(pkg_target)
        target_link_libraries(${target} ${pkg_target})
        message(STATUS "Add prebuilt package '${pkg}' to target '${target}'.")
        return()
    endif()

    # If pkg hasn't found, find it by cmake.
    cocos_find_package(${pkg} ${pkg_upper} ${ARGN})

    # If pakcage define target, use it.
    if(TARGET ${pkg_upper}::${pkg_upper})
        set(pkg_target "${pkg_upper}::${pkg_upper}")
    elseif(TARGET ${pkg}::${pkg})
        set(pkg_target "${pkg}::${pkg}")
    endif()
    if(pkg_target)
        target_link_libraries(${target} ${pkg_target})
        message(STATUS "Add package ${pkg}'s target '${pkg_target}' to target '${target}'.")
        return()
    endif()

    # Add include dirs, libs, macros which defined by package to target.
    set(pkg ${pkg_upper})
    message(STATUS "Add package '${pkg}' to target '${target}':")

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
        target_include_directories(${target} PUBLIC ${_include_dirs})
        message(STATUS "    add inc_dirs: ${_include_dirs}")
    endif()
    
    set(_library_dirs)
    if(NOT _library_dirs)
        set(_library_dirs ${${prefix}_LIBRARY_DIRS})
    endif()
    if(_library_dirs)
        link_directories(${_library_dirs})
        message(STATUS "    add linkdirs: ${_library_dirs}")
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
        message(STATUS "    add pkg_libs: ${_libs}")
    endif()
    
    set(_defs)
    if(NOT _defs)
        set(_defs ${${prefix}_DEFINITIONS})
    endif()
    if(_defs)
        target_compile_definitions(${target} PRIVATE ${_defs})
        message(STATUS "    add defines: ${_defs}")
    endif()
endfunction()

#===============================================================================
# Define a helper function for copy depends dll to exe directory.
function(_get_depends_dll _target)
    get_target_property(_deps ${_target} INTERFACE_LINK_LIBRARIES)
    foreach(_lib ${_deps})
        if(TARGET ${_lib})
            get_target_property(_dlls ${_lib} IMPORTED_LOCATION)
            get_target_property(_implib ${_lib} IMPORTED_IMPLIB)
            if(_implib)
                foreach(_dll ${_dlls})
                    set(_DEPENDS_DLL "${_DEPENDS_DLL};${_dll}"
                        CACHE INTERNAL "" FORCE
                        )
                endforeach()
            endif()
            _get_depends_dll(${_lib})
        endif()
    endforeach()
endfunction()

function(cocos_add_copy_depends_dll_command _target)
    if(NOT COCOS_TARGET_SYSTEM_WINDOWS)
        message(AUTHOR_WARNING 
            "function cocos_copy_depends_dll_command on for win32."
            )
        return()
    endif()
    if(NOT TARGET ${_target})
        message(AUTHOR_WARNING "Input target '${_target}' is invalid.")
        return()
    endif()
    
    set(_DEPENDS_DLL "" CACHE INTERNAL "" FORCE)
    _get_depends_dll(${_target})
    #message("Get Dlls: ${_DEPENDS_DLL}")
    foreach(_dll ${_DEPENDS_DLL})
        add_custom_command(TARGET ${_target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${_dll}"
            "$<TARGET_FILE_DIR:${app_name}>"
            )
    endforeach()
    unset(_DEPENDS_DLL CACHE)
endfunction()

#===============================================================================
#other helpers
include(CMakeParseArguments)

# Define a helper function for adding sources to target.
# usage: cocos_target_sources(<target_name>
#           [GROUP name]
#           <FILES f1 [f2 ...]>
#           )
function(cocos_target_sources _target)
   if(NOT TARGET ${_target})
        message(AUTHOR_WARNING "Invalid parameter target name '${_target}'.")
        return()
    endif()

    set(oneValueArgs    GROUP)
    set(multiValueArgs  FILES)
    cmake_parse_arguments(_opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(NOT _opt_FILES)
        message(AUTHOR_WARNING "There is no file input.")
        return()
    endif()
    target_sources(${_target} PRIVATE ${_opt_FILES})
    if(_opt_GROUP)
        source_group("${_opt_GROUP}" FILES ${_opt_FILES})
    endif()
endfunction()

# Define a helper function for adding resources to deployment target.
# usage: cocos_target_resource(<target_name>
#           [GROUP name]
#           [LOCATION "relative/path/to/package/root"]
#           [FLAT_TO_LOCATION <TRUE|FALSE>]
#           <FILES f1 [f2 ...]>
#           [BASEDIR "path suffix"] # if FLAT_TO_LOCATION = TRUE, unused.
#           )
function(cocos_target_resource _target)
    if(NOT TARGET ${_target})
        message(AUTHOR_WARNING "Invalid parameter target name '${_target}'.")
        return()
    endif()

    set(oneValueArgs    GROUP LOCATION FLAT_TO_LOCATION BASEDIR)
    set(multiValueArgs  FILES)
    cmake_parse_arguments(_opt "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(NOT _opt_FILES)
        message(AUTHOR_WARNING "There is no file input.")
        return()
    endif()

    target_sources(${_target} PRIVATE ${_opt_FILES})
    if(_opt_GROUP)
        source_group("${_opt_GROUP}" FILES ${_opt_FILES})
    endif()

    if(NOT _opt_LOCATION)
        return()
    endif()

    # Set resource package location below.
    if(APPLE)
        if(IOS)
            # For ios, the package root is not app folder, fix it.
            set(_opt_LOCATION "$(EXECUTABLE_NAME).app/${_opt_LOCATION}")
        endif()

        #message("GROUP:${_opt_GROUP}\n"
        #    "LOCATION:${_opt_LOCATION}}\n"
        #    "FLAT_TO_LOCATION:${_opt_FLAT_TO_LOCATION}\n"
        #    "BASEDIR:${_opt_BASEDIR}\n"
        #    "FILES:${_opt_FILES}\n"
        #    "UNPARSED_ARGUMENTS:${_opt_UNPARSED_ARGUMENTS}.\n"
        #    )
        foreach(_res ${_opt_FILES})# ${_opt_UNPARSED_ARGUMENTS})
            #message(${_res})
            if(_opt_FLAT_TO_LOCATION)
                set(_loc "${_opt_LOCATION}")
            else()
                get_filename_component(_dir ${_res} PATH)
                if(_opt_BASEDIR)
                    get_filename_component(_abs_base ${_opt_BASEDIR} ABSOLUTE)
                    get_filename_component(_abs_dir ${_dir} ABSOLUTE)
                    file(RELATIVE_PATH _dir ${_abs_base} ${_abs_dir})
                endif()
                set(_loc "${_opt_LOCATION}/${_dir}")
            endif()
            #message(${_loc})
            set_source_files_properties(${_res} PROPERTIES
                #HEADER_FILE_ONLY 1
                MACOSX_CONTENT 1
                XCODE_LAST_KNOWN_FILE_TYPE 1
                MACOSX_PACKAGE_LOCATION "${_loc}"
                )
        endforeach()
    endif()
endfunction()


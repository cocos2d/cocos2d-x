# FindFontconfig
# --------------
#
# Locate Fontconfig library
#

if(NOT FONTCONFIG_FOUND)
  find_package(PkgConfig)
  pkg_search_module(FONTCONFIG fontconfig)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Fontconfig
  REQUIRED_VARS FONTCONFIG_FOUND
  VERSION_VAR FONTCONFIG_VERSION
  )


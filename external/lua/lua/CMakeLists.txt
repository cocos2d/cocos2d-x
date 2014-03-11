set(LUA_SRC
  lapi.c
  lauxlib.c
  lbaselib.c
  lcode.c
  ldblib.c
  ldebug.c
  ldo.c
  ldump.c
  lfunc.c
  lgc.c
  linit.c
  liolib.c
  llex.c
  lmathlib.c
  lmem.c
  loadlib.c
  lobject.c
  lopcodes.c
  loslib.c
  lparser.c
  lstate.c
  lstring.c
  lstrlib.c
  ltable.c
  ltablib.c
  ltm.c
  lundump.c
  lvm.c
  lzio.c
  print.c
)

add_library(lua STATIC
  ${LUA_SRC}
)

set_target_properties(lua
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

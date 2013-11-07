if(BUILD_HelloCpp)
add_subdirectory(Cpp/HelloCpp)
endif(BUILD_HelloCpp)

if(BUILD_TestCpp)
add_subdirectory(Cpp/TestCpp)
endif(BUILD_TestCpp)

if(BUILD_HelloLua)
add_subdirectory(Lua/HelloLua)
endif(BUILD_HelloLua)

if(BUILD_TestLua)
add_subdirectory(Lua/TestLua)
endif(BUILD_TestLua)
/*
** Lua binding: HelperFunc_luabinding
** Generated automatically by tolua++-1.0.92 on Tue Jul 15 15:28:05 2014.
*/

#include "HelperFunc_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "../apptools/HelperFunc.h"

/* function to release collected object via destructor */
#ifdef __cplusplus


#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 
 tolua_usertype(tolua_S,"HelperFunc");
}

/* method: getFileData of class  HelperFunc */
#ifndef TOLUA_DISABLE_tolua_HelperFunc_luabinding_HelperFunc_getFileData00
static int tolua_HelperFunc_luabinding_HelperFunc_getFileData00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HelperFunc",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pPathFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
     HelperFunc::getFileData(pPathFile);
   
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_HelperFunc_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,"cc",0);
 tolua_beginmodule(tolua_S,"cc");
  tolua_cclass(tolua_S,"HelperFunc","HelperFunc","",NULL);
  tolua_beginmodule(tolua_S,"HelperFunc");
   tolua_function(tolua_S,"getFileData",tolua_HelperFunc_luabinding_HelperFunc_getFileData00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_HelperFunc_luabinding (lua_State* tolua_S) {
 return tolua_HelperFunc_luabinding_open(tolua_S);
};
#endif


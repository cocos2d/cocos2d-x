
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

TOLUA_API void tolua_prepare_ccobject_table(lua_State* L);
TOLUA_API void tolua_pushusertype_ccobject(lua_State* L, int uid, int* p_refid, void* ptr, const char* type);
TOLUA_API void tolua_remove_ccobject_by_refid(lua_State* L, int refid);

TOLUA_API void tolua_remove_function_by_refid(lua_State* L, int refid);

// C functions
TOLUA_API int tolua_isfunction(lua_State* L, int lo, tolua_Error* err);
TOLUA_API int tolua_ref_function(lua_State* L, int lo, int def);


#endif // __TOLUA_FIX_H_

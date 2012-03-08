
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#define TOLUA_REFID_PTR_MAPPING "tolua_refid_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "tolua_refid_type_mapping"

TOLUA_API void tolua_prepare_ccobject_table(lua_State* L);
TOLUA_API int tolua_pushusertype_ccobject(lua_State* L,
                                          int uid,
                                          int* p_refid,
                                          void* ptr,
                                          const char* type);
TOLUA_API int tolua_remove_ccobject_by_refid(lua_State* L, int refid);
TOLUA_API int tolua_ref_function(lua_State* L, int lo, int def);
TOLUA_API void tolua_remove_function_by_refid(lua_State* L, int refid);
TOLUA_API int tolua_isfunction(lua_State* L, int lo, tolua_Error* err);
TOLUA_API void tolua_stack_dump(lua_State* L, const char* label);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __TOLUA_FIX_H_

#ifndef __LUA_OPENGL_H__
#define __LUA_OPENGL_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "base_nodes/CCNode.h"
class GLNode:public cc::Node
{
    virtual void draw();
};


TOLUA_API int tolua_opengl_open(lua_State* tolua_S);

#endif //__LUA_OPENGL_H__

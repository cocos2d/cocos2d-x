#ifndef __LUA_OPENGL_H__
#define __LUA_OPENGL_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "CCNode.h"

class GLNode:public cocos2d::Node
{
    virtual void draw();
};

TOLUA_API int tolua_opengl_open(lua_State* tolua_S);
TOLUA_API int register_glnode_manual(lua_State* tolua_S);

#endif //__LUA_OPENGL_H__

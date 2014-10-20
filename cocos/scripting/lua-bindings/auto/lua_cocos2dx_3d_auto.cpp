#include "lua_cocos2dx_3d_auto.hpp"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_3d_Skeleton3D_getBoneByName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getBoneByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Skeleton3D:getBoneByName");
        if(!ok)
            return 0;
        cocos2d::Bone3D* ret = cobj->getBoneByName(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneByName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getBoneByName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_getRootBone(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getRootBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Skeleton3D:getRootBone");
        if(!ok)
            return 0;
        cocos2d::Bone3D* ret = cobj->getRootBone(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getRootBone",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getRootBone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_updateBoneMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_updateBoneMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateBoneMatrix();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:updateBoneMatrix",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_updateBoneMatrix'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_getBoneByIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getBoneByIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Skeleton3D:getBoneByIndex");
        if(!ok)
            return 0;
        cocos2d::Bone3D* ret = cobj->getBoneByIndex(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneByIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getBoneByIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_getRootCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getRootCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getRootCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getRootCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getRootCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_getBoneIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getBoneIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Bone3D* arg0;

        ok &= luaval_to_object<cocos2d::Bone3D>(tolua_S, 2, "cc.Bone3D",&arg0);
        if(!ok)
            return 0;
        int ret = cobj->getBoneIndex(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getBoneIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Skeleton3D_getBoneCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Skeleton3D_getBoneCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ssize_t ret = cobj->getBoneCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Skeleton3D_getBoneCount'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_3d_Skeleton3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Skeleton3D)");
    return 0;
}

int lua_register_cocos2dx_3d_Skeleton3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Skeleton3D");
    tolua_cclass(tolua_S,"Skeleton3D","cc.Skeleton3D","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Skeleton3D");
        tolua_function(tolua_S,"getBoneByName",lua_cocos2dx_3d_Skeleton3D_getBoneByName);
        tolua_function(tolua_S,"getRootBone",lua_cocos2dx_3d_Skeleton3D_getRootBone);
        tolua_function(tolua_S,"updateBoneMatrix",lua_cocos2dx_3d_Skeleton3D_updateBoneMatrix);
        tolua_function(tolua_S,"getBoneByIndex",lua_cocos2dx_3d_Skeleton3D_getBoneByIndex);
        tolua_function(tolua_S,"getRootCount",lua_cocos2dx_3d_Skeleton3D_getRootCount);
        tolua_function(tolua_S,"getBoneIndex",lua_cocos2dx_3d_Skeleton3D_getBoneIndex);
        tolua_function(tolua_S,"getBoneCount",lua_cocos2dx_3d_Skeleton3D_getBoneCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Skeleton3D).name();
    g_luaType[typeName] = "cc.Skeleton3D";
    g_typeCast["Skeleton3D"] = "cc.Skeleton3D";
    return 1;
}

int lua_cocos2dx_3d_Sprite3D_setCullFaceEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setCullFaceEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Sprite3D:setCullFaceEnabled");
        if(!ok)
            return 0;
        cobj->setCullFaceEnabled(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:setCullFaceEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setCullFaceEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);

            if (!ok) { break; }
            cobj->setTexture(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite3D:setTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getLightMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getLightMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        unsigned int ret = cobj->getLightMask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getLightMask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getLightMask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_removeAllAttachNode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_removeAllAttachNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->removeAllAttachNode();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:removeAllAttachNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_removeAllAttachNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getMesh(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getMesh'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Mesh* ret = cobj->getMesh();
        object_to_luaval<cocos2d::Mesh>(tolua_S, "cc.Mesh",(cocos2d::Mesh*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getMesh",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getMesh'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_setLightMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setLightMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Sprite3D:setLightMask");
        if(!ok)
            return 0;
        cobj->setLightMask(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:setLightMask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setLightMask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_setCullFace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setCullFace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Sprite3D:setCullFace");
        if(!ok)
            return 0;
        cobj->setCullFace(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:setCullFace",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setCullFace'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_removeAttachNode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_removeAttachNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:removeAttachNode");
        if(!ok)
            return 0;
        cobj->removeAttachNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:removeAttachNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_removeAttachNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getMeshByIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getMeshByIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Sprite3D:getMeshByIndex");
        if(!ok)
            return 0;
        cocos2d::Mesh* ret = cobj->getMeshByIndex(arg0);
        object_to_luaval<cocos2d::Mesh>(tolua_S, "cc.Mesh",(cocos2d::Mesh*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getMeshByIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getMeshByIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getMeshByName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getMeshByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:getMeshByName");
        if(!ok)
            return 0;
        cocos2d::Mesh* ret = cobj->getMeshByName(arg0);
        object_to_luaval<cocos2d::Mesh>(tolua_S, "cc.Mesh",(cocos2d::Mesh*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getMeshByName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getMeshByName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getSkeleton(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getSkeleton'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Skeleton3D* ret = cobj->getSkeleton();
        object_to_luaval<cocos2d::Skeleton3D>(tolua_S, "cc.Skeleton3D",(cocos2d::Skeleton3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getSkeleton",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getSkeleton'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_getAttachNode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getAttachNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:getAttachNode");
        if(!ok)
            return 0;
        cocos2d::AttachNode* ret = cobj->getAttachNode(arg0);
        object_to_luaval<cocos2d::AttachNode>(tolua_S, "cc.AttachNode",(cocos2d::AttachNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getAttachNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getAttachNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Sprite3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.Sprite3D:create");
            if (!ok) { break; }
            cocos2d::Sprite3D* ret = cocos2d::Sprite3D::create(arg0, arg1);
            object_to_luaval<cocos2d::Sprite3D>(tolua_S, "cc.Sprite3D",(cocos2d::Sprite3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Sprite3D:create");
            if (!ok) { break; }
            cocos2d::Sprite3D* ret = cocos2d::Sprite3D::create(arg0);
            object_to_luaval<cocos2d::Sprite3D>(tolua_S, "cc.Sprite3D",(cocos2d::Sprite3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.Sprite3D:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_3d_Sprite3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Sprite3D)");
    return 0;
}

int lua_register_cocos2dx_3d_Sprite3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Sprite3D");
    tolua_cclass(tolua_S,"Sprite3D","cc.Sprite3D","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Sprite3D");
        tolua_function(tolua_S,"setCullFaceEnabled",lua_cocos2dx_3d_Sprite3D_setCullFaceEnabled);
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_3d_Sprite3D_setTexture);
        tolua_function(tolua_S,"getLightMask",lua_cocos2dx_3d_Sprite3D_getLightMask);
        tolua_function(tolua_S,"removeAllAttachNode",lua_cocos2dx_3d_Sprite3D_removeAllAttachNode);
        tolua_function(tolua_S,"getMesh",lua_cocos2dx_3d_Sprite3D_getMesh);
        tolua_function(tolua_S,"setLightMask",lua_cocos2dx_3d_Sprite3D_setLightMask);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_3d_Sprite3D_getBlendFunc);
        tolua_function(tolua_S,"setCullFace",lua_cocos2dx_3d_Sprite3D_setCullFace);
        tolua_function(tolua_S,"removeAttachNode",lua_cocos2dx_3d_Sprite3D_removeAttachNode);
        tolua_function(tolua_S,"getMeshByIndex",lua_cocos2dx_3d_Sprite3D_getMeshByIndex);
        tolua_function(tolua_S,"getMeshByName",lua_cocos2dx_3d_Sprite3D_getMeshByName);
        tolua_function(tolua_S,"getSkeleton",lua_cocos2dx_3d_Sprite3D_getSkeleton);
        tolua_function(tolua_S,"getAttachNode",lua_cocos2dx_3d_Sprite3D_getAttachNode);
        tolua_function(tolua_S,"create", lua_cocos2dx_3d_Sprite3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Sprite3D).name();
    g_luaType[typeName] = "cc.Sprite3D";
    g_typeCast["Sprite3D"] = "cc.Sprite3D";
    return 1;
}

int lua_cocos2dx_3d_Mesh_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);

            if (!ok) { break; }
            cobj->setTexture(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Mesh:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Mesh:setTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Texture2D* ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getTexture",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_getTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_getName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR BlendFunc
		ok = false;
        if(!ok)
            return 0;
        cobj->setBlendFunc(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_isVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_isVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isVisible();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:isVisible",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_isVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Mesh_setVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Mesh_setVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Mesh:setVisible");
        if(!ok)
            return 0;
        cobj->setVisible(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Mesh_setVisible'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_3d_Mesh_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Mesh)");
    return 0;
}

int lua_register_cocos2dx_3d_Mesh(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Mesh");
    tolua_cclass(tolua_S,"Mesh","cc.Mesh","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Mesh");
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_3d_Mesh_setTexture);
        tolua_function(tolua_S,"getTexture",lua_cocos2dx_3d_Mesh_getTexture);
        tolua_function(tolua_S,"getName",lua_cocos2dx_3d_Mesh_getName);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_3d_Mesh_setBlendFunc);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_3d_Mesh_getBlendFunc);
        tolua_function(tolua_S,"isVisible",lua_cocos2dx_3d_Mesh_isVisible);
        tolua_function(tolua_S,"setVisible",lua_cocos2dx_3d_Mesh_setVisible);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Mesh).name();
    g_luaType[typeName] = "cc.Mesh";
    g_typeCast["Mesh"] = "cc.Mesh";
    return 1;
}

int lua_cocos2dx_3d_Animation3D_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Animation3D_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation3D:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animation3D_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Animation3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animation3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Animation3D:create");
        if(!ok)
            return 0;
        cocos2d::Animation3D* ret = cocos2d::Animation3D::create(arg0);
        object_to_luaval<cocos2d::Animation3D>(tolua_S, "cc.Animation3D",(cocos2d::Animation3D*)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Animation3D:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.Animation3D:create");
        if(!ok)
            return 0;
        cocos2d::Animation3D* ret = cocos2d::Animation3D::create(arg0, arg1);
        object_to_luaval<cocos2d::Animation3D>(tolua_S, "cc.Animation3D",(cocos2d::Animation3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animation3D:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animation3D_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_3d_Animation3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Animation3D)");
    return 0;
}

int lua_register_cocos2dx_3d_Animation3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Animation3D");
    tolua_cclass(tolua_S,"Animation3D","cc.Animation3D","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Animation3D");
        tolua_function(tolua_S,"getDuration",lua_cocos2dx_3d_Animation3D_getDuration);
        tolua_function(tolua_S,"create", lua_cocos2dx_3d_Animation3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Animation3D).name();
    g_luaType[typeName] = "cc.Animation3D";
    g_typeCast["Animation3D"] = "cc.Animation3D";
    return 1;
}

int lua_cocos2dx_3d_Animate3D_setSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animate3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Animate3D_setSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Animate3D:setSpeed");
        if(!ok)
            return 0;
        cobj->setSpeed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_setSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Animate3D_setWeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animate3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Animate3D_setWeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Animate3D:setWeight");
        if(!ok)
            return 0;
        cobj->setWeight(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setWeight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_setWeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Animate3D_getSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animate3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Animate3D_getSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_getSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Animate3D_getWeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animate3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Animate3D_getWeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getWeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:getWeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_getWeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_Animate3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            cocos2d::Animation3D* arg0;
            ok &= luaval_to_object<cocos2d::Animation3D>(tolua_S, 2, "cc.Animation3D",&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animate3D:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Animate3D:create");
            if (!ok) { break; }
            cocos2d::Animate3D* ret = cocos2d::Animate3D::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Animate3D>(tolua_S, "cc.Animate3D",(cocos2d::Animate3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Animation3D* arg0;
            ok &= luaval_to_object<cocos2d::Animation3D>(tolua_S, 2, "cc.Animation3D",&arg0);
            if (!ok) { break; }
            cocos2d::Animate3D* ret = cocos2d::Animate3D::create(arg0);
            object_to_luaval<cocos2d::Animate3D>(tolua_S, "cc.Animate3D",(cocos2d::Animate3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.Animate3D:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_3d_Animate3D_getTransitionTime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        double ret = cocos2d::Animate3D::getTransitionTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate3D:getTransitionTime",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_getTransitionTime'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_3d_Animate3D_createWithFrames(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Animation3D* arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_object<cocos2d::Animation3D>(tolua_S, 2, "cc.Animation3D",&arg0);
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Animate3D:createWithFrames");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Animate3D:createWithFrames");
        if(!ok)
            return 0;
        cocos2d::Animate3D* ret = cocos2d::Animate3D::createWithFrames(arg0, arg1, arg2);
        object_to_luaval<cocos2d::Animate3D>(tolua_S, "cc.Animate3D",(cocos2d::Animate3D*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Animation3D* arg0;
        int arg1;
        int arg2;
        double arg3;
        ok &= luaval_to_object<cocos2d::Animation3D>(tolua_S, 2, "cc.Animation3D",&arg0);
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Animate3D:createWithFrames");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Animate3D:createWithFrames");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Animate3D:createWithFrames");
        if(!ok)
            return 0;
        cocos2d::Animate3D* ret = cocos2d::Animate3D::createWithFrames(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Animate3D>(tolua_S, "cc.Animate3D",(cocos2d::Animate3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate3D:createWithFrames",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Animate3D_createWithFrames'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_3d_Animate3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Animate3D)");
    return 0;
}

int lua_register_cocos2dx_3d_Animate3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Animate3D");
    tolua_cclass(tolua_S,"Animate3D","cc.Animate3D","cc.ActionInterval",nullptr);

    tolua_beginmodule(tolua_S,"Animate3D");
        tolua_function(tolua_S,"setSpeed",lua_cocos2dx_3d_Animate3D_setSpeed);
        tolua_function(tolua_S,"setWeight",lua_cocos2dx_3d_Animate3D_setWeight);
        tolua_function(tolua_S,"getSpeed",lua_cocos2dx_3d_Animate3D_getSpeed);
        tolua_function(tolua_S,"getWeight",lua_cocos2dx_3d_Animate3D_getWeight);
        tolua_function(tolua_S,"create", lua_cocos2dx_3d_Animate3D_create);
        tolua_function(tolua_S,"getTransitionTime", lua_cocos2dx_3d_Animate3D_getTransitionTime);
        tolua_function(tolua_S,"createWithFrames", lua_cocos2dx_3d_Animate3D_createWithFrames);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Animate3D).name();
    g_luaType[typeName] = "cc.Animate3D";
    g_typeCast["Animate3D"] = "cc.Animate3D";
    return 1;
}

int lua_cocos2dx_3d_AttachNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AttachNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Bone3D* arg0;
        ok &= luaval_to_object<cocos2d::Bone3D>(tolua_S, 2, "cc.Bone3D",&arg0);
        if(!ok)
            return 0;
        cocos2d::AttachNode* ret = cocos2d::AttachNode::create(arg0);
        object_to_luaval<cocos2d::AttachNode>(tolua_S, "cc.AttachNode",(cocos2d::AttachNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AttachNode:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_AttachNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_3d_AttachNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AttachNode)");
    return 0;
}

int lua_register_cocos2dx_3d_AttachNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AttachNode");
    tolua_cclass(tolua_S,"AttachNode","cc.AttachNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"AttachNode");
        tolua_function(tolua_S,"create", lua_cocos2dx_3d_AttachNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::AttachNode).name();
    g_luaType[typeName] = "cc.AttachNode";
    g_typeCast["AttachNode"] = "cc.AttachNode";
    return 1;
}

int lua_cocos2dx_3d_BillBoard_getMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillBoard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillBoard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillBoard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_BillBoard_getMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getMode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillBoard:getMode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_BillBoard_getMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_BillBoard_setMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillBoard* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillBoard",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillBoard*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_BillBoard_setMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BillBoard::Mode arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillBoard:setMode");
        if(!ok)
            return 0;
        cobj->setMode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillBoard:setMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_BillBoard_setMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_3d_BillBoard_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.BillBoard",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard::Mode arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create();
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::BillBoard::Mode arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard::Mode arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.BillBoard:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_BillBoard_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_3d_BillBoard_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.BillBoard",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Texture2D* arg0;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
        if(!ok)
            return 0;
        cocos2d::BillBoard* ret = cocos2d::BillBoard::createWithTexture(arg0);
        object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Texture2D* arg0;
        cocos2d::BillBoard::Mode arg1;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0);
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.BillBoard:createWithTexture");
        if(!ok)
            return 0;
        cocos2d::BillBoard* ret = cocos2d::BillBoard::createWithTexture(arg0, arg1);
        object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.BillBoard:createWithTexture",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_BillBoard_createWithTexture'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_3d_BillBoard_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BillBoard)");
    return 0;
}

int lua_register_cocos2dx_3d_BillBoard(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.BillBoard");
    tolua_cclass(tolua_S,"BillBoard","cc.BillBoard","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"BillBoard");
        tolua_function(tolua_S,"getMode",lua_cocos2dx_3d_BillBoard_getMode);
        tolua_function(tolua_S,"setMode",lua_cocos2dx_3d_BillBoard_setMode);
        tolua_function(tolua_S,"create", lua_cocos2dx_3d_BillBoard_create);
        tolua_function(tolua_S,"createWithTexture", lua_cocos2dx_3d_BillBoard_createWithTexture);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::BillBoard).name();
    g_luaType[typeName] = "cc.BillBoard";
    g_typeCast["BillBoard"] = "cc.BillBoard";
    return 1;
}
TOLUA_API int register_all_cocos2dx_3d(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_3d_Animate3D(tolua_S);
	lua_register_cocos2dx_3d_Sprite3D(tolua_S);
	lua_register_cocos2dx_3d_AttachNode(tolua_S);
	lua_register_cocos2dx_3d_BillBoard(tolua_S);
	lua_register_cocos2dx_3d_Animation3D(tolua_S);
	lua_register_cocos2dx_3d_Skeleton3D(tolua_S);
	lua_register_cocos2dx_3d_Mesh(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}


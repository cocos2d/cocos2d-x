#include "scripting/lua-bindings/auto/lua_cocos2dx_backend_auto.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"


int lua_register_cocos2dx_backend_BufferUsage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BufferUsage", 0);
    tolua_beginmodule(tolua_S,"BufferUsage");
        tolua_constant(tolua_S, "STATIC", 0);
        tolua_constant(tolua_S, "DYNAMIC", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::BufferUsage).name();
    g_luaType[typeName] = "ccb.BufferUsage";
    g_typeCast["BufferUsage"] = "ccb.BufferUsage";
    return 1;
}


int lua_register_cocos2dx_backend_BufferType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BufferType", 0);
    tolua_beginmodule(tolua_S,"BufferType");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "INDEX", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::BufferType).name();
    g_luaType[typeName] = "ccb.BufferType";
    g_typeCast["BufferType"] = "ccb.BufferType";
    return 1;
}


int lua_register_cocos2dx_backend_ShaderStage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "ShaderStage", 0);
    tolua_beginmodule(tolua_S,"ShaderStage");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "FRAGMENT", 1);
        tolua_constant(tolua_S, "VERTEX_AND_FRAGMENT", 2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::ShaderStage).name();
    g_luaType[typeName] = "ccb.ShaderStage";
    g_typeCast["ShaderStage"] = "ccb.ShaderStage";
    return 1;
}


int lua_register_cocos2dx_backend_VertexFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "VertexFormat", 0);
    tolua_beginmodule(tolua_S,"VertexFormat");
        tolua_constant(tolua_S, "FLOAT4", 0);
        tolua_constant(tolua_S, "FLOAT3", 1);
        tolua_constant(tolua_S, "FLOAT2", 2);
        tolua_constant(tolua_S, "FLOAT", 3);
        tolua_constant(tolua_S, "INT4", 4);
        tolua_constant(tolua_S, "INT3", 5);
        tolua_constant(tolua_S, "INT2", 6);
        tolua_constant(tolua_S, "INT", 7);
        tolua_constant(tolua_S, "USHORT4", 8);
        tolua_constant(tolua_S, "USHORT2", 9);
        tolua_constant(tolua_S, "UBYTE4", 10);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::VertexFormat).name();
    g_luaType[typeName] = "ccb.VertexFormat";
    g_typeCast["VertexFormat"] = "ccb.VertexFormat";
    return 1;
}


int lua_register_cocos2dx_backend_PixelFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "PixelFormat", 0);
    tolua_beginmodule(tolua_S,"PixelFormat");
        tolua_constant(tolua_S, "AUTO", 0);
        tolua_constant(tolua_S, "BGRA8888", 1);
        tolua_constant(tolua_S, "RGBA8888", 2);
        tolua_constant(tolua_S, "RGB888", 3);
        tolua_constant(tolua_S, "RGB565", 4);
        tolua_constant(tolua_S, "A8", 5);
        tolua_constant(tolua_S, "I8", 6);
        tolua_constant(tolua_S, "AI88", 7);
        tolua_constant(tolua_S, "RGBA4444", 8);
        tolua_constant(tolua_S, "RGB5A1", 9);
        tolua_constant(tolua_S, "PVRTC4", 10);
        tolua_constant(tolua_S, "PVRTC4A", 11);
        tolua_constant(tolua_S, "PVRTC2", 12);
        tolua_constant(tolua_S, "PVRTC2A", 13);
        tolua_constant(tolua_S, "ETC", 14);
        tolua_constant(tolua_S, "S3TC_DXT1", 15);
        tolua_constant(tolua_S, "S3TC_DXT3", 16);
        tolua_constant(tolua_S, "S3TC_DXT5", 17);
        tolua_constant(tolua_S, "ATC_RGB", 18);
        tolua_constant(tolua_S, "ATC_EXPLICIT_ALPHA", 19);
        tolua_constant(tolua_S, "ATC_INTERPOLATED_ALPHA", 20);
        tolua_constant(tolua_S, "MTL_B5G6R5", 21);
        tolua_constant(tolua_S, "MTL_BGR5A1", 22);
        tolua_constant(tolua_S, "MTL_ABGR4", 23);
        tolua_constant(tolua_S, "D24S8", 24);
        tolua_constant(tolua_S, "DEFAULT", 0);
        tolua_constant(tolua_S, "NONE", -1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::PixelFormat).name();
    g_luaType[typeName] = "ccb.PixelFormat";
    g_typeCast["PixelFormat"] = "ccb.PixelFormat";
    return 1;
}


int lua_register_cocos2dx_backend_TextureUsage(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureUsage", 0);
    tolua_beginmodule(tolua_S,"TextureUsage");
        tolua_constant(tolua_S, "READ", 0);
        tolua_constant(tolua_S, "WRITE", 1);
        tolua_constant(tolua_S, "RENDER_TARGET", 2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureUsage).name();
    g_luaType[typeName] = "ccb.TextureUsage";
    g_typeCast["TextureUsage"] = "ccb.TextureUsage";
    return 1;
}


int lua_register_cocos2dx_backend_IndexFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "IndexFormat", 0);
    tolua_beginmodule(tolua_S,"IndexFormat");
        tolua_constant(tolua_S, "U_SHORT", 0);
        tolua_constant(tolua_S, "U_INT", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::IndexFormat).name();
    g_luaType[typeName] = "ccb.IndexFormat";
    g_typeCast["IndexFormat"] = "ccb.IndexFormat";
    return 1;
}


int lua_register_cocos2dx_backend_VertexStepMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "VertexStepMode", 0);
    tolua_beginmodule(tolua_S,"VertexStepMode");
        tolua_constant(tolua_S, "VERTEX", 0);
        tolua_constant(tolua_S, "INSTANCE", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::VertexStepMode).name();
    g_luaType[typeName] = "ccb.VertexStepMode";
    g_typeCast["VertexStepMode"] = "ccb.VertexStepMode";
    return 1;
}


int lua_register_cocos2dx_backend_PrimitiveType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "PrimitiveType", 0);
    tolua_beginmodule(tolua_S,"PrimitiveType");
        tolua_constant(tolua_S, "POINT", 0);
        tolua_constant(tolua_S, "LINE", 1);
        tolua_constant(tolua_S, "LINE_STRIP", 2);
        tolua_constant(tolua_S, "TRIANGLE", 3);
        tolua_constant(tolua_S, "TRIANGLE_STRIP", 4);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::PrimitiveType).name();
    g_luaType[typeName] = "ccb.PrimitiveType";
    g_typeCast["PrimitiveType"] = "ccb.PrimitiveType";
    return 1;
}


int lua_register_cocos2dx_backend_TextureType(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureType", 0);
    tolua_beginmodule(tolua_S,"TextureType");
        tolua_constant(tolua_S, "TEXTURE_2D", 0);
        tolua_constant(tolua_S, "TEXTURE_CUBE", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureType).name();
    g_luaType[typeName] = "ccb.TextureType";
    g_typeCast["TextureType"] = "ccb.TextureType";
    return 1;
}


int lua_register_cocos2dx_backend_SamplerAddressMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "SamplerAddressMode", 0);
    tolua_beginmodule(tolua_S,"SamplerAddressMode");
        tolua_constant(tolua_S, "REPEAT", 0);
        tolua_constant(tolua_S, "MIRROR_REPEAT", 1);
        tolua_constant(tolua_S, "CLAMP_TO_EDGE", 2);
        tolua_constant(tolua_S, "DONT_CARE", 3);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::SamplerAddressMode).name();
    g_luaType[typeName] = "ccb.SamplerAddressMode";
    g_typeCast["SamplerAddressMode"] = "ccb.SamplerAddressMode";
    return 1;
}


int lua_register_cocos2dx_backend_SamplerFilter(lua_State* tolua_S)
{
    tolua_module(tolua_S, "SamplerFilter", 0);
    tolua_beginmodule(tolua_S,"SamplerFilter");
        tolua_constant(tolua_S, "NEAREST", 0);
        tolua_constant(tolua_S, "NEAREST_MIPMAP_NEAREST", 1);
        tolua_constant(tolua_S, "NEAREST_MIPMAP_LINEAR", 2);
        tolua_constant(tolua_S, "LINEAR", 3);
        tolua_constant(tolua_S, "LINEAR_MIPMAP_LINEAR", 4);
        tolua_constant(tolua_S, "LINEAR_MIPMAP_NEAREST", 5);
        tolua_constant(tolua_S, "DONT_CARE", 6);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::SamplerFilter).name();
    g_luaType[typeName] = "ccb.SamplerFilter";
    g_typeCast["SamplerFilter"] = "ccb.SamplerFilter";
    return 1;
}


int lua_register_cocos2dx_backend_StencilOperation(lua_State* tolua_S)
{
    tolua_module(tolua_S, "StencilOperation", 0);
    tolua_beginmodule(tolua_S,"StencilOperation");
        tolua_constant(tolua_S, "KEEP", 0);
        tolua_constant(tolua_S, "ZERO", 1);
        tolua_constant(tolua_S, "REPLACE", 2);
        tolua_constant(tolua_S, "INVERT", 3);
        tolua_constant(tolua_S, "INCREMENT_WRAP", 4);
        tolua_constant(tolua_S, "DECREMENT_WRAP", 5);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::StencilOperation).name();
    g_luaType[typeName] = "ccb.StencilOperation";
    g_typeCast["StencilOperation"] = "ccb.StencilOperation";
    return 1;
}


int lua_register_cocos2dx_backend_CompareFunction(lua_State* tolua_S)
{
    tolua_module(tolua_S, "CompareFunction", 0);
    tolua_beginmodule(tolua_S,"CompareFunction");
        tolua_constant(tolua_S, "NEVER", 0);
        tolua_constant(tolua_S, "LESS", 1);
        tolua_constant(tolua_S, "LESS_EQUAL", 2);
        tolua_constant(tolua_S, "GREATER", 3);
        tolua_constant(tolua_S, "GREATER_EQUAL", 4);
        tolua_constant(tolua_S, "EQUAL", 5);
        tolua_constant(tolua_S, "NOT_EQUAL", 6);
        tolua_constant(tolua_S, "ALWAYS", 7);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::CompareFunction).name();
    g_luaType[typeName] = "ccb.CompareFunction";
    g_typeCast["CompareFunction"] = "ccb.CompareFunction";
    return 1;
}


int lua_register_cocos2dx_backend_BlendOperation(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BlendOperation", 0);
    tolua_beginmodule(tolua_S,"BlendOperation");
        tolua_constant(tolua_S, "ADD", 0);
        tolua_constant(tolua_S, "SUBTRACT", 1);
        tolua_constant(tolua_S, "RESERVE_SUBTRACT", 2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::BlendOperation).name();
    g_luaType[typeName] = "ccb.BlendOperation";
    g_typeCast["BlendOperation"] = "ccb.BlendOperation";
    return 1;
}


int lua_register_cocos2dx_backend_BlendFactor(lua_State* tolua_S)
{
    tolua_module(tolua_S, "BlendFactor", 0);
    tolua_beginmodule(tolua_S,"BlendFactor");
        tolua_constant(tolua_S, "ZERO", 0);
        tolua_constant(tolua_S, "ONE", 1);
        tolua_constant(tolua_S, "SRC_COLOR", 2);
        tolua_constant(tolua_S, "ONE_MINUS_SRC_COLOR", 3);
        tolua_constant(tolua_S, "SRC_ALPHA", 4);
        tolua_constant(tolua_S, "ONE_MINUS_SRC_ALPHA", 5);
        tolua_constant(tolua_S, "DST_COLOR", 6);
        tolua_constant(tolua_S, "ONE_MINUS_DST_COLOR", 7);
        tolua_constant(tolua_S, "DST_ALPHA", 8);
        tolua_constant(tolua_S, "ONE_MINUS_DST_ALPHA", 9);
        tolua_constant(tolua_S, "CONSTANT_ALPHA", 10);
        tolua_constant(tolua_S, "SRC_ALPHA_SATURATE", 11);
        tolua_constant(tolua_S, "ONE_MINUS_CONSTANT_ALPHA", 12);
        tolua_constant(tolua_S, "BLEND_CLOLOR", 13);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::BlendFactor).name();
    g_luaType[typeName] = "ccb.BlendFactor";
    g_typeCast["BlendFactor"] = "ccb.BlendFactor";
    return 1;
}


int lua_register_cocos2dx_backend_ColorWriteMask(lua_State* tolua_S)
{
    tolua_module(tolua_S, "ColorWriteMask", 0);
    tolua_beginmodule(tolua_S,"ColorWriteMask");
        tolua_constant(tolua_S, "NONE", 0);
        tolua_constant(tolua_S, "RED", 1);
        tolua_constant(tolua_S, "GREEN", 2);
        tolua_constant(tolua_S, "BLUE", 4);
        tolua_constant(tolua_S, "ALPHA", 8);
        tolua_constant(tolua_S, "ALL", 15);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::ColorWriteMask).name();
    g_luaType[typeName] = "ccb.ColorWriteMask";
    g_typeCast["ColorWriteMask"] = "ccb.ColorWriteMask";
    return 1;
}


int lua_register_cocos2dx_backend_CullMode(lua_State* tolua_S)
{
    tolua_module(tolua_S, "CullMode", 0);
    tolua_beginmodule(tolua_S,"CullMode");
        tolua_constant(tolua_S, "NONE", 0);
        tolua_constant(tolua_S, "BACK", 1);
        tolua_constant(tolua_S, "FRONT", 2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::CullMode).name();
    g_luaType[typeName] = "ccb.CullMode";
    g_typeCast["CullMode"] = "ccb.CullMode";
    return 1;
}


int lua_register_cocos2dx_backend_Winding(lua_State* tolua_S)
{
    tolua_module(tolua_S, "Winding", 0);
    tolua_beginmodule(tolua_S,"Winding");
        tolua_constant(tolua_S, "CLOCK_WISE", 0);
        tolua_constant(tolua_S, "COUNTER_CLOCK_WISE", 1);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Winding).name();
    g_luaType[typeName] = "ccb.Winding";
    g_typeCast["Winding"] = "ccb.Winding";
    return 1;
}


int lua_register_cocos2dx_backend_TextureCubeFace(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureCubeFace", 0);
    tolua_beginmodule(tolua_S,"TextureCubeFace");
        tolua_constant(tolua_S, "POSITIVE_X", 0);
        tolua_constant(tolua_S, "NEGATIVE_X", 1);
        tolua_constant(tolua_S, "POSITIVE_Y", 2);
        tolua_constant(tolua_S, "NEGATIVE_Y", 3);
        tolua_constant(tolua_S, "POSITIVE_Z", 4);
        tolua_constant(tolua_S, "NEGATIVE_Z", 5);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureCubeFace).name();
    g_luaType[typeName] = "ccb.TextureCubeFace";
    g_typeCast["TextureCubeFace"] = "ccb.TextureCubeFace";
    return 1;
}

int lua_cocos2dx_backend_Program_getMaxVertexLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getMaxVertexLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getMaxVertexLocation'", nullptr);
            return 0;
        }
        int ret = cobj->getMaxVertexLocation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getMaxVertexLocation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getMaxVertexLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getMaxFragmentLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getMaxFragmentLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getMaxFragmentLocation'", nullptr);
            return 0;
        }
        int ret = cobj->getMaxFragmentLocation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getMaxFragmentLocation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getMaxFragmentLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getFragmentShader(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getFragmentShader'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getFragmentShader'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getFragmentShader();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getFragmentShader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getFragmentShader'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getUniformBufferSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getUniformBufferSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::ShaderStage arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getUniformBufferSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getUniformBufferSize'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getUniformBufferSize(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getUniformBufferSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getUniformBufferSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getUniformLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getUniformLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Uniform arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getUniformLocation");

            if (!ok) { break; }
            cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
            uniformLocation_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.Program:getUniformLocation");

            if (!ok) { break; }
            cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
            uniformLocation_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.Program:getUniformLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getUniformLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getProgramType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getProgramType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getProgramType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getProgramType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getProgramType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getProgramType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getActiveAttributes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getActiveAttributes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getActiveAttributes'", nullptr);
            return 0;
        }
        std::unordered_map<std::string, cocos2d::backend::AttributeBindInfo> ret = cobj->getActiveAttributes();
        program_activeattrs_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getActiveAttributes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getActiveAttributes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getAttributeLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getAttributeLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Attribute arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.Program:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.Program:getAttributeLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getAttributeLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getVertexShader(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Program_getVertexShader'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getVertexShader'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getVertexShader();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getVertexShader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getVertexShader'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Program_getBuiltinProgram(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::backend::ProgramType arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getBuiltinProgram");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getBuiltinProgram'", nullptr);
            return 0;
        }
        cocos2d::backend::Program* ret = cocos2d::backend::Program::getBuiltinProgram(arg0);
        object_to_luaval<cocos2d::backend::Program>(tolua_S, "ccb.Program",(cocos2d::backend::Program*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.Program:getBuiltinProgram",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getBuiltinProgram'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_backend_Program_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Program)");
    return 0;
}

int lua_register_cocos2dx_backend_Program(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.Program");
    tolua_cclass(tolua_S,"Program","ccb.Program","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Program");
        tolua_function(tolua_S,"getMaxVertexLocation",lua_cocos2dx_backend_Program_getMaxVertexLocation);
        tolua_function(tolua_S,"getMaxFragmentLocation",lua_cocos2dx_backend_Program_getMaxFragmentLocation);
        tolua_function(tolua_S,"getFragmentShader",lua_cocos2dx_backend_Program_getFragmentShader);
        tolua_function(tolua_S,"getUniformBufferSize",lua_cocos2dx_backend_Program_getUniformBufferSize);
        tolua_function(tolua_S,"getUniformLocation",lua_cocos2dx_backend_Program_getUniformLocation);
        tolua_function(tolua_S,"getProgramType",lua_cocos2dx_backend_Program_getProgramType);
        tolua_function(tolua_S,"getActiveAttributes",lua_cocos2dx_backend_Program_getActiveAttributes);
        tolua_function(tolua_S,"getAttributeLocation",lua_cocos2dx_backend_Program_getAttributeLocation);
        tolua_function(tolua_S,"getVertexShader",lua_cocos2dx_backend_Program_getVertexShader);
        tolua_function(tolua_S,"getBuiltinProgram", lua_cocos2dx_backend_Program_getBuiltinProgram);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Program).name();
    g_luaType[typeName] = "ccb.Program";
    g_typeCast["Program"] = "ccb.Program";
    return 1;
}

int lua_cocos2dx_backend_VertexLayout_getVertexStepMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_getVertexStepMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_getVertexStepMode'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getVertexStepMode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:getVertexStepMode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_getVertexStepMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_isValid(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_isValid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_isValid'", nullptr);
            return 0;
        }
        bool ret = cobj->isValid();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:isValid",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_isValid'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_setLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_setLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.VertexLayout:setLayout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_setLayout'", nullptr);
            return 0;
        }
        cobj->setLayout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:setLayout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_setLayout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_setAttribute(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_setAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        std::string arg0;
        unsigned int arg1;
        cocos2d::backend::VertexFormat arg2;
        unsigned int arg3;
        bool arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccb.VertexLayout:setAttribute");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_setAttribute'", nullptr);
            return 0;
        }
        cobj->setAttribute(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:setAttribute",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_setAttribute'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_getStride(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_getStride'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_getStride'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getStride();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:getStride",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_getStride'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::backend::VertexLayout();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccb.VertexLayout");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:VertexLayout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_backend_VertexLayout_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (VertexLayout)");
    return 0;
}

int lua_register_cocos2dx_backend_VertexLayout(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.VertexLayout");
    tolua_cclass(tolua_S,"VertexLayout","ccb.VertexLayout","",nullptr);

    tolua_beginmodule(tolua_S,"VertexLayout");
        tolua_function(tolua_S,"new",lua_cocos2dx_backend_VertexLayout_constructor);
        tolua_function(tolua_S,"getVertexStepMode",lua_cocos2dx_backend_VertexLayout_getVertexStepMode);
        tolua_function(tolua_S,"isValid",lua_cocos2dx_backend_VertexLayout_isValid);
        tolua_function(tolua_S,"setLayout",lua_cocos2dx_backend_VertexLayout_setLayout);
        tolua_function(tolua_S,"setAttribute",lua_cocos2dx_backend_VertexLayout_setAttribute);
        tolua_function(tolua_S,"getStride",lua_cocos2dx_backend_VertexLayout_getStride);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::VertexLayout).name();
    g_luaType[typeName] = "ccb.VertexLayout";
    g_typeCast["VertexLayout"] = "ccb.VertexLayout";
    return 1;
}

int lua_cocos2dx_backend_ProgramState_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::backend::UniformLocation arg0;
        unsigned int arg1;
        cocos2d::backend::TextureBackend* arg2;

        ok &= luaval_to_uniformLocation(tolua_S, 2, arg0, "ccb.ProgramState:setTexture");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.ProgramState:setTexture");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 4, "ccb.TextureBackend",&arg2, "ccb.ProgramState:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setTexture",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_clone(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_clone'", nullptr);
            return 0;
        }
        cocos2d::backend::ProgramState* ret = cobj->clone();
        object_to_luaval<cocos2d::backend::ProgramState>(tolua_S, "ccb.ProgramState",(cocos2d::backend::ProgramState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_setParameterAutoBinding(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_setParameterAutoBinding'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.ProgramState:setParameterAutoBinding");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccb.ProgramState:setParameterAutoBinding");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_setParameterAutoBinding'", nullptr);
            return 0;
        }
        cobj->setParameterAutoBinding(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setParameterAutoBinding",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_setParameterAutoBinding'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_getProgram(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_getProgram'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_getProgram'", nullptr);
            return 0;
        }
        cocos2d::backend::Program* ret = cobj->getProgram();
        object_to_luaval<cocos2d::backend::Program>(tolua_S, "ccb.Program",(cocos2d::backend::Program*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:getProgram",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_getProgram'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_getAttributeLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_getAttributeLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Attribute arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.ProgramState:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.ProgramState:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.ProgramState:getAttributeLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_getAttributeLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::Program* arg0;

        ok &= luaval_to_object<cocos2d::backend::Program>(tolua_S, 2, "ccb.Program",&arg0, "ccb.ProgramState:ProgramState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::backend::ProgramState(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccb.ProgramState");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:ProgramState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_backend_ProgramState_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProgramState)");
    return 0;
}

int lua_register_cocos2dx_backend_ProgramState(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.ProgramState");
    tolua_cclass(tolua_S,"ProgramState","ccb.ProgramState","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ProgramState");
        tolua_function(tolua_S,"new",lua_cocos2dx_backend_ProgramState_constructor);
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_backend_ProgramState_setTexture);
        tolua_function(tolua_S,"clone",lua_cocos2dx_backend_ProgramState_clone);
        tolua_function(tolua_S,"setParameterAutoBinding",lua_cocos2dx_backend_ProgramState_setParameterAutoBinding);
        tolua_function(tolua_S,"getProgram",lua_cocos2dx_backend_ProgramState_getProgram);
        tolua_function(tolua_S,"getAttributeLocation",lua_cocos2dx_backend_ProgramState_getAttributeLocation);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::ProgramState).name();
    g_luaType[typeName] = "ccb.ProgramState";
    g_typeCast["ProgramState"] = "ccb.ProgramState";
    return 1;
}

int lua_cocos2dx_backend_TextureBackend_getTextureFormat(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_getTextureFormat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_getTextureFormat'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureFormat();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureFormat",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_getTextureFormat'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_getTextureType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_getTextureType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_getTextureType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_getTextureType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_updateSamplerDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_updateSamplerDescriptor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::SamplerDescriptor arg0;

        ok &= luaval_to_samplerDescriptor(tolua_S, 2, arg0, "ccb.TextureBackend:updateSamplerDescriptor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_updateSamplerDescriptor'", nullptr);
            return 0;
        }
        cobj->updateSamplerDescriptor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:updateSamplerDescriptor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_updateSamplerDescriptor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_updateTextureDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_updateTextureDescriptor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::TextureDescriptor arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR TextureDescriptor
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_updateTextureDescriptor'", nullptr);
            return 0;
        }
        cobj->updateTextureDescriptor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:updateTextureDescriptor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_updateTextureDescriptor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_getTextureUsage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_getTextureUsage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_getTextureUsage'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureUsage();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getTextureUsage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_getTextureUsage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_hasMipmaps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_hasMipmaps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_hasMipmaps'", nullptr);
            return 0;
        }
        bool ret = cobj->hasMipmaps();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:hasMipmaps",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_hasMipmaps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_generateMipmaps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_generateMipmaps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_generateMipmaps'", nullptr);
            return 0;
        }
        cobj->generateMipmaps();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:generateMipmaps",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_generateMipmaps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_TextureBackend_getBytes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureBackend_getBytes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        bool arg4;
        std::function<void (const unsigned char *, unsigned int, unsigned int)> arg5;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.TextureBackend:getBytes");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.TextureBackend:getBytes");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.TextureBackend:getBytes");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.TextureBackend:getBytes");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccb.TextureBackend:getBytes");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureBackend_getBytes'", nullptr);
            return 0;
        }
        cobj->getBytes(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:getBytes",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureBackend_getBytes'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_backend_TextureBackend_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextureBackend)");
    return 0;
}

int lua_register_cocos2dx_backend_TextureBackend(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.TextureBackend");
    tolua_cclass(tolua_S,"TextureBackend","ccb.TextureBackend","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"TextureBackend");
        tolua_function(tolua_S,"getTextureFormat",lua_cocos2dx_backend_TextureBackend_getTextureFormat);
        tolua_function(tolua_S,"getTextureType",lua_cocos2dx_backend_TextureBackend_getTextureType);
        tolua_function(tolua_S,"updateSamplerDescriptor",lua_cocos2dx_backend_TextureBackend_updateSamplerDescriptor);
        tolua_function(tolua_S,"updateTextureDescriptor",lua_cocos2dx_backend_TextureBackend_updateTextureDescriptor);
        tolua_function(tolua_S,"getTextureUsage",lua_cocos2dx_backend_TextureBackend_getTextureUsage);
        tolua_function(tolua_S,"hasMipmaps",lua_cocos2dx_backend_TextureBackend_hasMipmaps);
        tolua_function(tolua_S,"generateMipmaps",lua_cocos2dx_backend_TextureBackend_generateMipmaps);
        tolua_function(tolua_S,"getBytes",lua_cocos2dx_backend_TextureBackend_getBytes);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureBackend).name();
    g_luaType[typeName] = "ccb.TextureBackend";
    g_typeCast["TextureBackend"] = "ccb.TextureBackend";
    return 1;
}

int lua_cocos2dx_backend_Texture2DBackend_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_getHeight'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:getHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_getHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture2DBackend_getWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_getWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_getWidth'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:getWidth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_getWidth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture2DBackend_updateData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_updateData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_updateData'", nullptr);
            return 0;
        }
        cobj->updateData(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateData",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_updateData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture2DBackend_updateCompressedData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedData'", nullptr);
            return 0;
        }
        cobj->updateCompressedData(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateCompressedData",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture2DBackend_updateSubData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_updateSubData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned char* arg5;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_updateSubData'", nullptr);
            return 0;
        }
        cobj->updateSubData(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateSubData",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_updateSubData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture2DBackend_updateCompressedSubData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedSubData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 7) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned int arg5;
        unsigned char* arg6;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 7,&arg5, "ccb.Texture2DBackend:updateCompressedSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedSubData'", nullptr);
            return 0;
        }
        cobj->updateCompressedSubData(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateCompressedSubData",argc, 7);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture2DBackend_updateCompressedSubData'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_backend_Texture2DBackend_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Texture2DBackend)");
    return 0;
}

int lua_register_cocos2dx_backend_Texture2DBackend(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.Texture2DBackend");
    tolua_cclass(tolua_S,"Texture2DBackend","ccb.Texture2DBackend","ccb.TextureBackend",nullptr);

    tolua_beginmodule(tolua_S,"Texture2DBackend");
        tolua_function(tolua_S,"getHeight",lua_cocos2dx_backend_Texture2DBackend_getHeight);
        tolua_function(tolua_S,"getWidth",lua_cocos2dx_backend_Texture2DBackend_getWidth);
        tolua_function(tolua_S,"updateData",lua_cocos2dx_backend_Texture2DBackend_updateData);
        tolua_function(tolua_S,"updateCompressedData",lua_cocos2dx_backend_Texture2DBackend_updateCompressedData);
        tolua_function(tolua_S,"updateSubData",lua_cocos2dx_backend_Texture2DBackend_updateSubData);
        tolua_function(tolua_S,"updateCompressedSubData",lua_cocos2dx_backend_Texture2DBackend_updateCompressedSubData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Texture2DBackend).name();
    g_luaType[typeName] = "ccb.Texture2DBackend";
    g_typeCast["Texture2DBackend"] = "ccb.Texture2DBackend";
    return 1;
}

int lua_cocos2dx_backend_TextureCubemapBackend_updateFaceData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureCubemapBackend* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureCubemapBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureCubemapBackend*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_TextureCubemapBackend_updateFaceData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::backend::TextureCubeFace arg0;
        void* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.TextureCubemapBackend:updateFaceData");

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_TextureCubemapBackend_updateFaceData'", nullptr);
            return 0;
        }
        cobj->updateFaceData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureCubemapBackend:updateFaceData",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_TextureCubemapBackend_updateFaceData'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_backend_TextureCubemapBackend_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextureCubemapBackend)");
    return 0;
}

int lua_register_cocos2dx_backend_TextureCubemapBackend(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.TextureCubemapBackend");
    tolua_cclass(tolua_S,"TextureCubemapBackend","ccb.TextureCubemapBackend","ccb.TextureBackend",nullptr);

    tolua_beginmodule(tolua_S,"TextureCubemapBackend");
        tolua_function(tolua_S,"updateFaceData",lua_cocos2dx_backend_TextureCubemapBackend_updateFaceData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureCubemapBackend).name();
    g_luaType[typeName] = "ccb.TextureCubemapBackend";
    g_typeCast["TextureCubemapBackend"] = "ccb.TextureCubemapBackend";
    return 1;
}

int lua_cocos2dx_backend_Device_newProgram(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Device* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Device",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Device*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Device_newProgram'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccb.Device:newProgram");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccb.Device:newProgram");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Device_newProgram'", nullptr);
            return 0;
        }
        cocos2d::backend::Program* ret = cobj->newProgram(arg0, arg1);
        object_to_luaval<cocos2d::backend::Program>(tolua_S, "ccb.Program",(cocos2d::backend::Program*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Device:newProgram",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Device_newProgram'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Device_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.Device",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Device_getInstance'", nullptr);
            return 0;
        }
        cocos2d::backend::Device* ret = cocos2d::backend::Device::getInstance();
        object_to_luaval<cocos2d::backend::Device>(tolua_S, "ccb.Device",(cocos2d::backend::Device*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.Device:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Device_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_backend_Device_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Device)");
    return 0;
}

int lua_register_cocos2dx_backend_Device(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.Device");
    tolua_cclass(tolua_S,"Device","ccb.Device","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Device");
        tolua_function(tolua_S,"newProgram",lua_cocos2dx_backend_Device_newProgram);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_backend_Device_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Device).name();
    g_luaType[typeName] = "ccb.Device";
    g_typeCast["Device"] = "ccb.Device";
    return 1;
}
TOLUA_API int register_all_cocos2dx_backend(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccb",0);
	tolua_beginmodule(tolua_S,"ccb");

	lua_register_cocos2dx_backend_ColorWriteMask(tolua_S);
	lua_register_cocos2dx_backend_TextureType(tolua_S);
	lua_register_cocos2dx_backend_PrimitiveType(tolua_S);
	lua_register_cocos2dx_backend_SamplerAddressMode(tolua_S);
	lua_register_cocos2dx_backend_ProgramState(tolua_S);
	lua_register_cocos2dx_backend_IndexFormat(tolua_S);
	lua_register_cocos2dx_backend_TextureBackend(tolua_S);
	lua_register_cocos2dx_backend_TextureCubemapBackend(tolua_S);
	lua_register_cocos2dx_backend_SamplerFilter(tolua_S);
	lua_register_cocos2dx_backend_TextureCubeFace(tolua_S);
	lua_register_cocos2dx_backend_VertexLayout(tolua_S);
	lua_register_cocos2dx_backend_BlendFactor(tolua_S);
	lua_register_cocos2dx_backend_Device(tolua_S);
	lua_register_cocos2dx_backend_VertexFormat(tolua_S);
	lua_register_cocos2dx_backend_VertexStepMode(tolua_S);
	lua_register_cocos2dx_backend_StencilOperation(tolua_S);
	lua_register_cocos2dx_backend_CompareFunction(tolua_S);
	lua_register_cocos2dx_backend_BufferUsage(tolua_S);
	lua_register_cocos2dx_backend_TextureUsage(tolua_S);
	lua_register_cocos2dx_backend_BufferType(tolua_S);
	lua_register_cocos2dx_backend_CullMode(tolua_S);
	lua_register_cocos2dx_backend_Winding(tolua_S);
	lua_register_cocos2dx_backend_PixelFormat(tolua_S);
	lua_register_cocos2dx_backend_Program(tolua_S);
	lua_register_cocos2dx_backend_BlendOperation(tolua_S);
	lua_register_cocos2dx_backend_ShaderStage(tolua_S);
	lua_register_cocos2dx_backend_Texture2DBackend(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}


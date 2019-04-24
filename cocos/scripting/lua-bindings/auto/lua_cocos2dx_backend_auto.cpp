#include "scripting/lua-bindings/auto/lua_cocos2dx_backend_auto.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
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
    g_luaType[typeName] = "ccbakend.BufferUsage";
    g_typeCast["BufferUsage"] = "ccbakend.BufferUsage";
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
    g_luaType[typeName] = "ccbakend.BufferType";
    g_typeCast["BufferType"] = "ccbakend.BufferType";
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
    g_luaType[typeName] = "ccbakend.ShaderStage";
    g_typeCast["ShaderStage"] = "ccbakend.ShaderStage";
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
    g_luaType[typeName] = "ccbakend.VertexFormat";
    g_typeCast["VertexFormat"] = "ccbakend.VertexFormat";
    return 1;
}


int lua_register_cocos2dx_backend_TextureFormat(lua_State* tolua_S)
{
    tolua_module(tolua_S, "TextureFormat", 0);
    tolua_beginmodule(tolua_S,"TextureFormat");
        tolua_constant(tolua_S, "NONE", 0);
        tolua_constant(tolua_S, "R8G8B8A8", 1);
        tolua_constant(tolua_S, "R8G8B8", 2);
        tolua_constant(tolua_S, "A8", 3);
        tolua_constant(tolua_S, "D24S8", 4);
        tolua_constant(tolua_S, "I8", 5);
        tolua_constant(tolua_S, "AI88", 6);
        tolua_constant(tolua_S, "RGBA4444", 7);
        tolua_constant(tolua_S, "RGB565", 8);
        tolua_constant(tolua_S, "RGB5A1", 9);
        tolua_constant(tolua_S, "MTL_B5G6R5", 10);
        tolua_constant(tolua_S, "MTL_BGR5A1", 11);
        tolua_constant(tolua_S, "MTL_ABGR4", 12);
        tolua_constant(tolua_S, "ETC1", 13);
        tolua_constant(tolua_S, "ATC_RGB", 14);
        tolua_constant(tolua_S, "ATC_EXPLICIT_ALPHA", 15);
        tolua_constant(tolua_S, "ATC_INTERPOLATED_ALPHA", 16);
        tolua_constant(tolua_S, "PVRTC2", 17);
        tolua_constant(tolua_S, "PVRTC2A", 18);
        tolua_constant(tolua_S, "PVRTC4", 19);
        tolua_constant(tolua_S, "PVRTC4A", 20);
        tolua_constant(tolua_S, "S3TC_DXT1", 21);
        tolua_constant(tolua_S, "S3TC_DXT3", 22);
        tolua_constant(tolua_S, "S3TC_DXT5", 23);
        tolua_constant(tolua_S, "SYSTEM_DEFAULT", 24);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::TextureFormat).name();
    g_luaType[typeName] = "ccbakend.TextureFormat";
    g_typeCast["TextureFormat"] = "ccbakend.TextureFormat";
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
    g_luaType[typeName] = "ccbakend.TextureUsage";
    g_typeCast["TextureUsage"] = "ccbakend.TextureUsage";
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
    g_luaType[typeName] = "ccbakend.IndexFormat";
    g_typeCast["IndexFormat"] = "ccbakend.IndexFormat";
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
    g_luaType[typeName] = "ccbakend.VertexStepMode";
    g_typeCast["VertexStepMode"] = "ccbakend.VertexStepMode";
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
    g_luaType[typeName] = "ccbakend.PrimitiveType";
    g_typeCast["PrimitiveType"] = "ccbakend.PrimitiveType";
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
    g_luaType[typeName] = "ccbakend.TextureType";
    g_typeCast["TextureType"] = "ccbakend.TextureType";
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
    g_luaType[typeName] = "ccbakend.SamplerAddressMode";
    g_typeCast["SamplerAddressMode"] = "ccbakend.SamplerAddressMode";
    return 1;
}


int lua_register_cocos2dx_backend_SamplerFilter(lua_State* tolua_S)
{
    tolua_module(tolua_S, "SamplerFilter", 0);
    tolua_beginmodule(tolua_S,"SamplerFilter");
        tolua_constant(tolua_S, "NEAREST", 0);
        tolua_constant(tolua_S, "LINEAR", 1);
        tolua_constant(tolua_S, "DONT_CARE", 2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::SamplerFilter).name();
    g_luaType[typeName] = "ccbakend.SamplerFilter";
    g_typeCast["SamplerFilter"] = "ccbakend.SamplerFilter";
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
    g_luaType[typeName] = "ccbakend.StencilOperation";
    g_typeCast["StencilOperation"] = "ccbakend.StencilOperation";
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
    g_luaType[typeName] = "ccbakend.CompareFunction";
    g_typeCast["CompareFunction"] = "ccbakend.CompareFunction";
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
    g_luaType[typeName] = "ccbakend.BlendOperation";
    g_typeCast["BlendOperation"] = "ccbakend.BlendOperation";
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
    g_luaType[typeName] = "ccbakend.BlendFactor";
    g_typeCast["BlendFactor"] = "ccbakend.BlendFactor";
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
    g_luaType[typeName] = "ccbakend.ColorWriteMask";
    g_typeCast["ColorWriteMask"] = "ccbakend.ColorWriteMask";
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
    g_luaType[typeName] = "ccbakend.CullMode";
    g_typeCast["CullMode"] = "ccbakend.CullMode";
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
    g_luaType[typeName] = "ccbakend.Winding";
    g_typeCast["Winding"] = "ccbakend.Winding";
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
    g_luaType[typeName] = "ccbakend.TextureCubeFace";
    g_typeCast["TextureCubeFace"] = "ccbakend.TextureCubeFace";
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getMaxVertexLocation",argc, 0);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getMaxFragmentLocation",argc, 0);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getFragmentShader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getFragmentShader'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccbakend.Program:getUniformLocation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Program_getUniformLocation'", nullptr);
            return 0;
        }
        cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
        uniformLocation_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getUniformLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getUniformLocation'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getActiveAttributes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getActiveAttributes'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Program",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Program:getVertexShader",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Program_getVertexShader'.",&tolua_err);
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
    tolua_usertype(tolua_S,"ccbakend.Program");
    tolua_cclass(tolua_S,"Program","ccbakend.Program","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Program");
        tolua_function(tolua_S,"getMaxVertexLocation",lua_cocos2dx_backend_Program_getMaxVertexLocation);
        tolua_function(tolua_S,"getMaxFragmentLocation",lua_cocos2dx_backend_Program_getMaxFragmentLocation);
        tolua_function(tolua_S,"getFragmentShader",lua_cocos2dx_backend_Program_getFragmentShader);
        tolua_function(tolua_S,"getUniformLocation",lua_cocos2dx_backend_Program_getUniformLocation);
        tolua_function(tolua_S,"getActiveAttributes",lua_cocos2dx_backend_Program_getActiveAttributes);
        tolua_function(tolua_S,"getVertexShader",lua_cocos2dx_backend_Program_getVertexShader);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Program).name();
    g_luaType[typeName] = "ccbakend.Program";
    g_typeCast["Program"] = "ccbakend.Program";
    return 1;
}

int lua_cocos2dx_backend_ProgramState_setUniform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_setUniform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::backend::UniformLocation arg0;
        const void* arg1;
        unsigned int arg2;

        ok &= luaval_to_uniformLocation(tolua_S, 2, arg0, "ccbakend.ProgramState:setUniform");

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccbakend.ProgramState:setUniform");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_setUniform'", nullptr);
            return 0;
        }
        cobj->setUniform(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:setUniform",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_setUniform'.",&tolua_err);
#endif

    return 0;
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
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
        cocos2d::backend::Texture* arg2;

        ok &= luaval_to_uniformLocation(tolua_S, 2, arg0, "ccbakend.ProgramState:setTexture");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccbakend.ProgramState:setTexture");

        ok &= luaval_to_object<cocos2d::backend::Texture>(tolua_S, 4, "ccbakend.Texture",&arg2, "ccbakend.ProgramState:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:setTexture",argc, 3);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
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
        object_to_luaval<cocos2d::backend::ProgramState>(tolua_S, "ccbakend.ProgramState",(cocos2d::backend::ProgramState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:clone",argc, 0);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
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

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccbakend.ProgramState:setParameterAutoBinding");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccbakend.ProgramState:setParameterAutoBinding");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_setParameterAutoBinding'", nullptr);
            return 0;
        }
        cobj->setParameterAutoBinding(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:setParameterAutoBinding",argc, 2);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
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
        object_to_luaval<cocos2d::backend::Program>(tolua_S, "ccbakend.Program",(cocos2d::backend::Program*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:getProgram",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_getProgram'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_ProgramState_getUniformLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_ProgramState_getUniformLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccbakend.ProgramState:getUniformLocation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_getUniformLocation'", nullptr);
            return 0;
        }
        cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
        uniformLocation_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:getUniformLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_ProgramState_getUniformLocation'.",&tolua_err);
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
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccbakend.ProgramState:ProgramState");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccbakend.ProgramState:ProgramState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_ProgramState_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::backend::ProgramState(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccbakend.ProgramState");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.ProgramState:ProgramState",argc, 2);
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
    tolua_usertype(tolua_S,"ccbakend.ProgramState");
    tolua_cclass(tolua_S,"ProgramState","ccbakend.ProgramState","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ProgramState");
        tolua_function(tolua_S,"new",lua_cocos2dx_backend_ProgramState_constructor);
        tolua_function(tolua_S,"setUniform",lua_cocos2dx_backend_ProgramState_setUniform);
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_backend_ProgramState_setTexture);
        tolua_function(tolua_S,"clone",lua_cocos2dx_backend_ProgramState_clone);
        tolua_function(tolua_S,"setParameterAutoBinding",lua_cocos2dx_backend_ProgramState_setParameterAutoBinding);
        tolua_function(tolua_S,"getProgram",lua_cocos2dx_backend_ProgramState_getProgram);
        tolua_function(tolua_S,"getUniformLocation",lua_cocos2dx_backend_ProgramState_getUniformLocation);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::ProgramState).name();
    g_luaType[typeName] = "ccbakend.ProgramState";
    g_typeCast["ProgramState"] = "ccbakend.ProgramState";
    return 1;
}

int lua_cocos2dx_backend_Texture_getTextureFormat(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_getTextureFormat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_getTextureFormat'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureFormat();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:getTextureFormat",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_getTextureFormat'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture_generateMipmaps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_generateMipmaps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_generateMipmaps'", nullptr);
            return 0;
        }
        cobj->generateMipmaps();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:generateMipmaps",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_generateMipmaps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture_updateSamplerDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_updateSamplerDescriptor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::SamplerDescriptor arg0;

        ok &= luaval_to_samplerDescriptor(tolua_S, 2, arg0, "ccbakend.Texture:updateSamplerDescriptor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_updateSamplerDescriptor'", nullptr);
            return 0;
        }
        cobj->updateSamplerDescriptor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:updateSamplerDescriptor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_updateSamplerDescriptor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture_getTextureUsage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_getTextureUsage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_getTextureUsage'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureUsage();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:getTextureUsage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_getTextureUsage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture_getTextureType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_getTextureType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_getTextureType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTextureType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:getTextureType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_getTextureType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_Texture_getBytes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.Texture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_Texture_getBytes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        bool arg4;
        std::function<void (const unsigned char *, int, int)> arg5;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccbakend.Texture:getBytes");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccbakend.Texture:getBytes");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccbakend.Texture:getBytes");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccbakend.Texture:getBytes");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccbakend.Texture:getBytes");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_Texture_getBytes'", nullptr);
            return 0;
        }
        cobj->getBytes(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.Texture:getBytes",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_Texture_getBytes'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_backend_Texture_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Texture)");
    return 0;
}

int lua_register_cocos2dx_backend_Texture(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccbakend.Texture");
    tolua_cclass(tolua_S,"Texture","ccbakend.Texture","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Texture");
        tolua_function(tolua_S,"getTextureFormat",lua_cocos2dx_backend_Texture_getTextureFormat);
        tolua_function(tolua_S,"generateMipmaps",lua_cocos2dx_backend_Texture_generateMipmaps);
        tolua_function(tolua_S,"updateSamplerDescriptor",lua_cocos2dx_backend_Texture_updateSamplerDescriptor);
        tolua_function(tolua_S,"getTextureUsage",lua_cocos2dx_backend_Texture_getTextureUsage);
        tolua_function(tolua_S,"getTextureType",lua_cocos2dx_backend_Texture_getTextureType);
        tolua_function(tolua_S,"getBytes",lua_cocos2dx_backend_Texture_getBytes);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::Texture).name();
    g_luaType[typeName] = "ccbakend.Texture";
    g_typeCast["Texture"] = "ccbakend.Texture";
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.VertexLayout",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:getVertexStepMode",argc, 0);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.VertexLayout",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:isValid",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_isValid'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_backend_VertexLayout_setAtrribute(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccbakend.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_backend_VertexLayout_setAtrribute'", nullptr);
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

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccbakend.VertexLayout:setAtrribute");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccbakend.VertexLayout:setAtrribute");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccbakend.VertexLayout:setAtrribute");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccbakend.VertexLayout:setAtrribute");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccbakend.VertexLayout:setAtrribute");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_setAtrribute'", nullptr);
            return 0;
        }
        cobj->setAtrribute(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:setAtrribute",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_setAtrribute'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.VertexLayout",0,&tolua_err)) goto tolua_lerror;
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
    if (argc == 2) 
    {
        unsigned int arg0;
        cocos2d::backend::VertexStepMode arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccbakend.VertexLayout:setLayout");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccbakend.VertexLayout:setLayout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_backend_VertexLayout_setLayout'", nullptr);
            return 0;
        }
        cobj->setLayout(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:setLayout",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_backend_VertexLayout_setLayout'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"ccbakend.VertexLayout",0,&tolua_err)) goto tolua_lerror;
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
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:getStride",argc, 0);
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
        tolua_pushusertype(tolua_S,(void*)cobj,"ccbakend.VertexLayout");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccbakend.VertexLayout:VertexLayout",argc, 0);
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
    tolua_usertype(tolua_S,"ccbakend.VertexLayout");
    tolua_cclass(tolua_S,"VertexLayout","ccbakend.VertexLayout","",nullptr);

    tolua_beginmodule(tolua_S,"VertexLayout");
        tolua_function(tolua_S,"new",lua_cocos2dx_backend_VertexLayout_constructor);
        tolua_function(tolua_S,"getVertexStepMode",lua_cocos2dx_backend_VertexLayout_getVertexStepMode);
        tolua_function(tolua_S,"isValid",lua_cocos2dx_backend_VertexLayout_isValid);
        tolua_function(tolua_S,"setAtrribute",lua_cocos2dx_backend_VertexLayout_setAtrribute);
        tolua_function(tolua_S,"setLayout",lua_cocos2dx_backend_VertexLayout_setLayout);
        tolua_function(tolua_S,"getStride",lua_cocos2dx_backend_VertexLayout_getStride);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::backend::VertexLayout).name();
    g_luaType[typeName] = "ccbakend.VertexLayout";
    g_typeCast["VertexLayout"] = "ccbakend.VertexLayout";
    return 1;
}
TOLUA_API int register_all_cocos2dx_backend(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccbackend",0);
	tolua_beginmodule(tolua_S,"ccbackend");

	lua_register_cocos2dx_backend_ColorWriteMask(tolua_S);
	lua_register_cocos2dx_backend_TextureType(tolua_S);
	lua_register_cocos2dx_backend_PrimitiveType(tolua_S);
	lua_register_cocos2dx_backend_SamplerAddressMode(tolua_S);
	lua_register_cocos2dx_backend_ProgramState(tolua_S);
	lua_register_cocos2dx_backend_IndexFormat(tolua_S);
	lua_register_cocos2dx_backend_TextureFormat(tolua_S);
	lua_register_cocos2dx_backend_SamplerFilter(tolua_S);
	lua_register_cocos2dx_backend_TextureCubeFace(tolua_S);
	lua_register_cocos2dx_backend_VertexLayout(tolua_S);
	lua_register_cocos2dx_backend_BlendFactor(tolua_S);
	lua_register_cocos2dx_backend_VertexFormat(tolua_S);
	lua_register_cocos2dx_backend_VertexStepMode(tolua_S);
	lua_register_cocos2dx_backend_Texture(tolua_S);
	lua_register_cocos2dx_backend_StencilOperation(tolua_S);
	lua_register_cocos2dx_backend_CompareFunction(tolua_S);
	lua_register_cocos2dx_backend_BufferUsage(tolua_S);
	lua_register_cocos2dx_backend_TextureUsage(tolua_S);
	lua_register_cocos2dx_backend_BufferType(tolua_S);
	lua_register_cocos2dx_backend_CullMode(tolua_S);
	lua_register_cocos2dx_backend_Winding(tolua_S);
	lua_register_cocos2dx_backend_Program(tolua_S);
	lua_register_cocos2dx_backend_BlendOperation(tolua_S);
	lua_register_cocos2dx_backend_ShaderStage(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}


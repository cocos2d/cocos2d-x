/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LuaBasicConversions.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

std::unordered_map<std::string, std::string>  g_luaType;
std::unordered_map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err)
{
    if (NULL == L || NULL == err || NULL == msg || 0 == strlen(msg))
        return;

    if (msg[0] == '#')
    {
        const char* expected = err->type;
        const char* provided = tolua_typename(L,err->index);
        if (msg[1]=='f')
        {
            int narg = err->index;
            if (err->array)
                CCLOG("%s\n     argument #%d is array of '%s'; array of '%s' expected.\n",msg+2,narg,provided,expected);
            else
                CCLOG("%s\n     argument #%d is '%s'; '%s' expected.\n",msg+2,narg,provided,expected);
        }
        else if (msg[1]=='v')
        {
            if (err->array)
                CCLOG("%s\n     value is array of '%s'; array of '%s' expected.\n",msg+2,provided,expected);
            else
                CCLOG("%s\n     value is '%s'; '%s' expected.\n",msg+2,provided,expected);
        }
    }
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int lua_isusertype (lua_State* L, int lo, const char* type);
#ifdef __cplusplus
}
#endif

bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def)
{
    if (def && lua_gettop(L)<abs(lo))
        return true;
    
    if (lua_isnil(L,lo) || lua_isusertype(L,lo,type))
        return true;
    
    return false;
}

bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned short)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}


bool luaval_to_int32(lua_State* L,int lo,int* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned char)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_boolean(lua_State* L,int lo,bool* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isboolean(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (bool)tolua_toboolean(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_number(lua_State* L,int lo,double* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_long_long(lua_State* L,int lo,long long* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (long long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_iscppstring(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = tolua_tocppstring(L,lo,NULL);
    }
    
    return ok;
}

bool luaval_to_point(lua_State* L,int lo,Point* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }

    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_physics_material(lua_State* L,int lo,PhysicsMaterial* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    
    if (ok)
    {
        lua_pushstring(L, "density");
        lua_gettable(L, lo);
        outValue->density = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "restitution");
        lua_gettable(L, lo);
        outValue->restitution = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "friction");
        lua_gettable(L, lo);
        outValue->friction = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue)
{
    return luaval_to_long(L, lo, reinterpret_cast<long*>(outValue));
}

bool luaval_to_long(lua_State* L,int lo, long* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_size(lua_State* L,int lo,Size* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "width");  /* L: paramStack key */
        lua_gettable(L,lo);/* L: paramStack paramStack[lo][key] */
        outValue->width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);/* L: paramStack*/
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_rect(lua_State* L,int lo,Rect* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L,lo);
        outValue->origin.x = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "y");
        lua_gettable(L,lo);
        outValue->origin.y = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "width");
        lua_gettable(L,lo);
        outValue->size.width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->size.height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_color4b(lua_State* L,int lo,Color4B* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if(ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_color4f(lua_State* L,int lo,Color4F* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_color3b(lua_State* L,int lo,Color3B* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_affinetransform(lua_State* L,int lo, AffineTransform* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "c");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "d");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "tx");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "ty");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    return ok;
}

bool luaval_to_fontdefinition(lua_State* L, int lo, FontDefinition* outValue )
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
#endif
    }
    
    if (ok)
    {
        // defaul values
        const char *            defautlFontName         = "Arial";
        const int               defaultFontSize         = 32;
        TextHAlignment          defaultTextAlignment    = TextHAlignment::LEFT;
        TextVAlignment          defaultTextVAlignment   = TextVAlignment::TOP;
        
        // by default shadow and stroke are off
        outValue->_shadow._shadowEnabled = false;
        outValue->_stroke._strokeEnabled = false;
        
        // white text by default
        outValue->_fontFillColor = Color3B::WHITE;
        
        lua_pushstring(L, "fontName");
        lua_gettable(L,lo);
        outValue->_fontName = tolua_tocppstring(L,lo,defautlFontName);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontSize");
        lua_gettable(L,lo);
        outValue->_fontSize = lua_isnil(L,-1) ? defaultFontSize : (int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontAlignmentH");
        lua_gettable(L,lo);
        outValue->_alignment = lua_isnil(L,-1) ? defaultTextAlignment : (TextHAlignment)(int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontAlignmentV");
        lua_gettable(L,lo);
        outValue->_vertAlignment = lua_isnil(L,-1) ? defaultTextVAlignment : (TextVAlignment)(int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontFillColor");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_color3b(L, -1, &outValue->_fontFillColor);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "fontDimensions");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_size(L, -1, &outValue->_dimensions);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "shadowEnabled");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_boolean(L, -1, &outValue->_shadow._shadowEnabled);
            if (outValue->_shadow._shadowEnabled)
            {
                // default shadow values
                outValue->_shadow._shadowOffset  = Size(5, 5);
                outValue->_shadow._shadowBlur    = 1;
                outValue->_shadow._shadowOpacity = 1;
            }
            
            lua_pushstring(L, "shadowOffset");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
                luaval_to_size(L, -1, &outValue->_shadow._shadowOffset);                
            }
            lua_pop(L,1);
            
            lua_pushstring(L, "shadowBlur");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
               outValue->_shadow._shadowBlur = (float)lua_tonumber(L,-1);
            }
            lua_pop(L,1);
            
            lua_pushstring(L, "shadowOpacity");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
                outValue->_shadow._shadowOpacity = lua_tonumber(L,-1);
            }
            lua_pop(L,1);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "strokeEnabled");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_boolean(L, -1, &outValue->_stroke._strokeEnabled);
            if (outValue->_stroke._strokeEnabled)
            {
                // default stroke values
                outValue->_stroke._strokeSize  = 1;
                outValue->_stroke._strokeColor = Color3B::BLUE;
                
                lua_pushstring(L, "strokeColor");
                lua_gettable(L,lo);
                if (!lua_isnil(L,-1))
                {
                     luaval_to_color3b(L, -1, &outValue->_stroke._strokeColor);
                }
                lua_pop(L,1);
                
                lua_pushstring(L, "strokeSize");
                lua_gettable(L,lo);
                if (!lua_isnil(L,-1))
                {
                    outValue->_stroke._strokeSize = (float)lua_tonumber(L,-1);
                }
                lua_pop(L,1);
            }
        }
        lua_pop(L,1);
    }

    
    return ok;
}

bool luaval_to_array(lua_State* L,int lo, Array** outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        if (len > 0)
        {
            Array* arr =  Array::createWithCapacity(len);
            if (NULL == arr)
                return false;
            
            for (int i = 0; i < len; i++)
            {
                lua_pushnumber(L,i + 1);
                lua_gettable(L,lo);
                if (lua_isnil(L,-1))
                {
                    lua_pop(L, 1);
                    continue;
                }
                
                if (lua_isuserdata(L, -1))
                {
                    Object* obj = static_cast<Object*>(tolua_tousertype(L, -1, NULL) );
                    if (NULL != obj)
                    {
                        arr->addObject(obj);
                    }
                }
                else if(lua_istable(L, -1))
                {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);
                    if (lua_isnil(L, -1) )
                    {
                        lua_pop(L,1);
                        Dictionary* dictVal = NULL;
                        if (luaval_to_dictionary(L,-1,&dictVal))
                        {
                            arr->addObject(dictVal);
                        }
                    }
                    else
                    {
                       lua_pop(L,1);
                       Array* arrVal = NULL;
                       if(luaval_to_array(L, -1, &arrVal))
                       {
                           arr->addObject(arrVal);
                       }
                    }
                }
                else if(lua_isstring(L, -1))
                {
                    std::string stringValue = "";
                    if(luaval_to_std_string(L, -1, &stringValue) )
                    {
                        arr->addObject(String::create(stringValue));
                    }
                }
                else if(lua_isboolean(L, -1))
                {
                    bool boolVal = false;
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        arr->addObject(Bool::create(boolVal));
                    }
                }
                else if(lua_isnumber(L, -1))
                {
                    arr->addObject(Double::create(tolua_tonumber(L, -1, 0)));
                }
                else
                {
                    CCASSERT(false, "not supported type");
                }
                lua_pop(L, 1);
            }
            
            *outValue = arr;
        }
    }
    
    return ok;
}

bool luaval_to_dictionary(lua_State* L,int lo, Dictionary** outValue)
{
    if (NULL == L || NULL == outValue)
        return  false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        bool boolVal = false;
        Dictionary* dict = NULL;
        lua_pushnil(L);                                             /* L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);
                continue;
            }
            
            if (NULL == dict)
            {
                dict = Dictionary::create();
            }
            
            if(luaval_to_std_string(L, -2, &stringKey))
            {
                if (lua_isuserdata(L, -1))
                {
                    Object* obj = static_cast<Object*>(tolua_tousertype(L, -1, NULL) );
                    if (NULL != obj)
                    {
                        //get the key to string
                        dict->setObject(obj, stringKey);
                    }
                }
                else if(lua_istable(L, -1))
                {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);
                    if (lua_isnil(L, -1) )
                    {
                        lua_pop(L,1);
                        Dictionary* dictVal = NULL;
                        if (luaval_to_dictionary(L,-1,&dictVal))
                        {
                            dict->setObject(dictVal,stringKey);
                        }
                    }
                    else
                    {
                        lua_pop(L,1);
                        Array* arrVal = NULL;
                        if(luaval_to_array(L, -1, &arrVal))
                        {
                            dict->setObject(arrVal,stringKey);
                        }
                    }
                }
                else if(lua_isstring(L, -1))
                {
                    if(luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict->setObject(String::create(stringValue), stringKey);
                    }
                }
                else if(lua_isboolean(L, -1))
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict->setObject(Bool::create(boolVal),stringKey);
                    }
                }
                else if(lua_isnumber(L, -1))
                {
                     dict->setObject(Double::create(tolua_tonumber(L, -1, 0)),stringKey);
                }
                else
                {
                    CCASSERT(false, "not supported type");
                }
            }
            
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
        
                                                                    /* L: lotable ..... */
    }
    
    return ok;
}

bool luaval_to_array_of_Point(lua_State* L,int lo,Point **points, int *numPoints)
{
    if (NULL == L)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;

    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        if (len > 0)
        {
            Point* array = (Point*)malloc(sizeof(Point) * len);
            if (NULL == array)
                return false;
            for (uint32_t i = 0; i < len; ++i)
            {
                lua_pushnumber(L,i + 1);
                lua_gettable(L,lo);
                if (!tolua_istable(L,-1, 0, &tolua_err))
                {
#if COCOS2D_DEBUG >=1
                    luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
                    lua_pop(L, 1);
                    free(array);
                    return false;
                }
                ok &= luaval_to_point(L, lua_gettop(L), &array[i]);
                if (!ok)
                {
                    lua_pop(L, 1);
                    free(array);
                    return false;
                }
                lua_pop(L, 1);
            }
            
            *numPoints = len;
            *points    = array;
        }
    }
    return ok;
}


bool luavals_variadic_to_array(lua_State* L,int argc, Array** ret)
{
    if (nullptr == L || argc == 0 )
        return false;
    
    bool ok = true;
    
    Array* array = Array::create();
    for (int i = 0; i < argc; i++)
    {
        double num = 0.0;
        if (lua_isnumber(L, i + 2))
        {
            ok &= luaval_to_number(L, i + 2, &num);
            if (!ok)
                break;
            
            array->addObject(Integer::create((int)num));
        }
        else if (lua_isstring(L, i + 2))
        {
            std::string str = lua_tostring(L, i + 2);
            array->addObject(String::create(str));
        }
        else if (lua_isuserdata(L, i + 2))
        {
            tolua_Error err;
            if (!tolua_isusertype(L, i + 2, "cc.Object", 0, &err))
            {
#if COCOS2D_DEBUG >=1
                luaval_to_native_err(L,"#ferror:",&err);
#endif
                ok = false;
                break;
            }
            Object* obj = static_cast<Object*>(tolua_tousertype(L, i + 2, nullptr));
            array->addObject(obj);
        }
    }
    
    *ret = array;
    
    return ok;
}

bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret)
{
    if (nullptr == L || argc == 0 )
        return false;
    
    for (int i = 0; i < argc; i++)
    {
        if(lua_istable(L, i + 2))
        {
            lua_pushnumber(L, 1);
            lua_gettable(L, i + 2);
            if (lua_isnil(L, -1) )
            {
                lua_pop(L,1);
                ValueMap dictVal;
                if (luaval_to_ccvaluemap(L, i + 2, &dictVal))
                {
                    ret->push_back(Value(dictVal));
                }
            }
            else
            {
                lua_pop(L,1);
                ValueVector arrVal;
                if(luaval_to_ccvaluevector(L, i + 2, &arrVal))
                {
                    ret->push_back(Value(arrVal));
                }
            }
        }
        else if(lua_isstring(L, i + 2))
        {
            std::string stringValue = "";
            if(luaval_to_std_string(L, i + 2, &stringValue) )
            {
                ret->push_back(Value(stringValue));
            }
        }
        else if(lua_isboolean(L, i + 2))
        {
            bool boolVal = false;
            if (luaval_to_boolean(L, i + 2, &boolVal))
            {
                ret->push_back(Value(boolVal));
            }
        }
        else if(lua_isnumber(L, i + 2))
        {
            ret->push_back(Value(tolua_tonumber(L, i + 2, 0)));
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
 }

bool luaval_to_ccvalue(lua_State* L, int lo, cocos2d::Value* ret)
{
    if ( nullptr == L || nullptr == ret)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    
    if (tolua_istable(L, lo, 0, &tolua_err))
    {
        lua_pushnumber(L,1);
        lua_gettable(L,lo);
        
        if (lua_isnil(L, -1) )                          /** if table[1] = nil,we don't think it is a pure array */
        {
            lua_pop(L,1);
            ValueMap dictVal;
            if (luaval_to_ccvaluemap(L, lo, &dictVal))
            {
                *ret = Value(dictVal);
            }
        }
        else
        {
            lua_pop(L,1);
            ValueVector arrVal;
            if (luaval_to_ccvaluevector(L, lo, &arrVal))
            {
                *ret = Value(arrVal);
            }
        }
    }
    else if (tolua_isstring(L, lo, 0, &tolua_err))
    {
        std::string stringValue = "";
        if (luaval_to_std_string(L, lo, &stringValue))
        {
             *ret = Value(stringValue);
        }
    }
    else if (tolua_isboolean(L, lo, 0, &tolua_err))
    {
        bool boolVal = false;
        if (luaval_to_boolean(L, lo, &boolVal))
        {
            *ret = Value(boolVal);
        }
    }
    else if (tolua_isnumber(L, lo, 0, &tolua_err))
    {
        *ret = Value(tolua_tonumber(L, lo, 0));
    }
    
    return ok;
}
bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret)
{
    if ( nullptr == L || nullptr == ret)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        bool boolVal = false;
        ValueMap& dict = *ret;
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }
            
            if(luaval_to_std_string(L, -2, &stringKey))
            {

                if(lua_istable(L, -1))
                {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);

                    if (lua_isnil(L, -1) )                          /** if table[1] = nil,we don't think it is a pure array */
                    {
                        lua_pop(L,1);
                        ValueMap dictVal;
                        if (luaval_to_ccvaluemap(L, -1, &dictVal))
                        {
                            dict[stringKey] = Value(dictVal);
                        }
                    }
                    else
                    {
                        lua_pop(L,1);
                        ValueVector arrVal;
                        if (luaval_to_ccvaluevector(L, -1, &arrVal))
                        {
                            dict[stringKey] = Value(arrVal);
                        }
                    }
                }
                else if(lua_isstring(L, -1))
                {
                    if(luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict[stringKey] = Value(stringValue);
                    }
                }
                else if(lua_isboolean(L, -1))
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict[stringKey] = Value(boolVal);
                    }
                }
                else if(lua_isnumber(L, -1))
                {
                    dict[stringKey] = Value(tolua_tonumber(L, -1, 0));
                }
                else
                {
                    CCASSERT(false, "not supported type");
                }
            }
            
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }
    
    return ok;
}
bool luaval_to_ccvaluemapintkey(lua_State* L, int lo, cocos2d::ValueMapIntKey* ret)
{
    if (nullptr == L || nullptr == ret)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        int intKey = 0;
        bool boolVal = false;
        ValueMapIntKey& dict = *ret;
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }
            
            if(luaval_to_std_string(L, -2, &stringKey))
            {
                intKey = atoi(stringKey.c_str());
                if(lua_istable(L, -1))
                {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);
                    
                    if (lua_isnil(L, -1) )                          /** if table[1] = nil,we don't think it is a pure array */
                    {
                        lua_pop(L,1);
                        ValueMap dictVal;
                        if (luaval_to_ccvaluemap(L, -1, &dictVal))
                        {
                            dict[intKey] = Value(dictVal);
                        }
                    }
                    else
                    {
                        lua_pop(L,1);
                        ValueVector arrVal;
                        if (luaval_to_ccvaluevector(L, -1, &arrVal))
                        {
                            dict[intKey] = Value(arrVal);
                        }
                    }
                }
                else if(lua_isstring(L, -1))
                {
                    if(luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict[intKey] = Value(stringValue);
                    }
                }
                else if(lua_isboolean(L, -1))
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict[intKey] = Value(boolVal);
                    }
                }
                else if(lua_isnumber(L, -1))
                {
                    dict[intKey] = Value(tolua_tonumber(L, -1, 0));
                }
                else
                {
                    CCASSERT(false, "not supported type");
                }
            }
            
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }
    
    return ok;
}
bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret)
{
    if (nullptr == L || nullptr == ret)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(L,i + 1);
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                lua_pop(L, 1);
                continue;
            }
            
            if(lua_istable(L, -1))
            {
                lua_pushnumber(L,1);
                lua_gettable(L,-2);
                if (lua_isnil(L, -1) )
                {
                    lua_pop(L,1);
                    ValueMap dictVal;
                    if (luaval_to_ccvaluemap(L, -1, &dictVal))
                    {
                        ret->push_back(Value(dictVal));
                    }
                }
                else
                {
                    lua_pop(L,1);
                    ValueVector arrVal;
                    if(luaval_to_ccvaluevector(L, -1, &arrVal))
                    {
                        ret->push_back(Value(arrVal));
                    }
                }
            }
            else if(lua_isstring(L, -1))
            {
                std::string stringValue = "";
                if(luaval_to_std_string(L, -1, &stringValue) )
                {
                    ret->push_back(Value(stringValue));
                }
            }
            else if(lua_isboolean(L, -1))
            {
                bool boolVal = false;
                if (luaval_to_boolean(L, -1, &boolVal))
                {
                    ret->push_back(Value(boolVal));
                }
            }
            else if(lua_isnumber(L, -1))
            {
                ret->push_back(Value(tolua_tonumber(L, -1, 0)));
            }
            else
            {
                CCASSERT(false, "not supported type");
            }
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        std::string value = "";
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isstring(L, -1))
            {
                ok = luaval_to_std_string(L, -1, &value);
                if(ok)
                    ret->push_back(value);
            }
            else
            {
                CCASSERT(false, "string type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((int)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCASSERT(false, "int type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

void points_to_luaval(lua_State* L,const Point* pt, int count)
{
    if (NULL  == L)
        return;
    lua_newtable(L);
    for (int i = 1; i <= count; ++i)
    {
        lua_pushnumber(L, i);
        point_to_luaval(L, pt[i-1]);
        lua_rawset(L, -3);
    }
}

void point_to_luaval(lua_State* L,const Point& pt)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) pt.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) pt.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void physics_material_to_luaval(lua_State* L,const PhysicsMaterial& pm)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "density");                       /* L: table key */
    lua_pushnumber(L, (lua_Number) pm.density);         /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "restitution");                   /* L: table key */
    lua_pushnumber(L, (lua_Number) pm.restitution);     /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "friction");                      /* L: table key */
    lua_pushnumber(L, (lua_Number) pm.friction);        /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void physics_raycastinfo_to_luaval(lua_State* L, const PhysicsRayCastInfo& info)
{
    if (NULL  == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    
    lua_pushstring(L, "shape");                       /* L: table key */
    PhysicsShape* shape = info.shape;
    if (shape == nullptr)
    {
        lua_pushnil(L);
    }else
    {
        std::string hashName = typeid(*shape).name();
        auto iter = g_luaType.find(hashName);
        std::string className = "";
        if(iter != g_luaType.end()){
            className = iter->second.c_str();
        } else {
            className = "PhysicsShape";
        }
        
        int ID =  (int)(shape->_ID);
        int* luaID = &(shape->_luaID);
        toluafix_pushusertype_ccobject(L, ID, luaID, (void*)shape,className.c_str());
    }
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "start");                   /* L: table key */
    point_to_luaval(L, info.start);
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "ended");                   /* L: table key */
    point_to_luaval(L, info.end);
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "contact");                   /* L: table key */
    point_to_luaval(L, info.contact);
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "normal");                   /* L: table key */
    point_to_luaval(L, info.normal);
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "fraction");                      /* L: table key */
    lua_pushnumber(L, (lua_Number) info.fraction);        /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void physics_contactdata_to_luaval(lua_State* L, const PhysicsContactData* data)
{
    if (nullptr  == L || nullptr == data)
        return;
    
    lua_newtable(L);                                    /* L: table */
    
    lua_pushstring(L, "points");
    points_to_luaval(L, data->points, data->count);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "normal");
    point_to_luaval(L, data->normal);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "POINT_MAX");
    lua_pushnumber(L, data->POINT_MAX);
    lua_rawset(L, -3);
}

void size_to_luaval(lua_State* L,const Size& sz)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void rect_to_luaval(lua_State* L,const Rect& rt)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.origin.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.origin.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.size.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.size.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void color4b_to_luaval(lua_State* L,const Color4B& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void color4f_to_luaval(lua_State* L,const Color4F& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void color3b_to_luaval(lua_State* L,const Color3B& cc)
{
    if (NULL  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void affinetransform_to_luaval(lua_State* L,const AffineTransform& inValue)
{
    if (NULL  == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "a");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.a);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.b);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "c");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.c);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "d");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "tx");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "ty");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void fontdefinition_to_luaval(lua_State* L,const FontDefinition& inValue)
{
    if (NULL == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "fontName");                      /* L: table key */
    tolua_pushcppstring(L, inValue._fontName);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontSize");                      /* L: table key */
    lua_pushnumber(L,(lua_Number)inValue._fontSize);                 /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontAlignmentH");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue._alignment);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontAlignmentV");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue._vertAlignment);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontFillColor");                             /* L: table key */
    color3b_to_luaval(L, inValue._fontFillColor);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontDimensions");                             /* L: table key */
    size_to_luaval(L, inValue._dimensions);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    //Shadow
    lua_pushstring(L, "shadowEnabled");                             /* L: table key */
    lua_pushboolean(L, inValue._shadow._shadowEnabled);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowOffset");                             /* L: table key */
    size_to_luaval(L, inValue._shadow._shadowOffset);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowBlur");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue._shadow._shadowBlur);  /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowOpacity");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue._shadow._shadowOpacity);  /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    //Stroke
    lua_pushstring(L, "shadowEnabled");                             /* L: table key */
    lua_pushboolean(L, inValue._stroke._strokeEnabled);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "strokeColor");                             /* L: table key */
    color3b_to_luaval(L, inValue._stroke._strokeColor);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "strokeSize");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue._stroke._strokeSize);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void array_to_luaval(lua_State* L,Array* inValue)
{
    lua_newtable(L);
    
    if (nullptr == L || nullptr == inValue)
        return;
    
    Object* obj = nullptr;
    
    std::string className = "";
    String* strVal = nullptr;
    Dictionary* dictVal = nullptr;
    Array* arrVal = nullptr;
    Double* doubleVal = nullptr;
    Bool* boolVal = nullptr;
    Float* floatVal = nullptr;
    Integer* intVal = nullptr;
    int indexTable = 1;
    
    CCARRAY_FOREACH(inValue, obj)
    {
        if (nullptr == obj)
            continue;
        
        std::string typeName = typeid(*obj).name();
        auto iter = g_luaType.find(typeName);
        if (g_luaType.end() != iter)
        {
            className = iter->second;
            if (nullptr != dynamic_cast<cocos2d::Object *>(obj))
            {
                lua_pushnumber(L, (lua_Number)indexTable);                
                int ID = (obj) ? (int)obj->_ID : -1;
                int* luaID = (obj) ? &obj->_luaID : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,className.c_str());
                lua_rawset(L, -3);
                obj->retain();
                ++indexTable;
            }
        }
        else if((strVal = dynamic_cast<cocos2d::String *>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushstring(L, strVal->getCString());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((dictVal = dynamic_cast<cocos2d::Dictionary*>(obj)))
        {
            dictionary_to_luaval(L, dictVal);
        }
        else if ((arrVal = dynamic_cast<cocos2d::Array*>(obj)))
        {
            array_to_luaval(L, arrVal);
        }
        else if ((doubleVal = dynamic_cast<Double*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushnumber(L, (lua_Number)doubleVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((floatVal = dynamic_cast<Float*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushnumber(L, (lua_Number)floatVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((intVal = dynamic_cast<Integer*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushinteger(L, (lua_Integer)intVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((boolVal = dynamic_cast<Bool*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushboolean(L, boolVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else
        {
            CCASSERT(false, "the type isn't suppored.");
        }
    }
}

void dictionary_to_luaval(lua_State* L, Dictionary* dict)
{
    lua_newtable(L);
    
    if (nullptr == L || nullptr == dict)
        return;
    
    DictElement* element = nullptr;
    
    std::string className = "";
    String* strVal = nullptr;
    Dictionary* dictVal = nullptr;
    Array* arrVal = nullptr;
    Double* doubleVal = nullptr;
    Bool* boolVal = nullptr;
    Float* floatVal = nullptr;
    Integer* intVal = nullptr;
    
    CCDICT_FOREACH(dict, element)
    {
        if (NULL == element)
            continue;
        
        std::string typeName = typeid(element->getObject()).name();
        
        auto iter = g_luaType.find(typeName);
        if (g_luaType.end() != iter)
        {
            className = iter->second;
            if ( nullptr != dynamic_cast<cocos2d::Object *>(element->getObject()))
            {
                lua_pushstring(L, element->getStrKey());
                int ID = (element->getObject()) ? (int)element->getObject()->_ID : -1;
                int* luaID = (element->getObject()) ? &(element->getObject()->_luaID) : NULL;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)element->getObject(),className.c_str());
                lua_rawset(L, -3);
                element->getObject()->retain();
            }
        }
        else if((strVal = dynamic_cast<cocos2d::String *>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushstring(L, strVal->getCString());
            lua_rawset(L, -3);
        }
        else if ((dictVal = dynamic_cast<cocos2d::Dictionary*>(element->getObject())))
        {
            dictionary_to_luaval(L, dictVal);
        }
        else if ((arrVal = dynamic_cast<cocos2d::Array*>(element->getObject())))
        {
            array_to_luaval(L, arrVal);
        }
        else if ((doubleVal = dynamic_cast<Double*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushnumber(L, (lua_Number)doubleVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((floatVal = dynamic_cast<Float*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushnumber(L, (lua_Number)floatVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((intVal = dynamic_cast<Integer*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushinteger(L, (lua_Integer)intVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((boolVal = dynamic_cast<Bool*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushboolean(L, boolVal->getValue());
            lua_rawset(L, -3);
        }
        else
        {
            CCASSERT(false, "the type isn't suppored.");
        }
    }
}

void ccvalue_to_luaval(lua_State* L,const cocos2d::Value& inValue)
{
    const Value& obj = inValue;
    switch (obj.getType())
    {
        case Value::Type::BOOLEAN:
            lua_pushboolean(L, obj.asBool());
            break;
        case Value::Type::FLOAT:
        case Value::Type::DOUBLE:
            lua_pushnumber(L, obj.asDouble());
            break;
        case Value::Type::INTEGER:
            lua_pushinteger(L, obj.asInt());
            break;
        case Value::Type::STRING:
            lua_pushstring(L, obj.asString().c_str());
            break;
        case Value::Type::VECTOR:
            ccvaluevector_to_luaval(L, obj.asValueVector());
            break;
        case Value::Type::MAP:
            ccvaluemap_to_luaval(L, obj.asValueMap());
            break;
        case Value::Type::INT_KEY_MAP:
            ccvaluemapintkey_to_luaval(L, obj.asIntKeyMap());
            break;
        default:
            break;
    }
}
void ccvaluemap_to_luaval(lua_State* L,const cocos2d::ValueMap& inValue)
{
    lua_newtable(L);
    
    if (nullptr == L)
        return;
    
    for (auto iter = inValue.begin(); iter != inValue.end(); ++iter)
    {
        std::string key = iter->first;
        const Value& obj = iter->second;
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushboolean(L, obj.asBool());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushnumber(L, obj.asDouble());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::INTEGER:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushinteger(L, obj.asInt());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::STRING:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushstring(L, obj.asString().c_str());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::VECTOR:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluevector_to_luaval(L, obj.asValueVector());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::MAP:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluemap_to_luaval(L, obj.asValueMap());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::INT_KEY_MAP:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluemapintkey_to_luaval(L, obj.asIntKeyMap());
                    lua_rawset(L, -3);
                }
                break;
            default:
                break;
        }
    }
}
void ccvaluemapintkey_to_luaval(lua_State* L, const cocos2d::ValueMapIntKey& inValue)
{
    lua_newtable(L);
    
    if (nullptr == L)
        return;
    
    for (auto iter = inValue.begin(); iter != inValue.end(); ++iter)
    {
        std::stringstream keyss;
        keyss << iter->first;
        std::string key = keyss.str();
        
        const Value& obj = iter->second;
        
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushboolean(L, obj.asBool());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushnumber(L, obj.asDouble());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::INTEGER:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushinteger(L, obj.asInt());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::STRING:
                {
                    lua_pushstring(L, key.c_str());
                    lua_pushstring(L, obj.asString().c_str());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::VECTOR:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluevector_to_luaval(L, obj.asValueVector());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::MAP:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluemap_to_luaval(L, obj.asValueMap());
                    lua_rawset(L, -3);
                }
                break;
            case Value::Type::INT_KEY_MAP:
                {
                    lua_pushstring(L, key.c_str());
                    ccvaluemapintkey_to_luaval(L, obj.asIntKeyMap());
                    lua_rawset(L, -3);
                }
                break;
            default:
                break;
        }
    }
}
void ccvaluevector_to_luaval(lua_State* L, const cocos2d::ValueVector& inValue)
{
    lua_newtable(L);
    
    if (nullptr == L)
        return;
    
    int index  = 1;
    for (const auto& obj : inValue)
    {
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    lua_pushboolean(L, obj.asBool());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    lua_pushnumber(L, obj.asDouble());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::INTEGER:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    lua_pushnumber(L, obj.asInt());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::STRING:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    lua_pushstring(L, obj.asString().c_str());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::VECTOR:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    ccvaluevector_to_luaval(L, obj.asValueVector());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::MAP:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    ccvaluemap_to_luaval(L, obj.asValueMap());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            case Value::Type::INT_KEY_MAP:
                {
                    lua_pushnumber(L, (lua_Number)index);
                    ccvaluemapintkey_to_luaval(L, obj.asIntKeyMap());
                    lua_rawset(L, -3);
                    ++index;
                }
                break;
            default:
                break;
        }
    }
}

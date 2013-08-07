/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org
 
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
extern "C" {
#include "tolua++.h"
}

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


bool luaval_to_int32(lua_State* L,int lo,int* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isboolean(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_iscppstring(L,lo,0,&tolua_err))
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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

bool luaval_to_size(lua_State* L,int lo,Size* outValue)
{
    if (NULL == L || NULL == outValue)
        return false;
    
    bool ok = true;
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
#if COCOS2D_DEBUG >=1
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
        luaval_to_native_err(L,"#ferror:",&tolua_err);
        ok = false;
    }
#endif
    
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
                    if(luaval_to_std_string(L, -2, &stringValue))
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
    if (NULL == L || NULL == inValue)
        return;
    
    if (0 == inValue->count() )
        return;
    
    Object* obj = NULL;
    lua_newtable(L);
    
    std::string className = "";
    int pos = 0;
    String* strVal = NULL;
    Dictionary* dictVal = NULL;
    Array* arrVal = NULL;
    Double* doubleVal = NULL;
    Bool* boolVal = NULL;
    Float* floatVal = NULL;
    Integer* intVal = NULL;
    
    CCARRAY_FOREACH(inValue, obj)
    {
        if (NULL == obj)
            continue;
        
        className = typeid(*obj).name();
        pos  = className.rfind(":");
        if (pos > 0 && pos + 1 < className.length() )
        {
            className = className.substr(pos + 1, std::string::npos);
            
            luaL_getmetatable(L, className.c_str()); /* stack: table mt */
            
            if (!lua_isnil(L, -1))
            {
                lua_pop(L, 1);
                tolua_pushusertype(L, (void*)obj, className.c_str());
            }
            else
            {
                lua_pop(L, -1);
                if((strVal = dynamic_cast<cocos2d::String *>(obj)))
                {
                    lua_pushstring(L, strVal->getCString());
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
                    lua_pushnumber(L, (lua_Number)doubleVal->getValue());
                }
                else if ((floatVal = dynamic_cast<Float*>(obj)))
                {
                    lua_pushnumber(L, (lua_Number)floatVal->getValue());
                }
                else if ((intVal = dynamic_cast<Integer*>(obj)))
                {
                    lua_pushinteger(L, (lua_Integer)intVal->getValue());
                }
                else if ((boolVal = dynamic_cast<Bool*>(obj)))
                {
                    lua_pushboolean(L, boolVal->getValue());
                } else
                {
                    CCASSERT(false, "the type isn't suppored.");
                }
            }
        }
    }
}

void dictionary_to_luaval(lua_State* L, Dictionary* dict)
{
    if (NULL == L || NULL == dict)
        return;
    
    if (0 == dict->count() )
        return;
    
    DictElement* element = NULL;
    lua_newtable(L);
    
    std::string className = "";
    int pos = 0;
    String* strVal = NULL;
    Dictionary* dictVal = NULL;
    Array* arrVal = NULL;
    Double* doubleVal = NULL;
    Bool* boolVal = NULL;
    Float* floatVal = NULL;
    Integer* intVal = NULL;
    Object* obj     = NULL;
    
    CCDICT_FOREACH(dict, element)
    {
        if (NULL == element)
            continue;
        
        className = typeid(*element).name();
        pos  = className.rfind(":");
        if (pos > 0 && pos + 1 < className.length() )
        {
            obj = element->getObject();
            if (NULL == obj)
                continue;
            
            className = className.substr(pos + 1, std::string::npos);
            
            luaL_getmetatable(L, className.c_str()); /* stack: table mt */
            if (!lua_isnil(L, -1))
            {
                lua_pop(L, 1);
                tolua_pushusertype(L, (void*)obj, className.c_str());
            }
            else
            {
                lua_pop(L, -1);
                if((strVal = dynamic_cast<cocos2d::String *>(obj)))
                {
                    lua_pushstring(L, element->getStrKey());
                    lua_pushstring(L, strVal->getCString());
                    lua_rawset(L, -3);
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
                    lua_pushstring(L, element->getStrKey());
                    lua_pushnumber(L, (lua_Number)doubleVal->getValue());
                    lua_rawset(L, -3);
                }
                else if ((floatVal = dynamic_cast<Float*>(obj)))
                {
                    lua_pushstring(L, element->getStrKey());
                    lua_pushnumber(L, (lua_Number)floatVal->getValue());
                    lua_rawset(L, -3);
                }
                else if ((intVal = dynamic_cast<Integer*>(obj)))
                {
                    lua_pushstring(L, element->getStrKey());
                    lua_pushinteger(L, (lua_Integer)intVal->getValue());
                    lua_rawset(L, -3);
                }
                else if ((boolVal = dynamic_cast<Bool*>(obj)))
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
    }
}

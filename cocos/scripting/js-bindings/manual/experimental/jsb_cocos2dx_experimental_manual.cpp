/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#include "jsb_cocos2dx_experimental_manual.h"
#include "cocos2d_specifics.hpp"
#include "2d/SpritePolygon.h"

bool jsval_to_vector_vec2(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::Vec2>* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);
    ret->reserve(len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            cocos2d::Vec2 vec2;
            ok &= jsval_to_vector2(cx, value, &vec2);
            ret->push_back(vec2);
        }
    }
    return ok;
}

bool jsval_to_vector_unsigned_short(JSContext* cx, JS::HandleValue v, std::vector<unsigned short>* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);
    ret->reserve(len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            unsigned short index;
            ok &= jsval_to_uint16(cx, value, &index);
            ret->push_back(index);
        }
    }
    return ok;
}

bool jsval_to_cctex2f(JSContext* cx, JS::HandleValue vp, cocos2d::Tex2F* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    double x, y;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    !isnan(x) && !isnan(y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->u = (GLfloat)x;
    ret->v = (GLfloat)y;
    return true;
}

bool jsval_to_v3fc4bt2f(JSContext* cx, JS::HandleValue v, cocos2d::V3F_C4B_T2F* ret)
{
    JS::RootedObject object(cx, v.toObjectOrNull());
    
    cocos2d::Vec3 v3;
    cocos2d::Color4B color;
    cocos2d::Tex2F t2;
    
    JS::RootedValue jsv3(cx);
    JS::RootedValue jscolor(cx);
    JS::RootedValue jst2(cx);
    
    bool ok = JS_GetProperty(cx, object, "v3f", &jsv3) &&
        JS_GetProperty(cx, object, "c4b", &jscolor) &&
        JS_GetProperty(cx, object, "t2f", &jst2) &&
        jsval_to_vector3(cx, jsv3, &v3) &&
        jsval_to_cccolor4b(cx, jscolor, &color) &&
        jsval_to_cctex2f(cx, jst2, &t2);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->vertices = v3;
    ret->colors = color;
    ret->texCoords = t2;
    return true;
}

bool jsval_to_vector_v3fc4bt2f(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::V3F_C4B_T2F>* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);
    ret->reserve(len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            cocos2d::V3F_C4B_T2F vert;
            ok &= jsval_to_v3fc4bt2f(cx, value, &vert);
            ret->push_back(vert);
        }
    }
    return ok;
}

bool js_cocos2dx_SpritePolygon_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 1)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::string file;
        bool ok = jsval_to_std_string(cx, args.get(0), &file);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_SpritePolygon_create : Error processing arguments");
        
        auto sprite = cocos2d::experimental::SpritePolygon::create(file);
        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::SpritePolygon>(cx, sprite);
        JS::RootedValue ret(cx, OBJECT_TO_JSVAL(jsProxy->obj));
        
        args.rval().set(ret);
        return true;
    }
    
    
    if(argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::string file;
        std::vector<cocos2d::Vec2> verts;
        bool ok = jsval_to_std_string(cx, args.get(0), &file);
        ok &= jsval_to_vector_vec2(cx, args.get(1), &verts);
        
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_SpritePolygon_create : Error processing arguments");
        
        auto sprite = cocos2d::experimental::SpritePolygon::create(file, verts);
        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::SpritePolygon>(cx, sprite);
        JS::RootedValue ret(cx, OBJECT_TO_JSVAL(jsProxy->obj));
        
        args.rval().set(ret);
        return true;

    }
    
    if(argc == 3)
    {
        do
        {
            JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
            std::string file;
            std::vector<cocos2d::Vec2> verts;
            std::vector<unsigned short> indices;
            
            bool ok = jsval_to_std_string(cx, args.get(0), &file);
            ok &= jsval_to_vector_vec2(cx, args.get(1), &verts);
            ok &= jsval_to_vector_unsigned_short(cx, args.get(2), &indices);
            
            if(!ok)
                break;
            
            auto sprite = cocos2d::experimental::SpritePolygon::create(file, verts, indices);
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::SpritePolygon>(cx, sprite);
            JS::RootedValue ret(cx, OBJECT_TO_JSVAL(jsProxy->obj));
            
            args.rval().set(ret);
            return true;
        }while (0);

        do
        {
            JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
            std::string file;
            std::vector<cocos2d::V3F_C4B_T2F> verts;
            std::vector<unsigned short> indices;
            
            bool ok = jsval_to_std_string(cx, args.get(0), &file);
            ok &= jsval_to_vector_v3fc4bt2f(cx, args.get(1), &verts);
            ok &= jsval_to_vector_unsigned_short(cx, args.get(2), &indices);
            
            if(!ok)
                break;
            
            auto sprite = cocos2d::experimental::SpritePolygon::create(file, verts, indices);
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::SpritePolygon>(cx, sprite);
            JS::RootedValue ret(cx, OBJECT_TO_JSVAL(jsProxy->obj));
            
            args.rval().set(ret);
            return true;
        }while(0);
        
        JS_ReportError(cx, "js_cocos2dx_SpritePolygon_create : Error processing arguments");
    }
    
    JS_ReportError(cx, "js_cocos2dx_SpritePolygon_create : wrong number of arguments: %d", argc);
    return false;
}

void register_all_cocos2dx_experimental_manual(JSContext *cx, JS::HandleObject global)
{

    JS::RootedObject ccObj(cx);
    get_or_create_js_obj(cx, global, "ccexp", &ccObj);
    
    JS::RootedValue tmpVal(cx);
    JS_GetProperty(cx, ccObj, "SpritePolygon", &tmpVal);
    JS::RootedObject tmpObj(cx, tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_SpritePolygon_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);

}
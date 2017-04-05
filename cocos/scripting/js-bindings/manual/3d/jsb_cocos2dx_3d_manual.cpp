/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#include "scripting/js-bindings/manual/3d/jsb_cocos2dx_3d_manual.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/auto/jsb_cocos2dx_3d_auto.hpp"
#include "3d/CCAnimate3D.h"
#include "3d/CCBundle3D.h"
#include "3d/CCMesh.h"
#include "3d/CCSprite3D.h"
#include "renderer/CCTextureCube.h"

using namespace cocos2d;

class JSB_HeapValueWrapper{
public:
    JSB_HeapValueWrapper(JSContext* cx, JS::HandleValue value)
    :_cx(cx)
    {
        _data = value;
        js_add_object_root(value);
    }

    ~JSB_HeapValueWrapper(){
        JS::RootedValue value(_cx, _data);
        js_remove_object_root(value);
    }

    jsval get(){
        return _data;
    }
private:
    JSContext* _cx;
    JS::Heap<JS::Value> _data;
};

static bool js_cocos2dx_Sprite3D_createAsync(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if(argc == 4 || argc == 5)
    {
        std::string modelPath;
        jsval_to_std_string(cx, args.get(0), &modelPath);

        std::function<void(Sprite3D*, void*)> callback;
        JS::RootedValue targetVal(cx, args.get(argc == 4 ? 2 : 3));
        JS::RootedObject target(cx, targetVal.toObjectOrNull());
        JS::RootedValue fval(cx, args.get(argc == 4 ? 1 : 2));
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, target, fval));
        auto lambda = [=](Sprite3D* larg0, void* larg1) -> void{
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            jsval largv[2];
            largv[0] = OBJECT_TO_JSVAL(js_get_or_create_jsobject<Sprite3D>(cx, larg0));
            JSB_HeapValueWrapper* v = (JSB_HeapValueWrapper*)larg1;
            JS::RootedValue dataVal(cx, v->get());
            largv[1] = dataVal;

            JS::RootedValue rval(cx);
		    bool ok = func->invoke(2, largv, &rval);
		    if (!ok && JS_IsExceptionPending(cx)) {
		        JS_ReportPendingException(cx);
		    }

            delete v;
        };
        callback = lambda;

        JSB_HeapValueWrapper* data = new (std::nothrow) JSB_HeapValueWrapper(cx, args.get(argc == 4 ? 3 : 4));

        if(argc == 4)
            cocos2d::Sprite3D::createAsync(modelPath, callback, data);
        else
        {
            std::string texturePath;
            jsval_to_std_string(cx, args.get(1), &texturePath);
            cocos2d::Sprite3D::createAsync(modelPath, texturePath, callback, data);
        }
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool js_cocos2dx_Sprite3D_getAABB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFaceEnabled : Invalid Native Object");
    if(argc == 0)
    {
        cocos2d::AABB aabb = cobj->getAABB();

        JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
        JS::RootedValue min(cx, vector3_to_jsval(cx, aabb._min));
        JS::RootedValue max(cx, vector3_to_jsval(cx, aabb._max));

        bool ok = JS_DefineProperty(cx, tmp, "min", min, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "max", max, JSPROP_ENUMERATE | JSPROP_PERMANENT);

        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFaceEnabled : Error processing arguments");

        args.rval().set(OBJECT_TO_JSVAL(tmp));
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool js_cocos2dx_Mesh_getMeshVertexAttribute(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getMeshVertexAttribute : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_getMeshVertexAttribute : Error processing arguments");
        const cocos2d::MeshVertexAttrib ret = cobj->getMeshVertexAttribute(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = meshVertexAttrib_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getMeshVertexAttribute : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_cocos2dx_CCTextureCube_setTexParameters(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    TextureCube* cobj = (TextureCube*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)

    if (argc == 4)
    {
        bool ok = true;

        GLuint arg0, arg1, arg2, arg3;

        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        ok &= jsval_to_uint32(cx, args.get(3), &arg3);

        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

        Texture2D::TexParams param = { arg0, arg1, arg2, arg3 };

        cobj->setTexParameters(param);

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}

bool jsval_to_DetailMap(JSContext* cx, JS::HandleValue v, Terrain::DetailMap* ret)
{
    JS::RootedObject jsobj(cx, v.toObjectOrNull());

    JS::RootedValue js_file(cx);
    JS::RootedValue js_size(cx);

    std::string file;
    double size;

    bool ok = JS_GetProperty(cx, jsobj, "file", &js_file) &&
            JS_GetProperty(cx, jsobj, "size", &js_size) &&
            jsval_to_std_string(cx, js_file, &file) &&
            JS::ToNumber(cx, js_size, &size);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    ret->_detailMapSrc = file;
    ret->_detailMapSize = size;

    return true;
}

bool jsval_to_TerrainData(JSContext* cx, JS::HandleValue v, Terrain::TerrainData* ret)
{
    JS::RootedObject jsobj(cx, v.toObjectOrNull());

    JS::RootedValue js_heightMap(cx);
    JS::RootedValue js_alphaMap(cx);
    JS::RootedValue js_chunkSize(cx);
    JS::RootedValue js_mapHeight(cx);
    JS::RootedValue js_mapScale(cx);
    JS::RootedValue js_detailMap(cx);

    std::string heightMap, alphaMap;
    Size chunkSize;
    double mapScale, mapHeight;

    bool ok = true;
    ok &= JS_GetProperty(cx, jsobj, "heightMap", &js_heightMap) &&
        JS_GetProperty(cx, jsobj, "alphaMap", &js_alphaMap) &&
        JS_GetProperty(cx, jsobj, "chunkSize", &js_chunkSize) &&
        JS_GetProperty(cx, jsobj, "mapHeight", &js_mapHeight) &&
        JS_GetProperty(cx, jsobj, "mapScale", &js_mapScale) &&
        JS_GetProperty(cx, jsobj, "detailMap", &js_detailMap) &&
        jsval_to_std_string(cx, js_heightMap, &heightMap) &&
        jsval_to_std_string(cx, js_alphaMap, &alphaMap) &&
        jsval_to_ccsize(cx, js_chunkSize, &chunkSize) &&
        JS::ToNumber(cx, js_mapScale, &mapScale) &&
        JS::ToNumber(cx, js_mapHeight, &mapHeight);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    ret->_heightMapSrc = heightMap.c_str();
    char* tmp = (char*)malloc(sizeof(char) * (alphaMap.size() + 1));
    strcpy(tmp, alphaMap.c_str());
    tmp[alphaMap.size()] = '\0';
    ret->_alphaMapSrc = tmp;
    ret->_chunkSize = chunkSize;
    ret->_mapHeight = mapHeight;
    ret->_mapScale = mapScale;
    ret->_skirtHeightRatio = 1;

    JS::RootedObject jsobj_detailMap(cx, js_detailMap.toObjectOrNull());
    uint32_t length = 0;
    JS_GetArrayLength(cx, jsobj_detailMap, &length);
    for(uint32_t i = 0; i < length; ++i)
    {
        JS::RootedValue element(cx);
        JS_GetElement(cx, jsobj_detailMap, i, &element);

        Terrain::DetailMap dm;
        jsval_to_DetailMap(cx, element, &dm);
        ret->_detailMaps[i] = dm;
    }
    ret->_detailMapAmount = length;

    return true;
}

bool js_cocos2dx_Terrain_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if(argc == 1 || argc == 2)
    {
        bool ok = true;
        Terrain* ret = nullptr;

        Terrain::TerrainData arg0;
        ok &= jsval_to_TerrainData(cx, args.get(0), &arg0);
        if(argc == 1)
        {
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            ret = Terrain::create(arg0);
        }
        else if(argc == 2)
        {
            Terrain::CrackFixedType arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t*)&arg1);
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            ret = Terrain::create(arg0, arg1);
        }

        args.rval().set(OBJECT_TO_JSVAL(js_get_or_create_jsobject<Terrain>(cx, ret)));
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

jsval std_vector_vec3_to_jsval(JSContext* cx, const std::vector<cocos2d::Vec3>& triangles)
{
    JS::RootedObject jsarr(cx, JS_NewArrayObject(cx, triangles.size()));

    uint32_t i = 0;
    for(auto iter = triangles.begin(); iter != triangles.end(); ++iter)
    {
        JS::RootedValue element(cx, vector3_to_jsval(cx, *iter));
        JS_SetElement(cx, jsarr, i, element);
        ++i;
    }

    return OBJECT_TO_JSVAL(jsarr);
}

bool js_cocos2dx_Bundle3D_getTrianglesList(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 1)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        std::string path;
        bool ok = jsval_to_std_string(cx, args.get(0), &path);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

        std::vector<cocos2d::Vec3> triangles = cocos2d::Bundle3D::getTrianglesList(path);

        JS::RootedValue ret(cx, std_vector_vec3_to_jsval(cx, triangles));
        args.rval().set(ret);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool js_cocos2dx_Terrain_getHeightData(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 0)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_Terrain_getHeightData : Invalid Native Object");

        auto data = cobj->getHeightData();

        args.rval().set(std_vector_float_to_jsval(cx, data));
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

// this code cannot be automated since it must use
// get_or_create_jsobject instead of create_jsobject
// since Animation3D::create() might return an existing copy
// since it caches them
bool js_cocos2dx_3d_Animation3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animation3D_create : Error processing arguments");

        auto ret = cocos2d::Animation3D::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animation3D>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_get_or_create_jsobject(cx, ret, typeClass, "cocos2d::Animation3D"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animation3D_create : Error processing arguments");

        auto ret = cocos2d::Animation3D::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animation3D>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_get_or_create_jsobject(cx, ret, typeClass, "cocos2d::Animation3D"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Animation3D_create : wrong number of arguments");
    return false;
}

void register_all_cocos2dx_3d_manual(JSContext *cx, JS::HandleObject global)
{
    JS::RootedValue tmpVal(cx);
    JS::RootedObject ccObj(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &ccObj);

    JS_GetProperty(cx, ccObj, "Sprite3D", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "createAsync", js_cocos2dx_Sprite3D_createAsync, 4, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Terrain", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_Terrain_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Animation3D", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_3d_Animation3D_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Bundle3D", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "getTrianglesList", js_cocos2dx_Bundle3D_getTrianglesList, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_Sprite3D_prototype);
    JS_DefineFunction(cx, tmpObj, "getAABB", js_cocos2dx_Sprite3D_getAABB, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_Mesh_prototype);
    JS_DefineFunction(cx, tmpObj, "getMeshVertexAttribute", js_cocos2dx_Mesh_getMeshVertexAttribute, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_TextureCube_prototype);
    JS_DefineFunction(cx, tmpObj, "setTexParameters", js_cocos2dx_CCTextureCube_setTexParameters, 4, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_Terrain_prototype);
    JS_DefineFunction(cx, tmpObj, "getHeightData", js_cocos2dx_Terrain_getHeightData, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

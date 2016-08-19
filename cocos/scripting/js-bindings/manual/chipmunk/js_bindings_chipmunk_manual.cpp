/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "jsapi.h"
#include "jsfriendapi.h"
#include "extensions/cocos-ext.h"
#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#ifdef JSB_INCLUDE_CHIPMUNK

#include "scripting/js-bindings/manual/chipmunk/js_bindings_chipmunk_manual.h"
#include "scripting/js-bindings/manual/js_manual_conversions.h"

USING_NS_CC_EXT;
// Function declarations
void static freeSpaceChildren(cpSpace *space);

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

#pragma mark - conversions

/*
 * PhysicsSprite
 */
#pragma mark - PhysicsSprite

JSClass* JSPROXY_CCPhysicsSprite_class = NULL;
JSObject* JSPROXY_CCPhysicsSprite_object = NULL;

// Arguments:
// Ret value: BOOL (b)
bool JSPROXY_CCPhysicsSprite_isDirty(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    if (real->isDirty()) {
        args.rval().set(JSVAL_TRUE);
    }
    else args.rval().set(JSVAL_FALSE);
    return true;
}

// Arguments:
// Ret value: cpBody* (N/A)
bool JSPROXY_CCPhysicsSprite_getCPBody(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)
    cpBody* ret_val = nullptr;

    ret_val = real->getCPBody();
    JS::RootedObject bodyProto(cx, JSB_cpBody_object);
    jsval ret_jsval = c_class_to_jsval( cx, ret_val, bodyProto, JSB_cpBody_class, "cpBody" );
    args.rval().set(ret_jsval);

    return true;
}

// Arguments:
// Ret value: BOOL (b)
bool JSPROXY_CCPhysicsSprite_ignoreBodyRotation(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    bool ret_val;

    ret_val = real->isIgnoreBodyRotation();
    args.rval().set(BOOLEAN_TO_JSVAL(ret_val));
    return true;
}

// Arguments: cpBody*
// Ret value: void (None)
bool JSPROXY_CCPhysicsSprite_setCPBody_(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    bool ok = true;
    cpBody* arg0 = nullptr;

    ok &= jsval_to_opaque( cx, args.get(0), (void**)&arg0 );
    if( ! ok ) return false;

    real->setCPBody((cpBody*)arg0);
    args.rval().setUndefined();
    return true;
}

// Arguments: BOOL
// Ret value: void (None)
bool JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PhysicsSprite* real = (PhysicsSprite *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    bool arg0 = JS::ToBoolean( args.get(0) );

    real->setIgnoreBodyRotation((bool)arg0);
    args.rval().setUndefined();
    return true;
}

/*
 * PhysicsDebugNode
 */
//#pragma mark - PhysicsDebugNode

JSClass* JSB_CCPhysicsDebugNode_class = NULL;
JSObject* JSB_CCPhysicsDebugNode_object = NULL;
extern JSObject *js_cocos2dx_CCDrawNode_prototype;

// Constructor

// Arguments: cpSpace*
// Ret value: PhysicsDebugNode* (o)
bool JSB_CCPhysicsDebugNode_debugNodeForCPSpace__static(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cpSpace* arg0 = nullptr;

    ok &= jsval_to_opaque( cx, args.get(0), (void**)&arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    PhysicsDebugNode* ret = PhysicsDebugNode::create(arg0);
    JS::RootedValue jsret(cx);
    if (ret) {
        js_type_class_t *typeClass = js_get_type_from_native<PhysicsDebugNode>(ret);
        jsret.set(OBJECT_TO_JSVAL(jsb_ref_autoreleased_get_or_create_jsobject(cx, ret, typeClass, "cocos2d::extension::PhysicsDebugNode")));
    } else {
        jsret.set(JS::NullValue());
    }
    args.rval().set(jsret);

    return true;
}

// Arguments: cpSpace*
// Ret value: void (None)
bool JSB_CCPhysicsDebugNode_setSpace_(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    PhysicsDebugNode* real = (PhysicsDebugNode *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    bool ok = true;
    cpSpace* arg0 = nullptr;

    ok &= jsval_to_opaque( cx, args.get(0), (void**)&arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    real->setSpace(arg0);
    args.rval().setUndefined();
    return true;
}

// Arguments:
// Ret value: cpSpace* (N/A)
bool JSB_CCPhysicsDebugNode_space(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
    PhysicsDebugNode* real = (PhysicsDebugNode *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    cpSpace* ret_val;
    ret_val = real->getSpace();
    jsval ret_jsval = opaque_to_jsval( cx, ret_val );
    args.rval().set(ret_jsval);

    return true;
}

bool JSB_CCPhysicsDebugNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    PhysicsDebugNode* cobj = new (std::nothrow) PhysicsDebugNode();

    js_type_class_t *typeClass = js_get_type_from_native<PhysicsDebugNode>(cobj);
    JS::RootedObject obj(cx, jsb_ref_get_or_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::PhysicsDebugNode"));
    JS::RootedValue retVal(cx, OBJECT_TO_JSVAL(obj));
    args.rval().set(retVal);

    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void JSB_CCPhysicsDebugNode_createClass(JSContext *cx, JS::HandleObject globalObj, const char* name )
{
    JSB_CCPhysicsDebugNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    JSB_CCPhysicsDebugNode_class->name = name;
    JSB_CCPhysicsDebugNode_class->addProperty = JS_PropertyStub;
    JSB_CCPhysicsDebugNode_class->delProperty = JS_DeletePropertyStub;
    JSB_CCPhysicsDebugNode_class->getProperty = JS_PropertyStub;
    JSB_CCPhysicsDebugNode_class->setProperty = JS_StrictPropertyStub;
    JSB_CCPhysicsDebugNode_class->enumerate = JS_EnumerateStub;
    JSB_CCPhysicsDebugNode_class->resolve = JS_ResolveStub;
    JSB_CCPhysicsDebugNode_class->convert = JS_ConvertStub;
    JSB_CCPhysicsDebugNode_class->flags = 0;

    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("_setSpace", JSB_CCPhysicsDebugNode_setSpace_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("getSpace", JSB_CCPhysicsDebugNode_space, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("_create", JSB_CCPhysicsDebugNode_debugNodeForCPSpace__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FS_END
    };

    TypeTest<cocos2d::DrawNode> t1;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t1.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);

    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");

    JS::RootedObject parentProto(cx, typeClass->proto.ref());
    JSB_CCPhysicsDebugNode_object = JS_InitClass(cx, globalObj, parentProto, JSB_CCPhysicsDebugNode_class, JSB_CCPhysicsDebugNode_constructor, 0,properties,funcs,NULL,st_funcs);

    JS::RootedObject proto(cx, JSB_CCPhysicsDebugNode_object);
    jsb_register_class<PhysicsDebugNode>(cx, JSB_CCPhysicsDebugNode_class, proto, parentProto);
}

// Arguments: NSString*, CGRect
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static(JSContext *cx, uint32_t argc, jsval *vp) {

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    PhysicsSprite* ret = nullptr;
    if (argc == 2) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::Rect arg1;
        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

        ret = PhysicsSprite::create(arg0, arg1);
    }
    else if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

        ret = PhysicsSprite::create(arg0);
    }
    else {
        return false;
    }

    jsval jsret;
    if (ret) {
        js_type_class_t *typeClass = js_get_type_from_native<PhysicsSprite>(ret);
        jsret = OBJECT_TO_JSVAL(jsb_ref_autoreleased_get_or_create_jsobject(cx, ret, typeClass, "cocos2d::extension::PhysicsSprite"));
    } else {
        jsret = JSVAL_NULL;
    }
    args.rval().set(jsret);
    return true;
}

// Arguments: SpriteFrame*
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    cocos2d::SpriteFrame* arg0 = nullptr;
    if (argc >= 1) {
        do {
            js_proxy_t *proxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            proxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(proxy ? proxy->ptr : NULL);
            TEST_NATIVE_OBJECT(cx, arg0)
        } while (0);
    }
    PhysicsSprite* ret = PhysicsSprite::createWithSpriteFrame(arg0);

    JS::RootedValue jsret(cx);
    if (ret) {
        js_type_class_t *typeClass = js_get_type_from_native<PhysicsSprite>(ret);
        jsret.set(OBJECT_TO_JSVAL(jsb_ref_autoreleased_get_or_create_jsobject(cx, ret, typeClass, "cocos2d::extension::PhysicsSprite")));
    } else {
        jsret.set(JS::NullValue());
    }
    args.rval().set(jsret);
    return true;
}

// Arguments: NSString*
// Ret value: PhysicsSprite* (o)
bool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    const char* arg0 = nullptr;
    std::string arg0_tmp;
    if (argc == 1) {
        ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();

        PhysicsSprite* ret = PhysicsSprite::createWithSpriteFrameName(arg0);

        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::PhysicsSprite>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::PhysicsSprite"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool JSPROXY_CCPhysicsSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    auto cobj = new (std::nothrow) cocos2d::extension::PhysicsSprite;
    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::PhysicsSprite>(cobj);
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::PhysicsSprite"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));

    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}

static bool JSPROXY_CCPhysicsSprite_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    auto nobj = new (std::nothrow) cocos2d::extension::PhysicsSprite;
    auto newproxy = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &newproxy->obj, nobj, "cocos2d::extension::PhysicsSprite");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

void JSPROXY_CCPhysicsSprite_createClass(JSContext *cx, JS::HandleObject globalObj)
{
    JSPROXY_CCPhysicsSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    JSPROXY_CCPhysicsSprite_class->name = "PhysicsSprite";
    JSPROXY_CCPhysicsSprite_class->addProperty = JS_PropertyStub;
    JSPROXY_CCPhysicsSprite_class->delProperty = JS_DeletePropertyStub;
    JSPROXY_CCPhysicsSprite_class->getProperty = JS_PropertyStub;
    JSPROXY_CCPhysicsSprite_class->setProperty = JS_StrictPropertyStub;
    JSPROXY_CCPhysicsSprite_class->enumerate = JS_EnumerateStub;
    JSPROXY_CCPhysicsSprite_class->resolve = JS_ResolveStub;
    JSPROXY_CCPhysicsSprite_class->convert = JS_ConvertStub;
    JSPROXY_CCPhysicsSprite_class->flags = 0;

    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("isDirty", JSPROXY_CCPhysicsSprite_isDirty, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("getCPBody", JSPROXY_CCPhysicsSprite_getCPBody, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("getIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_ignoreBodyRotation, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("_setCPBody", JSPROXY_CCPhysicsSprite_setCPBody_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("setIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("ctor", JSPROXY_CCPhysicsSprite_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static, 2, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrame", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrameName", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FS_END
    };

    TypeTest<cocos2d::Sprite> t1;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t1.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");

    JS::RootedObject parentProto(cx, typeClass->proto.ref());
    JSPROXY_CCPhysicsSprite_object = JS_InitClass(cx, globalObj, parentProto, JSPROXY_CCPhysicsSprite_class, JSPROXY_CCPhysicsSprite_constructor, 0,properties,funcs,NULL,st_funcs);

    JS::RootedObject proto(cx, JSPROXY_CCPhysicsSprite_object);
    jsb_register_class<PhysicsSprite>(cx, JSPROXY_CCPhysicsSprite_class, proto, parentProto);

    anonEvaluate(cx, globalObj, "(function () { cc.PhysicsSprite.extend = cc.Class.extend; })()");
}


void register_CCPhysicsSprite(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ccObj(cx);
    get_or_create_js_obj(cx, obj, "cc", &ccObj);
    JSPROXY_CCPhysicsSprite_createClass(cx, ccObj);
}

void register_CCPhysicsDebugNode(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ccObj(cx);
    get_or_create_js_obj(cx, obj, "cc", &ccObj);
    JSB_CCPhysicsDebugNode_createClass(cx, ccObj, "PhysicsDebugNode");
}

bool jsval_to_cpBB( JSContext *cx, jsval vp, cpBB *ret )
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, vp);
    bool ok = JS_ValueToObject(cx, jsv, &jsobj);
    JSB_PRECONDITION( ok, "Error converting value to object");
    JSB_PRECONDITION( jsobj, "Not a valid JS object");

    JS::RootedValue vall(cx);
    JS::RootedValue valb(cx);
    JS::RootedValue valr(cx);
    JS::RootedValue valt(cx);
    ok = true;
    ok &= JS_GetProperty(cx, jsobj, "l", &vall);
    ok &= JS_GetProperty(cx, jsobj, "b", &valb);
    ok &= JS_GetProperty(cx, jsobj, "r", &valr);
    ok &= JS_GetProperty(cx, jsobj, "t", &valt);
    JSB_PRECONDITION( ok, "Error obtaining point properties");

    double l = 0, b = 0, r = 0, t = 0;
    ok &= JS::ToNumber(cx, vall, &l);
    ok &= JS::ToNumber(cx, valb, &b);
    ok &= JS::ToNumber(cx, valr, &r);
    ok &= JS::ToNumber(cx, valt, &t);
    JSB_PRECONDITION( ok, "Error converting value to numbers");

    ret->l = l;
    ret->b = b;
    ret->r = r;
    ret->t = t;

    return true;
}

jsval cpBB_to_jsval(JSContext *cx, cpBB bb )
{
    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
    if (!object)
        return JSVAL_VOID;

    if (!JS_DefineProperty(cx, object, "l", bb.l, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "b", bb.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "r", bb.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "t", bb.t, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JSVAL_VOID;

    return OBJECT_TO_JSVAL(object);
}

// In order to be compatible with Chipmunk-JS API,
// this function expect to receive an array of numbers, and not an array of vects
// OK:  [1,2,  3,4,  5,6]   <- expected
// BAD: [{x:1, y:2}, {x:3,y:4}, {x:5, y:6}]  <- not expected
bool jsval_to_array_of_cpvect( JSContext *cx, jsval vp, cpVect**verts, int *numVerts)
{
    // Parsing sequence
    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, vp);
    bool ok = JS_ValueToObject(cx, jsv, &jsobj);
    JSB_PRECONDITION( ok, "Error converting value to object");

    JSB_PRECONDITION( jsobj && JS_IsArrayObject( cx, jsobj),  "Object must be an array");

    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);

    JSB_PRECONDITION( len%2==0, "Array length should be even");

    cpVect *array = (cpVect*)malloc( sizeof(cpVect) * len/2);

    for( uint32_t i=0; i< len;i++ ) {
        JS::RootedValue valarg(cx);
        JS_GetElement(cx, jsobj, i, &valarg);

        double value = 0;
        ok = JS::ToNumber(cx, valarg, &value);
        if (!ok) {
            free(array);
        }
        JSB_PRECONDITION(ok, "Error converting value to nsobject");

        if(i%2==0)
            array[i/2].x = value;
        else
            array[i/2].y = value;
    }

    *numVerts = len/2;
    *verts = array;

    return true;
}


bool jsval_to_cpVect( JSContext *cx, jsval vp, cpVect *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, vp);
    if( !JS_ValueToObject(cx, jsv, &jsobj) )
        return false;

    JSB_PRECONDITION( jsobj, "Not a valid JS object");

    JS::RootedValue valx(cx);
    JS::RootedValue valy(cx);
    bool ok = true;
    ok &= JS_GetProperty(cx, jsobj, "x", &valx);
    ok &= JS_GetProperty(cx, jsobj, "y", &valy);

    if( ! ok )
        return false;

    double x = 0, y = 0;
    ok &= JS::ToNumber(cx, valx, &x);
    ok &= JS::ToNumber(cx, valy, &y);

    if( ! ok )
        return false;

    ret->x = x;
    ret->y = y;

    return true;

#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JSObject *tmp_arg = nullptr;
    if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
        return false;

    JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");

    JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");

    *ret = *(cpVect*)JS_GetArrayBufferViewData( tmp_arg, cx );

    return true;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


jsval cpVect_to_jsval( JSContext *cx, cpVect p)
{

#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    if (!object)
        return JSVAL_VOID;

    if (!JS_DefineProperty(cx, object, "x", p.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "y", p.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JSVAL_VOID;

    return OBJECT_TO_JSVAL(object);

#else // JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

#ifdef __LP64__
    JSObject *typedArray = JS_NewFloat64Array( cx, 2 );
#else
    JSObject *typedArray = JS_NewFloat32Array( cx, 2 );
#endif

    cpVect *buffer = (cpVect*)JS_GetArrayBufferViewData(typedArray, cx );
    *buffer = p;
    return OBJECT_TO_JSVAL(typedArray);
#endif // ! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

bool jsval_to_cpShapeFilter( JSContext *cx, jsval vp, cpShapeFilter *filter )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, vp);
    if( !JS_ValueToObject(cx, jsv, &jsobj) )
        return false;

    JSB_PRECONDITION( jsobj, "Not a valid JS object");

    JS::RootedValue valgroup(cx);
    JS::RootedValue valcategories(cx);
    JS::RootedValue valmask(cx);

    bool ok = true;
    ok &= JS_GetProperty(cx, jsobj, "group", &valgroup);
    ok &= JS_GetProperty(cx, jsobj, "categories", &valcategories);
    ok &= JS_GetProperty(cx, jsobj, "mask", &valmask);

    if( ! ok )
        return false;

    double group, categories, mask;
    ok &= JS::ToNumber(cx, valgroup, &group);
    ok &= JS::ToNumber(cx, valcategories, &categories);
    ok &= JS::ToNumber(cx, valmask, &mask);

    if( ! ok )
        return false;

    filter->group = group;
    filter->categories = categories;
    filter->mask = mask;

    return true;

#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
#error "not supported"
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

jsval cpShapeFilter_to_jsval( JSContext *cx, cpShapeFilter filter)
{

#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    if (!object)
        return JSVAL_VOID;

    if (!JS_DefineProperty(cx, object, "group", (double)filter.group, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "categories", filter.categories, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "mask", filter.mask, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JSVAL_VOID;

    return OBJECT_TO_JSVAL(object);

#else // JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
#error "Not supported"
#endif // ! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

bool jsval_to_cpTransform( JSContext *cx, jsval vp, cpTransform *transform )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, vp);
    if( !JS_ValueToObject(cx, jsv, &jsobj) )
        return false;

    JSB_PRECONDITION( jsobj, "Not a valid JS object");

    JS::RootedValue vala(cx);
    JS::RootedValue valb(cx);
    JS::RootedValue valc(cx);
    JS::RootedValue vald(cx);
    JS::RootedValue valtx(cx);
    JS::RootedValue valty(cx);

    bool ok = true;
    ok &= JS_GetProperty(cx, jsobj, "a", &vala);
    ok &= JS_GetProperty(cx, jsobj, "b", &valb);
    ok &= JS_GetProperty(cx, jsobj, "c", &valc);
    ok &= JS_GetProperty(cx, jsobj, "d", &vald);
    ok &= JS_GetProperty(cx, jsobj, "tx", &valtx);
    ok &= JS_GetProperty(cx, jsobj, "ty", &valty);

    if( ! ok )
        return false;

    double a,b,c,d,tx,ty;
    ok &= JS::ToNumber(cx, vala, &a);
    ok &= JS::ToNumber(cx, valb, &b);
    ok &= JS::ToNumber(cx, valc, &c);
    ok &= JS::ToNumber(cx, vald, &d);
    ok &= JS::ToNumber(cx, valtx, &tx);
    ok &= JS::ToNumber(cx, valty, &ty);

    if( ! ok )
        return false;

    transform->a = a;
    transform->b = b;
    transform->c = c;
    transform->d = d;
    transform->tx = tx;
    transform->ty = ty;

    return true;

#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
#error "not supported"
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

jsval cpTransform_to_jsval( JSContext *cx, cpTransform transform)
{

#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    if (!object)
        return JSVAL_VOID;

    if (!JS_DefineProperty(cx, object, "a", transform.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "b", transform.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "c", transform.c, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "d", transform.d, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "tx", transform.tx, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "ty", transform.ty, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JSVAL_VOID;

    return OBJECT_TO_JSVAL(object);

#else // JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
#error "Not supported"
#endif // ! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

jsval cpPointQueryInfo_to_jsval(JSContext *cx, cpPointQueryInfo pointQueryInfo)
{
    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    if (!object)
        return JSVAL_VOID;

    bool ok = true;

    JSObject* jsobj = jsb_get_jsobject_for_proxy((void*)pointQueryInfo.shape);
    if (!jsobj)
    {
        JS::RootedObject shapeProto(cx, JSB_cpShape_object);
        jsobj = JS_NewObject(cx, JSB_cpShape_class, shapeProto, JS::NullPtr());
        jsb_set_jsobject_for_proxy(jsobj, (void*)pointQueryInfo.shape);
        jsb_set_c_proxy_for_jsobject(jsobj, (void*)pointQueryInfo.shape, JSB_C_FLAG_DO_NOT_CALL_FREE);
    }

    JS::RootedObject rootedShape(cx, jsobj);

    JS::RootedValue rootedPoint(cx, cpVect_to_jsval(cx, pointQueryInfo.point));
    JS::RootedValue rootedGradient(cx, cpVect_to_jsval(cx, pointQueryInfo.gradient));

    ok &= JS_DefineProperty(cx, object, "shape", rootedShape, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "point", rootedPoint, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "distance", pointQueryInfo.distance, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "gradient", rootedGradient, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    // v6.2 backward compatibility
    ok &= JS_DefineProperty(cx, object, "p", rootedPoint, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "d", pointQueryInfo.distance, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    return OBJECT_TO_JSVAL(object);
}

jsval cpSegmentQueryInfo_to_jsval(JSContext *cx, cpSegmentQueryInfo segmentQueryInfo)
{
    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    if (!object)
        return JSVAL_VOID;

    bool ok = true;

    JSObject* jsobj = jsb_get_jsobject_for_proxy((void*)segmentQueryInfo.shape);
    if (!jsobj)
    {
        JS::RootedObject shapeProto(cx, JSB_cpShape_object);
        jsobj = JS_NewObject(cx, JSB_cpShape_class, shapeProto, JS::NullPtr());
        jsb_set_jsobject_for_proxy(jsobj, (void*)segmentQueryInfo.shape);
        jsb_set_c_proxy_for_jsobject(jsobj, (void*)segmentQueryInfo.shape, JSB_C_FLAG_DO_NOT_CALL_FREE);
    }
    JS::RootedObject rootedShape(cx, jsobj);

    JS::RootedValue rootedPoint(cx, cpVect_to_jsval(cx, segmentQueryInfo.point));
    JS::RootedValue rootedNormal(cx, cpVect_to_jsval(cx, segmentQueryInfo.normal));

    ok &= JS_DefineProperty(cx, object, "shape", rootedShape, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "point", rootedPoint, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "normal", rootedNormal, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "alpha", segmentQueryInfo.alpha, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    // v6.2 backward compatibility
    ok &= JS_DefineProperty(cx, object, "p", rootedPoint, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "n", rootedNormal, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, object, "t", segmentQueryInfo.alpha, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    return OBJECT_TO_JSVAL(object);
}
#pragma mark - Collision Handler

struct collision_handler {
    cpCollisionType     typeA;
    cpCollisionType     typeB;

    JS::Heap<JSObject*> begin;
    JS::Heap<JSObject*> pre;
    JS::Heap<JSObject*> post;
    JS::Heap<JSObject*> separate;
    JS::Heap<JSObject*> jsthis;
    JSContext           *cx;

    // "owner" of the collision handler
    // Needed when the space goes out of scope, it will remove all the allocated collision handlers for him.
    cpSpace             *space;

    unsigned long       hash_key;

    unsigned int        is_oo; // Objected oriented API ?
    UT_hash_handle  hh;

    collision_handler()
    {
        begin = nullptr;
        pre = nullptr;
        post = nullptr;
        separate = nullptr;
        jsthis = nullptr;
    }

    void setJSSpace(JS::HandleValue jsspace)
    {
        if (!jsspace.isNullOrUndefined())
        {
            jsthis = jsspace.toObjectOrNull();
            JS::RootedValue callback(ScriptingCore::getInstance()->getGlobalContext());
            callback.set(OBJECT_TO_JSVAL(begin));
            if (!callback.isNullOrUndefined())
            {
                js_add_object_reference(jsspace, callback);
            }
            callback.set(OBJECT_TO_JSVAL(pre));
            if (!callback.isNullOrUndefined())
            {
                js_add_object_reference(jsspace, callback);
            }
            callback.set(OBJECT_TO_JSVAL(post));
            if (!callback.isNullOrUndefined())
            {
                js_add_object_reference(jsspace, callback);
            }
            callback.set(OBJECT_TO_JSVAL(separate));
            if (!callback.isNullOrUndefined())
            {
                js_add_object_reference(jsspace, callback);
            }
        }
    }
};

// hash
struct collision_handler* collision_handler_hash = NULL;

// helper pair
static unsigned long pair_ints( unsigned long A, unsigned long B )
{
    // order is not important
    unsigned long k1 = MIN(A, B );
    unsigned long k2 = MAX(A, B );

    return (k1 + k2) * (k1 + k2 + 1) /2 + k2;
}

static cpBool myCollisionBegin(cpArbiter *arb, cpSpace *space, void *data)
{
    struct collision_handler *handler = (struct collision_handler*) data;

    jsval args[2];
    if( handler->is_oo ) {
        JS::RootedObject arbiterProto(handler->cx, JSB_cpArbiter_object);
        JS::RootedObject spaceProto(handler->cx, JSB_cpSpace_object);
        args[0] = c_class_to_jsval(handler->cx, arb, arbiterProto, JSB_cpArbiter_class, "cpArbiter");
        args[1] = c_class_to_jsval(handler->cx, space, spaceProto, JSB_cpSpace_class, "cpArbiter");
    } else {
        args[0] = opaque_to_jsval(handler->cx, arb);
        args[1] = opaque_to_jsval(handler->cx, space );
    }

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedValue rval(handler->cx);
    JS::RootedObject jsthis(handler->cx, handler->jsthis);
    JS::RootedValue jsbegin(handler->cx, OBJECT_TO_JSVAL(handler->begin));
    bool ok = JS_CallFunctionValue(handler->cx, jsthis, jsbegin, JS::HandleValueArray::fromMarkedLocation(2, args), &rval);
    JSB_PRECONDITION2(ok, handler->cx, cpFalse, "Error calling collision callback: begin");

    if( rval.isBoolean() ) {
        bool ret = rval.toBoolean();
        return (cpBool)ret;
    }
    return cpTrue;
}

static cpBool myCollisionPre(cpArbiter *arb, cpSpace *space, void *data)
{
    struct collision_handler *handler = (struct collision_handler*) data;

    jsval args[2];
    if( handler->is_oo ) {
        JS::RootedObject arbiterProto(handler->cx, JSB_cpArbiter_object);
        JS::RootedObject spaceProto(handler->cx, JSB_cpSpace_object);
        args[0] = c_class_to_jsval(handler->cx, arb, arbiterProto, JSB_cpArbiter_class, "cpArbiter");
        args[1] = c_class_to_jsval(handler->cx, space, spaceProto, JSB_cpSpace_class, "cpArbiter");
    } else {
        args[0] = opaque_to_jsval( handler->cx, arb);
        args[1] = opaque_to_jsval( handler->cx, space );
    }

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedValue rval(handler->cx);
    JS::RootedObject jsthis(handler->cx, handler->jsthis);
    JS::RootedValue jspre(handler->cx, OBJECT_TO_JSVAL(handler->pre));
    bool ok = JS_CallFunctionValue( handler->cx, jsthis, jspre, JS::HandleValueArray::fromMarkedLocation(2, args), &rval);
    JSB_PRECONDITION2(ok, handler->cx, false, "Error calling collision callback: pre");

    if( rval.isBoolean() ) {
        bool ret = rval.toBoolean();
        return (cpBool)ret;
    }
    return cpTrue;
}

static void myCollisionPost(cpArbiter *arb, cpSpace *space, void *data)
{
    struct collision_handler *handler = (struct collision_handler*) data;

    jsval args[2];

    if( handler->is_oo ) {
        JS::RootedObject arbiterProto(handler->cx, JSB_cpArbiter_object);
        JS::RootedObject spaceProto(handler->cx, JSB_cpSpace_object);
        args[0] = c_class_to_jsval(handler->cx, arb, arbiterProto, JSB_cpArbiter_class, "cpArbiter");
        args[1] = c_class_to_jsval(handler->cx, space, spaceProto, JSB_cpSpace_class, "cpArbiter");
    } else {
        args[0] = opaque_to_jsval( handler->cx, arb);
        args[1] = opaque_to_jsval( handler->cx, space );
    }

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedValue ignore(handler->cx);
    JS::RootedObject jsthis(handler->cx, handler->jsthis);
    JS::RootedValue jspost(handler->cx, OBJECT_TO_JSVAL(handler->post));
    bool ok = JS_CallFunctionValue( handler->cx, jsthis, jspost, JS::HandleValueArray::fromMarkedLocation(2, args), &ignore);
    JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Post");
}

static void myCollisionSeparate(cpArbiter *arb, cpSpace *space, void *data)
{
    struct collision_handler *handler = (struct collision_handler*) data;
    if(! handler->cx || !handler->space)
        return;

    jsval args[2];
    if( handler->is_oo ) {
        JS::RootedObject arbiterProto(handler->cx, JSB_cpArbiter_object);
        JS::RootedObject spaceProto(handler->cx, JSB_cpSpace_object);
        args[0] = c_class_to_jsval(handler->cx, arb, arbiterProto, JSB_cpArbiter_class, "cpArbiter");
        args[1] = c_class_to_jsval(handler->cx, space, spaceProto, JSB_cpSpace_class, "cpArbiter");
    } else {
        args[0] = opaque_to_jsval( handler->cx, arb);
        args[1] = opaque_to_jsval( handler->cx, space );
    }

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedValue ignore(handler->cx);
    JS::RootedObject jsthis(handler->cx, handler->jsthis);
    JS::RootedValue jssep(handler->cx, OBJECT_TO_JSVAL(handler->separate));
    bool ok = JS_CallFunctionValue( handler->cx, jsthis, jssep, JS::HandleValueArray::fromMarkedLocation(2, args), &ignore);
    JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Separate");}

#pragma mark - cpSpace

#pragma mark constructor / destructor

void JSB_cpSpace_finalize(JSFreeOp *fop, JSObject *jsthis)
{
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    if ( proxy ) {
        CCLOGINFO("jsbindings: finalizing JS object %p (cpSpace), handle: %p", jsthis, proxy->handle);

        // space
        cpSpace *space = (cpSpace*) proxy->handle;


        // Remove collision handlers, since the user might have forgotten to manually remove them
        struct collision_handler *current = nullptr, *tmp = nullptr;
        HASH_ITER(hh, collision_handler_hash, current, tmp) {
            if( current->space == space ) {
                HASH_DEL(collision_handler_hash,current);  /* delete; users advances to next */
                delete current;            /* optional- if you want to free  */
            }
        }

        // Free Space Children
        freeSpaceChildren(space);

        jsb_del_jsobject_for_proxy(space);
        if(proxy->flags == JSB_C_FLAG_CALL_FREE)
            cpSpaceFree(space);
        jsb_del_c_proxy_for_jsobject(jsthis);
#if COCOS2D_DEBUG > 1
        CCLOG("------RELEASED------ Cpp(cp.Space): %p - JS: %p", space, jsthis);
#endif // COCOS2D_DEBUG
    }
}


#pragma mark addCollisionHandler

static
bool __jsb_cpSpace_addCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, JS::HandleObject jsspace, cpSpace *space, unsigned int is_oo)
{
    struct collision_handler *handler = new (std::nothrow) collision_handler();
    handler->typeA = 0;
    handler->typeB = 0;

    JSB_PRECONDITION(handler, "Error allocating memory");

    bool ok = true;

    // args
    JS::RootedValue jstypeA(cx, *argvp++);
    JS::RootedValue jstypeB(cx, *argvp++);
    ok &= jsval_to_int(cx, jstypeA, (int32_t*) &handler->typeA );
    ok &= jsval_to_int(cx, jstypeB, (int32_t*) &handler->typeB );

    handler->begin = argvp->toObjectOrNull();
    argvp++;
    handler->pre = argvp->toObjectOrNull();
    argvp++;
    handler->post = argvp->toObjectOrNull();
    argvp++;
    handler->separate = argvp->toObjectOrNull();
    argvp++;

    JS::RootedValue spaceVal(cx, OBJECT_TO_JSVAL(jsspace));
    handler->setJSSpace(spaceVal);

    JSB_PRECONDITION(ok, "Error parsing arguments");

    // Object Oriented API ?
    handler->is_oo = is_oo;
    // owner of the collision handler
    handler->space = space;
    handler->cx = cx;

    cpCollisionHandler* cp_collision_handler = cpSpaceAddCollisionHandler(space, handler->typeA, handler->typeB);
    cp_collision_handler->userData = handler;
    cp_collision_handler->beginFunc = handler->begin ? &myCollisionBegin : cpCollisionHandlerDoNothing.beginFunc;
    cp_collision_handler->preSolveFunc = handler->pre ? &myCollisionPre : cpCollisionHandlerDoNothing.preSolveFunc;
    cp_collision_handler->postSolveFunc = handler->post ? &myCollisionPost : cpCollisionHandlerDoNothing.postSolveFunc;
    cp_collision_handler->separateFunc = handler->separate ? &myCollisionSeparate : cpCollisionHandlerDoNothing.separateFunc;

    //
    // Already added ? If so, remove it.
    // Then add new entry
    //
    struct collision_handler *hashElement = NULL;
    unsigned long paired_key = pair_ints(handler->typeA, handler->typeB );
    HASH_FIND_INT(collision_handler_hash, &paired_key, hashElement);
    if( hashElement ) {
        HASH_DEL( collision_handler_hash, hashElement );
        delete hashElement;
    }

    handler->hash_key = paired_key;
    HASH_ADD_INT( collision_handler_hash, hash_key, handler );

    return true;
}

bool JSB_cpSpaceAddCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==7, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue spaceVal(cx, args.get(0));
    JS::RootedObject jsspace(cx);
    JS_ValueToObject(cx, spaceVal, &jsspace);

    // args
    cpSpace *space = nullptr;
    jsval* argvp = args.array();
    JS::RootedValue jsarg(cx, *argvp++);
    bool ok = jsval_to_opaque(cx, jsarg, (void**)&space);
    JSB_PRECONDITION(ok, "Error parsing arguments");

    return __jsb_cpSpace_addCollisionHandler(cx, vp, argvp, jsspace, space, 0);
}

// method
bool JSB_cpSpace_addCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==6, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;

    return __jsb_cpSpace_addCollisionHandler(cx, vp, args.array(), jsthis, (cpSpace*)handle, 1);
}

bool JSB_cpSpace_setDefaultCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==4, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    collision_handler *handler = new (std::nothrow) collision_handler();
    JSB_PRECONDITION(handler, "Error allocating memory");

    handler->typeA = 0;
    handler->typeB = 0;
    handler->begin = args.get(0).toObjectOrNull();
    handler->pre = args.get(1).toObjectOrNull();
    handler->post = args.get(2).toObjectOrNull();
    handler->separate = args.get(3).toObjectOrNull();

    JS::RootedValue spaceVal(cx, OBJECT_TO_JSVAL(jsthis));
    handler->setJSSpace(spaceVal);

    // Object Oriented API ?
    handler->is_oo = 1;
    // owner of the collision handler
    handler->space = space;
    handler->cx = cx;

    cpCollisionHandler* defaultHandler = cpSpaceAddDefaultCollisionHandler(space);
    defaultHandler->beginFunc = !handler->begin ? NULL : &myCollisionBegin;
    defaultHandler->preSolveFunc = !handler->pre ? NULL : &myCollisionPre;
    defaultHandler->postSolveFunc = !handler->post ? NULL : &myCollisionPost;
    defaultHandler->separateFunc = !handler->separate ? NULL : &myCollisionSeparate;
    defaultHandler->userData = handler;
    //
    // Already added ? If so, remove it.
    // Then add new entry
    //
    struct collision_handler *hashElement = NULL;
    unsigned long paired_key = pair_ints(handler->typeA, handler->typeB );
    HASH_FIND_INT(collision_handler_hash, &paired_key, hashElement);
    if( hashElement ) {
        HASH_DEL( collision_handler_hash, hashElement );
        delete hashElement;
    }

    handler->hash_key = paired_key;
    HASH_ADD_INT( collision_handler_hash, hash_key, handler );

    args.rval().setUndefined();
    return true;
}

#pragma mark removeCollisionHandler

static
bool __jsb_cpSpace_removeCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, cpSpace *space)
{
    bool ok = true;

    cpCollisionType typeA = 0;
    cpCollisionType typeB = 0;
    JS::RootedValue jstypeA(cx, *argvp++);
    JS::RootedValue jstypeB(cx, *argvp++);
    ok &= jsval_to_int(cx, jstypeA, (int32_t*) &typeA);
    ok &= jsval_to_int(cx, jstypeB, (int32_t*) &typeB);

    JSB_PRECONDITION(ok, "Error parsing arguments");

    cpCollisionHandler* collisionHandler = cpSpaceAddCollisionHandler(space, typeA, typeB);
    collisionHandler->beginFunc = cpCollisionHandlerDoNothing.beginFunc;
    collisionHandler->postSolveFunc = cpCollisionHandlerDoNothing.postSolveFunc;
    collisionHandler->preSolveFunc = cpCollisionHandlerDoNothing.preSolveFunc;
    collisionHandler->separateFunc = cpCollisionHandlerDoNothing.separateFunc;

    // Remove it
    struct collision_handler *hashElement = NULL;
    unsigned long key = pair_ints(typeA, typeB );
    HASH_FIND_INT(collision_handler_hash, &key, hashElement);
    if( hashElement ) {
        HASH_DEL( collision_handler_hash, hashElement );
        delete hashElement;
    }

    return true;
}

// Free function
bool JSB_cpSpaceRemoveCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==3, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    cpSpace* space = nullptr;
    jsval* argvp = args.array();
    JS::RootedValue jsarg(cx, *argvp++);
    bool ok = jsval_to_opaque( cx, jsarg, (void**)&space);

    JSB_PRECONDITION(ok, "Error parsing arguments");

    return __jsb_cpSpace_removeCollisionHandler(cx, vp, argvp, space);
}

// method
bool JSB_cpSpace_removeCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;

    return __jsb_cpSpace_removeCollisionHandler(cx, vp, args.array(), (cpSpace*)handle);
}

#pragma mark Add functios. Root JSObjects

// Arguments: cpBody*
// Ret value: cpBody*
bool JSB_cpSpace_addBody(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpBody* arg1 = nullptr;

    jsval retval = args.get(0); struct jsb_c_proxy_s *retproxy;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceAddBody((cpSpace*)arg0 , (cpBody*)arg1  );

    // Root it:
    JS::AddNamedObjectRoot(cx, &retproxy->jsobj, "cpBody");

    // addBody returns the same object that was added, so return it without conversions
    args.rval().set(retval);

    return true;
}

// Arguments: cpConstraint*
// Ret value: cpConstraint*
bool JSB_cpSpace_addConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpConstraint* arg1 = nullptr;

    jsval retval = args.get(0); struct jsb_c_proxy_s *retproxy;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceAddConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );

    // Root it:
    JS::AddNamedObjectRoot(cx, &retproxy->jsobj, "cpConstraint");

    // addConstraint returns the same object that was added, so return it without conversions
    args.rval().set(retval);

    return true;
}

// Arguments: cpShape*
// Ret value: cpShape*
bool JSB_cpSpace_addShape(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpShape* arg1 = nullptr;

    jsval retval = args.get(0); struct jsb_c_proxy_s *retproxy;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceAddShape((cpSpace*)arg0 , (cpShape*)arg1  );

    // Root it:
    JS::AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape");

    // addShape returns the same object that was added, so return it without conversions
    args.rval().set(retval);

    return true;
}

// FIXME: Not present on Chipmunk v7.0
// Arguments: cpShape*
// Ret value: cpShape*
//bool JSB_cpSpace_addStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
//    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
//    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
//    cpSpace* arg0 = (cpSpace*) proxy->handle;
//    bool ok = true;
//    cpShape* arg1 = nullptr;
//
//    jsval retval = args.get(0); struct jsb_c_proxy_s *retproxy;
//    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
//    JSB_PRECONDITION(ok, "Error processing arguments");
//
//    cpSpaceAddStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
//
//    // Root it:
//    JS::AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape (static)");
//
//    // addStaticShape returns the same object that was added, so return it without conversions
//    args.rval().set(retval);
//
//    return true;
//}

#pragma mark Remove functios. Untoot JSObjects

// Arguments: cpBody*
// Ret value: void
bool JSB_cpSpace_removeBody(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpBody* arg1 = nullptr;

    struct jsb_c_proxy_s *retproxy = nullptr;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceRemoveBody((cpSpace*)arg0, (cpBody*)arg1);
    JS::RemoveObjectRoot(cx, &retproxy->jsobj);

    args.rval().setUndefined();
    return true;
}

// Arguments: cpConstraint*
// Ret value: void
bool JSB_cpSpace_removeConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpConstraint* arg1 = nullptr;

    struct jsb_c_proxy_s *retproxy = nullptr;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceRemoveConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
    JS::RemoveObjectRoot(cx, &retproxy->jsobj);

    args.rval().setUndefined();
    return true;
}

// Arguments: cpShape*
// Ret value: void
bool JSB_cpSpace_removeShape(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* arg0 = (cpSpace*) proxy->handle;
    bool ok = true;
    cpShape* arg1 = nullptr;

    struct jsb_c_proxy_s *retproxy = nullptr;
    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpSpaceRemoveShape((cpSpace*)arg0 , (cpShape*)arg1  );
    JS::RemoveObjectRoot(cx, &retproxy->jsobj);

    args.rval().setUndefined();
    return true;
}

// FIXME: Not present on Chipmunk v7.0
// Arguments: cpShape*
// Ret value: void
//bool JSB_cpSpace_removeStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
//    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
//    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
//    cpSpace* arg0 = (cpSpace*) proxy->handle;
//    bool ok = true;
//    cpShape* arg1 = nullptr;
//
//    struct jsb_c_proxy_s *retproxy = nullptr;
//    ok &= jsval_to_c_class( cx, args.get(0), (void**)&arg1, &retproxy );
//    JSB_PRECONDITION(ok, "Error processing arguments");
//
//    cpSpaceRemoveStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
//    JS::RemoveObjectRoot(cx, &retproxy->jsobj);
//
//    args.rval().setUndefined();
//    return true;
//}

#pragma mark segmentQueryFirst function

// FIXME: Chipmunk v7.0: different arguments
// cpSegementQuery has different functionality
// cpShape *cpSpaceSegmentQueryFirst(cpSpace *space, cpVect start, cpVect end, cpFloat radius, cpShapeFilter filter, cpSegmentQueryInfo *out)
bool JSB_cpSpace_segmentQueryFirst(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    cpVect start, end;
    double radius;
    cpShapeFilter filter;
    bool ok = true;
    ok &= jsval_to_cpVect( cx, args.get(0), &start );
    ok &= jsval_to_cpVect( cx, args.get(1), &end );
    ok &= JS::ToNumber(cx, args.get(2), &radius);
    ok &= jsval_to_cpShapeFilter(cx, args.get(3), &filter);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    cpSegmentQueryInfo out;
    cpShape* target = cpSpaceSegmentQueryFirst(space, start, end, radius, filter, &out);

    if (target)
    {
        args.rval().set(cpSegmentQueryInfo_to_jsval(cx, out));
    }
    else
    {
        args.rval().set(JSVAL_NULL);
    }
    return true;
}

#pragma mark nearestPointQueryNearest function

// FIXME: Chipmunk v7.0: different arguments
// cpNearestPointQueryInfo changed its arguments
// cpShape *cpSpacePointQueryNearest(cpSpace *space, cpVect point, cpFloat maxDistance, cpShapeFilter filter, cpPointQueryInfo *out);
bool JSB_cpSpace_pointQueryNearest(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    cpVect point;
    double maxDistance;
    cpShapeFilter filter;
    bool ok = true;
    ok &= jsval_to_cpVect( cx, args.get(0), &point );
    ok &= JS::ToNumber(cx, args.get(1), &maxDistance);
    ok &= jsval_to_cpShapeFilter(cx, args.get(2), &filter);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    cpPointQueryInfo info;
    cpShape* target = cpSpacePointQueryNearest(space, point, maxDistance, filter, &info);

    if (target)
    {
        args.rval().set(cpPointQueryInfo_to_jsval(cx, info));
    }
    else
    {
        args.rval().set(JSVAL_NULL);
    }
    return true;
}

struct JSB_cp_each_UserData
{
    JSContext *cx;
    jsval* func;
};

// FIXME: Chipmunk v7.0: different arguments
//typedef void (*cpSpacePointQueryFunc)(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, void *data);
void JSB_cpSpace_pointQuery_func(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, void *data)
{
    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(shape);
    if(jsCpObject)
    {
        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
        JS::RootedValue rval(cx);

        jsval argv[4];
        argv[0] = OBJECT_TO_JSVAL(jsCpObject);
        argv[1] = cpVect_to_jsval(cx, point);
        argv[2] = DOUBLE_TO_JSVAL(distance);
        argv[3] = cpVect_to_jsval(cx, gradient);

        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(4, argv), &rval);
    }
}

// FIXME: Chipmunk v7.0: different arguments
// cpSpacePointQuery(cpSpace *space, cpVect point, cpFloat maxDistance, cpShapeFilter filter, cpSpacePointQueryFunc func, void *data);
bool JSB_cpSpace_pointQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 4, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JSObject* jsthis = args.thisv().toObjectOrNull();
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    cpVect point;
    double maxDistance;
    cpShapeFilter filter;

    bool ok = jsval_to_cpVect(cx, args.get(0), &point);
    ok &= JS::ToNumber(cx, args.get(1), &maxDistance);
    ok &= jsval_to_cpShapeFilter(cx, args.get(2), &filter);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(3).address());

    cpSpacePointQuery(space, point, maxDistance, filter, JSB_cpSpace_pointQuery_func, data);
    free(data);

    args.rval().setUndefined();
    return true;
}

// FIXME: no longer present in Chipmuk v7.0
// Replaced with cpSpacePointQueryNearest() which also uses different arguments
//void JSB_cpSpace_nearestPointQuery_func(cpShape *shape, cpFloat distance, cpVect point, void *data)
//{
//    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(shape);
//    if(jsCpObject)
//    {
//        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
//        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
//        JS::RootedValue rval(cx);
//        jsval argv[3];
//        argv[0] = OBJECT_TO_JSVAL(jsCpObject);
//        argv[1] = DOUBLE_TO_JSVAL(distance);
//        argv[2] = cpVect_to_jsval(cx, point);
//
//        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
//        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(3, argv), &rval);
//
//    }
//}
//
//bool JSB_cpSpace_nearestPointQuery(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JSB_PRECONDITION2(argc == 5, cx, false, "Invalid number of arguments");
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//
//    JSObject* jsthis = args.thisv().toObjectOrNull();
//    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
//    cpSpace* space = (cpSpace*) proxy->handle;
//
//    cpVect point;
//    double maxDistance = 0;
//    cpLayers layers = 0;
//    cpGroup group = 0;
//
//    bool ok = jsval_to_cpVect(cx, args.get(0), &point);
//    ok &= JS::ToNumber(cx, args.get(1), &maxDistance);
//    ok &= jsval_to_uint32(cx, args.get(2), &layers);
//    ok &= jsval_to_uint(cx, args.get(3), (unsigned int*)&group);
//    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
//    if (!data)
//        return false;
//
//    data->cx = cx;
//    data->func = const_cast<JS::Value*>(args.get(4).address());
//
//    cpSpaceNearestPointQuery(space, point, maxDistance, layers, group, JSB_cpSpace_nearestPointQuery_func, data);
//
//    free(data);
//    args.rval().setUndefined();
//    return true;
//}

// FIXME: Chipmunk v7.0 uses new arguments
// typedef void (*cpSpaceSegmentQueryFunc)(cpShape *shape, cpVect point, cpVect normal, cpFloat alpha, void *data);
void JSB_cpSpace_segmentQuery_func(cpShape *shape, cpVect point, cpVect normal, cpFloat alpha, void *data)
{
    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(shape);
    if(jsCpObject)
    {
        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
        JS::RootedValue rval(cx);
        jsval argv[4];
        argv[0] = OBJECT_TO_JSVAL(jsCpObject);
        argv[1] = cpVect_to_jsval(cx, point);
        argv[2] = cpVect_to_jsval(cx, normal);
        argv[3] = DOUBLE_TO_JSVAL(alpha);

        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(4, argv), &rval);

    }
}

// FIXME: Chipmunk v7.0 uses new parameters
// void cpSpaceSegmentQuery(cpSpace *space, cpVect start, cpVect end, cpFloat radius, cpShapeFilter filter, cpSpaceSegmentQueryFunc func, void *data);
bool JSB_cpSpace_segmentQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 5, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    cpVect start, end;
    double radius;
    cpShapeFilter filter;

    bool ok = jsval_to_cpVect(cx, args.get(0), &start);
    ok = jsval_to_cpVect(cx, args.get(1), &end);
    ok &= JS::ToNumber(cx, args.get(2), &radius);
    ok &= jsval_to_cpShapeFilter(cx, args.get(3), &filter);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");


    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(4).address());

    cpSpaceSegmentQuery(space, start, end, radius, filter, JSB_cpSpace_segmentQuery_func, data);

    free(data);
    args.rval().setUndefined();
    return true;
}

// typedef void (*cpSpaceBBQueryFunc)(cpShape *shape, void *data);
void JSB_cpSpace_bbQuery_func(cpShape *shape, void *data)
{
    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(shape);
    if(jsCpObject)
    {
        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
        JS::RootedValue rval(cx);

        jsval argv[1];
        argv[0] = OBJECT_TO_JSVAL(jsCpObject);

        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(1, argv), &rval);
    }
}


// FIXME: Different parameters in Chipmunk v7.0
// void cpSpaceBBQuery(cpSpace *space, cpBB bb, cpShapeFilter filter, cpSpaceBBQueryFunc func, void *data);
bool JSB_cpSpace_bbQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 4, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JSObject* jsthis = args.thisv().toObjectOrNull();
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*) proxy->handle;

    cpBB bb;
    cpShapeFilter filter;

    bool ok = jsval_to_cpBB(cx, args.get(0), &bb);
    ok &= jsval_to_cpShapeFilter(cx, args.get(1), &filter);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(3).address());

    cpSpaceBBQuery(space, bb, filter, JSB_cpSpace_bbQuery_func, data);

    free(data);
    args.rval().setUndefined();
    return true;
}

template<typename T>
void JSB_cpSpace_each_func(T* cpObject, void *data)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(cpObject);
    if(jsCpObject)
    {
        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
        JS::RootedValue rval(cx);
        jsval argv = OBJECT_TO_JSVAL(jsCpObject);

        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(1, &argv), &rval);

    }
}

bool JSB_cpSpace_eachShape(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpSpaceEachShape(space, JSB_cpSpace_each_func, data);
    free(data);
    return true;
}

bool JSB_cpSpace_eachBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpSpaceEachBody(space, JSB_cpSpace_each_func, data);
    free(data);
    return true;
}

bool JSB_cpSpace_eachConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpSpaceEachConstraint(space, JSB_cpSpace_each_func, data);
    free(data);
    return true;
}

//typedef void (*cpBodyShapeIteratorFunc)(cpBody *body, cpShape *shape, void *data);
template<typename T>
void JSB_cpBody_each_func(cpBody *body, T* cpObject, void *data)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JSObject *jsCpObject = jsb_get_jsobject_for_proxy(cpObject);
    if(jsCpObject)
    {
        JSContext* cx = ((JSB_cp_each_UserData*)data)->cx;
        JS::RootedValue func(cx, *((JSB_cp_each_UserData*)data)->func);
        JS::RootedValue rval(cx);
        jsval argv = OBJECT_TO_JSVAL(jsCpObject);

        JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::fromMarkedLocation(1, &argv), &rval);
        
    }
}

bool JSB_cpBody_eachShape(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpBody* body = (cpBody*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpBodyEachShape(body, JSB_cpBody_each_func, data);
    free(data);
    return true;
}

bool JSB_cpBody_eachConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpBody* body = (cpBody*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpBodyEachConstraint(body, JSB_cpBody_each_func, data);
    free(data);
    return true;
}

bool JSB_cpBody_eachArbiter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpBody* body = (cpBody*)proxy->handle;

    JSB_cp_each_UserData *data = (JSB_cp_each_UserData*)malloc(sizeof(JSB_cp_each_UserData));
    if (!data)
        return false;

    data->cx = cx;
    data->func = const_cast<JS::Value*>(args.get(0).address());

    cpBodyEachArbiter(body, JSB_cpBody_each_func, data);
    free(data);
    return true;
}

// FIXME: API changed in Chipmunk v7.0
// cpFloat cpShapePointQuery(const cpShape *shape, cpVect p, cpPointQueryInfo *out);
bool JSB_cpShape_pointQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpShape* shape = (cpShape*) proxy->handle;

    cpVect p;

    bool ok = jsval_to_cpVect(cx, args.get(0), &p);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    cpPointQueryInfo info;
    cpShapePointQuery(shape, p, &info);
    jsval ret = cpPointQueryInfo_to_jsval(cx, info);

    args.rval().set(ret);
    return true;
}

// Extra argument in Chipmunk v7.0
// cpBool cpShapeSegmentQuery(const cpShape *shape, cpVect a, cpVect b, cpFloat radius, cpSegmentQueryInfo *info);
bool JSB_cpShape_segmentQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 3 || argc == 2, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpShape* shape = (cpShape*) proxy->handle;

    cpVect a, b;
    double radius = 10;

    bool ok = jsval_to_cpVect(cx, args.get(0), &a);
    ok = jsval_to_cpVect(cx, args.get(1), &b);

    // Chipmunk v7.0 only
    if (argc == 3)
        ok &= JS::ToNumber(cx, args.get(2), &radius);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    cpSegmentQueryInfo info;
    cpShapeSegmentQuery(shape, a, b, radius, &info);
    jsval ret = cpSegmentQueryInfo_to_jsval(cx, info);

    args.rval().set(ret);
    return true;
}

struct __PostStep_data{
    JSContext* cx;
    JS::Heap<JS::Value> func;
};

void __JSB_PostStep_callback(cpSpace *space, void *key, __PostStep_data *data)
{
    JSContext* cx = data->cx;
    JS::RootedValue func(cx, data->func);
    JS::RootedValue rval(cx);

    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    JS_CallFunctionValue(cx, JS::NullPtr(), func, JS::HandleValueArray::empty(), &rval);

    free(data);
}

bool JSB_cpSpace_addPostStepCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject* jsthis = args.thisv().toObjectOrNull();
    jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    cpSpace* space = (cpSpace*)proxy->handle;

    __PostStep_data* volatile data = (__PostStep_data*)malloc(sizeof(__PostStep_data));
    if (!data)
        return false;

    data->cx = cx;
    data->func = args.get(0);
    js_add_object_reference(args.thisv(), args.get(0));

    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)__JSB_PostStep_callback, data, data);

    //    free(data);
    args.rval().setUndefined();
    return true;
}

#pragma mark - Arbiter

#pragma mark getBodies
static
bool __jsb_cpArbiter_getBodies(JSContext *cx, const JS::CallArgs& args, cpArbiter *arbiter, unsigned int is_oo)
{
    cpBody *bodyA = nullptr;
    cpBody *bodyB = nullptr;
    cpArbiterGetBodies(arbiter, &bodyA, &bodyB);

    JS::RootedValue valA(cx);
    JS::RootedValue valB(cx);
    if( is_oo ) {
        JS::RootedObject bodyProto(cx, JSB_cpBody_object);
        valA = c_class_to_jsval(cx, bodyA, bodyProto, JSB_cpBody_class, "cpArbiter");
        valB = c_class_to_jsval(cx, bodyB, bodyProto, JSB_cpBody_class, "cpArbiter");
    } else {
        valA = opaque_to_jsval(cx, bodyA);
        valB = opaque_to_jsval(cx, bodyB);
    }

    JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, 2));
    JS_SetElement(cx, jsobj, 0, valA);
    JS_SetElement(cx, jsobj, 1, valB);

    args.rval().set(OBJECT_TO_JSVAL(jsobj));

    return true;
}

// Free function
bool JSB_cpArbiterGetBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    cpArbiter* arbiter = nullptr;
    if( ! jsval_to_opaque( cx, args.get(0), (void**)&arbiter ) )
        return false;

    return __jsb_cpArbiter_getBodies(cx, args, arbiter, 0);
}

// Method
bool JSB_cpArbiter_getBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    JSB_PRECONDITION( proxy, "Invalid private object");
    void *handle = proxy->handle;
    return __jsb_cpArbiter_getBodies(cx, args, (cpArbiter*)handle, 1);
}

#pragma mark getShapes
static
bool __jsb_cpArbiter_getShapes(JSContext *cx, const JS::CallArgs& args, cpArbiter *arbiter, unsigned int is_oo)
{
    cpShape *shapeA = nullptr;
    cpShape *shapeB = nullptr;
    cpArbiterGetShapes(arbiter, &shapeA, &shapeB);

    JS::RootedValue valA(cx);
    JS::RootedValue valB(cx);
    if( is_oo ) {
        JS::RootedObject shapeProto(cx, JSB_cpShape_object);
        valA = c_class_to_jsval(cx, shapeA, shapeProto, JSB_cpShape_class, "cpShape");
        valB = c_class_to_jsval(cx, shapeB, shapeProto, JSB_cpShape_class, "cpShape");
    } else {
        valA = opaque_to_jsval(cx, shapeA);
        valB = opaque_to_jsval(cx, shapeB);
    }

    JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, 2));
    JS_SetElement(cx, jsobj, 0, valA);
    JS_SetElement(cx, jsobj, 1, valB);

    args.rval().set(OBJECT_TO_JSVAL(jsobj));

    return true;
}

// function
bool JSB_cpArbiterGetShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    cpArbiter* arbiter = nullptr;
    if( ! jsval_to_opaque( cx, args.get(0), (void**) &arbiter ) )
        return false;

    return __jsb_cpArbiter_getShapes(cx, args, arbiter, 0);
}

// method
bool JSB_cpArbiter_getShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;
    return __jsb_cpArbiter_getShapes(cx, args, (cpArbiter*)handle, 1);
}

#pragma mark - Body

#pragma mark constructor

// Manually added to identify static vs dynamic bodies
bool JSB_cpBody_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");
    JS::RootedObject bodyProto(cx, JSB_cpBody_object);
    JSObject *jsobj = JS_NewObject(cx, JSB_cpBody_class, bodyProto, JS::NullPtr());
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    double m = 0; double i = 0;

    ok &= JS::ToNumber( cx, args.get(0), &m );
    ok &= JS::ToNumber( cx, args.get(1), &i );
    JSB_PRECONDITION(ok, "Error processing arguments");

    cpBody *ret_body = NULL;
    if( m == INFINITY && i == INFINITY) {
        ret_body = cpBodyNewStatic();

        // XXX: Hack. IT WILL LEAK "rogue" objects., But at least it prevents a crash.
        // The thing is that "rogue" bodies needs to be freed after the its shape, and I am not sure
        // how to do it in a "js" way.
        jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_DO_NOT_CALL_FREE);
    } else {
        ret_body = cpBodyNew((cpFloat)m , (cpFloat)i  );
        jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_CALL_FREE);
    }

    jsb_set_jsobject_for_proxy(jsobj, ret_body);

    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    return true;
}

#pragma mark getUserData

static
bool __jsb_cpBody_getUserData(JSContext *cx, const JS::CallArgs& args, cpBody *body)
{
    JSObject *data = (JSObject*) cpBodyGetUserData(body);
    args.rval().set(OBJECT_TO_JSVAL(data));

    return true;
}

// free function
bool JSB_cpBodyGetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    cpBody *body = nullptr;
    if( ! jsval_to_opaque( cx, args.get(0), (void**) &body ) )
        return false;

    return __jsb_cpBody_getUserData(cx, args, body);
}

// method
bool JSB_cpBody_getUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;
    return __jsb_cpBody_getUserData(cx, args, (cpBody*)handle);
}


#pragma mark setUserData

static
bool __jsb_cpBody_setUserData(JSContext *cx, jsval *vp, jsval *argvp, cpBody *body)
{
    JS::RootedObject jsobj(cx);
    JS::RootedValue jsv(cx, *argvp);
    bool ok = JS_ValueToObject(cx, jsv, &jsobj);

    JSB_PRECONDITION(ok, "Error parsing arguments");

    cpBodySetUserData(body, jsobj);

    return true;
}

// free function
bool JSB_cpBodySetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==2, cx, false, "Invalid number of arguments");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    cpBody *body = nullptr;
    jsval* argvp = args.array();
    JS::RootedValue jsarg(cx, *argvp++);
    bool ok = jsval_to_opaque(cx, jsarg, (void**) &body);
    JSB_PRECONDITION(ok, "Error parsing arguments");
    return __jsb_cpBody_setUserData(cx, vp, argvp, body);
}

// method
bool JSB_cpBody_setUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;
    return __jsb_cpBody_setUserData(cx, vp, args.array(), (cpBody*)handle);
}

#pragma mark - Poly related

// Chipmunk v7.0: Arguments: int, cpVect*, cpFloat
// Chipmunk v6.2: Arguments: int, cpVect*
// cpFloat cpAreaForPoly(const int count, const cpVect *verts, cpFloat radius);
bool JSB_cpAreaForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==2 || argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cpVect *verts = nullptr;
    int numVerts = 0;
    double radius=0;

    ok &= jsval_to_array_of_cpvect( cx, args.get(0), &verts, &numVerts);
    if (argc==2) // Chipmunk v7.0 only
        ok &= JS::ToNumber(cx, args.get(1), &radius);
    JSB_PRECONDITION2(ok, cx, false, "Error parsing array");

    cpFloat area = cpAreaForPoly(numVerts, verts, radius);

    free(verts);

    args.rval().set(DOUBLE_TO_JSVAL(area));
    return true;
}

// Chipmunk v7.0: Arguments: cpFloat, int, cpVect*, cpVect, cpFloat
// Chipmunk v6.2: Arguments: cpFloat, int, cpVect*, cpVect
// cpFloat cpMomentForPoly(cpFloat m, int count, const cpVect *verts, cpVect offset, cpFloat radius);
bool JSB_cpMomentForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==4 || argc==3, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cpVect *verts = nullptr;
    cpVect offset;
    int numVerts = 0;
    double m = 0;
    double radius=0;

    ok &= JS::ToNumber(cx, args.get(0), &m);
    ok &= jsval_to_array_of_cpvect( cx, args.get(1), &verts, &numVerts);
    ok &= jsval_to_cpVect( cx, args.get(2), (cpVect*) &offset );

    if (argc==4) // Chipmunk v7.0 only
        ok &= JS::ToNumber(cx, args.get(3), &radius);

    JSB_PRECONDITION2(ok, cx, false, "Error parsing args");

    cpFloat moment = cpMomentForPoly((cpFloat)m, numVerts, verts, offset, radius);

    free(verts);

    args.rval().set(DOUBLE_TO_JSVAL(moment));
    return true;
}

// cpVect cpCentroidForPoly(const int numVerts, const cpVect *verts);
bool JSB_cpCentroidForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cpVect *verts = nullptr;
    int numVerts = 0;

    ok &= jsval_to_array_of_cpvect( cx, args.get(0), &verts, &numVerts);
    JSB_PRECONDITION2(ok, cx, false, "Error parsing args");

    cpVect centroid = cpCentroidForPoly(numVerts, verts);

    free(verts);

    args.rval().set(cpVect_to_jsval(cx, (cpVect)centroid));
    return true;
}

// void cpRecenterPoly(const int numVerts, cpVect *verts);
bool JSB_cpRecenterPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCASSERT(false, "NOT IMPLEMENTED");
    return false;
}

#pragma mark - Object Oriented Chipmunk

/*
 * Chipmunk Base Object
 */

JSClass* JSB_cpBase_class = NULL;
JSObject* JSB_cpBase_object = NULL;
// Constructor
bool JSB_cpBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc==1, cx, false, "Invalid arguments. Expecting 1");
    JS::RootedObject baseProto(cx, JSB_cpBase_object);
    JSObject *jsobj = JS_NewObject(cx, JSB_cpBase_class, baseProto, JS::NullPtr());

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    void *handle = NULL;

    ok = jsval_to_opaque(cx, args.get(0), &handle);

    JSB_PRECONDITION(ok, "Error converting arguments for JSB_cpBase_constructor");

    jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
    jsb_set_jsobject_for_proxy(jsobj, handle);

    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    return true;
}

// Destructor
void JSB_cpBase_finalize(JSFreeOp *fop, JSObject *obj)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cpBase)", obj);
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);

    js_proxy_t* nproxy = nullptr;
    js_proxy_t* jsproxy = nullptr;
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy)
    {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

bool JSB_cpBase_getHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");
    JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments");

    struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
    void *handle = proxy->handle;

    jsval ret_val = opaque_to_jsval(cx, handle);
    args.rval().set(ret_val);
    return true;
}

bool JSB_cpBase_setHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
    JSB_PRECONDITION( jsthis, "Invalid jsthis object");
    JSB_PRECONDITION2(argc==1, cx, false, "Invalid number of arguments");

    void *handle = nullptr;
    bool ok = jsval_to_opaque(cx, args.get(0), &handle);
    JSB_PRECONDITION( ok, "Invalid parsing arguments");

    jsb_set_c_proxy_for_jsobject(jsthis, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
    jsb_set_jsobject_for_proxy(jsthis, handle);

    args.rval().setUndefined();
    return true;
}


void JSB_cpBase_createClass(JSContext *cx, JS::HandleObject globalObj, const char* name )
{
    JSB_cpBase_class = (JSClass *)calloc(1, sizeof(JSClass));
    JSB_cpBase_class->name = name;
    JSB_cpBase_class->addProperty = JS_PropertyStub;
    JSB_cpBase_class->delProperty = JS_DeletePropertyStub;
    JSB_cpBase_class->getProperty = JS_PropertyStub;
    JSB_cpBase_class->setProperty = JS_StrictPropertyStub;
    JSB_cpBase_class->enumerate = JS_EnumerateStub;
    JSB_cpBase_class->resolve = JS_ResolveStub;
    JSB_cpBase_class->convert = JS_ConvertStub;
    JSB_cpBase_class->finalize = JSB_cpBase_finalize;
    JSB_cpBase_class->flags = JSCLASS_HAS_PRIVATE;

    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("getHandle", JSB_cpBase_getHandle, 0, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FN("setHandle", JSB_cpBase_setHandle, 1, JSPROP_PERMANENT  | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    JSB_cpBase_object = JS_InitClass(cx, globalObj, JS::NullPtr(), JSB_cpBase_class, JSB_cpBase_constructor,0,properties,funcs,NULL,st_funcs);
}

// Chipmunk v7.0: Arguments: cpBody*, int, const cpVect *, cpTransform, cpFloat
// Chipmunk v6.2: Arguments: cpBody*, int, const cpVect *, cpVect
// Manual "methods"
// Constructor
// cpShape* cpPolyShapeNew(cpBody *body, int count, const cpVect *verts, cpTransform transform, cpFloat radius);
bool JSB_cpPolyShape_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==4 || argc==3, cx, false, "Invalid number of arguments");
    JS::RootedObject polyShapeProto(cx, JSB_cpPolyShape_object);
    JSObject *jsobj = JS_NewObject(cx, JSB_cpPolyShape_class, polyShapeProto, JS::NullPtr());
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cpBody* body = nullptr; cpVect *verts = nullptr;
    cpTransform transform; double radius=0;
    int numVerts = 0;

    ok &= jsval_to_c_class( cx, args.get(0), (void**)&body, NULL );
    ok &= jsval_to_array_of_cpvect( cx, args.get(1), &verts, &numVerts);
    if (argc==4) { // Chipmunk v7.0
        ok &= jsval_to_cpTransform(cx, args.get(2), &transform);
        ok &= JS::ToNumber(cx, args.get(3), &radius);
    } else { // Chipmunk v6.2
        cpVect tmpVect;
        ok &= jsval_to_cpVect(cx, args.get(2), &tmpVect);
        transform = cpTransformIdentity;
        transform.tx = tmpVect.x;
        transform.ty = tmpVect.y;
    }
    JSB_PRECONDITION(ok, "Error processing arguments");
    cpShape *shape = cpPolyShapeNew(body, numVerts, verts, transform, radius);

    jsb_set_c_proxy_for_jsobject(jsobj, shape, JSB_C_FLAG_CALL_FREE);
    jsb_set_jsobject_for_proxy(jsobj, shape);

    args.rval().set(OBJECT_TO_JSVAL(jsobj));

    free(verts);

    return true;
}

bool JSB_cpPolyShape_getVerts(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(args.thisv().toObjectOrNull());
    const cpPolyShape* polyShape = (cpPolyShape*) proxy->handle;
    int numVerts = cpPolyShapeGetCount(&polyShape->shape);

    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
    int i = 0;
    while (i < numVerts) {
        cpVect vec = cpPolyShapeGetVert(&polyShape->shape, i);

        JS::RootedValue x(cx);
        JS::RootedValue y(cx);
        x = DOUBLE_TO_JSVAL(vec.x);
        y = DOUBLE_TO_JSVAL(vec.y);
        JS_SetElement(cx, jsretArr, i*2, x);
        JS_SetElement(cx, jsretArr, i*2+1, y);
        i++;
    }
    args.rval().set(OBJECT_TO_JSVAL(jsretArr));
    return true;
}

// FIXME: Chipmunk v7.0. Not present
//static bool js_get_cpPolyShape_planes(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(args.thisv().toObjectOrNull());
//    cpPolyShape* shape = (cpPolyShape*) proxy->handle;
//    int numVerts = shape->numVerts;
//    cpSplittingPlane* planes = shape->planes;
//
//    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
//    int i = 0;
//    while(i < numVerts){
//        cpSplittingPlane *plane = planes + i;
//        JS::RootedValue elem(cx);
//
//        JS::RootedObject jsobj(cx, jsb_get_jsobject_for_proxy(plane));
//        if(!jsobj)
//        {
//            JS::RootedObject splittingPlaneProto(cx, JSB_cpSplittingPlane_object);
//            jsobj = JS_NewObject(cx, JSB_cpSplittingPlane_class, splittingPlaneProto, JS::NullPtr());
//            jsb_set_jsobject_for_proxy(jsobj, plane);
//            jsb_set_c_proxy_for_jsobject(jsobj, plane, JSB_C_FLAG_DO_NOT_CALL_FREE);
//        }
//
//        elem = OBJECT_TO_JSVAL(jsobj);
//        JS_SetElement(cx, jsretArr, i, elem);
//        i++;
//    }
//    args.rval().set(OBJECT_TO_JSVAL(jsretArr));
//    return true;
//}

#pragma mark Space Free functions
//
// When the space is removed, it should all remove its children. But not "free" them.
// "free" will be performed by the JS Garbage Collector
//
// Functions copied & pasted from ChipmunkDemo.c
// https://github.com/slembcke/Chipmunk-Physics/blob/master/Demo/ChipmunkDemo.c#L89
//

static void unroot_jsobject_from_handle(void *handle)
{
    JSObject *jsobj = jsb_get_jsobject_for_proxy(handle);
    //2014.9.19 by joshua
    //add safe guard
    if(jsobj)
    {
        struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);

        // HACK context from global
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RemoveObjectRoot(cx, &proxy->jsobj);
    }

}
static void shapeFreeWrap(cpSpace *space, cpShape *shape, void *unused){
    cpSpaceRemoveShape(space, shape);
    unroot_jsobject_from_handle(shape);
    //  cpShapeFree(shape);
}

static void postShapeFree(cpShape *shape, cpSpace *space){
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)shapeFreeWrap, shape, NULL);
}

static void constraintFreeWrap(cpSpace *space, cpConstraint *constraint, void *unused){
    cpSpaceRemoveConstraint(space, constraint);
    unroot_jsobject_from_handle(constraint);
    //  cpConstraintFree(constraint);
}

static void postConstraintFree(cpConstraint *constraint, cpSpace *space){
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)constraintFreeWrap, constraint, NULL);
}

static void bodyFreeWrap(cpSpace *space, cpBody *body, void *unused){
    cpSpaceRemoveBody(space, body);
    unroot_jsobject_from_handle(body);
    //  cpBodyFree(body);
}

static void postBodyFree(cpBody *body, cpSpace *space){
    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)bodyFreeWrap, body, NULL);
}

// Safe and future proof way to remove and free all objects that have been added to the space.
void static freeSpaceChildren(cpSpace *space)
{
    // Must remove these BEFORE freeing the body or you will access dangling pointers.
    cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)postShapeFree, space);
    cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)postConstraintFree, space);
    
    cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)postBodyFree, space);
}

// Chipmunk v7.0: Arguments: int, cpVect, cpVect, cpFloat
// Chipmunk v6.2: Arguments: int, cpVect, cpVect
// Ret value: int
// cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b, cpFloat radius);
bool JSB_cpMomentForSegment(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc == 3 || argc == 4, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    int arg_idx=0; // #001
    bool ok = true;
    int32_t arg0; cpVect arg1; cpVect arg2;
    double arg3 = 0;

    ok &= jsval_to_int32( cx, args.get(arg_idx++), &arg0 );
    ok &= jsval_to_cpVect( cx, args.get(arg_idx++), (cpVect*) &arg1 );
    ok &= jsval_to_cpVect( cx, args.get(arg_idx++), (cpVect*) &arg2 );
    if (argc == 4) // chipmunk v7.0 only
        ok &= JS::ToNumber( cx, args.get(arg_idx++), &arg3 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    double ret_val;

    ret_val = cpMomentForSegment((int)arg0 , (cpVect)arg1 , (cpVect)arg2 , arg3  );

    args.rval().set(DOUBLE_TO_JSVAL(ret_val));
    
    return true;
}


#endif // JSB_INCLUDE_CHIPMUNK
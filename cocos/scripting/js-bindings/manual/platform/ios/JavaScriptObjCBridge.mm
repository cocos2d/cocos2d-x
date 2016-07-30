/*
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

#import <Foundation/Foundation.h>

#import "scripting/js-bindings/manual/platform/ios/JavaScriptObjCBridge.h"
#include "scripting/js-bindings/manual/spidermonkey_specifics.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/js_manual_conversions.h"

JavaScriptObjCBridge::CallInfo::~CallInfo(void)
{
    if (m_returnType == TypeString)
    {
        delete m_ret.stringValue;
    }
}
JS::Value JavaScriptObjCBridge::convertReturnValue(JSContext *cx, ReturnValue retValue, ValueType type)
{
    JS::Value ret = JSVAL_NULL;
    
    switch (type)
    {
        case TypeInteger:
            return INT_TO_JSVAL(retValue.intValue);
        case TypeFloat:
            return DOUBLE_TO_JSVAL((double)retValue.floatValue);
        case TypeBoolean:
            return BOOLEAN_TO_JSVAL(retValue.boolValue);
        case TypeString:
            return c_string_to_jsval(cx, retValue.stringValue->c_str(),retValue.stringValue->size());
        default:
            break;
    }
    
    return ret;
}

bool JavaScriptObjCBridge::CallInfo::execute(JSContext *cx,jsval *argv,unsigned argc)
{
    
    NSString * className =[NSString stringWithCString: m_className.c_str() encoding:NSUTF8StringEncoding];
    NSString *methodName = [NSString stringWithCString: m_methodName.c_str() encoding:NSUTF8StringEncoding];
    
    bool ok = true;
    NSMutableDictionary *m_dic = [NSMutableDictionary dictionary];
    for(int i = 2;i<argc;i++){
        jsval arg = argv[i];
        NSString *key = [NSString stringWithFormat:@"argument%d" ,i-2];

        if(arg.isObject() || arg.isObject()){
            m_dic = NULL;
            m_error = JSO_ERR_TYPE_NOT_SUPPORT;
            return false;
        }else if(arg.isString()){
            JSStringWrapper valueWapper(arg.toString(), cx);
            [m_dic setObject:[NSString stringWithCString:valueWapper.get() encoding:NSUTF8StringEncoding] forKey:key];
        }else if(arg.isNumber()){
            double a;
            JS::RootedValue jsa(cx,arg);
            ok &= JS::ToNumber(cx, jsa, &a);

            [m_dic setObject:[NSNumber numberWithFloat:a] forKey:key];
        }else if(arg.isBoolean()){
            JS::RootedValue jsa(cx,arg);
            bool a = JS::ToBoolean(jsa);
            [m_dic setObject:[NSNumber numberWithBool:a] forKey:key];
        }
    }
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    if(!className || !methodName){
        m_error = JSO_ERR_INVALID_AEGUMENTS;
        return false;
    }
    Class targetClass = NSClassFromString(className);
    if(!targetClass){
        m_error = JSO_ERR_CLASS_NOT_FOUND;
        return false;
    }
    SEL methodSel;
    methodSel = NSSelectorFromString(methodName);
    if(!methodSel){
        m_error = JSO_ERR_METHOD_NOT_FOUND;
        return false;
    }
    methodSel = NSSelectorFromString(methodName);
    NSMethodSignature *methodSig = [targetClass methodSignatureForSelector:(SEL)methodSel];
    if(methodSig == nil){
        m_error =  JSO_ERR_METHOD_NOT_FOUND;
        return false;
    }
    @try {
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:methodSig];
        [invocation setTarget:targetClass];
        [invocation setSelector:methodSel];
        if(m_dic != nil){
            for(int i = 2;i<m_dic.count+2;i++){
                id obj = [m_dic objectForKey:[NSString stringWithFormat:@"argument%d",i-2] ];

                if ([obj isKindOfClass:[NSNumber class]] &&
                    ((strcmp([obj objCType], "c") == 0 || strcmp([obj objCType], "B") == 0))) //BOOL
                {
                    bool b = [obj boolValue];
                    [invocation setArgument:&b atIndex:i];
                }
                else
                {
                    [invocation setArgument:&obj atIndex:i];
                }
            }
        }
        NSUInteger returnLength = [methodSig methodReturnLength];
        const char *returnType = [methodSig methodReturnType];
        [invocation invoke];
        
        if(returnLength >0){
            if (strcmp(returnType, "@") == 0)
            {
                id ret;
                [invocation getReturnValue:&ret];
                pushValue(ret);
            }
            else if (strcmp(returnType, "c") == 0 || strcmp(returnType, "B") == 0) // BOOL
            {
                char ret;
                [invocation getReturnValue:&ret];
                m_ret.boolValue = ret;
                m_returnType = TypeBoolean;
            }
            else if (strcmp(returnType, "i") == 0) // int
            {
                int ret;
                [invocation getReturnValue:&ret];
                m_ret.intValue = ret;
                m_returnType = TypeInteger;
            }
            else if (strcmp(returnType, "f") == 0) // float
            {
                float ret;
                [invocation getReturnValue:&ret];
                m_ret.floatValue = ret;
                m_returnType = TypeFloat;
            }
            else
            {
                 m_error = JSO_ERR_TYPE_NOT_SUPPORT;
                NSLog(@"not support return type = %s", returnType);
                return false;
            }
        }else{
            m_returnType = TypeVoid;
        }
    }@catch(NSException *exception){
        NSLog(@"EXCEPTION THROW: %@", exception);
        m_error = JSO_ERR_EXCEPTION_OCCURRED;
        return false;
    }
    
    return true;
}
void JavaScriptObjCBridge::CallInfo::pushValue(void *val){
    id oval = (id)val;
    if (oval == nil)
    {
        return;
    }
    else if ([oval isKindOfClass:[NSNumber class]])
    {
        NSNumber *number = (NSNumber *)oval;
        const char *numberType = [number objCType];
        if (strcmp(numberType, @encode(BOOL)) == 0)
        {
            m_ret.boolValue = [number boolValue];
            m_returnType = TypeBoolean;
        }
        else if (strcmp(numberType, @encode(int)) == 0)
        {
            m_ret.intValue = [number intValue];
            m_returnType = TypeInteger;
        }
        else
        {
            m_ret.floatValue = [number floatValue];
            m_returnType = TypeFloat;
        }
    }
    else if ([oval isKindOfClass:[NSString class]])
    {
        const char *content = [oval cStringUsingEncoding:NSUTF8StringEncoding];
        m_ret.stringValue = new (std::nothrow) string(content);
        m_returnType = TypeString;
    }
    else if ([oval isKindOfClass:[NSDictionary class]])
    {

    }
    else
    {
        const char *content = [[NSString stringWithFormat:@"%@", oval] cStringUsingEncoding:NSUTF8StringEncoding];
        m_ret.stringValue =  new string(content);
        m_returnType = TypeString;
    }
}
/**
 *  @brief Initialize Object and needed properties.
 *
 */
JS_BINDED_CLASS_GLUE_IMPL(JavaScriptObjCBridge);

/**
 *  @brief Implementation for the Javascript Constructor
 *
 */
JS_BINDED_CONSTRUCTOR_IMPL(JavaScriptObjCBridge)
{
    JavaScriptObjCBridge* jsj = new (std::nothrow) JavaScriptObjCBridge();
    
    js_proxy_t *p;
    jsval out;
    
    JS::RootedObject proto(cx, JavaScriptObjCBridge::js_proto);
    JS::RootedObject parentProto(cx, JavaScriptObjCBridge::js_parent);
    JS::RootedObject obj(cx, JS_NewObject(cx, &JavaScriptObjCBridge::js_class, proto, parentProto));
    
    if (obj) {
        JS_SetPrivate(obj, jsj);
        out = OBJECT_TO_JSVAL(obj);
    }
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().set(out);
    p = jsb_new_proxy(jsj, obj);
    
    JS::AddNamedObjectRoot(cx, &p->obj, "JavaScriptObjCBridge");
    return true;
}

/**
 *  @brief destructor for Javascript
 *
 */
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj)
{
    CCLOG("basic_object_finalize %p ...", obj);
    
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

JS_BINDED_FUNC_IMPL(JavaScriptObjCBridge, callStaticMethod){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc >= 2) {
        JSStringWrapper arg0(args.get(0));
        JSStringWrapper arg1(args.get(1));
        CallInfo call(arg0.get(),arg1.get());
        bool ok = call.execute(cx,args.array(),argc);
        if(!ok){
            JS_ReportError(cx, "js_cocos2dx_JSObjCBridge : call result code: %d", call.getErrorCode());
            return false;
        }
        args.rval().set(convertReturnValue(cx, call.getReturnValue(), call.getReturnValueType()));
        return ok;
    }
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}

/**
 *  @brief register JavascriptJavaBridge to be usable in js
 *
 */
void JavaScriptObjCBridge::_js_register(JSContext *cx, JS::HandleObject global)
{
    JSClass jsclass = {
        "JavaScriptObjCBridge", JSCLASS_HAS_PRIVATE, JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,basic_object_finalize
    };
    
    JavaScriptObjCBridge::js_class = jsclass;
    static JSPropertySpec props[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE ),
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_BINDED_FUNC_FOR_DEF(JavaScriptObjCBridge, callStaticMethod),
        JS_FS_END
    };
    
    JavaScriptObjCBridge::js_parent = NULL;
    JavaScriptObjCBridge::js_proto = JS_InitClass(cx, global, JS::NullPtr(), &JavaScriptObjCBridge::js_class , JavaScriptObjCBridge::_js_constructor, 0, props, funcs, NULL, NULL);
}



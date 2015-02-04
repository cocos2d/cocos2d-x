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

#import "JavaScriptObjCBridge.h"
#include "spidermonkey_specifics.h"
#include "ScriptingCore.h"
#include "js_manual_conversions.h"
#include "cocos2d.h"
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
        int type = JS_TypeOfValue(cx,arg);
        if(type == JSTYPE_VOID || type == JSTYPE_OBJECT || type == JSTYPE_FUNCTION){
            m_dic = NULL;
            m_error = JSO_ERR_TYPE_NOT_SUPPORT;
            return false;
        }else if(type == JSTYPE_STRING){
            JSStringWrapper valueWapper(JSVAL_TO_STRING(arg), cx);
            [m_dic setObject:[NSString stringWithCString:valueWapper.get() encoding:NSUTF8StringEncoding] forKey:key];
        }else if(type == JSTYPE_NUMBER){
            double a;
            ok &= JS::ToNumber(cx, JS::RootedValue(cx,arg), &a);

            [m_dic setObject:[NSNumber numberWithFloat:a] forKey:key];
        }else if(type == JSTYPE_BOOLEAN){
            bool a = JS::ToBoolean(JS::RootedValue(cx,arg));
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
                [invocation setArgument:&obj atIndex:i];
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
        m_ret.stringValue = new string(content);
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
    JavaScriptObjCBridge* jsj = new JavaScriptObjCBridge();
    
    js_proxy_t *p;
    jsval out;
    
    JSObject *obj = JS_NewObject(cx, &JavaScriptObjCBridge::js_class, JavaScriptObjCBridge::js_proto, JavaScriptObjCBridge::js_parent);
    
    if (obj) {
        JS_SetPrivate(obj, jsj);
        out = OBJECT_TO_JSVAL(obj);
    }
    
    JS_SET_RVAL(cx, vp, out);
    p =jsb_new_proxy(jsj, obj);
    
    JS_AddNamedObjectRoot(cx, &p->obj, "JavaScriptObjCBridge");
    return true;
}

/**
 *  @brief destructor for Javascript
 *
 */
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj)
{
    CCLOG("basic_object_finalize %p ...", obj);
}
JS_BINDED_FUNC_IMPL(JavaScriptObjCBridge, callStaticMethod){
    jsval *argv = JS_ARGV(cx, vp);
    if (argc >= 2) {
        JSStringWrapper arg0(argv[0]);
        JSStringWrapper arg1(argv[1]);
        CallInfo call(arg0.get(),arg1.get());
        bool ok = call.execute(cx,argv,argc);
        if(!ok){
            JS_ReportError(cx, "js_cocos2dx_JSJavaBridge : call result code: %d", call.getErrorCode());
            return false;
        }
        JS_SET_RVAL(cx, vp, convertReturnValue(cx, call.getReturnValue(), call.getReturnValueType()));
        return ok;
    }
    return false;
}
static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
/**
 *  @brief register JavascriptJavaBridge to be usable in js
 *
 */
void JavaScriptObjCBridge::_js_register(JSContext *cx, JSObject *global)
{
    JSClass jsclass = {
        "JavaScriptObjCBridge", JSCLASS_HAS_PRIVATE, JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,basic_object_finalize, JSCLASS_NO_OPTIONAL_MEMBERS
    };
    
    JavaScriptObjCBridge::js_class = jsclass;
    static JSPropertySpec props[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_BINDED_FUNC_FOR_DEF(JavaScriptObjCBridge, callStaticMethod),
        JS_FS_END
    };
    
    JavaScriptObjCBridge::js_parent = NULL;
    JavaScriptObjCBridge::js_proto = JS_InitClass(cx, global, NULL, &JavaScriptObjCBridge::js_class , JavaScriptObjCBridge::_js_constructor, 0, props, funcs, NULL, NULL);
}



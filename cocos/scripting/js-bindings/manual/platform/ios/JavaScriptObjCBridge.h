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



#include <string>
#include <vector>
#include "scripting/js-bindings/manual/jsb_helper.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "scripting/js-bindings/manual/js_bindings_config.h"
using namespace std;

#define JSO_ERR_OK                 (0)
#define JSO_ERR_TYPE_NOT_SUPPORT   (-1)
#define JSO_ERR_INVALID_AEGUMENTS  (-2)
#define JSO_ERR_METHOD_NOT_FOUND   (-3)
#define JSO_ERR_EXCEPTION_OCCURRED (-4)
#define JSO_ERR_CLASS_NOT_FOUND    (-5)
#define JSO_ERR_VM_FAILURE         (-6)

class JavaScriptObjCBridge{
    
private:
    typedef enum : char
    {
        TypeInvalid = -1,
        TypeVoid    = 0,
        TypeInteger = 1,
        TypeFloat   = 2,
        TypeBoolean = 3,
        TypeString  = 4,
        TypeVector  = 5,
        TypeFunction= 6,
    } ValueType;
    typedef vector<ValueType> ValueTypes;
    
    typedef union
    {
        int     intValue;
        float   floatValue;
        int     boolValue;
        string *stringValue;
    } ReturnValue;
    class CallInfo
    {
    public:
        CallInfo(const char *className, const char *methodName)
        :m_valid(false)
        ,m_error(JSO_ERR_OK)
        ,m_argumentsCount(0)
        ,m_methodName(methodName)
        ,m_className(className)
        ,m_returnType(TypeVoid)
        {
        }
        ~CallInfo(void);
        bool isValid(void) {
            return m_valid;
        }
        
        int getErrorCode(void) {
            return m_error;
        }
        ValueType getReturnValueType(){
        	return m_returnType;
        }
        ReturnValue getReturnValue(){
        	return m_ret;
        }
        bool execute(JSContext *cx,jsval *argv,unsigned argc);
    private:
        bool m_valid;
        int m_error;
        int m_argumentsCount;
        string m_className;
        string m_methodName;
        ValueTypes m_argumentsType;
        ValueType m_returnType;
        ReturnValue m_ret;
        string m_retjstring;
        void pushValue(void *val);
    };
    JS::Value convertReturnValue(JSContext *cx, ReturnValue retValue, ValueType type);
public:
    JS_BINDED_CLASS_GLUE(JSObjCBridge);
    JS_BINDED_CONSTRUCTOR(JSObjCBridge);
    JS_BINDED_FUNC(JSObjCBridge, callStaticMethod);
};
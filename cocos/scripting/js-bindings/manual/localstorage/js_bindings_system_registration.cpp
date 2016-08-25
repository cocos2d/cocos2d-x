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

#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/js_bindings_core.h"
#include "storage/local-storage/LocalStorage.h"
#include "platform/CCFileUtils.h"

// system
#include "scripting/js-bindings/manual/localstorage/js_bindings_system_functions.h"


void jsb_register_system( JSContext *_cx,  JS::HandleObject object)
{
    //
    // sys
    //
    JS::RootedObject proto(_cx);
    JS::RootedObject parent(_cx);
    JS::RootedObject sys(_cx, JS_NewObject(_cx, nullptr, proto, parent));
    JS::RootedValue systemVal(_cx);
    systemVal.set(OBJECT_TO_JSVAL(sys));
    JS_SetProperty(_cx, object, "sys", systemVal);


    // sys.localStorage
    JSObject *ls = JS_NewObject(_cx, nullptr, proto, parent);
    JS::RootedValue lsVal(_cx);
    lsVal.set(OBJECT_TO_JSVAL(ls));
    JS_SetProperty(_cx, sys, "localStorage", lsVal);

    // sys.localStorage functions
    JS::RootedObject system(_cx, ls);
#include "scripting/js-bindings/manual/localstorage/js_bindings_system_functions_registration.h"
    
    // Init DB with full path
    //NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    //NSString *fullpath = [path stringByAppendingPathComponent:@"jsb.sqlite"];
    std::string strFilePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    strFilePath += "/jsb.sqlite";
    localStorageInit(strFilePath);
    
}


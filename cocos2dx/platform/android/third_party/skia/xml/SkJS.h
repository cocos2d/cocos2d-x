/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SkTypes.h"
#include "SkWindow.h"

extern "C" {
    typedef long JSWord;
    typedef JSWord jsword;
    typedef jsword  jsval;
    typedef struct JSRuntime JSRuntime;
    typedef struct JSContext JSContext;
    typedef struct JSObject JSObject;
}

class SkString;

class SkJS : public SkOSWindow {
public:
    SkJS(void* hwnd);
    ~SkJS();
    SkBool EvaluateScript(const char* script, jsval* rVal);
    SkBool ValueToString(jsval value, SkString* string);
#ifdef SK_DEBUG
    static void Test(void* hwnd);
#endif
protected:
    void InitializeDisplayables(const SkBitmap& , JSContext *, JSObject *, JSObject *);
    void DisposeDisplayables();
    JSRuntime *fRuntime;
    JSContext *fContext;
    JSObject *fGlobal;
};


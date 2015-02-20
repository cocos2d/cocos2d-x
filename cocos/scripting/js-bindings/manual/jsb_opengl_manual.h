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


#ifndef __jsb_opengl_manual
#define __jsb_opengl_manual

#include "js_bindings_config.h"
#ifdef JSB_INCLUDE_OPENGL

//#include <Availability.h>
#include "jsapi.h"
#include "jsfriendapi.h"

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

// compatible with iOS
#define glClearDepthf glClearDepth
#define glDepthRangef glDepthRange
#ifndef glReleaseShaderCompiler
    #define glReleaseShaderCompiler()
#endif

#endif // __MAC_OS_X_VERSION_MAX_ALLOWED

// forward declaration of new functions
bool JSB_glGetSupportedExtensions(JSContext *cx, uint32_t argc, jsval *vp);


#endif // JSB_INCLUDE_OPENGL

#endif // __jsb_opengl_manual

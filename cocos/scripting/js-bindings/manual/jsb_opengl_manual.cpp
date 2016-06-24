/*
 * Copyright (c) 2013 Zynga Inc.
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
#ifdef JSB_INCLUDE_OPENGL

#include "scripting/js-bindings/manual/jsb_opengl_manual.h"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "scripting/js-bindings/manual/js_bindings_core.h"
#include "scripting/js-bindings/manual/jsb_opengl_functions.h"
#include "platform/CCGL.h"


// Helper functions that link "glGenXXXs" (OpenGL ES 2.0 spec), with "gl.createXXX" (WebGL spec)
bool JSB_glGenTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    GLuint texture;
    glGenTextures(1, &texture);

    args.rval().set(INT_TO_JSVAL(texture));
    return true;
}

bool JSB_glGenBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    args.rval().set(INT_TO_JSVAL(buffer));
    return true;
}

bool JSB_glGenRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    GLuint renderbuffers;
    glGenRenderbuffers(1, &renderbuffers);
    args.rval().set(INT_TO_JSVAL(renderbuffers));
    return true;
}

bool JSB_glGenFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    GLuint framebuffers;
    glGenFramebuffers(1, &framebuffers);
    args.rval().set(INT_TO_JSVAL(framebuffers));
    return true;
}

bool JSB_glDeleteTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    glDeleteTextures(1, &arg0);
    args.rval().set(JSVAL_VOID);
    return true;
}

bool JSB_glDeleteBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    glDeleteBuffers(1, &arg0);
    args.rval().set(JSVAL_VOID);
    return true;
}

bool JSB_glDeleteRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    glDeleteRenderbuffers(1, &arg0);
    args.rval().set(JSVAL_VOID);
    return true;
}

bool JSB_glDeleteFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    glDeleteFramebuffers(1, &arg0);
    args.rval().set(JSVAL_VOID);
    return true;
}

bool JSB_glShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0; const char *arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_charptr(cx, args.get(1), &arg1);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    glShaderSource(arg0, 1, &arg1, NULL);
    args.rval().set(JSVAL_VOID);
    return true;
}

bool JSB_glGetShaderiv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLint ret;
    glGetShaderiv(arg0, arg1, &ret);
    args.rval().set(INT_TO_JSVAL(ret));
    return true;
}

bool JSB_glGetProgramiv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLint ret;
    glGetProgramiv(arg0, arg1, &ret);
    args.rval().set(INT_TO_JSVAL(ret));
    return true;
}

bool JSB_glGetProgramInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_INFO_LOG_LENGTH, &length);
    GLchar* src = new (std::nothrow) GLchar[length];
    glGetProgramInfoLog(arg0, length, NULL, src);
    
    args.rval().set(charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}

// DOMString? getShaderInfoLog(WebGLShader? shader);
bool JSB_glGetShaderInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetShaderiv(arg0, GL_INFO_LOG_LENGTH, &length);
    GLchar* src = new (std::nothrow) GLchar[length];
    glGetShaderInfoLog(arg0, length, NULL, src);
    
    args.rval().set(charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}

// DOMString? getShaderSource(WebGLShader? shader);
bool JSB_glGetShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetShaderiv(arg0, GL_SHADER_SOURCE_LENGTH, &length);
    GLchar* src = new (std::nothrow) GLchar[length];
    glGetShaderSource(arg0, length, NULL, src);

    args.rval().set(charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}

//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
// WebGLActiveInfo? getActiveAttrib(WebGLProgram? program, GLuint index);
bool JSB_glGetActiveAttrib(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    GLchar* buffer = new (std::nothrow) GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    glGetActiveAttrib(arg0, arg1, length, NULL, &size, &type, buffer);

    jsval retval = JSVAL_VOID;

    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    JSB_PRECONDITION2(ok, cx, false, "Error creating JS Object");

    JS::RootedValue jsname(cx, charptr_to_jsval(cx, buffer));
    if (!JS_DefineProperty(cx, object, "size", (int32_t)size, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "type", (int32_t)type, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return false;

    retval = OBJECT_TO_JSVAL(object);

    args.rval().set(retval);
    CC_SAFE_DELETE_ARRAY(buffer);
    return true;
}


//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
//  };
// WebGLActiveInfo? getActiveUniform(WebGLProgram? program, GLuint index);
bool JSB_glGetActiveUniform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    GLchar* buffer = new (std::nothrow) GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, buffer);

    jsval retval = JSVAL_VOID;

    
    JS::RootedObject object(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr() ));
    JSB_PRECONDITION2(ok, cx, false, "Error creating JS Object");

    JS::RootedValue jsname(cx, charptr_to_jsval(cx, buffer));
    if (!JS_DefineProperty(cx, object, "size", (int32_t)size, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "type", (int32_t)type, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return false;

    retval = OBJECT_TO_JSVAL(object);

    args.rval().set(retval);
    CC_SAFE_DELETE_ARRAY(buffer);
    return true;
}

// sequence<WebGLShader>? getAttachedShaders(WebGLProgram? program);
bool JSB_glGetAttachedShaders(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ATTACHED_SHADERS, &length);
    GLuint* buffer = new (std::nothrow) GLuint[length];
    memset(buffer, 0, length * sizeof(GLuint));
    //Fix bug 2448, it seems that glGetAttachedShaders will crash if we send NULL to the third parameter (eg Windows), same as in lua binding
    GLsizei realShaderCount = 0;
    glGetAttachedShaders(arg0, length, &realShaderCount, buffer);
    
    JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, length));
    JSB_PRECONDITION2(jsobj, cx, false, "Error creating JS Object");

    for( int i=0; i<length; i++) {
        JS::RootedValue e(cx, INT_TO_JSVAL(buffer[i]));
        JS_SetElement(cx, jsobj, i, e );
    }

    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    CC_SAFE_DELETE_ARRAY(buffer);
    return true;

}

// sequence<DOMString>? getSupportedExtensions();
bool JSB_glGetSupportedExtensions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);

    JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, 0));
    JSB_PRECONDITION2(jsobj, cx, false, "Error creating JS Object");

    // copy, to be able to add '\0'
    size_t len = strlen((char*)extensions);
    GLubyte* copy = new (std::nothrow) GLubyte[len+1];
    strncpy((char*)copy, (const char*)extensions, len );

    size_t start_extension = 0;
    int element=0;
    for( size_t i=0; i<len+1; i++) {
        if( copy[i]==' ' || copy[i]==',' || i==len ) {
            copy[i] = 0;

            JS::RootedValue str(cx, charptr_to_jsval(cx, (const char*)&copy[start_extension]));
            JS_SetElement(cx, jsobj, element++, str );

            start_extension = i+1;

            i++;
        }
    }

    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    CC_SAFE_DELETE_ARRAY(copy);
    return true;
    
}

// any getTexParameter(GLenum target, GLenum pname);
bool JSB_glGetTexParameterfv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "JSB_glGetTexParameterfv: Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );

    JSB_PRECONDITION2(ok, cx, false, "JSB_glGetTexParameterfv: Error processing arguments");

    GLfloat param;
    glGetTexParameterfv(arg0, arg1, &param);

    args.rval().set(DOUBLE_TO_JSVAL(param));
    return true;
}

// any getUniform(WebGLProgram? program, WebGLUniformLocation? location);
bool JSB_glGetUniformfv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, false, "JSB_glGetUniformfv: Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, args.get(0), &arg0 );
    ok &= jsval_to_uint( cx, args.get(1), &arg1 );

    JSB_PRECONDITION2(ok, cx, false, "JSB_glGetUniformfv: Error processing arguments");

    GLint activeUniforms;
    glGetProgramiv(arg0, GL_ACTIVE_UNIFORMS, &activeUniforms);
    
    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
    GLchar* namebuffer = new (std::nothrow) GLchar[length+1];
    GLint size = -1;
    GLenum type = -1;

    bool isLocationFound = false;
    for(int i = 0; i  <  activeUniforms; ++i)
    {
        glGetActiveUniform(arg0, i, length, NULL, &size, &type, namebuffer);
        if(arg1 == glGetUniformLocation(arg0, namebuffer))
        {
            isLocationFound = true;
            break;
        }
    }
    if(!isLocationFound)
    {
        size = -1;
        type = -1;
    }
    CC_SAFE_DELETE_ARRAY(namebuffer);

    int usize = 0;
    int utype = 0;
    switch(type) {

        // float
        case GL_FLOAT:
            usize = 1;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT2:
            usize = 2 * 2;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT3:
            usize = 3 * 3;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT4:
            usize = 4 * 4;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC2:
            usize = 2;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC3:
            usize = 3;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC4:
            usize = 4;
            utype = GL_FLOAT;           
            break;

        // int
        case GL_INT:
            usize = 1;
            utype = GL_INT;
            break;
        case GL_INT_VEC2:
            usize = 1;
            utype = GL_INT;
            break;
        case GL_INT_VEC3:
            usize = 1;
            utype = GL_INT;
            break;
        case GL_INT_VEC4:
            usize = 1;
            utype = GL_INT;
            break;

        default:
            JSB_PRECONDITION2(false, cx, false, "JSB_glGetUniformfv: Uniform Type not supported");
    }

    JSObject *typedArray = NULL;
    if( utype == GL_FLOAT) {
        // FIXME: glew on windows will cause array overflow after invoking glGetUniformfv.
        // It seems that glGetUniformfv re-assign the memory with a wrong size which is 4x than we pass in.
        // For temporary solution, we allocate 4x array. 
        GLfloat* param = new (std::nothrow) GLfloat[usize*4];
        glGetUniformfv(arg0, arg1, param);

        typedArray = JS_NewFloat32Array(cx, usize);
        float *buffer = (float*)JS_GetArrayBufferViewData(typedArray);
        memcpy( buffer, param, sizeof(float) * usize);
        CC_SAFE_DELETE_ARRAY(param);
    } else if( utype == GL_INT ) {
        // FIXME: glew on windows will cause array overflow after invoking glGetUniformfv.
        // It seems that glGetUniformfv re-assign the memory with a wrong size which is 4x than we pass in.
        // For temporary solution, we allocate 4x array. 
        GLint* param = new (std::nothrow) GLint[usize*4];
        glGetUniformiv(arg0, arg1, param);

        typedArray = JS_NewInt32Array(cx, usize);
        GLint *buffer = (GLint*)JS_GetArrayBufferViewData(typedArray);
        memcpy( buffer, param, sizeof(GLint) * usize);
        CC_SAFE_DELETE_ARRAY(param);
    }

    args.rval().set(OBJECT_TO_JSVAL(typedArray));
    return true;
}


#endif // JSB_INCLUDE_OPENGL

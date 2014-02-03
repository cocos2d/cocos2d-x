/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2013 Zynga Inc.
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


#include "js_bindings_config.h"
#ifdef JSB_INCLUDE_OPENGL

#include "jsapi.h"
#include "jsfriendapi.h"

#include "jsb_opengl_manual.h"
#include "js_manual_conversions.h"
#include "js_bindings_core.h"
#include "jsb_opengl_functions.h"


// Helper functions that link "glGenXXXs" (OpenGL ES 2.0 spec), with "gl.createXXX" (WebGL spec)
JSBool JSB_glGenTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

    GLuint texture;
    glGenTextures(1, &texture);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(texture));
    return JS_TRUE;
}

JSBool JSB_glGenBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

    GLuint buffer;
    glGenBuffers(1, &buffer);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(buffer));
    return JS_TRUE;
}

JSBool JSB_glGenRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

    GLuint renderbuffers;
    glGenRenderbuffers(1, &renderbuffers);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(renderbuffers));
    return JS_TRUE;
}

JSBool JSB_glGenFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

    GLuint framebuffers;
    glGenFramebuffers(1, &framebuffers);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(framebuffers));
    return JS_TRUE;
}

JSBool JSB_glDeleteTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    glDeleteTextures(1, &arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool JSB_glDeleteBuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    glDeleteBuffers(1, &arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool JSB_glDeleteRenderbuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    glDeleteRenderbuffers(1, &arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool JSB_glDeleteFramebuffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    glDeleteFramebuffers(1, &arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool JSB_glShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0; const char *arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_charptr(cx, *argvp++, &arg1);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    glShaderSource(arg0, 1, &arg1, NULL);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

JSBool JSB_glGetShaderiv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLint ret;
    glGetShaderiv(arg0, arg1, &ret);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret));
    return JS_TRUE;
}

JSBool JSB_glGetProgramiv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLint ret;
    glGetProgramiv(arg0, arg1, &ret);
    JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret));
    return JS_TRUE;
}

JSBool JSB_glGetProgramInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_INFO_LOG_LENGTH, &length);
    GLchar* src = new GLchar[length];
    glGetProgramInfoLog(arg0, length, NULL, src);
    
    JS_SET_RVAL(cx, vp, charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return JS_TRUE;
}

// DOMString? getShaderInfoLog(WebGLShader? shader);
JSBool JSB_glGetShaderInfoLog(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetShaderiv(arg0, GL_INFO_LOG_LENGTH, &length);
    GLchar* src = new GLchar[length];
    glGetShaderInfoLog(arg0, length, NULL, src);
    
    JS_SET_RVAL(cx, vp, charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return JS_TRUE;
}

// DOMString? getShaderSource(WebGLShader? shader);
JSBool JSB_glGetShaderSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetShaderiv(arg0, GL_SHADER_SOURCE_LENGTH, &length);
    GLchar* src = new GLchar[length];
    glGetShaderSource(arg0, length, NULL, src);

    JS_SET_RVAL(cx, vp, charptr_to_jsval(cx, src));
    CC_SAFE_DELETE_ARRAY(src);
    return JS_TRUE;
}

//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
// WebGLActiveInfo? getActiveAttrib(WebGLProgram? program, GLuint index);
JSBool JSB_glGetActiveAttrib(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    GLchar* buffer = new GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    glGetActiveAttrib(arg0, arg1, length, NULL, &size, &type, buffer);

    jsval retval = JSVAL_VOID;

    JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error creating JS Object");

    if (!JS_DefineProperty(cx, object, "size", INT_TO_JSVAL(size), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "type", INT_TO_JSVAL(type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "name", charptr_to_jsval(cx, buffer), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JS_FALSE;

    retval = OBJECT_TO_JSVAL(object);

    JS_SET_RVAL(cx, vp, retval);
    CC_SAFE_DELETE_ARRAY(buffer);
    return JS_TRUE;
}


//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
//  };
// WebGLActiveInfo? getActiveUniform(WebGLProgram? program, GLuint index);
JSBool JSB_glGetActiveUniform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    GLchar* buffer = new GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, buffer);

    jsval retval = JSVAL_VOID;


    JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error creating JS Object");

    if (!JS_DefineProperty(cx, object, "size", INT_TO_JSVAL(size), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "type", INT_TO_JSVAL(type), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
        !JS_DefineProperty(cx, object, "name", charptr_to_jsval(cx, buffer), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
        return JS_FALSE;

    retval = OBJECT_TO_JSVAL(object);

    JS_SET_RVAL(cx, vp, retval);
    CC_SAFE_DELETE_ARRAY(buffer);
    return JS_TRUE;
}

// sequence<WebGLShader>? getAttachedShaders(WebGLProgram? program);
JSBool JSB_glGetAttachedShaders(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 1, cx, JS_FALSE, "Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ATTACHED_SHADERS, &length);
    GLuint* buffer = new GLuint[length];
    memset(buffer, 0, length * sizeof(GLuint));
    //Fix bug 2448, it seems that glGetAttachedShaders will crash if we send NULL to the third parameter (eg Windows), same as in lua binding
    GLsizei realShaderCount = 0;
    glGetAttachedShaders(arg0, length, &realShaderCount, buffer);
    
    JSObject *jsobj = JS_NewArrayObject(cx, length, NULL);
    JSB_PRECONDITION2(jsobj, cx, JS_FALSE, "Error creating JS Object");

    for( int i=0; i<length; i++) {
        jsval e = INT_TO_JSVAL(buffer[i]);
        JS_SetElement(cx, jsobj, i, &e );
    }

    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
    CC_SAFE_DELETE_ARRAY(buffer);
    return JS_TRUE;

}

// sequence<DOMString>? getSupportedExtensions();
JSBool JSB_glGetSupportedExtensions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 0, cx, JS_FALSE, "Invalid number of arguments" );

    const GLubyte *extensions = glGetString(GL_EXTENSIONS);

    JSObject *jsobj = JS_NewArrayObject(cx, 0, NULL);
    JSB_PRECONDITION2(jsobj, cx, JS_FALSE, "Error creating JS Object");

    // copy, to be able to add '\0'
    size_t len = strlen((char*)extensions);
    GLubyte* copy = new GLubyte[len+1];
    strncpy((char*)copy, (const char*)extensions, len );

    int start_extension=0;
    int element=0;
    for( int i=0; i<len+1; i++) {
        if( copy[i]==' ' || copy[i]==',' || i==len ) {
            copy[i] = 0;

            jsval str = charptr_to_jsval(cx, (const char*)&copy[start_extension]);
            JS_SetElement(cx, jsobj, element++, &str );

            start_extension = i+1;

            i++;
        }
    }

    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
    CC_SAFE_DELETE_ARRAY(copy);
    return JS_TRUE;
    
}

// any getTexParameter(GLenum target, GLenum pname);
JSBool JSB_glGetTexParameterfv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "JSB_glGetTexParameterfv: Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "JSB_glGetTexParameterfv: Error processing arguments");

    GLfloat param;
    glGetTexParameterfv(arg0, arg1, &param);

    JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(param));
    return JS_TRUE;
}

// any getUniform(WebGLProgram? program, WebGLUniformLocation? location);
JSBool JSB_glGetUniformfv(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2( argc == 2, cx, JS_FALSE, "JSB_glGetUniformfv: Invalid number of arguments" );
    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;
    uint32_t arg0, arg1;

    ok &= jsval_to_uint( cx, *argvp++, &arg0 );
    ok &= jsval_to_uint( cx, *argvp++, &arg1 );

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "JSB_glGetUniformfv: Error processing arguments");

    GLsizei length;
    glGetProgramiv(arg0, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
    GLchar* namebuffer = new GLchar[length+1];
    GLint size = -1;
    GLenum type = -1;

    glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, namebuffer);
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
            JSB_PRECONDITION2(false, cx, JS_FALSE, "JSB_glGetUniformfv: Uniform Type not supported");
    }

    JSObject *typedArray = NULL;
    if( utype == GL_FLOAT) {
        // FIXME: glew on windows will cause array overflow after invoking glGetUniformfv.
        // It seems that glGetUniformfv re-assign the memeroy with a wrong size which is 4x than we pass in.
        // For temporary solution, we allocate 4x array. 
        GLfloat* param = new GLfloat[usize*4];
        glGetUniformfv(arg0, arg1, param);

        typedArray = JS_NewFloat32Array(cx, usize);
        float *buffer = (float*)JS_GetArrayBufferViewData(typedArray);
        memcpy( buffer, param, sizeof(float) * usize);
        CC_SAFE_DELETE_ARRAY(param);
    } else if( utype == GL_INT ) {
        // FIXME: glew on windows will cause array overflow after invoking glGetUniformfv.
        // It seems that glGetUniformfv re-assign the memeroy with a wrong size which is 4x than we pass in.
        // For temporary solution, we allocate 4x array. 
        GLint* param = new GLint[usize*4];
        glGetUniformiv(arg0, arg1, param);

        typedArray = JS_NewInt32Array(cx, usize);
        GLint *buffer = (GLint*)JS_GetArrayBufferViewData(typedArray);
        memcpy( buffer, param, sizeof(GLint) * usize);
        CC_SAFE_DELETE_ARRAY(param);
    }

    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(typedArray));
    return JS_TRUE;
}


#endif // JSB_INCLUDE_OPENGL

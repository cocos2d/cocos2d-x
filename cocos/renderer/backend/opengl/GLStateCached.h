#pragma once

#include "platform/CCGL.h"
#include "renderer/backend/Macros.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN

class GL
{
public:
    static void enable(GLenum cap);
    static void disable(GLenum cap);
    static void depthMask(GLboolean flag);
    static void depthFunc(GLenum func);
    static void frontFace(GLenum mode);
    static void stencilFunc(GLenum func, GLint ref, GLuint mask);
    static void stencilOp(GLenum sfail, GLenum zfail, GLenum zpass);
    static void stencilMask(GLuint mask);
    static void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
    static void stencilOpSeparate(GLenum face, GLenum sfail, GLenum zfail, GLenum zpass);
    static void stencilMaskSeparate(GLenum face, GLuint mask);
    static void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
    static void blendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
    static void cullFace(GLenum mode);
    static void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    static void bindBuffer(GLenum target, GLuint buffer);
    static void bindFramebuffer(GLenum target, GLuint framebuffer);
    static void activeTexture(GLenum texture);
    static void bindTexture(GLenum target, GLuint texture);

    static void getBooleanv(GLenum pname, GLboolean *params);
    static void getFloatv(GLenum pname, GLfloat *params);
    static void getIntegerv(GLenum pname, GLint *params);

    struct DefaultGLState 
    {
        Viewport viewport;
        GLboolean scissorEnabled = GL_FALSE;

        GLboolean redColorMask = GL_TRUE;
        GLboolean greenColorMask = GL_TRUE;
        GLboolean blueColorMask = GL_TRUE;
        GLboolean alphaColorMask = GL_TRUE;

        GLboolean cullingEnabled = GL_FALSE;
        GLenum cullFace = GL_BACK;
        GLenum frontFace = GL_CCW;

        GLboolean depthEnabled = GL_FALSE;
        GLboolean depthMask = GL_TRUE;
        GLenum depthFunc = GL_LESS;

        GLboolean stencilEnabled = GL_FALSE;
        GLint frontStencilReference = GL_ZERO;
        GLint backStencilReference = GL_ZERO;
        GLenum frontStencilComparedFunc = GL_ALWAYS;
        GLenum backStencilComparedFunc = GL_ALWAYS;
        GLuint frontStencilReadMask = GL_ONE;
        GLuint backStencilReadMask = GL_ONE;
        GLuint frontStencilWriteMask = GL_ONE;
        GLuint backStencilWriteMask = GL_ONE;
        GLenum frontStencilSFailOperation = GL_KEEP;
        GLenum frontStencilZFailOperation = GL_KEEP;
        GLenum frontStencilZPassOperation = GL_KEEP;
        GLenum backStencilSFailOperation = GL_KEEP;
        GLenum backStencilZFailOperation = GL_KEEP;
        GLenum backStencilZPassOperation = GL_KEEP;

        GLboolean blendEnabled = GL_FALSE;
        GLenum rgbBlendEquation = GL_FUNC_ADD;
        GLenum alphaBlendEquation = GL_FUNC_ADD;
        GLenum srcRGBBlendFactor = GL_ONE;
        GLenum srcAlphaBlendFactor = GL_ONE;
        GLenum dstRGBBlendFactor = GL_ZERO;
        GLenum dstALphaBlendFactor = GL_ZERO;

        GLenum bufferTarget = GL_ARRAY_BUFFER;
        GLuint bufferObject = GL_ZERO;
        GLuint framebufferObject = GL_ZERO;

        GLenum textureUnit = GL_TEXTURE0;
        GLenum textureTarget = GL_TEXTURE_2D;
        GLuint textureObject = GL_ZERO;
    };
private:
    static DefaultGLState _defaultGLState;
};

CC_BACKEND_END
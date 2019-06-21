#include "GLStateCached.h"
CC_BACKEND_BEGIN

#define GL_STATE_CACHED_ENABLED
#ifdef GL_STATE_CACHED_ENABLED
#define RETURN() return;
#else
#define RETURN()
#endif

GL::DefaultGLState GL::_defaultGLState;

void GL::enable(GLenum cap)
{
    switch(cap)
    {
        case GL_DEPTH_TEST:
            if (_defaultGLState.depthEnabled)
                RETURN();
            glEnable(GL_DEPTH_TEST);
            _defaultGLState.depthEnabled = GL_TRUE;
            break;
        case GL_STENCIL_TEST:
            if (_defaultGLState.stencilEnabled)
                RETURN();
            glEnable(GL_STENCIL_TEST);
            _defaultGLState.stencilEnabled = GL_TRUE;
            break;
        case GL_BLEND:
            if (_defaultGLState.blendEnabled)
                RETURN();
            glEnable(GL_BLEND);
            _defaultGLState.blendEnabled = GL_TRUE;
            break;
        case GL_CULL_FACE:
            if (_defaultGLState.cullingEnabled)
                RETURN();
            glEnable(GL_CULL_FACE);
            _defaultGLState.cullingEnabled = GL_TRUE;
            break;
        case GL_SCISSOR_TEST:
            if (_defaultGLState.scissorEnabled)
                RETURN();
            glEnable(GL_SCISSOR_TEST);
            _defaultGLState.scissorEnabled = GL_TRUE;
            break;
        default:
            CCASSERT(0, "Not Implemented");
            break;
    }
}

void GL::disable(GLenum cap)
{
    switch(cap)
    {
    case GL_DEPTH_TEST:
        if (!_defaultGLState.depthEnabled)
            RETURN();
        glDisable(GL_DEPTH_TEST);
        _defaultGLState.depthEnabled = GL_FALSE;
        break;
    case GL_STENCIL_TEST:
        if (!_defaultGLState.stencilEnabled)
            RETURN();
        glDisable(GL_STENCIL_TEST);
        _defaultGLState.stencilEnabled = GL_FALSE;
        break;
    case GL_BLEND:
        if (!_defaultGLState.blendEnabled)
            RETURN();
        glDisable(GL_BLEND);
        _defaultGLState.blendEnabled = GL_FALSE;
        break;
    case GL_CULL_FACE:
        if (!_defaultGLState.cullingEnabled)
            RETURN();
        glDisable(GL_CULL_FACE);
        _defaultGLState.cullingEnabled = GL_FALSE;
        break;
    case GL_SCISSOR_TEST:
        if (!_defaultGLState.scissorEnabled)
            RETURN();
        glDisable(GL_SCISSOR_TEST);
        _defaultGLState.scissorEnabled = GL_FALSE;
        break;
    default:
        CCASSERT(0, "Not Implemented");
        break;
    }
}

void GL::depthMask(GLboolean flag)
{
    if (flag)
    {
        if (_defaultGLState.depthMask)
            RETURN();

        glDepthMask(GL_TRUE);
        _defaultGLState.depthMask = GL_TRUE;
    }
    else
    {
        if (!_defaultGLState.depthMask)
            RETURN();

        glDepthMask(GL_FALSE);
        _defaultGLState.depthMask = GL_FALSE;
    }
}

void GL::depthFunc(GLenum func)
{
    if (func == _defaultGLState.depthFunc)
        RETURN();

    glDepthFunc(func);
    _defaultGLState.depthFunc = func;
}

void GL::frontFace(GLenum mode)
{
    if (mode == _defaultGLState.frontFace)
        RETURN();

    glFrontFace(mode);
    _defaultGLState.frontFace = mode;
}

void GL::stencilFunc(GLenum func, GLint ref, GLuint mask)
{
    if (func == _defaultGLState.frontStencilComparedFunc &&
        ref == _defaultGLState.frontStencilReference &&
        mask == _defaultGLState.frontStencilReadMask)
        RETURN();

    glStencilFunc(func, ref, mask);
    _defaultGLState.frontStencilComparedFunc = _defaultGLState.backStencilComparedFunc = func;
    _defaultGLState.frontStencilReference = _defaultGLState.backStencilReference = ref;
    _defaultGLState.frontStencilReadMask = _defaultGLState.backStencilReadMask = mask;
}

void GL::stencilOp(GLenum sfail, GLenum zfail, GLenum zpass)
{
    if (sfail == _defaultGLState.frontStencilSFailOperation &&
        zfail == _defaultGLState.frontStencilZFailOperation &&
        zpass == _defaultGLState.frontStencilZPassOperation)
        RETURN();

    glStencilOp(sfail, zfail, zpass);
    _defaultGLState.frontStencilSFailOperation = _defaultGLState.backStencilSFailOperation = sfail;
    _defaultGLState.frontStencilZFailOperation = _defaultGLState.backStencilZFailOperation = zfail;
    _defaultGLState.frontStencilZPassOperation = _defaultGLState.backStencilZPassOperation = zpass;
}

void GL::stencilMask(GLuint mask)
{
    if (mask == _defaultGLState.frontStencilWriteMask)
        RETURN();

    glStencilMask(mask);
    _defaultGLState.frontStencilWriteMask = _defaultGLState.frontStencilWriteMask = mask;
}

void GL::stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
    if (face == GL_FRONT)
    {
        if (func == _defaultGLState.frontStencilComparedFunc &&
            ref == _defaultGLState.frontStencilReference &&
            mask == _defaultGLState.frontStencilReadMask)
            RETURN();

        glStencilFuncSeparate(GL_FRONT, func, ref, mask);
        _defaultGLState.frontStencilComparedFunc = func;
        _defaultGLState.frontStencilReference = ref;
        _defaultGLState.frontStencilReadMask = mask;
    }
    else
    {
        if (func == _defaultGLState.backStencilComparedFunc &&
            ref == _defaultGLState.backStencilReference &&
            mask == _defaultGLState.backStencilReadMask)
            RETURN();

        glStencilFuncSeparate(GL_BACK, func, ref, mask);
        _defaultGLState.backStencilComparedFunc = func;
        _defaultGLState.backStencilReference = ref;
        _defaultGLState.backStencilReadMask = mask;
    }
}

void GL::stencilOpSeparate(GLenum face, GLenum sfail, GLenum zfail, GLenum zpass)
{
    if (face == GL_FRONT)
    {
        if (sfail == _defaultGLState.frontStencilSFailOperation &&
            zfail == _defaultGLState.frontStencilZFailOperation &&
            zpass == _defaultGLState.frontStencilZPassOperation)
            RETURN();

        glStencilOpSeparate(GL_FRONT, sfail, zfail, zpass);
        _defaultGLState.frontStencilSFailOperation = sfail;
        _defaultGLState.frontStencilZFailOperation = zfail;
        _defaultGLState.frontStencilZPassOperation = zpass;
    }
    else
    {
        if (sfail == _defaultGLState.backStencilSFailOperation &&
            zfail == _defaultGLState.backStencilZFailOperation &&
            zpass == _defaultGLState.backStencilZPassOperation)
            RETURN();

        glStencilOpSeparate(GL_BACK, sfail, zfail, zpass);
        _defaultGLState.backStencilSFailOperation = sfail;
        _defaultGLState.backStencilZFailOperation = zfail;
        _defaultGLState.backStencilZPassOperation = zpass;
    }
}

void GL::stencilMaskSeparate(GLenum face, GLuint mask)
{
    if (face == GL_FRONT)
    {
        if (mask == _defaultGLState.frontStencilWriteMask)
            RETURN();

        glStencilMaskSeparate(GL_FRONT, mask);
        _defaultGLState.frontStencilWriteMask = mask;
    }
    else
    {
        if (mask == _defaultGLState.backStencilWriteMask)
            RETURN();

        glStencilMaskSeparate(GL_BACK, mask);
        _defaultGLState.backStencilWriteMask = mask;
    }
}

void GL::blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
    if (modeRGB == _defaultGLState.rgbBlendEquation &&
        modeAlpha == _defaultGLState.alphaBlendEquation)
        RETURN();

    glBlendEquationSeparate(modeRGB, modeAlpha);
    _defaultGLState.rgbBlendEquation = modeRGB;
    _defaultGLState.alphaBlendEquation = modeAlpha;
}

void GL::blendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    if (sfactorRGB == _defaultGLState.srcRGBBlendFactor &&
        dfactorRGB == _defaultGLState.dstRGBBlendFactor &&
        sfactorAlpha == _defaultGLState.srcAlphaBlendFactor &&
        dfactorAlpha == _defaultGLState.dstALphaBlendFactor)
        RETURN();

    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    _defaultGLState.srcRGBBlendFactor = sfactorRGB;
    _defaultGLState.dstRGBBlendFactor = dfactorRGB;
    _defaultGLState.srcAlphaBlendFactor = sfactorAlpha;
    _defaultGLState.dstALphaBlendFactor = dfactorAlpha;
}

void GL::cullFace(GLenum mode)
{
    if (mode == _defaultGLState.cullFace)
        RETURN();

    glCullFace(mode);
    _defaultGLState.cullFace = mode;
}

void GL::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    if (red == _defaultGLState.redColorMask &&
        green == _defaultGLState.greenColorMask &&
        blue == _defaultGLState.blueColorMask &&
        alpha == _defaultGLState.alphaColorMask)
        RETURN();

    glColorMask(red, green, blue, alpha);
    _defaultGLState.redColorMask = red;
    _defaultGLState.greenColorMask = green;
    _defaultGLState.blueColorMask = blue;
    _defaultGLState.alphaColorMask = alpha;
}

void GL::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (x == _defaultGLState.viewport.x &&
        y == _defaultGLState.viewport.y &&
        width == _defaultGLState.viewport.w &&
        height == _defaultGLState.viewport.h)
        RETURN();

    glViewport(x, y, width, height);
    _defaultGLState.viewport = {x, y, (unsigned int)width, (unsigned int)height};
}

void GL::bindBuffer(GLenum target, GLuint buffer)
{
    if (target == _defaultGLState.bufferTarget &&
        buffer == _defaultGLState.bufferObject)
        RETURN();
    
    cocos2d::log("last bufferID = %d, current bufferID = %d", _defaultGLState.bufferObject, buffer );

    glBindBuffer(target, buffer);
    _defaultGLState.bufferTarget = target;
    _defaultGLState.bufferObject = buffer;
}

void GL::getBooleanv(GLenum pname, GLboolean *params)
{
#ifdef GL_STATE_CACHED_ENABLED
    switch (pname)
    {
    case GL_DEPTH_WRITEMASK:
        *params = _defaultGLState.depthMask;
        break;
    case GL_DEPTH_TEST:
        *params = _defaultGLState.depthEnabled;
        break;
    default:
        CCASSERT(0, "Not Implemented");
        break;
    }
#else
    glGetBooleanv(pname, params);
#endif
}

void GL::getFloatv(GLenum pname, GLfloat *params)
{
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, params);
}

void GL::getIntegerv(GLenum pname, GLint *params)
{
#ifdef GL_STATE_CACHED_ENABLED
    switch (pname)
    {
    case GL_DEPTH_FUNC:
        *params = _defaultGLState.depthFunc;
        break;
    default:
        CCASSERT(0, "Not Implemented");
        break;
    }
#else
    glGetIntegerv(GL_DEPTH_FUNC, params);
#endif
}

CC_BACKEND_END

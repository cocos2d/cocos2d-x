/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include "ccMacros.h"
#include "ccShaders.h"

NS_CC_BEGIN

enum {
    kShaderType_PositionTextureColor,
    kShaderType_PositionTextureColorAlphaTest,
    kShaderType_PositionColor,
    kShaderType_PositionTexture,
    kShaderType_PositionTexture_uColor,
    kShaderType_PositionTextureA8Color,
    kShaderType_Position_uColor,
    kShaderType_PositionLengthTexureColor,
    
    kShaderType_MAX,
};

static ShaderCache *_sharedShaderCache = 0;

ShaderCache* ShaderCache::sharedShaderCache()
{
    if (!_sharedShaderCache) {
        _sharedShaderCache = new ShaderCache();
        if (!_sharedShaderCache->init())
        {
            CC_SAFE_DELETE(_sharedShaderCache);
        }
    }
    return _sharedShaderCache;
}

void ShaderCache::purgeSharedShaderCache()
{
    CC_SAFE_RELEASE_NULL(_sharedShaderCache);
}

ShaderCache::ShaderCache()
: _programs(0)
{

}

ShaderCache::~ShaderCache()
{
    CCLOGINFO("cocos2d deallocing %p", this);
    _programs->release();
}

bool ShaderCache::init()
{
    _programs = new Dictionary();
    loadDefaultShaders();
    return true;
}

void ShaderCache::loadDefaultShaders()
{
    // Position Texture Color shader
    GLProgram *p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureColor);

    _programs->setObject(p, kShader_PositionTextureColor);
    p->release();

    // Position Texture Color alpha test
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureColorAlphaTest);

    _programs->setObject(p, kShader_PositionTextureColorAlphaTest);
    p->release();

    //
    // Position, Color shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionColor);

    _programs->setObject(p, kShader_PositionColor);
    p->release();

    //
    // Position Texture shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTexture);

    _programs->setObject(p, kShader_PositionTexture);
    p->release();

    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTexture_uColor);

    _programs->setObject(p ,kShader_PositionTexture_uColor);
    p->release();

    //
    // Position Texture A8 Color shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureA8Color);
    
    _programs->setObject(p, kShader_PositionTextureA8Color);
    p->release();

    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_Position_uColor);
    
    _programs->setObject(p, kShader_Position_uColor);
    p->release();
    
    //
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
	//
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionLengthTexureColor);
    
    _programs->setObject(p, kShader_PositionLengthTexureColor);
    p->release();
}

void ShaderCache::reloadDefaultShaders()
{
    // reset all programs and reload them
    
    // Position Texture Color shader
    GLProgram *p = programForKey(kShader_PositionTextureColor);    
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTextureColor);

    // Position Texture Color alpha test
    p = programForKey(kShader_PositionTextureColorAlphaTest);
    p->reset();    
    loadDefaultShader(p, kShaderType_PositionTextureColorAlphaTest);
    
    //
    // Position, Color shader
    //
    p = programForKey(kShader_PositionColor);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionColor);
    
    //
    // Position Texture shader
    //
    p = programForKey(kShader_PositionTexture);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTexture);
    
    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = programForKey(kShader_PositionTexture_uColor);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTexture_uColor);
    
    //
    // Position Texture A8 Color shader
    //
    p = programForKey(kShader_PositionTextureA8Color);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTextureA8Color);
    
    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = programForKey(kShader_Position_uColor);
    p->reset();
    loadDefaultShader(p, kShaderType_Position_uColor);
    
    //
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
	//
    p = programForKey(kShader_PositionLengthTexureColor);
    p->reset();
    loadDefaultShader(p, kShaderType_Position_uColor);
}

void ShaderCache::loadDefaultShader(GLProgram *p, int type)
{
    switch (type) {
        case kShaderType_PositionTextureColor:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);
            
            break;
        case kShaderType_PositionTextureColorAlphaTest:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);

            break;
        case kShaderType_PositionColor:  
            p->initWithVertexShaderByteArray(ccPositionColor_vert ,ccPositionColor_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameColor, kVertexAttrib_Color);

            break;
        case kShaderType_PositionTexture:
            p->initWithVertexShaderByteArray(ccPositionTexture_vert ,ccPositionTexture_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);

            break;
        case kShaderType_PositionTexture_uColor:
            p->initWithVertexShaderByteArray(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);

            break;
        case kShaderType_PositionTextureA8Color:
            p->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);

            break;
        case kShaderType_Position_uColor:
            p->initWithVertexShaderByteArray(ccPosition_uColor_vert, ccPosition_uColor_frag);    
            
            p->addAttribute("aVertex", kVertexAttrib_Position);    
            
            break;
        case kShaderType_PositionLengthTexureColor:
            p->initWithVertexShaderByteArray(ccPositionColorLengthTexture_vert, ccPositionColorLengthTexture_frag);
            
            p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
            p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);
            p->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
            
            break;
        default:
            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }
    
    p->link();
    p->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
}

GLProgram* ShaderCache::programForKey(const char* key)
{
    return (GLProgram*)_programs->objectForKey(key);
}

void ShaderCache::addProgram(GLProgram* program, const char* key)
{
    _programs->setObject(program, key);
}

NS_CC_END

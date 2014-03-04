/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
    kShaderType_PositionTextureColor_noMVP,
    kShaderType_PositionTextureColorAlphaTest,
    kShaderType_PositionColor,
    kShaderType_PositionColor_noMVP,
    kShaderType_PositionTexture,
    kShaderType_PositionTexture_uColor,
    kShaderType_PositionTextureA8Color,
    kShaderType_Position_uColor,
    kShaderType_PositionLengthTexureColor,
    kShaderType_LabelDistanceFieldNormal,
    kShaderType_LabelDistanceFieldGlow,
    kShaderType_LabelDistanceFieldOutline,
    kShaderType_LabelDistanceFieldShadow,
    kShaderType_MAX,
};

static ShaderCache *_sharedShaderCache = 0;

ShaderCache* ShaderCache::getInstance()
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

void ShaderCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedShaderCache);
}

// XXX: deprecated
ShaderCache* ShaderCache::sharedShaderCache()
{
    return ShaderCache::getInstance();
}

// XXX: deprecated
void ShaderCache::purgeSharedShaderCache()
{
    ShaderCache::destroyInstance();
}

ShaderCache::ShaderCache()
: _programs()
{

}

ShaderCache::~ShaderCache()
{
    for( auto it = _programs.begin(); it != _programs.end(); ++it ) {
        (it->second)->release();
    }

    CCLOGINFO("deallocing ShaderCache: %p", this);
}

bool ShaderCache::init()
{    
    loadDefaultShaders();
    return true;
}

void ShaderCache::loadDefaultShaders()
{
    // Position Texture Color shader
    GLProgram *p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureColor);
    _programs.insert( std::make_pair( GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, p ) );

    // Position Texture Color without MVP shader
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureColor_noMVP);
    _programs.insert( std::make_pair( GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, p ) );

    // Position Texture Color alpha test
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureColorAlphaTest);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST, p) );

    //
    // Position, Color shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionColor);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_COLOR, p) );

    //
    // Position, Color shader no MVP
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionColor_noMVP);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP, p) );

    //
    // Position Texture shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTexture);
    _programs.insert( std::make_pair( GLProgram::SHADER_NAME_POSITION_TEXTURE, p) );

    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTexture_uColor);
    _programs.insert( std::make_pair( GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR, p) );

    //
    // Position Texture A8 Color shader
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionTextureA8Color);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR, p) );

    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_Position_uColor);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_U_COLOR, p) );
    
    //
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
	//
    p = new GLProgram();
    loadDefaultShader(p, kShaderType_PositionLengthTexureColor);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR, p) );

    p = new GLProgram();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldNormal);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL, p) );

    p = new GLProgram();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldGlow);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW, p) );

    p = new GLProgram();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldOutline);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_OUTLINE, p) );

    p = new GLProgram();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldShadow);
    _programs.insert( std::make_pair(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_SHADOW, p) );
}

void ShaderCache::reloadDefaultShaders()
{
    // reset all programs and reload them
    
    // Position Texture Color shader
    GLProgram *p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);    
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTextureColor);

    // Position Texture Color without MVP shader
    p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
    p->reset();    
    loadDefaultShader(p, kShaderType_PositionTextureColor_noMVP);

    // Position Texture Color alpha test
    p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    p->reset();    
    loadDefaultShader(p, kShaderType_PositionTextureColorAlphaTest);
    
    //
    // Position, Color shader
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_COLOR);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionColor);
    
    //
    // Position, Color shader no MVP
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP);
    loadDefaultShader(p, kShaderType_PositionColor_noMVP);

    //
    // Position Texture shader
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTexture);
    
    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTexture_uColor);
    
    //
    // Position Texture A8 Color shader
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionTextureA8Color);
    
    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = getProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    p->reset();
    loadDefaultShader(p, kShaderType_Position_uColor);
    
    //
	// Position, Legth(TexCoords, Color (used by Draw Node basically )
	//
    p = getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR);
    p->reset();
    loadDefaultShader(p, kShaderType_PositionLengthTexureColor);

    p = getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL);
    p->reset();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldNormal);

    p = getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW);
    p->reset();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldGlow);

    p = getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_OUTLINE);
    p->reset();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldOutline);

    p = getProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_SHADOW);
    p->reset();
    loadDefaultShader(p, kShaderType_LabelDistanceFieldShadow);
}

void ShaderCache::loadDefaultShader(GLProgram *p, int type)
{
    switch (type) {
        case kShaderType_PositionTextureColor:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            
            break;
        case kShaderType_PositionTextureColor_noMVP:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, ccPositionTextureColor_noMVP_frag);

            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;

        case kShaderType_PositionTextureColorAlphaTest:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_PositionColor:  
            p->initWithVertexShaderByteArray(ccPositionColor_vert ,ccPositionColor_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);

            break;
        case kShaderType_PositionColor_noMVP:
            p->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert ,ccPositionColor_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            break;
        case kShaderType_PositionTexture:
            p->initWithVertexShaderByteArray(ccPositionTexture_vert ,ccPositionTexture_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_PositionTexture_uColor:
            p->initWithVertexShaderByteArray(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_PositionTextureA8Color:
            p->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_Position_uColor:
            p->initWithVertexShaderByteArray(ccPosition_uColor_vert, ccPosition_uColor_frag);    
            
            p->addAttribute("aVertex", GLProgram::VERTEX_ATTRIB_POSITION);    
            
            break;
        case kShaderType_PositionLengthTexureColor:
            p->initWithVertexShaderByteArray(ccPositionColorLengthTexture_vert, ccPositionColorLengthTexture_frag);
            
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            
            break;
        case kShaderType_LabelDistanceFieldNormal:
            p->initWithVertexShaderByteArray(ccLabelDistanceFieldNormal_vert, ccLabelDistanceFieldNormal_frag);

            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_LabelDistanceFieldGlow:
            p->initWithVertexShaderByteArray(ccLabelDistanceFieldGlow_vert, ccLabelDistanceFieldGlow_frag);

            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_LabelDistanceFieldOutline:
            p->initWithVertexShaderByteArray(ccLabelDistanceFieldOutline_vert, ccLabelDistanceFieldOutline_frag);

            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        case kShaderType_LabelDistanceFieldShadow:
            p->initWithVertexShaderByteArray(ccLabelDistanceFieldShadow_vert, ccLabelDistanceFieldShadow_frag);

            p->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
            p->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

            break;
        default:
            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }
    
    p->link();
    p->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
}

GLProgram* ShaderCache::getProgram(const std::string &key)
{
    auto it = _programs.find(key);
    if( it != _programs.end() )
        return it->second;
    return nullptr;
}

void ShaderCache::addProgram(GLProgram* program, const std::string &key)
{
    program->retain();
    _programs.insert( std::make_pair( key, program) );
}

NS_CC_END

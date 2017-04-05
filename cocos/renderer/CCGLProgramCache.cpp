/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "renderer/CCGLProgramCache.h"

#include "renderer/CCGLProgram.h"
#include "renderer/ccShaders.h"
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

enum {
    kShaderType_PositionTextureColor,
    kShaderType_PositionTextureColor_noMVP,
    kShaderType_PositionTextureColorAlphaTest,
    kShaderType_PositionTextureColorAlphaTestNoMV,
    kShaderType_PositionColor,
    kShaderType_PositionColorTextureAsPointsize,
    kShaderType_PositionColor_noMVP,
    kShaderType_PositionTexture,
    kShaderType_PositionTexture_uColor,
    kShaderType_PositionTextureA8Color,
    kShaderType_Position_uColor,
    kShaderType_PositionLengthTextureColor,
    kShaderType_LabelDistanceFieldNormal,
    kShaderType_LabelDistanceFieldGlow,
    kShaderType_UIGrayScale,
    kShaderType_LabelNormal,
    kShaderType_LabelOutline,
    kShaderType_3DPosition,
    kShaderType_3DPositionTex,
    kShaderType_3DSkinPositionTex,
    kShaderType_3DPositionNormal,
    kShaderType_3DPositionNormalTex,
    kShaderType_3DSkinPositionNormalTex,
    kShaderType_3DPositionBumpedNormalTex,
    kShaderType_3DSkinPositionBumpedNormalTex,
    kShaderType_3DParticleTex,
    kShaderType_3DParticleColor,
    kShaderType_3DSkyBox,
    kShaderType_3DTerrain,
    kShaderType_CameraClear,
    // ETC1 ALPHA supports.
    kShaderType_ETC1ASPositionTextureColor,
    kShaderType_ETC1ASPositionTextureColor_noMVP,

    kShaderType_ETC1ASPositionTextureGray,
    kShaderType_ETC1ASPositionTextureGray_noMVP,
    kShaderType_MAX,
};

static GLProgramCache *_sharedGLProgramCache = nullptr;

GLProgramCache* GLProgramCache::getInstance()
{
    if (!_sharedGLProgramCache) {
        _sharedGLProgramCache = new (std::nothrow) GLProgramCache();
        if (!_sharedGLProgramCache->init())
        {
            CC_SAFE_DELETE(_sharedGLProgramCache);
        }
    }
    return _sharedGLProgramCache;
}

void GLProgramCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedGLProgramCache);
}

// FIXME: deprecated
GLProgramCache* GLProgramCache::sharedShaderCache()
{
    return GLProgramCache::getInstance();
}

// FIXME: deprecated
void GLProgramCache::purgeSharedShaderCache()
{
    GLProgramCache::destroyInstance();
}

GLProgramCache::GLProgramCache()
: _programs()
{

}

GLProgramCache::~GLProgramCache()
{
    for(auto& program : _programs) {
        program.second->release();
    }

    CCLOGINFO("deallocing GLProgramCache: %p", this);
}

bool GLProgramCache::init()
{
    loadDefaultGLPrograms();
    
    auto listener = EventListenerCustom::create(Configuration::CONFIG_FILE_LOADED, [this](EventCustom* /*event*/){
        reloadDefaultGLProgramsRelativeToLights();
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, -1);
    
    return true;
}

void GLProgramCache::loadDefaultGLPrograms()
{
    // Position Texture Color shader
    GLProgram *p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColor);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, p);

    // Position Texture Color without MVP shader
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColor_noMVP);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, p);

    // Position Texture Color alpha test
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColorAlphaTest);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST, p);

    // Position Texture Color alpha test
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColorAlphaTestNoMV);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV, p);
    //
    // Position, Color shader
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionColor);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_COLOR, p);

    // Position, Color, PointSize shader
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionColorTextureAsPointsize);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE, p);

    //
    // Position, Color shader no MVP
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionColor_noMVP);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP, p);

    //
    // Position Texture shader
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTexture);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE, p);

    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTexture_uColor);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR, p);

    //
    // Position Texture A8 Color shader
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionTextureA8Color);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR, p);

    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_Position_uColor);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_U_COLOR, p);

    //
    // Position, Length(TexCoords, Color (used by Draw Node basically )
    //
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_PositionLengthTextureColor);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_LabelDistanceFieldNormal);
    _programs.emplace(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_LabelDistanceFieldGlow);
    _programs.emplace(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_UIGrayScale);
    _programs.emplace(GLProgram::SHADER_NAME_POSITION_GRAYSCALE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_LabelNormal);
    _programs.emplace(GLProgram::SHADER_NAME_LABEL_NORMAL, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_LabelOutline);
    _programs.emplace(GLProgram::SHADER_NAME_LABEL_OUTLINE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DPosition);
    _programs.emplace(GLProgram::SHADER_3D_POSITION, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DPositionTex);
    _programs.emplace(GLProgram::SHADER_3D_POSITION_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionTex);
    _programs.emplace(GLProgram::SHADER_3D_SKINPOSITION_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormal);
    _programs.emplace(GLProgram::SHADER_3D_POSITION_NORMAL, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormalTex);
    _programs.emplace(GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionNormalTex);
    _programs.emplace(GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DPositionBumpedNormalTex);
    _programs.emplace(GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionBumpedNormalTex);
    _programs.emplace(GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DParticleColor);
    _programs.emplace(GLProgram::SHADER_3D_PARTICLE_COLOR, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DParticleTex);
    _programs.emplace(GLProgram::SHADER_3D_PARTICLE_TEXTURE, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DSkyBox);
    _programs.emplace(GLProgram::SHADER_3D_SKYBOX, p);

    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_3DTerrain);
    _programs.emplace(GLProgram::SHADER_3D_TERRAIN, p);
    
    p = new (std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_CameraClear);
    _programs.emplace(GLProgram::SHADER_CAMERA_CLEAR, p);

    /// ETC1 ALPHA supports.
    p = new(std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureColor);
    _programs.emplace(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR, p);

    p = new(std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureColor_noMVP);
    _programs.emplace(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP, p);

    /// ETC1 Gray supports.
    p = new(std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureGray);
    _programs.emplace(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY, p);

    p = new(std::nothrow) GLProgram();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureGray_noMVP);
    _programs.emplace(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP, p);
}

void GLProgramCache::reloadDefaultGLPrograms()
{
    // reset all programs and reload them

    // Position Texture Color shader
    GLProgram *p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColor);

    // Position Texture Color without MVP shader
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColor_noMVP);

    // Position Texture Color alpha test
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColorAlphaTest);

    // Position Texture Color alpha test
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTextureColorAlphaTestNoMV);
    //
    // Position, Color shader
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionColor);

    // Position, Color, PointSize shader
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionColorTextureAsPointsize);

    //
    // Position, Color shader no MVP
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP);
    loadDefaultGLProgram(p, kShaderType_PositionColor_noMVP);

    //
    // Position Texture shader
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTexture);

    //
    // Position, Texture attribs, 1 Color as uniform shader
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTexture_uColor);

    //
    // Position Texture A8 Color shader
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionTextureA8Color);

    //
    // Position and 1 color passed as a uniform (to simulate glColor4ub )
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_Position_uColor);

    //
    // Position, Length(TexCoords, Color (used by Draw Node basically )
    //
    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_PositionLengthTextureColor);

    p = getGLProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_LabelDistanceFieldNormal);

    p = getGLProgram(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_LabelDistanceFieldGlow);

    p = getGLProgram(GLProgram::SHADER_NAME_POSITION_GRAYSCALE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_UIGrayScale);

    p = getGLProgram(GLProgram::SHADER_NAME_LABEL_NORMAL);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_LabelNormal);

    p = getGLProgram(GLProgram::SHADER_NAME_LABEL_OUTLINE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_LabelOutline);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPosition);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionTex);

    p = getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionTex);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormal);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionBumpedNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionBumpedNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_PARTICLE_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DParticleTex);

    p = getGLProgram(GLProgram::SHADER_3D_PARTICLE_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DParticleColor);

    p = getGLProgram(GLProgram::SHADER_3D_SKYBOX);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkyBox);

    p = getGLProgram(GLProgram::SHADER_3D_TERRAIN);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DTerrain);
    
    p = getGLProgram(GLProgram::SHADER_CAMERA_CLEAR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_CameraClear);

    // ETC1 ALPHA supports.
    p = getGLProgram(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureColor);

    p = getGLProgram(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureColor_noMVP);

    // ETC1 Gray supports.
    p = getGLProgram(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureGray);

    p = getGLProgram(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_ETC1ASPositionTextureGray_noMVP);
}

void GLProgramCache::reloadDefaultGLProgramsRelativeToLights()
{
    GLProgram *p = getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormal);
    
    p = getGLProgram(GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionNormalTex);
    
    p = getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DPositionBumpedNormalTex);

    p = getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE);
    p->reset();
    loadDefaultGLProgram(p, kShaderType_3DSkinPositionBumpedNormalTex);
}

void GLProgramCache::loadDefaultGLProgram(GLProgram *p, int type)
{
    switch (type) {
        case kShaderType_PositionTextureColor:
            p->initWithByteArrays(ccPositionTextureColor_vert, ccPositionTextureColor_frag);
            break;
        case kShaderType_PositionTextureColor_noMVP:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccPositionTextureColor_noMVP_frag);
            break;
        case kShaderType_PositionTextureColorAlphaTest:
            p->initWithByteArrays(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);
            break;
        case kShaderType_PositionTextureColorAlphaTestNoMV:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccPositionTextureColorAlphaTest_frag);
            break;
        case kShaderType_PositionColor:
            p->initWithByteArrays(ccPositionColor_vert ,ccPositionColor_frag);
            break;
        case kShaderType_PositionColorTextureAsPointsize:
            p->initWithByteArrays(ccPositionColorTextureAsPointsize_vert ,ccPositionColor_frag);
            break;
        case kShaderType_PositionColor_noMVP:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert ,ccPositionColor_frag);
            break;
        case kShaderType_PositionTexture:
            p->initWithByteArrays(ccPositionTexture_vert ,ccPositionTexture_frag);
            break;
        case kShaderType_PositionTexture_uColor:
            p->initWithByteArrays(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
            break;
        case kShaderType_PositionTextureA8Color:
            p->initWithByteArrays(ccPositionTextureA8Color_vert, ccPositionTextureA8Color_frag);
            break;
        case kShaderType_Position_uColor:
            p->initWithByteArrays(ccPosition_uColor_vert, ccPosition_uColor_frag);
            p->bindAttribLocation("aVertex", GLProgram::VERTEX_ATTRIB_POSITION);
            break;
        case kShaderType_PositionLengthTextureColor:
            p->initWithByteArrays(ccPositionColorLengthTexture_vert, ccPositionColorLengthTexture_frag);
            break;
        case kShaderType_LabelDistanceFieldNormal:
            p->initWithByteArrays(ccLabel_vert, ccLabelDistanceFieldNormal_frag);
            break;
        case kShaderType_LabelDistanceFieldGlow:
            p->initWithByteArrays(ccLabel_vert, ccLabelDistanceFieldGlow_frag);
            break;
        case kShaderType_UIGrayScale:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert,
                                  ccPositionTexture_GrayScale_frag);
            break;
        case kShaderType_LabelNormal:
            p->initWithByteArrays(ccLabel_vert, ccLabelNormal_frag);
            break;
        case kShaderType_LabelOutline:
            p->initWithByteArrays(ccLabel_vert, ccLabelOutline_frag);
            break;
        case kShaderType_3DPosition:
            p->initWithByteArrays(cc3D_PositionTex_vert, cc3D_Color_frag);
            break;
        case kShaderType_3DPositionTex:
            p->initWithByteArrays(cc3D_PositionTex_vert, cc3D_ColorTex_frag);
            break;
        case kShaderType_3DSkinPositionTex:
            p->initWithByteArrays(cc3D_SkinPositionTex_vert, cc3D_ColorTex_frag);
            break;
        case kShaderType_3DPositionNormal:
            {
                std::string def = getShaderMacrosForLight();
                p->initWithByteArrays((def + std::string(cc3D_PositionNormalTex_vert)).c_str(), (def + std::string(cc3D_ColorNormal_frag)).c_str());
            }
            break;
        case kShaderType_3DPositionNormalTex:
            {
                std::string def = getShaderMacrosForLight();
                p->initWithByteArrays((def + std::string(cc3D_PositionNormalTex_vert)).c_str(), (def + std::string(cc3D_ColorNormalTex_frag)).c_str());
            }
            break;
        case kShaderType_3DSkinPositionNormalTex:
            {
                std::string def = getShaderMacrosForLight();
                p->initWithByteArrays((def + std::string(cc3D_SkinPositionNormalTex_vert)).c_str(), (def + std::string(cc3D_ColorNormalTex_frag)).c_str());
            }
            break;
        case kShaderType_3DPositionBumpedNormalTex:
            {
                std::string def = getShaderMacrosForLight();
                std::string normalMapDef = "\n#define USE_NORMAL_MAPPING 1 \n";
                p->initWithByteArrays((def + normalMapDef + std::string(cc3D_PositionNormalTex_vert)).c_str(), (def + normalMapDef + std::string(cc3D_ColorNormalTex_frag)).c_str());
            }
            break;
        case kShaderType_3DSkinPositionBumpedNormalTex:
            {
                std::string def = getShaderMacrosForLight();
                std::string normalMapDef = "\n#define USE_NORMAL_MAPPING 1 \n";
                p->initWithByteArrays((def + normalMapDef + std::string(cc3D_SkinPositionNormalTex_vert)).c_str(), (def + normalMapDef + std::string(cc3D_ColorNormalTex_frag)).c_str());
            }
            break;
        case kShaderType_3DParticleTex:
           {
                p->initWithByteArrays(cc3D_Particle_vert, cc3D_Particle_tex_frag);
           }
            break;
        case kShaderType_3DParticleColor:
            p->initWithByteArrays(cc3D_Particle_vert, cc3D_Particle_color_frag);
            break;
        case kShaderType_3DSkyBox:
            p->initWithByteArrays(cc3D_Skybox_vert, cc3D_Skybox_frag);
            break;
        case kShaderType_3DTerrain:
            p->initWithByteArrays(cc3D_Terrain_vert, cc3D_Terrain_frag);
            break;
        case kShaderType_CameraClear:
            p->initWithByteArrays(ccCameraClearVert, ccCameraClearFrag);
            break;
            /// ETC1 ALPHA supports.
        case kShaderType_ETC1ASPositionTextureColor:
            p->initWithByteArrays(ccPositionTextureColor_vert, ccETC1ASPositionTextureColor_frag);
            break;
        case kShaderType_ETC1ASPositionTextureColor_noMVP:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccETC1ASPositionTextureColor_frag);
            break;
            /// ETC1 GRAY supports.
        case kShaderType_ETC1ASPositionTextureGray:
            p->initWithByteArrays(ccPositionTextureColor_vert, ccETC1ASPositionTextureGray_frag);
            break;
        case kShaderType_ETC1ASPositionTextureGray_noMVP:
            p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccETC1ASPositionTextureGray_frag);
            break;
        default:
            CCLOG("cocos2d: %s:%d, error shader type", __FUNCTION__, __LINE__);
            return;
    }

    p->link();
    p->updateUniforms();

    CHECK_GL_ERROR_DEBUG();
}

GLProgram* GLProgramCache::getGLProgram(const std::string &key)
{
    auto it = _programs.find(key);
    if( it != _programs.end() )
        return it->second;
    return nullptr;
}

void GLProgramCache::addGLProgram(GLProgram* program, const std::string &key)
{
    // release old one
    auto prev = getGLProgram(key);
    if( prev == program )
        return;

    _programs.erase(key);
    CC_SAFE_RELEASE_NULL(prev);

    if (program)
        program->retain();
    _programs[key] = program;
}

std::string GLProgramCache::getShaderMacrosForLight() const
{
    GLchar def[256];
    auto conf = Configuration::getInstance();

    snprintf(def, sizeof(def)-1, "\n#define MAX_DIRECTIONAL_LIGHT_NUM %d \n"
            "\n#define MAX_POINT_LIGHT_NUM %d \n"
            "\n#define MAX_SPOT_LIGHT_NUM %d \n",
             conf->getMaxSupportDirLightInShader(),
             conf->getMaxSupportPointLightInShader(),
             conf->getMaxSupportSpotLightInShader());
    return std::string(def);
}

NS_CC_END

/****************************************************************************
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

#include "renderer/CCMeshCommand.h"
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "base/CCLight.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "xxhash.h"

NS_CC_BEGIN

//render state
static bool   s_cullFaceEnabled = false;
static GLenum s_cullFace = 0;
static bool   s_depthTestEnabled = false;
static bool   s_depthWriteEnabled = false;

struct DirectionLightUniformNames
{
    std::string color;
    std::string dir;
};

struct PointLightUniformNames
{
    std::string color;
    std::string position;
    std::string rangeInverse;
};

struct SpotLightUniformNames
{
    std::string color;
    std::string position;
    std::string dir;
    std::string innerAngleCos;
    std::string outerAngleCos;
    std::string rangeInverse;
};

static std::vector<DirectionLightUniformNames> s_dirLightUniformNames;
static std::vector<PointLightUniformNames> s_pointLightUniformNames;
static std::vector<SpotLightUniformNames> s_spotLightUniformNames;

MeshCommand::MeshCommand()
: _textureID(0)
, _blendType(BlendFunc::DISABLE)
, _glProgramState(nullptr)
, _cullFaceEnabled(false)
, _cullFace(GL_BACK)
, _depthTestEnabled(false)
, _depthWriteEnabled(false)
, _displayColor(1.0f, 1.0f, 1.0f, 1.0f)
, _matrixPalette(nullptr)
, _matrixPaletteSize(0)
, _materialID(0)
, _vao(0)
, _lightMask(-1)
{
    _type = RenderCommand::Type::MESH_COMMAND;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // listen the event that renderer was recreated on Android/WP8
    _rendererRecreatedListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(MeshCommand::listenRendererRecreated, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_rendererRecreatedListener, -1);
#endif
}

void MeshCommand::init(float globalOrder,
                       GLuint textureID,
                       GLProgramState* glProgramState,
                       BlendFunc blendType,
                       GLuint vertexBuffer,
                       GLuint indexBuffer,
                       GLenum primitive,
                       GLenum indexFormat,
                       ssize_t indexCount,
                       const Mat4 &mv)
{
    CCASSERT(glProgramState, "GLProgramState cannot be nill");
    
    _globalOrder = globalOrder;
    _textureID = textureID;
    _blendType = blendType;
    _glProgramState = glProgramState;

    _vertexBuffer = vertexBuffer;
    _indexBuffer = indexBuffer;
    _primitive = primitive;
    _indexFormat = indexFormat;
    _indexCount = indexCount;
    _mv.set(mv);

    setLightUniformNames();
}

void MeshCommand::setCullFaceEnabled(bool enable)
{
    _cullFaceEnabled = enable;
}

void MeshCommand::setCullFace(GLenum cullFace)
{
    _cullFace = cullFace;
}

void MeshCommand::setDepthTestEnabled(bool enable)
{
    _depthTestEnabled = enable;
}

void MeshCommand::setDepthWriteEnabled(bool enable)
{
    _depthWriteEnabled = enable;
}

void MeshCommand::setDisplayColor(const Vec4& color)
{
    _displayColor = color;
}

MeshCommand::~MeshCommand()
{
    releaseVAO();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_rendererRecreatedListener);
#endif
}

void MeshCommand::applyRenderState()
{
    if (_cullFaceEnabled && !s_cullFaceEnabled)
    {
        glEnable(GL_CULL_FACE);
        if (s_cullFace != _cullFace)
        {
            glCullFace(_cullFace);
            s_cullFace = _cullFace;
        }
        s_cullFaceEnabled = true;
    }
    if (_depthTestEnabled && !s_depthTestEnabled)
    {
        glEnable(GL_DEPTH_TEST);
        s_depthTestEnabled = true;
    }
    if (_depthWriteEnabled && !s_depthWriteEnabled)
    {
        glDepthMask(GL_TRUE);
        s_depthWriteEnabled = true;
    }
}

void MeshCommand::restoreRenderState()
{
    if (s_cullFaceEnabled)
    {
        glDisable(GL_CULL_FACE);
        s_cullFaceEnabled = false;
    }
    if (s_depthTestEnabled)
    {
        glDisable(GL_DEPTH_TEST);
        s_depthTestEnabled = false;
    }
    if (s_depthWriteEnabled)
    {
        glDepthMask(GL_FALSE);
        s_depthWriteEnabled = false;
    }
    s_cullFace = 0;
}

void MeshCommand::genMaterialID(GLuint texID, void* glProgramState, GLuint vertexBuffer, GLuint indexBuffer, const BlendFunc& blend)
{
    int intArray[7] = {0};
    intArray[0] = (int)texID;
    *(int**)&intArray[1] = (int*) glProgramState;
    intArray[3] = (int) vertexBuffer;
    intArray[4] = (int) indexBuffer;
    intArray[5] = (int) blend.src;
    intArray[6] = (int) blend.dst;
    _materialID = XXH32((const void*)intArray, sizeof(intArray), 0);
}

void MeshCommand::MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform)
{
    glUniform4fv( uniform->location, (GLsizei)_matrixPaletteSize, (const float*)_matrixPalette );
}

void MeshCommand::preBatchDraw()
{
    // Set material
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    if (Configuration::getInstance()->supportsShareableVAO() && _vao == 0)
        buildVAO();
    if (_vao)
    {
        GL::bindVAO(_vao);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        _glProgramState->applyAttributes();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
}
void MeshCommand::batchDraw()
{
    // set render state
    applyRenderState();
    
    _glProgramState->setUniformVec4("u_color", _displayColor);
    
    if (_matrixPaletteSize && _matrixPalette)
    {
        _glProgramState->setUniformCallback("u_matrixPalette", CC_CALLBACK_2(MeshCommand::MatrixPalleteCallBack, this));
        
    }

    if (Director::getInstance()->getRunningScene()->getLights().size() > 0)
        setLightUniforms();
    
    _glProgramState->applyGLProgram(_mv);
    _glProgramState->applyUniforms();
    
    // Draw
    glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);
}
void MeshCommand::postBatchDraw()
{
    //restore render state
    restoreRenderState();
    if (_vao)
    {
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void MeshCommand::execute()
{
    // set render state
    applyRenderState();
    // Set material
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    _glProgramState->setUniformVec4("u_color", _displayColor);
    
    if (_matrixPaletteSize && _matrixPalette)
    {
        _glProgramState->setUniformCallback("u_matrixPalette", CC_CALLBACK_2(MeshCommand::MatrixPalleteCallBack, this));
        
    }

    if (Director::getInstance()->getRunningScene()->getLights().size() > 0)
        setLightUniforms();
    
    _glProgramState->apply(_mv);   
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    // Draw
    glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);
    
    //restore render state
    restoreRenderState();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshCommand::buildVAO()
{
    releaseVAO();
    glGenVertexArrays(1, &_vao);
    GL::bindVAO(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    auto flags = _glProgramState->getVertexAttribsFlags();
    for (int i = 0; flags > 0; i++) {
        int flag = 1 << i;
        if (flag & flags)
            glEnableVertexAttribArray(i);
        flags &= ~flag;
    }
    _glProgramState->applyAttributes(false);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    GL::bindVAO(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void MeshCommand::releaseVAO()
{
    if (_vao)
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
        GL::bindVAO(0);
    }
}


void MeshCommand::setLightUniforms()
{
    Director *director = Director::getInstance();
    auto scene = director->getRunningScene();
    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();
    auto &lights = scene->getLights();
    if (_glProgramState->getVertexAttribsFlags() & (1 << GLProgram::VERTEX_ATTRIB_NORMAL))
    {
        GLint enabledDirLightNum = 0;
        GLint enabledPointLightNum = 0;
        GLint enabledSpotLightNum = 0;
        Vec3 ambientColor;
        for (const auto& light : lights)
        {
            bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & _lightMask);
            if (useLight)
            {
                float intensity = light->getIntensity();
                switch (light->getLightType())
                {
                    case LightType::DIRECTIONAL:
                    {
                        CCASSERT(enabledDirLightNum < maxDirLight, "");
                        auto dirLight = static_cast<DirectionLight *>(light);
                        Vec3 dir = dirLight->getDirectionInWorld();
                        dir.normalize();
                        const Color3B &col = dirLight->getDisplayedColor();
                        _glProgramState->setUniformVec3(s_dirLightUniformNames[enabledDirLightNum].color, Vec3(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity));
                        _glProgramState->setUniformVec3(s_dirLightUniformNames[enabledDirLightNum].dir, dir);
                        ++enabledDirLightNum;
                    }
                        break;
                    case LightType::POINT:
                    {
                        CCASSERT(enabledPointLightNum < maxPointLight, "");
                        auto pointLight = static_cast<PointLight *>(light);
                        Mat4 mat= pointLight->getNodeToWorldTransform();
                        const Color3B &col = pointLight->getDisplayedColor();
                        _glProgramState->setUniformVec3(s_pointLightUniformNames[enabledPointLightNum].color, Vec3(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity));
                        _glProgramState->setUniformVec3(s_pointLightUniformNames[enabledPointLightNum].position, Vec3(mat.m[12], mat.m[13], mat.m[14]));
                        _glProgramState->setUniformFloat(s_pointLightUniformNames[enabledPointLightNum].rangeInverse, 1.0f / pointLight->getRange());
                        ++enabledPointLightNum;
                    }
                        break;
                    case LightType::SPOT:
                    {
                        CCASSERT(enabledSpotLightNum < maxSpotLight, "");
                        auto spotLight = static_cast<SpotLight *>(light);
                        Vec3 dir = spotLight->getDirectionInWorld();
                        dir.normalize();
                        Mat4 mat= light->getNodeToWorldTransform();
                        const Color3B &col = spotLight->getDisplayedColor();
                        _glProgramState->setUniformVec3(s_spotLightUniformNames[enabledSpotLightNum].color, Vec3(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity));
                        _glProgramState->setUniformVec3(s_spotLightUniformNames[enabledSpotLightNum].position, Vec3(mat.m[12], mat.m[13], mat.m[14]));
                        _glProgramState->setUniformVec3(s_spotLightUniformNames[enabledSpotLightNum].dir, dir);
                        _glProgramState->setUniformFloat(s_spotLightUniformNames[enabledSpotLightNum].innerAngleCos, spotLight->getCosInnerAngle());
                        _glProgramState->setUniformFloat(s_spotLightUniformNames[enabledSpotLightNum].outerAngleCos, spotLight->getCosOuterAngle());
                        _glProgramState->setUniformFloat(s_spotLightUniformNames[enabledSpotLightNum].rangeInverse, 1.0f / spotLight->getRange());
                        ++enabledSpotLightNum;
                    }
                        break;
                    case LightType::AMBIENT:
                    {
                        auto ambLight = static_cast<AmbientLight *>(light);
                        const Color3B &col = ambLight->getDisplayedColor();
                        ambientColor += Vec3(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                    }
                        break;
                    default:
                        break;
                }
            }
        }
        
        for (unsigned short i = enabledDirLightNum; i < maxDirLight; ++i)
        {
            _glProgramState->setUniformVec3(s_dirLightUniformNames[i].color, Vec3::ZERO);
            _glProgramState->setUniformVec3(s_dirLightUniformNames[i].dir, Vec3::ZERO);
        }
        
        for (unsigned short i = enabledPointLightNum; i < maxPointLight; ++i)
        {
            _glProgramState->setUniformVec3(s_pointLightUniformNames[i].color, Vec3::ZERO);
            _glProgramState->setUniformVec3(s_pointLightUniformNames[i].position, Vec3::ZERO);
            _glProgramState->setUniformFloat(s_pointLightUniformNames[i].rangeInverse, 0.0f);
        }
        
        for (unsigned short i = enabledSpotLightNum; i < maxSpotLight; ++i)
        {
            _glProgramState->setUniformVec3(s_spotLightUniformNames[i].color, Vec3::ZERO);
            _glProgramState->setUniformVec3(s_spotLightUniformNames[i].position, Vec3::ZERO);
            _glProgramState->setUniformVec3(s_spotLightUniformNames[i].dir, Vec3::ZERO);
            _glProgramState->setUniformFloat(s_spotLightUniformNames[i].innerAngleCos, 0.0f);
            _glProgramState->setUniformFloat(s_spotLightUniformNames[i].outerAngleCos, 0.0f);
            _glProgramState->setUniformFloat(s_spotLightUniformNames[i].rangeInverse, 0.0f);
        }
        
        _glProgramState->setUniformVec3("u_AmbientLightSourceColor", ambientColor);
    }
    else // normal does not exist
    {
        Vec3 ambient(0.0f, 0.0f, 0.0f);
        bool hasAmbient;
        for (const auto& light : lights)
        {
            if (light->getLightType() == LightType::AMBIENT)
            {
                bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & _lightMask);
                if (useLight)
                {
                    hasAmbient = true;
                    const Color3B &col = light->getDisplayedColor();
                    ambient.x += col.r * light->getIntensity();
                    ambient.y += col.g * light->getIntensity();
                    ambient.z += col.b * light->getIntensity();
                }
            }
        }
        if (hasAmbient)
        {
            ambient.x /= 255.f; ambient.y /= 255.f; ambient.z /= 255.f;
        }
        _glProgramState->setUniformVec4("u_color", Vec4(_displayColor.x * ambient.x, _displayColor.y * ambient.y, _displayColor.z * ambient.z, _displayColor.w));
    }
}

void MeshCommand::setLightUniformNames()
{
    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();
    if (s_dirLightUniformNames.size() != maxDirLight)
    {
        s_dirLightUniformNames.resize(maxDirLight);
        char str[64];
        for (unsigned int i = 0; i < maxDirLight; ++i)
        {
            sprintf(str, "u_DirLightSourceColor[%d]", i);
            s_dirLightUniformNames[i].color = str;
            sprintf(str, "u_DirLightSourceDirection[%d]", i);
            s_dirLightUniformNames[i].dir = str;
        }
    }

    if (s_pointLightUniformNames.size() != maxPointLight)
    {
        s_pointLightUniformNames.resize(maxPointLight);
        char str[64];
        for (unsigned int i = 0; i < maxPointLight; ++i)
        {
            sprintf(str, "u_PointLightSourceColor[%d]", i);
            s_pointLightUniformNames[i].color = str;
            sprintf(str, "u_PointLightSourcePosition[%d]", i);
            s_pointLightUniformNames[i].position = str;
            sprintf(str, "u_PointLightSourceRangeInverse[%d]", i);
            s_pointLightUniformNames[i].rangeInverse = str;
        }
    }

    if (s_spotLightUniformNames.size() != maxSpotLight)
    {
        s_spotLightUniformNames.resize(maxSpotLight);
        char str[64];
        for (unsigned int i = 0; i < maxSpotLight; ++i)
        {
            sprintf(str, "u_SpotLightSourceColor[%d]", i);
            s_spotLightUniformNames[i].color = str;
            sprintf(str, "u_SpotLightSourcePosition[%d]", i);
            s_spotLightUniformNames[i].position = str;
            sprintf(str, "u_SpotLightSourceDirection[%d]", i);
            s_spotLightUniformNames[i].dir = str;
            sprintf(str, "u_SpotLightSourceInnerAngleCos[%d]", i);
            s_spotLightUniformNames[i].innerAngleCos = str;
            sprintf(str, "u_SpotLightSourceOuterAngleCos[%d]", i);
            s_spotLightUniformNames[i].outerAngleCos = str;
            sprintf(str, "u_SpotLightSourceRangeInverse[%d]", i);
            s_spotLightUniformNames[i].rangeInverse = str;
        }
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
void MeshCommand::listenRendererRecreated(EventCustom* event)
{
    _vao = 0;
}

#endif

NS_CC_END

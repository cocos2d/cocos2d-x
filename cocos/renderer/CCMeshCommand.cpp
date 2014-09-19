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
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "3d/CCLight3D.h"
#include "xxhash.h"

NS_CC_BEGIN

//render state
static bool   s_cullFaceEnabled = false;
static GLenum s_cullFace = 0;
static bool   s_depthTestEnabled = false;
static bool   s_depthWriteEnabled = false;

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
, _useLights(false)
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

    _useLights = (0 < CC_MAX_DIRECTIONAL_LIGHT_NUM) || 
                        (0 < CC_MAX_POINT_LIGHT_NUM)               || 
                        (0 < CC_MAX_SPOT_LIGHT_NUM)                 ||
                        (0 < CC_MAX_AMBIENT_LIGHT_NUM);
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
    
    _glProgramState->applyGLProgram(_mv);
    _glProgramState->applyUniforms();

    if (_useLights)
    {
        applyLightUniforms();
    }
    
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
    
    _glProgramState->apply(_mv);
    
    if (_useLights)
    {
        applyLightUniforms();
    }
    
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


void MeshCommand::applyLightUniforms()
{
    Director *director = Director::getInstance();
    auto scene = director->getRunningScene();
    if (scene)
    {
        GLProgram *glProgram = _glProgramState->getGLProgram();
        GLint programID = glProgram->getProgram();
        auto &lights = scene->getLights();
        char str[64];
        GLint enabledDirLightNum = 0;
        GLint enabledPointLightNum = 0;
        GLint enabledSpotLightNum = 0;
        GLint enabledAmbientLightNum = 0;
        for (unsigned int i = 0; i < lights.size(); ++i)
        {
            BaseLight3D *light = lights[i];
            float intensity = light->isEnabled() == true? light->getIntensity() : 0.0f;
            switch (light->getLightType())
            {
            case LightType::DIRECTIONAL:
                {
                    CCASSERT(enabledDirLightNum < CC_MAX_DIRECTIONAL_LIGHT_NUM, "");
                    DirectionLight3D *dirLight = static_cast<DirectionLight3D *>(light);
                    Vec3 dir = dirLight->getDirectionInWorld();
                    dir.normalize();
                    const Color3B &col = dirLight->getDisplayedColor();
                    sprintf(str, "CC_DirLightSourceColor[%d]", enabledDirLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
                    sprintf(str, "CC_DirLightSourceDirection[%d]", enabledDirLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), dir.x, dir.y, dir.z);
                    sprintf(str, "CC_DirLightSourceIntensity[%d]", enabledDirLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), intensity);
                    ++enabledDirLightNum;
                }
                break;
            case LightType::POINT:
                {
                    CCASSERT(enabledPointLightNum < CC_MAX_POINT_LIGHT_NUM, "");
                    PointLight3D *pointLight = static_cast<PointLight3D *>(light);
                    Mat4 mat= pointLight->getNodeToWorldTransform();
                    const Color3B &col = pointLight->getDisplayedColor();
                    sprintf(str, "CC_PointLightSourceColor[%d]", enabledPointLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
                    sprintf(str, "CC_PointLightSourcePosition[%d]", enabledPointLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), mat.m[12], mat.m[13], mat.m[14]);
                    sprintf(str, "CC_PointLightSourceRangeInverse[%d]", enabledPointLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), 1.0f / pointLight->getRange());
                    sprintf(str, "CC_PointLightSourceIntensity[%d]", enabledPointLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), intensity);
                    ++enabledPointLightNum;
                }
                break;
            case LightType::SPOT:
                {
                    CCASSERT(enabledSpotLightNum < CC_MAX_SPOT_LIGHT_NUM, "");
                    SpotLight3D *spotLight = static_cast<SpotLight3D *>(light);
                    Vec3 dir = spotLight->getDirectionInWorld();
                    dir.normalize();
                    Mat4 mat= light->getNodeToWorldTransform();
                    const Color3B &col = spotLight->getDisplayedColor();
                    sprintf(str, "CC_SpotLightSourceColor[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
                    sprintf(str, "CC_SpotLightSourcePosition[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), mat.m[12], mat.m[13], mat.m[14]);
                    sprintf(str, "CC_SpotLightSourceDirection[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), dir.x, dir.y, dir.z);
                    sprintf(str, "CC_SpotLightSourceInnerAngleCos[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), spotLight->getCosInnerAngle());
                    sprintf(str, "CC_SpotLightSourceOuterAngleCos[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), spotLight->getCosOuterAngle());
                    sprintf(str, "CC_SpotLightSourceRangeInverse[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), 1.0f / spotLight->getRange());
                    sprintf(str, "CC_SpotLightSourceIntensity[%d]", enabledSpotLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), intensity);
                    ++enabledSpotLightNum;
                }
                break;
            case LightType::AMBIENT:
                {
                    CCASSERT(enabledAmbientLightNum < CC_MAX_AMBIENT_LIGHT_NUM, "");
                    AmbientLight3D *ambLight = static_cast<AmbientLight3D *>(light);
                    const Color3B &col = ambLight->getDisplayedColor();
                    sprintf(str, "CC_AmbientLightSourceColor[%d]", enabledAmbientLightNum);
                    glProgram->setUniformLocationWith3f(glGetUniformLocation(programID, str), col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
                    sprintf(str, "CC_AmbientLightSourceIntensity[%d]", enabledAmbientLightNum);
                    glProgram->setUniformLocationWith1f(glGetUniformLocation(programID, str), intensity);
                    ++enabledAmbientLightNum;
                }
                break;
            default:
                break;
            }
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

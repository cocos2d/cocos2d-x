/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
#include "2d/CCCameraBackgroundBrush.h"
#include "2d/CCCamera.h"
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCTextureCube.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"
#endif

NS_CC_BEGIN

CameraBackgroundBrush::CameraBackgroundBrush()
: _glProgramState(nullptr)
{
    
}

CameraBackgroundBrush::~CameraBackgroundBrush()
{
    CC_SAFE_RELEASE(_glProgramState);
}

CameraBackgroundBrush* CameraBackgroundBrush::createNoneBrush()
{
    auto ret = new (std::nothrow) CameraBackgroundBrush();
    ret->init();
    
    ret->autorelease();
    return ret;
}

CameraBackgroundColorBrush* CameraBackgroundBrush::createColorBrush(const Color4F& color, float depth)
{
    return CameraBackgroundColorBrush::create(color, depth);
}

CameraBackgroundDepthBrush* CameraBackgroundBrush::createDepthBrush(float depth)
{
    return CameraBackgroundDepthBrush::create(depth);
}

CameraBackgroundSkyBoxBrush* CameraBackgroundBrush::createSkyboxBrush(const std::string& positive_x, const std::string& negative_x, const std::string& positive_y, const std::string& negative_y, const std::string& positive_z, const std::string& negative_z)
{
    return CameraBackgroundSkyBoxBrush::create(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z);
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundDepthBrush::CameraBackgroundDepthBrush()
: _depth(0.f)
, _clearColor(GL_FALSE)
{
    
}
CameraBackgroundDepthBrush::~CameraBackgroundDepthBrush()
{
    
}

CameraBackgroundDepthBrush* CameraBackgroundDepthBrush::create(float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundDepthBrush();
    
    if (nullptr != ret && ret->init())
    {
        ret->_depth = depth;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool CameraBackgroundDepthBrush::init()
{
    auto shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_CAMERA_CLEAR);
    _glProgramState = GLProgramState::getOrCreateWithGLProgram(shader);
    _glProgramState->retain();
    
    _quad.bl.vertices = Vec3(-1,-1,0);
    _quad.br.vertices = Vec3(1,-1,0);
    _quad.tl.vertices = Vec3(-1,1,0);
    _quad.tr.vertices = Vec3(1,1,0);
    
    _quad.bl.colors = _quad.br.colors = _quad.tl.colors = _quad.tr.colors = Color4B(0,0,0,1);
    
    _quad.bl.texCoords = Tex2F(0,0);
    _quad.br.texCoords = Tex2F(1,0);
    _quad.tl.texCoords = Tex2F(0,1);
    _quad.tr.texCoords = Tex2F(1,1);
    return true;
}

void CameraBackgroundDepthBrush::drawBackground(Camera* /*camera*/)
{
    GLboolean oldDepthTest;
    GLint oldDepthFunc;
    GLboolean oldDepthMask;
    {
        glColorMask(_clearColor, _clearColor, _clearColor, _clearColor);
        glStencilMask(0);
        
        oldDepthTest = glIsEnabled(GL_DEPTH_TEST);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthMask);
        
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }
    
    //draw
    
    _glProgramState->setUniformFloat("depth", _depth);
    _glProgramState->apply(Mat4::IDENTITY);
    GLshort indices[6] = {0, 1, 2, 3, 2, 1};
    
    {
        GL::bindVAO(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        
        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), &_quad.tl.vertices);
        
        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), &_quad.tl.colors);
        
        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), &_quad.tl.texCoords);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    }
    
    
    {
        if(GL_FALSE == oldDepthTest)
        {
            glDisable(GL_DEPTH_TEST);
        }
        glDepthFunc(oldDepthFunc);
        
        if(GL_FALSE == oldDepthMask)
        {
            glDepthMask(GL_FALSE);
        }
        
        /* IMPORTANT: We only need to update the states that are not restored.
         Since we don't know what was the previous value of the mask, we update the RenderState
         after setting it.
         The other values don't need to be updated since they were restored to their original values
         */
        glStencilMask(0xFFFFF);
        //        RenderState::StateBlock::_defaultState->setStencilWrite(0xFFFFF);
        
        /* BUG: RenderState does not support glColorMask yet. */
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundColorBrush::CameraBackgroundColorBrush()
: _color(0.f, 0.f, 0.f, 0.f)
{
    
}

CameraBackgroundColorBrush::~CameraBackgroundColorBrush()
{
    
}

bool CameraBackgroundColorBrush::init()
{
    CameraBackgroundDepthBrush::init();
    this->_clearColor = GL_TRUE;
    return true;
}

void CameraBackgroundColorBrush::setColor(const Color4F& color)
{
    _quad.bl.colors = _quad.br.colors = _quad.tl.colors = _quad.tr.colors = Color4B(color);
}

CameraBackgroundColorBrush* CameraBackgroundColorBrush::create(const Color4F& color, float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundColorBrush();

    if (nullptr != ret && ret->init())
    {
        ret->setColor(color);
        ret->setDepth(depth);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////
CameraBackgroundSkyBoxBrush::CameraBackgroundSkyBoxBrush()
: _vao(0)
, _vertexBuffer(0)
, _indexBuffer(0)
, _texture(nullptr)
, _actived(true)
, _textureValid(true)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                initBuffer();
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

CameraBackgroundSkyBoxBrush::~CameraBackgroundSkyBoxBrush()
{
    CC_SAFE_RELEASE(_texture);
    
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);
    
    _vertexBuffer = 0;
    _indexBuffer = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
}

CameraBackgroundSkyBoxBrush* CameraBackgroundSkyBoxBrush::create(
    const std::string& positive_x,
    const std::string& negative_x,
    const std::string& positive_y,
    const std::string& negative_y,
    const std::string& positive_z,
    const std::string& negative_z
    )
{
    CameraBackgroundSkyBoxBrush* ret = nullptr;

    auto texture = TextureCube::create(positive_x,
                                       negative_x,
                                       positive_y,
                                       negative_y,
                                       positive_z,
                                       negative_z);

    if (texture != nullptr)
    {

        Texture2D::TexParams tRepeatParams;
        tRepeatParams.magFilter = GL_LINEAR;
        tRepeatParams.minFilter = GL_LINEAR;
        tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
        tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
        texture->setTexParameters(tRepeatParams);

        ret = new (std::nothrow) CameraBackgroundSkyBoxBrush;

        if (nullptr != ret && ret->init())
        {
            ret->setTexture(texture);
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(texture);
            CC_SAFE_DELETE(ret);
        }
    }

    return ret;
}

CameraBackgroundSkyBoxBrush* CameraBackgroundSkyBoxBrush::create()
{
    auto ret = new (std::nothrow) CameraBackgroundSkyBoxBrush();
    
    if (nullptr != ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

void CameraBackgroundSkyBoxBrush::drawBackground(Camera* camera)
{
    if (!_actived)
        return;

    Mat4 cameraModelMat = camera->getNodeToWorldTransform();
    
    Vec4 color(1.f, 1.f, 1.f, 1.f);
    _glProgramState->setUniformVec4("u_color", color);
    cameraModelMat.m[12] = cameraModelMat.m[13] = cameraModelMat.m[14] = 0;
    _glProgramState->setUniformMat4("u_cameraRot", cameraModelMat);
    
    _glProgramState->apply(Mat4::IDENTITY);
    
    glEnable(GL_DEPTH_TEST);
    RenderState::StateBlock::_defaultState->setDepthTest(true);
    
    glDepthMask(GL_TRUE);
    RenderState::StateBlock::_defaultState->setDepthWrite(true);
    
    glDepthFunc(GL_ALWAYS);
    RenderState::StateBlock::_defaultState->setDepthFunction(RenderState::DEPTH_ALWAYS);
    
    glEnable(GL_CULL_FACE);
    RenderState::StateBlock::_defaultState->setCullFace(true);
    
    glCullFace(GL_BACK);
    RenderState::StateBlock::_defaultState->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    
    glDisable(GL_BLEND);
    RenderState::StateBlock::_defaultState->setBlend(false);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    else
    {
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), nullptr);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
    
    glDrawElements(GL_TRIANGLES, (GLsizei)36, GL_UNSIGNED_BYTE, nullptr);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);
    
    CHECK_GL_ERROR_DEBUG();
}

bool CameraBackgroundSkyBoxBrush::init()
{
    auto shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKYBOX);
    _glProgramState = GLProgramState::create(shader);
    _glProgramState->setVertexAttribPointer(GLProgram::ATTRIBUTE_NAME_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), nullptr);
    _glProgramState->retain();
    
    initBuffer();
    
    return true;
}

void CameraBackgroundSkyBoxBrush::initBuffer()
{
    if (_vertexBuffer)
        glDeleteBuffers(1, &_vertexBuffer);
    if (_indexBuffer)
        glDeleteBuffers(1, &_indexBuffer);
    
    if (Configuration::getInstance()->supportsShareableVAO() && _vao)
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    // init vertex buffer object
    Vec3 vexBuf[] =
    {
        Vec3(1, -1, 1),  Vec3(1, 1, 1),  Vec3(-1, 1, 1),  Vec3(-1, -1, 1),
        Vec3(1, -1, -1), Vec3(1, 1, -1), Vec3(-1, 1, -1), Vec3(-1, -1, -1)
    };
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vexBuf), vexBuf, GL_STATIC_DRAW);
    
    // init index buffer object
    const unsigned char idxBuf[] = {  2, 1, 0, 3, 2, 0, // font
        1, 5, 4, 1, 4, 0, // right
        4, 5, 6, 4, 6, 7, // back
        7, 6, 2, 7, 2, 3, // left
        2, 6, 5, 2, 5, 1, // up
        3, 0, 4, 3, 4, 7  // down
    };
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idxBuf), idxBuf, GL_STATIC_DRAW);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        _glProgramState->applyAttributes(false);
        
        GL::bindVAO(0);
    }
}

void CameraBackgroundSkyBoxBrush::setTexture(TextureCube*  texture)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_texture);
    _texture = texture;
    _glProgramState->setUniformTexture("u_Env", _texture);
}

bool CameraBackgroundSkyBoxBrush::isActived() const
{
    return _actived;
}
void CameraBackgroundSkyBoxBrush::setActived(bool actived)
{
    _actived = actived;
}

void CameraBackgroundSkyBoxBrush::setTextureValid(bool valid)
{
    _textureValid = valid;
}

bool CameraBackgroundSkyBoxBrush::isValid()
{
    return _actived;
}

NS_CC_END

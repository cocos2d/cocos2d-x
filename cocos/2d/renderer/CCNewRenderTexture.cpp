/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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


#include "CCNewRenderTexture.h"
#include "CCCustomCommand.h"
#include "CCRenderer.h"
#include "CCGroupCommand.h"
#include "CCConfiguration.h"
#include "CCDirector.h"

NS_CC_BEGIN

NewRenderTexture* NewRenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    NewRenderTexture* pRet = new NewRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

NewRenderTexture* NewRenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    NewRenderTexture* pRet = new NewRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

NewRenderTexture* NewRenderTexture::create(int w, int h)
{
    NewRenderTexture* pRet = new NewRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, Texture2D::PixelFormat::RGB888 , 0))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void NewRenderTexture::draw()
{
    if (_autoDraw)
    {
        //Begin will create a render group using new render target
        begin();

        //clear screen
        CustomCommand* clearCmd = CustomCommand::getCommandPool().generateCommand();
        clearCmd->init(0, _vertexZ);
        clearCmd->func = CC_CALLBACK_0(NewRenderTexture::onClear, this);
        Director::getInstance()->getRenderer()->addCommand(clearCmd);

        //! make sure all children are drawn
        sortAllChildren();

        for(const auto &child: _children)
        {
            if (child != _sprite)
                child->visit();
        }

        //End will pop the current render group
        end();
    }
}

void NewRenderTexture::beginWithClear(float r, float g, float b, float a)
{
    beginWithClear(r, g, b, a, 0, 0, GL_COLOR_BUFFER_BIT);
}

void NewRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue)
{
    beginWithClear(r, g, b, a, depthValue, 0, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void NewRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue)
{
    beginWithClear(r, g, b, a, depthValue, stencilValue, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void NewRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags)
{
    setClearColor({r, g, b, a});

    setClearDepth(depthValue);

    setClearStencil(stencilValue);

    setClearFlags(flags);

    this->begin();

    //clear screen
    CustomCommand* clearCmd = CustomCommand::getCommandPool().generateCommand();
    clearCmd->init(0, _vertexZ);
    clearCmd->func = CC_CALLBACK_0(NewRenderTexture::onClear, this);
    Director::getInstance()->getRenderer()->addCommand(clearCmd);
}

void NewRenderTexture::begin()
{
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLGetMatrix(KM_GL_PROJECTION, &_projectionMatrix);

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLGetMatrix(KM_GL_MODELVIEW, &_transformMatrix);

    GroupCommand* groupCommand = GroupCommand::getCommandPool().generateCommand();
    groupCommand->init(0, _vertexZ);

    Renderer *renderer =  Director::getInstance()->getRenderer();
    renderer->addCommand(groupCommand);
    renderer->pushGroup(groupCommand->getRenderQueueID());

    CustomCommand* beginCmd = CustomCommand::getCommandPool().generateCommand();
    beginCmd->init(0, _vertexZ);
    beginCmd->func = CC_CALLBACK_0(NewRenderTexture::onBegin, this);

    Director::getInstance()->getRenderer()->addCommand(beginCmd);
}

void NewRenderTexture::end()
{
    CustomCommand* endCmd = CustomCommand::getCommandPool().generateCommand();
    endCmd->init(0, _vertexZ);
    endCmd->func = CC_CALLBACK_0(NewRenderTexture::onEnd, this);

    Renderer *renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(endCmd);
    renderer->popGroup();
}

void NewRenderTexture::onBegin()
{
    //
    kmGLGetMatrix(KM_GL_PROJECTION, &_oldProjMatrix);
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadMatrix(&_projectionMatrix);

    kmGLGetMatrix(KM_GL_MODELVIEW, &_oldTransMatrix);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadMatrix(&_transformMatrix);

    Director *director = Director::getInstance();
    director->setProjection(director->getProjection());

    const Size& texSize = _texture->getContentSizeInPixels();

    // Calculate the adjustment ratios based on the old and new projections
    Size size = director->getWinSizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;

    // Adjust the orthographic projection and viewport
    glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);


    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
            (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

    //TODO move this to configration, so we don't check it every time
    /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
     */
    if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
    {
        // -- bind a temporary texture so we can clear the render buffer without losing our texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
        CHECK_GL_ERROR_DEBUG();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
    }
}

void NewRenderTexture::onEnd()
{
    Director *director = Director::getInstance();

    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    // restore viewport
    director->setViewport();

    //
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadMatrix(&_oldProjMatrix);

    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadMatrix(&_oldTransMatrix);
}

void NewRenderTexture::onClear()
{
    // save clear color
    GLfloat oldClearColor[4] = {0.0f};
    GLfloat oldDepthClearValue = 0.0f;
    GLint oldStencilClearValue = 0;

    // backup and set
    if (_clearFlags & GL_COLOR_BUFFER_BIT)
    {
        glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClearColor);
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    }

    if (_clearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glClearDepth(_clearDepth);
    }

    if (_clearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &oldStencilClearValue);
        glClearStencil(_clearStencil);
    }

    // clear
    glClear(_clearFlags);

    // restore
    if (_clearFlags & GL_COLOR_BUFFER_BIT)
    {
        glClearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);
    }
    if (_clearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glClearDepth(oldDepthClearValue);
    }
    if (_clearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glClearStencil(oldStencilClearValue);
    }
}

void NewRenderTexture::clearDepth(float depthValue)
{
    setClearDepth(depthValue);

    this->begin();

    CustomCommand* cmd = CustomCommand::getCommandPool().generateCommand();
    cmd->init(0, _vertexZ);
    cmd->func = CC_CALLBACK_0(NewRenderTexture::onClearDepth, this);

    Director::getInstance()->getRenderer()->addCommand(cmd);

    this->end();
}

void NewRenderTexture::onClearDepth()
{
    //! save old depth value
    GLfloat depthClearValue;
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClearValue);

    glClearDepth(_clearDepth);
    glClear(GL_DEPTH_BUFFER_BIT);

    // restore clear color
    glClearDepth(depthClearValue);
}

NewRenderTexture::NewRenderTexture()
:RenderTexture()
{

}

NewRenderTexture::~NewRenderTexture()
{

}

NS_CC_END
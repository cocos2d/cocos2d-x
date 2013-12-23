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
    return nullptr;
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
    return nullptr;
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
    return nullptr;
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

void NewRenderTexture::_beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags)
{
    setClearColor(Color4F(r, g, b, a));

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

NewRenderTexture::NewRenderTexture()
:RenderTexture()
{

}

NewRenderTexture::~NewRenderTexture()
{

}

NS_CC_END
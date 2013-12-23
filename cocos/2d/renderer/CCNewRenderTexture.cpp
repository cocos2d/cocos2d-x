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

NewRenderTexture::NewRenderTexture()
:RenderTexture()
{

}

NewRenderTexture::~NewRenderTexture()
{

}

NS_CC_END
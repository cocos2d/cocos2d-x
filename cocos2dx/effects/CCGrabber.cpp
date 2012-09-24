/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      On-Core
 
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
#include "CCGrabber.h"
#include "ccMacros.h"
#include "textures/CCTexture2D.h"
#include "platform/platform.h"

NS_CC_BEGIN

CCGrabber::CCGrabber(void)
    : m_fbo(0)
    , m_oldFBO(0)
{
    memset(m_oldClearColor, 0, sizeof(m_oldClearColor));

    // generate FBO
    glGenFramebuffers(1, &m_fbo);
}

void CCGrabber::grab(CCTexture2D *pTexture)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_oldFBO);

    // bind
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // associate texture with FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pTexture->getName(), 0);

    // check if it worked (probably worth doing :) )
    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        CCAssert(0, "Frame Grabber: could not attach texture to framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_oldFBO);
}

void CCGrabber::beforeRender(CCTexture2D *pTexture)
{
    CC_UNUSED_PARAM(pTexture);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    
    // save clear color
    glGetFloatv(GL_COLOR_CLEAR_VALUE, m_oldClearColor);
    // BUG XXX: doesn't work with RGB565.

    glClearColor(0, 0, 0, 0);

    // BUG #631: To fix #631, uncomment the lines with #631
    // Warning: But it CCGrabber won't work with 2 effects at the same time
//  glClearColor(0.0f,0.0f,0.0f,1.0f);    // #631

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//  glColorMask(true, true, true, false);    // #631
}

void CCGrabber::afterRender(cocos2d::CCTexture2D *pTexture)
{
    CC_UNUSED_PARAM(pTexture);

    glBindFramebuffer(GL_FRAMEBUFFER, m_oldFBO);
//  glColorMask(true, true, true, true);    // #631
    
    // Restore clear color
    glClearColor(m_oldClearColor[0], m_oldClearColor[1], m_oldClearColor[2], m_oldClearColor[3]);
}

CCGrabber::~CCGrabber()
{
    CCLOGINFO("cocos2d: deallocing %p", this);
    glDeleteFramebuffers(1, &m_fbo);
}

NS_CC_END

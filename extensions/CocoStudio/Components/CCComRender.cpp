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

#include "CCComRender.h"

NS_CC_EXT_BEGIN

CCComRender::CCComRender(void)
: m_pRender(NULL)
{
  
}


CCComRender::CCComRender(cocos2d::CCNode *node, const char *comName)
{
    m_pRender = node;
    m_strName.assign(comName);
}

CCComRender::~CCComRender(void)
{
    m_pRender = NULL;
}

void CCComRender::onEnter()
{
    if (m_pOwner != NULL)
    {
        m_pOwner->addChild(m_pRender);
    }
}

void CCComRender::onExit()
{
    m_pRender = NULL;
}

cocos2d::CCNode* CCComRender::getNode()
{
    return m_pRender;
}

void CCComRender::setNode(cocos2d::CCNode *pNode)
{
	m_pRender = pNode;
}

CCComRender* CCComRender::create(cocos2d::CCNode *pNode, const char *comName)
{
    CCComRender * pRet = new CCComRender(pNode, comName);
    if (pRet != NULL && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

NS_CC_EXT_END

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

#include "support/component/CCComponent.h"
#include "CCDirector.h"


NS_CC_BEGIN

CCComponent::CCComponent(void)
: m_pOwner(NULL)
, m_bEnabled(true)
{
}

CCComponent::~CCComponent(void)
{
}

bool CCComponent::init()
{
    return true;
}

void CCComponent::onEnter()
{
}

void CCComponent::onExit()
{
}

void CCComponent::update(float delta)
{
}

void CCComponent::serialize(void *ar)
{
}

CCComponent* CCComponent::create(void)
{
    CCComponent * pRet = new CCComponent();
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

const char* CCComponent::getName() const
{
    return m_strName.c_str();
}

void  CCComponent::setName(const char *pName)
{
	m_strName.assign(pName);
}

CCNode* CCComponent::getOwner() const
{
    return m_pOwner;
}

void CCComponent::setOwner(CCNode *pOwner)
{
    m_pOwner = pOwner;
}

bool CCComponent::isEnabled() const
{
    return m_bEnabled;
}

void CCComponent::setEnabled(bool b)
{
    m_bEnabled = b;
}

CCNode* CCComponent::getNode()
{
	return NULL;
}

void CCComponent::setNode(CCNode *pNode)
{
	CC_UNUSED_PARAM(pNode);
}

NS_CC_END

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

#include "GUINodeRGBA.h"

NS_CC_EXT_BEGIN

GUINodeRGBA * GUINodeRGBA::create(void)
{
	GUINodeRGBA * pRet = new GUINodeRGBA();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
    
bool GUINodeRGBA::init()
{
    if (CCNodeRGBA::init())
    {
        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);
        
        return true;
    }
    return false;
}

void GUINodeRGBA::addChild(cocos2d::CCNode *child)
{
    CCNode::addChild(child);
    CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(child);
    if (item)
    {
        item->setColor(getColor());
        item->setOpacity(getOpacity());
    }
}

void GUINodeRGBA::setColor(const cocos2d::ccColor3B &color3)
{
    CCNodeRGBA::setColor(color3);
    CCObject* pObj;
    CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(pObj);
        if (item)
        {
            item->setColor(color3);
        }
    }
}

void GUINodeRGBA::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);
    CCObject* pObj;
    CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(pObj);
        if (item)
        {
            item->setOpacity(opacity);
        }
    }
}

NS_CC_EXT_END
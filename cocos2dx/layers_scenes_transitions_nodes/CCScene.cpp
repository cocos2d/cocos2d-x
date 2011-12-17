/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCScene.h"
#include "CCPointExtension.h"
#include "CCDirector.h"

#if LUA_ENGINE
#include "CCLuaEngine.h"
#endif

namespace cocos2d
{

CCScene::CCScene()
#if LUA_ENGINE
: m_eventsFunctionRefID(0)
#endif
{
	m_bIsRelativeAnchorPoint = false;
	setAnchorPoint(ccp(0.5f, 0.5f));
}

CCScene::~CCScene()
{
#if LUA_ENGINE
    unregisterScriptEventsHandler();
#endif
}

bool CCScene::init()
{
	bool bRet = false;
 	do 
 	{
 		CCDirector * pDirector;
 		CC_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
 		this->setContentSize(pDirector->getWinSize());
 		// success
 		bRet = true;
 	} while (0);
 	return bRet;
}

CCScene *CCScene::node()
{
	CCScene *pRet = new CCScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
    else
    {
	    CC_SAFE_DELETE(pRet)
	    return NULL;
    }
}


#if LUA_ENGINE

void CCScene::onEnter()
{
    if (m_eventsFunctionRefID)
    {
        CCLuaEngine::sharedEngine()->executeFunctionWithBooleanData(m_eventsFunctionRefID, true);
    }
    CCNode::onEnter();
}

void CCScene::onExit()
{
    if (m_eventsFunctionRefID)
    {
        CCLuaEngine::sharedEngine()->executeFunctionWithBooleanData(m_eventsFunctionRefID, false);
    }
    CCNode::onExit();
}

void CCScene::registerScriptEventsHandler(int functionRefID)
{
    unregisterScriptEventsHandler();
    m_eventsFunctionRefID = functionRefID;
    LUALOG("[LUA] ADD Scene events handler: %d", functionRefID);
}

void CCScene::unregisterScriptEventsHandler(void)
{
    if (m_eventsFunctionRefID)
    {
        CCLuaEngine::sharedEngine()->removeLuaFunctionRef(m_eventsFunctionRefID);
        LUALOG("[LUA] DEL Scene events handler: %d", m_eventsFunctionRefID);
    }
    m_eventsFunctionRefID = 0;
}

#endif // LUA_ENGINE
    
}//namespace   cocos2d 

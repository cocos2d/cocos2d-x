/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "support/CGPointExtension.h"
#include "CCDirector.h"

namespace   cocos2d {

CCScene::CCScene()
{
	m_bIsRelativeAnchorPoint = false;
	m_tAnchorPoint = ccp(0.5f, 0.5f);
}

CCScene::~CCScene()
{
}

bool CCScene::init()
{
	bool bRet = false;
 	do 
 	{
 		CCDirector * pDirector;
 		CCX_BREAK_IF( ! (pDirector = CCDirector::getSharedDirector()) );
 		this->setContentSize(pDirector->getWinSize());
 		// success
 		bRet = true;
 	} while (0);
 	return bRet;
}

CCScene *CCScene::node()
{
	CCScene *pRet = new CCScene();
	if (pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	return NULL;
}
}//namespace   cocos2d 

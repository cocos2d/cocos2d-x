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

#ifndef __TestCpp__UISceneManager__
#define __TestCpp__UISceneManager__

#include "cocos2d.h"

USING_NS_CC;

class UISceneManager : public CCObject
{
public:
    UISceneManager();
    ~UISceneManager();
    /** Returns the singleton of the ui scene manager. */
    static UISceneManager * sharedUISceneManager();
	static void purgeUISceneManager();
    
    /** Returns the next ui scene. */
    cocos2d::CCScene *nextUIScene();
    
    /** Returns the previous ui scene. */
    cocos2d::CCScene *previousUIScene();
    
    /** Returns the current control scene. */
    cocos2d::CCScene *currentUIScene();
    
    /** UI scene id. */
    CC_SYNTHESIZE(int, m_nCurrentUISceneId, CurrentUISceneId)
};

#endif /* defined(__TestCpp__UISceneManager__) */

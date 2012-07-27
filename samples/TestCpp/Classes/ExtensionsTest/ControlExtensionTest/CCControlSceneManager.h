/*
 * CCControlSceneManager.h
 *
 * Copyright (c) 2011 Yannick Loriot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef __CCCONTROLSCENEMANAGER_H__
#define __CCCONTROLSCENEMANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class CCControlSceneManager : public cocos2d::CCObject
{
public:
    CCControlSceneManager();
    ~CCControlSceneManager();
    /** Returns the singleton of the control scene manager. */
    static CCControlSceneManager * sharedControlSceneManager();

    /** Returns the next control scene. */
    cocos2d::CCScene *nextControlScene();

    /** Returns the previous control scene. */
    cocos2d::CCScene *previousControlScene();

    /** Returns the current control scene. */
    cocos2d::CCScene *currentControlScene();

    /** Control scene id. */
    CC_SYNTHESIZE(int, m_nCurrentControlSceneId, CurrentControlSceneId)
};

#endif /* __CCCONTROLSCENEMANAGER_H__ */

/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#ifndef __TEST_FACEBOOK_USER_SCENE_H__
#define __TEST_FACEBOOK_USER_SCENE_H__

#include "cocos2d.h"
#include "FacebookAgent.h"

class TestFacebookUser : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onExit();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuBackCallback(Ref* sender);
    void eventMenuCallback(Ref* sender);

    // implement the "static node()" method manually
    CREATE_FUNC(TestFacebookUser);
private:
    bool isLogin;
    cocos2d::Label* callbackInfo;
};

#endif // __TEST_FACEBOOK_USER_SCENE_H__

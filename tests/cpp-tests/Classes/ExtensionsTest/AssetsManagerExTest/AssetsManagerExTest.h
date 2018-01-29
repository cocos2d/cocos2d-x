/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef __AssetsManagerEx_Test_H__
#define __AssetsManagerEx_Test_H__

#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"

DEFINE_TEST_SUITE(AssetsManagerExTests);

class AssetsManagerExLoaderScene : public TestCase
{
public:
    static AssetsManagerExLoaderScene* create(int testIndex);

    AssetsManagerExLoaderScene(int testIndex);
    
    void startDownloadCallback(cocos2d::Ref* sender);

    virtual std::string title() const override;

    virtual bool init() override;
    virtual void onExit() override;
    
private:
    int _testIndex;
    cocos2d::Layer* _loadLayer;
    cocos2d::Menu* _downloadMenu;

    cocos2d::extension::AssetsManagerEx* _am;
    cocos2d::Label* _progress;
    cocos2d::extension::EventListenerAssetsManagerEx* _amListener;

    void onLoadEnd();
};

#endif /* defined(__AssetsManagerEx_Test_H__) */

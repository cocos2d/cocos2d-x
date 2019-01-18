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

#ifndef __tests__VideoPlayerTest__
#define __tests__VideoPlayerTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(VideoPlayerTests);

class VideoPlayerTest : public UIScene
{
public:
    CREATE_FUNC(VideoPlayerTest);

    virtual bool init() override;

    void menuCloseCallback(cocos2d::Ref* sender);

    void menuRatioCallback(cocos2d::Ref* sender);
    void menuResourceVideoCallback(cocos2d::Ref* sender);
    void menuOnlineVideoCallback(cocos2d::Ref* sender);

    void menuFullScreenCallback(cocos2d::Ref* sender);
    void menuPauseCallback(cocos2d::Ref* sender);
    void menuResumeCallback(cocos2d::Ref* sender);
    void menuStopCallback(cocos2d::Ref* sender);
    void menuHintCallback(cocos2d::Ref* sender);
    void menuLoopCallback(cocos2d::Ref* sender);
    
    void sliderCallback(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType);

    void videoEventCallback(cocos2d::Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);

private:
    void createVideo();
    void createSlider();

    cocos2d::MenuItemFont* _hintItem;
    cocos2d::experimental::ui::VideoPlayer* _videoPlayer;
    cocos2d::Label* _videoStateLabel;
    cocos2d::Label* _loopStatusLabel;
    cocos2d::Rect _visibleRect;

    cocos2d::Layer* _rootLayer;

};


class SimpleVideoPlayerTest : public UIScene
{
public:
    CREATE_FUNC(SimpleVideoPlayerTest);
    
    SimpleVideoPlayerTest();
    
    virtual bool init() override;
    
    void menuCloseCallback(cocos2d::Ref* sender);
    void switchStyleCallback(cocos2d::Ref* sender);
    void switchUserInputCallback(cocos2d::Ref* sender);
    
private:
    void createVideo();
    
    cocos2d::Rect _visibleRect;
    cocos2d::experimental::ui::VideoPlayer* _videoPlayer;
    
    cocos2d::MenuItemFont*   _switchUserInputEnabled;
    cocos2d::MenuItemFont*   _switchStyle;
    
    
    bool _userInputEnabled;
    cocos2d::experimental::ui::VideoPlayer::StyleType _style;
    
    void updateButtonsTexts();
};


#endif // __tests__VideoPlayerTest__

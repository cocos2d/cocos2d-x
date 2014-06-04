/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "UIVideoPlayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <unordered_map>
#include <stdlib.h>
#include <jni.h>
#include <string>
#include "jni/JniHelper.h"
#include "base/CCDirector.h"
#include "CCGLView.h"
#include "base/CCEventListenerKeyboard.h"

//-----------------------------------------------------------------------------------------------------------
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxVideoHelper"

void executeVideoCallback(int index,int event);

USING_NS_CC;

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxVideoHelper_nativeExecuteVideoCallback(JNIEnv * env, jobject obj, jint index,jint event) {
        executeVideoCallback(index,event);
    }
}

int createVideoWidgetJNI()
{
    JniMethodInfo t;
    int ret = -1;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createVideoWidget", "()I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);

        t.env->DeleteLocalRef(t.classID);
    }

    return ret;
}

void callVideoNonParameterFun(int index,const char* funName)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, funName, "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);

        t.env->DeleteLocalRef(t.classID);
    }
}

void removeVideoWidgetJNI(int index)
{
    callVideoNonParameterFun(index,"removeVideoWidget");
}

void setVideoRectJNI(int index,int left,int top,int width,int height)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setVideoRect", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, left, top, width, height);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setVideoURLJNI(int index,int videoSource,const std::string& videoUrl)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setVideoUrl", "(IILjava/lang/String;)V")) {
        jstring stringArg = t.env->NewStringUTF(videoUrl.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, videoSource,stringArg);

        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void startVideoJNI(int index)
{
    callVideoNonParameterFun(index,"startVideo");
}

void pauseVideoJNI(int index)
{
    callVideoNonParameterFun(index,"pauseVideo");
}

void resumeVideoJNI(int index)
{
    callVideoNonParameterFun(index,"resumeVideo");
}

void stopVideoJNI(int index)
{
    callVideoNonParameterFun(index,"stopVideo");
}

void seekVideoToJNI(int index,int msec)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "seekVideoTo", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, msec);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setVideoVisible(int index,bool visible)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setVideoVisible", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, visible);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setVideoKeepRatioEnabled(int index,bool enabled)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setVideoKeepRatioEnabled", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, enabled);

        t.env->DeleteLocalRef(t.classID);
    }
}
//-----------------------------------------------------------------------------------------------------------

using namespace cocos2d::experimental::ui;

static std::unordered_map<int, VideoPlayer*> s_allVideoPlayers;

VideoPlayer::VideoPlayer()
: _videoPlayerIndex(-1)
, _eventCallback(nullptr)
, _fullScreenEnabled(false)
, _fullScreenDirty(false)
, _keepAspectRatioEnabled(false)
{
    _videoPlayerIndex = createVideoWidgetJNI();
    s_allVideoPlayers[_videoPlayerIndex] = this;

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, cocos2d::Event* event){
        if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE && _fullScreenEnabled)
        {
            this->setFullScreenEnabled(false);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

VideoPlayer::~VideoPlayer()
{
    s_allVideoPlayers.erase(_videoPlayerIndex);
    removeVideoWidgetJNI(_videoPlayerIndex);
}

void VideoPlayer::setFileName(const std::string& fileName)
{
    _videoURL = fileName;
    _videoSource = VideoPlayer::Source::FILENAME;
    setVideoURLJNI(_videoPlayerIndex, (int)Source::FILENAME,_videoURL);
}

void VideoPlayer::setURL(const std::string& videoUrl)
{
    _videoURL = videoUrl;
    _videoSource = VideoPlayer::Source::URL;
    setVideoURLJNI(_videoPlayerIndex,(int)Source::URL,_videoURL);
}

void VideoPlayer::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    cocos2d::ui::Widget::draw(renderer,transform,flags);

    if ((flags&FLAGS_TRANSFORM_DIRTY) || _fullScreenDirty)
    {
        _fullScreenDirty = false;
        auto directorInstance = Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();

        if (_fullScreenEnabled)
        {
            setVideoRectJNI(_videoPlayerIndex,0,0,frameSize.width,frameSize.height);
        }
        else
        {
            auto winSize = directorInstance->getWinSize();

            auto leftBottom = convertToWorldSpace(Point::ZERO);
            auto rightTop = convertToWorldSpace(Point(_contentSize.width,_contentSize.height));

            auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
            auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();

            setVideoRectJNI(_videoPlayerIndex,uiLeft,uiTop,
                (rightTop.x - leftBottom.x) * glView->getScaleX(),
                (rightTop.y - leftBottom.y) * glView->getScaleY());
        }
    }

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _customDebugDrawCommand.init(_globalZOrder);
    _customDebugDrawCommand.func = CC_CALLBACK_0(VideoPlayer::drawDebugData, this);
    renderer->addCommand(&_customDebugDrawCommand);
#endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    if (_fullScreenEnabled != enabled)
    {
        _fullScreenEnabled = enabled;
        _fullScreenDirty = true;
    }
}

bool VideoPlayer::isFullScreenEnabled()const
{
    return _fullScreenEnabled;
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable)
    {
        _keepAspectRatioEnabled = enable;
        setVideoKeepRatioEnabled(_videoPlayerIndex,enable);
    }
}

#if CC_VIDEOPLAYER_DEBUG_DRAW
void VideoPlayer::drawDebugData()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");

    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    auto size = getContentSize();

    Point vertices[4]=
    {
        Point::ZERO,
        Point(size.width, 0),
        Point(size.width, size.height),
        Point(0, size.height)
    };

    DrawPrimitives::drawPoly(vertices, 4, true);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
#endif

void VideoPlayer::play()
{
    if (! _videoURL.empty())
    {
        startVideoJNI(_videoPlayerIndex);
    }
}

void VideoPlayer::pause()
{
    if (! _videoURL.empty())
    {
        pauseVideoJNI(_videoPlayerIndex);
    }
}

void VideoPlayer::resume()
{
    if (! _videoURL.empty())
    {
        resumeVideoJNI(_videoPlayerIndex);
    }
}

void VideoPlayer::stop()
{
    if (! _videoURL.empty())
    {
        stopVideoJNI(_videoPlayerIndex);
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (! _videoURL.empty())
    {
        seekVideoToJNI(_videoPlayerIndex,int(sec * 1000));
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}

void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);

    if (! _videoURL.empty())
    {
        setVideoVisible(_videoPlayerIndex,visible);
    } 
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback)
{
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(VideoPlayer::EventType event)
{
    if (event == VideoPlayer::EventType::PLAYING) {
        _isPlaying = true;
    } else {
        _isPlaying = false;
    }

    if (_eventCallback)
    {
        _eventCallback(this,event);
    }
}

cocos2d::ui::Widget* VideoPlayer::createCloneInstance()
{
    return VideoPlayer::create();
}

void VideoPlayer::copySpecialProperties(Widget *widget)
{
    VideoPlayer* videoPlayer = dynamic_cast<VideoPlayer*>(widget);
    if (videoPlayer)
    {
        _isPlaying = videoPlayer->_isPlaying;
        _fullScreenEnabled = videoPlayer->_fullScreenEnabled;
        _fullScreenDirty = videoPlayer->_fullScreenDirty;
        _videoURL = videoPlayer->_videoURL;
        _keepAspectRatioEnabled = videoPlayer->_keepAspectRatioEnabled;
        _videoSource = videoPlayer->_videoSource;
        _videoPlayerIndex = videoPlayer->_videoPlayerIndex;
        _eventCallback = videoPlayer->_eventCallback;
        _videoView = videoPlayer->_videoView;
    }
}

void executeVideoCallback(int index,int event)
{
    auto it = s_allVideoPlayers.find(index);
    if (it != s_allVideoPlayers.end())
    {
        s_allVideoPlayers[index]->onPlayEvent((VideoPlayer::EventType)event);
    }
}

#endif

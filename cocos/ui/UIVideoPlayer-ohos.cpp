/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#include "ui/UIVideoPlayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)

#include <unordered_map>
#include <stdlib.h>
#include <string>
#include "base/CCDirector.h"
#include "base/CCEventListenerKeyboard.h"
#include "platform/ohos/CCFileUtils-ohos.h"
#include "ui/UIVideoPlayer-ohos.h"
#include "platform/ohos/napi/helper/NapiHelper.h"

#include "ui/UIHelper.h"

USING_NS_CC;
#define QUIT_FULLSCREEN 1000

//-----------------------------------------------------------------------------------------------------------

using namespace cocos2d::ui;
static int32_t kVideoPlayerTag = 0;
static std::unordered_map<int, VideoPlayer *> s_allVideoPlayers;
static const std::string SANDBOX_PREFIX = "file://";

VideoPlayer::VideoPlayer()
    : _fullScreenDirty(false),
      _fullScreenEnabled(false),
      _keepAspectRatioEnabled(false),
      _videoPlayerIndex(-1),
      _eventCallback(nullptr),
      _isPlaying(false),
      _isLooping(false),
      _isUserInputEnabled(true),
      _styleType(StyleType::DEFAULT) {
    // Add an index.
    _videoPlayerIndex = kVideoPlayerTag++;
    s_allVideoPlayers[_videoPlayerIndex] = this;

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
    JSFunction::getFunction("VideoPlayer.createVideoPlayer").invoke<void>(_videoPlayerIndex);
}

VideoPlayer::~VideoPlayer() {
    if (_videoPlayerIndex != -1 && kVideoPlayerTag != -1) {
        JSFunction::getFunction("VideoPlayer.removeVideoPlayer").invoke<void>(_videoPlayerIndex);
        auto iter = s_allVideoPlayers.find(_videoPlayerIndex);
        if (iter != s_allVideoPlayers.end()) {
            s_allVideoPlayers.erase(iter);
        }
    }
}

void VideoPlayer::setFileName(const std::string &fileName) {
    _videoURL = FileUtils::getInstance()->fullPathForFilename(fileName);
    if (_videoURL[0] == '/') {
        _videoSource = VideoPlayer::Source::URL;
        JSFunction::getFunction("VideoPlayer.setURL").invoke<void>(_videoPlayerIndex, SANDBOX_PREFIX + _videoURL, (int)_videoSource);
    } else {
        _videoSource = VideoPlayer::Source::FILENAME;
        JSFunction::getFunction("VideoPlayer.setURL").invoke<void>(_videoPlayerIndex, _videoURL, (int)_videoSource);
    }
}

void VideoPlayer::setURL(const std::string &videoUrl) {
    _videoURL = videoUrl;
    _videoSource = VideoPlayer::Source::URL;
    JSFunction::getFunction("VideoPlayer.setURL").invoke<void>(_videoPlayerIndex, _videoURL, (int)_videoSource);
}

void VideoPlayer::setLooping(bool looping) {
    _isLooping = looping;
    JSFunction::getFunction("VideoPlayer.setLooping").invoke<void>(_videoPlayerIndex, _isLooping);
}

void VideoPlayer::setUserInputEnabled(bool enableInput) {
    _isUserInputEnabled = enableInput;
    // todo:鸿蒙暂时不支持
}

void VideoPlayer::setStyle(StyleType style) {
    _styleType = style;
}

void VideoPlayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    cocos2d::ui::Widget::draw(renderer, transform, flags);

    if (flags & FLAGS_TRANSFORM_DIRTY) {
        auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(this);
        JSFunction::getFunction("VideoPlayer.setVideoPlayerRect").invoke<void>(_videoPlayerIndex, (int)uiRect.origin.x, (int)uiRect.origin.y,
            (int)uiRect.size.width, (int)uiRect.size.height);
    }

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode->clear();
    auto size = getContentSize();
    Point vertices[4] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};
    _debugdrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled) {
    if (_fullScreenEnabled != enabled) {
        _fullScreenEnabled = enabled;
        JSFunction::getFunction("VideoPlayer.requestFullscreen").invoke<void>(_videoPlayerIndex, enabled);
    }
}

bool VideoPlayer::isFullScreenEnabled() const {
    return _fullScreenEnabled;
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable) {
    if (_keepAspectRatioEnabled != enable) {
        _keepAspectRatioEnabled = enable;
        JSFunction::getFunction("VideoPlayer.setKeepAspectRatioEnabled").invoke<void>(_videoPlayerIndex, enable);
    }
}

#if CC_VIDEOPLAYER_DEBUG_DRAW
void VideoPlayer::drawDebugData() {
    Director *director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    auto size = getContentSize();

    Point vertices[4] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};

    DrawPrimitives::drawPoly(vertices, 4, true);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
#endif

void VideoPlayer::play() {
    if (!_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.play").invoke<void>(_videoPlayerIndex);
    }
}

void VideoPlayer::pause() {
    if (!_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.pause").invoke<void>(_videoPlayerIndex);
    }
}

void VideoPlayer::resume() {
    if (!_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.play").invoke<void>(_videoPlayerIndex);
    }
}

void VideoPlayer::stop() {
    if (!_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.stop").invoke<void>(_videoPlayerIndex);
    }
}

void VideoPlayer::seekTo(float sec) {
    if (!_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.seekTo").invoke<void>(_videoPlayerIndex, (int)sec);
    }
}

bool VideoPlayer::isPlaying() const {
    return _isPlaying;
}

bool VideoPlayer::isLooping() const {
    return _isLooping;
}

bool VideoPlayer::isUserInputEnabled() const {
    return _isUserInputEnabled;
}

void VideoPlayer::setVisible(bool visible) {
    cocos2d::ui::Widget::setVisible(visible);

    if (!visible || isRunning()) {
        JSFunction::getFunction("VideoPlayer.setVisible").invoke<void>(_videoPlayerIndex, visible);
    }
}

void VideoPlayer::onEnter() {
    Widget::onEnter();
    if (isVisible() && !_videoURL.empty()) {
        JSFunction::getFunction("VideoPlayer.setVisible").invoke<void>(_videoPlayerIndex, true);
    }
}

void VideoPlayer::onExit() {
    Widget::onExit();
    JSFunction::getFunction("VideoPlayer.setVisible").invoke<void>(_videoPlayerIndex, false);
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback &callback) {
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(int event) {
    if (event == QUIT_FULLSCREEN) {
        _fullScreenEnabled = false;
    } else {
        VideoPlayer::EventType videoEvent = (VideoPlayer::EventType)event;
        if (videoEvent == VideoPlayer::EventType::PLAYING) {
            _isPlaying = true;
        } else {
            _isPlaying = false;
        }

        if (_eventCallback) {
            _eventCallback(this, videoEvent);
        }
    }
}

cocos2d::ui::Widget *VideoPlayer::createCloneInstance() {
    return VideoPlayer::create();
}

void VideoPlayer::copySpecialProperties(Widget *widget) {
    VideoPlayer *videoPlayer = dynamic_cast<VideoPlayer *>(widget);
    if (videoPlayer) {
        _isPlaying = videoPlayer->_isPlaying;
        _isLooping = videoPlayer->_isLooping;
        _isUserInputEnabled = videoPlayer->_isUserInputEnabled;
        _styleType = videoPlayer->_styleType;
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

void executeVideoCallback(int index, int event) {
    auto it = s_allVideoPlayers.find(index);
    if (it != s_allVideoPlayers.end()) {
        s_allVideoPlayers[index]->onPlayEvent(event);
    }
}

#endif

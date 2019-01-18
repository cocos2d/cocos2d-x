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


#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)

#include <stdlib.h>
#include <string>
#include "base/CCDirector.h"
#include "base/CCEventListenerKeyboard.h"

#include "player.h"
#include "platform/tizen/CCApplication-tizen.h"

#include <app.h>
#include <camera.h>
#include <efl_extension.h>

//-----------------------------------------------------------------------------------------------------------
USING_NS_CC;

#define QUIT_FULLSCREEN 1000

using namespace cocos2d::experimental::ui;

class _VideoPlayerTizen
{
public:
    _VideoPlayerTizen(VideoPlayer* videoPlayer)
    {
        _videoPlayer = videoPlayer;

        Application* app = Application::getInstance();
        _layout = elm_layout_add(app->_win);
        Evas *evas = evas_object_evas_get(_layout);
        _image = evas_object_image_filled_add(evas);
        evas_object_show(_image);
        player_create(&_player);
        player_set_looping(_player, videoPlayer->isLooping() );

        evas_object_event_callback_add(_image, EVAS_CALLBACK_MOUSE_UP, _VideoPlayerTizen::mouse_up_cb, this);
        eext_object_event_callback_add(app->_win, EEXT_CALLBACK_BACK, _VideoPlayerTizen::win_back_cb, this);
    }

    virtual ~_VideoPlayerTizen()
    {
        Application* app = Application::getInstance();
        eext_object_event_callback_del(app->_win, EEXT_CALLBACK_BACK, _VideoPlayerTizen::win_back_cb);
        evas_object_event_callback_del(_image, EVAS_CALLBACK_MOUSE_UP, _VideoPlayerTizen::mouse_up_cb);

        player_stop(_player);
        player_unprepare(_player);
        player_destroy(_player);
        evas_object_del(_image);
        evas_object_del(_layout);
    }

    static void mouse_up_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
    {
        if (_videoPlayer->_isUserInputEnabled())
        {
            _VideoPlayerTizen* videoPlayerTizen = (_VideoPlayerTizen*)data;
            if (videoPlayerTizen->_videoPlayer->isPlaying())
            {
                videoPlayerTizen->_videoPlayer->pause();
            }
            else
            {
                videoPlayerTizen->_videoPlayer->resume();
            }
        }
    }

    static void win_back_cb(void *data, Evas_Object *obj, void *event_info) {
        _VideoPlayerTizen* videoPlayerTizen = (_VideoPlayerTizen*)data;
        videoPlayerTizen->_videoPlayer->onPlayEvent(QUIT_FULLSCREEN);
        evas_object_resize(videoPlayerTizen->_image, videoPlayerTizen->_width, videoPlayerTizen->_height);
        evas_object_move(videoPlayerTizen->_image, videoPlayerTizen->_x, videoPlayerTizen->_y);
    }

    void setRectangle(Evas_Coord x, Evas_Coord y, Evas_Coord width, Evas_Coord height)
    {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
    }

    player_h _player;
    Evas_Object* _image;
    Evas_Object* _layout;
    VideoPlayer* _videoPlayer;
    Evas_Coord _x;
    Evas_Coord _y;
    Evas_Coord _width;
    Evas_Coord _height;
};

VideoPlayer::VideoPlayer()
: _videoPlayerIndex(-1)
, _eventCallback(nullptr)
, _fullScreenEnabled(false)
, _fullScreenDirty(false)
, _keepAspectRatioEnabled(false)
, _isLooping(false)
, _isUserInputEnabled(true)
, _styleType(StyleType::DEFAULT)
{
    _videoView = (void*) new (std::nothrow) _VideoPlayerTizen(this);

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addchild(_debugDrawNode);
#endif
}

VideoPlayer::~VideoPlayer()
{
    delete (_VideoPlayerTizen*)_videoView;
}

void VideoPlayer::setFileName(const std::string& fileName)
{
    _videoURL = fileName;
    _videoSource = VideoPlayer::Source::FILENAME;

    _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;

    const char* uri = _videoURL.c_str();
    std::string fullpath;
    fullpath.append(app_get_resource_path());
    fullpath.append(fileName.c_str());
    player_set_uri(impl->_player, fullpath.c_str());
}

void VideoPlayer::setURL(const std::string& videoUrl)
{
    _videoURL = videoUrl;
    _videoSource = VideoPlayer::Source::URL;

    _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
    player_set_uri(impl->_player, videoUrl.c_str());
}

void VideoPlayer::setLooping(bool looping)
{
    _isLooping = looping;
    _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
   player_set_looping(impl->_player, looping );
}

void VideoPlayer::setUserInputEnabled(bool enableInput)
{
    _isUserInputEnabled = enableInput
    
}

void VideoPlayer::setStyle(StyleType style)
{
    _styleType = style;
}

void VideoPlayer::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    cocos2d::ui::Widget::draw(renderer,transform,flags);

    if (flags & FLAGS_TRANSFORM_DIRTY)
    {
        auto directorInstance = Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();

        auto winSize = directorInstance->getWinSize();

        auto leftBottom = convertToWorldSpace(Point::ZERO);
        auto rightTop = convertToWorldSpace(Point(_contentSize.width,_contentSize.height));

        auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
        auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();

        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        Evas_Coord width = (rightTop.x - leftBottom.x) * glView->getScaleX();
        Evas_Coord height = (rightTop.y - leftBottom.y) * glView->getScaleY();
        Evas_Coord x = leftBottom.x * glView->getScaleX();
        Evas_Coord y = leftBottom.y * glView->getScaleY();

        impl->setRectangle(x, y, width, height);
        evas_object_resize(impl->_image, width, height);
        evas_object_move(impl->_image, uiLeft, uiTop);
    }

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode->clear();
    auto size = getContentSize();
    Point vertices[4]=
    {
        Point::ZERO,
        Point(size.width, 0),
        Point(size.width, size.height),
        Point(0, size.height)
    };
    _debugdrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    if (_fullScreenEnabled != enabled)
    {
        _fullScreenEnabled = enabled;

        auto directorInstance = Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();

        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        evas_object_resize(impl->_image, frameSize.width, frameSize.height);
        evas_object_move(impl->_image, 0, 0);
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
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        if (_keepAspectRatioEnabled == enable)
        {
                player_set_display_mode(impl->_player, PLAYER_DISPLAY_MODE_LETTER_BOX);
        }
        else
        {
                player_set_display_mode(impl->_player, PLAYER_DISPLAY_MODE_FULL_SCREEN);
        }
    }
}

#if CC_VIDEOPLAYER_DEBUG_DRAW
void VideoPlayer::drawDebugData()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");

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

static void _player_completed_cb(void *user_data)
{
    VideoPlayer* player = (VideoPlayer*)user_data;
    player->onPlayEvent((int)VideoPlayer::EventType::COMPLETED);
}

static void _player_interrupted_cb(player_interrupted_code_e code, void *user_data)
{
    VideoPlayer* player = (VideoPlayer*)user_data;
    player->onPlayEvent((int)VideoPlayer::EventType::PAUSED);
}

static void _player_video_frame_decoded_cb(unsigned char *data, int width, int height, unsigned int size, void *user_data)
{
    VideoPlayer* player = (VideoPlayer*)user_data;
    player->onPlayEvent((int)VideoPlayer::EventType::PLAYING);
}

void VideoPlayer::play()
{
    if (! _videoURL.empty())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        player_set_sound_type(impl->_player, SOUND_TYPE_MEDIA);
        player_set_display(impl->_player, PLAYER_DISPLAY_TYPE_EVAS, GET_DISPLAY(impl->_image));

        if (_keepAspectRatioEnabled)
        {
            player_set_display_mode(impl->_player, PLAYER_DISPLAY_MODE_LETTER_BOX);
        }
        else
        {
            player_set_display_mode(impl->_player, PLAYER_DISPLAY_MODE_FULL_SCREEN);
        }

        player_set_completed_cb(impl->_player, _player_completed_cb, this);
        player_set_interrupted_cb(impl->_player, _player_interrupted_cb, this);

        player_prepare(impl->_player);
        int ret = player_start(impl->_player);
        if (ret == PLAYER_ERROR_NONE)
        {
            this->onPlayEvent((int)VideoPlayer::EventType::PLAYING);
        }
        this->setVisible(true);
    }
}

void VideoPlayer::pause()
{
    if (! _videoURL.empty())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        int ret = player_pause(impl->_player);
        if (ret == PLAYER_ERROR_NONE)
        {
            this->onPlayEvent((int)VideoPlayer::EventType::PAUSED);
        }
    }
}

void VideoPlayer::resume()
{
    if (! _videoURL.empty())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        int ret = player_start(impl->_player);
        if (ret == PLAYER_ERROR_NONE)
        {
            this->onPlayEvent((int)VideoPlayer::EventType::PLAYING);
        }
    }
}

void VideoPlayer::stop()
{
    if (! _videoURL.empty())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        int ret = player_stop(impl->_player);
        if (ret == PLAYER_ERROR_NONE)
        {
            this->onPlayEvent((int)VideoPlayer::EventType::STOPPED);
        }
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (! _videoURL.empty())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        player_set_play_position(impl->_player, sec, false, NULL, NULL);
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}

void VideoPlayer::onEnter()
{
    Widget::onEnter();
    if (isVisible())
    {
        _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
        player_set_display_visible(impl->_player, true);
    }
}

void VideoPlayer::onExit()
{
    Widget::onExit();
    _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;
    player_set_display_visible(impl->_player, false);
}

void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);
    _VideoPlayerTizen* impl = (_VideoPlayerTizen*)_videoView;

    if (!visible)
    {
        player_set_display_visible(impl->_player, false);
    }
    else if(isRunning())
    {
        player_set_display_visible(impl->_player, true);
    }
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback)
{
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(int event)
{
    if (event == QUIT_FULLSCREEN)
    {
        _fullScreenEnabled = false;
    } 
    else
    {
        VideoPlayer::EventType videoEvent = (VideoPlayer::EventType)event;
        if (videoEvent == VideoPlayer::EventType::PLAYING) {
            _isPlaying = true;
        } else {
            _isPlaying = false;
        }

        if (_eventCallback)
        {
            _eventCallback(this,videoEvent);
        }
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

#endif

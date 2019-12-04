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

// No Available on tvOS
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)

using namespace cocos2d::experimental::ui;
//-------------------------------------------------------------------------------------

#include "platform/ios/CCEAGLView-ios.h"
#import <AVKit/AVPlayerViewController.h>
#import <CoreMedia/CMTime.h>
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

@interface UIVideoViewWrapperIos : NSObject

typedef NS_ENUM(NSInteger, PlayerbackState) {
    PlayerbackStateUnknown = 0,
    PlayerbackStatePaused,
    PlayerbackStopped,
    PlayerbackStatePlaying,
    PlayerbackStateCompleted
};

@property (assign, nonatomic) AVPlayerViewController * playerController;

- (void) setFrame:(int) left :(int) top :(int) width :(int) height;
- (void) setURL:(int) videoSource :(std::string&) videoUrl;
- (void) play;
- (void) pause;
- (void) resume;
- (void) stop;
- (void) seekTo:(float) sec;
- (void) setVisible:(BOOL) visible;
- (void) setKeepRatioEnabled:(BOOL) enabled;
- (void) setFullScreenEnabled:(BOOL) enabled;
- (BOOL) isFullScreenEnabled;
- (void) showPlaybackControls:(BOOL) value;
- (void) setRepeatEnabled:(BOOL)enabled;
- (void) setUserInteractionEnabled:(BOOL)userInteractionEnabled;


-(id) init:(void*) videoPlayer;
-(void) videoFinished:(NSNotification*) notification;

@end

@implementation UIVideoViewWrapperIos
{
    int _left;
    int _top;
    int _width;
    int _height;
    BOOL _keepRatioEnabled;
    BOOL _repeatEnabled;
    BOOL _showPlaybackControls;
    BOOL _userInteractionEnabled;
    PlayerbackState _state;
    VideoPlayer* _videoPlayer;
}

-(id)init:(void*)videoPlayer
{
    if (self = [super init]) {
        self.playerController = [AVPlayerViewController new];

        [self setRepeatEnabled:FALSE];
        [self showPlaybackControls:TRUE];
        [self setUserInteractionEnabled:TRUE];
        [self setKeepRatioEnabled:FALSE];
        
        _videoPlayer = (VideoPlayer*)videoPlayer;
        _state = PlayerbackStateUnknown;
    }

    return self;
}

-(void) dealloc
{
    _videoPlayer = nullptr;
    [self clean];
    [self.playerController release];
    [super dealloc];
}

-(void) clean
{
    [self stop];
    [self removePlayerEventListener];
    [self.playerController.view removeFromSuperview];
}

-(void) setFrame:(int)left :(int)top :(int)width :(int)height
{
    _left = left;
    _width = width;
    _top = top;
    _height = height;
    [self.playerController.view setFrame:CGRectMake(left, top, width, height)];
}

-(void) setFullScreenEnabled:(BOOL) enabled
{
    // AVPlayerViewController doesn't provide API to enable fullscreen. But you can toggle
    // fullsreen by the playback controllers.
}

-(BOOL) isFullScreenEnabled
{
    return false;
}


-(void) showPlaybackControls:(BOOL)value
{
    _showPlaybackControls = value;
    self.playerController.showsPlaybackControls = value;
}

-(void) setRepeatEnabled:(BOOL)enabled
{
    _repeatEnabled = enabled;
    if (self.playerController.player) {
        if (_repeatEnabled)
            self.playerController.player.actionAtItemEnd = AVPlayerActionAtItemEndNone;
        else
            self.playerController.player.actionAtItemEnd = AVPlayerActionAtItemEndPause;
    }
}

-(void) setUserInteractionEnabled:(BOOL)userInteractionEnabled
{
    _userInteractionEnabled = userInteractionEnabled;
    self.playerController.view.userInteractionEnabled = _userInteractionEnabled;
}

-(void) setURL:(int)videoSource :(std::string &)videoUrl
{
    [self clean];

    if (videoSource == 1)
        self.playerController.player = [[[AVPlayer alloc] initWithURL:[NSURL URLWithString:@(videoUrl.c_str())]] autorelease];
    else
        self.playerController.player = [[[AVPlayer alloc] initWithURL:[NSURL fileURLWithPath:@(videoUrl.c_str())]] autorelease];

    [self setRepeatEnabled:_repeatEnabled];
    [self setKeepRatioEnabled:_keepRatioEnabled];
    [self setUserInteractionEnabled:_userInteractionEnabled];
    [self showPlaybackControls:_showPlaybackControls];

    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    auto eaglview = (CCEAGLView *) view->getEAGLView();
    [eaglview addSubview:self.playerController.view];
    [self registerPlayerEventListener];
}

-(void) videoFinished:(NSNotification *)notification
{
    if(_videoPlayer != nullptr) {
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::COMPLETED);
        _state = PlayerbackStateCompleted;

        if (_repeatEnabled) {
            [self seekTo:0];
            [self play];
        }
    }
}

-(void) seekTo:(float)sec
{
    if (self.playerController.player)
        [self.playerController.player seekToTime:CMTimeMake(sec, 1)];
}

-(void) setVisible:(BOOL)visible
{
    [self.playerController.view setHidden:!visible];
}

-(void) setKeepRatioEnabled:(BOOL)enabled
{
    _keepRatioEnabled = enabled;
    if (_keepRatioEnabled)
        self.playerController.videoGravity = AVLayerVideoGravityResizeAspect;
    else
        self.playerController.videoGravity = AVLayerVideoGravityResizeAspectFill;
}

-(void) play
{
    if (self.playerController.player && _state != PlayerbackStatePlaying) {
        [self.playerController.player play];
        _state = PlayerbackStatePlaying;
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::PLAYING);
    }
}

-(void) pause
{
    if (self.playerController.player && _state == PlayerbackStatePlaying) {
        [self.playerController.player pause];
        _state = PlayerbackStatePaused;
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::PAUSED);
    }
}

-(void) resume
{
    if (self.playerController.player && _state == PlayerbackStatePaused)
        [self play];
}

-(void) stop
{
    // AVPlayer doesn't have stop, so just pause it, and seek time to 0.
    if (self.playerController.player && _state != PlayerbackStopped) {
        [self seekTo:0];
        [self.playerController.player pause];
        _state = PlayerbackStopped;
        
        // stop() will be invoked in dealloc, which is invoked by _videoPlayer's destructor,
        // so do't send the message when _videoPlayer is being deleted.
        if (_videoPlayer)
            _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::STOPPED);
    }
}

-(void) registerPlayerEventListener
{
    if (self.playerController.player)
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(videoFinished:)
                                                 name:AVPlayerItemDidPlayToEndTimeNotification
                                                 object:self.playerController.player.currentItem];
}

-(void) removePlayerEventListener
{
    if (self.playerController.player)
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                              name:AVPlayerItemDidPlayToEndTimeNotification
                                              object:self.playerController.player.currentItem];
}

@end
//------------------------------------------------------------------------------------------------------------

VideoPlayer::VideoPlayer()
: _isPlaying(false)
, _fullScreenDirty(false)
, _fullScreenEnabled(false)
, _keepAspectRatioEnabled(false)
, _videoPlayerIndex(-1)
, _eventCallback(nullptr)
, _isLooping(false)
, _isUserInputEnabled(true)
, _styleType(StyleType::DEFAULT)
{
    _videoView = [[UIVideoViewWrapperIos alloc] init:this];

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
}

VideoPlayer::~VideoPlayer()
{
    if(_videoView)
    {
        [((UIVideoViewWrapperIos*)_videoView) dealloc];
    }
}

void VideoPlayer::setFileName(const std::string& fileName)
{
    _videoURL = FileUtils::getInstance()->fullPathForFilename(fileName);
    _videoSource = VideoPlayer::Source::FILENAME;
    [((UIVideoViewWrapperIos*)_videoView) setURL:(int)_videoSource :_videoURL];
}

void VideoPlayer::setURL(const std::string& videoUrl)
{
    _videoURL = videoUrl;
    _videoSource = VideoPlayer::Source::URL;
    [((UIVideoViewWrapperIos*)_videoView) setURL:(int)_videoSource :_videoURL];
}

void VideoPlayer::setLooping(bool looping)
{
    _isLooping = looping;
    [((UIVideoViewWrapperIos*)_videoView) setRepeatEnabled:_isLooping];
}

void VideoPlayer::setUserInputEnabled(bool enableInput)
{
    _isUserInputEnabled = enableInput;
    [((UIVideoViewWrapperIos*)_videoView) setUserInteractionEnabled:enableInput];
}

void VideoPlayer::setStyle(StyleType style)
{
    _styleType = style;

    switch (style) {
        case StyleType::DEFAULT:
            [((UIVideoViewWrapperIos*)_videoView) showPlaybackControls:TRUE];
            break;

        case StyleType::NONE:
            [((UIVideoViewWrapperIos*)_videoView) showPlaybackControls:FALSE];
            break;
    }
}

void VideoPlayer::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    cocos2d::ui::Widget::draw(renderer,transform,flags);

    if (flags & FLAGS_TRANSFORM_DIRTY)
    {
        auto directorInstance = Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();
        auto scaleFactor = [static_cast<CCEAGLView *>(glView->getEAGLView()) contentScaleFactor];

        auto winSize = directorInstance->getWinSize();

        auto leftBottom = convertToWorldSpace(Vec2::ZERO);
        auto rightTop = convertToWorldSpace(Vec2(_contentSize.width,_contentSize.height));

        auto uiLeft = (frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX()) / scaleFactor;
        auto uiTop = (frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY()) / scaleFactor;

        [((UIVideoViewWrapperIos*)_videoView) setFrame :uiLeft :uiTop
                                                          :(rightTop.x - leftBottom.x) * glView->getScaleX() / scaleFactor
                                                          :( (rightTop.y - leftBottom.y) * glView->getScaleY()/scaleFactor)];
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
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
#endif
}

bool VideoPlayer::isFullScreenEnabled()const
{
    return [((UIVideoViewWrapperIos*)_videoView) isFullScreenEnabled];
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    [((UIVideoViewWrapperIos*)_videoView) setFullScreenEnabled:enabled];
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable)
    {
        _keepAspectRatioEnabled = enable;
        [((UIVideoViewWrapperIos*)_videoView) setKeepRatioEnabled:enable];
    }
}

void VideoPlayer::play()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) play];
    }
}

void VideoPlayer::pause()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) pause];
    }
}

void VideoPlayer::resume()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) resume];
    }
}

void VideoPlayer::stop()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) stop];
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) seekTo:sec];
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}

bool VideoPlayer::isLooping() const
{
    return _isLooping;
}

bool VideoPlayer::isUserInputEnabled() const
{
    return _isUserInputEnabled;
}

void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);

    if (!visible)
    {
        [((UIVideoViewWrapperIos*)_videoView) setVisible:NO];
    }
    else if(isRunning())
    {
        [((UIVideoViewWrapperIos*)_videoView) setVisible:YES];
    }
}

void VideoPlayer::onEnter()
{
    Widget::onEnter();
    if (isVisible())
    {
        [((UIVideoViewWrapperIos*)_videoView) setVisible: YES];
    }
}

void VideoPlayer::onExit()
{
    Widget::onExit();
    [((UIVideoViewWrapperIos*)_videoView) setVisible: NO];
}

void VideoPlayer::addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback)
{
    _eventCallback = callback;
}

void VideoPlayer::onPlayEvent(int event)
{
    if (event == (int)VideoPlayer::EventType::PLAYING) {
        _isPlaying = true;
    } else {
        _isPlaying = false;
    }

    if (_eventCallback)
    {
        _eventCallback(this, (VideoPlayer::EventType)event);
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

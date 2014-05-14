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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

using namespace cocos2d::experimental::ui;
//-------------------------------------------------------------------------------------
#include "CCEAGLView.h"
#import <MediaPlayer/MediaPlayer.h>

@interface UIVideoViewWrapperIos : NSObject

@property (strong,nonatomic) MPMoviePlayerController * moviePlayer;

- (void) setVideoRect:(int) left :(int) top :(int) width :(int) height;
- (void) setVideoURL:(int) videoSource :(std::string&) videoUrl;
- (void) startVideo;
- (void) pauseVideo;
- (void) resumeVideo;
- (void) stopVideo;
- (void) seekVideoTo:(float) sec;
- (void) setVideoVisible:(bool) visible;
- (void) setVideoKeepRatioEnabled:(bool) enabled;
- (void) setFullScreenEnabled:(bool) enabled;
- (bool) isFullScreenEnabled;

-(id) init:(void*) videoPlayer;

-(void) videoFinished:(NSNotification*) notification;
-(void) playStateChange;

+(NSString*) fullPathFromRelativePath:(NSString*) relPath;

@end

@implementation UIVideoViewWrapperIos
{
    int _left;
    int _top;
    int _width;
    int _height;
    bool _keepRatioEnabled;
    
    VideoPlayer* _videoPlayer;
}

-(id)init:(void*)videoPlayer
{
    if (self = [super init]) {
        self.moviePlayer = nullptr;
        _videoPlayer = (VideoPlayer*)videoPlayer;
        _keepRatioEnabled = false;
    }
    
    return self;
}

-(void) dealloc
{
    if (self.moviePlayer != nullptr) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:self.moviePlayer];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackStateDidChangeNotification object:self.moviePlayer];
        
        [self.moviePlayer stop];
        [self.moviePlayer.view removeFromSuperview];
        self.moviePlayer = nullptr;
        _videoPlayer = nullptr;
    }
    [super dealloc];
}

-(void) setVideoRect:(int)left :(int)top :(int)width :(int)height
{
    _left = left;
    _width = width;
    _top = top;
    _height = height;
    if (self.moviePlayer != nullptr) {
        [self.moviePlayer.view setFrame:CGRectMake(left, top, width, height)];
    }
}

-(void) setFullScreenEnabled:(bool) enabled
{
    if (self.moviePlayer != nullptr) {
        [self.moviePlayer setFullscreen:enabled animated:(true)];
    }
}

-(bool) isFullScreenEnabled
{
    if (self.moviePlayer != nullptr) {
        return [self.moviePlayer isFullscreen];
    }
    
    return false;
}

-(void) setVideoURL:(int)videoSource :(std::string &)videoUrl
{
    if (self.moviePlayer != nullptr) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:self.moviePlayer];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackStateDidChangeNotification object:self.moviePlayer];
        
        [self.moviePlayer stop];
        [self.moviePlayer.view removeFromSuperview];
        self.moviePlayer = nullptr;
    }
    
    if (videoSource == 1) {
        self.moviePlayer = [[MPMoviePlayerController alloc] initWithContentURL:[NSURL URLWithString:@(videoUrl.c_str())]];
        self.moviePlayer.movieSourceType = MPMovieSourceTypeStreaming;
    } else {
        NSString *path = [UIVideoViewWrapperIos fullPathFromRelativePath:@(videoUrl.c_str())];
        self.moviePlayer = [[MPMoviePlayerController alloc] initWithContentURL:[NSURL fileURLWithPath:path]];
        self.moviePlayer.movieSourceType = MPMovieSourceTypeFile;
    }
    self.moviePlayer.allowsAirPlay = false;
    self.moviePlayer.controlStyle = MPMovieControlStyleEmbedded;
    self.moviePlayer.view.userInteractionEnabled = true;
    
    auto clearColor = [UIColor clearColor];
    self.moviePlayer.backgroundView.backgroundColor = clearColor;
    self.moviePlayer.view.backgroundColor = clearColor;
    for (UIView * subView in self.moviePlayer.view.subviews) {
        subView.backgroundColor = clearColor;
    }
    
    if (_keepRatioEnabled) {
        self.moviePlayer.scalingMode = MPMovieScalingModeAspectFit;
    } else {
        self.moviePlayer.scalingMode = MPMovieScalingModeFill;
    }
    
    auto view = cocos2d::Director::getInstance()->getOpenGLView();
    auto eaglview = (CCEAGLView *) view->getEAGLView();
    [eaglview addSubview:self.moviePlayer.view];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(videoFinished:) name:MPMoviePlayerPlaybackDidFinishNotification object:self.moviePlayer];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(playStateChange) name:MPMoviePlayerPlaybackStateDidChangeNotification object:self.moviePlayer];
}

-(void) videoFinished:(NSNotification *)notification
{
    if(_videoPlayer != nullptr)
    {
        if([self.moviePlayer playbackState] != MPMoviePlaybackStateStopped)
        {
            _videoPlayer->onVideoEvent(VideoPlayer::EventType::COMPLETED);
        }
    }
}

-(void) playStateChange
{
    MPMoviePlaybackState state = [self.moviePlayer playbackState];
    switch (state) {
        case MPMoviePlaybackStatePaused:
            _videoPlayer->onVideoEvent(VideoPlayer::EventType::PAUSED);
            break;
        case MPMoviePlaybackStateStopped:
            _videoPlayer->onVideoEvent(VideoPlayer::EventType::STOPPED);
            break;
        case MPMoviePlaybackStatePlaying:
            _videoPlayer->onVideoEvent(VideoPlayer::EventType::PLAYING);
            break;
        case MPMoviePlaybackStateInterrupted:
            break;
        case MPMoviePlaybackStateSeekingBackward:
            break;
        case MPMoviePlaybackStateSeekingForward:
            break;
        default:
            break;
    }
}

-(void) seekVideoTo:(float)sec
{
    if (self.moviePlayer != NULL) {
        [self.moviePlayer setCurrentPlaybackTime:(sec)];
    }
}

-(void) setVideoVisible:(bool)visible
{
    if (self.moviePlayer != NULL) {
        [self.moviePlayer.view setHidden:visible];
    }
}

-(void) setVideoKeepRatioEnabled:(bool)enabled
{
    _keepRatioEnabled = enabled;
    if (self.moviePlayer != NULL) {
        if (enabled) {
            self.moviePlayer.scalingMode = MPMovieScalingModeAspectFit;
        } else {
            self.moviePlayer.scalingMode = MPMovieScalingModeFill;
        }
    }
}

-(void) startVideo
{
    if (self.moviePlayer != NULL) {
        [self.moviePlayer.view setFrame:CGRectMake(_left, _top, _width, _height)];
        [self.moviePlayer play];
    }
}

-(void) pauseVideo
{
    if (self.moviePlayer != NULL) {
        [self.moviePlayer pause];
    }
}

-(void) resumeVideo
{
    if (self.moviePlayer != NULL) {
        if([self.moviePlayer playbackState] == MPMoviePlaybackStatePaused)
        {
            [self.moviePlayer play];
        }
    }
}

-(void) stopVideo
{
    if (self.moviePlayer != NULL) {
        [self.moviePlayer stop];
    }
}

+(NSString*) fullPathFromRelativePath:(NSString*) relPath
{
    // do not convert an absolute path (starting with '/')
    if(([relPath length] > 0) && ([relPath characterAtIndex:0] == '/'))
    {
        return relPath;
    }
    
    NSMutableArray *imagePathComponents = [NSMutableArray arrayWithArray:[relPath pathComponents]];
    NSString *file = [imagePathComponents lastObject];
    
    [imagePathComponents removeLastObject];
    NSString *imageDirectory = [NSString pathWithComponents:imagePathComponents];
    
    NSString *fullpath = [[NSBundle mainBundle] pathForResource:file ofType:nil inDirectory:imageDirectory];
    if (fullpath == nil)
        fullpath = relPath;
    
    return fullpath;
}
@end
//------------------------------------------------------------------------------------------------------------

VideoPlayer::VideoPlayer()
: _videoPlayerIndex(-1)
, _callback(nullptr)
, _fullScreenEnabled(false)
, _fullScreenDirty(false)
, _keepAspectRatioEnabled(false)
, _isPlaying(false)
{
    _videiView = [[UIVideoViewWrapperIos alloc] init:this];
}

VideoPlayer::~VideoPlayer()
{
    if(_videiView)
    {
        [((UIVideoViewWrapperIos*)_videiView) dealloc];
    }
}

void VideoPlayer::setVideoFileName(const std::string& fileName)
{
    _videoUrl = fileName;
    _videoSource = VideoPlayer::VideoSource::FILENAME;
    [((UIVideoViewWrapperIos*)_videiView) setVideoURL:(int)_videoSource :_videoUrl];
}

void VideoPlayer::setVideoURL(const std::string& videoUrl)
{
    _videoUrl = videoUrl;
    _videoSource = VideoPlayer::VideoSource::URL;
    [((UIVideoViewWrapperIos*)_videiView) setVideoURL:(int)_videoSource :_videoUrl];
}

void VideoPlayer::draw(Renderer* renderer, const Matrix &transform, bool transformUpdated)
{
    cocos2d::ui::Widget::draw(renderer,transform,transformUpdated);
    
    if (transformUpdated)
    {
        auto directorInstance = Director::getInstance();
        auto glView = directorInstance->getOpenGLView();
        auto frameSize = glView->getFrameSize();
        auto scaleFactor = directorInstance->getContentScaleFactor();
        
        auto winSize = directorInstance->getWinSize();
        
        auto leftBottom = convertToWorldSpace(Vec2::ZERO);
        auto rightTop = convertToWorldSpace(Vec2(_contentSize.width,_contentSize.height));
        
        auto uiLeft = (frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX()) / scaleFactor;
        auto uiTop = (frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY()) / scaleFactor;
        
        [((UIVideoViewWrapperIos*)_videiView) setVideoRect:uiLeft :uiTop
                                                          :(rightTop.x - leftBottom.x) * glView->getScaleX() / scaleFactor
                                                          :( (rightTop.y - leftBottom.y) * glView->getScaleY()/scaleFactor)];
    }
    
#if CC_VIDEOPLAYER_DEBUG_DRAW
    _customDebugDrawCommand.init(_globalZOrder);
    _customDebugDrawCommand.func = CC_CALLBACK_0(VideoPlayer::drawDebugData, this);
    renderer->addCommand(&_customDebugDrawCommand);
#endif
}

bool VideoPlayer::isFullScreenEnabled()
{
    return [((UIVideoViewWrapperIos*)_videiView) isFullScreenEnabled];
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    [((UIVideoViewWrapperIos*)_videiView) setFullScreenEnabled:enabled];
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable)
    {
        _keepAspectRatioEnabled = enable;
        [((UIVideoViewWrapperIos*)_videiView) setVideoKeepRatioEnabled:enable];
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

void VideoPlayer::startVideo()
{
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) startVideo];
    }
}

void VideoPlayer::pauseVideo()
{
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) pauseVideo];
    }
}

void VideoPlayer::resumeVideo()
{
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) resumeVideo];
    }
}

void VideoPlayer::stopVideo()
{
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) stopVideo];
    }
}

void VideoPlayer::seekVideoTo(float sec)
{
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) seekVideoTo:sec];
    }
}

bool VideoPlayer::isPlaying() const
{
    return _isPlaying;
}

void VideoPlayer::setVisible(bool visible)
{
    cocos2d::ui::Widget::setVisible(visible);
    
    if (! _videoUrl.empty())
    {
        [((UIVideoViewWrapperIos*)_videiView) setVideoVisible:visible];
    }
}

void VideoPlayer::addEventListener(const VideoPlayer::EventCallback& callback)
{
    _callback = callback;
}

void VideoPlayer::onVideoEvent(VideoPlayer::EventType event)
{
    if (event == VideoPlayer::EventType::PLAYING) {
        _isPlaying = true;
    } else {
        _isPlaying = false;
    }
    
    if (_callback)
    {
        _callback(this,event);
    }
}

#endif

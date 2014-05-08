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

#ifndef __COCOS2D_UI_VIDEOWEIGTH_H_
#define __COCOS2D_UI_VIDEOWEIGTH_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ui/UIWidget.h"

NS_CC_BEGIN
namespace experimental{
namespace ui{

    enum class VideoWidgetEvent
    {
        PLAYING = 0,
        PAUSED,
        STOPPED,
        COMPLETED
    };
    
    typedef std::function<void(Ref*,VideoWidgetEvent)> VideoWidgetCallback;

    class VideoWidget : public cocos2d::ui::Widget
    {
    public:
        
       CREATE_FUNC(VideoWidget);

       //Sets local file[support assets' file on android] as a video source for VideoWidget
       virtual void setVideoFileName(const std::string& videoPath);
       virtual const std::string& getVideoFileName() const { return _videoUrl;}

       //Sets network link as a video source for VideoWidget 
       virtual void setVideoURL(const std::string& videoUrl);
       virtual const std::string& getVideoURL() const { return _videoUrl;}

       virtual void startVideo();
       virtual void pauseVideo();
       virtual void resumeVideo();
       virtual void stopVideo();

       virtual void seekVideoTo(float sec);
       virtual bool isPlaying() const;

       virtual void setVisible(bool visible) override;

       virtual void setKeepAspectRatioEnabled(bool enable);
       virtual bool isKeepAspectRatioEnabled() { return _keepAspectRatioEnabled;}

       virtual void setFullScreenEnabled(bool enabled);
       virtual bool isFullScreenEnabled();
       
       virtual void setEventListener(const VideoWidgetCallback& callback);

       virtual void onVideoEvent(VideoWidgetEvent event);
       virtual void draw(Renderer *renderer, const Matrix& transform, bool transformUpdated) override;

    protected:
        VideoWidget();
        virtual ~VideoWidget();

#if CC_VIDEOWIDGET_DEBUG_DRAW
        CustomCommand _customDebugDrawCommand;
        void VideoWidget::drawDebugData();
#endif

        enum class VideoSource
        {
            FILENAME = 0,
            URL
        };

        bool _isPlaying;
        bool _fullScreenDirty;
        bool _fullScreenEnabled;
        bool _keepAspectRatioEnabled;

        std::string _videoUrl;
        VideoSource _videoSource;

        int _videoWidgetIndex;
        VideoWidgetCallback _callback;
        
        void* _videiView;
    };
}
}

NS_CC_END

#endif
#endif

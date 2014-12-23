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

        class VideoPlayer : public cocos2d::ui::Widget
        {
        public:
            enum class EventType
            {
                PLAYING = 0,
                PAUSED,
                STOPPED,
                COMPLETED
            };
            typedef std::function<void(Ref*,VideoPlayer::EventType)> ccVideoPlayerCallback;

            CREATE_FUNC(VideoPlayer);

            //Sets local file[support assets' file on android] as a video source for VideoPlayer
            virtual void setFileName(const std::string& videoPath);
            virtual const std::string& getFileName() const { return _videoURL;}

            //Sets network link as a video source for VideoPlayer 
            virtual void setURL(const std::string& _videoURL);
            virtual const std::string& getURL() const { return _videoURL;}

            virtual void play();
            virtual void pause();
            virtual void resume();
            virtual void stop();

            virtual void seekTo(float sec);
            virtual bool isPlaying() const;

            virtual void setVisible(bool visible) override;

            virtual void setKeepAspectRatioEnabled(bool enable);
            virtual bool isKeepAspectRatioEnabled()const { return _keepAspectRatioEnabled;}

            virtual void setFullScreenEnabled(bool enabled);
            virtual bool isFullScreenEnabled()const;

            virtual void addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback);

            virtual void onPlayEvent(int event);
            virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;

        protected:
            virtual cocos2d::ui::Widget* createCloneInstance() override;
            virtual void copySpecialProperties(Widget* model) override;
            
        CC_CONSTRUCTOR_ACCESS:
            VideoPlayer();
            virtual ~VideoPlayer();

        protected:
#if CC_VIDEOPLAYER_DEBUG_DRAW
            DrawNode *_debugDrawNode;
#endif

            enum class Source
            {
                FILENAME = 0,
                URL
            };

            bool _isPlaying;
            bool _fullScreenDirty;
            bool _fullScreenEnabled;
            bool _keepAspectRatioEnabled;

            std::string _videoURL;
            Source _videoSource;

            int _videoPlayerIndex;
            ccVideoPlayerCallback _eventCallback;

            void* _videoView;
        };
    }
}

NS_CC_END

#endif
#endif

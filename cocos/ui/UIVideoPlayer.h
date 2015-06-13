/****************************************************************************
 Copyright (c) 2014-2015 Chukong Technologies Inc.

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

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN
namespace experimental{
    namespace ui{

        /**
         * @class VideoPlayer
         * @brief @~english Displays a video file.
         * @~chinese 一个播放视频文件的控件。
         * 
         * @note @~english VideoPlayer displays a video file base on system widget.
         * It's mean VideoPlayer displays a video file above all graphical elements of cocos2d-x.
         * @~chinese VideoPlayer基于系统控件实现的视频播放，这意味着视频会被显示在cocos2d-x的所有图形元素之上。
         * @js NA
         */
        class VideoPlayer : public cocos2d::ui::Widget
        {
        public:
            /**
             * @~english Videoplayer play event type.
             * @~chinese Videoplayer视频播放事件。
             */
            enum class EventType
            {
                PLAYING = 0,
                PAUSED,
                STOPPED,
                COMPLETED
            };

            /**
             * @~english A callback which will be called after specific VideoPlayer event happens.
             * @~chinese VideoPlayer播放相关事件发生时的回调。
             */
            typedef std::function<void(Ref*,VideoPlayer::EventType)> ccVideoPlayerCallback;

            /**@~english
             * Static create method for instancing a VideoPlayer.
             * @~chinese 
             * 一个实例化VideoPlayer的静态创建函数。
             */
            CREATE_FUNC(VideoPlayer);

            /**@~english
             * Sets a file path as a video source for VideoPlayer.
             * @~chinese 
             * 设置一个视频文件路径作为VideoPlayer的视频源。
             */
            virtual void setFileName(const std::string& videoPath);
            
            /**
             * @brief @~english Get the filie path of video source.
             * @~chinese 获取视频源的文件路径。
             * 
             * @return @~english The video file path.
             * @~chinese 视频视频文件的路径。
             */
            virtual const std::string& getFileName() const { return _videoURL;}

            /**@~english
             * Sets a URL as a video source for VideoPlayer.
             * @~chinese 
             * 设置一个URL地址作为VideoPlayer的视频源。
             */
            virtual void setURL(const std::string& _videoURL);

            
            /**
             * @brief @~english Get the URL of video source.
             *
             * @~chinese 获取视频源的URL。
             * 
             * @return @~english A URL address.
             * @~chinese 一个URL地址。
             */
            virtual const std::string& getURL() const { return _videoURL;}

            /**
             * @~english Starts playback.
             * @~chinese 开始播放。
             */
            virtual void play();

            /**
             * @~english Pauses playback.
             * @~chinese 暂停播放。
             */
            virtual void pause();

            /**
             * @~english Resumes playback.
             * @~chinese 恢复播放。
             */
            virtual void resume();

            /**
             * @~english Stops playback.
             * @~chinese 停止播放。
             */
            virtual void stop();

            /**
             * @~english Seeks to specified time position.
             * @~chinese 跳转到指定的时间位置。
             * 
             * @param sec @~english The offset in seconds from the start to seek to.
             * @~chinese 相对起始位置的偏移量，以秒为单位。
             */
            virtual void seekTo(float sec);

            /**
             * @~english Checks whether the VideoPlayer is playing.
             * @~chinese 检查VideoPlayer当前是否正在播放。
             * 
             * @return @~english True if currently playing, false otherwise.
             * @~chinese VideoPlayer如果正在播放返回true，否则返回false。
             */
            virtual bool isPlaying() const;

            /**
             * @~english Causes the video player to keep aspect ratio or no when displaying the video.
             * @~chinese 设置视频播放时是否保持长宽比。
             * 
             * @param enable @~english Specify true to keep aspect ratio or false to scale the video until 
             * both dimensions fit the visible bounds of the view exactly.
             * @~chinese 设置为true时保持长宽比，否则视频会被拉伸以填满整个播放控件。
             */
            virtual void setKeepAspectRatioEnabled(bool enable);

            /**@~english
             * Indicates whether the video player keep aspect ratio when displaying the video.
             * @~chinese 获取视频播放是否保持长宽比
             */
            virtual bool isKeepAspectRatioEnabled()const { return _keepAspectRatioEnabled;}

            /**
             * @~english Causes the video player to enter or exit full-screen mode.
             * @~chinese 设置视频播放是否全屏模式。
             * 
             * @param fullscreen @~english Specify true to enter full-screen mode or false to exit full-screen mode.
             * @~chinese 指定true时进入全屏播放模式。
             */
            virtual void setFullScreenEnabled(bool fullscreen);

            /**
             * @~english Indicates whether the video player is in full-screen mode.
             * @~chinese 获取视频播放器是否进入全屏模式。
             * 
             * @return @~english True if the video player is in full-screen mode, false otherwise.
             * @~chinese 如果视频播放器在全屏播放模式下返回true,否则返回false。
             */
            virtual bool isFullScreenEnabled()const;

            /**
             * @~english Register a callback to be invoked when the video state is updated.
             * @~chinese 注册视频播放状态改变时的回调。
             * 
             * @param callback @~english a callback.
             * @~chinese 回调。
             */
            virtual void addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback);
            
            /**
             * @~english A function which will be called when video the video state is updated.
             * @~chinese 视频状态改变时被调用的一个成员函数。
             * 
             * @param event @~english event code. @~chinese 事件代码。
             * @see VideoPlayer::EventType.
             */
            virtual void onPlayEvent(int event);

            virtual void setVisible(bool visible) override;
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
// end group
/// @}
#endif
#endif

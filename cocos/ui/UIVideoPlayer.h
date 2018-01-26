/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) && !defined(CC_PLATFORM_OS_TVOS)

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
         * @brief Displays a video file.
         * 
         * @note VideoPlayer displays a video file base on system widget.
         * It's mean VideoPlayer displays a video file above all graphical elements of cocos2d-x.
         * @js NA
         */
        class VideoPlayer : public cocos2d::ui::Widget
        {
        public:
            /**
             * Videoplayer play event type.
             */
            enum class EventType
            {
                PLAYING = 0,
                PAUSED,
                STOPPED,
                COMPLETED
            };

            /**
             * A callback which will be called after specific VideoPlayer event happens.
             */
            typedef std::function<void(Ref*,VideoPlayer::EventType)> ccVideoPlayerCallback;

            /**
             *Static create method for instancing a VideoPlayer.
             */
            CREATE_FUNC(VideoPlayer);

            /**
             * Sets a file path as a video source for VideoPlayer.
             */
            virtual void setFileName(const std::string& videoPath);
            
            /**
             * @brief Get the local video file name.
             *
             * @return The video file name.
             */
            virtual const std::string& getFileName() const { return _videoURL;}

            /**
             * Sets a URL as a video source for VideoPlayer.
             */
            virtual void setURL(const std::string& _videoURL);

            
            /**
             * @brief Get the URL of remoting video source.
             *
             * @return A remoting URL address.
             */
            virtual const std::string& getURL() const { return _videoURL;}

            /**
             * Starts playback.
             */
            virtual void play();

            /**
             * Pauses playback.
             */
            virtual void pause()override;

            /**
             * Resumes playback.
             */
            virtual void resume()override;

            /**
             * Stops playback.
             */
            virtual void stop();

            /**
             * Seeks to specified time position.
             *
             * @param sec   The offset in seconds from the start to seek to.
             */
            virtual void seekTo(float sec);

            /**
             * Checks whether the VideoPlayer is playing.
             *
             * @return True if currently playing, false otherwise.
             */
            virtual bool isPlaying() const;

            /**
             * Causes the video player to keep aspect ratio or no when displaying the video.
             *
             * @param enable    Specify true to keep aspect ratio or false to scale the video until 
             * both dimensions fit the visible bounds of the view exactly.
             */
            virtual void setKeepAspectRatioEnabled(bool enable);

            /**
             * Indicates whether the video player keep aspect ratio when displaying the video.
             */
            virtual bool isKeepAspectRatioEnabled()const { return _keepAspectRatioEnabled;}

            /**
             * Causes the video player to enter or exit full-screen mode.
             * 
             * @param fullscreen    Specify true to enter full-screen mode or false to exit full-screen mode.
             */
            virtual void setFullScreenEnabled(bool fullscreen);

            /**
             * Indicates whether the video player is in full-screen mode.
             *
             * @return True if the video player is in full-screen mode, false otherwise.
             */
            virtual bool isFullScreenEnabled()const;

            /**
             * Register a callback to be invoked when the video state is updated.
             *
             * @param callback  The callback that will be run.
             */
            virtual void addEventListener(const VideoPlayer::ccVideoPlayerCallback& callback);
            
            /**
             * @brief A function which will be called when video is playing.
             *
             * @param event @see VideoPlayer::EventType.
             
             */
            virtual void onPlayEvent(int event);
            virtual void setVisible(bool visible) override;
            virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
            virtual void onEnter() override;
            virtual void onExit() override;

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

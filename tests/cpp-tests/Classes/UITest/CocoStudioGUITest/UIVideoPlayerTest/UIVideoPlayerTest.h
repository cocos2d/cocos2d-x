#ifndef __tests__VideoPlayerTest__
#define __tests__VideoPlayerTest__

#include "../UIScene.h"

USING_NS_CC;

class VideoPlayerTest : public UIScene
{
public:
    UI_SCENE_CREATE_FUNC(VideoPlayerTest);

    virtual bool init();

    void menuCloseCallback(Ref* sender);

    void menuRatioCallback(Ref* sender);
    void menuResourceVideoCallback(Ref* sender);
    void menuOnlineVideoCallback(Ref* sender);

    void menuFullScreenCallback(Ref* sender);
    void menuPauseCallback(Ref* sender);
    void menuResumeCallback(Ref* sender);
    void menuStopCallback(Ref* sender);
    void menuHintCallback(Ref* sender);
    
    void sliderCallback(Ref *sender, ui::Slider::EventType eventType);

    void videoEventCallback(Ref* sender, experimental::ui::VideoPlayer::EventType eventType);

private:
    void createVideo();
    void createSlider();

    MenuItemFont* _hintItem;
    experimental::ui::VideoPlayer* _videoPlayer;
    Label* _videoStateLabel;
    Rect _visibleRect;

    Layer* _rootLayer;

};

#endif // __tests__VideoPlayerTest__

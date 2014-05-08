#ifndef __tests__VideoWidgetTest__
#define __tests__VideoWidgetTest__

#include "../UIScene.h"

USING_NS_CC;

class VideoWidgetTest : public UIScene
{
public:
    UI_SCENE_CREATE_FUNC(VideoWidgetTest);

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
    
    void sliderCallback(Ref *sender, ui::SliderEventType eventType);

    void videoEventCallback(Ref* sender, experimental::ui::VideoWidgetEvent eventType);

private:
    void createVideo();
    void createSlider();

    MenuItemFont* _hintItem;
    experimental::ui::VideoWidget* _videoWidget;
    Label* _videoStateLabel;
    Rect _visibleRect;

    Layer* _rootLayer;

};

#endif // __tests__VideoWidgetTest__

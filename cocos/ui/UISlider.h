/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

typedef enum
{
    SLIDER_PERCENTCHANGED
}SliderEventType;

typedef void (Ref::*SEL_SlidPercentChangedEvent)(Ref*,SliderEventType);
#define sliderpercentchangedselector(_SELECTOR) (SEL_SlidPercentChangedEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class Slider : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    Slider();
    
    /**
     * Default destructor
     */
    virtual ~Slider();
    
    /**
     * Allocates and initializes.
     */
    static Slider* create();
    
    /**
     * Load texture for slider bar.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadBarTexture(const std::string& fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets if slider is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool able);
    
    bool isScale9Enabled();
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsets(const Rect &capInsets);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetsBarRenderer(const Rect &capInsets);
    
    const Rect& getCapInsetsBarRenderer();
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetProgressBarRebderer(const Rect &capInsets);
    
    const Rect& getCapInsetsProgressBarRebderer();
    
    /**
     * Load textures for slider ball.
     *
     * @param slider ball normal    normal state texture.
     *
     * @param slider ball selected    selected state texture.
     *
     * @param slider ball disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextures(const std::string& normal,
                              const std::string& pressed,
                              const std::string& disabled,
                              TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load normal state texture for slider ball.
     *
     * @param normal    normal state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureNormal(const std::string& normal,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load selected state texture for slider ball.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTexturePressed(const std::string& pressed,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for slider ball.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureDisabled(const std::string& disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for slider progress bar.
     *
     * @param fileName    file path of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadProgressBarTexture(const std::string& fileName, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Changes the progress direction of slider.
     *
     * @param percent    percent value from 1 to 100.
     */
    void setPercent(int percent);
    
    /**
     * Gets the progress direction of slider.
     *
     * @return percent    percent value from 1 to 100.
     */
    int getPercent();
    
    /**
     * Add call back function called when slider's percent has changed to slider.
     */
    void addEventListenerSlider(Ref* target,SEL_SlidPercentChangedEvent selector);
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override the widget's hitTest function to perfom its own
    virtual bool hitTest(const Point &pt) override;
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;
    float getPercentWithBallPos(float location);
    void percentChangedEvent();
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Node*  _barRenderer;
    Node* _progressBarRenderer;
    Size _progressBarTextureSize;
    
    Sprite* _slidBallNormalRenderer;
    Sprite* _slidBallPressedRenderer;
    Sprite* _slidBallDisabledRenderer;
    Node* _slidBallRenderer;
    
    float _barLength;
    int _percent;
    
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    std::string _textureFile;
    std::string _progressBarTextureFile;
    std::string _slidBallNormalTextureFile;
    std::string _slidBallPressedTextureFile;
    std::string _slidBallDisabledTextureFile;

    Rect _capInsetsBarRenderer;
    Rect _capInsetsProgressBarRenderer;

    Ref*       _sliderEventListener;
    SEL_SlidPercentChangedEvent    _sliderEventSelector;
    TextureResType _barTexType;
    TextureResType _progressBarTexType;
    TextureResType _ballNTexType;
    TextureResType _ballPTexType;
    TextureResType _ballDTexType;
    bool _barRendererAdaptDirty;
    bool _progressBarRendererDirty;
};

}
NS_CC_END

#endif /* defined(__CocoGUI__Slider__) */

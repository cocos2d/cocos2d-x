/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "gui/UIWidget.h"

namespace gui {

typedef enum
{
    SLIDER_PERCENTCHANGED
}SliderEventType;

typedef void (cocos2d::Object::*SEL_SlidPercentChangedEvent)(cocos2d::Object*,SliderEventType);
#define sliderpercentchangedselector(_SELECTOR) (SEL_SlidPercentChangedEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class UISlider : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UISlider();
    
    /**
     * Default destructor
     */
    virtual ~UISlider();
    
    /**
     * Allocates and initializes.
     */
    static UISlider* create();
    
    /**
     * Load texture for slider bar.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadBarTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets if slider is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool able);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsets(const cocos2d::Rect &capInsets);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetsBarRenderer(const cocos2d::Rect &capInsets);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetProgressBarRebderer(const cocos2d::Rect &capInsets);
    
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
    void loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load normal state texture for slider ball.
     *
     * @param normal    normal state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureNormal(const char* normal,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load selected state texture for slider ball.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTexturePressed(const char* pressed,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for slider ball.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadSlidBallTextureDisabled(const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for slider progress bar.
     *
     * @param fileName    file path of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadProgressBarTexture(const char* fileName, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
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
    void addEventListenerSlider(cocos2d::Object* target,SEL_SlidPercentChangedEvent selector);
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const cocos2d::Point &touchPoint) override;
    
    //override "getContentSize" method of widget.
    virtual const cocos2d::Size& getContentSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual cocos2d::Node* getVirtualRenderer() override;
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;

protected:
    virtual void initRenderer() override;
    float getPercentWithBallPos(float location);
    void percentChangedEvent();
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
protected:
    cocos2d::Node*  _barRenderer;
    cocos2d::Node* _progressBarRenderer;
    cocos2d::Size _progressBarTextureSize;
    
    cocos2d::Sprite* _slidBallNormalRenderer;
    cocos2d::Sprite* _slidBallPressedRenderer;
    cocos2d::Sprite* _slidBallDisabledRenderer;
    cocos2d::Node* _slidBallRenderer;
    
    float _barLength;
    int _percent;
    
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    std::string _textureFile;
    std::string _progressBarTextureFile;
    std::string _slidBallNormalTextureFile;
    std::string _slidBallPressedTextureFile;
    std::string _slidBallDisabledTextureFile;

    cocos2d::Rect _capInsetsBarRenderer;
    cocos2d::Rect _capInsetsProgressBarRenderer;

    cocos2d::Object*       _sliderEventListener;
    SEL_SlidPercentChangedEvent    _sliderEventSelector;
    TextureResType _barTexType;
    TextureResType _progressBarTexType;
    TextureResType _ballNTexType;
    TextureResType _ballPTexType;
    TextureResType _ballDTexType;
};

}

#endif /* defined(__CocoGUI__UISlider__) */

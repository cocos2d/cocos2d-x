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

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    SLIDER_PERCENTCHANGED
}SliderEventType;

typedef void (CCObject::*SEL_SlidPercentChangedEvent)(CCObject*,SliderEventType);
#define sliderpercentchangedselector(_SELECTOR) (SEL_SlidPercentChangedEvent)(&_SELECTOR)


/*compatible*/
typedef void (CCObject::*SEL_PercentChangedEvent)(CCObject*);
#define coco_percentchangedselector(_SELECTOR) (SEL_PercentChangedEvent)(&_SELECTOR)
/************/

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
    void setCapInsets(const CCRect &capInsets);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetsBarRenderer(const CCRect &capInsets);
    
    /**
     * Sets capinsets for slider, if slider is using scale9 renderer.
     *
     * @param capInsets    capinsets for slider
     */
    void setCapInsetProgressBarRebderer(const CCRect &capInsets);
    
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
    void addEventListenerSlider(CCObject* target,SEL_SlidPercentChangedEvent selector);
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const CCPoint &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    //override "getContentSize" method of widget.
    virtual const CCSize& getContentSize() const;
    
    //override "getVirtualRenderer" method of widget.
    virtual CCNode* getVirtualRenderer();
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    

    
    /*Compatible*/
    /**
     * These methods will be removed
     */
    void setBarTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL){loadBarTexture(fileName,texType);};
    void setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallTextures(normal, pressed, disabled,texType);};
    void setSlidBallNormalTexture(const char* normal,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallTextureNormal(normal,texType);};
    void setSlidBallPressedTexture(const char* pressed,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallTexturePressed(pressed,texType);};
    void setSlidBallDisabledTexture(const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallTextureDisabled(disabled,texType);};
    void setProgressBarTexture(const char* fileName, TextureResType texType = UI_TEX_TYPE_LOCAL){loadProgressBarTexture(fileName,texType);};
    void setSlidBallPercent(int percent){setPercent(percent);};
    void setScale9Size(const CCSize& size){setScale9Enabled(true);setSize(size);};
    void setScale9Enable(bool is){setScale9Enabled(is);};
    void addPercentChangedEvent(CCObject* target,SEL_PushEvent selector)
    {
        m_pPercentListener = target;
        m_pfnPercentSelector = selector;
    };
    /************/
protected:
    virtual void initRenderer();
    float getPercentWithBallPos(float location);
    void percentChangedEvent();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    virtual void onSizeChanged();
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
protected:
    CCNode*  m_pBarRenderer;
    CCNode* m_pProgressBarRenderer;
    CCSize m_ProgressBarTextureSize;
    
    CCSprite* m_pSlidBallNormalRenderer;
    CCSprite* m_pSlidBallPressedRenderer;
    CCSprite* m_pSlidBallDisabledRenderer;
    CCNode* m_pSlidBallRenderer;
    
    float m_fBarLength;
    int m_nPercent;
    
    bool m_bScale9Enabled;
    bool m_bPrevIgnoreSize;
    std::string m_strTextureFile;
    std::string m_strProgressBarTextureFile;
    std::string m_strSlidBallNormalTextureFile;
    std::string m_strSlidBallPressedTextureFile;
    std::string m_strSlidBallDisabledTextureFile;

    CCRect m_capInsetsBarRenderer;
    CCRect m_capInsetsProgressBarRenderer;

    CCObject*       m_pSliderEventListener;
    SEL_SlidPercentChangedEvent    m_pfnSliderEventSelector;
    TextureResType m_eBarTexType;
    TextureResType m_eProgressBarTexType;
    TextureResType m_eBallNTexType;
    TextureResType m_eBallPTexType;
    TextureResType m_eBallDTexType;
    
    /*Compatible*/
    CCObject*       m_pPercentListener;
    SEL_PushEvent    m_pfnPercentSelector;
    /************/
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISlider__) */

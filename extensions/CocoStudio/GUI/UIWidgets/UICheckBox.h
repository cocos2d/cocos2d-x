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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
}CheckBoxEventType;

typedef void (CCObject::*SEL_SelectedStateEvent)(CCObject*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (cocos2d::extension::SEL_SelectedStateEvent)(&_SELECTOR)

/*******Compatible*******/
typedef void (CCObject::*SEL_SelectEvent)(CCObject*);
typedef void (CCObject::*SEL_UnSelectEvent)(CCObject*);
#define coco_selectselector(_SELECTOR) (cocos2d::extension::SEL_SelectEvent)(&_SELECTOR)
#define coco_unselectselector(_SELECTOR) (cocos2d::extension::SEL_UnSelectEvent)(&_SELECTOR)
/************************/
/**
*   @js NA
*   @lua NA
*/
class UICheckBox : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UICheckBox();
    
    /**
     * Default destructor
     */
    virtual ~UICheckBox();
    
    /**
     * Allocates and initializes.
     */
    static UICheckBox* create();
    
    /**
     * Load textures for checkbox.
     *
     * @param backGround    backGround texture.
     *
     * @param backGroundSelected    backGround selected state texture.
     *
     * @param cross    cross texture.
     *
     * @param frontCrossDisabled    cross dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGround texture for checkbox.
     *
     * @param backGround    backGround texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGround(const char* backGround,TextureResType type = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundSelected texture for checkbox.
     *
     * @param backGroundSelected     backGround selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundSelected(const char* backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load cross texture for checkbox.
     *
     * @param cross    cross texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCross(const char* cross,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundDisabled texture for checkbox.
     *
     * @param backGroundDisabled    backGroundDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundDisabled(const char* backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load frontCrossDisabled texture for checkbox.
     *
     * @param frontCrossDisabled    frontCrossDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCrossDisabled(const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets selcted state for checkbox.
     *
     * @param selected    true that checkbox is selected, false otherwise.
     */
    void setSelectedState(bool selected);
    
    /**
     * Gets selcted state of checkbox.
     *
     * @return selected    true that checkbox is selected, false otherwise.
     */
    bool getSelectedState();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
    
    //add a call back function would called when checkbox is selected or unselected.
    void addEventListenerCheckBox(CCObject* target,SEL_SelectedStateEvent selector);
    
    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX);
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY);
    
    //override "isFlipX" method of widget.
    virtual bool isFlipX();
    
    //override "isFlipY" method of widget.
    virtual bool isFlipY();
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "getContentSize" method of widget.
    virtual const CCSize& getContentSize() const;
    
    //override "getVirtualRenderer" method of widget.
    virtual CCNode* getVirtualRenderer();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
    /*Compatible*/
    /**
     * These methods will be removed
     */
    void setTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextures(backGround, backGroundSelected, cross, backGroundDisabled,frontCrossDisabled,texType);};
    void setBackGroundTexture(const char* backGround,TextureResType type = UI_TEX_TYPE_LOCAL){loadTextureBackGround(backGround,type);};
    void setBackGroundSelectedTexture(const char* backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextureBackGroundSelected(backGroundSelected,texType);};
    void setFrontCrossTexture(const char* cross,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextureFrontCross(cross,texType);};
    void setBackGroundDisabledTexture(const char* backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextureBackGroundDisabled(backGroundDisabled,texType);};
    void setFrontCrossDisabledTexture(const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextureFrontCrossDisabled(frontCrossDisabled,texType);};
    void addSelectEvent(CCObject* target,SEL_SelectEvent selector)
    {
        m_pSelectListener = target;
        m_pfnSelectSelector = selector;
    };
    void addUnSelectEvent(CCObject* target,SEL_UnSelectEvent selector)
    {
        m_pUnSelectListener = target;
        m_pfnUnSelectSelector = selector;
    };
    /************/

protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    void selectedEvent();
    void unSelectedEvent();
    virtual void onSizeChanged();
    void backGroundTextureScaleChangedWithSize();
    void backGroundSelectedTextureScaleChangedWithSize();
    void frontCrossTextureScaleChangedWithSize();
    void backGroundDisabledTextureScaleChangedWithSize();
    void frontCrossDisabledTextureScaleChangedWithSize();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
protected:
    CCSprite* m_pBackGroundBoxRenderer;
    CCSprite* m_pBackGroundSelectedBoxRenderer;
    CCSprite* m_pFrontCrossRenderer;
    CCSprite* m_pBackGroundBoxDisabledRenderer;
    CCSprite* m_pFrontCrossDisabledRenderer;
    bool m_bIsSelected;

    CCObject*       m_pCheckBoxEventListener;
    SEL_SelectedStateEvent    m_pfnCheckBoxEventSelector;
    
    TextureResType m_eBackGroundTexType;
    TextureResType m_eBackGroundSelectedTexType;
    TextureResType m_eFrontCrossTexType;
    TextureResType m_eBackGroundDisabledTexType;
    TextureResType m_eFrontCrossDisabledTexType;
    
    std::string m_strBackGroundFileName;
    std::string m_strBackGroundSelectedFileName;
    std::string m_strFrontCrossFileName;
    std::string m_strBackGroundDisabledFileName;
    std::string m_strFrontCrossDisabledFileName;
    
    /*Compatible*/
    CCObject*       m_pSelectListener;
    SEL_SelectEvent    m_pfnSelectSelector;
    CCObject*       m_pUnSelectListener;
    SEL_UnSelectEvent    m_pfnUnSelectSelector;
    /************/
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UICheckBox__) */

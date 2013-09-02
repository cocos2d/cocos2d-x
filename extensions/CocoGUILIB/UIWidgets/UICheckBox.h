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

typedef void (CCObject::*SEL_SelectEvent)(CCObject*);
typedef void (CCObject::*SEL_UnSelectEvent)(CCObject*);
#define coco_selectselector(_SELECTOR) (cocos2d::extension::SEL_SelectEvent)(&_SELECTOR)
#define coco_unselectselector(_SELECTOR) (cocos2d::extension::SEL_UnSelectEvent)(&_SELECTOR)
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
    void loadBackGroundTexture(const char* backGround,TextureResType type = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundSelected texture for checkbox.
     *
     * @param backGroundSelected     backGround selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadBackGroundSelectedTexture(const char* backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load cross texture for checkbox.
     *
     * @param cross    cross texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadFrontCrossTexture(const char* cross,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load backGroundDisabled texture for checkbox.
     *
     * @param backGroundDisabled    backGroundDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadBackGroundDisabledTexture(const char* backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load frontCrossDisabled texture for checkbox.
     *
     * @param frontCrossDisabled    frontCrossDisabled texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadFrontCrossDisabledTexture(const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
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
    
    //add a call back function would called when checkbox is selected.
    virtual void addSelectEvent(CCObject* target,SEL_SelectEvent selector);
    
    //add a call back function would called when checkbox is unselected.
    virtual void addUnSelectEvent(CCObject* target,SEL_UnSelectEvent selector);
    
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
    
    /*Compatible*/
    CC_DEPRECATED_ATTRIBUTE void setTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTextures(backGround, backGroundSelected, cross, backGroundDisabled,frontCrossDisabled,texType);};
    CC_DEPRECATED_ATTRIBUTE void setBackGroundTexture(const char* backGround,TextureResType type = UI_TEX_TYPE_LOCAL){loadBackGroundTexture(backGround,type);};
    CC_DEPRECATED_ATTRIBUTE void setBackGroundSelectedTexture(const char* backGroundSelected,TextureResType texType = UI_TEX_TYPE_LOCAL){loadBackGroundSelectedTexture(backGroundSelected,texType);};
    CC_DEPRECATED_ATTRIBUTE void setFrontCrossTexture(const char* cross,TextureResType texType = UI_TEX_TYPE_LOCAL){loadFrontCrossTexture(cross,texType);};
    CC_DEPRECATED_ATTRIBUTE void setBackGroundDisabledTexture(const char* backGroundDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadBackGroundDisabledTexture(backGroundDisabled,texType);};
    CC_DEPRECATED_ATTRIBUTE void setFrontCrossDisabledTexture(const char* frontCrossDisabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadFrontCrossDisabledTexture(frontCrossDisabled,texType);};
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
protected:
    CCSprite* m_pBackGroundBoxRenderer;
    CCSprite* m_pBackGroundSelectedBoxRenderer;
    CCSprite* m_pFrontCrossRenderer;
    CCSprite* m_pBackGroundBoxDisabledRenderer;
    CCSprite* m_pFrontCrossDisabledRenderer;
    bool m_bIsSelected;
    CCObject*       m_pSelectListener;
    SEL_SelectEvent    m_pfnSelectSelector;
    CCObject*       m_pUnSelectListener;
    SEL_UnSelectEvent    m_pfnUnSelectSelector;
    TextureResType m_eBackGroundTexType;
    TextureResType m_eBackGroundSelectedTexType;
    TextureResType m_eFrontCrossTexType;
    TextureResType m_eBackGroundDisabledTexType;
    TextureResType m_eFrontCrossDisabledTexType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UICheckBox__) */

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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../Drawable/GUINodeRGBA.h"

NS_CC_EXT_BEGIN

typedef enum
{
    WidgetEventTouchDown           = 1 << 0,
    WidgetEventTouchDragInside     = 1 << 1,
    WidgetEventTouchDragOutside    = 1 << 2,
    WidgetEventTouchDragEnter      = 1 << 3,
    WidgetEventTouchDragExit       = 1 << 4,
    WidgetEventTouchUpInside       = 1 << 5,
    WidgetEventTouchUpOutside      = 1 << 6,
    WidgetEventTouchCancel         = 1 << 7,
    WidgetEventDrop                = 1 << 8
}WidgetEvent;

typedef enum
{
    WidgetStateNone = -1,
    WidgetStateNormal,
    WidgetStateSelected,
    WidgetStateDisabled
}WidgetState;

typedef enum
{
    WidgetTypeWidget,
    WidgetTypeContainer
}WidgetType;

typedef enum
{
    WIDGET_WIDGET,
    WIDGET_ROOTWIDGET,
    WIDGET_CONTAINERWIDGET,
    WIDGET_BUTTON,
    WIDGET_CHECKBOX,
    WIDGET_CONTROLBUTTON,
    WIDGET_GRADIENTPANEL,
    WIDGET_IMAGEVIEW,
    WIDGET_LABEL,
    WIDGET_LABELATLAS,
    WIDGET_LABELBMFONT,
    WIDGET_LISTVIEW,
    WIDGET_LOADINGBAR,
    WIDGET_NODECONTAINER,
    WIDGET_PANEL,
    WIDGET_SCROLLVIEW,
    WIDGET_SLIDER,
    WIDGET_TEXTAREA,
    WIDGET_TEXTBUTTON,
    WIDGET_TEXTFIELD,
    WIDGET_PAGEVIEW
}WidgetName;

typedef void (cocos2d::CCObject::*SEL_PushEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_MoveEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_ReleaseEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_CancelEvent)(cocos2d::CCObject*);
#define coco_pushselector(_SELECTOR) (cocos2d::extension::SEL_PushEvent)(&_SELECTOR)
#define coco_moveselector(_SELECTOR) (cocos2d::extension::SEL_MoveEvent)(&_SELECTOR)
#define coco_releaseselector(_SELECTOR) (cocos2d::extension::SEL_ReleaseEvent)(&_SELECTOR)
#define coco_cancelselector(_SELECTOR) (cocos2d::extension::SEL_CancelEvent)(&_SELECTOR)

class UILayer;

class UIWidget : public cocos2d::CCObject
{
public:
    UIWidget();
    virtual ~UIWidget();
    virtual void releaseResoures();
    static UIWidget* create();
    void initPressState(WidgetState state);
    void setPressState(WidgetState state);
    virtual bool addChild(UIWidget* child);
    virtual bool removeChild(UIWidget* child,bool cleanup);
    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    virtual void setWidgetZOrder(int z);
    virtual int getWidgetZOrder();
    virtual void reorderChild(UIWidget* child);
    void setBeTouchEnable(bool enable);
    bool getBeTouchEnable();
    void setUpdateEnable(bool enable);
    bool getUpdateEnable();
    bool isFocus();
    void setFocus(bool fucos);
    virtual void disable();
    virtual void active();
    virtual bool isActive();
    void updateBeTouchEnable(bool enable);
    void setVisible(bool visible);
    bool isVisible();
    virtual cocos2d::CCRect getRect();
    virtual cocos2d::CCRect getRelativeRect();
    virtual const CCSize& getContentSize(); 
    void getLocationInWindow();
    virtual float getRelativeLeftPos();
    virtual float getRelativeBottomPos();
    virtual float getRelativeRightPos();
    virtual float getRelativeTopPos();
    virtual cocos2d::CCNode* getValidNode();
    cocos2d::CCNode* getContainerNode();
    UIWidget* getWidgetParent();
    UIWidget* getChildByName(const char* name);
    UIWidget* getChildByTag(int tag);
    CCArray* getChildren();
    virtual void addPushDownEvent(cocos2d::CCObject* target,SEL_PushEvent selector);
    virtual void addMoveEvent(cocos2d::CCObject* target,SEL_MoveEvent selector);
    virtual void addReleaseEvent(cocos2d::CCObject* target,SEL_ReleaseEvent selector);
    virtual void addCancelEvent(cocos2d::CCObject* target,SEL_CancelEvent selector);
    //cocos2d property
    void setPosition(const cocos2d::CCPoint &pos);
    virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
    void updateAnchorPoint();
    cocos2d::CCPoint getPosition();
    cocos2d::CCPoint getAnchorPoint();
    virtual void setScale(float scale);
    float getScale();
    virtual void setScaleX(float scaleX);
    float getScaleX();
    virtual void setScaleY(float scaleY);
    float getScaleY();
    virtual void onScaleDirtyChanged();
    virtual void onScaleXDirtyChanged();
    virtual void onScaleYDirtyChanged();
    void setRotation(float rotation);
    float getRotation();
    void setRotationX(float rotationX);
    float getRotationX();
    void setRotationY(float rotationY);
    float getRotationY();
    virtual void setSkewX(float skewX);
    virtual float getSkewX();
    virtual void setSkewY(float skewY);
    virtual float getSkewY();
    virtual void setFlipX(bool flipX){};
    virtual bool isFlipX(){return false;};
    virtual void setFlipY(bool flipY){};
    virtual bool isFlipY(){return false;};
    virtual void setColor(const cocos2d::ccColor3B &color);
    virtual const cocos2d::ccColor3B& getColor();
    virtual void setOpacity(int opacity);
    virtual int getOpacity();
    void setBlendFunc(cocos2d::ccBlendFunc blendFunc);
    void ignoreAnchorPointForPosition(bool ignore);
    //cocos action
    virtual void setActionManager(cocos2d::CCActionManager* actionManager);
    virtual cocos2d::CCActionManager* getActionManager();
    cocos2d::CCAction* runAction(cocos2d::CCAction* action);
    void stopAllActions(void);
    void stopAction(cocos2d::CCAction* action);
    void stopActionByTag(int tag);
    cocos2d::CCAction* getActionByTag(int tag);
    
	void setActionTag(int tag);
	int getActionTag();
    
    virtual void setNeedCheckVisibleDepandParent(bool need);
    void didNotSelectSelf();
    virtual void onTouchBegan(cocos2d::CCPoint &touchPoint);
    virtual void onTouchMoved(cocos2d::CCPoint &touchPoint);
    virtual void onTouchEnded(cocos2d::CCPoint &touchPoint);
    virtual void onTouchCancelled(cocos2d::CCPoint &touchPoint);
    virtual void onTouchLongClicked(cocos2d::CCPoint &touchPoint);
    virtual bool isClippingEnable(){return false;};
    virtual void update(float dt){};
    virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
    bool checkVisibleDependParent(cocos2d::CCPoint &pt);
    bool checkBeVisibleInParent();
    virtual void checkChildInfo(int handleState,UIWidget* sender,cocos2d::CCPoint &touchPoint);
    //widget prop
    virtual float getAbsoluteScaleX();
    virtual float getAbsoluteScaleY();
    virtual bool getAbsoluteVisible();
    virtual void updateChildrenVisibleDirty(bool dirty);
    virtual void updateChildrenOpacityDirty(bool dirty);
    virtual void adaptSize(float xProportion,float yProportion);
    void setCreateFromFile(bool is);
    void setFileDesignSize(const CCSize &size);
    CCSize getFileDesignSize();
    void setUILayer(UILayer* uiLayer);
    void updateChildrenUILayer(UILayer* uiLayer);
    void structureChangedEvent();
    void disableUpdate();
    CCPoint getTouchStartPos();
    CCPoint getTouchMovePos();
    CCPoint getTouchEndPos();
    void setWidgetTag(int tag);
    int getWidgetTag();
    void setName(const char* name);
    const char* getName();
    void setUseMergedTexture(bool useMergedTexture);
    bool getUseMergedTexture();
    WidgetType getWidgetType();
    WidgetName getWidgetName();
protected:
    virtual bool init();
    virtual void initNodes();
    virtual void removeChildMoveToTrash(UIWidget* child);
    virtual void removeChildReferenceOnly(UIWidget* child);
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    void pushDownEvent();
    void moveEvent();
    void releaseUpEvent();
    void cancelUpEvent();
    void longClickEvent();
    virtual bool hitTest(cocos2d::CCNode* node, cocos2d::CCPoint &pt);
protected:
    bool m_bEnabled;
    bool m_bVisible;
    bool m_bActived;
    bool m_bFocus;
    bool m_bBeTouchEnabled;
    int m_nWidgetZOrder;
    cocos2d::CCPoint m_anchorPoint;
    UIWidget* m_pWidgetParent;
    WidgetState m_nCurPressState;
    WidgetState m_nPrevPressstate;
    bool m_bUpdateEnable;
    cocos2d::CCNode* m_pRender;
    float m_fContentSizeWidth;
    float m_fContentSizeHeight;
    bool m_bIsCreatedFromFile;
    CCSize m_fileDesignSize;
    cocos2d::CCPoint m_locationInWindow;
    cocos2d::CCSize m_contentSize;
    cocos2d::CCRect m_rect;
    cocos2d::CCRect m_relativeRect;
    bool m_bNeedCheckVisibleDependParent;
    bool m_bVisibleTouch;
    CCArray* m_children;
    CCPoint m_touchStartPos;
    CCPoint m_touchMovePos;
    CCPoint m_touchEndPos;
    cocos2d::CCObject*       m_pPushListener;
    SEL_PushEvent    m_pfnPushSelector;
    cocos2d::CCObject*       m_pMoveListener;
    SEL_MoveEvent    m_pfnMoveSelector;
    cocos2d::CCObject*       m_pReleaseListener;
    SEL_ReleaseEvent    m_pfnReleaseSelector;
    cocos2d::CCObject*       m_pCancelListener;
    SEL_ReleaseEvent    m_pfnCancelSelector;
    float m_fAbsoluteScaleX;
    float m_fAbsoluteScaleY;
    bool m_bAbsoluteVisible;
    bool m_bScaleXDirty;
    bool m_bScaleYDirty;
    bool m_bVisibleDirty;
    bool m_bOpacityDirty;
    float m_fAdaptScaleX;
    float m_fAdaptScaleY;
    int m_nWidgetTag;
    std::string m_strName;
    bool m_bUseMergedTexture;
    WidgetType m_WidgetType;
    WidgetName m_WidgetName;
    UILayer* m_pUILayer;
	int m_nActionTag;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIWidget__) */

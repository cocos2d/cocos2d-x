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

#ifndef __UIIMAGEVIEW_H__
#define __UIIMAGEVIEW_H__

#include "gui/UIWidget.h"

namespace gui {

/**
*   @js NA
*   @lua NA
*/
class UIImageView : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UIImageView();
    
    /**
     * Default destructor
     */
    virtual ~UIImageView();
    
    /**
     * Allocates and initializes.
     */
    static UIImageView* create();
    
    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Updates the texture rect of the UIImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     */
    void setTextureRect(const cocos2d::Rect& rect);
    
    /**
     * Sets if imageview is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool able);
    
    /**
     * Sets capinsets for imageview, if imageview is using scale9 renderer.
     *
     * @param capInsets    capinsets for imageview
     */
    void setCapInsets(const cocos2d::Rect &capInsets);
    
    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX) override;
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY) override;
    
    //override "isFlipX" method of widget.
    virtual bool isFlipX() override;
    
    //override "isFlipY" method of widget.
    virtual bool isFlipY() override;
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const cocos2d::Point &pt) override;
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const cocos2d::Point &touchPoint) override;
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const cocos2d::Point &touchPoint) override;
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;
    
    void setDoubleClickEnabled(bool able);
    void doubleClickEvent();
    void checkDoubleClick(float dt);
    virtual const cocos2d::Size& getContentSize() const override;
    virtual cocos2d::Node* getVirtualRenderer() override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    void imageTextureScaleChangedWithSize();
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
protected:
    int _clickCount;
    float _clickTimeInterval;
    bool _startCheckDoubleClick;
    bool _touchRelease;
    bool _doubleClickEnabled;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    cocos2d::Rect _capInsets;
    cocos2d::Node* _imageRenderer;
    std::string _textureFile;
    TextureResType _imageTexType;
    cocos2d::Size _imageTextureSize;
};

}

#endif /* defined(__CocoGUI__UIImageView__) */

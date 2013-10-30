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

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN
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
    void setTextureRect(const CCRect& rect);
    
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
    void setCapInsets(const CCRect &capInsets);
    
    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX);
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY);
    
    //override "isFlipX" method of widget.
    virtual bool isFlipX();
    
    //override "isFlipY" method of widget.
    virtual bool isFlipY();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
    void setDoubleClickEnabled(bool able);
    void doubleClickEvent();
    void checkDoubleClick(float dt);
    /*Compatible*/
    /**
     * These methods will be removed
     */
    void setTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTexture(fileName,texType);};
    void setScale9Size(const CCSize& size){setScale9Enabled(true);setSize(size);};
    void setScale9Enable(bool is){setScale9Enabled(is);};
    /************/
    virtual const CCSize& getContentSize() const;
    virtual CCNode* getVirtualRenderer();
protected:
    virtual void initRenderer();
    virtual void onSizeChanged();
    void imageTextureScaleChangedWithSize();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
protected:
    int m_nClickCount;
    float m_fClickTimeInterval;
    bool m_bStartCheckDoubleClick;
    bool m_touchRelease;
    bool m_bDoubleClickEnabled;
    bool m_bScale9Enabled;
    bool m_bPrevIgnoreSize;
    CCRect m_capInsets;
    CCNode* m_pImageRenderer;
    std::string m_strTextureFile;
    TextureResType m_eImageTexType;
    CCSize m_imageTextureSize;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIImageView__) */

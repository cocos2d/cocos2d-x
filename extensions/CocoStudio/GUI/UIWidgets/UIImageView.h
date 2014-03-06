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

NS_CC_BEGIN

namespace ui {

/**
*   @js NA
*   @lua NA
*/
class ImageView : public Widget
{
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    ImageView();
    
    /**
     * Default destructor
     */
    virtual ~ImageView();
    
    /**
     * Allocates and initializes.
     */
    static ImageView* create();
    
    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Updates the texture rect of the ImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     */
    void setTextureRect(const CCRect& rect);
    
    /**
     * Sets if imageview is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool able);
    
    bool isScale9Enabled();
    
    /**
     * Sets capinsets for imageview, if imageview is using scale9 renderer.
     *
     * @param capInsets    capinsets for imageview
     */
    void setCapInsets(const CCRect &capInsets);
    
    const CCRect& getCapInsets();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;
    
    virtual const CCSize& getContentSize() const;
    virtual CCNode* getVirtualRenderer();
protected:
    virtual void initRenderer();
    virtual void onSizeChanged();
    virtual void updateTextureColor();
    virtual void updateTextureOpacity();
    virtual void updateTextureRGBA();
    virtual void updateFlippedX();
    virtual void updateFlippedY();
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
protected:
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    CCRect _capInsets;
    CCNode* _imageRenderer;
    std::string _textureFile;
    TextureResType _imageTexType;
    CCSize _imageTextureSize;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__ImageView__) */

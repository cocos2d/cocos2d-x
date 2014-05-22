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

#ifndef __UIIMAGEVIEW_H__
#define __UIIMAGEVIEW_H__

#include "ui/UIWidget.h"

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
     * create a  imageview 
     *
     * @param imageFileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    static ImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);

    /**
     * Updates the texture rect of the ImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     */
    void setTextureRect(const Rect& rect);

    /**
     * Sets if imageview is using scale9 renderer.
     *
     * @param able true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool able);

    bool isScale9Enabled();

    /**
     * Sets capinsets for imageview, if imageview is using scale9 renderer.
     *
     * @param capInsets    capinsets for imageview
     */
    void setCapInsets(const Rect &capInsets);

    const Rect& getCapInsets();

    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;

    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;

    virtual const Size& getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool init(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    Node* _imageRenderer;
    std::string _textureFile;
    TextureResType _imageTexType;
    Size _imageTextureSize;
    bool _imageRendererAdaptDirty;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__ImageView__) */

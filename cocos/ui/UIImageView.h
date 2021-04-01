/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

struct CC_DLL ResourceData;

namespace ui {
    class Scale9Sprite;
/**
 * @brief A widget to display images.
 */
class CC_GUI_DLL ImageView : public Widget , public cocos2d::BlendProtocol
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ImageView();

    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~ImageView();

    /**
     * Create a empty ImageView.
     */
    static ImageView* create();
    
    /**
     * Create a  imageview  with a image name.
     *
     * @param imageFileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     * @return A ImageView instance.
     */
    static ImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);

    /**
     * Updates the texture rect of the ImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     */
    void setTextureRect(const Rect& rect);

    /**
     * Enable scale9 renderer.
     *
     * @param enabled Set to true will use scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool enabled);

    /**
     * Query whether button is using scale9 renderer or not.
     *@return whether button use scale9 renderer or not.
     */
    bool isScale9Enabled()const;

    /**
     * Sets capInsets for imageview.
     * The capInsets affects the ImageView's renderer only if `setScale9Enabled(true)` is called.
     *
     * @param capInsets    capinsets for imageview
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * Get ImageView's capInsets size.
     * @return Query capInsets size in Rect
     * @see `setCapInsets(const Rect&)`
     */
    const Rect& getCapInsets()const;
    
    /**
     * Sets the source blending function.
     *
     * @param blendFunc A structure with source and destination factor to specify pixel arithmetic. e.g. {BlendFactor::ONE, BlendFactor::ONE}, {BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    
    /**
     * Returns the blending function that is currently being used.
     *
     * @return A BlendFunc structure with source and destination factor which specified pixel arithmetic.
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc &getBlendFunc() const override;

    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;

    ResourceData getRenderFile();

CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool init(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    
    virtual void adaptRenderers() override;
    void loadTexture(SpriteFrame* spriteframe);
    void setupTexture();
    
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    Scale9Sprite* _imageRenderer;
    TextureResType _imageTexType;
    Size _imageTextureSize;
    bool _imageRendererAdaptDirty;
    std::string _textureFile;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__ImageView__) */

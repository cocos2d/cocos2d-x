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
     * 默认构造函数
     */
    ImageView();

    /**
     * 默认析构函数
     */
    virtual ~ImageView();

    /**
     * 创建和初始化
     */
    static ImageView* create();
    
    /**
     * 创建imageview 
     *
     * @param fileName   纹理（texture）文件名称
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    static ImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * 为imageview载入纹理
     *
     * @param fileName   纹理（texture）文件名称
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);

    /**
     * 更新ImageView的纹理矩形（texture rect）的大小
     * 它将调用setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)
	 * 参数为： rotated = NO, utrimmedSize = rect.size.
	 * 
	 * 译者注：只有在没有使用scale9渲染器（renderer）时，才会调用。
     */
    void setTextureRect(const Rect& rect);

    /**
     * 设置imageview是否使用scale9渲染器（renderer）
     *
     * @param able true则使用scale9渲染器（renderer）, false则不使用
     */
    void setScale9Enabled(bool able);

    bool isScale9Enabled();

    /**
     * 如果imageview使用scale9渲染器（renderer）则设置imageview的capinsets
     *
     * @param capInsets    imageview的capinsets
     */
    void setCapInsets(const Rect &capInsets);

    const Rect& getCapInsets();

    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;

    /**
     * 返回控件（widget）的类名（class name）
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

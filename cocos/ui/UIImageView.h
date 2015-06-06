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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {
    class Scale9Sprite;
/**
 * @brief @~english A widget to display images.
 * @~chinese 涓?涓皬閮ㄤ欢鏄剧ず鍥惧儚銆?
 */
class CC_GUI_DLL ImageView : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @~english
     * Default constructor
     * @~chinese 
     * 构造函数
     *
     * @js ctor
     * @lua new
     */
    ImageView();

    /**@~english
     * Default destructor
     * @~chinese 
     * 析构函数
     *
     * @js NA
     * @lua NA
     */
    virtual ~ImageView();

    /**
     * @~english
     * Create a empty ImageView.
     * @~chinese 
     * 创建一个空的ImageView对象
     */
    static ImageView* create();
    
    /**
     * @~english
     * Create a  imageview  with a image name.
     *
     * @~chinese 
     * 用一个文件名创建一个ImageView对象
     * 
     * @param imageFileName @~english file name of texture.
     * @~chinese 纹理文件的名字
     *
     * @param texType @see `Widget::TextureResType`
     *
     * @return @~english A ImageView instance.
     * @~chinese ImageView实例
     */
    static ImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * @~english
     * Load texture for imageview.
     *
     * @~chinese 
     * 加载纹理
     * 
     * @param fileName @~english file name of texture.
     * @~chinese 纹理文件的名字
     * @param texType @see `Widget::TextureResType`
     */
    void loadTexture(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);

    /**
     * @~english
     * Updates the texture rect of the ImageView in points.
     * It will call setTextureRect:rotated:untrimmedSize with rotated = NO, and utrimmedSize = rect.size.
     * @~chinese
     * 更新ImageView纹理矩形内的点数据
     * 它会调用setTextureRect:rotated:untrimmedSize，rotated默认为No，utrimmedSize默认为矩形的尺寸
     */
    void setTextureRect(const Rect& rect);

    /**
     * @~english
     * Enable scale9 renderer.
     *
     * @~chinese 
     * 开启9宫格渲染模式
     * 
     * @param enabled @~english Set to true will use scale9 renderer, false otherwise.
     * @~chinese 设置为true则开启9宫格渲染，为false则关闭
     */
    void setScale9Enabled(bool enabled);

    /**
     * @~english
     * Query whether button is using scale9 renderer or not.
     * @~chinese 
     * 判断是否开启了9宫格渲染
     * @return @~english whether button use scale9 renderer or not.
     * @~chinese 返回true或false表示是否开启
     */
    bool isScale9Enabled()const;

    /**
     * @~english
     * Sets capInsets for imageview.
     * The capInsets affects the ImageView's renderer only if `setScale9Enabled(true)` is called.
     *
     * @~chinese 
     * 设置ImageView的capInsets
     * 只有当`setScale9Enabled(true)`被调用之后，该capInsets才会影响的ImageView的渲染。
     * 
     * @param capInsets @~english capInsets for imageview
     * @~chinese 这个ImageView的capInset
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * @~english
     * Get ImageView's capInsets size.
     * @~chinese 
     * 获取一个ImageView的capInsets尺寸
     *
     * @return @~english Query capInsets size in Rect
     * @~chinese capInsets尺寸
     * @see `setCapInsets(const Rect&)`
     */
    const Rect& getCapInsets()const;

    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool init(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    
    virtual void adaptRenderers() override;
    
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    Scale9Sprite* _imageRenderer;
    std::string _textureFile;
    TextureResType _imageTexType;
    Size _imageTextureSize;
    bool _imageRendererAdaptDirty;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__ImageView__) */

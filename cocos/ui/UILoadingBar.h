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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

/**
*   @js NA
*   @lua NA
*/
class LoadingBar : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Direction
    {
        LEFT,
        RIGHT
    };
    /**
     * 默认构造函数
     */
    LoadingBar();
    
    /**
     * 默认析构函数
     */
    virtual ~LoadingBar();
    
    /**
     * 创建和初始化对象
     */
    static LoadingBar* create();
    
    /**
     * 根据纹理文件（texture）和进度百分比（percentage）创建一个进度条（LoadingBar）
     **/
    static LoadingBar* create(const std::string& textureName, float percentage = 0);
    
    /**
     * 修改进度条的前进方向
     *
     * @see Direction  LEFT从左至右前进，RIGHT从右至左前进。
     *
     * @param direction 方向
     */
    void setDirection(Direction direction);
    
    /**
     * 获得进度条（loadingbar）的前进方向
     *
     * @see Direction  LEFT从左至右前进，RIGHT从右至左前进。
     *
     * @return 方向
     */
    Direction getDirection()const;
    
    /**
     * 为进度条加载纹理文件（texture）
     *
     * @param texture   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const std::string& texture,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * 修改进度条（loadingbar）的进度
     *
     * @param percent    百分比值（percent）范围为1到100
     */
    void setPercent(float percent);
    
    /**
     * 获得进度条（loadingbar）的进度
     *
     * @return 百分比值（percent）范围为1到100
     */
    float getPercent() const;
    
    /**
     * 设置进度条（loadingbar）是否使用scale9渲染（renderer）
     *
     * @param enabled true则使用scale9渲染器（renderer）, false则不使用
     */
    void setScale9Enabled(bool enabled);
    
    bool isScale9Enabled();
    
    /**
     * 如果进度条（loadingbar）使用scale9渲染器（renderer）则设置进度条（loadingbar）的capinsets
     *
     * @param capInsets    进度条（loadingbar）的capinsets
     */
    void setCapInsets(const Rect &capInsets);
    
    const Rect& getCapInsets();
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * 返回控件（widget）的类名（class name）
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void setScale9Scale();
    void barRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Direction _direction;
    float _percent;
    float _totalLength;
    Node* _barRenderer;
    TextureResType _renderBarTexType;
    Size _barRendererTextureSize;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    std::string _textureFile;
    bool _barRendererAdaptDirty;
};

}
NS_CC_END
#endif /* defined(__CocoGUI__LoadingBar__) */

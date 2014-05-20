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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

CC_DEPRECATED_ATTRIBUTE typedef enum
{
    CHECKBOX_STATE_EVENT_SELECTED,
    CHECKBOX_STATE_EVENT_UNSELECTED
}CheckBoxEventType;

CC_DEPRECATED_ATTRIBUTE typedef void (Ref::*SEL_SelectedStateEvent)(Ref*,CheckBoxEventType);
#define checkboxselectedeventselector(_SELECTOR) (SEL_SelectedStateEvent)(&_SELECTOR)

/**
*   @js NA
*   @lua NA
*/
class CheckBox : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };
    
    typedef std::function<void(Ref*,CheckBox::EventType)> ccCheckBoxCallback;
    
    /**
     * 默认构造函数（constructor）
     */
    CheckBox();

    /**
     * 默认析构函数（destructor）
     */
    virtual ~CheckBox();

    /**
     * 分配（allocates）并初始化（initializes）.
     */
    static CheckBox* create();
    
    /**
     * 创建一个checkbox
     *
     * @param backGround    背景纹理（texture）.
     *
     * @param backGroundSelected    选择状态的背景纹理（texture）.
     *
     * @param cross    交叉纹理贴图（cross texture）.
     *
     * @param frontCrossDisabled    暗态交叉纹理贴图（cross dark state texture）（暗态（dark state）即为禁用状态（Disabled）  译者注）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    static CheckBox* create(const std::string& backGround,
                            const std::string& backGroundSeleted,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载checkbox的纹理贴图.
     *
     * @param backGround    背景纹理（texture）.
     *
     * @param backGroundSelected    选择状态的背景纹理（texture）.
     *
     * @param cross    交叉纹理贴图（cross texture）.
     *
     * @param frontCrossDisabled    暗态交叉纹理贴图（cross dark state texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const std::string& backGround,
                      const std::string& backGroundSelected,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载checkbox的背景纹理贴图.
     *
     * @param backGround    背景纹理（texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGround(const std::string& backGround,TextureResType type = TextureResType::LOCAL);

    /**
     * 加载checkbox选择状态的背景纹理贴图（backGroundSelected）.
     *
     * @param backGroundSelected     选择状态的背景纹理（texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundSelected(const std::string& backGroundSelected,TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载checkbox的交叉纹理贴图（cross texture）.
     *
     * @param cross    交叉纹理贴图（cross texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCross(const std::string&,TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载checkbox禁用状态的背景纹理贴图（backGroundDisabled）.
     *
     * @param backGroundDisabled    禁用状态的背景纹理贴图（texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureBackGroundDisabled(const std::string& backGroundDisabled,TextureResType texType = TextureResType::LOCAL);

    /**
     * 加载checkbox禁用状态的交叉纹理贴图（frontCrossDisabled）.
     *
     * @param frontCrossDisabled    禁用状态的交叉纹理贴图（texture）.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureFrontCrossDisabled(const std::string& frontCrossDisabled,TextureResType texType = TextureResType::LOCAL);

    /**
     * 设置checkbox的选中状态.
     *
     * @param selected    值为true 时 checkbox 为选中状态, 为false 则不会.
     */
    void setSelectedState(bool selected);

    /**
     * 获取checkbox的选中状态.
     *
     * @return selected    值为true 时 checkbox 为选中状态, 为false 则不会.
     */
    bool getSelectedState();

    //增加一个回调函数，当checkbox被选中或被反选时该函数将被调用
    CC_DEPRECATED_ATTRIBUTE void addEventListenerCheckBox(Ref* target,SEL_SelectedStateEvent selector);
    void addEventListener(const ccCheckBoxCallback& callback);

    //重写（override）widget 的 "onTouchEnded" 方法.
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);

    //重写（override）widget 的 "getVirtualRendererSize" 方法.
    virtual const Size& getVirtualRendererSize() const override;

    //重写（override）widget 的 "getVirtualRenderer" 方法.
    virtual Node* getVirtualRenderer() override;

    /**
     * 返回 widget的"类名（class name）".
     */
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& backGround,
                      const std::string& backGroundSeleted,
                      const std::string& cross,
                      const std::string& backGroundDisabled,
                      const std::string& frontCrossDisabled,
                      TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    void selectedEvent();
    void unSelectedEvent();
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    virtual void updateFlippedX() override;
    virtual void updateFlippedY() override;
    void backGroundTextureScaleChangedWithSize();
    void backGroundSelectedTextureScaleChangedWithSize();
    void frontCrossTextureScaleChangedWithSize();
    void backGroundDisabledTextureScaleChangedWithSize();
    void frontCrossDisabledTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Sprite* _backGroundBoxRenderer;
    Sprite* _backGroundSelectedBoxRenderer;
    Sprite* _frontCrossRenderer;
    Sprite* _backGroundBoxDisabledRenderer;
    Sprite* _frontCrossDisabledRenderer;
    bool _isSelected;
    //如果你使用了旧的事件回调（event callback）, 它将retain  _checkBoxEventListener
    Ref*       _checkBoxEventListener;
    
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005或更高版本
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_SelectedStateEvent    _checkBoxEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005或更高版本
#pragma warning (pop)
#endif
    
    ccCheckBoxCallback _checkBoxEventCallback;

    TextureResType _backGroundTexType;
    TextureResType _backGroundSelectedTexType;
    TextureResType _frontCrossTexType;
    TextureResType _backGroundDisabledTexType;
    TextureResType _frontCrossDisabledTexType;

    std::string _backGroundFileName;
    std::string _backGroundSelectedFileName;
    std::string _frontCrossFileName;
    std::string _backGroundDisabledFileName;
    std::string _frontCrossDisabledFileName;
    
    bool _backGroundBoxRendererAdaptDirty;
    bool _backGroundSelectedBoxRendererAdaptDirty;
    bool _frontCrossRendererAdaptDirty;
    bool _backGroundBoxDisabledRendererAdaptDirty;
    bool _frontCrossDisabledRendererAdaptDirty;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__CheckBox__) */

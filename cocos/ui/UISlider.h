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

#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */

class Sprite;

namespace ui {
    class Scale9Sprite;
    
typedef enum
{
    SLIDER_PERCENTCHANGED
}SliderEventType;

typedef void (Ref::*SEL_SlidPercentChangedEvent)(Ref*,SliderEventType);
#define sliderpercentchangedselector(_SELECTOR) (SEL_SlidPercentChangedEvent)(&_SELECTOR)

/** 
 * @class Silider
 * @brief UI Slider widget.
 * @~chinese 滑动条控件
 */
class CC_GUI_DLL Slider : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @enum EventType
     * @brief @~english Slider event type.
     * @~chinese 滑动条事件类型
     */
    enum class EventType
    {
        ON_PERCENTAGE_CHANGED,
        //@since v3.7
        ON_SLIDEBALL_DOWN,
        ON_SLIDEBALL_UP,
        ON_SLIDEBALL_CANCEL
    };
    typedef std::function<void(Ref*,EventType)> ccSliderCallback;
    /**
     * @~english Default constructor.
     * @~chinese 默认构造函数
     * @js ctor
     * @lua new
     */
    Slider();
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~Slider();
    
    /** 
     * @~english Create a slider widget.
     * @~chinese 创建一个滑动条
     * @return @~english An autoreleased Slider object.
     * @~chinese 被创建的滑动条
     */
    static Slider* create();
    
    /** 
     * @~english Create a slider widget with bar texture, ball texture and texture resource type.
     * @~chinese 通过指定的滑动条纹理，滑动条指针纹理以及纹理类型来创建滑动条
     * @param barTextureName @~english Bar texture file name.
     * @~chinese 滑动条纹理
     * @param normalBallTextureName @~english Ball texture file name.
     * @~chinese 滑动条指针纹理
     * @param resType @~english Texture resource type.
     * @~chinese 纹理类型
     * @return @~english An autoreleased Slider object.
     * @~chinese 被创建的滑动条
     */
    static Slider* create(const std::string& barTextureName,
                          const std::string& normalBallTextureName,
                          TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Load texture for slider bar.
     * @~chinese 读取滑动条的纹理
     * @param fileName   @~english File name of texture.
     * @~chinese 滑动条纹理的路径
     * @param resType    @~english  The reousrce type @see TextureResType .
     * @~chinese 滑动条资源类型
     */
    void loadBarTexture(const std::string& fileName,TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Sets if slider is using scale9 renderer.
     * @~chinese 设置滑动条是否使用九宫格 渲染器
     * @param able @~english True that using scale9 renderer, false otherwise.
     * @~chinese 使用九宫格渲染器时为true，反之为false
     */
    void setScale9Enabled(bool able);
    
    /**
     * @~english Gets If slider is using scale9 renderer.
     * @~chinese 获取当前滑动条是否使用九宫格渲染器
     * @return @~english True that using scale9 renderer, false otherwise.
     * @~chinese 使用九宫格渲染器返回true，反之返回false
     */
    bool isScale9Enabled()const;
    
    /**
     * @~english Sets capinsets for slider, if slider is using scale9 renderer.
     * @~chinese 设置滑动条的capinset，如果该滑动条使用了九宫格渲染器的话
     * @param capInsets @~english Capinsets for slider.
     * @~chinese 滑动条的capinsets
     */
    void setCapInsets(const Rect &capInsets);
    
    /**
     * @~english Sets capinsets for bar slider, if slider is using scale9 renderer.
     * @~chinese 设置滑动条的滑块的capinsets，如果使用了九宫格的渲染器的话
     * @param capInsets @~english Capinsets for bar slider.
     * @~chinese 滑动条滑块的capinsets
     */
    void setCapInsetsBarRenderer(const Rect &capInsets);
    
    /**
     * @~english Gets capinsets for bar slider, if slider is using scale9 renderer.
     * @~chinese 获取滑块的capinsets，如果滑动条开启了九宫格渲染
     * @return capInsets @~english Capinsets for bar slider.
     * @~chinese 滑块的capinsets
     */
    const Rect& getCapInsetsBarRenderer()const;
    
    /**
     * @~english Sets capinsets for progress bar slider, if slider is using scale9 renderer.
     * @~chinese 设置进度条的capinsets，如果滑动条开启了九宫格渲染
     * @param capInsets @~english Capinsets for progress bar slider.
     * @~chinese 进度条的capinsets
     * @js NA
     */
    void setCapInsetProgressBarRebderer(const Rect &capInsets);
    
    /**
     * @~english Gets capinsets for progress bar slider, if slider is using scale9 renderer.
     * @~chinese 获取进度条的capinsets，如果滑动条开启了九宫格渲染的话
     * @return @~english Capinsets for progress bar slider.
     * @~chinese 进度跳的九宫格渲染
     * @js NA
     */
    const Rect& getCapInsetsProgressBarRebderer()const;
    
    /**
     * @~english Load textures for slider ball.
     * @~chinese 读取滑动条的滑块的纹理
     * @param normal @~english Normal state texture.
     * @~chinese 正常状态下的纹理
     * @param pressed @~english Pressed state texture.
     * @~chinese 按住状态下的纹理
     * @param disabled @~english Disabled state texture.
     * @~chinese 禁用状态下的纹理
     * @param texType    @see TextureResType .
     * @~chinese 纹理资源类型
     */
    void loadSlidBallTextures(const std::string& normal,
                              const std::string& pressed = "",
                              const std::string& disabled = "",
                              TextureResType texType = TextureResType::LOCAL);
    
    /**
     * @~english Load normal state texture for slider ball.
     * @~chinese 读取正常状态下滑动条滑块纹理
     * @param normal    @~english Normal state texture.
     * @~chinese 正常状态的纹理
     * @param resType   @~english  @see TextureResType .
     * @~chinese 纹理资源类型
     */
    void loadSlidBallTextureNormal(const std::string& normal,TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Load pressed state texture for slider ball.
     * @~chinese 读取滑动条滑块按住状态的纹理
     * @param pressed   @~english  Pressed state texture.
     * @~chinese 按住状态下的纹理
     * @param resType    @~english @see TextureResType .
     * @~chinese 纹理资源类型
     */
    void loadSlidBallTexturePressed(const std::string& pressed,TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Load disabled state texture for slider ball.
     * @~chinese 读取禁用状态下的滑动条滑块纹理
     * @param disabled   @~english Disabled state texture.
     * @~chinese 禁用状态下的纹理
     * @param resType    @~english @see TextureResType .
     * @~chinese 纹理资源类型
     */
    void loadSlidBallTextureDisabled(const std::string& disabled,TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Load dark state texture for slider progress bar.
     * @~chinese 读取暗色状态下进度条纹理
     * @param fileName   @~english File path of texture.
     * @~chinese 纹理路径
     * @param resType  @~english   @see TextureResType .
     * @~chinese 纹理资源类型
     */
    void loadProgressBarTexture(const std::string& fileName, TextureResType resType = TextureResType::LOCAL);
    
    /**
     * @~english Changes the progress direction of slider.
     * @~chinese 设置滑动条的百分比
     * @param percent  @~english Percent value from 1 to 100.
     * @~chinese 百分比，从0至100
     */
    void setPercent(int percent);
    
    /**
     * @~english Gets the progress direction of slider.
     * @~chinese 获取滑动条的百分比
     * @return percent @~english Percent value from 1 to 100.
     * @~chinese 百分比，从0至100
     */
    int getPercent()const;

    /**
     * Set a large value could give more control to the precision.
     * @since v3.7
     * @param percent The max percent of Slider.
     */
    void setMaxPercent(int percent);

    /**
     * Query the maximum percent of Slider. The default value is 100.
     * @since v3.7
     * @return The maximum percent of the Slider.
     */
    int getMaxPercent()const;

    
    CC_DEPRECATED_ATTRIBUTE void addEventListenerSlider(Ref* target,SEL_SlidPercentChangedEvent selector);
    /**
     * @~english Add call back function called when slider's percent has changed to slider.
     * @~chinese 添加一个回调函数，该回调函数在滑动条百分比变化时被触发
     * @param callback @~english An given call back function called when slider's percent has changed to slider.
     */
    void addEventListener(const ccSliderCallback& callback);

    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent) override;
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent) override;
    
    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override the widget's hitTest function to perfom its own
    virtual bool hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const override;
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    /**
     * @~english When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @~chinese 当用户按住按钮时，按钮会按指定缩放系数缩放，按钮的最终缩放系数，等于原始缩放系数+_zoomScale
     * @param scale @~english The scale factor.
     * @~chinses 缩放系数
     * @since v3.3
     */
    void setZoomScale(float scale);
    /**
     * @brief @~english Return a zoom scale
     * @~chinese 获取缩放系数
     * @return @~english The zoom scale factor.
     * @~chinese 缩放系数
     * @since v3.3
     */
    float getZoomScale()const;

    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    virtual void initRenderer() override;
    float getPercentWithBallPos(const Vec2 &pt) const;
    void percentChangedEvent(EventType event);
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void setupBarTexture();
    void loadBarTexture(SpriteFrame* spriteframe);
    void setupProgressBarTexture();
    void loadProgressBarTexture(SpriteFrame* spriteframe);
    void loadSlidBallTextureNormal(SpriteFrame* spriteframe);
    void loadSlidBallTexturePressed(SpriteFrame* spriteframe);
    void loadSlidBallTextureDisabled(SpriteFrame* spriteframe);
   
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Scale9Sprite*  _barRenderer;
    Scale9Sprite* _progressBarRenderer;
    Size _barTextureSize;
    Size _progressBarTextureSize;
    
    Sprite* _slidBallNormalRenderer;
    Sprite* _slidBallPressedRenderer;
    Sprite* _slidBallDisabledRenderer;
    Node* _slidBallRenderer;
    
    float _barLength;
    int _percent;
    int _maxPercent;
    
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    
    float _zoomScale;
    float _sliderBallNormalTextureScaleX;
    float _sliderBallNormalTextureScaleY;

    bool _isSliderBallPressedTextureLoaded;
    bool _isSliderBallDisabledTexturedLoaded;

    Rect _capInsetsBarRenderer;
    Rect _capInsetsProgressBarRenderer;

    Ref*       _sliderEventListener;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif
    SEL_SlidPercentChangedEvent    _sliderEventSelector;
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif
    
    ccSliderCallback  _eventCallback;

    TextureResType _barTexType;
    TextureResType _progressBarTexType;
    TextureResType _ballNTexType;
    TextureResType _ballPTexType;
    TextureResType _ballDTexType;
    bool _barRendererAdaptDirty;
    bool _progressBarRendererDirty;
};

}

// end of ui group
/// @}

NS_CC_END

#endif /* defined(__CocoGUI__Slider__) */

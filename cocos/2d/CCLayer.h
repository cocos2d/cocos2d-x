/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCLAYER_H__
#define __CCLAYER_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCCustomCommand.h"


NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

class __Set;
class TouchScriptHandlerEntry;

class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;

class Touch;

//
// Layer
//
/** @class Layer
 * @brief @~english Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
 * @~chinese 图层是Node类的一个子类节点，它实现了TouchEventsDelegate协议。
 * 
 * 它所有从Node节点继承过来的功能都是有效的,并且添加了以下新功能:
 * - 它可以接收iPhone触摸
 * - 它可以得到加速度计输入事件
*/
class CC_DLL Layer : public Node
{
public:    
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese 创建一个全屏黑色的图层。
     * 
     * @return @~english An autoreleased Layer object.
     * @~chinese 一个autoreleased图层对象。
     */
    static Layer *create();

    // Deprecated touch callbacks.
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(__Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    

    /** @~english Callback function for touch began.
     *
     * @~chinese 触摸开始时的回调函数
     * 
     * @param touch @~english Touch infomation.
     * @~chinese 触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @return @~english if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
     * @~chinese 如果返回false,那么onTouchMoved、onTouchEnded onTouchCancelled永远不会被调用
     * @js NA
     */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch moved.
     *
     * @~chinese 触摸移动时的回调函数
     * 
     * @param touch @~english Touch infomation.
     * @~chinese 触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch ended.
     *
     * @~chinese 触摸结束时的回调函数
     * 
     * @param touch @~english Touch infomation.
     * @~chinese 触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    /** @~english Callback function for touch cancelled.
     *
     * @~chinese 触摸取消时的回调函数
     * 
     * @param touch @~english Touch infomation.
     * @~chinese 触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    /** @~english Callback function for multiple touches began.
     *
     * @~chinese 多点触摸开始时的回调函数
     * 
     * @param touches @~english Touches information.
     * @~chinese 多点触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches moved.
     *
     * @~chinese 多点触摸移动时的回调函数
     * 
     * @param touches @~english Touches information.
     * @~chinese 多点触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches ended.
     *
     * @~chinese 多点触摸结束时的回调函数
     * 
     * @param touches @~english Touches information.
     * @~chinese 多点触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    /** @~english Callback function for multiple touches cancelled.
     *
     * @~chinese 多点触摸取消时的回调函数
     * 
     * @param touches @~english Touches information.
     * @~chinese 多点触摸信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    /** 
      @deprecated Please override onAcceleration 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(Acceleration* accelerationValue) final {};

    /** @~english Callback funtion for acceleration.
     * @~chinese 加速计事件回调函数。
     * @param acc @~english Acceleration information.
     * @~chinese 加速计信息。
     * @param unused_event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);

    CC_DEPRECATED_ATTRIBUTE virtual void registerWithTouchDispatcher() final {};

    /** @~english whether or not it will receive Touch events.
     * You can enable / disable touch events with this property.
     * Only the touches of this node will be affected. This "method" is not propagated to it's children.
     * @~chinese 是否接收触摸事件。
     * 您可以调用该方法来启用或者禁用触摸事件。
     * 只有调用该方法的节点的接触将受到影响。这个“方法”不会传播到它的孩子。
     * @since v0.8.1
     * @js NA
    */
    CC_DEPRECATED_ATTRIBUTE bool isTouchEnabled() const;
    CC_DEPRECATED_ATTRIBUTE void setTouchEnabled(bool value);
    
    CC_DEPRECATED_ATTRIBUTE virtual void setTouchMode(Touch::DispatchMode mode);
    CC_DEPRECATED_ATTRIBUTE virtual Touch::DispatchMode getTouchMode() const;

    /** @~english
     * swallowsTouches of the touch events. Default is true
     * @~chinese 
     * 设置吞噬触摸事件。默认值是True.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void setSwallowsTouches(bool swallowsTouches);
    CC_DEPRECATED_ATTRIBUTE virtual bool isSwallowsTouches() const;

    /** @~english whether or not it will receive Accelerometer events
     * You can enable / disable accelerometer events with this property.
     * @~chinese 是否接收加速度计的事件
     * 您可以调用该方法来启用或禁用加速计事件
     * @since v0.8.1
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool isAccelerometerEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerEnabled(bool value);
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerInterval(double interval);

    /** @~english whether or not it will receive keyboard or keypad events
     * You can enable / disable accelerometer events with this property.
     * it's new in cocos2d-x
     * @~chinese 是否会收到键盘或虚拟键盘事件
     * 您调用该方法启用或者禁用键盘事件
     * 这是cocos2d-x的一个新方法
     * @js NA
     */

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeyboardEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setKeyboardEnabled(bool value);

    /** @~english
     * Please use onKeyPressed instead.
     * @~chinese 
     * 请使用onKeyPressed函数代替。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyPressed(int keyCode) final {};
    
    /** @~english
     * Please use onKeyReleased instead.
     * @~chinese 
     * 请使用onKeyReleased函数代替。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyReleased(int keyCode) final {};

    /** @~english Callback function for key pressed.
     * @~chinese 按键按下去时的回调函数
     * @param keyCode @~english KeyCode information.
     * @~chinese 键码信息。
     * @param event @~english Event information.
     * @~chinese 事件信息。
     * @js NA
     */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    /** @~english Callback function for key released.
     * @~chinese 按键释放时的回调函数
    * @param keyCode @~english KeyCode information.
     * @~chinese 键码信息。
    * @param event @~english Event information.
     * @~chinese 事件信息。
    * @js NA
    */
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeypadEnabled() const final { return _keyboardEnabled; }
    CC_DEPRECATED_ATTRIBUTE virtual void setKeypadEnabled(bool value);

    /** 
      @deprecated Please override onKeyReleased and check the keycode of KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE) instead. 
      @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void keyBackClicked() final {};
    CC_DEPRECATED_ATTRIBUTE virtual void keyMenuClicked() final {};

    // Overrides
    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    Layer();
    virtual ~Layer();

    virtual bool init() override;

protected:
    //add the api for avoid use deprecated api
    CC_DEPRECATED_ATTRIBUTE void _addTouchListener() {}

    CC_DEPRECATED_ATTRIBUTE void addTouchListener() {}
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch, Event* event);
    CC_DEPRECATED_ATTRIBUTE int executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event);

    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keyboardEnabled;
    EventListener* _touchListener;
    EventListenerKeyboard* _keyboardListener;
    EventListenerAcceleration* _accelerationListener;

    Touch::DispatchMode _touchMode;
    bool _swallowsTouches;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Layer);

};


/** @class __LayerRGBA
 * @brief @~english LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 *
 * All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 * - opacity
 * - RGB colors
 * @~chinese LayerRGBA类是Layer的子类，它实现了RGBAProtocol协议并且使用纯色作为背景。
 * 
 * 它所有从Layer继承过来的功能都是有效的,并且它还实现了一些新特性，这些特性可以对所有符合 RGBAProtocol的孩子结点生效。
 * - 不透明
 * - RGB颜色
 * @since 2.1
 * @js NA
 */
class CC_DLL __LayerRGBA : public Layer, public __RGBAProtocol
{
public:
    CREATE_FUNC(__LayerRGBA);
    
    
    //
    // Overrides
    //
    virtual GLubyte getOpacity() const override { return Layer::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const override { return Layer::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { Layer::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { Layer::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { Layer::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor() const override { return Layer::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Layer::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { Layer::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { Layer::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { Layer::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { Layer::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Layer::isOpacityModifyRGB(); }

CC_CONSTRUCTOR_ACCESS:
    __LayerRGBA();
    virtual ~__LayerRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__LayerRGBA);
};

//
// LayerColor
//
/** @class LayerColor
 * @brief @~english LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

 * All features from Layer are valid, plus the following new features:
 * - opacity
 * - RGB colors
 * @~chinese LayerColor是Layer类的子类，并且它实现了 RGBAProtocol协议
 *
 * 它所有从Layer继承过来的功能都是有效的,并且它还实现了一些新特性，这些特性可以对所有符合 RGBAProtocol的孩子结点生效。
 * - 不透明
 * - RGB颜色
 */
class CC_DLL LayerColor : public Layer, public BlendProtocol
{
public:
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese 创建一个全屏的黑色图层
     *
     * @return @~english An autoreleased LayerColor object.
     * @~chinese 一个自动释放的LayerColor对象。
     */
    static LayerColor* create();
    /** @~english Creates a Layer with color, width and height in Points.
     *
     * @~chinese 通过颜色,宽度和高度来创建一个图层
     * 
     * @param color @~english The color of layer.
     * @~chinese 图层的颜色。
     * @param width @~english The width of layer.
     * @~chinese 图层的宽度。
     * @param height @~english The height of layer.
     * @~chinese 图层的高度。
     * @return @~english An autoreleased LayerColor object.
     * @~chinese 一个自动释放LayerColor对象。
     */
    static LayerColor * create(const Color4B& color, GLfloat width, GLfloat height);
    /** @~english Creates a Layer with color. Width and height are the window size.
     *
     * @~chinese 使用颜色创建一个图层。宽度和高度等于窗口大小。
     * 
     * @param color @~english The color of layer.
     * @~chinese 图层的颜色。
     * @return @~english An autoreleased LayerColor object.
     * @~chinese 一个自动释放的LayerColor对象。
     */
    static LayerColor * create(const Color4B& color);

    /** @~english Change width in Points.
     * 
     * @~chinese 修改图层的宽度
     * 
     * @param w @~english The width of layer.
     * @~chinese 图层的宽度
     */
    void changeWidth(GLfloat w);
    /** @~english Change height in Points.
     *
     * @~chinese 修改图层的高度
     * 
     * @param h @~english The height of layer.
     * @~chinese 图层的高度。
     */
    void changeHeight(GLfloat h);
    /** @~english Change width and height in Points.
     * 
     * @~chinese 修改图层的宽度和高度
     * 
     * @param w @~english The width of layer.
     * @~chinese 图层的宽度。
     * @param h @~english The Height of layer.
     * @~chinese 图层的高度。
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setContentSize(const Size & var) override;
    /** @~english BlendFunction. Conforms to BlendProtocol protocol
     * @~chinese 混合函数,符合BlendProtocol协议
     * @lua NA
     */
    virtual const BlendFunc& getBlendFunc() const override;
    /**
     *@code@~english
     *When this function bound into js or lua,the parameter will be changed
     */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerColor();
    virtual ~LayerColor();
    
    bool init() override;
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    bool initWithColor(const Color4B& color);

protected:
    void onDraw(const Mat4& transform, uint32_t flags);

    virtual void updateColor() override;

    BlendFunc _blendFunc;
    Vec2 _squareVertices[4];
    Color4F  _squareColors[4];
    CustomCommand _customCommand;
    Vec3 _noMVPVertices[4];
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @class LayerGradient
 * @brief @~english LayerGradient is a subclass of LayerColor that draws gradients across the background.
 * All features from LayerColor are valid, plus the following new features:
 * - direction
 * - final color
 * - interpolation mode

 * Color is interpolated between the startColor and endColor along the given
 * vector (starting at the origin, ending at the terminus).  If no vector is
 * supplied, it defaults to (0, -1) -- a fade from top to bottom.
 * If 'compressedInterpolation' is disabled, you will not see either the start or end color for
 * non-cardinal vectors; a smooth gradient implying both end points will be still
 * be drawn, however.

 * If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
 * @~chinese LayerGradient类是LayerColor的子类,用来绘制渐变背景。
 * 
 * 它所有从LayerColor继承来的功能是有效的,再加上以下新的特性:
 * - 方向
 * - 最终颜色
 * - 插值模式
 * 
 * 颜色是用给定的向量(从原点,最后终点)，使用endColor和startColor进行插值得到的
 * 如果没有提供向量,它默认为(0,1) —— 表示从上到下渐变。
 * 
 * 如果“compressedInterpolation”是禁用的,你不会看到的开始或结束的颜色梯度
 *
 * 如果启用了“compressedInterpolation”(默认模式),您将看到的开始和结束的颜色梯度。
 * 
 * @since v0.99.5
 */
class CC_DLL LayerGradient : public LayerColor
{
public:
    /** @~english Creates a fullscreen black layer.
     *
     * @~chinese 创建一个全屏的黑色图层。
     * 
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese 一个自动释放的LayerGradient对象。
     */
    static LayerGradient* create();

    /** @~english Creates a full-screen Layer with a gradient between start and end.
     *
     * @~chinese 创建一个全屏的和在开始和结束颜色之间的梯度图层。
     * 
     * @param start @~english The start color.
     * @~chinese 起点颜色。
     * @param end @~english The end color.
     * @~chinese 终点颜色。
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese 一个自动释放LayerGradient对象。
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** @~english Creates a full-screen Layer with a gradient between start and end in the direction of v.
     *
     * @~chinese 在方向V上，使用开始颜色和结束颜色插值，创建一个全屏的带颜色梯度的图层。
     * 
     * @param start @~english The start color.
     * @~chinese 开始颜色。
     * @param end @~english The end color.
     * @~chinese 结束颜色。
     * @param v @~english The direction of gradient color.
     * @~chinese 颜色梯度的方向。
     * @return @~english An autoreleased LayerGradient object.
     * @~chinese 一个自动释放LayerGradient对象。
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Vec2& v);
    
    /** @~english Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors.
     * Default: true.
     *
     * @~chinese 为了在规范和非规范的向量空间内显示所有的颜色梯度,是否需要压缩插值。
     * 默认值: True
     * 
     * @param compressedInterpolation @~english The interpolation will be compressed if true.
     * @~chinese 如果插值被压缩则为true.
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    /** @~english Get the compressedInterpolation
     *
     * @~chinese 查询是否插值会压缩
     * 
     * @return @~english The interpolation will be compressed if true.
     * @~chinese 如果插值会压缩则返回真，否则返回假
     */
    bool isCompressedInterpolation() const;

    /** @~english Sets the start color of the gradient.
     * 
     * @~chinese 设置开始渐变颜色。
     * 
     * @param startColor @~english The start color.
     * @~chinese 开始颜色。
     */
    void setStartColor( const Color3B& startColor );
    /** @~english Returns the start color of the gradient.
     *
     * @~chinese 返回开始颜色梯度。
     * 
     * @return @~english The start color.
     * @~chinese 开始颜色。
     */
    const Color3B& getStartColor() const;

    /** @~english Sets the end color of the gradient.
     *
     * @~chinese 设置结束渐变颜色。
     * 
     * @param endColor @~english The end color.
     * @~chinese 结束颜色。
     */
    void setEndColor( const Color3B& endColor );
    /** @~english Returns the end color of the gradient.
     *
     * @~chinese 返回结束的颜色梯度。
     * 
     * @return @~english The end color.
     * @~chinese 结束颜色。
     */
    const Color3B& getEndColor() const;

    /** @~english Returns the start opacity of the gradient.
     *
     * @~chinese 返回开始的不透明的梯度。
     * 
     * @param startOpacity @~english The start opacity, from 0 to 255.
     * @~chinese 开始不透明度,从0到255。
     */
    void setStartOpacity( GLubyte startOpacity );
    /** @~english Returns the start opacity of the gradient.
     *
     * @~chinese 返回开始的不透明的梯度。
     * 
     * @return @~english The start opacity.
     * @~chinese 开始的不透明度。
     */
    GLubyte getStartOpacity() const;

    /** @~english Returns the end opacity of the gradient.
     *
     * @~chinese 返回结束不透明的渐变。
     * 
     * @param endOpacity @~english The end opacity, from 0 to 255.
     * @~chinese 不透明,从0到255。
     */
    void setEndOpacity( GLubyte endOpacity );
    /** @~english Returns the end opacity of the gradient.
     *
     * @~chinese 返回结束不透明的渐变。
     * 
     * @return @~english The end opacity.
     * @~chinese 不透明。
     */
    GLubyte getEndOpacity() const;

    /** @~english Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     *
     * @~chinese 设置梯度方向向量。
     * 默认值是垂直方向(0,1)。
     * 
     * @param alongVector @~english The direction of gradient.
     * @~chinese 梯度的方向。
     */
    void setVector(const Vec2& alongVector);
    /** @~english Returns the directional vector used for the gradient.
     *
     * @~chinese 返回梯度方向向量。
     * 
     * @return @~english The direction of gradient.
     * @~chinese 梯度的方向。
     */
    const Vec2& getVector() const;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init() override;
    /** @~english Initializes the Layer with a gradient between start and end.
     * @~chinese 使用开始徒崾丈闯跏蓟疾恪�
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** @~english Initializes the Layer with a gradient between start and end in the direction of v.
     * @~chinese 使用开始和结束颜色，以及梯度方向来初始化图层
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Vec2& v);

protected:
    virtual void updateColor() override;

    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Vec2   _alongVector;
    bool    _compressedInterpolation;
};


/** @class LayerMultiplex
 * @brief @~english MultipleLayer is a Layer with the ability to multiplex it's children.
 * Features:
 * - It supports one or more children
 * - Only one children will be active a time
 * @~chinese MultipleLayer是一种图层，它支持多路复用孩子节点
 * 特点:
 * - 它支持一个或多个孩子节点
 * - 同时只有一个孩子节点会被激活
 */
class CC_DLL LayerMultiplex : public Layer
{
public:
    /** @~english Creates and initializes a LayerMultiplex object.
     * @~chinese 创建并初始化一个LayerMultiplex对象。
     * @lua NA
     * 
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese 一个autoreleased LayerMultiplex对象。
     */
    static LayerMultiplex* create();

    /** @~english Creates a LayerMultiplex with an array of layers.
     * @~chinese 使用数组创建一个LayerMultiplex层。
     @since v2.1
     * @js NA
     *
     * @param arrayOfLayers @~english An array of layers.
     * @~chinese 一个数组的层。
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese 一个autoreleased LayerMultiplex对象。
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** @~english Creates a LayerMultiplex with one or more layers using a variable argument list.
     * @~chinese 创建一个变长参数列表来创建LayerMultiplex
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported
    typedef Layer* M;
    static LayerMultiplex* create(M m1, std::nullptr_t listEnd) { return createVariadic(m1, NULL); }
    static LayerMultiplex* create(M m1, M m2, std::nullptr_t listEnd) { return createVariadic(m1, m2, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static LayerMultiplex* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createVariadic(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for variable argument lists longer than 10 items, use createWithArray or createVariadic with NULL as the last argument
    static LayerMultiplex* createVariadic(Layer* item, ...) CC_REQUIRES_NULL_TERMINATION;
#else
    static LayerMultiplex * create(Layer* layer, ... );
#endif

    /** @~english Creates a LayerMultiplex with one layer.
     * @~chinese Creates a LayerMultiplex with one layer.
     * 使用一个图层来创建 MultiplexLayer
     *
     * @param layer @~english A certain layer.
     * @~chinese 某一图层。
     * @return @~english An autoreleased LayerMultiplex object.
     * @~chinese 一个自动释放的LayerMultiplex对象。
     * @js NA
     * @lua NA
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    /** @~english Add a certain layer to LayerMultiplex.
     *
     * @~chinese 添加图层到LayerMultiplex。
     * 
     * @param layer @~english A layer need to be added to the LayerMultiplex.
     * @~chinese 被添加到LayerMultiplex的图层
     */
    void addLayer(Layer* layer);

    /** @~english Switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @~chinese 切换到某一个索引为n的图层。
     * 当前(旧的)图层将从它的父亲中移除，当 (cleanup = true)时。
     * 
     * @param n @~english The layer indexed by n will display.
     * @~chinese 图层n将会显示。
     */
    void switchTo(int n);
    /** @~english release the current layer and switches to another layer indexed by n.
     * The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @~chinese 释放当前图层同时切换到另一个索引为n的图层。
     * 当前(旧的)图层将从它的父亲中移除，当 (cleanup = true)时。
     * 
     * @param n @~english The layer indexed by n will display.
     * @~chinese 将显示层被n。
     */
    void switchToAndReleaseMe(int n);

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    LayerMultiplex();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LayerMultiplex();
    
    virtual bool init() override;
    /** @~english initializes a MultiplexLayer with one or more layers using a variable argument list.
     * @~chinese 使用一个图层或者一个变长参数列表来初始化 MultiplexLayer
     * @js NA
     * @lua NA
     */
    bool initWithLayers(Layer* layer, va_list params);
    
    /** @~english initializes a MultiplexLayer with an array of layers
     * @~chinese 使用一个图层数组来初始化 LayerMultiplex
     * @since v2.1
     */
    bool initWithArray(const Vector<Layer*>& arrayOfLayers);

protected:
    unsigned int _enabledLayer;
    Vector<Layer*>    _layers;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerMultiplex);
};


// end of _2d group
/// @}

NS_CC_END

#endif // __CCLAYER_H__


/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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
#pragma once

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCCustomCommand.h"

#include <vector>

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
 * @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL Layer : public Node
{
public:    
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased Layer object.
     */
    static Layer *create();
    
    /* Callback function should not be deprecated, it will generate lots of warnings.
       Since 'setTouchEnabled' was deprecated, it will make warnings if developer overrides onTouchXXX and invokes setTouchEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for touch began.
     *
     * @param touch Touch information.
     * @param unused_event Event information.
     * @return if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
     * @js NA
     */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    /** Callback function for touch moved.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    /** Callback function for touch ended.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    /** Callback function for touch cancelled.
    *
    * @param touch Touch information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    /** Callback function for multiple touches began.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches moved.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches ended.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    /** Callback function for multiple touches cancelled.
    *
    * @param touches Touches information.
    * @param unused_event Event information.
    * @js NA
    */
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setAccelerometerEnabled' was deprecated, it will make warnings if developer overrides onAcceleration and invokes setAccelerometerEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for acceleration.
     * @param acc Acceleration information.
     * @param unused_event Event information.
     * @js NA
     */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);


	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setKeyboardEnabled' was deprecated, it will make warnings if developer overrides onKeyXXX and invokes setKeyboardEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    /** Callback function for key pressed.
     * @param keyCode KeyCode information.
     * @param event Event information.
     * @js NA
     */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    /** Callback function for key released.
    * @param keyCode KeyCode information.
    * @param event Event information.
    * @js NA
    */
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // Overrides
    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    Layer();
    virtual ~Layer();

    virtual bool init() override;

protected:
    
    int executeScriptTouchHandler(EventTouch::EventCode eventType, Touch* touch, Event* event);
    int executeScriptTouchesHandler(EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event);

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

//
// LayerColor
//
/** @class LayerColor
 * @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

All features from Layer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CC_DLL LayerColor : public Layer, public BlendProtocol
{
public:

    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased LayerColor object.
     */
    static LayerColor* create();
    /** Creates a Layer with color, width and height in Points.
     *
     * @param color The color of layer.
     * @param width The width of layer.
     * @param height The height of layer.
     * @return An autoreleased LayerColor object.
     */
    static LayerColor * create(const Color4B& color, float width, float height);
    /** Creates a Layer with color. Width and height are the window size.
     *
     * @param color The color of layer.
     * @return An autoreleased LayerColor object.
     */
    static LayerColor * create(const Color4B& color);

    /** Change width in Points.
     * 
     * @param w The width of layer.
     */
    void changeWidth(float w);
    /** Change height in Points.
     *
     * @param h The height of layer.
     */
    void changeHeight(float h);
    /** Change width and height in Points.
     * 
     * @param w The width of layer.
     * @param h The Height of layer.
    @since v0.8
    */
    void changeWidthAndHeight(float w, float h);

    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void setContentSize(const Size & var) override;
    /** BlendFunction. Conforms to BlendProtocol protocol */
    /**
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;
    /**
    *@code
    *When this function bound into js or lua,the parameter will be changed
    *In js: var setBlendFunc(var src, var dst)
    *In lua: local setBlendFunc(local src, local dst)
    *@endcode
    */
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerColor();
    virtual ~LayerColor();
    
    bool init() override;
    bool initWithColor(const Color4B& color, float width, float height);
    bool initWithColor(const Color4B& color);

protected:

    virtual void updateColor() override;
    void updateVertexBuffer();

    BlendFunc _blendFunc;
    Vec2 _squareVertices[4];
    CustomCommand _customCommand;

    V3F_C4F _vertexData[4];
    
    backend::UniformLocation _mvpMatrixLocation;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @class LayerGradient
 * @brief LayerGradient is a subclass of LayerColor that draws gradients across the background.

All features from LayerColor are valid, plus the following new features:
- direction
- final color
- interpolation mode

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.

If 'compressedInterpolation' is disabled, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.

If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.

@since v0.99.5
*/
class CC_DLL LayerGradient : public LayerColor
{
public:
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create();

    /** Creates a full-screen Layer with a gradient between start and end.
     *
     * @param start The start color.
     * @param end The end color.
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** Creates a full-screen Layer with a gradient between start and end in the direction of v.
     *
     * @param start The start color.
     * @param end The end color.
     * @param v The direction of gradient color.
     * @return An autoreleased LayerGradient object.
     */
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Vec2& v);
    
    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors.
     Default: true.
     *
     * @param compressedInterpolation The interpolation will be compressed if true.
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    /** Get the compressedInterpolation
     *
     * @return The interpolation will be compressed if true.
     */
    bool isCompressedInterpolation() const;

    /** Sets the start color of the gradient.
     * 
     * @param startColor The start color.
     */
    void setStartColor( const Color3B& startColor );
    /** Returns the start color of the gradient.
     *
     * @return The start color.
     */
    const Color3B& getStartColor() const;

    /** Sets the end color of the gradient.
     *
     * @param endColor The end color.
     */
    void setEndColor( const Color3B& endColor );
    /** Returns the end color of the gradient.
     *
     * @return The end color.
     */
    const Color3B& getEndColor() const;

    /** Returns the start opacity of the gradient.
     *
     * @param startOpacity The start opacity, from 0 to 255.
     */
    void setStartOpacity(uint8_t startOpacity );
    /** Returns the start opacity of the gradient.
     *
     * @return The start opacity.
     */
    uint8_t getStartOpacity() const;

    /** Returns the end opacity of the gradient.
     *
     * @param endOpacity The end opacity, from 0 to 255.
     */
    void setEndOpacity(uint8_t endOpacity );
    /** Returns the end opacity of the gradient.
     *
     * @return The end opacity.
     */
    uint8_t getEndOpacity() const;

    /** Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     *
     * @param alongVector The direction of gradient.
     */
    void setVector(const Vec2& alongVector);
    /** Returns the directional vector used for the gradient.
     *
     * @return The direction of gradient.
     */
    const Vec2& getVector() const;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init() override;
    /** Initializes the Layer with a gradient between start and end.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** Initializes the Layer with a gradient between start and end in the direction of v.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Vec2& v);

protected:
    virtual void updateColor() override;

    Color3B _startColor = Color3B::BLACK;
    Color3B _endColor = Color3B::BLACK;
    uint8_t _startOpacity = 255;
    uint8_t _endOpacity = 255;
    Vec2   _alongVector = {0.0f, -1.0f};
    bool    _compressedInterpolation = true;
};


/** @class LayerRadialGradient
 * @brief LayerRadialGradient is a subclass of Layer that draws radial gradients across the background.
 @since v3.16
 */
class CC_DLL LayerRadialGradient : public Layer
{
public:
    /** Create a LayerRadialGradient
     * @param startColor the inner color of the gradient
     * @param endColor the out color of the gradient
     * @param radius the radius of the gradient(length from center of gradient to outer color)
     * @param center the position of the center of the gradient
     * @param expand an alpha value(0.f-1.f) that specifies how much of that radius in only inner color(the gradient
                     starts outside of that amount)
     */
    static LayerRadialGradient* create(const Color4B& startColor, const Color4B& endColor, float radius, const Vec2& center, float expand);
    static LayerRadialGradient* create();
    
    //
    // overrides
    //
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void setContentSize(const Size& size) override;
    
    void setStartOpacity(uint8_t opacity);
    uint8_t getStartOpacity() const;
    
    void setEndOpacity(uint8_t opacity);
    uint8_t getEndOpacity() const;
    
    void setRadius(float radius);
    float getRadius() const;
    
    void setCenter(const Vec2& center);
    Vec2 getCenter() const;
    
    void setExpand(float expand);
    float getExpand() const;
    
    void setStartColor(const Color3B& color);
    void setStartColor(const Color4B& color);
    Color4B getStartColor() const;
    Color3B getStartColor3B() const;
    
    void setEndColor(const Color3B& color);
    void setEndColor(const Color4B& color);
    Color4B getEndColor() const;
    Color3B getEndColor3B() const;
    
    void setBlendFunc(const BlendFunc& blendFunc);
    BlendFunc getBlendFunc() const;
    
CC_CONSTRUCTOR_ACCESS:
    LayerRadialGradient();
    virtual ~LayerRadialGradient();
    
    bool initWithColor(const Color4B& startColor, const Color4B& endColor, float radius, const Vec2& center, float expand);
    
private:
    void convertColor4B24F(Color4F& outColor, const Color4B& inColor);
    
    Color4B _startColor = Color4B::BLACK;
    Color4F _startColorRend = Color4F::BLACK; // start color used in shader
    
    Color4B _endColor = Color4B::BLACK;
    Color4F _endColorRend = Color4F::BLACK; // end color used in shader

    Vec2 _vertices[4];
    Vec2 _center;
    float _radius = 0.f;
    float _expand = 0.f;
    CustomCommand _customCommand;
    
    BlendFunc _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    
    backend::UniformLocation _mvpMatrixLocation;
    backend::UniformLocation _startColorLocation;
    backend::UniformLocation _endColorLocation;
    backend::UniformLocation _centerLocation;
    backend::UniformLocation _radiusLocation;
    backend::UniformLocation _expandLocation;
};


/** @class LayerMultiplex
 * @brief MultipleLayer is a Layer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CC_DLL LayerMultiplex : public Layer
{
public:
    /** Creates and initializes a LayerMultiplex object.
     * @lua NA
     * 
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex* create();

    /** Creates a LayerMultiplex with an array of layers.
     @since v2.1
     * @js NA
     *
     * @param arrayOfLayers An array of layers.
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** Creates a LayerMultiplex with one or more layers using a variable argument list.
     * @code
     * When this function bound to lua or js,the input params are changed.
     * In js:var create(...)
     * In lua:local create(...)
     * @endcode
     */
    static LayerMultiplex * create(Layer* layer, ... );

    /** Creates a LayerMultiplex with one layer.
     * Lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     * @js NA
     * @lua NA
     *
     * @param layer A certain layer.
     * @return An autoreleased LayerMultiplex object.
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    /** Add a certain layer to LayerMultiplex.
     *
     * @param layer A layer need to be added to the LayerMultiplex.
     */
    void addLayer(Layer* layer);

    /** Switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @param n The layer indexed by n will display.
     */
    void switchTo(int n);
    /** The same as switchTo(int), but has a parameter to set if need to clean up child.
     */
    void switchTo(int n, bool cleanup);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup=true'.
     *
     * @param n The layer indexed by n will display.
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
    /** initializes a MultiplexLayer with one or more layers using a variable argument list.
     * @js NA
     * @lua NA
     */
    bool initWithLayers(Layer* layer, va_list params);
    
    /** initializes a MultiplexLayer with an array of layers
     @since v2.1
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

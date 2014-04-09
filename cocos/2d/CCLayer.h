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

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCEventTouch.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

#include "CCEventKeyboard.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup layer
 * @{
 */

class __Set;
class TouchScriptHandlerEntry;

class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;

//
// Layer
//
/** @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL Layer : public Node
{
public:    
    /** creates a fullscreen black layer */
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
    
    /* Callback function should not be deprecated, it will generate lots of warnings.
       Since 'setTouchEnabled' was deprecated, it will make warnings if developer overrides onTouchXXX and invokes setTouchEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    /** @deprecated Please override onAcceleration */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(Acceleration* accelerationValue) final {};

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setAccelerometerEnabled' was deprecated, it will make warnings if developer overrides onAcceleration and invokes setAccelerometerEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);

    /** If isTouchEnabled, this method is called onEnter. Override it to change the
    way Layer receives touch events.
    ( Default: TouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
    Example:
    void Layer::registerWithTouchDispatcher()
    {
    TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    }
    @since v0.8.0
    */
    CC_DEPRECATED_ATTRIBUTE virtual void registerWithTouchDispatcher() final {};

    /** whether or not it will receive Touch events.
    You can enable / disable touch events with this property.
    Only the touches of this node will be affected. This "method" is not propagated to it's children.
    @since v0.8.1
    */
    CC_DEPRECATED_ATTRIBUTE bool isTouchEnabled() const;
    CC_DEPRECATED_ATTRIBUTE void setTouchEnabled(bool value);
    
    CC_DEPRECATED_ATTRIBUTE virtual void setTouchMode(Touch::DispatchMode mode);
    CC_DEPRECATED_ATTRIBUTE virtual Touch::DispatchMode getTouchMode() const;

    /** swallowsTouches of the touch events. Default is true */
    CC_DEPRECATED_ATTRIBUTE virtual void setSwallowsTouches(bool swallowsTouches);
    CC_DEPRECATED_ATTRIBUTE virtual bool isSwallowsTouches() const;

    /** whether or not it will receive Accelerometer events
    You can enable / disable accelerometer events with this property.
    @since v0.8.1
    */
    CC_DEPRECATED_ATTRIBUTE virtual bool isAccelerometerEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerEnabled(bool value);
    CC_DEPRECATED_ATTRIBUTE virtual void setAccelerometerInterval(double interval);

    /** whether or not it will receive keyboard or keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeyboardEnabled() const;
    CC_DEPRECATED_ATTRIBUTE virtual void setKeyboardEnabled(bool value);

    /** Please use onKeyPressed instead. */
    CC_DEPRECATED_ATTRIBUTE virtual void keyPressed(int keyCode) final {};
    
    /** Please use onKeyReleased instead. */
    CC_DEPRECATED_ATTRIBUTE virtual void keyReleased(int keyCode) final {};

	/* Callback function should not be deprecated, it will generate lots of warnings.
	Since 'setKeyboardEnabled' was deprecated, it will make warnings if developer overrides onKeyXXX and invokes setKeyboardEnabled(true) instead of using EventDispatcher::addEventListenerWithXXX.
    */
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    CC_DEPRECATED_ATTRIBUTE virtual bool isKeypadEnabled() const final { return _keyboardEnabled; }
    CC_DEPRECATED_ATTRIBUTE virtual void setKeypadEnabled(bool value);

    /** @deprecated Please override onKeyReleased and check the keycode of KeyboardEvent::KeyCode::Menu(KEY_BACKSPACE) instead. */
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
    void _addTouchListener();

    CC_DEPRECATED_ATTRIBUTE void addTouchListener() { _addTouchListener();};
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


/** LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 
 All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 - opacity
 - RGB colors
 @since 2.1
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
    virtual void setOpacity(GLubyte opacity) override { return Layer::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { return Layer::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { return Layer::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor() const override { return Layer::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Layer::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { return Layer::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { return Layer::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Layer::isCascadeOpacityEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { return Layer::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { return Layer::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Layer::isOpacityModifyRGB(); }

protected:
    __LayerRGBA();
    virtual ~__LayerRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__LayerRGBA);
};

//
// LayerColor
//
/** @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

All features from Layer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CC_DLL LayerColor : public Layer, public BlendProtocol
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** creates a fullscreen black layer */
    static LayerColor* create();
    /** creates a Layer with color, width and height in Points */
    static LayerColor * create(const Color4B& color, GLfloat width, GLfloat height);
    /** creates a Layer with color. Width and height are the window size. */
    static LayerColor * create(const Color4B& color);

    /** change width in Points*/
    void changeWidth(GLfloat w);
    /** change height in Points*/
    void changeHeight(GLfloat h);
    /** change width and height in Points
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    //
    // Overrides
    //
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

    virtual void setContentSize(const Size & var) override;
    /** BlendFunction. Conforms to BlendProtocol protocol */
    /**
    * @js NA
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

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerColor();
    virtual ~LayerColor();
    
    bool init();
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    bool initWithColor(const Color4B& color);

protected:
    void onDraw(const kmMat4& transform, bool transformUpdated);

    virtual void updateColor() override;

    BlendFunc _blendFunc;
    Vertex2F _squareVertices[4];
    Color4F  _squareColors[4];
    CustomCommand _customCommand;
    Vertex3F _noMVPVertices[4];
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LayerColor);

};

//
// LayerGradient
//
/** @brief LayerGradient is a subclass of LayerColor that draws gradients across the background.

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
    /** Creates a fullscreen black layer */
    static LayerGradient* create();

    /** Creates a full-screen Layer with a gradient between start and end. */
    static LayerGradient* create(const Color4B& start, const Color4B& end);

    /** Creates a full-screen Layer with a gradient between start and end in the direction of v. */
    static LayerGradient* create(const Color4B& start, const Color4B& end, const Point& v);
    
    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
     Default: true
     */
    void setCompressedInterpolation(bool compressedInterpolation);
    bool isCompressedInterpolation() const;

    /** Sets the start color of the gradient */
    void setStartColor( const Color3B& startColor );
    /** Returns the start color of the gradient */
    const Color3B& getStartColor() const;

    /** Sets the end color of the gradient */
    void setEndColor( const Color3B& endColor );
    /** Returns the end color of the gradient */
    const Color3B& getEndColor() const;

    /** Returns the start opacity of the gradient */
    void setStartOpacity( GLubyte startOpacity );
    /** Returns the start opacity of the gradient */
    GLubyte getStartOpacity() const;

    /** Returns the end opacity of the gradient */
    void setEndOpacity( GLubyte endOpacity );
    /** Returns the end opacity of the gradient */
    GLubyte getEndOpacity() const;

    /** Sets the directional vector that will be used for the gradient.
    The default value is vertical direction (0,-1). 
     */
    void setVector(const Point& alongVector);
    /** Returns the directional vector used for the gradient */
    const Point& getVector() const;

    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayerGradient();
    virtual ~LayerGradient();
    
    virtual bool init();
    /** Initializes the Layer with a gradient between start and end.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end);
    
    /** Initializes the Layer with a gradient between start and end in the direction of v.
     * @js init
     * @lua init
     */
    bool initWithColor(const Color4B& start, const Color4B& end, const Point& v);

protected:
    virtual void updateColor() override;

    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Point   _alongVector;
    bool    _compressedInterpolation;
};


/** @brief MultipleLayer is a Layer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CC_DLL LayerMultiplex : public Layer
{
public:
    /** creates and initializes a LayerMultiplex object 
     * @js NA
     * @lua NA
     */
    static LayerMultiplex* create();

    /** creates a LayerMultiplex with an array of layers.
     @since v2.1
     * @js NA
     */
    static LayerMultiplex* createWithArray(const Vector<Layer*>& arrayOfLayers);

    /** creates a LayerMultiplex with one or more layers using a variable argument list. 
     * @code
     * When this function bound to lua or js,the input params are changed.
     * In js:var create(...)
     * In lua:local create(...)
     * @endcode
     */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // WP8 in VS2012 does not support nullptr in variable args lists and variadic templates are also not supported
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

    /**
     * lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     * @js NA
     * @lua NA
     */
    static LayerMultiplex * createWithLayer(Layer* layer);


    void addLayer(Layer* layer);

    /** switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup=true'.
     */
    void switchTo(int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup=true'.
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
    
    virtual bool init();
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


// end of layer group
/// @}

NS_CC_END

#endif // __CCLAYER_H__


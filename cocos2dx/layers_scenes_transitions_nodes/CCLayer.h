/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "platform/CCAccelerometerDelegate.h"
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "cocoa/CCArray.h"
#ifdef EMSCRIPTEN
#include "base_nodes/CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

/**
 * @addtogroup layer
 * @{
 */

class TouchScriptHandlerEntry;

//
// Layer
//
/** @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL Layer : public Node, public TouchDelegate, public KeypadDelegate
{
public:    
    /** creates a fullscreen black layer */
    static Layer *create(void);
    Layer();
    virtual ~Layer();
    virtual bool init();
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(Touch *touch, Event *event);
    virtual void ccTouchMoved(Touch *touch, Event *event);
    virtual void ccTouchEnded(Touch *touch, Event *event);
    virtual void ccTouchCancelled(Touch *touch, Event *event);

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(Set *touches, Event *event);
    virtual void ccTouchesMoved(Set *touches, Event *event);
    virtual void ccTouchesEnded(Set *touches, Event *event);
    virtual void ccTouchesCancelled(Set *touches, Event *event);
    
    virtual void didAccelerate(Acceleration* accelerationValue);

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
    virtual void registerWithTouchDispatcher(void);

    /** whether or not it will receive Touch events.
    You can enable / disable touch events with this property.
    Only the touches of this node will be affected. This "method" is not propagated to it's children.
    @since v0.8.1
    */
    virtual bool isTouchEnabled() const;
    virtual void setTouchEnabled(bool value);
    
    virtual void setTouchMode(Touch::DispatchMode mode);
    virtual Touch::DispatchMode getTouchMode() const;
    
    /** priority of the touch events. Default is 0 */
    virtual void setTouchPriority(int priority);
    virtual int getTouchPriority() const;

    /** swallowsTouches of the touch events. Default is true */
    virtual void setSwallowsTouches(bool swallowsTouches);
    virtual bool isSwallowsTouches() const;

    /** whether or not it will receive Accelerometer events
    You can enable / disable accelerometer events with this property.
    @since v0.8.1
    */
    virtual bool isAccelerometerEnabled() const;
    virtual void setAccelerometerEnabled(bool value);
    virtual void setAccelerometerInterval(double interval);

    /** whether or not it will receive keyboard or keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */

    virtual bool isKeyboardEnabled() const;
    virtual void setKeyboardEnabled(bool value);
    virtual void keyPressed(int keyCode) {};
    virtual void keyReleased(int keyCode) {};

    virtual bool isKeypadEnabled() const;
    virtual void setKeypadEnabled(bool value);

    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);
    //
    // Overrides
    //
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onEnterTransitionDidFinish() override;

protected:
    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keyboardEnabled;
    bool _keypadEnabled;
    
private:
    int _touchPriority;
    Touch::DispatchMode _touchMode;
    bool _swallowsTouches;
    
    int executeScriptTouchHandler(int eventType, Touch* touch);
    int executeScriptTouchesHandler(int eventType, Set* touches);
};

#ifdef __apple__
#pragma mark -
#pragma mark LayerRGBA
#endif

/** LayerRGBA is a subclass of Layer that implements the RGBAProtocol protocol using a solid color as the background.
 
 All features from Layer are valid, plus the following new features that propagate into children that conform to the RGBAProtocol:
 - opacity
 - RGB colors
 @since 2.1
 */
class CC_DLL LayerRGBA : public Layer, public RGBAProtocol
{
public:
    CREATE_FUNC(LayerRGBA);
    
    LayerRGBA();
    virtual ~LayerRGBA();
    
    virtual bool init();

    //
    // Overrides
    //
    virtual GLubyte getOpacity() const override;
    virtual GLubyte getDisplayedOpacity() const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual bool isCascadeOpacityEnabled() const override;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override;
    
    virtual const Color3B& getColor() const override;
    virtual const Color3B& getDisplayedColor() const override;
    virtual void setColor(const Color3B& color) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual bool isCascadeColorEnabled() const override;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override;
    
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB() const override { return false; }
protected:
	GLubyte		_displayedOpacity, _realOpacity;
	Color3B	    _displayedColor, _realColor;
	bool		_cascadeOpacityEnabled, _cascadeColorEnabled;
};

//
// LayerColor
//
/** @brief LayerColor is a subclass of Layer that implements the RGBAProtocol protocol.

All features from Layer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CC_DLL LayerColor : public LayerRGBA, public BlendProtocol
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

    LayerColor();
    virtual ~LayerColor();

    virtual bool init();
    /** initializes a Layer with color, width and height in Points */
    bool initWithColor(const Color4B& color, GLfloat width, GLfloat height);
    /** initializes a Layer with color. Width and height are the window size. */
    bool initWithColor(const Color4B& color);

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
    virtual void draw() override;
    virtual void setColor(const Color3B &color) override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setContentSize(const Size & var) override;
    /** BlendFunction. Conforms to BlendProtocol protocol */
    virtual const BlendFunc& getBlendFunc() const override;
    virtual void setBlendFunc(const BlendFunc& blendFunc) override;

protected:
    virtual void updateColor();

    BlendFunc _blendFunc;
    Vertex2F _squareVertices[4];
    Color4F  _squareColors[4];
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

    virtual bool init();
    /** Initializes the Layer with a gradient between start and end. */
    bool initWithColor(const Color4B& start, const Color4B& end);

    /** Initializes the Layer with a gradient between start and end in the direction of v. */
    bool initWithColor(const Color4B& start, const Color4B& end, const Point& v);
    
    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
     Default: YES
     */
    void setCompressedInterpolation(bool bCompressedInterpolation);
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
    /** creates and initializes a LayerMultiplex object */
    static LayerMultiplex* create();

    /** creates a LayerMultiplex with an array of layers.
     @since v2.1
     */
    static LayerMultiplex* createWithArray(Array* arrayOfLayers);

    /** creates a LayerMultiplex with one or more layers using a variable argument list. */
    static LayerMultiplex * create(Layer* layer, ... );

    /**
     * lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     */
    static LayerMultiplex * createWithLayer(Layer* layer);

    LayerMultiplex();
    virtual ~LayerMultiplex();

    /** initializes a MultiplexLayer with one or more layers using a variable argument list. */
    bool initWithLayers(Layer* layer, va_list params);

    /** initializes a MultiplexLayer with an array of layers
     @since v2.1
     */
    bool initWithArray(Array* arrayOfLayers);

    void addLayer(Layer* layer);

    /** switches to a certain layer indexed by n.
     The current (old) layer will be removed from it's parent with 'cleanup:YES'.
     */
    void switchTo(unsigned int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup:YES'.
    */
    void switchToAndReleaseMe(unsigned int n);

protected:
    unsigned int _enabledLayer;
    Array*     _layers;
};


// end of layer group
/// @}

NS_CC_END

#endif // __CCLAYER_H__


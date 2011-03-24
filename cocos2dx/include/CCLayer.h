/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#include "CCTouchDelegateProtocol.h"
#include "CCAccelerometerDelegate.h"
#include "CCKeypadDelegate.h"
#include "CCMouseEventDelegate.h"
#include "CCKeyboardEventDelegate.h"

namespace   cocos2d {

//
// CCLayer
//
/** @brief CCLayer is a subclass of CCNode that implements the TouchEventsDelegate protocol.

All features from CCNode are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL CCLayer : public CCNode, public CCTouchDelegate, public CCAccelerometerDelegate, public CCKeypadDelegate, public CCKeyboardEventDelegate, public CCMouseEventDelegate
{
public:
	CCLayer();
	virtual ~CCLayer();
	bool init();
	static CCLayer *node(void);

	virtual void onEnter();
	virtual void onExit();
    virtual void onEnterTransitionDidFinish();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void destroy(void);
	virtual void keep(void);
	
    virtual void didAccelerate(CCAcceleration* pAccelerationValue) {}
    virtual void AccelerometerDestroy(void);
    virtual void AccelerometerKeep(void);

    virtual void KeypadDestroy();
    virtual void KeypadKeep();

    virtual void KeyboardDestroy(void);
    virtual void KeyboardKeep(void);

    virtual void MouseDestroy();
    virtual void MouseKeep();

	/** If isTouchEnabled, this method is called onEnter. Override it to change the
	way CCLayer receives touch events.
	( Default: CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
	Example:
	void CCLayer::registerWithTouchDispatcher()
	{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
	}
	@since v0.8.0
	*/
	virtual void registerWithTouchDispatcher(void);

    /** priority of the mouse event delegate.
    Default 0.
    Override this method to set another priority.
    @since v0.99.5
    */
    virtual int mouseDelegatePriority() { return 0; }

    /** priority of the keyboard event delegate.
    Default 0.
    Override this method to set another priority.
    @since v0.99.5
    */
    virtual int keyboardDelegatePriority() { return 0; }

	/** whether or not it will receive Touch events.
	You can enable / disable touch events with this property.
	Only the touches of this node will be affected. This "method" is not propagated to it's children.
	@since v0.8.1
	*/
	CC_PROPERTY(bool, m_bIsTouchEnabled, IsTouchEnabled)
	/** whether or not it will receive Accelerometer events
	You can enable / disable accelerometer events with this property.
	@since v0.8.1
	*/
	CC_PROPERTY(bool, m_bIsAccelerometerEnabled, IsAccelerometerEnabled)
    /** whether or not it will receive Keyboard events
    You can enable / disable Keyboard events with this property.
    @since v0.99.5
    */
    CC_PROPERTY(bool, m_bIsKeyboardEnabled, IsKeyboardEnabled)
    /** whether or not it will receive mouse events
    You can enable / disable mouse events with this property.
    @since v0.99.5
    */
    CC_PROPERTY(bool, m_bIsMouseEnabled, IsMouseEnabled)
    /** whether or not it will receive keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */
    CC_PROPERTY(bool, m_bIsKeypadEnabled, IsKeypadEnabled)
};

//
// CCLayerColor
//
/** @brief CCLayerColor is a subclass of CCLayer that implements the CCRGBAProtocol protocol.

All features from CCLayer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CC_DLL CCLayerColor : public CCLayer , public CCRGBAProtocol, public CCBlendProtocol
{
protected:
	GLfloat m_pSquareVertices[4 * 2];
	GLubyte m_pSquareColors[4 * 4];

public:

	CCLayerColor();
	virtual ~CCLayerColor();

	virtual void draw();
	virtual void setContentSize(CCSize var);

	/** creates a CCLayer with color, width and height in Points */
	static CCLayerColor * layerWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
	/** creates a CCLayer with color. Width and height are the window size. */
	static CCLayerColor * layerWithColor(ccColor4B color);

	/** initializes a CCLayer with color, width and height in Points */
	virtual bool initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
	/** initializes a CCLayer with color. Width and height are the window size. */
	virtual bool initWithColor(ccColor4B color);

	/** change width in Points*/
	void changeWidth(GLfloat w);
	/** change height in Points*/
	void changeHeight(GLfloat h);
	/** change width and height in Points
	@since v0.8
	*/
	void changeWidthAndHeight(GLfloat w ,GLfloat h);

	/** Opacity: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY(GLubyte, m_cOpacity, Opacity)
	/** Opacity: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY(ccColor3B, m_tColor, Color)
	/** BlendFunction. Conforms to CCBlendProtocol protocol */
	CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)

	virtual CCRGBAProtocol* convertToRGBAProtocol() { return (CCRGBAProtocol*)this; }

protected:
	virtual void updateColor();
};

/** CCColorLayer
It is the same as CCLayerColor.

@deprecated Use CCLayerColor instead. This class will be removed in v1.0.1
*/
class CCColorLayer : public CCLayerColor
{

};

//
// CCLayerGradient
//
/** CCLayerGradient is a subclass of CCLayerColor that draws gradients across
the background.

All features from CCLayerColor are valid, plus the following new features:
- direction
- final color

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.

Given the nature of
the interpolation, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.

@since v0.99.5
*/
class CC_DLL CCLayerGradient : public CCLayerColor
{
public:
    /** Creates a full-screen CCLayer with a gradient between start and end. */
    static CCLayerGradient* layerWithColor(ccColor4B start, ccColor4B end);

    /** Creates a full-screen CCLayer with a gradient between start and end in the direction of v. */
    static CCLayerGradient* layerWithColor(ccColor4B start, ccColor4B end, CCPoint v);

    /** Initializes the CCLayer with a gradient between start and end. */
    virtual bool initWithColor(ccColor4B start, ccColor4B end);

    /** Initializes the CCLayer with a gradient between start and end in the direction of v. */
    virtual bool initWithColor(ccColor4B start, ccColor4B end, CCPoint v);

    ccColor3B getStartColor();
    void      setStartColor(ccColor3B colors);

    CC_PROPERTY(ccColor3B, m_endColor, EndColor)
    CC_PROPERTY(GLubyte, m_cStartOpacity, StartOpacity)
    CC_PROPERTY(GLubyte, m_cEndOpacity, EndOpacity)
    CC_PROPERTY(CCPoint, m_AlongVector, Vector)

protected:
    virtual void updateColor();
};

/** @brief CCMultipleLayer is a CCLayer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CC_DLL CCMultiplexLayer : public CCLayer
{
protected:
	unsigned int m_nEnabledLayer;
	CCMutableArray<CCLayer *> * m_pLayers;
public:

	CCMultiplexLayer();
	virtual ~CCMultiplexLayer();

	/** creates a CCMultiplexLayer with one or more layers using a variable argument list. */
	static CCMultiplexLayer * layerWithLayers(CCLayer* layer, ... );
	/** initializes a MultiplexLayer with one or more layers using a variable argument list. */
	bool initWithLayers(CCLayer* layer, va_list params);
	/** switches to a certain layer indexed by n. 
	The current (old) layer will be removed from it's parent with 'cleanup:YES'.
	*/
	void switchTo(unsigned int n);
	/** release the current layer and switches to another layer indexed by n.
	The current (old) layer will be removed from it's parent with 'cleanup:YES'.
	*/
	void switchToAndReleaseMe(unsigned int n);
};
}//namespace   cocos2d 

// for the subclass of CCLayer, each has to implement the static "node" method 
#define LAYER_NODE_FUNC(layer) \
static layer* node() \
{ \
	layer *pRet = new layer(); \
	if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}; 

#endif // __CCLAYER_H__


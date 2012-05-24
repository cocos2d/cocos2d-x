/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

#include "CCNode.h"
#include "CCProtocols.h"
#include "CCTouchDelegateProtocol.h"
#include "CCAccelerometerDelegate.h"
#include "CCKeypadDelegate.h"
#include "CCMutableArray.h"

namespace   cocos2d {

class CCTouchScriptHandlerEntry;

//
// CCLayer
//
/** @brief CCLayer is a subclass of CCNode that implements the TouchEventsDelegate protocol.

All features from CCNode are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL CCLayer : public CCNode, public CCTouchDelegate, public CCAccelerometerDelegate, public CCKeypadDelegate
{
public:
	CCLayer();
	virtual ~CCLayer();
	bool init();
	static CCLayer *node(void);

	virtual void onEnter();
	virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    // default implements are used to call script callback if exist
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// default implements are used to call script callback if exist
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	
    virtual void didAccelerate(CCAcceleration* pAccelerationValue) {CC_UNUSED_PARAM(pAccelerationValue);}

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
    
    /** Register script touch events handler */
    void registerScriptTouchHandler(int nHandler, bool bIsMultiTouches = false, int nPriority = INT_MIN, bool bSwallowsTouches = false);
    /** Unregister script touch events handler */
    void unregisterScriptTouchHandler(void);

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
    /** whether or not it will receive keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */
    CC_PROPERTY(bool, m_bIsKeypadEnabled, IsKeypadEnabled)
    
private:
    // Script touch events handler
    CCTouchScriptHandlerEntry* m_pScriptHandlerEntry;
    int  excuteScriptTouchHandler(int nEventType, CCTouch *pTouch);
    int  excuteScriptTouchHandler(int nEventType, CCSet *pTouches);
};
    
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

#define LAYER_NODE_FUNC_PARAM(layer,__PARAMTYPE__,__PARAM__) \
	static layer* node(__PARAMTYPE__ __PARAM__) \
{ \
	layer *pRet = new layer(); \
	if (pRet && pRet->init(__PARAM__)) \
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
	ccVertex2F m_pSquareVertices[4];
	ccColor4B  m_pSquareColors[4];

public:

	CCLayerColor();
	virtual ~CCLayerColor();

	virtual void draw();
	virtual void setContentSize(const CCSize& var);

	/** creates a CCLayer with color, width and height in Points */
	static CCLayerColor * layerWithColorWidthHeight(const ccColor4B& color, GLfloat width, GLfloat height);
	/** creates a CCLayer with color. Width and height are the window size. */
	static CCLayerColor * layerWithColor(const ccColor4B& color);

	/** initializes a CCLayer with color, width and height in Points */
	virtual bool initWithColorWidthHeight(const ccColor4B& color, GLfloat width, GLfloat height);
	/** initializes a CCLayer with color. Width and height are the window size. */
	virtual bool initWithColor(const ccColor4B& color);

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
	/** Color: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color)
	/** BlendFunction. Conforms to CCBlendProtocol protocol */
	CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)

	virtual void setIsOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool getIsOpacityModifyRGB(void) { return false;}
    LAYER_NODE_FUNC(CCLayerColor);
    
protected:
	virtual void updateColor();
};

//
// CCLayerGradient
//
/** CCLayerGradient is a subclass of CCLayerColor that draws gradients across
the background.

All features from CCLayerColor are valid, plus the following new features:
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
class CC_DLL CCLayerGradient : public CCLayerColor
{
public:
    /** Creates a full-screen CCLayer with a gradient between start and end. */
    static CCLayerGradient* layerWithColor(const ccColor4B& start, const ccColor4B& end);

    /** Creates a full-screen CCLayer with a gradient between start and end in the direction of v. */
    static CCLayerGradient* layerWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

    /** Initializes the CCLayer with a gradient between start and end. */
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end);

    /** Initializes the CCLayer with a gradient between start and end in the direction of v. */
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_startColor, StartColor)
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_endColor, EndColor)
    CC_PROPERTY(GLubyte, m_cStartOpacity, StartOpacity)
    CC_PROPERTY(GLubyte, m_cEndOpacity, EndOpacity)
	CC_PROPERTY_PASS_BY_REF(CCPoint, m_AlongVector, Vector)

    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
    Default: YES
    */
    CC_PROPERTY(bool, m_bCompressedInterpolation, IsCompressedInterpolation)

    LAYER_NODE_FUNC(CCLayerGradient);
protected:
    virtual void updateColor();
};

/** @brief CCMultipleLayer is a CCLayer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CC_DLL CCLayerMultiplex : public CCLayer
{
protected:
	unsigned int m_nEnabledLayer;
	CCMutableArray<CCLayer *> * m_pLayers;
public:

	CCLayerMultiplex();
	virtual ~CCLayerMultiplex();

	/** creates a CCLayerMultiplex with one or more layers using a variable argument list. */
	static CCLayerMultiplex * layerWithLayers(CCLayer* layer, ... );

    /**
	 * lua script can not init with undetermined number of variables
	 * so add these functinons to be used with lua.
	 */
	static CCLayerMultiplex * layerWithLayer(CCLayer* layer);
	void addLayer(CCLayer* layer);
	bool initWithLayer(CCLayer* layer);

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
    
    LAYER_NODE_FUNC(CCLayerMultiplex);
};

}//namespace   cocos2d 

#endif // __CCLAYER_H__


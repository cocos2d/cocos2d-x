/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "Cocos2dDefine.h"
#include "CCNode.h"
#include "CCProtocols.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "ccxCommon.h"
namespace   cocos2d {

//
// CCLayer
//
/** CCLayer is a subclass of CCNode that implements the TouchEventsDelegate protocol.

All features from CCNode are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
/// @todo public UIAccelerometerDelegate
class CCX_DLL CCLayer : public CCNode, public CCStandardTouchDelegate, public CCTargetedTouchDelegate//, public UIAccelerometerDelegate
{
public:
	CCLayer();
	virtual ~CCLayer();
	bool init();
	static CCLayer *node(void);

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent);
	
	/** If isTouchEnabled, this method is called onEnter. Override it to change the
	way CCLayer receives touch events.
	( Default: [[TouchDispatcher sharedDispatcher] addStandardDelegate:self priority:0] )
	Example:
	-(void) registerWithTouchDispatcher
	{
	[[TouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:INT_MIN+1 swallowsTouches:YES];
	}
	@since v0.8.0
	*/
	void registerWithTouchDispatcher(void);

	/** whether or not it will receive Touch events.
	You can enable / disable touch events with this property.
	Only the touches of this node will be affected. This "method" is not propagated to it's children.
	@since v0.8.1
	*/
	CCX_PROPERTY(bool, m_bIsTouchEnabled, IsTouchEnabled)
	/** whether or not it will receive Accelerometer events
	You can enable / disable accelerometer events with this property.
	@since v0.8.1
	*/
	CCX_PROPERTY(bool, m_bIsAccelerometerEnabled, IsAccelerometerEnabled)
};

//
// CCColorLayer
//
/** CCColorLayer is a subclass of CCLayer that implements the CCRGBAProtocol protocol.

All features from CCLayer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CCColorLayer : public CCLayer , public CCRGBAProtocol, public CCBlendProtocol
{
protected:
	GLfloat m_pSquareVertices[4 * 2];
	GLubyte m_pSquareColors[4 * 4];

public:

	CCColorLayer();
	virtual ~CCColorLayer();

	virtual void draw();
	virtual void setContentSize(CGSize var);

	/** creates a CCLayer with color, width and height */
	static CCColorLayer * layerWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
	/** creates a CCLayer with color. Width and height are the window size. */
	static CCColorLayer * layerWithColor(ccColor4B color);

	/** initializes a CCLayer with color, width and height */
	CCColorLayer * initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height);
	/** initializes a CCLayer with color. Width and height are the window size. */
	CCColorLayer * initWithColor(ccColor4B color);

	/** change width */
	void changeWidth(GLfloat w);
	/** change height */
	void changeHeight(GLfloat h);
	/** change width and height
	@since v0.8
	*/
	void changeWidthAndHeight(GLfloat w ,GLfloat h);

	/** Opacity: conforms to CCRGBAProtocol protocol */
	CCX_PROPERTY(GLubyte, m_cOpacity, Opacity)
	/** Opacity: conforms to CCRGBAProtocol protocol */
	CCX_PROPERTY(ccColor3B, m_tColor, Color)
	/** BlendFunction. Conforms to CCBlendProtocol protocol */
	CCX_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)

private :
	void updateColor();
};

/** CCMultipleLayer is a CCLayer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CCMultiplexLayer : public CCLayer
{
protected:
	unsigned int m_nEnabledLayer;
	NSMutableArray<CCLayer *> * m_pLayers;
public:

	CCMultiplexLayer();
	virtual ~CCMultiplexLayer();

	/** creates a CCMultiplexLayer with one or more layers using a variable argument list. */
	static CCMultiplexLayer * layerWithLayers(CCLayer* layer, ... );
	/** initializes a MultiplexLayer with one or more layers using a variable argument list. */
	CCMultiplexLayer * initWithLayers(CCLayer* layer, va_list params);
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

#endif // __CCLAYER_H__


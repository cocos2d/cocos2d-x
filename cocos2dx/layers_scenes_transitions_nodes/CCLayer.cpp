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

#include "CCLayer.h"

using namespace std;

// CCLayer
CCLayer::CCLayer()
{
	/// @todo
}

CCLayer::~CCLayer()
{
	/// @todo
}


/// Touch and Accelerometer related

void CCLayer::registerWithTouchDispatcher()
{
	/// @todo [[CCTouchDispatcher sharedDispatcher] addStandardDelegate:self priority:0];
}


/// isTouchEnabled getter
bool CCLayer::getIsTouchEnabled()
{
	return m_bIsTouchEnabled;
}
/// isTouchEnabled setter
void CCLayer::setIsTouchEnabled(bool enabled)
{
	/** @todo
	if( isTouchEnabled != enabled ) {
	isTouchEnabled = enabled;
	if( isRunning_ ) {
	if( enabled )
	[self registerWithTouchDispatcher];
	else
	[[CCTouchDispatcher sharedDispatcher] removeDelegate:self];
	}
	}*/
}

/// isAccelerometerEnabled getter
bool CCLayer::getIsAccelerometerEnabled()
{
	return m_bIsAccelerometerEnabled;
}
/// isAccelerometerEnabled setter
void CCLayer::setIsAccelerometerEnabled(bool enabled)
{
	/** @todo
	if( enabled != isAccelerometerEnabled ) {
		isAccelerometerEnabled = enabled;
		if( isRunning_ ) {
			if( enabled )
				[[UIAccelerometer sharedAccelerometer] setDelegate:self];
			else
				[[UIAccelerometer sharedAccelerometer] setDelegate:nil];
		}
	}*/
}


/// Callbacks
void CCLayer::onEnter()
{
	/** @todo
	// register 'parent' nodes first
	// since events are propagated in reverse order
	if (isTouchEnabled)
		[self registerWithTouchDispatcher];

	// then iterate over all the children
	[super onEnter];

	if( isAccelerometerEnabled )
		[[UIAccelerometer sharedAccelerometer] setDelegate:self];*/
}

void CCLayer::onExit()
{
	/**
	if( isTouchEnabled )
		[[CCTouchDispatcher sharedDispatcher] removeDelegate:self];

	if( isAccelerometerEnabled )
		[[UIAccelerometer sharedAccelerometer] setDelegate:nil];

	[super onExit];*/
}

/** @todo
-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
	NSAssert(NO, @"Layer#ccTouchBegan override me");
	return YES;
}*/

/// ColorLayer


CCColorLayer::CCColorLayer()
{
/// @todo
}
CCColorLayer::~CCColorLayer()
{
/// @todo
}

// Opacity and RGB color protocol
/// opacity getter
GLubyte CCColorLayer::getOpacity()
{
	return m_cOpacity;
}
/// opacity setter
void CCColorLayer::setOpacity(GLubyte var)
{
	m_cOpacity = var;
	updateColor();
}

/// color getter
ccColor3B CCColorLayer::getColor()
{
	return m_tColor;
}

/// color setter
void CCColorLayer::setColor(ccColor3B var)
{
	m_tColor = var;
	updateColor();
}


/// blendFunc getter
ccBlendFunc CCColorLayer::getBlendFunc()
{
	return m_tBlendFunc;
}
/// blendFunc setter
void CCColorLayer::setBlendFunc(ccBlendFunc var)
{
	m_tBlendFunc = var;
}


CCColorLayer * CCColorLayer::layerWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	CCColorLayer * pLayer = new CCColorLayer();
	pLayer->initWithColorWidthHeight(color,width,height);
	pLayer->autorelease();
	return pLayer;
}
CCColorLayer * CCColorLayer::layerWithColor(ccColor4B color)
{
	CCColorLayer * pLayer = new CCColorLayer();
	pLayer->initWithColor(color);
	pLayer->autorelease();
	return pLayer;
}

CCColorLayer* CCColorLayer::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	/** @todo
	if( (self=[super init]) ) {

		// default blend function
		blendFunc_ = (ccBlendFunc) { CC_BLEND_SRC, CC_BLEND_DST };

		color_.r = color.r;
		color_.g = color.g;
		color_.b = color.b;
		opacity_ = color.a;

		for (NSUInteger i=0; i<sizeof(squareVertices) / sizeof( squareVertices[0]); i++ )
			squareVertices[i] = 0.0f;

		[self updateColor];
		[self setContentSize:CGSizeMake(w,h)];
	}
	return self;*/
	return NULL;
}

CCColorLayer * CCColorLayer::initWithColor(ccColor4B color)
{
	/** @todo
	CGSize s = [[CCDirector sharedDirector] winSize];
	return [self initWithColor:color width:s.width height:s.height];*/
	return NULL;
}

/// override contentSize
void CCColorLayer::setContentSize(CGSize size)
{
	/** @todo
	squareVertices[2] = size.width;
	squareVertices[5] = size.height;
	squareVertices[6] = size.width;
	squareVertices[7] = size.height;

	[super setContentSize:size];*/
}

void CCColorLayer::changeWidthAndHeight(GLfloat w ,GLfloat h)
{
 /// @todo	[self setContentSize:CGSizeMake(w,h)];
}

void CCColorLayer::changeWidth(GLfloat w)
{
/// @todo	[self setContentSize:CGSizeMake(w,contentSize_.height)];
}

void CCColorLayer::changeHeight(GLfloat h)
{
/// @todo	[self setContentSize:CGSizeMake(contentSize_.width,h)];
}

void CCColorLayer::updateColor()
{
	/** @todo
	for( NSUInteger i=0; i < sizeof(squareColors) / sizeof(squareColors[0]);i++ )
	{
		if( i % 4 == 0 )
			squareColors[i] = color_.r;
		else if( i % 4 == 1)
			squareColors[i] = color_.g;
		else if( i % 4 ==2  )
			squareColors[i] = color_.b;
		else
			squareColors[i] = opacity_;
	}*/
}

void CCColorLayer::draw()
{		
	/** @todo
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, GL_COLOR_ARRAY
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glVertexPointer(2, GL_FLOAT, 0, squareVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);

	BOOL newBlend = NO;
	if( blendFunc_.src != CC_BLEND_SRC || blendFunc_.dst != CC_BLEND_DST ) {
		newBlend = YES;
		glBlendFunc(blendFunc_.src, blendFunc_.dst);
	}
	else if( opacity_ != 255 ) {
		newBlend = YES;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if( newBlend )
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

	// restore default GL state
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);*/
}


/// MultiplexLayer

CCMultiplexLayer::CCMultiplexLayer()
{
/// @todo
}
CCMultiplexLayer::~CCMultiplexLayer()
{
	/// @todo
}

CCMultiplexLayer * CCMultiplexLayer::layerWithLayers(CCLayer * layer, ...)
{
/** @todo	va_list args;
	va_start(args,layer);

	id s = [[[self alloc] initWithLayers: layer vaList:args] autorelease];

	va_end(args);
	return s;*/
	return NULL;
}

CCMultiplexLayer * CCMultiplexLayer::initWithLayers(CCLayer *layer, va_list params)
{
	/** @todo
	if( (self=[super init]) ) {

		layers = [[NSMutableArray arrayWithCapacity:5] retain];

		[layers addObject: layer];

		CCLayer *l = va_arg(params,CCLayer*);
		while( l ) {
			[layers addObject: l];
			l = va_arg(params,CCLayer*);
		}

		enabledLayer = 0;
		[self addChild: [layers objectAtIndex: enabledLayer]];	
	}

	return self;*/
	return NULL;
}

/** @todo
-(void) dealloc
{
	[layers release];
	[super dealloc];
}*/

void CCMultiplexLayer::switchTo(unsigned int n)
{
	/** @todo
	NSAssert( n < [layers count], @"Invalid index in MultiplexLayer switchTo message" );

	[self removeChild: [layers objectAtIndex:enabledLayer] cleanup:YES];

	enabledLayer = n;

	[self addChild: [layers objectAtIndex:n]];		*/
}

void CCMultiplexLayer::switchToAndReleaseMe(unsigned int n)
{
	/** @todo
	NSAssert( n < [layers count], @"Invalid index in MultiplexLayer switchTo message" );

	[self removeChild: [layers objectAtIndex:enabledLayer] cleanup:YES];

	[layers replaceObjectAtIndex:enabledLayer withObject:[NSNull null]];

	enabledLayer = n;

	[self addChild: [layers objectAtIndex:n]];		*/
}

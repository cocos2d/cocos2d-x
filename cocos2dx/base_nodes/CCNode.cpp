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

#include "CCNode.h"

using namespace std;

CCNode::CCNode(void)
:m_bIsRunning(false)
,m_fRotation(0.0f)
,m_fScaleX(1.0f)
,m_fScaleY(1.0f)
,m_tPosition(CGPoint(0,0))
,m_tAnchorPointInPixels(CGPoint(0,0))
,m_tAnchorPoint(CGPoint(0,0))
,m_tContentSize(CGSize(0,0))
// "whole screen" objects. like Scenes and Layers, should set isRelativeAnchorPoint to false
,m_bIsRelativeAnchorPoint(true)
,m_bIsTransformDirty(true)
,m_bIsInverseDirty(true)
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
,m_bIsTransformGLDirty(true)
#endif
,m_fVertexZ(0.0f)
,m_pGrid(NULL)
,m_bIsVisible(true)
,m_iTag(kCCNodeTagInvalid)
,m_iZOrder(0)
// lazy alloc
,m_pCamera(NULL)
// children (lazy allocs)
,m_pChildren(NULL)
// userData is always inited as nil
,m_pUserData(NULL)
{
    // nothing
}
/// @todo
CCNode::~CCNode()
{

}

float CCNode::getRotation()
{
	return m_fRotation;
}

CGPoint CCNode::getPosition()
{
	return m_tPosition;
}

float CCNode::getScaleX()
{
	return m_fScaleX;
}

float CCNode::getScaleY()
{
	return m_fScaleY;
}

void CCNode::setVisibility(bool bIsVisible)
{
	m_bIsVisible = bIsVisible;
}

bool CCNode::getVisibility()
{
	return m_bIsVisible;
}
/// @todo
//CCGridBase* CCNode::getGrid()
//{
//	return m_pGrid;
//}
/// @todo
//void CCNode::setGrid(CCGridBase* pGrid)
//{
//	if(/*!pGrid &&*/ m_pGrid)
//		m_pGrid->release();
//
//	m_pGrid = pGrid;
//
//	if(m_pGrid)
//		m_pGrid->retain();
//}


// getters synthesized, setters explicit
void CCNode::setRotation(float newRotation)
{
	m_fRotation = newRotation;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setScaleX(float newScaleX)
{
	m_fScaleX = newScaleX;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setScaleY(float newScaleY)
{
	m_fScaleY = newScaleY;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setPosition(CGPoint newPosition)
{
	m_tPosition = newPosition;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

void CCNode::setIsRelativeAnchorPoint(bool newValue)
{
	m_bIsRelativeAnchorPoint = newValue;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

bool CCNode::getIsRelativeAnchorPoint()
{
	return m_bIsRelativeAnchorPoint;
}
/// @todo
void CCNode::setAnchorPoint(CGPoint point)
{
	/*if( ! CGPointEqualToPoint(point, m_anchorPoint) ) 
	{
		m_anchorPoint = point;
		this->m_anchorPointInPixels = ccp( m_contentSize.width * m_anchorPoint.x, m_contentSize.height * m_anchorPoint.y );
		m_isTransformDirty = m_isInverseDirty = true;
		#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
			m_bIsTransformGLDirty = true;
		#endif
	}*/
}

CGPoint CCNode::getAnchorPoint()
{
	return m_tAnchorPoint;
}
/// @todo
void CCNode::setContentSize(CGSize size)
{
	//if( ! CGSizeEqualToSize(size, m_contentSize) ) 
	//{
	//	m_contentSize = size;
	//	m_anchorPointInPixels = ccp( m_contentSize.width * m_anchorPoint.x, m_contentSize.height * m_anchorPoint.y );
	//	m_isTransformDirty = m_isInverseDirty = true;
	//	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	//		m_bIsTransformGLDirty = true;
	//	#endif
	//}
}

CGSize CCNode::getContentSize()
{
	return m_tContentSize;
}
/// @todo
//CGRect CCNode::boundingBox()
//{
//	CGRect rect = CGRectMake(0, 0, m_contentSize.width, m_contentSize.height);
//	return CGRectApplyAffineTransform(rect, nodeToParentTransform());
//}
/// @todo
//float CCNode::scale()
//{
//	UXAssert( m_scaleX == m_scaleY, L"CocosNode#scale. ScaleX != ScaleY. Don't know which one to return");
//	return m_scaleX;
//}

void CCNode::setScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
	#endif
}

/// @todo
//UxMutableArray* CCNode::children()
//{
//	return m_pChildrenArray;
//}

void CCNode::setParent(CCNode* pParentNode)
{
	m_pParent = pParentNode;
}

CCNode* CCNode::getParent()
{
	return m_pParent;
}

int CCNode::getTag()
{
	return m_iTag;
}

void CCNode::setTag(int tag)
{
	m_iTag = tag;   
}

int CCNode::getZOrder()
{
	return m_iZOrder;
}

void CCNode::setVertexZ(float z)
{
	m_fVertexZ = z;
}

float CCNode::getVertexZ()
{
	return m_fVertexZ;
}

CGPoint CCNode::getAnchorPointInPixels()
{
	return m_tAnchorPointInPixels;
}

bool CCNode::getIsRunning()
{
	return m_bIsRunning;
}


/** @todo
#if CC_COCOSNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (int)
#endif
*/


/** @todo

@synthesize children = children_;
@synthesize visible=visible_;
@synthesize parent=parent_;
@synthesize grid=grid_;
@synthesize zOrder=zOrder_;
@synthesize tag=tag_;
@synthesize vertexZ = vertexZ_;
@synthesize isRunning=isRunning_;


@synthesize rotation=rotation_, scaleX=scaleX_, scaleY=scaleY_, position=position_;
@synthesize anchorPointInPixels=anchorPointInPixels_, isRelativeAnchorPoint=isRelativeAnchorPoint_;
@synthesize userData;
*/




float CCNode::getScale(void)
{
	///@todo NSAssert( scaleX_ == scaleY_, @"CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
	return m_fScale;
}


CCNode * CCNode::node(void)
{
/// @todo	return [[[self alloc] init] autorelease];
	return NULL;
}

void CCNode::cleanup()
{
	/** @todo
	// actions
	[self stopAllActions];
	[self unscheduleAllSelectors];

	// timers

	[children_ makeObjectsPerformSelector:@selector(cleanup)];*/
}
/** @todo  no declare in class
- (NSString*) description
{
	return [NSString stringWithFormat:@"<%@ = %08X | Tag = %i>", [self class], self, tag_];
}
*/
/** @todo no declare in class
- (void) dealloc
{
	CCLOGINFO( @"cocos2d: deallocing %@", self);

	// attributes
	[camera_ release];

	[grid_ release];

	// children

	for (CCNode *child in children_) {
		child.parent = nil;
	}

	[children_ release];


	[super dealloc];
}
*/

// lazy allocs
void CCNode::childrenAlloc(void)
{
	/// @todo children_ = [[CCArray alloc] initWithCapacity:4];
}
/** @todo  no declare in class
// camera: lazy alloc
CCCamera* camera
{
	if( ! camera_ ) {
		camera_ = [[CCCamera alloc] init];

		// by default, center camera at the Sprite's anchor point
		//		[camera_ setCenterX:anchorPointInPixels_.x centerY:anchorPointInPixels_.y centerZ:0];
		//		[camera_ setEyeX:anchorPointInPixels_.x eyeY:anchorPointInPixels_.y eyeZ:1];

		//		[camera_ setCenterX:0 centerY:0 centerZ:0];
		//		[camera_ setEyeX:0 eyeY:0 eyeZ:1];

	}

	return camera_;
}
*/
CCNode* CCNode::getChildByTag(int aTag)
{
	/** @todo
	NSAssert( aTag != kCCNodeTagInvalid, @"Invalid tag");

	for( CCNode *node in children_ ) {
		if( node.tag == aTag )
			return node;
	}
	// not found
	return nil;*/
	return NULL;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behaviour it only needs
* to override this method
*/
CCNode * CCNode::addChild(CCNode *node, int zOrder, int tag)
{	
	/** @todo
	NSAssert( child != nil, @"Argument must be non-nil");
	NSAssert( child.parent == nil, @"child already added. It can't be added again");

	if( ! children_ )
		[self childrenAlloc];

	[self insertChild:child z:z];

	child.tag = aTag;

	[child setParent: self];

	if( isRunning_ )
		[child onEnter];
	return self;*/
	return NULL;
}

CCNode * CCNode::addChild(CCNode *node, int zOrder)
{
	/** @todo
	NSAssert( child != nil, @"Argument must be non-nil");
	return [self addChild:child z:z tag:child.tag];*/
	return NULL;
}

CCNode * CCNode::addChild(CCNode *node)
{
	/** @todo
	NSAssert( child != nil, @"Argument must be non-nil");
	return [self addChild:child z:child.zOrder tag:child.tag];*/
	return NULL;
}

void CCNode::removeFromParentAndCleanup(bool cleanup)
{
	/** @todo
	[self.parent removeChild:self cleanup:cleanup];*/
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void CCNode::removeChild(CCNode* node, bool cleanup)
{
	/** @todo
	// explicit nil handling
	if (child == nil)
		return;

	if ( [children_ containsObject:child] )
		[self detachChild:child cleanup:cleanup];*/
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
	/** @todo
	NSAssert( aTag != kCCNodeTagInvalid, @"Invalid tag");

	CCNode *child = [self getChildByTag:aTag];

	if (child == nil)
		CCLOG(@"cocos2d: removeChildByTag: child not found!");
	else
		[self removeChild:child cleanup:cleanup];*/
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
	/** @todo
	// not using detachChild improves speed here
	for (CCNode *c in children_)
	{
		// IMPORTANT:
		//  -1st do onExit
		//  -2nd cleanup
		if (isRunning_)
			[c onExit];

		if (cleanup)
			[c cleanup];

		// set parent nil at the end (issue #476)
		[c setParent:nil];
	}

	[children_ removeAllObjects];*/
}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{
	/** @todo
	// IMPORTANT:
	//  -1st do onExit
	//  -2nd cleanup
	if (isRunning_)
		[child onExit];

	// If you don't do cleanup, the child's actions will not get removed and the
	// its scheduledSelectors_ dict will not get released!
	if (doCleanup)
		[child cleanup];

	// set parent nil at the end (issue #476)
	[child setParent:nil];

	[children_ removeObject:child];*/
}

// used internally to alter the zOrder variable. DON'T call this method manually
void CCNode::setZOrder(int z)
{
	m_iZOrder = z;
}

// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
	/** @todo
	int index=0;
	BOOL added = NO;
	for( CCNode *a in children_ ) {
		if ( a.zOrder > z ) {
			added = YES;
			[ children_ insertObject:child atIndex:index];
			break;
		}
		index++;
	}

	if( ! added )
		[children_ addObject:child];

	[child _setZOrder:z];*/
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
	/** @todo
	NSAssert( child != nil, @"Child must be non-nil");

	[child retain];
	[children_ removeObject:child];

	[self insertChild:child z:z];

	[child release];*/
}

void CCNode::draw()
{
	// override me
	// Only use this function to draw your staff.
	// DON'T draw your stuff outside this method
}

void CCNode::visit()
{
	/** @todo
	if (!visible_)
		return;

	glPushMatrix();

	if ( grid_ && grid_.active) {
		[grid_ beforeDraw];
		[self transformAncestors];
	}

	[self transform];

	ccArray *arrayData;
	int i = 0, nu;
	if(children_){
		arrayData = children_->data;
		nu = arrayData->num;
		for(;i<nu; i++){
			CCNode *child = arrayData->arr[i];
			if ( child.zOrder < 0 )
				[child visit];
			else
				break;
		}
	}

	[self draw];

	if(children_)
		for (;i<nu; i++)
			[arrayData->arr[i] visit];


	if ( grid_ && grid_.active)
		[grid_ afterDraw:self];

	glPopMatrix();*/
}

void CCNode::transformAncestors()
{
	if( m_pParent != NULL  )
	{
		m_pParent->transformAncestors();
		m_pParent->transform();
	}
}

void CCNode::transform()
{	
	/** @todo
	// transformations

#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	// BEGIN alternative -- using cached transform
	//
	if( isTransformGLDirty_ ) {
		CGAffineTransform t = [self nodeToParentTransform];
		CGAffineToGL(&t, transformGL_);
		isTransformGLDirty_ = NO;
	}

	glMultMatrixf(transformGL_);
	if( vertexZ_ )
		glTranslatef(0, 0, vertexZ_);

	// XXX: Expensive calls. Camera should be integrated into the cached affine matrix
	if ( camera_ && !(grid_ && grid_.active) ) {
		BOOL translate = (anchorPointInPixels_.x != 0.0f || anchorPointInPixels_.y != 0.0f);

		if( translate )
			glTranslatef(RENDER_IN_SUBPIXEL(anchorPointInPixels_.x), RENDER_IN_SUBPIXEL(anchorPointInPixels_.y), 0);

		[camera_ locate];

		if( translate )
			glTranslatef(RENDER_IN_SUBPIXEL(-anchorPointInPixels_.x), RENDER_IN_SUBPIXEL(-anchorPointInPixels_.y), 0);
	}


	// END alternative

#else
	// BEGIN original implementation
	// 
	// translate
	if ( isRelativeAnchorPoint_ && (anchorPointInPixels_.x != 0 || anchorPointInPixels_.y != 0 ) )
		glTranslatef( RENDER_IN_SUBPIXEL(-anchorPointInPixels_.x), RENDER_IN_SUBPIXEL(-anchorPointInPixels_.y), 0);

	if (anchorPointInPixels_.x != 0 || anchorPointInPixels_.y != 0)
		glTranslatef( RENDER_IN_SUBPIXEL(position_.x + anchorPointInPixels_.x), RENDER_IN_SUBPIXEL(position_.y + anchorPointInPixels_.y), vertexZ_);
	else if ( position_.x !=0 || position_.y !=0 || vertexZ_ != 0)
		glTranslatef( RENDER_IN_SUBPIXEL(position_.x), RENDER_IN_SUBPIXEL(position_.y), vertexZ_ );

	// rotate
	if (rotation_ != 0.0f )
		glRotatef( -rotation_, 0.0f, 0.0f, 1.0f );

	// scale
	if (scaleX_ != 1.0f || scaleY_ != 1.0f)
		glScalef( scaleX_, scaleY_, 1.0f );

	if ( camera_ && !(grid_ && grid_.active) )
		[camera_ locate];

	// restore and re-position point
	if (anchorPointInPixels_.x != 0.0f || anchorPointInPixels_.y != 0.0f)
		glTranslatef(RENDER_IN_SUBPIXEL(-anchorPointInPixels_.x), RENDER_IN_SUBPIXEL(-anchorPointInPixels_.y), 0);

	//
	// END original implementation
#endif
*/
}


void CCNode::onEnter()
{
	/** @todo callback?
	[children_ makeObjectsPerformSelector:@selector(onEnter)];

	[self resumeSchedulerAndActions];

	isRunning_ = YES;*/
}

void CCNode::onEnterTransitionDidFinish()
{
	/** @todo callback?
	[children_ makeObjectsPerformSelector:@selector(onEnterTransitionDidFinish)];*/
}

void CCNode::onExit()
{
	/** @todo callback?
	[self pauseSchedulerAndActions];

	isRunning_ = NO;	

	[children_ makeObjectsPerformSelector:@selector(onExit)];*/
}

/** @todo 
-(CCAction*) runAction:(CCAction*) action
{
	NSAssert( action != nil, @"Argument must be non-nil");

	[[CCActionManager sharedManager] addAction:action target:self paused:!isRunning_];
	return action;
}
*/

void CCNode::stopAllActions()
{
	/** @todo
	[[CCActionManager sharedManager] removeAllActionsFromTarget:self];*/
}

/** @todo
-(void) stopAction: (CCAction*) action
{
	[[CCActionManager sharedManager] removeAction:action];
}*/

void CCNode::stopActionByTag(int tag)
{
	/** @todo
	NSAssert( aTag != kCCActionTagInvalid, @"Invalid tag");
	[[CCActionManager sharedManager] removeActionByTag:aTag target:self];*/
}

/** @todo
-(CCAction*) getActionByTag:(int) aTag
{
	NSAssert( aTag != kCCActionTagInvalid, @"Invalid tag");

	return [[CCActionManager sharedManager] getActionByTag:aTag target:self];
}*/

int CCNode::numberOfRunningActions()
{
/// @todo	return [[CCActionManager sharedManager] numberOfRunningActionsInTarget:self];
	return 0;
}


/// @todo #pragma mark CCNode - Callbacks????

void CCNode::scheduleUpdate()
{
	scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
/// @todo	[[CCScheduler sharedScheduler] scheduleUpdateForTarget:self priority:priority paused:!isRunning_];
}

void CCNode::unscheduleUpdate()
{
/// @todo	[[CCScheduler sharedScheduler] unscheduleUpdateForTarget:self];
}

/** @todo
-(void) schedule:(SEL)selector
{
	[self schedule:selector interval:0];
}*/

/** @todo
-(void) schedule:(SEL)selector interval:(ccTime)interval
{
	NSAssert( selector != nil, @"Argument must be non-nil");
	NSAssert( interval >=0, @"Arguemnt must be positive");

	[[CCScheduler sharedScheduler] scheduleSelector:selector forTarget:self interval:interval paused:!isRunning_];
}*/

/** @todo
-(void) unschedule:(SEL)selector
{
	// explicit nil handling
	if (selector == nil)
		return;

	[[CCScheduler sharedScheduler] unscheduleSelector:selector forTarget:self];
}*/

void CCNode::unscheduleAllSelectors()
{
/// @todo	[[CCScheduler sharedScheduler] unscheduleAllSelectorsForTarget:self];
}

void CCNode::resumeSchedulerAndActions()
{
	/** @todo
	[[CCScheduler sharedScheduler] resumeTarget:self];
	[[CCActionManager sharedManager] resumeTarget:self];*/
}

void CCNode::pauseSchedulerAndActions()
{
	/** @todo
	[[CCScheduler sharedScheduler] pauseTarget:self];
	[[CCActionManager sharedManager] pauseTarget:self];*/
}

/** @todo
- (CGAffineTransform)nodeToParentTransform
{
	if ( isTransformDirty_ ) {

		transform_ = CGAffineTransformIdentity;

		if ( !isRelativeAnchorPoint_ && !CGPointEqualToPoint(anchorPointInPixels_, CGPointZero) )
			transform_ = CGAffineTransformTranslate(transform_, anchorPointInPixels_.x, anchorPointInPixels_.y);

		if( ! CGPointEqualToPoint(position_, CGPointZero) )
			transform_ = CGAffineTransformTranslate(transform_, position_.x, position_.y);
		if( rotation_ != 0 )
			transform_ = CGAffineTransformRotate(transform_, -CC_DEGREES_TO_RADIANS(rotation_));
		if( ! (scaleX_ == 1 && scaleY_ == 1) ) 
			transform_ = CGAffineTransformScale(transform_, scaleX_, scaleY_);

		if( ! CGPointEqualToPoint(anchorPointInPixels_, CGPointZero) )
			transform_ = CGAffineTransformTranslate(transform_, -anchorPointInPixels_.x, -anchorPointInPixels_.y);

		isTransformDirty_ = NO;
	}

	return transform_;
}

- (CGAffineTransform)parentToNodeTransform
{
	if ( isInverseDirty_ ) {
		inverse_ = CGAffineTransformInvert([self nodeToParentTransform]);
		isInverseDirty_ = NO;
	}

	return inverse_;
}

- (CGAffineTransform)nodeToWorldTransform
{
	CGAffineTransform t = [self nodeToParentTransform];

	for (CCNode *p = parent_; p != nil; p = p.parent)
		t = CGAffineTransformConcat(t, [p nodeToParentTransform]);

	return t;
}

- (CGAffineTransform)worldToNodeTransform
{
	return CGAffineTransformInvert([self nodeToWorldTransform]);
}

- (CGPoint)convertToNodeSpace:(CGPoint)worldPoint
{
	return CGPointApplyAffineTransform(worldPoint, [self worldToNodeTransform]);
}

- (CGPoint)convertToWorldSpace:(CGPoint)nodePoint
{
	return CGPointApplyAffineTransform(nodePoint, [self nodeToWorldTransform]);
}

- (CGPoint)convertToNodeSpaceAR:(CGPoint)worldPoint
{
	CGPoint nodePoint = [self convertToNodeSpace:worldPoint];
	return ccpSub(nodePoint, anchorPointInPixels_);
}

- (CGPoint)convertToWorldSpaceAR:(CGPoint)nodePoint
{
	nodePoint = ccpAdd(nodePoint, anchorPointInPixels_);
	return [self convertToWorldSpace:nodePoint];
}

- (CGPoint)convertToWindowSpace:(CGPoint)nodePoint
{
	CGPoint worldPoint = [self convertToWorldSpace:nodePoint];
	return [[CCDirector sharedDirector] convertToUI:worldPoint];
}

// convenience methods which take a UITouch instead of CGPoint

- (CGPoint)convertTouchToNodeSpace:(UITouch *)touch
{
	CGPoint point = [touch locationInView: [touch view]];
	point = [[CCDirector sharedDirector] convertToGL: point];
	return [self convertToNodeSpace:point];
}

- (CGPoint)convertTouchToNodeSpaceAR:(UITouch *)touch
{
	CGPoint point = [touch locationInView: [touch view]];
	point = [[CCDirector sharedDirector] convertToGL: point];
	return [self convertToNodeSpaceAR:point];
}
*/


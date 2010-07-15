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
,m_nTag(kCCNodeTagInvalid)
,m_nZOrder(0)
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
	CCLOGINFO( "cocos2d: deallocing", self);

	// attributes
	CCX_SAFE_RELEASE(m_pCamera);

	CCX_SAFE_RELEASE(m_pGrid);

	cleanup();

	// children
	CCX_SAFE_DELETE(m_pChildren);

}

void CCNode::arrayMakeObjectsPerformSelector(NSMutableArray * pArray, callbackFunc func)
{
	if(pArray && pArray->count() > 0)
	{
		CCNode* pNode;
		NSMutableArrayIterator it;
		for( it = pArray->begin(); it != pArray->end(); it++)
		{
			pNode = static_cast<CCNode*>(*it);

			if(pNode && func)
			{
				(pNode->*func)();
			}
		}
	}
}

/// zOrder getter
int CCNode::getZOrder()
{
	return m_nZOrder;
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void CCNode::setZOrder(int z)
{
	m_nZOrder = z;
}

/// ertexZ getter
float CCNode::getVertexZ()
{
	return m_fVertexZ;
}


/// vertexZ setter
void CCNode::setVertexZ(float var)
{
	m_fVertexZ = var;
}


/// rotation getter
float CCNode::getRotation()
{
	return m_fRotation;
}

/// rotation setter
void CCNode::setRotation(float newRotation)
{
	m_fRotation = newRotation;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}


/// scale getter
float CCNode::getScale(void)
{
	NSAssert( m_fScaleX == m_fScaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
	return m_fScale;
}

/// scale setter
void CCNode::setScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

/// scaleX getter
float CCNode::getScaleX()
{
	return m_fScaleX;
}

/// scaleX setter
void CCNode::setScaleX(float newScaleX)
{
	m_fScaleX = newScaleX;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

/// scaleY getter
float CCNode::getScaleY()
{
	return m_fScaleY;
}

/// scaleY setter
void CCNode::setScaleY(float newScaleY)
{
	m_fScaleY = newScaleY;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

/// position getter
CGPoint CCNode::getPosition()
{
	return m_tPosition;
}

/// position setter
void CCNode::setPosition(CGPoint newPosition)
{
	m_tPosition = newPosition;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

/// children getter
NSMutableArray * CCNode::getChildren()
{
	return m_pChildren;
}

/// camera getter: lazy alloc
CCCamera* CCNode::getCamera()
{
	if (!m_pCamera)
	{
		m_pCamera = new CCCamera();
	}
	
	return m_pCamera;
}


/// grid getter
CCGridBase* CCNode::getGrid()
{
	return m_pGrid;
}

/// grid setter
void CCNode::setGrid(CCGridBase* pGrid)
{
	if(m_pGrid)
		m_pGrid->release();

	m_pGrid = pGrid;

	if(m_pGrid)
		m_pGrid->retain();
}


/// isVisible getter
bool CCNode::getIsVisible()
{
	return m_bIsVisible;
}

/// isVisible setter
void CCNode::setIsVisible(bool var)
{
	m_bIsVisible = var;
}


/// anchorPoint getter
CGPoint CCNode::getAnchorPoint()
{
	return m_tAnchorPoint;
}

/// @todo anchorPoint setter
void CCNode::setAnchorPoint(CGPoint point)
{
	//if( ! CGPoint::CGPointEqualToPoint(point, m_tAnchorPoint) ) 
	//{
	//	m_tAnchorPoint = point;
	//	this->m_tAnchorPointInPixels = ccp( m_tContentSize.width * m_tAnchorPoint.x, m_tContentSize.height * m_tAnchorPoint.y );
	//	m_bIsTransformDirty = m_bIsInverseDirty = true;
	//	#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	//	m_bIsTransformGLDirty = true;
	//	#endif
	//}
}

/// anchorPointInPixels getter
CGPoint CCNode::getAnchorPointInPixels()
{
	return m_tAnchorPointInPixels;
}

/// contentSize getter
CGSize CCNode::getContentSize()
{
	return m_tContentSize;
}

/// @todo contentSize setter
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


/// isRunning getter
bool CCNode::getIsRunning()
{
	return m_bIsRunning;
}


/// parent getter
CCNode * CCNode::getParent()
{
	return m_pParent;
}
/// parent setter
void CCNode::setParent(CCNode * var)
{
	m_pParent = var;
}

/// isRelativeAnchorPoint getter
bool CCNode::getIsRelativeAnchorPoint()
{
	return m_bIsRelativeAnchorPoint;
}
/// isRelativeAnchorPoint setter
void CCNode::setIsRelativeAnchorPoint(bool newValue)
{
	m_bIsRelativeAnchorPoint = newValue;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CCX_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

/// tag getter
int CCNode::getTag()
{
	return m_nTag;
}

/// tag setter
void CCNode::setTag(int var)
{
	m_nTag = var;
}

/// userData getter
void * CCNode::getUserData()
{
	return m_pUserData;
}

/// userData setter
void CCNode::setUserData(void *var)
{
	m_pUserData = var;
}





/// @todo
//CGRect CCNode::boundingBox()
//{
//	CGRect rect = CGRectMake(0, 0, m_contentSize.width, m_contentSize.height);
//	return CGRectApplyAffineTransform(rect, nodeToParentTransform());
//}




/** @todo
#if CC_COCOSNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (int)
#endif
*/



CCNode * CCNode::node(void)
{
/// @todo	return [[[self alloc] init] autorelease];
	CCNode * pNode = new CCNode();
	pNode->autorelease();
	return pNode;
}


void CCNode::cleanup()
{
	// actions
	this->stopAllActions();
	
	// timers
	this->unscheduleAllSelectors();	

	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::cleanup);
}


std::string CCNode::description()
{
	char des[100];
	sprintf_s(des, 100, "<CCNode | Tag = %i>", m_nTag);
	string ret(des);

	return ret;
}

// lazy allocs
void CCNode::childrenAlloc(void)
{
	m_pChildren = new NSMutableArray(4);
}

CCNode* CCNode::getChildByTag(int aTag)
{
	NSAssert( aTag != kCCNodeTagInvalid, "Invalid tag");

	

	if(m_pChildren && m_pChildren->count() > 0)
	{
		CCNode* pNode;
		NSMutableArrayIterator it;
		for( it = m_pChildren->begin(); it != m_pChildren->end(); it++)
		{
			pNode = static_cast<CCNode*>(*it);
			if(pNode && pNode->m_nTag == aTag)
				return pNode;
		}
	}
	return NULL;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behaviour it only needs
* to override this method
*/
CCNode * CCNode::addChild(CCNode *child, int zOrder, int tag)
{	
	NSAssert( child != NULL, "Argument must be non-nil");
	NSAssert( child->m_pParent == NULL, "child already added. It can't be added again");

	if( ! m_pChildren )
		this->childrenAlloc();

	this->insertChild(child, zOrder);

	child->m_nTag = tag;

	child->setParent(this);

	if( m_bIsRunning )
		child->onEnter();
	return this;
}

CCNode * CCNode::addChild(CCNode *child, int zOrder)
{
	NSAssert( child != NULL, "Argument must be non-nil");
	return this->addChild(child, zOrder, child->m_nTag);
}

CCNode * CCNode::addChild(CCNode *child)
{
	NSAssert( child != NULL, "Argument must be non-nil");
	return this->addChild(child, child->m_nZOrder, child->m_nTag);
}

void CCNode::removeFromParentAndCleanup(bool cleanup)
{
	this->m_pParent->removeChild(this,cleanup);
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void CCNode::removeChild(CCNode* child, bool cleanup)
{
	// explicit nil handling
	if (m_pChildren == NULL)
		return;

	if ( m_pChildren->containsObject(child) )
		this->detachChild(child,cleanup);
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
	NSAssert( tag != kCCNodeTagInvalid, "Invalid tag");

	CCNode *child = this->getChildByTag(tag);

	if (child == NULL)
		CCLOG("cocos2d: removeChildByTag: child not found!");
	else
		this->removeChild(child, cleanup);
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
	// not using detachChild improves speed here
	if ( m_pChildren && m_pChildren->count() > 0 )
	{
		CCNode * pNode;
		NSMutableArrayIterator it;
		for ( it = m_pChildren->begin(); it!= m_pChildren->end(); it++ )
		{
			pNode = static_cast<CCNode *>(*it);
			if (pNode)
			{
				// IMPORTANT:
				//  -1st do onExit
				//  -2nd cleanup
				if(pNode->m_bIsRunning)
				{
					pNode->onExit();
				}

				if (cleanup)
				{
					pNode->cleanup();
				}
				// set parent nil at the end
				pNode->setParent(NULL);
			}
		}
	}
	m_pChildren->removeAllObjects();
}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{
	// IMPORTANT:
	//  -1st do onExit
	//  -2nd cleanup
	if (m_bIsRunning)
		child->onExit();

	// If you don't do cleanup, the child's actions will not get removed and the
	// its scheduledSelectors_ dict will not get released!
	if (doCleanup)
		child->cleanup();

	// set parent nil at the end
	child->setParent(NULL);

	m_pChildren->removeObject(child);
}


// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
	int index=0;
	bool added = false;

	if(m_pChildren && m_pChildren->count() > 0)
	{
		CCNode* pNode;
		NSMutableArrayIterator it;
		for( it = m_pChildren->begin(); it != m_pChildren->end(); it++)
		{
			pNode = static_cast<CCNode*>(*it);

			if ( pNode && pNode->m_nZOrder > z ) 
			{
				added = true;
				m_pChildren->insertObjectAtIndex(child, index);
				break;
			}
			index++;
		}
	}

	if( ! added )
		m_pChildren->addObject(child);

	child->setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
	NSAssert( child != NULL, "Child must be non-nil");

	child->retain();
	m_pChildren->removeObject(child);

	insertChild(child, zOrder);
}

void CCNode::draw()
{
	// override me
	// Only use- this function to draw your staff.
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
	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::onEnter);

	this->resumeSchedulerAndActions();

	m_bIsRunning = true;
}

void CCNode::onEnterTransitionDidFinish()
{
	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::onEnterTransitionDidFinish);
}

void CCNode::onExit()
{
	this->pauseSchedulerAndActions();

	m_bIsRunning = false;

	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::onExit);
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


// CCNode - Callbacks

void CCNode::scheduleUpdate()
{
	scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
	CCScheduler::getSharedScheduler()->scheduleUpdateForTarget(this, priority, !m_bIsRunning);
}

void CCNode::unscheduleUpdate()
{
	CCScheduler::getSharedScheduler()->unscheduleUpdateForTarget(this);
}

void CCNode::schedule(SEL_SCHEDULE selector)
{
	this->schedule(selector, 0);
}

void CCNode::schedule(SEL_SCHEDULE selector, ccTime interval)
{
	NSAssert( selector != NULL, "Argument must be non-nil");
	NSAssert( interval >=0, "Argument must be positive");

	CCScheduler::getSharedScheduler()->scheduleSelector(selector, this, interval, !m_bIsRunning);
}

void CCNode::unschedule(SEL_SCHEDULE selector)
{
	// explicit nil handling
	if (selector == NULL)
		return;

	CCScheduler::getSharedScheduler()->unscheduleSelector(selector, this);
}

void CCNode::unscheduleAllSelectors()
{
	CCScheduler::getSharedScheduler()->unscheduleAllSelectorsForTarget(this);
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
CGAffineTransform CCNode::nodeToParentTransform(void)
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
}*/
/** @todo
- (CGAffineTransform)parentToNodeTransform
{
	if ( isInverseDirty_ ) {
		inverse_ = CGAffineTransformInvert([self nodeToParentTransform]);
		isInverseDirty_ = NO;
	}

	return inverse_;
}*/
/** @todo
- (CGAffineTransform)nodeToWorldTransform
{
	CGAffineTransform t = [self nodeToParentTransform];

	for (CCNode *p = parent_; p != nil; p = p.parent)
		t = CGAffineTransformConcat(t, [p nodeToParentTransform]);

	return t;
}*/
/** @todo
- (CGAffineTransform)worldToNodeTransform
{
	return CGAffineTransformInvert([self nodeToWorldTransform]);
}*/

CGPoint CCNode::convertToNodeSpace(CGPoint worldPoint)
{
	/// @todo return CGPointApplyAffineTransform(worldPoint, [self worldToNodeTransform]);
	return CGPoint(0,0);
}

CGPoint CCNode::convertToWorldSpace(CGPoint nodePoint)
{
	/// @todo return CGPointApplyAffineTransform(nodePoint, [self nodeToWorldTransform]);
	return CGPoint(0,0);
}

CGPoint CCNode::convertToNodeSpaceAR(CGPoint worldPoint)
{
	/** @todo
	CGPoint nodePoint = [self convertToNodeSpace:worldPoint];
	return ccpSub(nodePoint, anchorPointInPixels_);*/
	return CGPoint(0,0);
}

CGPoint CCNode::convertToWorldSpaceAR(CGPoint nodePoint)
{
	/** @todo
	nodePoint = ccpAdd(nodePoint, anchorPointInPixels_);
	return [self convertToWorldSpace:nodePoint];*/
	return CGPoint(0,0);
}
/** @todo no declare in .h file
CGPoint CCNode::convertToWindowSpace(CGPoint nodePoint)
{
	
	CGPoint worldPoint = [self convertToWorldSpace:nodePoint];
	return [[CCDirector sharedDirector] convertToUI:worldPoint];
}*/

// convenience methods which take a UITouch instead of CGPoint
/** @todo
- (CGPoint)convertTouchToNodeSpace:(UITouch *)touch
{
	CGPoint point = [touch locationInView: [touch view]];
	point = [[CCDirector sharedDirector] convertToGL: point];
	return [self convertToNodeSpace:point];
}*/
/** @todo
- (CGPoint)convertTouchToNodeSpaceAR:(UITouch *)touch
{
	CGPoint point = [touch locationInView: [touch view]];
	point = [[CCDirector sharedDirector] convertToGL: point];
	return [self convertToNodeSpaceAR:point];
}
*/


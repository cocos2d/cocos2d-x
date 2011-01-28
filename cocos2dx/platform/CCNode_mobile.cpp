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
#include "CGPointExtension.h"
#include "support/TransformUtils.h"
#include "CCCamera.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "CCTouch.h"
#include "CCActionManager.h"

#if CC_COCOSNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (int)
#endif

namespace   cocos2d {

CCNode::CCNode(void)
:m_bIsRunning(false)
,m_fRotation(0.0f)
,m_fScaleX(1.0f)
,m_fScaleY(1.0f)
,m_tPosition(CGPointZero)
,m_tPositionInPixels(CGPointZero)
,m_tAnchorPointInPixels(CGPointZero)
,m_tAnchorPoint(CGPointZero)
,m_tContentSize(CGSizeZero)
,m_tContentSizeInPixels(CGSizeZero)
// "whole screen" objects. like Scenes and Layers, should set isRelativeAnchorPoint to false
,m_bIsRelativeAnchorPoint(true)
,m_bIsTransformDirty(true)
,m_bIsInverseDirty(true)
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
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
,m_pParent(NULL)
{
    // nothing
}
CCNode::~CCNode()
{
	CCLOGINFO( "cocos2d: deallocing" );

	// attributes
	CCX_SAFE_RELEASE(m_pCamera);

	CCX_SAFE_RELEASE(m_pGrid);


	if(m_pChildren && m_pChildren->count() > 0)
	{
		NSMutableArray<CCNode*>::NSMutableArrayIterator it;
		for( it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
		{
			if (*it)
			{
				(*it)->m_pParent = NULL;
			}		
		}
	}

	// children
	CCX_SAFE_RELEASE(m_pChildren);

}

void CCNode::arrayMakeObjectsPerformSelector(NSMutableArray<CCNode*> * pArray, callbackFunc func)
{
	if(pArray && pArray->count() > 0)
	{
		CCNode* pNode;
		NSMutableArray<CCNode*>::NSMutableArrayIterator it;
		for( it = pArray->begin(); it != pArray->end(); it++)
		{
			pNode = (*it);

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
	m_fVertexZ = var * CC_CONTENT_SCALE_FACTOR();
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
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}


/// scale getter
float CCNode::getScale(void)
{
	NSAssert( m_fScaleX == m_fScaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
	return m_fScaleX;
}

/// scale setter
void CCNode::setScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
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
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
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
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
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
	if (CC_CONTENT_SCALE_FACTOR() == 1)
	{
		m_tPositionInPixels = m_tPosition;
	}
	else
	{
		m_tPositionInPixels = ccpMult(newPosition, CC_CONTENT_SCALE_FACTOR());
	}

	m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

void CCNode::setPositionInPixels(CGPoint newPosition)
{
    m_tPositionInPixels = newPosition;

	if ( CC_CONTENT_SCALE_FACTOR() == 1)
	{
		m_tPosition = m_tPositionInPixels;
	}
	else
	{
		m_tPosition = ccpMult(newPosition, 1/CC_CONTENT_SCALE_FACTOR());
	}

	m_bIsTransformDirty = m_bIsInverseDirty = true;

#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif // CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
}

CGPoint CCNode::getPositionInPixels()
{
	return m_tPositionInPixels;
}

/// children getter
NSMutableArray<CCNode*> * CCNode::getChildren()
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
	CCX_SAFE_RETAIN(pGrid);
	CCX_SAFE_RELEASE(m_pGrid);
	m_pGrid = pGrid;
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

void CCNode::setAnchorPoint(CGPoint point)
{
	if( ! CGPoint::CGPointEqualToPoint(point, m_tAnchorPoint) ) 
	{
		m_tAnchorPoint = point;
		m_tAnchorPointInPixels = ccp( m_tContentSizeInPixels.width * m_tAnchorPoint.x, m_tContentSizeInPixels.height * m_tAnchorPoint.y );
		m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
#endif
	}
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

void CCNode::setContentSize(CGSize size)
{
	if( ! CGSize::CGSizeEqualToSize(size, m_tContentSize) ) 
	{
		m_tContentSize = size;

        if( CC_CONTENT_SCALE_FACTOR() == 1 )
        {
            m_tContentSizeInPixels = m_tContentSize;
        }
        else
        {
            m_tContentSizeInPixels = CGSizeMake( size.width * CC_CONTENT_SCALE_FACTOR(), size.height * CC_CONTENT_SCALE_FACTOR() );
        }

		m_tAnchorPointInPixels = ccp( m_tContentSizeInPixels.width * m_tAnchorPoint.x, m_tContentSizeInPixels.height * m_tAnchorPoint.y );
		m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
#endif
	}
}

void CCNode::setContentSizeInPixels(CGSize size)
{
	if (! CGSize::CGSizeEqualToSize(size, m_tContentSizeInPixels))
	{
        m_tContentSizeInPixels = size;

		if (CC_CONTENT_SCALE_FACTOR() == 1)
		{
			m_tContentSize = m_tContentSizeInPixels;
		}
		else
		{
			m_tContentSize = CGSizeMake(size.width / CC_CONTENT_SCALE_FACTOR(), size.height / CC_CONTENT_SCALE_FACTOR());
		}

		m_tAnchorPointInPixels = ccp(m_tContentSizeInPixels.width * m_tAnchorPoint.x, m_tContentSizeInPixels.height * m_tAnchorPoint.y);
		m_bIsTransformDirty = m_bIsInverseDirty = true;

#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
#endif // CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	}
}

CGSize CCNode::getContentSizeInPixels()
{
	return m_tContentSizeInPixels;
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
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
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


CGRect CCNode::boundingBox()
{
	CGRect ret = boundingBoxInPixels();
	return CC_RECT_PIXELS_TO_POINTS(ret);
}

CGRect CCNode::boundingBoxInPixels()
{
	CGRect rect = CGRectMake(0, 0, m_tContentSizeInPixels.width, m_tContentSizeInPixels.height);
	return CGRectApplyAffineTransform(rect, nodeToParentTransform());
}


CCNode * CCNode::node(void)
{
	CCNode * pRet = new CCNode();
	pRet->autorelease();
	return pRet;
}


void CCNode::cleanup()
{
	// actions
	this->stopAllActions();
	this->unscheduleAllSelectors();	

	// timers
	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::cleanup);
}


char * CCNode::description()
{
	char *ret = new char[100] ;
	sprintf(ret, "<CCNode | Tag = %d>", m_nTag);
	return ret;
}

// lazy allocs
void CCNode::childrenAlloc(void)
{
	m_pChildren = new NSMutableArray<CCNode*>(4);
}

CCNode* CCNode::getChildByTag(int aTag)
{
	NSAssert( aTag != kCCNodeTagInvalid, "Invalid tag");

	if(m_pChildren && m_pChildren->count() > 0)
	{
		CCNode* pNode;
		NSMutableArray<CCNode*>::NSMutableArrayIterator it;
		for( it = m_pChildren->begin(); it != m_pChildren->end(); it++)
		{
			pNode = (*it);
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
void CCNode::addChild(CCNode *child, int zOrder, int tag)
{	
	NSAssert( child != NULL, "Argument must be non-nil");
	NSAssert( child->m_pParent == NULL, "child already added. It can't be added again");

	if( ! m_pChildren )
	{
		this->childrenAlloc();
	}

	this->insertChild(child, zOrder);

	child->m_nTag = tag;

	child->setParent(this);

	if( m_bIsRunning )
	{
		child->onEnter();
		child->onEnterTransitionDidFinish();
	}
}

void CCNode::addChild(CCNode *child, int zOrder)
{
	NSAssert( child != NULL, "Argument must be non-nil");
	this->addChild(child, zOrder, child->m_nTag);
}

void CCNode::addChild(CCNode *child)
{
	NSAssert( child != NULL, "Argument must be non-nil");
	this->addChild(child, child->m_nZOrder, child->m_nTag);
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
	{
		return;
	}

	if ( m_pChildren->containsObject(child) )
	{
		this->detachChild(child,cleanup);
	}
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
	NSAssert( tag != kCCNodeTagInvalid, "Invalid tag");

	CCNode *child = this->getChildByTag(tag);

	if (child == NULL)
	{
		CCLOG("cocos2d: removeChildByTag: child not found!");
	}
	else
	{
		this->removeChild(child, cleanup);
	}
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
	// not using detachChild improves speed here
	if ( m_pChildren && m_pChildren->count() > 0 )
	{
		CCNode * pNode;
		NSMutableArray<CCNode*>::NSMutableArrayIterator it;
		for ( it = m_pChildren->begin(); it!= m_pChildren->end(); it++ )
		{
			pNode = *it;
			if (pNode)
			{
				// IMPORTANT:
				//  -1st do onExit
				//  -2nd cleanup
				if(m_bIsRunning)
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
		
		m_pChildren->removeAllObjects();
	}
	
}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{
	// IMPORTANT:
	//  -1st do onExit
	//  -2nd cleanup
	if (m_bIsRunning)
	{
		child->onExit();
	}

	// If you don't do cleanup, the child's actions will not get removed and the
	// its scheduledSelectors_ dict will not get released!
	if (doCleanup)
	{
		child->cleanup();
	}

	// set parent nil at the end
	child->setParent(NULL);

	m_pChildren->removeObject(child);
}


// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
    unsigned int index = 0;
    CCNode* a = m_pChildren->getLastObject();
    if (!a || a->getZOrder() <= z)
    {
        m_pChildren->addObject(child);
    }
    else
    {
        CCNode* pNode;
        NSMutableArray<CCNode*>::NSMutableArrayIterator it;
        for( it = m_pChildren->begin(); it != m_pChildren->end(); it++)
        {
            pNode = (*it);

            if ( pNode && pNode->m_nZOrder > z ) 
            {
                m_pChildren->insertObjectAtIndex(child, index);
                break;
            }
            index++;
        }
    }

    child->setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
	NSAssert( child != NULL, "Child must be non-nil");

	child->retain();
	m_pChildren->removeObject(child);

	insertChild(child, zOrder);
	child->release();
}

 void CCNode::draw()
 {
	 //assert(0);
 	// override me
 	// Only use- this function to draw your staff.
 	// DON'T draw your stuff outside this method
 }

void CCNode::visit()
{
	// quick return if not visible
	if (!m_bIsVisible)
	{
		return;
	}
	glPushMatrix();

 	if (m_pGrid && m_pGrid->isActive())
 	{
 		m_pGrid->beforeDraw();
 		this->transformAncestors();
 	}

	this->transform();

    CCNode* pNode;
    NSMutableArray<CCNode*>::NSMutableArrayIterator it;

	if(m_pChildren && m_pChildren->count() > 0)
	{
		// draw children zOrder < 0
		for( it = m_pChildren->begin(); it != m_pChildren->end(); it++)
		{
			pNode = (*it);

			if ( pNode && pNode->m_nZOrder < 0 ) 
			{
				pNode->visit();
			}
			else
			{
				break;
			}
		}
    }

	// self draw
	this->draw();

	// draw children zOrder >= 0
    if (m_pChildren && m_pChildren->count() > 0)
    {
		for ( ; it!=m_pChildren->end(); it++ )
		{
			pNode = (*it);
            if (pNode)
            {
                pNode->visit();
            }
		}		
	}

 	if (m_pGrid && m_pGrid->isActive())
 	{
 		m_pGrid->afterDraw(this);
	}
 
	glPopMatrix();
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
	// transformations

#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	// BEGIN alternative -- using cached transform
	//
	if( m_bIsTransformGLDirty ) {
		CGAffineTransform t = this->nodeToParentTransform();
		CGAffineToGL(&t, m_pTransformGL);
		m_bIsTransformGLDirty = false;
	}

	glMultMatrixf(m_pTransformGL);
	if( m_fVertexZ )
	{
		glTranslatef(0, 0, m_fVertexZ);
	}

	// XXX: Expensive calls. Camera should be integrated into the cached affine matrix
	if (m_pCamera && !(m_pGrid && m_pGrid->isActive())) {
		bool translate = (m_tAnchorPointInPixels.x != 0.0f || m_tAnchorPointInPixels.y != 0.0f);

		if( translate )
		{
			ccglTranslate(RENDER_IN_SUBPIXEL(m_tAnchorPointInPixels.x), RENDER_IN_SUBPIXEL(m_tAnchorPointInPixels.y), 0);
		}

		m_pCamera->locate();

		if( translate )
		{
			ccglTranslate(RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.x), RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.y), 0);
		}
	}


	// END alternative

#else
	// BEGIN original implementation
	// 
	// translate
	if ( m_bIsRelativeAnchorPoint && (m_tAnchorPointInPixels.x != 0 || m_tAnchorPointInPixels.y != 0 ) )
		glTranslatef( RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.x), RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.y), 0);

	if (m_tAnchorPointInPixels.x != 0 || m_tAnchorPointInPixels.y != 0)
		glTranslatef( RENDER_IN_SUBPIXEL(m_tPositionInPixels.x + m_tAnchorPointInPixels.x), RENDER_IN_SUBPIXEL(m_tPositionInPixels.y + m_tAnchorPointInPixels.y), m_fVertexZ);
	else if ( m_tPositionInPixels.x !=0 || m_tPositionInPixels.y !=0 || m_fVertexZ != 0)
		glTranslatef( RENDER_IN_SUBPIXEL(m_tPositionInPixels.x), RENDER_IN_SUBPIXEL(m_tPositionInPixels.y), m_fVertexZ );

	// rotate
	if (m_fRotation != 0.0f )
		glRotatef( -m_fRotation, 0.0f, 0.0f, 1.0f );

	// scale
	if (m_fScaleX != 1.0f || m_fScaleY != 1.0f)
		glScalef( m_fScaleX, m_fScaleY, 1.0f );

	if ( m_pCamera  && !(m_pGrid && m_pGrid->isActive()) )
		m_pCamera->locate();

	// restore and re-position point
	if (m_tAnchorPointInPixels.x != 0.0f || m_tAnchorPointInPixels.y != 0.0f)
		glTranslatef(RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.x), RENDER_IN_SUBPIXEL(-m_tAnchorPointInPixels.y), 0);

	//
	// END original implementation
#endif

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
CCAction * CCNode::runAction(CCAction* action)
{
	NSAssert( action != NULL, "Argument must be non-nil");
	CCActionManager::sharedManager()->addAction(action, this, !m_bIsRunning);
	return action;
}

void CCNode::stopAllActions()
{
	CCActionManager::sharedManager()->removeAllActionsFromTarget(this);
}

void CCNode::stopAction(CCAction* action)
{
	CCActionManager::sharedManager()->removeAction(action);
}

void CCNode::stopActionByTag(int tag)
{
	NSAssert( tag != kCCActionTagInvalid, "Invalid tag");
	CCActionManager::sharedManager()->removeActionByTag(tag, this);
}

CCAction * CCNode::getActionByTag(int tag)
{
	NSAssert( tag != kCCActionTagInvalid, "Invalid tag");
	return CCActionManager::sharedManager()->getActionByTag(tag, this);
}

int CCNode::numberOfRunningActions()
{
	return CCActionManager::sharedManager()->numberOfRunningActionsInTarget(this);
}

// CCNode - Callbacks

void CCNode::scheduleUpdate()
{
	scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
	CCScheduler::sharedScheduler()->scheduleUpdateForTarget(this, priority, !m_bIsRunning);
}

void CCNode::unscheduleUpdate()
{
	CCScheduler::sharedScheduler()->unscheduleUpdateForTarget(this);
}

void CCNode::schedule(SEL_SCHEDULE selector)
{
	this->schedule(selector, 0);
}

void CCNode::schedule(SEL_SCHEDULE selector, ccTime interval)
{
	NSAssert( selector != NULL, "Argument must be non-nil");
	NSAssert( interval >=0, "Argument must be positive");

	CCScheduler::sharedScheduler()->scheduleSelector(selector, this, interval, !m_bIsRunning);
}

void CCNode::unschedule(SEL_SCHEDULE selector)
{
	// explicit nil handling
	if (selector == 0)
		return;

	CCScheduler::sharedScheduler()->unscheduleSelector(selector, this);
}

void CCNode::unscheduleAllSelectors()
{
	CCScheduler::sharedScheduler()->unscheduleAllSelectorsForTarget(this);
}

void CCNode::resumeSchedulerAndActions()
{
	CCScheduler::sharedScheduler()->resumeTarget(this);
	CCActionManager::sharedManager()->resumeTarget(this);
}

void CCNode::pauseSchedulerAndActions()
{
	CCScheduler::sharedScheduler()->pauseTarget(this);
	CCActionManager::sharedManager()->pauseTarget(this);
}

void CCNode::selectorProtocolRetain(void)
{
	retain();
}

void CCNode::selectorProtocolRelease(void)
{
	release();
}

CGAffineTransform CCNode::nodeToParentTransform(void)
{
	if ( m_bIsTransformDirty ) {

		m_tTransform = CGAffineTransformIdentity;

		if( ! m_bIsRelativeAnchorPoint && ! CGPoint::CGPointEqualToPoint(m_tAnchorPointInPixels, CGPointZero) )
			m_tTransform = CGAffineTransformTranslate(m_tTransform, m_tAnchorPointInPixels.x, m_tAnchorPointInPixels.y);

		if( ! CGPoint::CGPointEqualToPoint(m_tPositionInPixels, CGPointZero) )
			m_tTransform = CGAffineTransformTranslate(m_tTransform, m_tPositionInPixels.x, m_tPositionInPixels.y);
		if( m_fRotation != 0 )
			m_tTransform = CGAffineTransformRotate(m_tTransform, -CC_DEGREES_TO_RADIANS(m_fRotation));
		if( ! (m_fScaleX == 1 && m_fScaleY == 1) ) 
			m_tTransform = CGAffineTransformScale(m_tTransform, m_fScaleX, m_fScaleY);

		if( ! CGPoint::CGPointEqualToPoint(m_tAnchorPointInPixels, CGPointZero) )
			m_tTransform = CGAffineTransformTranslate(m_tTransform, -m_tAnchorPointInPixels.x, -m_tAnchorPointInPixels.y);

		m_bIsTransformDirty = false;
	}

	return m_tTransform;
}

CGAffineTransform CCNode::parentToNodeTransform(void)
{
	if ( m_bIsInverseDirty ) {
		m_tInverse = CGAffineTransformInvert(this->nodeToParentTransform());
		m_bIsInverseDirty = false;
	}

	return m_tInverse;
}

CGAffineTransform CCNode::nodeToWorldTransform()
{
	CGAffineTransform t = this->nodeToParentTransform();

	for (CCNode *p = m_pParent; p != NULL; p = p->getParent())
		t = CGAffineTransformConcat(t, p->nodeToParentTransform());

	return t;
}

CGAffineTransform CCNode::worldToNodeTransform(void)
{
	return CGAffineTransformInvert(this->nodeToWorldTransform());
}

CGPoint CCNode::convertToNodeSpace(CGPoint worldPoint)
{
	CGPoint ret;
	if(CC_CONTENT_SCALE_FACTOR() == 1)
	{
		ret = CGPointApplyAffineTransform(worldPoint, worldToNodeTransform());
	}
	else 
	{
		ret = ccpMult(worldPoint, CC_CONTENT_SCALE_FACTOR());
		ret = CGPointApplyAffineTransform(ret, worldToNodeTransform());
		ret = ccpMult(ret, 1/CC_CONTENT_SCALE_FACTOR());
	}

	return ret;
}

CGPoint CCNode::convertToWorldSpace(CGPoint nodePoint)
{
	CGPoint ret;
	if(CC_CONTENT_SCALE_FACTOR() == 1)
	{
		ret = CGPointApplyAffineTransform(nodePoint, nodeToWorldTransform());
	}
	else 
	{
		ret = ccpMult( nodePoint, CC_CONTENT_SCALE_FACTOR() );
		ret = CGPointApplyAffineTransform(ret, nodeToWorldTransform());
		ret = ccpMult( ret, 1/CC_CONTENT_SCALE_FACTOR() );
	}

	return ret;
}

CGPoint CCNode::convertToNodeSpaceAR(CGPoint worldPoint)
{
	CGPoint nodePoint = convertToNodeSpace(worldPoint);
	CGPoint anchorInPoints;
	if( CC_CONTENT_SCALE_FACTOR() == 1 )
	{
		anchorInPoints = m_tAnchorPointInPixels;
	}
	else
	{
		anchorInPoints = ccpMult( m_tAnchorPointInPixels, 1/CC_CONTENT_SCALE_FACTOR() );
	}

	return ccpSub(nodePoint, anchorInPoints);
}

CGPoint CCNode::convertToWorldSpaceAR(CGPoint nodePoint)
{
	CGPoint anchorInPoints;
	if( CC_CONTENT_SCALE_FACTOR() == 1 )
	{
		anchorInPoints = m_tAnchorPointInPixels;
	}
	else
	{
		anchorInPoints = ccpMult( m_tAnchorPointInPixels, 1/CC_CONTENT_SCALE_FACTOR() );
	}

	nodePoint = ccpAdd(nodePoint, anchorInPoints);
	return convertToWorldSpace(nodePoint);
}
CGPoint CCNode::convertToWindowSpace(CGPoint nodePoint)
{
	CGPoint worldPoint = this->convertToWorldSpace(nodePoint);
	return CCDirector::sharedDirector()->convertToUI(worldPoint);
}

// convenience methods which take a CCTouch instead of CGPoint
CGPoint CCNode::convertTouchToNodeSpace(CCTouch *touch)
{
	CGPoint point = touch->locationInView(touch->view());
	point = CCDirector::sharedDirector()->convertToGL(point);
	return this->convertToNodeSpace(point);
}
CGPoint CCNode::convertTouchToNodeSpaceAR(CCTouch *touch)
{
	CGPoint point = touch->locationInView(touch->view());
	point = CCDirector::sharedDirector()->convertToGL(point);
	return this->convertToNodeSpaceAR(point);
}

}//namespace   cocos2d 

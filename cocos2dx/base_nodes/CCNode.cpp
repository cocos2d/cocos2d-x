/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
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

#include "CCNode.h"
#include "CCPointExtension.h"
#include "support/TransformUtils.h"
#include "CCCamera.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "CCTouch.h"
#include "CCActionManager.h"
#include "CCScriptSupport.h"

#if CC_COCOSNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (int)
#endif

namespace   cocos2d {

CCNode::CCNode(void)
: m_nZOrder(0)
, m_fVertexZ(0.0f)
, m_fRotation(0.0f)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_tPosition(CCPointZero)
, m_tPositionInPixels(CCPointZero)
, m_fSkewX(0.0)
, m_fSkewY(0.0)
// children (lazy allocs)
, m_pChildren(NULL)
// lazy alloc
, m_pCamera(NULL)
, m_pGrid(NULL)
, m_bIsVisible(true)
, m_tAnchorPoint(CCPointZero)
, m_tAnchorPointInPixels(CCPointZero)
, m_tContentSize(CCSizeZero)
, m_tContentSizeInPixels(CCSizeZero)
, m_bIsRunning(false)
, m_pParent(NULL)
// "whole screen" objects. like Scenes and Layers, should set isRelativeAnchorPoint to false
, m_bIsRelativeAnchorPoint(true)
, m_nTag(kCCNodeTagInvalid)
// userData is always inited as nil
, m_pUserData(NULL)
, m_bIsTransformDirty(true)
, m_bIsInverseDirty(true)
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
, m_bIsTransformGLDirty(true)
#endif
, m_nScriptHandler(0)
{
    // nothing
}
CCNode::~CCNode(void)
{
	CCLOGINFO( "cocos2d: deallocing" );

	// attributes
	CC_SAFE_RELEASE(m_pCamera);

	CC_SAFE_RELEASE(m_pGrid);

	if(m_pChildren && m_pChildren->count() > 0)
	{
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pChild = (CCNode*) child;
            if (pChild)
            {
                pChild->m_pParent = NULL;
            }
        }
	}

	// children
	CC_SAFE_RELEASE(m_pChildren);

}

void CCNode::arrayMakeObjectsPerformSelector(CCArray* pArray, callbackFunc func)
{
	if(pArray && pArray->count() > 0)
	{
        CCObject* child;
        CCARRAY_FOREACH(pArray, child)
        {
            CCNode* pNode = (CCNode*) child;
            if(pNode && (0 != func))
            {
                (pNode->*func)();
            }
        }
	}
}

float CCNode::getSkewX()
{
	return m_fSkewX;
}

void CCNode::setSkewX(float newSkewX)
{
	m_fSkewX = newSkewX;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

float CCNode::getSkewY()
{
	return m_fSkewY;
	m_bIsTransformDirty = m_bIsInverseDirty = true;
#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	m_bIsTransformGLDirty = true;
#endif
}

void CCNode::setSkewY(float newSkewY)
{
	m_fSkewY = newSkewY;

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
	return m_fVertexZ / CC_CONTENT_SCALE_FACTOR();
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
	CCAssert( m_fScaleX == m_fScaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
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
const CCPoint& CCNode::getPosition()
{
	return m_tPosition;
}

/// position setter
void CCNode::setPosition(const CCPoint& newPosition)
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

void CCNode::setPositionInPixels(const CCPoint& newPosition)
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

const CCPoint& CCNode::getPositionInPixels()
{
	return m_tPositionInPixels;
}

const CCPoint& CCNode::getPositionLua(void)
{
    return m_tPosition;
}

void CCNode::getPosition(float* x, float* y)
{
    *x = m_tPosition.x;
    *y = m_tPosition.y;
}

float CCNode::getPositionX(void)
{
    return m_tPosition.x;
}

float CCNode::getPositionY(void)
{
    return  m_tPosition.y;
}

void CCNode::setPositionX(float x)
{
    setPosition(ccp(x, m_tPosition.y));
}

void CCNode::setPositionY(float y)
{
    setPosition(ccp(m_tPosition.x, y));
}

void CCNode::setPosition(float x, float y)
{
    setPosition(ccp(x, y));
}

void CCNode::setPositionInPixels(float x, float y)
{
    setPositionInPixels(ccp(x, y));
}

/// children getter
CCArray* CCNode::getChildren()
{
	return m_pChildren;
}

unsigned int CCNode::getChildrenCount(void)
{
    return m_pChildren ? m_pChildren->count() : 0;
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
	CC_SAFE_RETAIN(pGrid);
	CC_SAFE_RELEASE(m_pGrid);
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
const CCPoint& CCNode::getAnchorPoint()
{
	return m_tAnchorPoint;
}

void CCNode::setAnchorPoint(const CCPoint& point)
{
	if( ! CCPoint::CCPointEqualToPoint(point, m_tAnchorPoint) ) 
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
const CCPoint& CCNode::getAnchorPointInPixels()
{
	return m_tAnchorPointInPixels;
}

/// contentSize getter
const CCSize& CCNode::getContentSize()
{
	return m_tContentSize;
}

void CCNode::setContentSize(const CCSize& size)
{
	if( ! CCSize::CCSizeEqualToSize(size, m_tContentSize) ) 
	{
		m_tContentSize = size;

        if( CC_CONTENT_SCALE_FACTOR() == 1 )
        {
            m_tContentSizeInPixels = m_tContentSize;
        }
        else
        {
            m_tContentSizeInPixels = CCSizeMake( size.width * CC_CONTENT_SCALE_FACTOR(), size.height * CC_CONTENT_SCALE_FACTOR() );
        }

		m_tAnchorPointInPixels = ccp( m_tContentSizeInPixels.width * m_tAnchorPoint.x, m_tContentSizeInPixels.height * m_tAnchorPoint.y );
		m_bIsTransformDirty = m_bIsInverseDirty = true;
#ifdef CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
#endif
	}
}

void CCNode::setContentSizeInPixels(const CCSize& size)
{
	if (! CCSize::CCSizeEqualToSize(size, m_tContentSizeInPixels))
	{
        m_tContentSizeInPixels = size;

		if (CC_CONTENT_SCALE_FACTOR() == 1)
		{
			m_tContentSize = m_tContentSizeInPixels;
		}
		else
		{
			m_tContentSize = CCSizeMake(size.width / CC_CONTENT_SCALE_FACTOR(), size.height / CC_CONTENT_SCALE_FACTOR());
		}

		m_tAnchorPointInPixels = ccp(m_tContentSizeInPixels.width * m_tAnchorPoint.x, m_tContentSizeInPixels.height * m_tAnchorPoint.y);
		m_bIsTransformDirty = m_bIsInverseDirty = true;

#if CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
		m_bIsTransformGLDirty = true;
#endif // CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	}
}

const CCSize& CCNode::getContentSizeInPixels()
{
	return m_tContentSizeInPixels;
}


// isRunning getter
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


CCRect CCNode::boundingBox()
{
	CCRect ret = boundingBoxInPixels();
	return CC_RECT_PIXELS_TO_POINTS(ret);
}

CCRect CCNode::boundingBoxInPixels()
{
	CCRect rect = CCRectMake(0, 0, m_tContentSizeInPixels.width, m_tContentSizeInPixels.height);
	return CCRectApplyAffineTransform(rect, nodeToParentTransform());
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
    m_pChildren = CCArray::arrayWithCapacity(4);
    m_pChildren->retain();
}

CCNode* CCNode::getChildByTag(int aTag)
{
	CCAssert( aTag != kCCNodeTagInvalid, "Invalid tag");

	if(m_pChildren && m_pChildren->count() > 0)
	{
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
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
	CCAssert( child != NULL, "Argument must be non-nil");
	CCAssert( child->m_pParent == NULL, "child already added. It can't be added again");

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
	CCAssert( child != NULL, "Argument must be non-nil");
	this->addChild(child, zOrder, child->m_nTag);
}

void CCNode::addChild(CCNode *child)
{
	CCAssert( child != NULL, "Argument must be non-nil");
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
	CCAssert( tag != kCCNodeTagInvalid, "Invalid tag");

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
        CCObject* child;
        CCARRAY_FOREACH(m_pChildren, child)
		{
            CCNode* pNode = (CCNode*) child;
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
    CCNode* a = (CCNode*) m_pChildren->lastObject();
    if (!a || a->getZOrder() <= z)
    {
        m_pChildren->addObject(child);
    }
    else
    {
        CCObject* pObject;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pNode = (CCNode*) pObject;
            if ( pNode && (pNode->m_nZOrder > z ))
            {
                m_pChildren->insertObject(child, index);
                break;
            }
            index++;
        }
    }

    child->setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
	CCAssert( child != NULL, "Child must be non-nil");

	child->retain();
	m_pChildren->removeObject(child);

	insertChild(child, zOrder);
	child->release();
}

 void CCNode::draw()
 {
	 //CCAssert(0);
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

    CCNode* pNode = NULL;
    unsigned int i = 0;

	if(m_pChildren && m_pChildren->count() > 0)
	{
		// draw children zOrder < 0
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];

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
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
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
		CCAffineTransform t = this->nodeToParentTransform();
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

	// skew
	if ( (skewX_ != 0.0f) || (skewY_ != 0.0f) ) 
	{
		CCAffineTransform skewMatrix = CCAffineTransformMake( 1.0f, tanf(CC_DEGREES_TO_RADIANS(skewY_)), tanf(CC_DEGREES_TO_RADIANS(skewX_)), 1.0f, 0.0f, 0.0f );
		GLfloat	glMatrix[16];
		CCAffineToGL(&skewMatrix, glMatrix);															 
		glMultMatrixf(glMatrix);
	}

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

    if (m_nScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeFunctionWithIntegerData(m_nScriptHandler, kCCNodeOnEnter);
    }
}

void CCNode::onEnterTransitionDidFinish()
{
	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::onEnterTransitionDidFinish);
}

void CCNode::onExit()
{
	this->pauseSchedulerAndActions();

	m_bIsRunning = false;

    if (m_nScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeFunctionWithIntegerData(m_nScriptHandler, kCCNodeOnExit);
    }

	arrayMakeObjectsPerformSelector(m_pChildren, &CCNode::onExit);
}

void CCNode::registerScriptHandler(int nHandler)
{
    unregisterScriptHandler();
    m_nScriptHandler = nHandler;
    LUALOG("[LUA] Add CCNode event handler: %d", m_nScriptHandler);
}

void CCNode::unregisterScriptHandler(void)
{
    if (m_nScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeLuaHandler(m_nScriptHandler);
        LUALOG("[LUA] Remove CCNode event handler: %d", m_nScriptHandler);
        m_nScriptHandler = 0;
    }
}

CCAction * CCNode::runAction(CCAction* action)
{
	CCAssert( action != NULL, "Argument must be non-nil");
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
	CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
	CCActionManager::sharedManager()->removeActionByTag(tag, this);
}

CCAction * CCNode::getActionByTag(int tag)
{
	CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
	return CCActionManager::sharedManager()->getActionByTag(tag, this);
}

unsigned int CCNode::numberOfRunningActions()
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
	CCAssert( selector, "Argument must be non-nil");
	CCAssert( interval >=0, "Argument must be positive");

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

CCAffineTransform CCNode::nodeToParentTransform(void)
{
	if (m_bIsTransformDirty) {

		m_tTransform = CCAffineTransformIdentity;

		if( ! m_bIsRelativeAnchorPoint && ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPixels, CCPointZero) )
		{
			m_tTransform = CCAffineTransformTranslate(m_tTransform, m_tAnchorPointInPixels.x, m_tAnchorPointInPixels.y);
		}

		if(! CCPoint::CCPointEqualToPoint(m_tPositionInPixels, CCPointZero))
		{
			m_tTransform = CCAffineTransformTranslate(m_tTransform, m_tPositionInPixels.x, m_tPositionInPixels.y);
		}

		if(m_fRotation != 0)
		{
			m_tTransform = CCAffineTransformRotate(m_tTransform, -CC_DEGREES_TO_RADIANS(m_fRotation));
		}

		if(m_fSkewX != 0 || m_fSkewY != 0) 
		{
			// create a skewed coordinate system
			CCAffineTransform skew = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)), tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f, 0.0f, 0.0f);
			// apply the skew to the transform
			m_tTransform = CCAffineTransformConcat(skew, m_tTransform);
		}

		if(! (m_fScaleX == 1 && m_fScaleY == 1)) 
		{
			m_tTransform = CCAffineTransformScale(m_tTransform, m_fScaleX, m_fScaleY);
		}

		if(! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPixels, CCPointZero))
		{
			m_tTransform = CCAffineTransformTranslate(m_tTransform, -m_tAnchorPointInPixels.x, -m_tAnchorPointInPixels.y);
		}

		m_bIsTransformDirty = false;
	}

	return m_tTransform;
}

CCAffineTransform CCNode::parentToNodeTransform(void)
{
	if ( m_bIsInverseDirty ) {
		m_tInverse = CCAffineTransformInvert(this->nodeToParentTransform());
		m_bIsInverseDirty = false;
	}

	return m_tInverse;
}

CCAffineTransform CCNode::nodeToWorldTransform()
{
	CCAffineTransform t = this->nodeToParentTransform();

	for (CCNode *p = m_pParent; p != NULL; p = p->getParent())
		t = CCAffineTransformConcat(t, p->nodeToParentTransform());

	return t;
}

CCAffineTransform CCNode::worldToNodeTransform(void)
{
	return CCAffineTransformInvert(this->nodeToWorldTransform());
}

CCPoint CCNode::convertToNodeSpace(const CCPoint& worldPoint)
{
	CCPoint ret;
	if(CC_CONTENT_SCALE_FACTOR() == 1)
	{
		ret = CCPointApplyAffineTransform(worldPoint, worldToNodeTransform());
	}
	else 
	{
		ret = ccpMult(worldPoint, CC_CONTENT_SCALE_FACTOR());
		ret = CCPointApplyAffineTransform(ret, worldToNodeTransform());
		ret = ccpMult(ret, 1/CC_CONTENT_SCALE_FACTOR());
	}

	return ret;
}

CCPoint CCNode::convertToWorldSpace(const CCPoint& nodePoint)
{
	CCPoint ret;
	if(CC_CONTENT_SCALE_FACTOR() == 1)
	{
		ret = CCPointApplyAffineTransform(nodePoint, nodeToWorldTransform());
	}
	else 
	{
		ret = ccpMult( nodePoint, CC_CONTENT_SCALE_FACTOR() );
		ret = CCPointApplyAffineTransform(ret, nodeToWorldTransform());
		ret = ccpMult( ret, 1/CC_CONTENT_SCALE_FACTOR() );
	}

	return ret;
}

CCPoint CCNode::convertToNodeSpaceAR(const CCPoint& worldPoint)
{
	CCPoint nodePoint = convertToNodeSpace(worldPoint);
	CCPoint anchorInPoints;
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

CCPoint CCNode::convertToWorldSpaceAR(const CCPoint& nodePoint)
{
	CCPoint anchorInPoints;
	if( CC_CONTENT_SCALE_FACTOR() == 1 )
	{
		anchorInPoints = m_tAnchorPointInPixels;
	}
	else
	{
		anchorInPoints = ccpMult( m_tAnchorPointInPixels, 1/CC_CONTENT_SCALE_FACTOR() );
	}

	CCPoint pt = ccpAdd(nodePoint, anchorInPoints);
	return convertToWorldSpace(pt);
}
CCPoint CCNode::convertToWindowSpace(const CCPoint& nodePoint)
{
	CCPoint worldPoint = this->convertToWorldSpace(nodePoint);
	return CCDirector::sharedDirector()->convertToUI(worldPoint);
}

// convenience methods which take a CCTouch instead of CCPoint
CCPoint CCNode::convertTouchToNodeSpace(CCTouch *touch)
{
	CCPoint point = touch->locationInView(touch->view());
	point = CCDirector::sharedDirector()->convertToGL(point);
	return this->convertToNodeSpace(point);
}
CCPoint CCNode::convertTouchToNodeSpaceAR(CCTouch *touch)
{
	CCPoint point = touch->locationInView(touch->view());
	point = CCDirector::sharedDirector()->convertToGL(point);
	return this->convertToNodeSpaceAR(point);
}

}//namespace   cocos2d 

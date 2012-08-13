/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "cocoa/CCString.h"
#include "CCNode.h"
#include "support/CCPointExtension.h"
#include "support/TransformUtils.h"
#include "CCCamera.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "touch_dispatcher/CCTouch.h"
#include "actions/CCActionManager.h"
#include "script_support/CCScriptSupport.h"
#include "shaders/CCGLProgram.h"
// externals
#include "kazmath/GL/matrix.h"


#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (int)
#endif

NS_CC_BEGIN

// XXX: Yes, nodes might have a sort problem once every 15 days if the game runs at 60 FPS and each frame sprites are reordered.
static int s_globalOrderOfArrival = 1;

CCNode::CCNode(void)
: m_nZOrder(0)
, m_fVertexZ(0.0f)
, m_fRotation(0.0f)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_tPosition(CCPointZero)
, m_fSkewX(0.0f)
, m_fSkewY(0.0f)
// children (lazy allocs)
, m_pChildren(NULL)
// lazy alloc
, m_pCamera(NULL)
, m_pGrid(NULL)
, m_bIsVisible(true)
, m_tAnchorPoint(CCPointZero)
, m_tAnchorPointInPoints(CCPointZero)
, m_tContentSize(CCSizeZero)
, m_bIsRunning(false)
, m_pParent(NULL)
// "whole screen" objects. like Scenes and Layers, should set m_bIgnoreAnchorPointForPosition to false
, m_bIgnoreAnchorPointForPosition(false)
, m_nTag(kCCNodeTagInvalid)
// userData is always inited as nil
, m_pUserData(NULL)
, m_pUserObject(NULL)
, m_bIsTransformDirty(true)
, m_bIsInverseDirty(true)
, m_nScriptHandler(0)
, m_pShaderProgram(NULL)
, m_nOrderOfArrival(0)
, m_glServerState(CC_GL_BLEND)
, m_bReorderChildDirty(false)
{
    // set default scheduler and actionManager
    CCDirector *director = CCDirector::sharedDirector();
    m_pActionManager = director->getActionManager();
    m_pActionManager->retain();
    m_pScheduler = director->getScheduler();
    m_pScheduler->retain();
}

CCNode::~CCNode(void)
{
    CCLOGINFO( "cocos2d: deallocing" );

    CC_SAFE_RELEASE(m_pActionManager);
    CC_SAFE_RELEASE(m_pScheduler);
    // attributes
    CC_SAFE_RELEASE(m_pCamera);

    CC_SAFE_RELEASE(m_pGrid);
    CC_SAFE_RELEASE(m_pShaderProgram);
    CC_SAFE_RELEASE(m_pUserObject);

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

float CCNode::getSkewX()
{
    return m_fSkewX;
}

void CCNode::setSkewX(float newSkewX)
{
    m_fSkewX = newSkewX;
    m_bIsTransformDirty = m_bIsInverseDirty = true;
}

float CCNode::getSkewY()
{
    return m_fSkewY;
}

void CCNode::setSkewY(float newSkewY)
{
    m_fSkewY = newSkewY;

    m_bIsTransformDirty = m_bIsInverseDirty = true;
}

/// zOrder getter
int CCNode::getZOrder()
{
    return m_nZOrder;
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void CCNode::_setZOrder(int z)
{
    m_nZOrder = z;
}

void CCNode::setZOrder(int z)
{
    _setZOrder(z);
    if (m_pParent)
    {
        m_pParent->reorderChild(this, z);
    }
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
    m_bIsTransformDirty = m_bIsInverseDirty = true;
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
bool CCNode::isVisible()
{
    return m_bIsVisible;
}

/// isVisible setter
void CCNode::setVisible(bool var)
{
    m_bIsVisible = var;
}

const CCPoint& CCNode::getAnchorPointInPoints()
{
    return m_tAnchorPointInPoints;
}

/// anchorPoint getter
const CCPoint& CCNode::getAnchorPoint()
{
    return m_tAnchorPoint;
}

void CCNode::setAnchorPoint(const CCPoint& point)
{
    if( ! point.equals(m_tAnchorPoint))
    {
        m_tAnchorPoint = point;
        m_tAnchorPointInPoints = ccp( m_tContentSize.width * m_tAnchorPoint.x, m_tContentSize.height * m_tAnchorPoint.y );
        m_bIsTransformDirty = m_bIsInverseDirty = true;
    }
}

/// contentSize getter
const CCSize & CCNode::getContentSize()
{
    return m_tContentSize;
}

void CCNode::setContentSize(const CCSize & size)
{
    if( ! size.equals(m_tContentSize))
    {
        m_tContentSize = size;

        m_tAnchorPointInPoints = ccp( m_tContentSize.width * m_tAnchorPoint.x, m_tContentSize.height * m_tAnchorPoint.y );
        m_bIsTransformDirty = m_bIsInverseDirty = true;
    }
}

// isRunning getter
bool CCNode::isRunning()
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
bool CCNode::isIgnoreAnchorPointForPosition()
{
    return m_bIgnoreAnchorPointForPosition;
}
/// isRelativeAnchorPoint setter
void CCNode::ignoreAnchorPointForPosition(bool newValue)
{
    if (newValue != m_bIgnoreAnchorPointForPosition) 
    {
		m_bIgnoreAnchorPointForPosition = newValue;
		m_bIsTransformDirty = m_bIsInverseDirty = true;
	}
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
    CCRect rect = CCRectMake(0, 0, m_tContentSize.width, m_tContentSize.height);
    return CCRectApplyAffineTransform(rect, nodeToParentTransform());
}

CCNode * CCNode::node(void)
{
    return CCNode::create();
}

CCNode * CCNode::create(void)
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
    arrayMakeObjectsPerformSelector(m_pChildren, cleanup, CCNode*);
}


const char* CCNode::description()
{
    return CCString::createWithFormat("<CCNode | Tag = %d>", m_nTag)->getCString();
}

// lazy allocs
void CCNode::childrenAlloc(void)
{
    m_pChildren = CCArray::createWithCapacity(4);
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
    child->setOrderOfArrival(s_globalOrderOfArrival++);

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
    if (m_pParent != NULL)
    {
        m_pParent->removeChild(this,cleanup);
    } 
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
                    pNode->onExitTransitionDidStart();
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
        child->onExitTransitionDidStart();
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
    m_bReorderChildDirty = true;
    ccArrayAppendObjectWithResize(m_pChildren->data, child);
    child->_setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
    CCAssert( child != NULL, "Child must be non-nil");
    m_bReorderChildDirty = true;
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    child->_setZOrder(zOrder);
}

void CCNode::sortAllChildren()
{
    if (m_bReorderChildDirty)
    {
        int i,j,length = m_pChildren->data->num;
        CCNode ** x = (CCNode**)m_pChildren->data->arr;
        CCNode *tempItem;

        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
            while(j>=0 && ( tempItem->m_nZOrder < x[j]->m_nZOrder || ( tempItem->m_nZOrder== x[j]->m_nZOrder && tempItem->m_nOrderOfArrival < x[j]->m_nOrderOfArrival ) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }

        //don't need to check children recursively, that's done in visit of each child

        m_bReorderChildDirty = false;
    }
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
    // quick return if not visible. children won't be drawn.
    if (!m_bIsVisible)
    {
        return;
    }
    kmGLPushMatrix();

     if (m_pGrid && m_pGrid->isActive())
     {
         m_pGrid->beforeDraw();
     }

    this->transform();

    CCNode* pNode = NULL;
    unsigned int i = 0;

    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
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
        // self draw
        this->draw();

        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            if (pNode)
            {
                pNode->visit();
            }
        }        
    }
    else
    {
        this->draw();
    }

    // reset for next frame
    m_nOrderOfArrival = 0;

     if (m_pGrid && m_pGrid->isActive())
     {
         m_pGrid->afterDraw(this);
    }
 
    kmGLPopMatrix();
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
    kmMat4 transfrom4x4;

    // Convert 3x3 into 4x4 matrix
    CCAffineTransform tmpAffine = this->nodeToParentTransform();
    CGAffineToGL(&tmpAffine, transfrom4x4.mat);

    // Update Z vertex manually
    transfrom4x4.mat[14] = m_fVertexZ;

    kmGLMultMatrix( &transfrom4x4 );


    // XXX: Expensive calls. Camera should be integrated into the cached affine matrix
    if ( m_pCamera != NULL && !(m_pGrid != NULL && m_pGrid->isActive()) )
    {
        bool translate = (m_tAnchorPointInPoints.x != 0.0f || m_tAnchorPointInPoints.y != 0.0f);

        if( translate )
            kmGLTranslatef(RENDER_IN_SUBPIXEL(m_tAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(m_tAnchorPointInPoints.y), 0 );

        m_pCamera->locate();

        if( translate )
            kmGLTranslatef(RENDER_IN_SUBPIXEL(-m_tAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(-m_tAnchorPointInPoints.y), 0 );
    }

}


void CCNode::onEnter()
{
    arrayMakeObjectsPerformSelector(m_pChildren, onEnter, CCNode*);

    this->resumeSchedulerAndActions();

    m_bIsRunning = true;

    if (m_nScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeFunctionWithIntegerData(m_nScriptHandler, kCCNodeOnEnter);
    }
}

void CCNode::onEnterTransitionDidFinish()
{
    arrayMakeObjectsPerformSelector(m_pChildren, onEnterTransitionDidFinish, CCNode*);
}

void CCNode::onExitTransitionDidStart()
{
    arrayMakeObjectsPerformSelector(m_pChildren, onExitTransitionDidStart, CCNode*);
}

void CCNode::onExit()
{
    this->pauseSchedulerAndActions();

    m_bIsRunning = false;

    if (m_nScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeFunctionWithIntegerData(m_nScriptHandler, kCCNodeOnExit);
    }

    arrayMakeObjectsPerformSelector(m_pChildren, onExit, CCNode*);
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

void CCNode::setActionManager(CCActionManager* actionManager)
{
    if( actionManager != m_pActionManager ) {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(m_pActionManager);
        m_pActionManager = actionManager;
    }
}

CCActionManager* CCNode::getActionManager()
{
    return m_pActionManager;
}

CCAction * CCNode::runAction(CCAction* action)
{
    CCAssert( action != NULL, "Argument must be non-nil");
    m_pActionManager->addAction(action, this, !m_bIsRunning);
    return action;
}

void CCNode::stopAllActions()
{
    m_pActionManager->removeAllActionsFromTarget(this);
}

void CCNode::stopAction(CCAction* action)
{
    m_pActionManager->removeAction(action);
}

void CCNode::stopActionByTag(int tag)
{
    CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
    m_pActionManager->removeActionByTag(tag, this);
}

CCAction * CCNode::getActionByTag(int tag)
{
    CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
    return m_pActionManager->getActionByTag(tag, this);
}

unsigned int CCNode::numberOfRunningActions()
{
    return m_pActionManager->numberOfRunningActionsInTarget(this);
}

// CCNode - Callbacks

void CCNode::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != m_pScheduler ) {
        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(m_pScheduler);
        m_pScheduler = scheduler;
    }
}

CCScheduler* CCNode::getScheduler()
{
    return m_pScheduler;
}

void CCNode::scheduleUpdate()
{
    scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
    m_pScheduler->scheduleUpdateForTarget(this, priority, !m_bIsRunning);
}

void CCNode::unscheduleUpdate()
{
    m_pScheduler->unscheduleUpdateForTarget(this);
}

void CCNode::schedule(SEL_SCHEDULE selector)
{
    this->schedule(selector, 0.0f, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCAssert( selector, "Argument must be non-nil");
    CCAssert( interval >=0, "Argument must be positive");

    m_pScheduler->scheduleSelector(selector, this, interval, !m_bIsRunning, repeat, delay);
}

void CCNode::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void CCNode::unschedule(SEL_SCHEDULE selector)
{
    // explicit nil handling
    if (selector == 0)
        return;

    m_pScheduler->unscheduleSelector(selector, this);
}

void CCNode::unscheduleAllSelectors()
{
    m_pScheduler->unscheduleAllSelectorsForTarget(this);
}

void CCNode::resumeSchedulerAndActions()
{
    m_pScheduler->resumeTarget(this);
    m_pActionManager->resumeTarget(this);
}

void CCNode::pauseSchedulerAndActions()
{
    m_pScheduler->pauseTarget(this);
    m_pActionManager->pauseTarget(this);
}

CCAffineTransform CCNode::nodeToParentTransform(void)
{
    if (m_bIsTransformDirty) 
    {

        // Translate values
        float x = m_tPosition.x;
        float y = m_tPosition.y;

        if (m_bIgnoreAnchorPointForPosition) 
        {
            x += m_tAnchorPointInPoints.x;
            y += m_tAnchorPointInPoints.y;
        }

        // Rotation values
        float c = 1, s = 0;
        if (m_fRotation) 
        {
            float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
            c = cosf(radians);
            s = sinf(radians);
        }

        bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );


        // optimization:
        // inline anchor point calculation if skew is not needed
        if (! needsSkewMatrix && !m_tAnchorPointInPoints.equals(CCPointZero))
        {
            x += c * -m_tAnchorPointInPoints.x * m_fScaleX + -s * -m_tAnchorPointInPoints.y * m_fScaleY;
            y += s * -m_tAnchorPointInPoints.x * m_fScaleX +  c * -m_tAnchorPointInPoints.y * m_fScaleY;
        }


        // Build Transform Matrix
        m_tTransform = CCAffineTransformMake( c * m_fScaleX,  s * m_fScaleX,
            -s * m_fScaleY, c * m_fScaleY,
            x, y );

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix) 
        {
            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
                tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
                0.0f, 0.0f );
            m_tTransform = CCAffineTransformConcat(skewMatrix, m_tTransform);

            // adjust anchor point
            if (!m_tAnchorPointInPoints.equals(CCPointZero))
            {
                m_tTransform = CCAffineTransformTranslate(m_tTransform, -m_tAnchorPointInPoints.x, -m_tAnchorPointInPoints.y);
            }
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
    CCPoint ret = CCPointApplyAffineTransform(worldPoint, worldToNodeTransform());
    return ret;
}

CCPoint CCNode::convertToWorldSpace(const CCPoint& nodePoint)
{
    CCPoint ret = CCPointApplyAffineTransform(nodePoint, nodeToWorldTransform());
    return ret;
}

CCPoint CCNode::convertToNodeSpaceAR(const CCPoint& worldPoint)
{
    CCPoint nodePoint = convertToNodeSpace(worldPoint);
    return ccpSub(nodePoint, m_tAnchorPointInPoints);
}

CCPoint CCNode::convertToWorldSpaceAR(const CCPoint& nodePoint)
{
    CCPoint pt = ccpAdd(nodePoint, m_tAnchorPointInPoints);
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
    CCPoint point = touch->getLocation();
    return this->convertToNodeSpace(point);
}
CCPoint CCNode::convertTouchToNodeSpaceAR(CCTouch *touch)
{
    CCPoint point = touch->getLocation();
    return this->convertToNodeSpaceAR(point);
}

NS_CC_END


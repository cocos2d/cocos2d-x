#include "CCEGLViewProtocol.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCDirector.h"
#include "cocoa/CCSet.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCInteger.h"

NS_CC_BEGIN

static CCTouch* s_pTouches[CC_MAX_TOUCHES] = { NULL };
static unsigned int s_indexBitsUsed = 0;
static CCDictionary s_TouchesIntergerDict;

static int getUnUsedIndex()
{
    int i;
    int temp = s_indexBitsUsed;

    for (i = 0; i < CC_MAX_TOUCHES; i++) {
        if (! (temp & 0x00000001)) {
            s_indexBitsUsed |= (1 <<  i);
            return i;
        }

        temp >>= 1;
    }

    // all bits are used
    return -1;
}

static void removeUsedIndexBit(int index)
{
    if (index < 0 || index >= CC_MAX_TOUCHES) 
    {
        return;
    }

    unsigned int temp = 1 << index;
    temp = ~temp;
    s_indexBitsUsed &= temp;
}

CCEGLViewProtocol::CCEGLViewProtocol()
: m_pDelegate(NULL)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_eResolutionPolicy(kResolutionUnKnown)
{
}

CCEGLViewProtocol::~CCEGLViewProtocol()
{

}

void CCEGLViewProtocol::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCAssert(resolutionPolicy != kResolutionUnKnown, "should set resolutionPolicy");
    
    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    m_obDesignResolutionSize.setSize(width, height);
    
    m_fScaleX = (float)m_obScreenSize.width / m_obDesignResolutionSize.width;
    m_fScaleY = (float)m_obScreenSize.height / m_obDesignResolutionSize.height;
    
    if (resolutionPolicy == kResolutionNoBorder)
    {
        m_fScaleX = m_fScaleY = MAX(m_fScaleX, m_fScaleY);
    }
    
    if (resolutionPolicy == kResolutionShowAll)
    {
        m_fScaleX = m_fScaleY = MIN(m_fScaleX, m_fScaleY);
    }

    if ( resolutionPolicy == kResolutionFixedHeight) {
    	m_fScaleX = m_fScaleY;
    	m_obDesignResolutionSize.width = ceilf(m_obScreenSize.width/m_fScaleX);
    }

    if ( resolutionPolicy == kResolutionFixedWidth) {
    	m_fScaleY = m_fScaleX;
    	m_obDesignResolutionSize.height = ceilf(m_obScreenSize.height/m_fScaleY);
    }

    // calculate the rect of viewport    
    float viewPortW = m_obDesignResolutionSize.width * m_fScaleX;
    float viewPortH = m_obDesignResolutionSize.height * m_fScaleY;

    m_obViewPortRect.setRect((m_obScreenSize.width - viewPortW) / 2, (m_obScreenSize.height - viewPortH) / 2, viewPortW, viewPortH);
    
    m_eResolutionPolicy = resolutionPolicy;
    
	// reset director's member variables to fit visible rect
    CCDirector::sharedDirector()->m_obWinSizeInPoints = getDesignResolutionSize();
    CCDirector::sharedDirector()->createStatsLabel();
    CCDirector::sharedDirector()->setGLDefaultValues();
}

const CCSize& CCEGLViewProtocol::getDesignResolutionSize() const 
{
    return m_obDesignResolutionSize;
}

const CCSize& CCEGLViewProtocol::getFrameSize() const
{
    return m_obScreenSize;
}

void CCEGLViewProtocol::setFrameSize(float width, float height)
{
    m_obDesignResolutionSize = m_obScreenSize = CCSizeMake(width, height);
}

CCSize  CCEGLViewProtocol::getVisibleSize() const
{
    if (m_eResolutionPolicy == kResolutionNoBorder)
    {
        return CCSizeMake(m_obScreenSize.width/m_fScaleX, m_obScreenSize.height/m_fScaleY);
    }
    else 
    {
        return m_obDesignResolutionSize;
    }
}

CCPoint CCEGLViewProtocol::getVisibleOrigin() const
{
    if (m_eResolutionPolicy == kResolutionNoBorder)
    {
        return CCPointMake((m_obDesignResolutionSize.width - m_obScreenSize.width/m_fScaleX)/2, 
                           (m_obDesignResolutionSize.height - m_obScreenSize.height/m_fScaleY)/2);
    }
    else 
    {
        return CCPointZero;
    }
}

void CCEGLViewProtocol::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCEGLViewProtocol::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
               (GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
               (GLsizei)(w * m_fScaleX),
               (GLsizei)(h * m_fScaleY));
}

void CCEGLViewProtocol::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
              (GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
              (GLsizei)(w * m_fScaleX),
              (GLsizei)(h * m_fScaleY));
}

bool CCEGLViewProtocol::isScissorEnabled()
{
	return (GL_FALSE == glIsEnabled(GL_SCISSOR_TEST)) ? false : true;
}

CCRect CCEGLViewProtocol::getScissorRect()
{
	GLfloat params[4];
	glGetFloatv(GL_SCISSOR_BOX, params);
	float x = (params[0] - m_obViewPortRect.origin.x) / m_fScaleX;
	float y = (params[1] - m_obViewPortRect.origin.y) / m_fScaleY;
	float w = params[2] / m_fScaleX;
	float h = params[3] / m_fScaleY;
	return CCRectMake(x, y, w, h);
}

void CCEGLViewProtocol::setViewName(const char* pszViewName)
{
    if (pszViewName != NULL && strlen(pszViewName) > 0)
    {
        strncpy(m_szViewName, pszViewName, sizeof(m_szViewName));
    }
}

const char* CCEGLViewProtocol::getViewName()
{
    return m_szViewName;
}

void CCEGLViewProtocol::handleTouchesBegin(int num, int ids[], float xs[], float ys[])
{
    CCSet set;
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        CCInteger* pIndex = (CCInteger*)s_TouchesIntergerDict.objectForKey(id);
        int nUnusedIndex = 0;

        // it is a new touch
        if (pIndex == NULL)
        {
            nUnusedIndex = getUnUsedIndex();

            // The touches is more than MAX_TOUCHES ?
            if (nUnusedIndex == -1) {
                CCLOG("The touches is more than MAX_TOUCHES, nUnusedIndex = %d", nUnusedIndex);
                continue;
            }

            CCTouch* pTouch = s_pTouches[nUnusedIndex] = new CCTouch();
			pTouch->setTouchInfo(nUnusedIndex, (x - m_obViewPortRect.origin.x) / m_fScaleX, 
                                     (y - m_obViewPortRect.origin.y) / m_fScaleY);
            
            //CCLOG("x = %f y = %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);
            
            CCInteger* pInterObj = new CCInteger(nUnusedIndex);
            s_TouchesIntergerDict.setObject(pInterObj, id);
            set.addObject(pTouch);
            pInterObj->release();
        }
    }

    if (set.count() == 0)
    {
        CCLOG("touchesBegan: count = 0");
        return;
    }

    m_pDelegate->touchesBegan(&set, NULL);
}

void CCEGLViewProtocol::handleTouchesMove(int num, int ids[], float xs[], float ys[])
{
    CCSet set;
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        CCInteger* pIndex = (CCInteger*)s_TouchesIntergerDict.objectForKey(id);
        if (pIndex == NULL) {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }

        CCLOGINFO("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        CCTouch* pTouch = s_pTouches[pIndex->getValue()];
        if (pTouch)
        {
			pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x) / m_fScaleX, 
								(y - m_obViewPortRect.origin.y) / m_fScaleY);
            
            set.addObject(pTouch);
        }
        else
        {
            // It is error, should return.
            CCLOG("Moving touches with id: %d error", id);
            return;
        }
    }

    if (set.count() == 0)
    {
        CCLOG("touchesMoved: count = 0");
        return;
    }

    m_pDelegate->touchesMoved(&set, NULL);
}

void CCEGLViewProtocol::getSetOfTouchesEndOrCancel(CCSet& set, int num, int ids[], float xs[], float ys[])
{
    for (int i = 0; i < num; ++i)
    {
        int id = ids[i];
        float x = xs[i];
        float y = ys[i];

        CCInteger* pIndex = (CCInteger*)s_TouchesIntergerDict.objectForKey(id);
        if (pIndex == NULL)
        {
            CCLOG("if the index doesn't exist, it is an error");
            continue;
        }
        /* Add to the set to send to the director */
        CCTouch* pTouch = s_pTouches[pIndex->getValue()];        
        if (pTouch)
        {
            CCLOGINFO("Ending touches with id: %d, x=%f, y=%f", id, x, y);
			pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x) / m_fScaleX, 
								(y - m_obViewPortRect.origin.y) / m_fScaleY);

            set.addObject(pTouch);

            // release the object
            pTouch->release();
            s_pTouches[pIndex->getValue()] = NULL;
            removeUsedIndexBit(pIndex->getValue());

            s_TouchesIntergerDict.removeObjectForKey(id);

        } 
        else
        {
            CCLOG("Ending touches with id: %d error", id);
            return;
        } 

    }

    if (set.count() == 0)
    {
        CCLOG("touchesEnded or touchesCancel: count = 0");
        return;
    }
}

void CCEGLViewProtocol::handleTouchesEnd(int num, int ids[], float xs[], float ys[])
{
    CCSet set;
    getSetOfTouchesEndOrCancel(set, num, ids, xs, ys);
    m_pDelegate->touchesEnded(&set, NULL);
}

void CCEGLViewProtocol::handleTouchesCancel(int num, int ids[], float xs[], float ys[])
{
    CCSet set;
    getSetOfTouchesEndOrCancel(set, num, ids, xs, ys);
    m_pDelegate->touchesCancelled(&set, NULL);
}

const CCRect& CCEGLViewProtocol::getViewPortRect() const
{
    return m_obViewPortRect;
}

float CCEGLViewProtocol::getScaleX() const
{
    return m_fScaleX;
}

float CCEGLViewProtocol::getScaleY() const
{
    return m_fScaleY;
}

NS_CC_END

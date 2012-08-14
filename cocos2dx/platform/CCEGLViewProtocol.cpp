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
, m_fScreenScaleFactor(1.0f)
, m_fYScale(1.0f)
, m_fXScale(1.0f)
, m_bIsRetinaEnabled(false)
, m_eResolutionPolicy(kResolutionUnKnown)
{
}

CCEGLViewProtocol::~CCEGLViewProtocol()
{

}

void CCEGLViewProtocol::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCAssert(m_bIsRetinaEnabled == false, "can not enable retina while set design resolution size!");
    CCAssert(resolutionPolicy != kResolutionUnKnown, "should set resolutionPolicy");
    
    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    m_obDesignResolutionSize.setSize(width, height);
    
    m_fXScale = (float)m_obScreenSize.width / m_obDesignResolutionSize.width;
    m_fYScale = (float)m_obScreenSize.height / m_obDesignResolutionSize.height;
    
    if (resolutionPolicy == kCCResolutionNoBorder)
    {
        m_fXScale = m_fYScale = MAX(m_fXScale, m_fYScale);
    }
    
    if (resolutionPolicy == kCCResolutionShowAll)
    {
        m_fXScale = m_fYScale = MIN(m_fXScale, m_fYScale);
    }

    // calculate the rect of viewport    
    float viewPortW = m_obDesignResolutionSize.width * m_fXScale;
    float viewPortH = m_obDesignResolutionSize.height * m_fYScale;

    m_obViewPortRect.setRect((m_obScreenSize.width - viewPortW) / 2, (m_obScreenSize.height - viewPortH) / 2, viewPortW, viewPortH);
    
    m_eResolutionPolicy = resolutionPolicy;
    
    //setViewPortInPoints(0, 0,m_obScreenSize.width, m_obScreenSize.height);
    
    // reset director's member vaviables to fit visible rect
    CCDirector::sharedDirector()->createStatsLabel();
    CCDirector::sharedDirector()->m_obWinSizeInPoints = CCDirector::sharedDirector()->m_obWinSizeInPixels = getSize(); 
    CCDirector::sharedDirector()->setGLDefaultValues();
}

bool CCEGLViewProtocol::enableRetina()
{
    return false;
}

CCSize CCEGLViewProtocol::getSize()
{
    return m_obDesignResolutionSize;
}

void CCEGLViewProtocol::setSize(float width, float height)
{
    m_obDesignResolutionSize = m_obScreenSize = CCSizeMake(width, height);
}

CCSize  CCEGLViewProtocol::getVisibleSize()
{
    if (m_eResolutionPolicy == kCCResolutionNoBorder)
    {
        return CCSizeMake(m_obScreenSize.width/m_fXScale, m_obScreenSize.height/m_fYScale);
    }
    else 
    {
        return m_obDesignResolutionSize;
    }
}

CCPoint CCEGLViewProtocol::getVisibleOrigin()
{
    if (m_eResolutionPolicy == kCCResolutionNoBorder)
    {
        return CCPointMake((m_obDesignResolutionSize.width - m_obScreenSize.width/m_fXScale)/2, 
                           (m_obDesignResolutionSize.height - m_obScreenSize.height/m_fYScale)/2);
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

float CCEGLViewProtocol::getScreenScaleFactor()
{
    return m_fScreenScaleFactor;
}

bool CCEGLViewProtocol::setContentScaleFactor(float contentScaleFactor)
{
    return false;
}

void CCEGLViewProtocol::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fXScale + m_obViewPortRect.origin.x),
               (GLint)(y * m_fYScale + m_obViewPortRect.origin.y),
               (GLsizei)(w * m_fXScale),
               (GLsizei)(h * m_fYScale));
}

void CCEGLViewProtocol::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fXScale + m_obViewPortRect.origin.x),
              (GLint)(y * m_fYScale + m_obViewPortRect.origin.y),
              (GLsizei)(w * m_fXScale),
              (GLsizei)(h * m_fYScale));
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
                return;
            }

            CCTouch* pTouch = s_pTouches[nUnusedIndex] = new CCTouch();
            if (m_bIsRetinaEnabled)
            {
                // on iOS, though retina is enabled, the value got from os is also 
                // relative to its original size
                pTouch->setTouchInfo(nUnusedIndex, (x - m_obViewPortRect.origin.x), 
                                     (y - m_obViewPortRect.origin.y));
            }
            else 
            {
                pTouch->setTouchInfo(nUnusedIndex, (x - m_obViewPortRect.origin.x) / m_fXScale, 
                                     (y - m_obViewPortRect.origin.y) / m_fYScale);
            }
            
            CCLOG("x = %f y = %f", pTouch->getLocationInView().x, pTouch->getLocationInView().y);
            
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
            return;
        }

        CCLOGINFO("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        CCTouch* pTouch = s_pTouches[pIndex->getValue()];
        if (pTouch)
        {
            if (m_bIsRetinaEnabled)
            {
                pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x), 
                                     (y - m_obViewPortRect.origin.y));
            }
            else 
            {
                pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x) / m_fXScale, 
                                     (y - m_obViewPortRect.origin.y) / m_fYScale);
            }
            
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
            return;
        }
        /* Add to the set to send to the director */
        CCTouch* pTouch = s_pTouches[pIndex->getValue()];        
        if (pTouch)
        {
            CCLOGINFO("Ending touches with id: %d, x=%f, y=%f", id, x, y);
            
            if (m_bIsRetinaEnabled)
            {
                pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x), 
                                     (y - m_obViewPortRect.origin.y));
            }
            else 
            {
                pTouch->setTouchInfo(pIndex->getValue(), (x - m_obViewPortRect.origin.x) / m_fXScale, 
                                     (y - m_obViewPortRect.origin.y) / m_fYScale);
            }

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

NS_CC_END

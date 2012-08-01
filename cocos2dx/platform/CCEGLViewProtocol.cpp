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
{
    strncpy(m_szViewName, "Cocos2d-x Game", sizeof(m_szViewName));
}

CCEGLViewProtocol::~CCEGLViewProtocol()
{

}

void CCEGLViewProtocol::setFrameSize(float width, float height)
{
    m_obScreenSize.setSize(width, height);
    m_obViewPortRect.size.setSize(width, height);
    m_obDesignResolutionSize.setSize(width, height);
}

CCSize CCEGLViewProtocol::getFrameSize()
{
    return m_obScreenSize;
}

void CCEGLViewProtocol::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    CCAssert(CC_CONTENT_SCALE_FACTOR() == 1.0f, "retina and scale mode can't be opened at the same time!");
    
    if (width == 0.0f || height == 0.0f)
    {
        return;
    }

    m_obDesignResolutionSize.setSize(width, height);
    
    m_fXScale = (float)m_obScreenSize.width / m_obDesignResolutionSize.width;
    m_fYScale = (float)m_obScreenSize.height / m_obDesignResolutionSize.height;
    
    if (resolutionPolicy == kResolutionScaleFullScreen)
    {
        m_fXScale = m_fYScale = MAX(m_fXScale, m_fYScale);
    }
    
    if (resolutionPolicy == kResolutionScaleNotFullScreen)
    {
        m_fXScale = m_fYScale = MIN(m_fXScale, m_fYScale);
    }

    // calculate the rect of viewport    
    float viewPortW = m_obDesignResolutionSize.width * m_fXScale;
    float viewPortH = m_obDesignResolutionSize.height * m_fYScale;

    m_obViewPortRect.setRect((m_obScreenSize.width - viewPortW) / 2, (m_obScreenSize.height - viewPortH) / 2, viewPortW, viewPortH);
}

CCSize CCEGLViewProtocol::getSize()
{
    return m_obDesignResolutionSize;
}

CCSize  CCEGLViewProtocol::getVisibleSize()
{
    /*
    float width = m_obSizeInPoint.width;
    float height = m_sSizeInPoint.height;
    
    if (m_fXScale > m_fYScale)
    {
        width *= (m_fYScale/m_fXScale);
    }
    
    if (m_fYScale > m_fXScale)
    {
        height *= (m_fXScale/m_fYScale);
    }
    
    return CCSizeMake(width, height);
     */
    
    return CCSizeZero;
}

CCPoint CCEGLViewProtocol::getVisibleOrigin()
{
    return CCPointZero;
}

void CCEGLViewProtocol::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

float CCEGLViewProtocol::getScreenScaleFactor()
{
    return m_fScreenScaleFactor;
}

bool CCEGLViewProtocol::canSetContentScaleFactor()
{
    return false;
}

void CCEGLViewProtocol::setContentScaleFactor(float contentScaleFactor)
{
    // should not run here
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

float CCEGLViewProtocol::getMainScreenScale()
{
    return -1.0f;
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
            
            CCLog("x = %f y = %f", pTouch->getLocation().x, pTouch->getLocation().y);
            
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

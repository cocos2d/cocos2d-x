#include "CCEGLViewProtocol.h"
#include "CCTouchDispatcher.h"
#include "CCDirector.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCDictionary.h"
#include "CCInteger.h"

#undef COCOS2D_DEBUG;
#define COCOS2D_DEBUG 1

NS_CC_BEGIN

#define MAX_TOUCHES  5

static CCTouch* s_pTouches[MAX_TOUCHES] = { NULL };
static unsigned int s_indexBitsUsed = 0;
static CCDictionary s_TouchesIntergerDict;

static int getUnUsedIndex()
{
    int i;
    int temp = s_indexBitsUsed;

    for (i = 0; i < MAX_TOUCHES; i++) {
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
    if (index < 0 || index >= MAX_TOUCHES) 
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
{

}

CCEGLViewProtocol::~CCEGLViewProtocol()
{

}

CCSize CCEGLViewProtocol::getSize()
{
    CCSize size(m_sSizeInPoint.width, m_sSizeInPoint.height);
    return size;
}

CCRect CCEGLViewProtocol::getViewPort()
{
    return m_rcViewPort;
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
    m_fScreenScaleFactor = contentScaleFactor;
}

void CCEGLViewProtocol::setViewPortInPoints(float x , float y , float w , float h)
{
    float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
    glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
        (GLint)(y * factor) + m_rcViewPort.origin.y,
        (GLsizei)(w * factor),
        (GLsizei)(h * factor));
}

void CCEGLViewProtocol::setScissorInPoints(float x , float y , float w , float h)
{
    float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
    glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
        (GLint)(y * factor) + m_rcViewPort.origin.y,
        (GLsizei)(w * factor),
        (GLsizei)(h * factor));
}

float CCEGLViewProtocol::getMainScreenScale()
{
    return -1.0f;
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
            pTouch->SetTouchInfo(nUnusedIndex, (x - m_rcViewPort.origin.x) / m_fScreenScaleFactor, 
                (y - m_rcViewPort.origin.y) / m_fScreenScaleFactor);

            s_TouchesIntergerDict.setObject(CCInteger::integerWithInt(nUnusedIndex), id);
            set.addObject(pTouch);
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

        CCLOG("Moving touches with id: %d, x=%f, y=%f", id, x, y);
        CCTouch* pTouch = s_pTouches[pIndex->getValue()];
        if (pTouch)
        {
            pTouch->SetTouchInfo(pIndex->getValue(), (x - m_rcViewPort.origin.x) / m_fScreenScaleFactor, 
                (y - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
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
            CCLOG("Ending touches with id: %d, x=%f, y=%f", id, x, y);

            pTouch->SetTouchInfo(pIndex->getValue(), (x - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
                (y - m_rcViewPort.origin.y) / m_fScreenScaleFactor);
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

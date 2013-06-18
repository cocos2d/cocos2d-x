#include "MutiTouchTest.h"


static ccColor3B s_TouchColors[CC_MAX_TOUCHES] = {
    ccYELLOW,
    ccBLUE,
    ccGREEN,
    ccRED,
    ccMAGENTA
};

class TouchPoint : public CCNode
{
public:
    TouchPoint()
    {
        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    }

    virtual void draw()
    {
        ccDrawColor4B(_touchColor.r, _touchColor.g, _touchColor.b, 255);
        glLineWidth(10);
        ccDrawLine( ccp(0, _touchPoint.y), ccp(getContentSize().width, _touchPoint.y) );
        ccDrawLine( ccp(_touchPoint.x, 0), ccp(_touchPoint.x, getContentSize().height) );
        glLineWidth(1);
        ccPointSize(30);
        ccDrawPoint(_touchPoint);
    }

    void setTouchPos(const CCPoint& pt)
    {
        _touchPoint = pt;
    }

    void setTouchColor(ccColor3B color)
    {
        _touchColor = color;
    }

    static TouchPoint* touchPointWithParent(CCNode* pParent)
    {
        TouchPoint* pRet = new TouchPoint();
        pRet->setContentSize(pParent->getContentSize());
        pRet->setAnchorPoint(ccp(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }

private:
    CCPoint _touchPoint;
    ccColor3B _touchColor;
};

bool MutiTouchTestLayer::init()
{
    if (CCLayer::init())
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}

static CCDictionary s_dic;

void MutiTouchTestLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void MutiTouchTestLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTouchPoint = TouchPoint::touchPointWithParent(this);
        CCPoint location = pTouch->getLocation();

        pTouchPoint->setTouchPos(location);
        pTouchPoint->setTouchColor(s_TouchColors[pTouch->getID()]);

        addChild(pTouchPoint);
        s_dic.setObject(pTouchPoint, pTouch->getID());
    }
    

}

void MutiTouchTestLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        CCPoint location = pTouch->getLocation();
        pTP->setTouchPos(location);
    }
}

void MutiTouchTestLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        removeChild(pTP, true);
        s_dic.removeObjectForKey(pTouch->getID());
    }
}

void MutiTouchTestLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

void MutiTouchTestScene::runThisTest()
{
    MutiTouchTestLayer* pLayer = MutiTouchTestLayer::create();

    addChild(pLayer, 0);

    CCDirector::sharedDirector()->replaceScene(this);
}

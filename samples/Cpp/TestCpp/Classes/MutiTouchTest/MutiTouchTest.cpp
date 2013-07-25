#include "MutiTouchTest.h"


static Color3B s_TouchColors[CC_MAX_TOUCHES] = {
    Color3B::YELLOW,
    Color3B::BLUE,
    Color3B::GREEN,
    Color3B::RED,
    Color3B::MAGENTA
};

class TouchPoint : public Node
{
public:
    TouchPoint()
    {
        setShaderProgram(ShaderCache::getInstance()->programForKey(kShader_PositionTextureColor));
    }

    virtual void draw()
    {
        ccDrawColor4B(_touchColor.r, _touchColor.g, _touchColor.b, 255);
        glLineWidth(10);
        ccDrawLine( Point(0, _touchPoint.y), Point(getContentSize().width, _touchPoint.y) );
        ccDrawLine( Point(_touchPoint.x, 0), Point(_touchPoint.x, getContentSize().height) );
        glLineWidth(1);
        ccPointSize(30);
        ccDrawPoint(_touchPoint);
    }

    void setTouchPos(const Point& pt)
    {
        _touchPoint = pt;
    }

    void setTouchColor(Color3B color)
    {
        _touchColor = color;
    }

    static TouchPoint* touchPointWithParent(Node* pParent)
    {
        TouchPoint* pRet = new TouchPoint();
        pRet->setContentSize(pParent->getContentSize());
        pRet->setAnchorPoint(Point(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }

private:
    Point _touchPoint;
    Color3B _touchColor;
};

bool MutiTouchTestLayer::init()
{
    if (Layer::init())
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}

static Dictionary s_dic;

void MutiTouchTestLayer::registerWithTouchDispatcher(void)
{
    Director::getInstance()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void MutiTouchTestLayer::ccTouchesBegan(Set *touches, Event *pEvent)
{

    for ( auto &item: *touches )
    {
        Touch* pTouch = (Touch*)item;
        TouchPoint* pTouchPoint = TouchPoint::touchPointWithParent(this);
        Point location = pTouch->getLocation();

        pTouchPoint->setTouchPos(location);
        pTouchPoint->setTouchColor(s_TouchColors[pTouch->getID()]);

        addChild(pTouchPoint);
        s_dic.setObject(pTouchPoint, pTouch->getID());
    }
    

}

void MutiTouchTestLayer::ccTouchesMoved(Set *touches, Event *pEvent)
{
    for( auto &item: *touches)
    {
        Touch* pTouch = (Touch*)item;
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        Point location = pTouch->getLocation();
        pTP->setTouchPos(location);
    }
}

void MutiTouchTestLayer::ccTouchesEnded(Set *touches, Event *pEvent)
{
    for ( auto &item: *touches )
    {
        Touch* pTouch = (Touch*)item;
        TouchPoint* pTP = (TouchPoint*)s_dic.objectForKey(pTouch->getID());
        removeChild(pTP, true);
        s_dic.removeObjectForKey(pTouch->getID());
    }
}

void MutiTouchTestLayer::ccTouchesCancelled(Set *pTouches, Event *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

void MutiTouchTestScene::runThisTest()
{
    MutiTouchTestLayer* layer = MutiTouchTestLayer::create();

    addChild(layer, 0);

    Director::getInstance()->replaceScene(this);
}

#include "MutiTouchTest.h"


static const Color3B* s_TouchColors[CC_MAX_TOUCHES] = {
    &Color3B::YELLOW,
    &Color3B::BLUE,
    &Color3B::GREEN,
    &Color3B::RED,
    &Color3B::MAGENTA
};

class TouchPoint : public Node
{
public:
    TouchPoint()
    {
        setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    }

    virtual void draw()
    {
        DrawPrimitives::setDrawColor4B(_touchColor.r, _touchColor.g, _touchColor.b, 255);
        glLineWidth(10);
        DrawPrimitives::drawLine( Point(0, _touchPoint.y), Point(getContentSize().width, _touchPoint.y) );
        DrawPrimitives::drawLine( Point(_touchPoint.x, 0), Point(_touchPoint.x, getContentSize().height) );
        glLineWidth(1);
        DrawPrimitives::setPointSize(30);
        DrawPrimitives::drawPoint(_touchPoint);
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
        auto pRet = new TouchPoint();
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

void MutiTouchTestLayer::ccTouchesBegan(Set *touches, Event  *event)
{

    for ( auto &item: *touches )
    {
        auto touch = static_cast<Touch*>(item);
        auto touchPoint = TouchPoint::touchPointWithParent(this);
        auto location = touch->getLocation();

        touchPoint->setTouchPos(location);
        touchPoint->setTouchColor(*s_TouchColors[touch->getID()]);

        addChild(touchPoint);
        s_dic.setObject(touchPoint, touch->getID());
    }
    

}

void MutiTouchTestLayer::ccTouchesMoved(Set *touches, Event  *event)
{
    for( auto &item: *touches)
    {
        auto touch = static_cast<Touch*>(item);
        auto pTP = static_cast<TouchPoint*>(s_dic.objectForKey(touch->getID()));
        auto location = touch->getLocation();
        pTP->setTouchPos(location);
    }
}

void MutiTouchTestLayer::ccTouchesEnded(Set *touches, Event  *event)
{
    for ( auto &item: *touches )
    {
        auto touch = static_cast<Touch*>(item);
        auto pTP = static_cast<TouchPoint*>(s_dic.objectForKey(touch->getID()));
        removeChild(pTP, true);
        s_dic.removeObjectForKey(touch->getID());
    }
}

void MutiTouchTestLayer::ccTouchesCancelled(Set  *touches, Event  *event)
{
    ccTouchesEnded(touches, event);
}

void MutiTouchTestScene::runThisTest()
{
    auto layer = MutiTouchTestLayer::create();

    addChild(layer, 0);

    Director::getInstance()->replaceScene(this);
}

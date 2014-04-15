#include "MutiTouchTest.h"


static const Color3B* s_TouchColors[EventTouch::MAX_TOUCHES] = {
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
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    }

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
    {
        DrawPrimitives::setDrawColor4B(_touchColor.r, _touchColor.g, _touchColor.b, 255);
        glLineWidth(10);
        DrawPrimitives::drawLine( Vector2(0, _touchPoint.y), Vector2(getContentSize().width, _touchPoint.y) );
        DrawPrimitives::drawLine( Vector2(_touchPoint.x, 0), Vector2(_touchPoint.x, getContentSize().height) );
        glLineWidth(1);
        DrawPrimitives::setPointSize(30);
        DrawPrimitives::drawPoint(_touchPoint);
    }

    void setTouchPos(const Vector2& pt)
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
        pRet->setAnchorPoint(Vector2(0.0f, 0.0f));
        pRet->autorelease();
        return pRet;
    }

private:
    Vector2 _touchPoint;
    Color3B _touchColor;
};

bool MutiTouchTestLayer::init()
{
    if (Layer::init())
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(MutiTouchTestLayer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(MutiTouchTestLayer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(MutiTouchTestLayer::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        auto title = Label::createWithSystemFont("Please touch the screen!", "", 24);
        title->setPosition(VisibleRect::top()+Vector2(0, -40));
        addChild(title);
        
        return true;
    }
    return false;
}

static Map<int, TouchPoint*> s_map;

void MutiTouchTestLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto touchPoint = TouchPoint::touchPointWithParent(this);
        auto location = touch->getLocation();

        touchPoint->setTouchPos(location);
        touchPoint->setTouchColor(*s_TouchColors[touch->getID()]);

        addChild(touchPoint);
        s_map.insert(touch->getID(), touchPoint);
    }
}

void MutiTouchTestLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    for( auto &item: touches)
    {
        auto touch = item;
        auto pTP = s_map.at(touch->getID());
        auto location = touch->getLocation();
        pTP->setTouchPos(location);
    }
}

void MutiTouchTestLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto pTP = s_map.at(touch->getID());
        removeChild(pTP, true);
        s_map.erase(touch->getID());
    }
}

void MutiTouchTestLayer::onTouchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
    onTouchesEnded(touches, event);
}

void MutiTouchTestScene::runThisTest()
{
    auto layer = MutiTouchTestLayer::create();

    addChild(layer, 0);

    Director::getInstance()->replaceScene(this);
}

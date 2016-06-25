/****************************************************************************
Copyright (c) 2016 Alfonso Grillo

    drakon.cocos@gmail.com

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

#include "GestureRecognizer.h"
#include "GestureRecognizerUtils.h"

NS_CC_BEGIN

std::vector<Color4F> GestureRecognizer::touchColors = //10 colors
{
    {1, 1, 1, 1}, // WHITE
    {1, 1, 0, 1}, // YELLOW
    {0, 1, 0, 1}, // GREEN
    {0, 0, 1, 1}, // BLUE
    {1, 0, 0, 1}, // RED
    {1, 0, 1, 1}, // MAGENTA
    {0, 0, 0, 1}, // BLACK
    {1, 0.5f, 0, 1}, // ORANGE
    {0.65f, 0.65f, 0.65f, 1}, // GRAY
    {0.5f, 0.3f, 0.7f, 1}
};

GestureRecognizer::GestureRecognizer(uint fingers) : fingerNumber(fingers)
{
    //CCLOG("Constructor GestureRecognizer");
    visibleSize = Director::getInstance()->getVisibleSize();
    addTouchListener();
    scheduleUpdate();
};

GestureRecognizer::~GestureRecognizer()
{
    //CCLOG("Destructor GestureRecognizer");
    if (listener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
        listener = nullptr;
    }
};

void GestureRecognizer::addTouchListener()
{
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan     = CC_CALLBACK_2(GestureRecognizer::_onTouchBegan, this);
    listener->onTouchMoved     = CC_CALLBACK_2(GestureRecognizer::_onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GestureRecognizer::_onTouchCancelled, this);
    listener->onTouchEnded     = CC_CALLBACK_2(GestureRecognizer::_onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GestureRecognizer::isTouchInNode(Touch* t) 
{
    // object contains point or touch started in the object and exited
    return nodeContainsThePoint(this, t->getLocation()) or mapHasKey(touches, t->getID());
}

void GestureRecognizer::setFillParentEnabled(bool enabled) 
{
    isFillParentEnabled = enabled;
}

void GestureRecognizer::setContentSize(const Size& contentSize) 
{
    //CCLOG("GestureRecognizer::setContentSize");
    isFillParentEnabled = false;
    Node::setContentSize(contentSize);
}

void GestureRecognizer::setDebugMode(bool isDebugMode, uint mask)
{
    if (isDebugMode)
    {
        debugMask = mask;
        if (not debugNode)
        {
            debugNode = DrawNode::create();
            addChild(debugNode);
            addDebugArea();
        }
    }
    else
    {
        if (debugNode)
        {
            debugMask = 0;
            debugNode->removeFromParent();
            debugNode = nullptr;
        }
    }
}

bool GestureRecognizer::isDebugModeEnabled() 
{
    return debugNode != nullptr;
}

void GestureRecognizer::setSwallowTouches(bool swallow) 
{
    if (listener)
        listener->setSwallowTouches(swallow);
}

#pragma mark - Debug node functions

// Does not support rotation for now
void GestureRecognizer::addDebugArea()
{
    if (debugNode and debugMask & GESTURE_DEBUG_AREA)
    {
        auto origin = Vec2::ZERO;
        auto dest   = origin + getBoundingBox().size;
        debugNode->setLineWidth(4.0f);
        debugNode->drawRect(origin, dest, Color4F(1.0f, 0.0f, 0.0f, 0.5f));
        debugNode->drawSolidRect(origin, dest, Color4F(1.0f, 0.0f, 0.0f, 0.2f));
        debugNode->drawDot(getBoundingBox().size * 0.5f, 3, Color4F(1.0f, 0.0f, 0.0f, 0.5f));
    }
}

void GestureRecognizer::resetDebugNode()
{
    if (debugNode)
    {
        debugNode->clear();
        addDebugArea();
    }
}

#pragma mark - Callbacks

bool GestureRecognizer::_onTouchBegan(Touch* touch, Event* ev) 
{
    if (enabled and isTouchInNode(touch))
    {
        if (debugNode and debugMask & GESTURE_DEBUG_POINTS) 
            debugNode->drawPoint(convertToNodeSpace(touch->getLocation()), 4.0f, touchColors[touch->getID()]);

        return onTouchBegan(touch, ev);
    }
    return false;
}

void GestureRecognizer::_onTouchMoved(Touch* touch, Event* ev) 
{
    if (enabled and isTouchInNode(touch))
    {
        if (debugNode and debugMask & GESTURE_DEBUG_POINTS) 
            debugNode->drawPoint(convertToNodeSpace(touch->getLocation()), 4.0f, touchColors[touch->getID()]);

        onTouchMoved(touch, ev);
    }
}

void GestureRecognizer::_onTouchCancelled(Touch* touch, Event* ev) 
{
    if (enabled and isTouchInNode(touch))
    {
        if (debugNode)
            resetDebugNode();

        onTouchCancelled(touch, ev);
    }
}

void GestureRecognizer::_onTouchEnded(Touch* touch, Event* ev) 
{
    if (enabled and isTouchInNode(touch))
    {
        if (debugNode)
            resetDebugNode();

        onTouchEnded(touch, ev);
    }
}

#pragma mark - Helper functions

Point GestureRecognizer::mean(const TouchesMap& map) const
{
    Point result = Point::ZERO;
    if ( not map.empty() )
    {
        float size = map.size();
        for (auto& pair : map)
            result += pair.second;
        return result / size;
    }
    return result;
}

void GestureRecognizer::scheduleTimeout(std::function<void(float)> func)
{
    unschedule(GESTURE_TIMEOUT_KEY);
    scheduleOnce(func, timeoutSeconds, GESTURE_TIMEOUT_KEY);
}

#pragma mark - Update

void GestureRecognizer::update(float delta) 
{
    // Gesture recognizer content size matches with parent content size
    Node::update(delta);
    if (isFillParentEnabled) 
    {
        auto parent = getParent();
        if ( parent and not parent->getContentSize().equals(getContentSize()) ) 
        {
            Node::setContentSize(parent->getContentSize());
            resetDebugNode();
        }
    }
}


NS_CC_END
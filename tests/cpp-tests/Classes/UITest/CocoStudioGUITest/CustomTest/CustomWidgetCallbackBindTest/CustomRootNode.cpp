#include "CustomRootNode.h"

#include "ui/UIText.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

CustomRootNode::CustomRootNode()
{
    _touchTypes.push_back("Touch: begin");
    _touchTypes.push_back("Touch: moved");
    _touchTypes.push_back("Touch: ended");
    _touchTypes.push_back("Touch: canceled");
    _click = "Click";
    _eventTypes.push_back("Event: selected");
    _eventTypes.push_back("Event: unselected");
}

Widget::ccWidgetTouchCallback CustomRootNode::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "onTouch")
    {
        return CC_CALLBACK_2(CustomRootNode::onTouch, this);
    }

    return nullptr;
}

Widget::ccWidgetClickCallback CustomRootNode::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(CustomRootNode::onClick, this);
    }

    return nullptr;
}

Widget::ccWidgetEventCallback CustomRootNode::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(CustomRootNode::onEvent, this);
    }
    return nullptr;
}

void CustomRootNode::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
    info->setString(_touchTypes.at((int)type));
}

void CustomRootNode::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
    info->setString(_click);
}

void CustomRootNode::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
    info->setString(_eventTypes.at(eventType));
}




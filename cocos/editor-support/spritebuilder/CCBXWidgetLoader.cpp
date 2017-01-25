#include "CCBXWidgetLoader.h"
#include "ui/UIWidget.h"
#include "audio/include/SimpleAudioEngine.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_ENABLED("userInteractionEnabled");
static const std::string PROPERTY_CLICK("block");
static const std::string PROPERTY_TOUCH("blockTouch");
static const std::string PROPERTY_SOUND("sound");
    
WidgetLoader *WidgetLoader::create()
{
    WidgetLoader *ret = new WidgetLoader();
    ret->autorelease();
    return ret;
}
    
Node *WidgetLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::Widget *widget = ui::Widget::create();
    widget->setAnchorPoint(Vec2(0.0f, 0.0f));
    return widget;
}
    
void WidgetLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    ui::Widget *widget = dynamic_cast<ui::Widget*>(node);
    widget->setTouchEnabled(_enabled);
    widget->ignoreContentAdaptWithSize(false);
}
    
void WidgetLoader::setCallbacks(Node* node, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *parentOwner) const
{
    ccReaderClickCallback click;
    ccReaderTouchCallback touch;
    if(!_click.name.empty())
    {
        switch (_click.type) {
            case TargetType::NONE:
                CCLOG("no assigment type for name:%s", _click.name.c_str());
                break;
                
            case TargetType::DOCUMENT_ROOT:
            {
                CCBXReaderOwner *rootOwner = dynamic_cast<CCBXReaderOwner*>(rootNode);
                if(rootOwner)
                {
                    if(!(click = rootOwner->onResolveCCBClickSelector(_click.name, node)))
                    {
                        CCLOG("callback not assigned for name:%s", _click.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment document_root but root node is not CCBXReaderOwner for name:%s", _click.name.c_str());
                }
            }
                break;
                
            case TargetType::OWNER:
                if(owner)
                {
                    if(!(click = owner->onResolveCCBClickSelector(_click.name, node)))
                    {
                        CCLOG("callback not assigned for name:%s", _click.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment type owner but no owner for name:%s", _click.name.c_str());
                }
                break;
                
            case TargetType::PARENT_OWNER:
                if(parentOwner)
                {
                    if(!(click = parentOwner->onResolveCCBClickSelector(_click.name, node)))
                    {
                        CCLOG("callback not assigned for name:%s", _click.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment type owner but no parent owner for name:%s", _click.name.c_str());
                }
                break;
        }
    }
    
    if(!_touch.name.empty())
    {
        switch (_touch.type) {
            case TargetType::NONE:
                CCLOG("no assigment type for name:%s", _touch.name.c_str());
                break;
                
            case TargetType::DOCUMENT_ROOT:
            {
                CCBXReaderOwner *rootOwner = dynamic_cast<CCBXReaderOwner*>(rootNode);
                if(rootOwner)
                {
                    if(!(touch = rootOwner->onResolveCCBTouchSelector(_touch.name, node)))
                    {
                        CCLOG("variable not assigned for name:%s", _touch.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment document_root but root node is not CCBXReaderOwner for name:%s", _touch.name.c_str());
                }
            }
                break;
                
            case TargetType::OWNER:
                if(owner)
                {
                    if(!(touch = owner->onResolveCCBTouchSelector(_touch.name, node)))
                    {
                        CCLOG("variable not assigned for name:%s", _touch.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment type owner but no owner for name:%s", _touch.name.c_str());
                }
                break;
                
            case TargetType::PARENT_OWNER:
                if(parentOwner)
                {
                    if(!(touch = parentOwner->onResolveCCBTouchSelector(_touch.name, node)))
                    {
                        CCLOG("variable not assigned for name:%s", _touch.name.c_str());
                    }
                }
                else
                {
                    CCLOG("assigment type owner but no owner for name:%s", _touch.name.c_str());
                }
                break;
        }
    }
    
    ui::Widget *widget = dynamic_cast<ui::Widget*>(node);
    if(widget)
    {
        std::string sound = _sound;
        if(!sound.empty() && click)
        {
            widget->addClickEventListener([click, sound](Ref* ref){
                if(CCBXReader::getPlaySound())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sound.c_str());
                click(ref);
            });
        }
        else if(!sound.empty())
        {
            widget->addClickEventListener([sound](Ref* ref){
                if(CCBXReader::getPlaySound())
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sound.c_str());
            });
        }
        else if(click)
        {
            widget->addClickEventListener(click);
        }
    }
    if(widget && touch)
    {
        widget->addTouchEventListener(touch);
    }
}
    
WidgetLoader::WidgetLoader():_enabled(false)
{
    
}
    
WidgetLoader::~WidgetLoader()
{
    
}
    
void WidgetLoader::onHandlePropTypeClickCallback(const std::string &propertyName, bool isExtraProp, const CallbackDescription &value)
{
    if(propertyName == PROPERTY_CLICK) {
        _click = value;
    } else if(propertyName == PROPERTY_TOUCH) {
        _touch = value;
    } else {
        NodeLoader::onHandlePropTypeClickCallback(propertyName, isExtraProp, value);
    }
}
    
void WidgetLoader::onHandlePropTypeTouchCallback(const std::string &propertyName, bool isExtraProp, const CallbackDescription &value)
{
    if(propertyName == PROPERTY_TOUCH) {
        _touch = value;
    } else {
        NodeLoader::onHandlePropTypeTouchCallback(propertyName, isExtraProp, value);
    }
}

void WidgetLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_ENABLED) {
        _enabled = value;
    } else {
        NodeLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}
    
void WidgetLoader::onHandlePropTypeSoundFile(const std::string &propertyName, bool isExtraProp, const std::string &value)
{
    if(propertyName == PROPERTY_SOUND){
        _sound = value;
    } else {
        WidgetLoader::onHandlePropTypeSoundFile(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END

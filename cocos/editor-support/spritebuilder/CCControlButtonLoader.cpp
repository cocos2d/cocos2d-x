#include "CCControlButtonLoader.h"
#include "CCLabel.h"
#include "CCDirector.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace spritebuilder {

#define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
#define PROPERTY_TITLE_NORMAL "title|1"
#define PROPERTY_TITLE_HIGHLIGHTED "title|2"
#define PROPERTY_TITLE_DISABLED "title|3"
#define PROPERTY_TITLECOLOR_NORMAL "titleColor|1"
#define PROPERTY_TITLECOLOR_HIGHLIGHTED "titleColor|2"
#define PROPERTY_TITLECOLOR_DISABLED "titleColor|3"
#define PROPERTY_TITLETTF_NORMAL "titleTTF|1"
#define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
#define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
#define PROPERTY_TITLETTFSIZE_NORMAL "titleTTFSize|1"
#define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
#define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
#define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"
#define PROPERTY_PREFEREDSIZE "preferredSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
#define PROPERTY_TITLE_FONTNAME "fontName"
#define PROPERTY_TITLE_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTAL_PADDING "horizontalPadding"
#define PROPERTY_VERTICAL_PADDING "verticalPadding"
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"
#define PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED "backgroundSpriteFrame|Selected"
    
#define PROPERTY_LABELCOLOR_NORMAL    "labelColor|Normal"
#define PROPERTY_LABELCOLOR_HIGHLIGHTED     "labelColor|Highlighted"
#define PROPERTY_LABELCOLOR_DISABLED     "labelColor|Disabled"
    
#define PROPERTY_LABELCOLOR     "labelColor"
#define PROPERTY_OUTLINE_COLOR     "outlineColor"
#define PROPERTY_FONT_COLOR     "fontColor"
#define PROPERTY_OUTLINE_WIDTH     "outlineWidth"
#define PROPERTY_SHADOW_COLOR     "shadowColor"

#define PROPERTY_SHADOW_BLUR_RADIUS     "shadowBlurRadius"

#define PROPERTY_SHADOW_OFFSET     "shadowOffset"
#define PROPERTY_TITLE     "title"
    
#define PROPERTY_MAXSIZE "maxSize"
    
class SpriteBuilderButtonControl : public ControlButton {
private:
    Size _maxSize;
    float _horizonPadding;
    float _verticalPadding;
public:
    static SpriteBuilderButtonControl* create() {
        SpriteBuilderButtonControl *ret = new SpriteBuilderButtonControl();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        } else
            return nullptr;
    }
    void setMaxSize(Size& size) {
        _maxSize = size;
        needsLayout();
    }
    void setHorizonPadding(float padding) {
        _horizonPadding = padding;
    }
    void setVerticalPadding(float padding) {
        _verticalPadding = padding;
    }
    void setTitleOutlineColor(Color4B color) {
        Label *titleLabel = dynamic_cast<Label*>(getTitleLabel());
        if (titleLabel) {
            titleLabel->enableOutline(color);
        }
    }
    virtual void needsLayout(void)
    {
        if (!_parentInited) {
            return;
        }
        // Hide the background and the label
        if (getTitleLabel() != nullptr) {
            getTitleLabel()->setVisible(false);
        }
        if (getBackgroundSprite()) {
            getBackgroundSprite()->setVisible(false);
        }
        // Update anchor of all labels
        this->setLabelAnchorPoint(this->_labelAnchorPoint);
        
        // Update the label to match with the current state
        _currentTitle = getTitleForState(_state);
        
        _currentTitleColor = getTitleColorForState(_state);
        
        this->setTitleLabel(getTitleLabelForState(_state));
        
        LabelProtocol* label = dynamic_cast<LabelProtocol*>(getTitleLabel());
        if (label && !_currentTitle.empty())
        {
            label->setString(_currentTitle);
        }
        
        if (getTitleLabel())
        {
            getTitleLabel()->setColor(_currentTitleColor);
        }
        if (getTitleLabel() != nullptr)
        {
            getTitleLabel()->setPosition(Point (getContentSize().width / 2, getContentSize().height / 2));
        }
        
        // Update the background sprite
        this->setBackgroundSprite(this->getBackgroundSpriteForState(_state));
        if (getBackgroundSprite() != nullptr)
        {
            getBackgroundSprite()->setPosition(Point (getContentSize().width / 2, getContentSize().height / 2));
        }
        
        // Get the title label size
        Size titleLabelSize;
        if (getTitleLabel() != nullptr)
        {
            titleLabelSize = getTitleLabel()->getBoundingBox().size;
        }
        
        // Adjust the background image if necessary
        if (_doesAdjustBackgroundImage)
        {
            // Add the margins
            if (getBackgroundSprite() != nullptr)
            {
                getBackgroundSprite()->setContentSize(Size(titleLabelSize.width + _marginH * 2, titleLabelSize.height + _marginV * 2));
            }
        }
        else
        {
            //TODO: should this also have margins if one of the preferred sizes is relaxed?
            if (getBackgroundSprite() != nullptr)
            {
                Size preferredSize = getBackgroundSprite()->getPreferredSize();
                if (preferredSize.width <= 0)
                {
                    preferredSize.width = titleLabelSize.width;
                }
                if (preferredSize.height <= 0)
                {
                    preferredSize.height = titleLabelSize.height;
                }
                
                getBackgroundSprite()->setContentSize(preferredSize);
            }
        }
        
        // Set the content size
        Rect rectTitle;
        if (getTitleLabel() != nullptr)
        {
            rectTitle = getTitleLabel()->getBoundingBox();
        }
        Rect rectBackground;
        if (getBackgroundSprite() != nullptr)
        {
            rectBackground = getBackgroundSprite()->getBoundingBox();
        }
        
        Rect maxRect = ControlUtils::RectUnion(rectTitle, rectBackground);
        if (_maxSize.width > 0 && maxRect.size.width > _maxSize.width)
            maxRect.size.width = _maxSize.width;
        
        if (_maxSize.height > 0 && maxRect.size.height > _maxSize.height)
            maxRect.size.height = _maxSize.height;
        
        if (titleLabelSize.width > maxRect.size.width - _horizonPadding * 2)
            maxRect.size.width += _horizonPadding * 2;
        
        if (titleLabelSize.height > maxRect.size.height - _verticalPadding * 2)
            maxRect.size.height += _verticalPadding * 2;
        
        setContentSize(Size(maxRect.size.width, maxRect.size.height));
        
        if (getTitleLabel() != nullptr)
        {
            getTitleLabel()->setPosition(Point(getContentSize().width/2, getContentSize().height/2));
            // Make visible the background and the label
            getTitleLabel()->setVisible(true);
        }
        
        if (getBackgroundSprite() != nullptr)
        {
            getBackgroundSprite()->setPosition(Point(getContentSize().width/2, getContentSize().height/2));
            getBackgroundSprite()->setVisible(true);
            getBackgroundSprite()->setContentSize(maxRect.size);
        }
    }
    
};
    
cocos2d::extension::ControlButton * ControlButtonLoader::createNode(cocos2d::Node * pParent, CCBReader * ccbReader) {
    auto pRet = SpriteBuilderButtonControl::create();
    return pRet;
}
void ControlButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((ControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);

    } else if(strcmp(pPropertyName, PROPERTY_TITLE_FONTNAME) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_FONTSIZE) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_HORIZONTAL_PADDING) == 0) {
        ((SpriteBuilderButtonControl *)pNode)->setHorizonPadding(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_VERTICAL_PADDING) == 0) {
        ((SpriteBuilderButtonControl *)pNode)->setVerticalPadding(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINE_WIDTH) == 0) {
        _outlineWidth = pFloatScale;
    }  else if(strcmp(pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS) == 0) {
        _shadowBlurRadius = pFloatScale;
    } else {//
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0) {
        _shadowOffset = pPosition;
    } else {
        ControlLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
    }
}
void ControlButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((ControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    
    
    if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
        ((ControlButton *)pNode)->setPreferredSize(pSize);
    } else if(strcmp(pPropertyName, PROPERTY_MAXSIZE) == 0) {
        ((SpriteBuilderButtonControl *)pNode)->setMaxSize(pSize);

    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pSpriteFrame != NULL) {

            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::NORMAL);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::HIGH_LIGHTED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::SELECTED);
        }
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::DISABLED);
        
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)-> setTitleColorForState(COLOR4F_TO_COLOR3B(pColor4F), Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_LABELCOLOR) == 0) {
        ((SpriteBuilderButtonControl *)pNode)->getTitleLabel()->setColor(COLOR4F_TO_COLOR3B(pColor4F));
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINE_COLOR) == 0) {
        _outlineColor = pColor4F;
    } else if(strcmp(pPropertyName, PROPERTY_FONT_COLOR) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::NORMAL);
        ((ControlButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::HIGH_LIGHTED);
        ((ControlButton *)pNode)->setTitleColorForState(Color3B(pColor4F.r, pColor4F.g, pColor4F.b), Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_SHADOW_COLOR) == 0) {
        _shadowColor = pColor4F;
    } else {
        ControlLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
    }
}
    
void ControlButtonLoader::updateForState(cocos2d::Node * pNode, cocos2d::extension::Control::State state) {
    Label *label = dynamic_cast<Label*>(((SpriteBuilderButtonControl *)pNode)->getTitleLabelForState(state));
    if (label) {
        float factor = Director::getInstance()->getContentScaleFactor();
        label->enableOutline(Color4B(_outlineColor.r * 255, _outlineColor.g * 255, _outlineColor.b * 255, _outlineColor.a * 255), _outlineWidth / factor);
        
        label->enableShadow(Color4B(_shadowColor.r, _shadowColor.g, _shadowColor.b, _shadowColor.a),
                            Size(_shadowOffset.x, _shadowOffset.y / factor), _shadowBlurRadius / factor);
    }
}
void ControlButtonLoader::onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader) {
    updateForState(pNode, Control::State::NORMAL);
    updateForState(pNode, Control::State::HIGH_LIGHTED);
    updateForState(pNode, Control::State::DISABLED);
    
}
    
void ControlButtonLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if (strcmp(pPropertyName, "horizontalAlignment") == 0) {
        
    } else if (strcmp(pPropertyName, "verticalAlignment") == 0) {
        
    } else

        NodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
}
};
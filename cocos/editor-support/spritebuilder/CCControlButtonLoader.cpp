#include "CCControlButtonLoader.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace spritebuilder {

#define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
    
#define PROPERTY_FONT_NAME "fontName"
#define PROPERTY_FONT_SIZE "fontSize"
#define PROPERTY_FONT_COLOR "fontColor"
    
#define PROPERTY_OUTLINE_COLOR "outlineColor"
#define PROPERTY_OUTLINE_WIDTH "outlineWidth"
    
#define PROPERTY_SHADOW_COLOR "shadowColor"
#define PROPERTY_SHADOW_BLUR_RADIUS "shadowBlurRadius"
#define PROPERTY_SHADOW_OFFSET "shadowOffset"
    
#define PROPERTY_PADDING_HORIZONTAL "horizontalPadding"
#define PROPERTY_PADDING_VERTICAL "verticalPadding"

#define PROPERTY_TITLE "title"

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
#define PROPERTY_PREFERREDSIZE "preferredSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"
#define PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED "backgroundSpriteFrame|Selected"
    
#define PROPERTY_LABELCOLOR_HIGHLIGHTED "labelColor|Highlighted"
    
#define PROPERTY_BLOCK "block"


void ControlButtonLoader::onHandlePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Vector2 pPosition, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0)
	{
        Label *label = dynamic_cast< Label* >( ((ControlButton*)pNode)->getTitleLabel() );
        TTFConfig config = label->getTTFConfig();
        
        // How can I get shadow color from label?
//        label->enableShadow(label->_shadowColor, Size(pPosition));
        label->enableShadow(Color4B::BLACK, Size(pPosition));
    }
	else
	{
		ControlLoader::onHandlePropTypePosition( pNode, pParent, pPropertyName, pPosition, pCCBReader );
    }
}

void ControlButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((ControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader) {
    if( strcmp(pPropertyName, PROPERTY_TITLE) == 0 ) {
        auto button = ((ControlButton*)pNode);
        button->setTitleForState( pString, Control::State::NORMAL );
        button->setTitleForState( pString, Control::State::HIGH_LIGHTED );
        button->setTitleForState( pString, Control::State::DISABLED );
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONT_NAME) == 0) {
        auto button = (ControlButton*)pNode;
        button->setTitleTTFForState( pFontTTF, Control::State::NORMAL );
        button->setTitleTTFForState( pFontTTF, Control::State::HIGH_LIGHTED );
        button->setTitleTTFForState( pFontTTF, Control::State::DISABLED );
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    auto button = dynamic_cast< ControlButton* >( pNode );
    Label *label = dynamic_cast< Label* >( button->getTitleLabel() );
    
    if( strcmp( pPropertyName, PROPERTY_FONT_SIZE ) == 0 )
	{
		label->setSystemFontSize( pFloatScale );
	}
	else if( strcmp( pPropertyName, PROPERTY_OUTLINE_WIDTH ) == 0 )
	{
        // Can't get outline color, and can't change outline width only....
		label->enableOutline( Color4B::BLACK, pFloatScale );
	}
	else if( strcmp( pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS ) == 0)
	{
        // Blur is not supported yet
	}
	else if( strcmp( pPropertyName, PROPERTY_PADDING_HORIZONTAL ) == 0 )
	{
		// What is horizontalPadding?
	}
	else if( strcmp( pPropertyName, PROPERTY_PADDING_VERTICAL ) == 0 )
	{
		// What is verticalPadding?
	} else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Vector2 pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((ControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFERREDSIZE) == 0) {
        ((ControlButton *)pNode)->setPreferredSize(pSize);
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

void ControlButtonLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}
    
void ControlButtonLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char* pPropertyName, Color4F pColor4F, CCBReader * pCCBReader)
{
    unsigned char r = pColor4F.r * 255;
    unsigned char g = pColor4F.g * 255;
    unsigned char b = pColor4F.b * 255;
    unsigned char a = pColor4F.a * 255;
    
    auto button = dynamic_cast< ControlButton* >( pNode );
    auto label = dynamic_cast< Label* >( button->getTitleLabel() );
    
    if( strcmp( pPropertyName, PROPERTY_FONT_COLOR ) == 0 )
    {
        label->setTextColor( Color4B(r, g, b, a) );
    }
    else if( strcmp( pPropertyName, PROPERTY_OUTLINE_COLOR ) == 0 )
    {
        label->enableOutline( Color4B(r, g, b, a) );
    }
    else if( strcmp( pPropertyName, PROPERTY_SHADOW_COLOR ) == 0 )
    {
        //
        // cocos2dx CCLabelTTF is not support shadow color, yet.
        //
        /*ccFontDefinition *tDef = label->getTextDefinition();
         label->setTextDefinition( tDef );*/
    }
    else if( strcmp( pPropertyName, PROPERTY_LABELCOLOR_HIGHLIGHTED ) == 0 )
    {
        button->setTitleColorForState( Color3B( r, g, b ), Control::State::HIGH_LIGHTED );
    }
    else
    {
        ControlLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, pCCBReader);
    }
}


void ControlButtonLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader)
{
    NodeLoader::onHandlePropTypeBlock( pNode, pParent, pPropertyName, pBlockData, pCCBReader );
}


void ControlButtonLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockCCControlData, CCBReader * pCCBReader)
{
    if( strcmp( pPropertyName, PROPERTY_BLOCK ) == 0 )
    {
        ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockCCControlData->_target, pBlockCCControlData->mSELControlHandler, pBlockCCControlData->mControlEvents);
    }
    else
    {
        ControlLoader::onHandlePropTypeBlockControl( pNode, pParent, pPropertyName, pBlockCCControlData, pCCBReader );
    }
}

};
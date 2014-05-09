#include "CCLabelTTFLoader.h"

using namespace cocos2d;

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_FONT_COLOR "fontColor"

#define PROPERTY_OUTLINE_COLOR "outlineColor"
#define PROPERTY_OUTLINE_WIDTH "outlineWidth"

#define PROPERTY_SHADOW_COLOR "shadowColor"
#define PROPERTY_SHADOW_BLUR_RADIUS "shadowBlurRadius"
#define PROPERTY_SHADOW_OFFSET "shadowOffset"

#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
#define PROPERTY_DIMENSIONS "dimensions"

namespace spritebuilder {

void LabelTTFLoader::onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Vector2 pPosition, CCBReader * ccbReader)
{
    if(strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0)
    {
        Label *label = dynamic_cast< Label* >( pNode );
        TTFConfig config = label->getTTFConfig();
        
        // How can I get shadow color from label?
//        label->enableShadow(label->_shadowColor, Size(pPosition));
        label->enableShadow(Color4B::BLACK, Size(pPosition));
    }
    else
    {
        NodeLoader::onHandlePropTypePosition( pNode, pParent, pPropertyName, pPosition, ccbReader );
    }
}
    
void LabelTTFLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char* pPropertyName, Color4F pCCColor4F, CCBReader * ccbReader )
{
    unsigned char r = pCCColor4F.r * 255;
    unsigned char g = pCCColor4F.g * 255;
    unsigned char b = pCCColor4F.b * 255;
    unsigned char a = pCCColor4F.a * 255;
    Color4B color = Color4B(r, g, b, a);
    
    Label *label = dynamic_cast< Label* >(pNode);
    if( label == nullptr ) {
        NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pCCColor4F, ccbReader);
        return;
    }
    
    if( strcmp( pPropertyName, PROPERTY_FONT_COLOR ) == 0 )
    {
        label->setTextColor(color);
        label->setOpacity( a );
    }
    else if( strcmp( pPropertyName, PROPERTY_OUTLINE_COLOR ) == 0 )
    {
        TTFConfig config = label->getTTFConfig();
        float width = config.outlineSize;
        if( width <= 0 )
        {
            label->enableOutline(color, 3);
        }
        else
        {
            label->enableOutline(color, width);
        }
        
    }
    else if( strcmp( pPropertyName, PROPERTY_SHADOW_COLOR ) == 0 )
    {
        label->enableShadow(color);
    }
    else
    {
        NodeLoader::onHandlePropTypeColor4( pNode, pParent, pPropertyName, pCCColor4F, ccbReader );
    }
}
    
void LabelTTFLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((Label *)pNode)->setColor(pColor3B);
    } else {
        NodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((Label *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((Label *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        ((Label *)pNode)->setSystemFontName(pFontTTF);
    } else {
        NodeLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeText(Node * pNode, Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        ((Label *)pNode)->setString(pText);
    } else {
        NodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        ((Label *)pNode)->setSystemFontSize(pFloatScale);
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINE_WIDTH) == 0) {
        ((Label *)pNode)->enableOutline(Color4B::BLACK, pFloatScale);
        //TODO Below code doens't work well because there is something error in setTTFConfig
//        Label *label = dynamic_cast< Label* >( pNode );
//        TTFConfig config = label->getTTFConfig();
//        config.outlineSize = pFloatScale;
//        config.fontSize = label->getSystemFontSize();
//        label->setTTFConfig(config);
	} else if(strcmp(pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS ) == 0) {
        // Not yet support shadow blur radius
	} else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
        ((Label *)pNode)->setHorizontalAlignment(TextHAlignment(pIntegerLabeled));
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
        ((Label *)pNode)->setVerticalAlignment(TextVAlignment(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size size, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_DIMENSIONS) == 0) {
        ((Label *)pNode)->setDimensions(size.width,size.height);
    } else {
        NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, size, ccbReader);
    }
}

}
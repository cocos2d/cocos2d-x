#include "CCLabelTTFLoader.h"
#include "ccMacros.h"
#include "CCDirector.h"
using namespace cocos2d;
/*
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
#define PROPERTY_DIMENSIONS "dimensions"
*/

#define PROPERTY_BLENDFUNC "blendFunc"

#define PROPERTY_STRING "string"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_ADJUSTSFONTSIZETOFIT "adjustsFontSizeToFit" // TODO:
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_COLOR "color"
#define PROPERTY_DIMENSIONS "dimensions"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_FONTCOLOR "fontColor"
#define PROPERTY_OUTLINECOLOR "outlineColor"
#define PROPERTY_OUTLINEWIDTH "outlineWidth"
#define PROPERTY_SHADOWCOLOR "shadowColor"
#define PROPERTY_SHADOWBLURRADIUS "shadowBlurRadius"
#define PROPERTY_SHADOWOFFSET "shadowOffset"
namespace spritebuilder {

    
void LabelTTFLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char * pPropertyName, Color4F pColor4F, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((Label *)pNode)->setTextColor(COLOR4F_TO_COLOR4B(pColor4F));
    } else if(strcmp(pPropertyName, PROPERTY_FONTCOLOR) == 0) {
        ((Label *)pNode)->setColor(COLOR4F_TO_COLOR3B(pColor4F));
        ((Label *)pNode)->setOpacity(pColor4F.a * 255);
    } else if(strcmp(pPropertyName, PROPERTY_OUTLINECOLOR) == 0) {
        this->_outlineColor = COLOR4F_TO_COLOR4B(pColor4F);

    } else if(strcmp(pPropertyName, PROPERTY_SHADOWCOLOR) == 0) {
        this->_shadowColor = COLOR4F_TO_COLOR4B(pColor4F);
        ((Label *)pNode)->enableShadow(this->_shadowColor, this->_shadowOffset, this->_shadowBlurRadius);
    } else {
        NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4F, ccbReader);
    }
}
void LabelTTFLoader::onHandlePropTypePosition(cocos2d::Node * pNode,cocos2d:: Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader) {
    
    if(strcmp(pPropertyName, PROPERTY_SHADOWOFFSET) == 0) {
        auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
        this->_shadowOffset = Size(pPosition.x / contentScaleFactor, pPosition.y / contentScaleFactor);
        
		((Label *)pNode)->enableShadow(this->_shadowColor, this->_shadowOffset, this->_shadowBlurRadius);
        
	} else {
        NodeLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
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
#if COCOS2D_VERSION <= 0x030000
		((Label *)pNode)->setFontName(pFontTTF);
#else
        ((Label *)pNode)->setSystemFontName(pFontTTF);
#endif
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
#if COCOS2D_VERSION <= 0x030000
		((Label *)pNode)->setFontSize(pFloatScale);
#else
        ((Label *)pNode)->setSystemFontSize(pFloatScale);
#endif
	} else if(strcmp(pPropertyName, PROPERTY_OUTLINEWIDTH) == 0) {
        this->_outlineWidth = pFloatScale;
	} else if(strcmp(pPropertyName, PROPERTY_SHADOWBLURRADIUS) == 0) {
        this->_shadowBlurRadius = pFloatScale;
   
        ((Label *)pNode)->enableShadow(this->_shadowColor, this->_shadowOffset, this->_shadowBlurRadius);
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
void LabelTTFLoader::onDone(cocos2d::Node * pNode, cocos2d::Node * pParent, CCBReader * ccbReader) {
    if (this->_outlineColor.a > 0)
        ((Label *)pNode)->enableOutline(this->_outlineColor, this->_outlineWidth);
    else
        ((Label *)pNode)->enableOutline(this->_outlineColor, 0);
}

}
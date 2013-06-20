#ifndef _CCB_CCCONTROLBUTTONLOADER_H_
#define _CCB_CCCONTROLBUTTONLOADER_H_

#include "CCControlLoader.h"
#include "../GUI/CCControlExtension/CCControlButton.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class ControlButtonLoader : public ControlLoader {
    public:
        virtual ~ControlButtonLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ControlButtonLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ControlButton);

        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader);
        virtual void onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif

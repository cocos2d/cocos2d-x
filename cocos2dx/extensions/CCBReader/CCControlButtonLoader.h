#ifndef _CCB_CCCONTROLBUTTONLOADER_H_
#define _CCB_CCCONTROLBUTTONLOADER_H_

#include "CCControlLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCControlButtonLoader : public CCControlLoader {
    public:
        virtual ~CCControlButtonLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCControlButtonLoader, loader);

    protected:
        virtual CCControl * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool, CCBReader *);
        virtual void onHandlePropTypeString(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString *, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString *, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B, CCBReader *);
};

NS_CC_EXT_END

#endif

#ifndef _CCBX_SPRITELOADER_H_
#define _CCBX_SPRITELOADER_H_

#include "CCBXNodeLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL SpriteLoader : public NodeLoader {
public:
    
    static SpriteLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    SpriteLoader();
    ~SpriteLoader();

protected:
    
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) override;
    virtual void onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value) override;
    virtual void onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &value) override;
private:
    SizeDescription _size;
    SpriteFrameDescription _spriteFrame;
    std::pair<bool,bool> _flipped;
    BlendFunc _blendFunc;
};

}

NS_CC_END

#endif

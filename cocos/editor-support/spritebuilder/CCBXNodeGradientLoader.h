#ifndef _CCBX_CCLAYERGRADIENTLOADER_H_
#define _CCBX_CCLAYERGRADIENTLOADER_H_

#include "CCBXNodeColorLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL NodeGradientLoader : public NodeColorLoader {
public:
    static NodeGradientLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;

CC_CONSTRUCTOR_ACCESS:
    NodeGradientLoader();
    ~NodeGradientLoader();
    
protected:
    virtual void onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value) override;
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypePoint(const std::string &propertyName, bool isExtraProp, const cocos2d::Point &value) override;
    
private:
    Color3B _startColor;
    Color3B _endColor;
    GLubyte _startOpacity;
    GLubyte _endOpacity;
    Point _vector;
};

}

NS_CC_END

#endif

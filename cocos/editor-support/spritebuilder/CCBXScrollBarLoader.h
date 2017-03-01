#ifndef _CCB_CCScrollBarLoader_H_
#define _CCB_CCScrollBarLoader_H_

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL ScrollBarLoader : public WidgetLoader {
public:
    
    static ScrollBarLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    
CC_CONSTRUCTOR_ACCESS:
    ScrollBarLoader();
    ~ScrollBarLoader();

protected:
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value) override;
    virtual void onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    
private:
    SpriteFrameDescription _background;
    //SpriteFrameDescription _progress;
    SpriteFrameDescription _handleNormal;
    SpriteFrameDescription _handleDisabled;
    SpriteFrameDescription _handleHiglihted;
    SpriteFrameDescription _handleMouseOver;
    FloatScaleDescription _imageScale;
    Vec4 _margins;
    Vec4 _handleMargins;
    float _zoomScale;
    float _percent;
    int _maxPercent;
    bool _isVertical;
};

}

NS_CC_END

#endif

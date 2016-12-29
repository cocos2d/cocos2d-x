#ifndef _CCB_CCLAYOUTBOXLOADER_H_
#define _CCB_CCLAYOUTBOXLOADER_H_

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

/* Forward declaration. */
class CCBReader;

class CC_DLL LayoutBoxLoader : public WidgetLoader {
public:
    
    static LayoutBoxLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const override;
    
CC_CONSTRUCTOR_ACCESS:
    LayoutBoxLoader();
    ~LayoutBoxLoader();

protected:
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value) override;
    
private:
    enum LayoutBoxDirection
    {
        /// The children will be layout out in a horizontal line.
        Horizontal,
        
        /// The children will be layout out in a vertical line.
        Vertical,
    };
    LayoutBoxDirection _direction;
    FloatScaleDescription _spacing;
    SizeDescription _dimensions;
    bool _clipping;
};

}

NS_CC_END

#endif

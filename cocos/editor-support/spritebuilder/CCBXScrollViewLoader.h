#ifndef _CCBX_CCSCROLLVIEWLOADER_H_
#define _CCBX_CCSCROLLVIEWLOADER_H_

#include "base/CCRef.h"

#include "CCBXWidgetLoader.h"

NS_CC_BEGIN
namespace spritebuilder {

class CC_DLL ScrollViewLoader : public WidgetLoader {
public:
    
    static ScrollViewLoader *create();
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) override;
    
CC_CONSTRUCTOR_ACCESS:
    ScrollViewLoader();
    ~ScrollViewLoader();

protected:
    
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value) override;
    virtual void onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, NodeLoader *value) override;
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value) override;
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value) override;
    virtual void onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value) override;
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value) override;
    virtual void onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value) override;
    
private:
    bool _verticalScrollEnabled;
    bool _horizontalScrollEnabled;
    bool _clipping;
    bool _bounce;
    bool _inertial;
    bool _scrollBar;
    NodeLoader *_file;
    FloatScaleDescription _scrollBarWidth;
    bool _scrollBarAutoHideEnabled;
    bool _scrollHideIfSizeFit;
    PositionDescription _scrollBarPositionFromCorner;
    Color3B _scrollBarColor;
    GLubyte _scrollBarOpacity;
};

}

NS_CC_END

#endif

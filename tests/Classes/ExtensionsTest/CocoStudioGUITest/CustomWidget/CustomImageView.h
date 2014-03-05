
#ifndef __TestCpp__CustomImageView__
#define __TestCpp__CustomImageView__

#include "gui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class CustomImageView : public ImageView
{
public:
    
    CustomImageView();
    ~CustomImageView();
    
    static CustomImageView* create();
    static Ref* createInstance();
    
    void setText(const std::string& text);
    const std::string& getText() const;
    
protected:
    virtual bool init() override;
    virtual void initRenderer() override;
    
protected:
    LabelTTF* _label;
};

#endif /* defined(__TestCpp__CustomImageView__) */

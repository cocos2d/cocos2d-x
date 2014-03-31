
#ifndef __TestCpp__CustomImageView__
#define __TestCpp__CustomImageView__

#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::ui;

class CustomImageView : public ImageView
{
public:
    
    CustomImageView();
    ~CustomImageView();
    
    static CustomImageView* create();
    static CCObject* createInstance();
    
    void setText(const char* text);
    const char* getText() const;
    
protected:
    virtual bool init();
    virtual void initRenderer();
    
protected:
    CCLabelTTF* _label;
};

#endif /* defined(__TestCpp__CustomImageView__) */

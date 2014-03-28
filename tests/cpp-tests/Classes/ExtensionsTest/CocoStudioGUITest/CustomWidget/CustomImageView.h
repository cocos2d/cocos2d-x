
#ifndef __TestCpp__CustomImageView__
#define __TestCpp__CustomImageView__

#include "ui/CocosGUI.h"

class CustomImageView : public cocos2d::ui::ImageView
{
public:
    
    CustomImageView();
    ~CustomImageView();
    
    static CustomImageView* create();
    static cocos2d::Ref* createInstance();
    
    void setText(const std::string& text);
    const std::string& getText() const;
    
protected:
    virtual bool init() override;
    virtual void initRenderer() override;
    
protected:
    cocos2d::Label* _label;
};

#endif /* defined(__TestCpp__CustomImageView__) */

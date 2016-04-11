

#ifndef __TestCpp__CustomImageViewReader__
#define __TestCpp__CustomImageViewReader__

#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/DictionaryHelper.h"
#include "ui/CocosGUI.h"

class CustomImageViewReader : public cocos2d::Ref
{
public:
    
    CustomImageViewReader();
    ~CustomImageViewReader();
    
    static CustomImageViewReader* getInstance();
    static void purge();
    
    virtual void setProperties(const std::string& classType, cocos2d::ui::Widget* widget, const rapidjson::Value& customOptions);
};

#endif /* defined(__TestCpp__CustomImageViewReader__) */

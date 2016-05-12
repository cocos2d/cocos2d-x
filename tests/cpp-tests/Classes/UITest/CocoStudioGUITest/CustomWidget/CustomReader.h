

#ifndef __TestCpp__CustomReader__
#define __TestCpp__CustomReader__

#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/DictionaryHelper.h"
#include "ui/CocosGUI.h"


class CustomReader : public cocos2d::Ref
{
public:
    CustomReader();
    ~CustomReader();
    
    static CustomReader* getInstance();
    static void purge();
    
    virtual void setProperties(const std::string& classType, cocos2d::ui::Widget* widget, const rapidjson::Value& customOptions);
};

#endif /* defined(__TestCpp__CustomReader__) */

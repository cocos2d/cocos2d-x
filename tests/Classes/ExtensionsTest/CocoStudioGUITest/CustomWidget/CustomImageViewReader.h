

#ifndef __TestCpp__CustomImageViewReader__
#define __TestCpp__CustomImageViewReader__

#include "cocos-ext.h"
#include "cocostudio/DictionaryHelper.h"
#include "gui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

class CustomImageViewReader : public Ref
{
public:
    
    CustomImageViewReader();
    ~CustomImageViewReader();
    
    static CustomImageViewReader* getInstance();
    static void purge();
    
    virtual void setProperties(const std::string& classType, Widget* widget, const rapidjson::Value& customOptions);
};

#endif /* defined(__TestCpp__CustomImageViewReader__) */

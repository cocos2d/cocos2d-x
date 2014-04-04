

#ifndef __TestCpp__CustomReader__
#define __TestCpp__CustomReader__

#include "extensions/cocos-ext.h"
#include "cocostudio/DictionaryHelper.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

class CustomReader : public Ref
{
public:
    CustomReader();
    ~CustomReader();
    
    static CustomReader* getInstance();
    static void purge();
    
    virtual void setProperties(const std::string& classType, Widget* widget, const rapidjson::Value& customOptions);
};

#endif /* defined(__TestCpp__CustomReader__) */

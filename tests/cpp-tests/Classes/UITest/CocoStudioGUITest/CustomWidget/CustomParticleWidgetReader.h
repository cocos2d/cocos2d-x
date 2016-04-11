//
//  CustomParticleWidgetReader.h
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#ifndef __CustomUI__CustomParticleWidgetReader__
#define __CustomUI__CustomParticleWidgetReader__

#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/DictionaryHelper.h"
#include "ui/CocosGUI.h"

class CustomParticleWidgetReader : public cocos2d::Ref
{
public:
    CustomParticleWidgetReader();
    ~CustomParticleWidgetReader();
    
    static CustomParticleWidgetReader* getInstance();
    static void purge();
    
    virtual void setProperties(const std::string& classType, cocos2d::ui::Widget* widget, const rapidjson::Value& customOptions);
};

#endif /* defined(__CustomUI__CustomParticleWidgetReader__) */

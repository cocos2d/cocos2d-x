#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_CUSTOM_GUI_READER_H

#include "cocostudio/WidgetReader/WidgetReader.h"

USING_NS_CC;

namespace cocostudio
{
    class CustomGUIReader : public Ref
    {
    public:

        CustomGUIReader();
        virtual ~CustomGUIReader();

        static CustomGUIReader* create(std::string &className, int createFunc, int setPropsFunc);

        void init(std::string &className, int createFunc, int setPropsFunc);

        Ref* createInstance();

        void setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions);

    private:
        std::string _className;
        int _createFunc;
        int _setPropsFunc;
    };
}



#endif

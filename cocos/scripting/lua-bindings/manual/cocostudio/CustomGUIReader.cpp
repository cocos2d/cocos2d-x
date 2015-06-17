#include "CustomGUIReader.h"
#include "CCLuaEngine.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

namespace cocostudio
{

    CustomGUIReader* CustomGUIReader::create(std::string &className, int createFunc, int setPropsFunc)
    {
        auto reader = new CustomGUIReader();
        reader->init(className, createFunc, setPropsFunc);
        return reader;
    }
   
    Ref* CustomGUIReader::createInstance()
    {
        Ref* result = nullptr;
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->executeFunction(_createFunc, 0, 1, [&result](lua_State* L,int numReturn){
            result = static_cast<Ref*>(tolua_tousertype(L, -1, nullptr));
            lua_pop(L, 1);
        });
        return result;
    }

    CustomGUIReader::CustomGUIReader()
    :_className()
    ,_createFunc(0)
    ,_setPropsFunc(0)
    {

    }

    CustomGUIReader::~CustomGUIReader()
    {
        if (_createFunc)
        {
            LuaEngine::getInstance()->removeScriptHandler(_createFunc);
            _createFunc = 0;
        }
        if (_setPropsFunc)
        {
            LuaEngine::getInstance()->removeScriptHandler(_setPropsFunc);
            _setPropsFunc = 0;
        }
    }

    void CustomGUIReader::init(std::string &className, int createFunc, int setPropsFunc)
    {
        _className = className;
        _createFunc = createFunc;
        _setPropsFunc = setPropsFunc;

        ObjectFactory* factoryCreate = ObjectFactory::getInstance();
        ObjectFactory::TInfo t;
        t._class = className;
        t._func = CC_CALLBACK_0(CustomGUIReader::createInstance, this);
        factoryCreate->registerType(t);

        auto guiReader = GUIReader::getInstance();
        auto objMap = guiReader->getParseObjectMap();
        (*objMap)[className] = this;
        auto callbackMap = guiReader->getParseCallBackMap();
        (*callbackMap)[className] = parseselector(CustomGUIReader::setCustomProps);
    }

	void CustomGUIReader::setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions)
	{
        if (_setPropsFunc != 0)
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            customOptions.Accept(writer);

            auto stack = LuaEngine::getInstance()->getLuaStack();
            stack->pushString(classType.c_str(), static_cast<int>(classType.size()));
            stack->pushObject(widget, "cc.Ref");
            stack->pushString(buffer.GetString(), static_cast<int>(buffer.GetSize()));
            stack->executeFunctionByHandler(_setPropsFunc, 3);
        }
	}
}

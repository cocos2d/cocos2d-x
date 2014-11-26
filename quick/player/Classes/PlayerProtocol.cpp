
#include "PlayerProtocol.h"
#include "base/ccMacros.h"

PLAYER_NS_BEGIN

USING_NS_CC;

PlayerProtocol *PlayerProtocol::_instance = nullptr;

PlayerProtocol::PlayerProtocol()
{
    CCASSERT(_instance == nullptr, "CAN NOT CREATE MORE PLAYER INSTANCE");
    _instance = this;
}

PlayerProtocol::~PlayerProtocol()
{
    _instance = nullptr;
}

PlayerProtocol *PlayerProtocol::getInstance()
{
    return _instance;
}

void PlayerProtocol::purgeInstance()
{
    if (_instance) delete _instance;
}

void PlayerProtocol::setPlayerSettings(const PlayerSettings &settings)
{
    _settings = settings;
}

PlayerSettings PlayerProtocol::getPlayerSettings() const
{
    return _settings;
}

static void glfwDropFunc(GLFWwindow *window, int count, const char **files)
{
    EventCustom forwardEvent("APP.EVENT");
    stringstream buf;
    buf << "{";
    buf << "\"name\":\"drop\",";
        buf << "\"data\":[";
        for (int i = 0; i < count; i++)
        {
            buf << "\"" << files[i] << "\"";
            if (i < count - 1)
                buf << ",";
        }
        buf << "]";
    buf << "}";
    
    forwardEvent.setDataString(buf.str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);
}

void PlayerProtocol::registerGLFWEvents()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//    glfwSetDropCallback(cocos2d::Director::getInstance()->getOpenGLView()->getWindow(), glfwDropFunc);
#endif
}

PLAYER_NS_END


#include "RuntimeCCSImpl.h"
#include "ConfigParser.h"
#include "cocostudio/CocoStudio.h"

////////////////////////////////////////

RuntimeCCSImpl *RuntimeCCSImpl::create()
{
    auto instance = new RuntimeCCSImpl();
    return instance;
}

void RuntimeCCSImpl::onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
}

void RuntimeCCSImpl::onReload(const rapidjson::Document &dArgParse, rapidjson::Document &dReplyParse)
{
}

void RuntimeCCSImpl::startScript(const std::string& file)
{
    std::string filename(file);
    if (filename.empty())
    {
        filename = ConfigParser::getInstance()->getEntryFile();
    }
    
    if (filename.rfind(".csd") != std::string::npos)
    {
        loadCSDProject(filename);
    }
    else if (filename.rfind(".csb") != std::string::npos)
    {
        loadCSBProject(filename);
    }
}

void RuntimeCCSImpl::loadCSDProject(const std::string& file)
{
    CCLOG("------------------------------------------------");
    CCLOG("LOAD Cocos Studio FILE (.csd): %s", file.c_str());
    CCLOG("------------------------------------------------");
    
    auto node = CSLoader::getInstance()->createNodeWithFlatBuffersForSimulator(file.c_str());
    auto action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator(file.c_str());
    if (action)
    {
        node->runAction(action);
        action->gotoFrameAndPlay(0);
    }
    
    if (node)
    {
        if (Director::getInstance()->getRunningScene())
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->replaceScene(scene);
        }
        else
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->runWithScene(scene);
        }
    }
}

void RuntimeCCSImpl::loadCSBProject(const std::string& file)
{
    CCLOG("\n------------------------------------------------\n");
    CCLOG("[WARNING]: using **SUITABLE** Cocos Studio generate csb file!!");
    CCLOG("LOAD Cocos Studio FILE (.csb): %s", file.c_str());
    CCLOG("\n------------------------------------------------\n");
    
    auto node = CSLoader::getInstance()->createNode(file);
    if (node)
    {
        if (Director::getInstance()->getRunningScene())
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->replaceScene(scene);
        }
        else
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->runWithScene(scene);
        }
    }
}

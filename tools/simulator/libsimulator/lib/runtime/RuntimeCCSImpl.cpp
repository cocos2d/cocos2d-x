
#include "RuntimeCCSImpl.h"
#include "ConfigParser.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIHelper.h"
#include "tinyxml2.h"

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
        Size frameSize = Director::getInstance()->getVisibleSize();
        node->setContentSize(frameSize);
        ui::Helper::doLayout(node);

        std::string inFullpath = FileUtils::getInstance()->fullPathForFilename(file).c_str();
        std::string content = FileUtils::getInstance()->getStringFromFile(file);
        tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
        document->Parse(content.c_str());
        const tinyxml2::XMLElement* rootElement = document->RootElement();
        const tinyxml2::XMLElement* element = rootElement->FirstChildElement();

        if(element)
        {
            if (strcmp("PropertyGroup", element->Name()) == 0)
            {
                const tinyxml2::XMLAttribute* attribute = element->FirstAttribute();
                while (attribute !=  nullptr)
                {
                    std::string csdType = attribute->Name();
                    if (csdType.compare("Type") == 0)
                    {
                        std::string csdValue = attribute->Value();
                        if (csdValue.compare("Skeleton") == 0 || csdValue.compare("Node") == 0)
                        {
                            node->setPosition(cocos2d::Vec2(frameSize.width / 2.0f, frameSize.height / 2.0f));
                        }
                        break;
                    }
                    attribute = attribute->Next();
                }
            }
        }

        delete document;

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
        Size frameSize = Director::getInstance()->getVisibleSize();
        node->setContentSize(frameSize);
        ui::Helper::doLayout(node);

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

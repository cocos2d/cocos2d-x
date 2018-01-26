//
//  RuntimeProtocol.cpp
//  Simulator
//
//

#include "RuntimeProtocol.h"
#include "cocos2d.h"

void RuntimeProtocol::end()
{    
}

void RuntimeProtocol::setProjectPath(const std::string& path)
{
    _projectPath = path;
}

std::string RuntimeProtocol::getProjectPath() const
{
    return _projectPath;
}

void RuntimeProtocol::startScript(const std::string& script)
{
    CCLOG("%s: NOT SUPPRT", __FUNCTION__);    
}

void RuntimeProtocol::onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    CCLOG("%s: NOT SUPPRT", __FUNCTION__);
}

void RuntimeProtocol::onClearCompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    CCLOG("%s: NOT SUPPRT", __FUNCTION__);
}

void RuntimeProtocol::onPrecompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    CCLOG("%s: NOT SUPPRT", __FUNCTION__);
}

void RuntimeProtocol::onReload(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse)
{
    CCLOG("%s: NOT SUPPRT", __FUNCTION__);
}

void RuntimeProtocol::onRemove(const std::string &filename)
{
}
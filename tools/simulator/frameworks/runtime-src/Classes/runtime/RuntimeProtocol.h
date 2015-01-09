//
//  RuntimeProtocol.h
//  Simulator
//
//

#ifndef __Simulator__RuntimeProtocol__
#define __Simulator__RuntimeProtocol__

#include <string>
#include "json/document.h"

class RuntimeProtocol
{
public:
    virtual void end();
    
    void setProjectPath(const std::string& path);
    std::string getProjectPath() const;
    virtual void startScript(const std::string& file);
    
    virtual void onStartDebuger(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    virtual void onClearCompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    virtual void onPrecompile(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);
    virtual void onReload(const rapidjson::Document& dArgParse, rapidjson::Document& dReplyParse);

protected:
    std::string _projectPath;
};

#endif /* defined(__Simulator__RuntimeBase__) */

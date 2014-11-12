
#ifndef __CCCUSTOM_FILTER__
#define __CCCUSTOM_FILTER__

#include "json/rapidjson.h"
#include "json/document.h"
#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== TestFilter

class CustomFilter : public Filter
{

public:
    static CustomFilter* create();
    static CustomFilter* create(std::string paramsStr);

    CustomFilter();

    void setParameter(const char* paramsStr);
protected:
    virtual GLProgram* loadShader();
    virtual void setUniforms(GLProgram* $glp);
    
    std::string m_vertFile;
    std::string m_fragFile;
    rapidjson::Document m_json;
};

NS_CC_EXT_END

#endif //__CCCUSTOM_FILTER__

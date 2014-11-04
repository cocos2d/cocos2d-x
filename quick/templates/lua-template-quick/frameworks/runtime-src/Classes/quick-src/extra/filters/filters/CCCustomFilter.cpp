#include "CCCustomFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN


//================== CustomFilter

CustomFilter* CustomFilter::create()
{
	CustomFilter* __filter = new CustomFilter();
	__filter->autorelease();
	return __filter;
}

CustomFilter* CustomFilter::create(std::string paramsStr)
{
	CustomFilter* __filter = CustomFilter::create();
	__filter->setParameter(paramsStr.c_str());
	return __filter;
}

CustomFilter::CustomFilter()
{
	this->shaderName = nullptr;
}

GLProgram* CustomFilter::loadShader()
{
    const GLchar* vertShader = nullptr;
    const GLchar* fragShader = nullptr;
    auto fileUtiles = FileUtils::getInstance();

    if (0 == m_vertFile.size()) {
        vertShader = ccPositionTextureColor_noMVP_vert;
    } else {
        auto vertFullPath = fileUtiles->fullPathForFilename(m_vertFile);
        auto vertSource = fileUtiles->getStringFromFile(vertFullPath);
        vertShader = vertSource.c_str();
    }
    
    auto fragmentFullPath = fileUtiles->fullPathForFilename(m_fragFile);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    fragShader = fragSource.c_str();
    
    GLProgram* __p = GLProgram::createWithByteArrays(vertShader, fragShader);

	return __p;
}

void CustomFilter::setParameter(const char* paramsStr)
{
    //m_json.Clear();
    m_json.Parse<0>(paramsStr);
    if (m_json.HasParseError())
    {
        CCLOG("CustomFilter - setParameter param is not json format:%s", m_json.GetParseError());
        return;
    }
//    if (!m_json.IsArray())
//    {
//        CCLOG("CustomFilter - setParameter param is not json format:%s", m_json.GetParseError());
//        return;
//    }
    
    for (rapidjson::Value::ConstMemberIterator it = m_json.MemberonBegin();
         it != m_json.MemberonEnd(); ++it) {
        std::string name = it->name.GetString();
        //std::string val = it->value.GetString();
        if (0 == name.compare("vert")) {
            m_vertFile = it->value.GetString();
        } else if(0 == name.compare("frag")) {
            m_fragFile = it->value.GetString();
        } else if(0 == name.compare("shaderName")) {
            shaderName = it->value.GetString();
        }
    }
    
    initProgram();
}

void CustomFilter::setUniforms(GLProgram* $cgp)
{
    for (rapidjson::Value::ConstMemberIterator it = m_json.MemberonBegin();
         it != m_json.MemberonEnd(); ++it) {
        std::string name = it->name.GetString();
        //std::string val = it->value.GetString();
        if (0 != name.compare("vert") && 0 != name.compare("frag") && 0 != name.compare("shaderName")) {
            if (rapidjson::Type::kNumberType == it->value.GetType()) {
                _pProgramState->setUniformFloat(name, it->value.GetDouble());
            } else if (rapidjson::Type::kArrayType == it->value.GetType()) {
                switch (it->value.Size()) {
                    case 2: {
                        _pProgramState->setUniformVec2(name,
                            Vec2(it->value[0u].GetDouble(), it->value[1].GetDouble()));
                        break;
                    }
                    case 3: {
                        _pProgramState->setUniformVec3(name,
                            Vec3(it->value[0u].GetDouble(), it->value[1].GetDouble(),
                                 it->value[2].GetDouble()));
                        break;
                    }
                    case 4: {
                        _pProgramState->setUniformVec4(name,
                            Vec4(it->value[0u].GetDouble(), it->value[1].GetDouble(),
                                 it->value[2].GetDouble(), it->value[2].GetDouble()));
                        break;
                    }
                    default: {
                        CCLOG("Customfilter - setUniforms invalid params number on param:%s",
                              name.c_str());
                        break;
                    }
                }
            } else {
                CCLOG("CustomFilter - setUniforms unkonw params:%s",
                      name.c_str());
            }
        }
    }
}

NS_CC_EXT_END

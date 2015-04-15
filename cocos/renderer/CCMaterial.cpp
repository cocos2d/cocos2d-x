/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCTextureCache.h"

#include "platform/CCFileUtils.h"

#include "json/document.h"

static const float MATERIAL_FORMAT_VERSION = 1.0;
static const char* MATERIAL_TYPE = "material";

NS_CC_BEGIN

Material* Material::createWithFilename(const std::string& filepath)
{
    auto validfilename = FileUtils::getInstance()->fullPathForFilename(filepath);

    if (validfilename.size() > 0)
        return new (std::nothrow) Material(validfilename);

    return nullptr;
}

Material* Material::createWithGLStateProgram(GLProgramState* programState)
{
    return new (std::nothrow) Material(programState);
}

Material::Material(cocos2d::GLProgramState *state)
{
    auto technique = Technique::createWithGLProgramState(state);
    _techniques.pushBack(technique);

    // weak pointer
    _currentTechnique = technique;
}

Material::Material(const std::string& validfilename)
: _currentTechnique(nullptr)
, _techniques()
{
    Data data = FileUtils::getInstance()->getDataFromFile(validfilename);
    char* bytes = (char*)data.getBytes();

    rapidjson::Document document;
    document.ParseInsitu<0>(bytes);

    if (document.HasParseError())
    {
        CCLOG("GetParseError %s\n", document.GetParseError());
        return;
    }

    CCASSERT(document.IsObject(), "Invalid JSON file");

    if (! parseMetadata(document)) {
        CCLOG("Error parsing Material metadata");
        return;
    }

    parseProperties(document);
}

bool Material::parseMetadata(const rapidjson::Document& jsonDocument)
{
    bool broken = false;

    const auto& metadata = jsonDocument["metadata"];
    if (metadata.IsObject())
    {
        auto version = metadata["version"].GetDouble();
        broken |= std::floor(version) != std::floor(MATERIAL_FORMAT_VERSION);

        auto type = metadata["type"].GetString();
        broken |= strcmp(type, MATERIAL_TYPE) != 0;
    }

    return !broken;
}

bool Material::parseProperties(const rapidjson::Document& jsonDocument)
{
    auto name = jsonDocument["name"].GetString();
    setName(name);

    auto& techniques = jsonDocument["techniques"];
    return parseTechniques(techniques);
}

bool Material::parseTechniques(const rapidjson::GenericValue<rapidjson::UTF8<> >& techniques)
{

    CCASSERT(techniques.IsArray(), "Invalid Techniques");

    for (rapidjson::SizeType i = 0; i < techniques.Size(); i++) {
        auto& technique = techniques[i];
        parseTechnique(technique);
    }
    return true;
}

bool Material::parseTechnique(const rapidjson::GenericValue<rapidjson::UTF8<> >& techniqueJSON)
{
    CCASSERT(techniqueJSON.IsObject(), "Invalid type for Technique. It must be an object");

    auto technique = Technique::create();
    _techniques.pushBack(technique);

    // first one is the default one
    if (!_currentTechnique)
        _currentTechnique = technique;

    // name
    if (techniqueJSON.HasMember("name"))
        setName(techniqueJSON["name"].GetString());

    // passes
    auto& passes = techniqueJSON["passes"];
    parsePasses(technique, passes);

    return true;
}

bool Material::parsePasses(Technique* technique, const rapidjson::GenericValue<rapidjson::UTF8<> >& passesJSON)
{
    CCASSERT(passesJSON.IsArray(), "Invalid type for 'passes'");

    for (rapidjson::SizeType i = 0; i < passesJSON.Size(); i++) {
        auto& pass = passesJSON[i];
        parsePass(technique, pass);
    }

    return true;
}

bool Material::parsePass(Technique* technique, const rapidjson::GenericValue<rapidjson::UTF8<> >& passJSON)
{
    auto pass = Pass::create();
    technique->addPass(pass);

    

    return true;
}


bool Material::parseRenderState(Pass* pass, const rapidjson::GenericValue<rapidjson::UTF8<> >& renderState)
{
    return true;
}

void Material::setName(const std::string&name)
{
    _name = name;
}

std::string Material::getName() const
{
    return _name;
}

Material::Material()
{
}

Material::~Material()
{
}

Technique* Material::getTechnique() const
{
    return _currentTechnique;
}
Technique* Material::getTechniqueByName(const std::string& name)
{
    for(const auto& technique : _techniques) {
        if( technique->getName() == name)
            return technique;
    }
    return nullptr;
}

Technique* Material::getTechniqueByIndex(ssize_t index)
{
    CC_ASSERT(index>=0 && index<_techniques.size() && "Invalid size");

    return _techniques.at(index);
}

void Material::addTechnique(Technique* technique)
{
    _techniques.pushBack(technique);
}

void Material::setTechnique(const std::string& techniqueName)
{
    auto technique = getTechniqueByName(techniqueName);
    if (technique)
        _currentTechnique = technique;
}

ssize_t Material::getTechniqueCount() const
{
    return _techniques.size();
}

NS_CC_END

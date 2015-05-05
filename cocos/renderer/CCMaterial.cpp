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
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"

#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

#include "json/document.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define strcasecmp _stricmp
#endif

static const float MATERIAL_FORMAT_VERSION = 1.0;
static const char* MATERIAL_TYPE = "material";

// Helpers declaration
static const char* getOptionalString(const rapidjson::GenericValue<rapidjson::UTF8<> >& json, const char* key, const char* defaultValue);
static bool isValidUniform(const char* name);

NS_CC_BEGIN

Material* Material::createWithFilename(const std::string& filepath)
{
    auto validfilename = FileUtils::getInstance()->fullPathForFilename(filepath);
    if (validfilename.size() > 0) {
        auto mat = new (std::nothrow) Material();
        if (mat && mat->initWithFile(validfilename))
        {
            mat->autorelease();
            return mat;
        }
    }

    return nullptr;
}

Material* Material::createWithGLStateProgram(GLProgramState* programState)
{
    CCASSERT(programState, "Invalid GL Program State");

    auto mat = new (std::nothrow) Material();
    if (mat && mat->initWithGLProgramState(programState))
    {
        mat->autorelease();
        return mat;

    }
    return nullptr;
}

bool Material::initWithGLProgramState(cocos2d::GLProgramState *state)
{
    auto technique = Technique::createWithGLProgramState(this, state);
    if (technique) {
        _techniques.pushBack(technique);

        // weak pointer
        _currentTechnique = technique;

        return true;
    }
    return false;
}

bool Material::initWithFile(const std::string& validfilename)
{
    Data data = FileUtils::getInstance()->getDataFromFile(validfilename);
    char* bytes = (char*)data.getBytes();
    bytes[data.getSize()-1]='\0';

    rapidjson::Document document;
    document.ParseInsitu<0>(bytes);

    if (document.HasParseError())
    {
        CCLOG("GetParseError %s\n", document.GetParseError());
        return false;
    }

    CCASSERT(document.IsObject(), "Invalid JSON file");

    if (! parseMetadata(document)) {
        CCLOG("Error parsing Material metadata");
        return false;
    }

    parseProperties(document);
    return true;
}

void Material::setTarget(cocos2d::Node *target)
{
    _target = target;
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

    auto& techniquesJSON = jsonDocument["techniques"];
    CCASSERT(techniquesJSON.IsArray(), "Invalid Techniques");

    for (rapidjson::SizeType i = 0; i < techniquesJSON.Size(); i++) {
        auto& techniqueJSON = techniquesJSON[i];
        parseTechnique(techniqueJSON);
    }

    return true;
}

bool Material::parseTechnique(const rapidjson::GenericValue<rapidjson::UTF8<> >& techniqueJSON)
{
    CCASSERT(techniqueJSON.IsObject(), "Invalid type for Technique. It must be an object");

    auto technique = Technique::create(this);
    _techniques.pushBack(technique);

    // first one is the default one
    if (!_currentTechnique)
        _currentTechnique = technique;

    // name
    if (techniqueJSON.HasMember("name"))
        technique->setName(techniqueJSON["name"].GetString());

    // passes
    auto& passesJSON = techniqueJSON["passes"];
    CCASSERT(passesJSON.IsArray(), "Invalid type for 'passes'");

    for (rapidjson::SizeType i = 0; i < passesJSON.Size(); i++) {
        auto& passJSON = passesJSON[i];
        parsePass(technique, passJSON);
    }

    return true;
}

bool Material::parsePass(Technique* technique, const rapidjson::GenericValue<rapidjson::UTF8<> >& passJSON)
{
    auto pass = Pass::create(technique);
    technique->addPass(pass);

    // Textures
    if (passJSON.HasMember("textures")) {
        auto& texturesJSON = passJSON["textures"];
        CCASSERT(texturesJSON.IsArray(), "Invalid type for 'textures'");

        for (rapidjson::SizeType i = 0; i < texturesJSON.Size(); i++) {
            auto& textureJSON = texturesJSON[i];
            parseTexture(pass, textureJSON);
        }
    }

    // Render State
    if (passJSON.HasMember("renderState")) {
        parseRenderState(pass, passJSON["renderState"]);
    }

    // Shaders
    if (passJSON.HasMember("shader")) {
        parseShader(pass, passJSON["shader"]);
    }

    return true;
}

bool Material::parseTexture(Pass* pass, const rapidjson::GenericValue<rapidjson::UTF8<> >& textureJSON)
{
    CCASSERT(textureJSON.IsObject(), "Invalid type for Texture. It must be an object");

    // required
    auto filename = textureJSON["path"].GetString();

    auto texture = Director::getInstance()->getTextureCache()->addImage(filename);
    if (!texture) {
        CCLOG("Invalid filepath");
        return false;
    }

    // optionals

    {
        Texture2D::TexParams texParams;

        // mipmap
        bool usemipmap = false;
        const char* mipmap = getOptionalString(textureJSON, "mipmap", "false");
        if (mipmap && strcasecmp(mipmap, "true")==0) {
            texture->generateMipmap();
            usemipmap = true;
        }

        // valid options: REPEAT, CLAMP
        const char* wrapS = getOptionalString(textureJSON, "wrapS", "CLAMP_TO_EDGE");
        if (strcasecmp(wrapS, "REPEAT")==0)
            texParams.wrapS = GL_REPEAT;
        else if(strcasecmp(wrapS, "CLAMP_TO_EDGE")==0)
            texParams.wrapS = GL_CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapS: %s", wrapS);


        // valid options: REPEAT, CLAMP
        const char* wrapT = getOptionalString(textureJSON, "wrapT", "CLAMP_TO_EDGE");
        if (strcasecmp(wrapT, "REPEAT")==0)
            texParams.wrapT = GL_REPEAT;
        else if(strcasecmp(wrapT, "CLAMP_TO_EDGE")==0)
            texParams.wrapT = GL_CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapT: %s", wrapT);


        // valid options: NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
        const char* minFilter = getOptionalString(textureJSON, "minFilter", mipmap ? "LINEAR_MIPMAP_NEAREST" : "LINEAR");
        if (strcasecmp(minFilter, "NEAREST")==0)
            texParams.minFilter = GL_NEAREST;
        else if(strcasecmp(minFilter, "LINEAR")==0)
            texParams.minFilter = GL_LINEAR;
        else if(strcasecmp(minFilter, "NEAREST_MIPMAP_NEAREST")==0)
            texParams.minFilter = GL_NEAREST_MIPMAP_NEAREST;
        else if(strcasecmp(minFilter, "LINEAR_MIPMAP_NEAREST")==0)
            texParams.minFilter = GL_LINEAR_MIPMAP_NEAREST;
        else if(strcasecmp(minFilter, "NEAREST_MIPMAP_LINEAR")==0)
            texParams.minFilter = GL_NEAREST_MIPMAP_LINEAR;
        else if(strcasecmp(minFilter, "LINEAR_MIPMAP_LINEAR")==0)
            texParams.minFilter = GL_LINEAR_MIPMAP_LINEAR;
        else
            CCLOG("Invalid minFilter: %s", minFilter);

        // valid options: NEAREST, LINEAR
        const char* magFilter = getOptionalString(textureJSON, "magFilter", "LINEAR");
        if (strcasecmp(magFilter, "NEAREST")==0)
            texParams.magFilter = GL_NEAREST;
        else if(strcasecmp(magFilter, "LINEAR")==0)
            texParams.magFilter = GL_LINEAR;
        else
            CCLOG("Invalid magFilter: %s", magFilter);

        texture->setTexParameters(texParams);
    }

    pass->_textures.pushBack(texture);
    return true;
}

bool Material::parseShader(Pass* pass, const rapidjson::GenericValue<rapidjson::UTF8<> >& shaderJSON)
{

    CCASSERT(shaderJSON.IsObject(), "Invalid type for 'shader'. It must be an object");

    // vertexShader
    const char* vertShader = getOptionalString(shaderJSON, "vertexShader", nullptr);

    // fragmentShader
    const char* fragShader = getOptionalString(shaderJSON, "fragmentShader", nullptr);

    // compileTimeDefines
    const char* compileTimeDefines = getOptionalString(shaderJSON, "defines", "");

    if (vertShader && fragShader)
    {
        auto glProgramState = GLProgramState::getOrCreateWithShaders(vertShader, fragShader, compileTimeDefines);
        pass->setGLProgramState(glProgramState);

        // Parse uniforms only if the GLProgramState was created
        for( auto it = shaderJSON.MemberonBegin(); it != shaderJSON.MemberonEnd(); it++)
        {
            // skip "defines", "vertexShader", "fragmentShader"
            if (isValidUniform(it->name.GetString()))
                parseUniform(glProgramState, it);
        }

//        glProgramState->updateUniformsAndAttributes();
    }

    return true;
}

bool Material::parseUniform(GLProgramState* programState, const rapidjson::Value::ConstMemberIterator& iterator)
{
    const char* key = iterator->name.GetString();
    auto& value = iterator->value;

    if (value.IsNumber()) {
        float v = value.GetDouble();
        programState->setUniformFloat(key, v);
    }
    else if (value.IsArray()) {

        int size = value.Size();
        switch (size) {
            case 1:
            {
                rapidjson::SizeType idx = 0;
                float v = value[idx].GetDouble();
                programState->setUniformFloat(key, v);
                break;
            }
            case 2:
            {
                Vec2 vect = parseUniformVec2(value);
                programState->setUniformVec2(key, vect);
                break;
            }
            case 3:
            {
                Vec3 vect = parseUniformVec3(value);
                programState->setUniformVec3(key, vect);
                break;
            }
            case 4:
            {
                Vec4 vect = parseUniformVec4(value);
                programState->setUniformVec4(key, vect);
                break;
            }
            case 16:
            {
                Mat4 mat = parseUniformMat4(value);
                programState->setUniformMat4(key, mat);
                break;
            }
            default:
                break;
        }

    }
    return true;
}

Vec2 Material::parseUniformVec2(const rapidjson::GenericValue<rapidjson::UTF8<> >& value)
{
    Vec2 ret;
    rapidjson::SizeType idx = 0;
    ret.x = value[idx++].GetDouble();
    ret.y = value[idx++].GetDouble();
    return ret;
}

Vec3 Material::parseUniformVec3(const rapidjson::GenericValue<rapidjson::UTF8<> >& value)
{
    Vec3 ret;
    rapidjson::SizeType idx = 0;
    ret.x = value[idx++].GetDouble();
    ret.y = value[idx++].GetDouble();
    ret.z = value[idx++].GetDouble();
    return ret;
}

Vec4 Material::parseUniformVec4(const rapidjson::GenericValue<rapidjson::UTF8<> >& value)
{
    Vec4 ret;
    rapidjson::SizeType idx = 0;
    ret.x = value[idx++].GetDouble();
    ret.y = value[idx++].GetDouble();
    ret.z = value[idx++].GetDouble();
    ret.w = value[idx++].GetDouble();
    return ret;
}

Mat4 Material::parseUniformMat4(const rapidjson::GenericValue<rapidjson::UTF8<> >& value)
{
    Mat4 ret;

    for(rapidjson::SizeType i= 0; i<16; i++)
        ret.m[i] = value[i].GetDouble();

    return ret;
}

bool Material::parseRenderState(Pass* pass, const rapidjson::GenericValue<rapidjson::UTF8<> >& renderState)
{
    auto state = pass->getStateBlock();

    // Parse uniforms only if the GLProgramState was created
    for( auto it = renderState.MemberonBegin(); it != renderState.MemberonEnd(); it++)
    {
        // Render state only can have "strings" or numbers as values. No objects or lists
        state->setState(it->name.GetString(), it->value.GetString());
    }

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
: _name("")
, _target(nullptr)
, _currentTechnique(nullptr)
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
        CCLOG("technique name: %s", technique->getName().c_str());
        if (technique->getName().compare(name)==0)
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

// Helpers implementation
static bool isValidUniform(const char* name)
{
    return !(strcmp(name, "defines")==0 ||
            strcmp(name, "vertexShader")==0 ||
            strcmp(name, "fragmentShader")==0);
}

static const char* getOptionalString(const rapidjson::GenericValue<rapidjson::UTF8<> >& json, const char* key, const char* defaultValue)
{
    if (json.HasMember(key)) {
        return json[key].GetString();
    }
    return defaultValue;
}


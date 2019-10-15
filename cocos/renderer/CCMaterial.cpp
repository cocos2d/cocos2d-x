/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/backend/Device.h"
#include "base/CCProperties.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "base/CCConsole.h"

#include <sstream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define strcasecmp _stricmp
#endif

NS_CC_BEGIN

namespace {
    std::string replaceDefines(const std::string &compileTimeDefines) {

        auto defineParts = Console::Utility::split(compileTimeDefines, ';');
        std::stringstream ss;
        for (auto &p : defineParts)
        {
            if (p.find("#define ") == std::string::npos)
            {
                ss << "#define " << p << std::endl;
            }
            else
            {
                ss << p << std::endl;
            }
        }
        return ss.str();

    }
}

// Helpers declaration
static const char* getOptionalString(Properties* properties, const char* key, const char* defaultValue);
static bool isValidUniform(const char* name);

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

Material* Material::createWithProperties(Properties* materialProperties)
{
    auto mat = new (std::nothrow) Material();
    if (mat && mat->initWithProperties(materialProperties))
    {
        mat->autorelease();
        return mat;
    }
    return nullptr;
}

Material* Material::createWithProgramState(backend::ProgramState* programState)
{
    CCASSERT(programState, "Invalid Program State");

    auto mat = new (std::nothrow) Material();
    if (mat && mat->initWithProgramState(programState))
    {
        mat->autorelease();
        return mat;

    }
    return nullptr;
}

bool Material::initWithProgramState(backend::ProgramState *state)
{
    auto technique = Technique::createWithProgramState(this, state);
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
    // Warning: properties is not a "Ref" object, must be manually deleted
    Properties* properties = Properties::createNonRefCounted(validfilename);

    // get the first material
    parseProperties((strlen(properties->getNamespace()) > 0) ? properties : properties->getNextNamespace());

    CC_SAFE_DELETE(properties);
    return true;
}

bool Material::initWithProperties(Properties* materialProperties)
{
    return parseProperties(materialProperties);
}

void Material::draw(MeshCommand* meshCommands, float globalZOrder, backend::Buffer* vertexBuffer, backend::Buffer* indexBuffer,
                    CustomCommand::PrimitiveType primitive, CustomCommand::IndexFormat indexFormat,
                    unsigned int indexCount, const Mat4& modelView)
{
    int i = 0;
    for (const auto& pass: _currentTechnique->_passes)
    {
        pass->draw(&meshCommands[i], globalZOrder, vertexBuffer, indexBuffer,primitive, indexFormat, indexCount, modelView);
        i++;
    }
}


void Material::setTarget(cocos2d::Node *target)
{
    _target = target;
}

bool Material::parseProperties(Properties* materialProperties)
{
    setName(materialProperties->getId());
    auto space = materialProperties->getNextNamespace();
    while (space)
    {
        const char* name = space->getNamespace();
        if (strcmp(name, "technique") == 0)
        {
            parseTechnique(space);
        }
        else if (strcmp(name, "renderState") == 0)
        {
            parseRenderState(&_renderState.getStateBlock(), space);
        }

        space = materialProperties->getNextNamespace();

    }
    return true;
}

bool Material::parseTechnique(Properties* techniqueProperties)
{
    auto technique = Technique::create(this);
    _techniques.pushBack(technique);

    // first one is the default one
    if (!_currentTechnique)
        _currentTechnique = technique;

    // name
    technique->setName(techniqueProperties->getId());


    // passes
    auto space = techniqueProperties->getNextNamespace();
    while (space)
    {
        const char* name = space->getNamespace();
        if (strcmp(name, "pass") == 0)
        {
            parsePass(technique, space);
        }
        else if (strcmp(name, "renderState") == 0)
        {
            parseRenderState(&technique->getStateBlock(), space);
        }

        space = techniqueProperties->getNextNamespace();
    }

    return true;
}

bool Material::parsePass(Technique* technique, Properties* passProperties)
{
    auto pass = Pass::create(technique);
    technique->addPass(pass);

    pass->setName(passProperties->getId());

    // Pass can have 3 different namespaces:
    //  - one or more "sampler"
    //  - one "renderState"
    //  - one "shader"

    auto space = passProperties->getNextNamespace();
    while (space)
    {
        const char* name = space->getNamespace();
        if (strcmp(name, "shader") == 0)
        {
            parseShader(pass, space);
        }
        else if (strcmp(name, "renderState") == 0)
        {
            parseRenderState(&pass->_renderState.getStateBlock(), space);
        }
        else {
            CCASSERT(false, "Invalid namespace");
            return false;
        }

        space = passProperties->getNextNamespace();
    }

    return true;
}

// cocos2d-x doesn't support Samplers yet. But will be added soon
bool Material::parseSampler(backend::ProgramState* programState, Properties* samplerProperties)
{
    CCASSERT(samplerProperties->getId(), "Sampler must have an id. The id is the uniform name");
    
    // required
    auto filename = samplerProperties->getString("path");

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
        const char* mipmap = getOptionalString(samplerProperties, "mipmap", "false");
        if (mipmap && strcasecmp(mipmap, "true")==0) {
            texture->generateMipmap();
            usemipmap = true;
        }

        // valid options: REPEAT, CLAMP
        const char* wrapS = getOptionalString(samplerProperties, "wrapS", "CLAMP_TO_EDGE");
        if (strcasecmp(wrapS, "REPEAT")==0)
            texParams.sAddressMode = backend::SamplerAddressMode::REPEAT;
        else if(strcasecmp(wrapS, "CLAMP_TO_EDGE")==0)
            texParams.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapS: %s", wrapS);


        // valid options: REPEAT, CLAMP
        const char* wrapT = getOptionalString(samplerProperties, "wrapT", "CLAMP_TO_EDGE");
        if (strcasecmp(wrapT, "REPEAT")==0)
            texParams.tAddressMode = backend::SamplerAddressMode::REPEAT;
        else if(strcasecmp(wrapT, "CLAMP_TO_EDGE")==0)
            texParams.tAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapT: %s", wrapT);


        // valid options: NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
        const char* minFilter = getOptionalString(samplerProperties, "minFilter", usemipmap ? "LINEAR_MIPMAP_NEAREST" : "LINEAR");
        if (strcasecmp(minFilter, "NEAREST")==0)
            texParams.minFilter = backend::SamplerFilter::NEAREST;
        else if(strcasecmp(minFilter, "LINEAR")==0)
            texParams.minFilter = backend::SamplerFilter::LINEAR;
        else if(strcasecmp(minFilter, "NEAREST_MIPMAP_NEAREST")==0)
            texParams.minFilter = backend::SamplerFilter::NEAREST;
        else if(strcasecmp(minFilter, "LINEAR_MIPMAP_NEAREST")==0)
            texParams.minFilter = backend::SamplerFilter::LINEAR;
        else if(strcasecmp(minFilter, "NEAREST_MIPMAP_LINEAR")==0)
            texParams.minFilter = backend::SamplerFilter::LINEAR;
        else if(strcasecmp(minFilter, "LINEAR_MIPMAP_LINEAR")==0)
            texParams.minFilter = backend::SamplerFilter::LINEAR;
        else
            CCLOG("Invalid minFilter: %s", minFilter);

        // valid options: NEAREST, LINEAR
        const char* magFilter = getOptionalString(samplerProperties, "magFilter", "LINEAR");
        if (strcasecmp(magFilter, "NEAREST")==0)
            texParams.magFilter = backend::SamplerFilter::NEAREST;
        else if(strcasecmp(magFilter, "LINEAR")==0)
            texParams.magFilter = backend::SamplerFilter::LINEAR;
        else
            CCLOG("Invalid magFilter: %s", magFilter);

        texture->setTexParameters(texParams);
    }

    auto textureName = samplerProperties->getId();
    auto location = programState->getUniformLocation(textureName);
    
    if (!location)
    {
        CCLOG("warning: failed to find texture uniform location %s when parsing material", textureName);
        return false;
    }

    if (_textureSlots.find(textureName) == _textureSlots.end())
    {
        _textureSlots[textureName] = _textureSlotIndex;
        programState->setTexture(location, _textureSlotIndex++, texture->getBackendTexture());
    }
    else
    {
        programState->setTexture(location, _textureSlots[textureName], texture->getBackendTexture());
    }

    return true;
}

bool Material::parseShader(Pass* pass, Properties* shaderProperties)
{
    // vertexShader
    const char* vertShader = getOptionalString(shaderProperties, "vertexShader", nullptr);

    // fragmentShader
    const char* fragShader = getOptionalString(shaderProperties, "fragmentShader", nullptr);

    // compileTimeDefines
    const char* compileTimeDefines = getOptionalString(shaderProperties, "defines", "");

    auto *fu = FileUtils::getInstance();

    if (vertShader && fragShader)
    {

        auto vertShaderSrc = fu->getStringFromFile(vertShader);
        auto fragShaderSrc = fu->getStringFromFile(fragShader);

        auto defs = replaceDefines(compileTimeDefines);

        vertShaderSrc = defs + "\n" + vertShaderSrc;
        fragShaderSrc = defs + "\n" + fragShaderSrc;

        auto* program = backend::Device::getInstance()->newProgram(vertShaderSrc, fragShaderSrc);
        auto programState = new backend::ProgramState(program);
        pass->setProgramState(programState);

        // Parse uniforms only if the GLProgramState was created
        auto property = shaderProperties->getNextProperty();
        while (property)
        {
            if (isValidUniform(property))
            {
                parseUniform(programState, shaderProperties, property);
            }

            property = shaderProperties->getNextProperty();
        }

        auto space = shaderProperties->getNextNamespace();
        while (space)
        {
            const char* name = space->getNamespace();
            if (strcmp(name, "sampler") == 0)
            {
                parseSampler(programState, space);
            }
            space = shaderProperties->getNextNamespace();
        }
        CC_SAFE_RELEASE(program);
        CC_SAFE_RELEASE(programState);
    }

    return true;
}

bool Material::parseUniform(backend::ProgramState* programState, Properties* properties, const char* uniformName)
{
    bool ret = true;

    auto type = properties->getType(uniformName);

    backend::UniformLocation location;
    location = programState->getUniformLocation(uniformName);

    switch (type) {
        case Properties::Type::NUMBER:
        {
            auto f = properties->getFloat(uniformName);
            programState->setUniform(location, &f, sizeof(f));
            break;
        }

        case Properties::Type::VECTOR2:
        {
            Vec2 v2;
            properties->getVec2(uniformName, &v2);
            programState->setUniform(location, &v2, sizeof(v2));
            break;
        }

        case Properties::Type::VECTOR3:
        {
            Vec3 v3;
            properties->getVec3(uniformName, &v3);
            programState->setUniform(location, &v3, sizeof(v3));
            break;
        }

        case Properties::Type::VECTOR4:
        {
            Vec4 v4;
            properties->getVec4(uniformName, &v4);
            programState->setUniform(location, &v4, sizeof(v4));
            break;
        }

        case Properties::Type::MATRIX:
        {
            Mat4 m4;
            properties->getMat4(uniformName, &m4);
            programState->setUniform(location, &m4.m, sizeof(m4.m));
            break;
        }

        case Properties::Type::STRING:
        default:
        {
            // Assume this is a parameter auto-binding.
            programState->setParameterAutoBinding(uniformName, properties->getString());
            break;
        }
    }
    return ret;
}


bool Material::parseRenderState(RenderState::StateBlock *state, Properties* properties)
{
    if (nullptr == state)
    {
        return false;
    }

    auto property = properties->getNextProperty();
    while (property)
    {
        // Parse uniforms only if the GLProgramState was created
        // Render state only can have "strings" or numbers as values. No new namespaces
        state->setState(property, properties->getString(property));

        property = properties->getNextProperty();
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
, _currentTechnique(nullptr)
, _target(nullptr)
{
}

Material::~Material()
{
}

Material* Material::clone() const
{
    auto material = new (std::nothrow) Material();
    if (material)
    {
        //RenderState::cloneInto(material);
        material->_renderState = _renderState;

        for (const auto& technique: _techniques)
        {
            auto t = technique->clone();
            t->_material = material;
            material->_techniques.pushBack(t);
        }

        // current technique
        auto name = _currentTechnique->getName();
        material->_currentTechnique = material->getTechniqueByName(name);
        material->_textureSlots = material->_textureSlots;
        material->_textureSlotIndex = material->_textureSlotIndex;
        material->autorelease();
    }
    return material;
}

Technique* Material::getTechnique() const
{
    return _currentTechnique;
}

const Vector<Technique*>& Material::getTechniques() const
{
    return _techniques;
}

Technique* Material::getTechniqueByName(const std::string& name)
{
    for(const auto& technique : _techniques) {
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


// Helpers implementation
static bool isValidUniform(const char* name)
{
    return !(strcmp(name, "defines")==0 ||
            strcmp(name, "vertexShader")==0 ||
            strcmp(name, "fragmentShader")==0);
}

static const char* getOptionalString(Properties* properties, const char* key, const char* defaultValue)
{

    const char* ret = properties->getString(key);
    if (!ret)
        ret = defaultValue;

    return ret;
}

NS_CC_END

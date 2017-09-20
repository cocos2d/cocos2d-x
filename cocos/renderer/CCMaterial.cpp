/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.

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
#include "base/CCProperties.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define strcasecmp _stricmp
#endif

NS_CC_BEGIN

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
            parseRenderState(this, space);
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
            parseRenderState(this, space);
        }

        space = techniqueProperties->getNextNamespace();
    }

    return true;
}

bool Material::parsePass(Technique* technique, Properties* passProperties)
{
    auto pass = Pass::create(technique);
    technique->addPass(pass);

    // Pass can have 3 different namespaces:
    //  - one or more "sampler"
    //  - one "renderState"
    //  - one "shader"

    auto space = passProperties->getNextNamespace();
    while (space)
    {
        const char* name = space->getNamespace();
        if (strcmp(name, "shader") == 0)
            parseShader(pass, space);
        else if (strcmp(name, "renderState") == 0)
            parseRenderState(pass, space);
        else {
            CCASSERT(false, "Invalid namespace");
            return false;
        }

        space = passProperties->getNextNamespace();
    }

    return true;
}

// cocos2d-x doesn't support Samplers yet. But will be added soon
bool Material::parseSampler(GLProgramState* glProgramState, Properties* samplerProperties)
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
            texParams.wrapS = GL_REPEAT;
        else if(strcasecmp(wrapS, "CLAMP_TO_EDGE")==0)
            texParams.wrapS = GL_CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapS: %s", wrapS);


        // valid options: REPEAT, CLAMP
        const char* wrapT = getOptionalString(samplerProperties, "wrapT", "CLAMP_TO_EDGE");
        if (strcasecmp(wrapT, "REPEAT")==0)
            texParams.wrapT = GL_REPEAT;
        else if(strcasecmp(wrapT, "CLAMP_TO_EDGE")==0)
            texParams.wrapT = GL_CLAMP_TO_EDGE;
        else
            CCLOG("Invalid wrapT: %s", wrapT);


        // valid options: NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
        const char* minFilter = getOptionalString(samplerProperties, "minFilter", usemipmap ? "LINEAR_MIPMAP_NEAREST" : "LINEAR");
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
        const char* magFilter = getOptionalString(samplerProperties, "magFilter", "LINEAR");
        if (strcasecmp(magFilter, "NEAREST")==0)
            texParams.magFilter = GL_NEAREST;
        else if(strcasecmp(magFilter, "LINEAR")==0)
            texParams.magFilter = GL_LINEAR;
        else
            CCLOG("Invalid magFilter: %s", magFilter);

        texture->setTexParameters(texParams);
    }

    glProgramState->setUniformTexture(samplerProperties->getId(), texture);
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

    if (vertShader && fragShader)
    {
        auto glProgramState = GLProgramState::getOrCreateWithShaders(vertShader, fragShader, compileTimeDefines);
        pass->setGLProgramState(glProgramState);

        // Parse uniforms only if the GLProgramState was created
        auto property = shaderProperties->getNextProperty();
        while (property)
        {
            if (isValidUniform(property))
            {
                parseUniform(glProgramState, shaderProperties, property);
            }

            property = shaderProperties->getNextProperty();
        }

        auto space = shaderProperties->getNextNamespace();
        while (space)
        {
            const char* name = space->getNamespace();
            if (strcmp(name, "sampler") == 0)
            {
                parseSampler(glProgramState, space);
            }
            space = shaderProperties->getNextNamespace();
        }
    }

    return true;
}

bool Material::parseUniform(GLProgramState* programState, Properties* properties, const char* uniformName)
{
    bool ret = true;

    auto type = properties->getType(uniformName);

    switch (type) {
        case Properties::Type::NUMBER:
        {
            auto f = properties->getFloat(uniformName);
            programState->setUniformFloat(uniformName, f);
            break;
        }

        case Properties::Type::VECTOR2:
        {
            Vec2 v2;
            properties->getVec2(uniformName, &v2);
            programState->setUniformVec2(uniformName, v2);
            break;
        }

        case Properties::Type::VECTOR3:
        {
            Vec3 v3;
            properties->getVec3(uniformName, &v3);
            programState->setUniformVec3(uniformName, v3);
            break;
        }

        case Properties::Type::VECTOR4:
        {
            Vec4 v4;
            properties->getVec4(uniformName, &v4);
            programState->setUniformVec4(uniformName, v4);
            break;
        }

        case Properties::Type::MATRIX:
        {
            Mat4 m4;
            properties->getMat4(uniformName, &m4);
            programState->setUniformMat4(uniformName, m4);
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


bool Material::parseRenderState(RenderState* renderState, Properties* properties)
{
    auto state = renderState->getStateBlock();

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
        RenderState::cloneInto(material);

        for (const auto& technique: _techniques)
        {
            auto t = technique->clone();
            t->_parent = material;
            material->_techniques.pushBack(t);
        }

        // current technique
        auto name = _currentTechnique->getName();
        material->_currentTechnique = material->getTechniqueByName(name);

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

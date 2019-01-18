#include "ProgramCache.h"
#include "Device.h"
#include "ShaderModule.h"
#include "renderer/ccShaders.h"

CC_BACKEND_BEGIN

std::unordered_map<std::size_t, backend::Program*>  ProgramCache::_cachedPrograms;
ProgramCache* ProgramCache::_sharedProgramCache = nullptr;

ProgramCache* ProgramCache::getInstance()
{
    if(!_sharedProgramCache)
    {
        _sharedProgramCache = new (std::nothrow) ProgramCache();
        if(!_sharedProgramCache->init())
        {
            CC_SAFE_RELEASE(_sharedProgramCache);
        }
    }
    return _sharedProgramCache;
}

void ProgramCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedProgramCache);
}

ProgramCache::~ProgramCache()
{
    for(auto& program : _cachedPrograms)
    {
        CC_SAFE_RELEASE(program.second);
    }
    CCLOGINFO("deallocing ProgramCache: %p", this);
    ShaderCache::destroyInstance();
}

bool ProgramCache::init()
{
    addProgram(positionTextureColor_vert, positionTextureColor_frag);
    addProgram(positionTextureColor_vert, etc1_frag);
    addProgram(positionTextureColor_vert, label_distanceNormal_frag);
    addProgram(positionTextureColor_vert, label_normal_frag);
    addProgram(positionTextureColor_vert, labelOutline_frag);
    addProgram(positionTextureColor_vert, labelDistanceFieldGlow_frag);
    addProgram(positionTextureColor_vert, labelDistanceFieldGlow_frag);
    addProgram(positionColorLengthTexture_vert, positionColorLengthTexture_frag);
    addProgram(positionColorTextureAsPointsize_vert, positionColor_frag);
    addProgram(positionColor_vert, positionColor_frag);
    addProgram(position_vert, layer_radialGradient_frag);
    addProgram(positionTexture_vert, positionTexture_frag);
    addProgram(positionTextureColor_vert, positionTextureColorAlphaTest_frag);
    addProgram(positionUColor_vert, positionUColor_frag);
    return true;
}

void ProgramCache::addProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    std::string shaderSource = vertexShader + fragmentShader;
    auto key = std::hash<std::string>{}(shaderSource);
    auto program = backend::Device::getInstance()->newProgram(vertexShader, fragmentShader);
    ProgramCache::_cachedPrograms.emplace(key, program);
}

backend::Program* ProgramCache::newProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    std::string shaderSource = vertexShader + fragmentShader;
    auto key = std::hash<std::string>{}(shaderSource);
    const auto& iter = ProgramCache::_cachedPrograms.find(key);
    if (ProgramCache::_cachedPrograms.end() != iter)
    {
        CC_SAFE_RETAIN(iter->second);
        return iter->second;
    }
    
    auto program = backend::Device::getInstance()->newProgram(vertexShader, fragmentShader);
    ProgramCache::_cachedPrograms.emplace(key, program);
    
    return program;
}

void ProgramCache::removeProgram(backend::Program* program)
{
    if (!program)
    {
        return;
    }
    
    for (auto it = _cachedPrograms.cbegin(); it != _cachedPrograms.cend();)
    {
        if (it->second == program)
        {
            it->second->release();
            it = _cachedPrograms.erase(it);
            break;
        }
        else
            ++it;
    }
}

void ProgramCache::removeUnusedProgram()
{
    for (auto iter = _cachedPrograms.cbegin(); iter != _cachedPrograms.cend();)
    {
        auto program = iter->second;
        if (program->getReferenceCount() == 1)
        {
//            CCLOG("cocos2d: TextureCache: removing unused program");
            program->release();
            iter = _cachedPrograms.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void ProgramCache::removeAllProgram()
{
    for (auto& program : _cachedPrograms) {
        program.second->release();
    }
    _cachedPrograms.clear();
}

CC_BACKEND_END

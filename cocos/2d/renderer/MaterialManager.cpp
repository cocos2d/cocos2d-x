//
// Created by NiTe Luo on 11/6/13.
//


#include "MaterialManager.h"

NS_CC_BEGIN

using namespace std;

static MaterialManager* s_instance = 0;

MaterialManager *MaterialManager::getInstance()
{
    if(!s_instance)
    {
        s_instance = new MaterialManager();
        if(!s_instance->init())
        {
            CC_SAFE_DELETE(s_instance);
        }
    }
    return s_instance;
}

void MaterialManager::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_instance);
}

void MaterialManager::getMaterialID(GLuint textureID, GLuint shaderID, BlendFunc blendFunc)
{

}

void MaterialManager::registerTexture(GLuint textureID)
{

}

void MaterialManager::unregisterTexture(GLuint textureID)
{

}

void MaterialManager::registerShader(GLuint shaderID)
{

}

void MaterialManager::unregisterShader(GLuint shaderID)
{

}

MaterialManager::MaterialManager()
{

}

MaterialManager::~MaterialManager()
{

}

bool MaterialManager::init()
{
    return true;
}

int MaterialManager::getTextureID(GLuint textureID)
{
    return 0;
}

int MaterialManager::getShaderID(GLuint shaderID)
{
    return 0;
}

int MaterialManager::getBlendFuncID(BlendFunc blendFunc)
{
    int32_t key = (blendFunc.src << 16) + blendFunc.dst;
    int id;
    auto it = _blendFuncMapping.find(key);
    if (it != _blendFuncMapping.end())
    {
        return it->second;
    }
    else
    {
        //Add Blending function to the list
        id = (int)_blendFuncMapping.size();
        _blendFuncMapping[key] = id;
        return id;
    }
}

NS_CC_END
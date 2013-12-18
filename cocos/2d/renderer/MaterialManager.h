//
// Created by NiTe Luo on 11/6/13.
//



#ifndef _CC_MATERIALMANAGER_H_
#define _CC_MATERIALMANAGER_H_

#include "CCPlatformMacros.h"
#include "CCObject.h"
#include "ccTypes.h"
#include <map>

NS_CC_BEGIN
using namespace std;

class MaterialManager : public Object
{
public:
    static MaterialManager* getInstance();
    static void destroyInstance();


    void getMaterialID(GLuint textureID, GLuint shaderID, BlendFunc blendFunc);

    void registerTexture(GLuint textureID);
    void unregisterTexture(GLuint textureID);

    void registerShader(GLuint shaderID);
    void unregisterShader(GLuint shaderID);
    
    int getBlendFuncID(BlendFunc blendFunc);
    
protected:
    MaterialManager();
    virtual ~MaterialManager();

    bool init();

    int getTextureID(GLuint textureID);
    int getShaderID(GLuint shaderID);

    map<GLuint, int> _textureIDMapping;
    map<GLuint, int> _shaderIDMapping;
    map<int32_t, int> _blendFuncMapping;
};

NS_CC_END

#endif //_CC_MATERIALMANAGER_H_

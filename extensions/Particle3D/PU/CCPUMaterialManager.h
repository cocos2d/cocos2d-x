/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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
 ****************************************************************************/

#ifndef __CC_PU_PARTICLE_3D_MATERIAL_MANAGER_H__
#define __CC_PU_PARTICLE_3D_MATERIAL_MANAGER_H__
#include "math/CCMath.h"
#include "base/ccTypes.h"
#include <vector>

NS_CC_BEGIN

class CC_DLL PUMaterial : public Ref
{
public:

    PUMaterial();

    std::string fileName;
    std::string name;
    bool isEnabledLight;
    Vec4 ambientColor;
    Vec4 diffuseColor;
    Vec4 specularColor;
    Vec4 emissiveColor;
    float shininess;

    BlendFunc blendFunc;
    bool depthTest;
    bool depthWrite;

    std::string textureFile;
    GLuint wrapMode;
};

class CC_DLL PUMaterialCache
{
public:

    PUMaterialCache();
    ~PUMaterialCache();

    static PUMaterialCache* Instance();

    bool loadMaterials(const std::string &file);
    bool loadMaterialsFromSearchPaths(const std::string &fileFolder);
    PUMaterial* getMaterial(const std::string &name);
    void addMaterial(PUMaterial *material);

protected:

    typedef std::vector<PUMaterial *> MaterialVector;
    MaterialVector _materialMap;
};

NS_CC_END

#endif


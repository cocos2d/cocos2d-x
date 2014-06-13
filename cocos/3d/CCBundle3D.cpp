/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "CCBundle3D.h"
#include "CCAnimationCurve.h"
#include "CCAnimation3D.h"
#include "CCSprite3D.h"
#include "CCMeshSkin.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

Bundle3D* Bundle3D::_instance = nullptr;

Bundle3D* Bundle3D::getInstance()
{
    if (_instance == nullptr)
        _instance = new Bundle3D();
    return _instance;
}

void Bundle3D::purgeBundle3D()
{
    CC_SAFE_DELETE(_instance);
}

bool Bundle3D::load(const std::string& path)
{
    return true;
}

/**
 * load mesh data from bundle
 * @param id The ID of the mesh, load the first Mesh in the bundle if it is empty
 */
bool Bundle3D::loadMeshData(const std::string& id, MeshData* meshdata)
{
    meshdata->resetData();
    meshdata->vertexSizeInFloat = 13 * 4;
    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    //dabing's data
//   float vert[] = {0.f,50.f,0.f,  0.f,0.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
//                   0.f,0.f,50.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
//                   50.f,0.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
//                  50.f,50.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f};
    float vert[] = {0.f,50.f,0.f,  0.f,0.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
        0.f,0.f,50.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
        50.f,0.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
        -50.f,0.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f};

    
    //float vert[] = {0.f,50.f,0.f,  0.f,0.f,50.f, 50.f,0.f,0.f, -50.f,0.f,0.f};
    memcpy(&meshdata->vertex[0], vert, meshdata->vertexSizeInFloat * sizeof(float));
    
    meshdata->numIndex = 4 * 3;
    //meshdata->numIndex = 3;
    meshdata->indices.resize(meshdata->numIndex);
    unsigned short index[] = {0,1,2, 0,3,1, 0,2,3, 3,2,1};
    //unsigned short index[] = {0,3,2};
    //unsigned short index[] = {0,1,2};
    memcpy(&meshdata->indices[0], index, meshdata->numIndex * sizeof(unsigned short));
    
    meshdata->attribCount = 4;
    meshdata->attribs.resize(meshdata->attribCount);
    meshdata->attribs[0].attribSizeBytes = 3 * sizeof(float);
    meshdata->attribs[0].size = 3;
    meshdata->attribs[0].type = GL_FLOAT;
    meshdata->attribs[0].vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
    
    meshdata->attribs[1].attribSizeBytes = 2 * sizeof(float);
    meshdata->attribs[1].size = 2;
    meshdata->attribs[1].type = GL_FLOAT;
    meshdata->attribs[1].vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
    
    meshdata->attribs[2].attribSizeBytes = 4 * sizeof(float);
    meshdata->attribs[2].size = 4;
    meshdata->attribs[2].type = GL_FLOAT;
    meshdata->attribs[2].vertexAttrib = GLProgram::VERTEX_ATTRIB_BLEND_INDEX;
    
    meshdata->attribs[3].attribSizeBytes = 4 * sizeof(float);
    meshdata->attribs[3].size = 4;
    meshdata->attribs[3].type = GL_FLOAT;
    meshdata->attribs[3].vertexAttrib = GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;
    
    return true;
}

//
/**
 * load skin data from bundle
 * @param id The ID of the skin, load the first Skin in the bundle if it is empty
 */
bool Bundle3D::loadSkinData(const std::string& id, SkinData* skindata)
{
    skindata->resetData();
    skindata->boneNames.push_back("root");
    skindata->inverseBindPoseMatrices.push_back(Mat4::IDENTITY);
    skindata->rootBoneIndex = 0;
    
    return true;
}

//
/**
 * load material data from bundle
 * @param id The ID of the material, load the first Material in the bundle if it is empty
 */
bool Bundle3D::loadMaterialData(const std::string& id, MaterialData* materialdata)
{
    materialdata->texturePath = "Sprite3DTest/boss.png";
    return true;
}

/**
 * load material data from bundle
 * @param id The ID of the animation, load the first animation in the bundle if it is empty
 */
bool Bundle3D::loadAnimationData(const std::string& id, Animation3DData* animationdata)
{
    animationdata->_rotationKeys.clear();
    animationdata->_scaleKeys.clear();
    animationdata->_translationKeys.clear();
    
    animationdata->_totalTime = 3.0f;
    
    float keytime1[] = {0.f, 0.333f, 0.667f, 1.f};
    std::string boneName = "root";
    
    Quaternion quat;
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), 0, &quat);
    animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime1[0], quat));
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(90), &quat);
     animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime1[1], quat));
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(180), &quat);
    animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime1[2], quat));
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(270), &quat);
    animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime1[3], quat));
    
    animationdata->_translationKeys[boneName].push_back(Animation3DData::Vec3Key(keytime1[0], Vec3(0.0f, 0.0f, 0.0f)));
    animationdata->_translationKeys[boneName].push_back(Animation3DData::Vec3Key(keytime1[1], Vec3(0.0f, 20.0f, 0.0f)));
    animationdata->_translationKeys[boneName].push_back(Animation3DData::Vec3Key(keytime1[2], Vec3(20.0f, 0.0f, 0.0f)));
    animationdata->_translationKeys[boneName].push_back(Animation3DData::Vec3Key(keytime1[3], Vec3(0.0f, 0.0f, 20.0f)));
    
    return true;
}

Bundle3D::Bundle3D()
{
    
}
Bundle3D::~Bundle3D()
{
    
}



NS_CC_END

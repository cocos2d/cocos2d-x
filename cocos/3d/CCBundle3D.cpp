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

Bundle3D::MeshData::MeshData()
: vertex(nullptr)
, vertexSizeInFloat(0)
, indices(nullptr)
, numIndex(0)
, attribs(nullptr)
, attribCount(0)
{
    
}
Bundle3D::MeshData::~MeshData()
{
    resetData();
}
void Bundle3D::MeshData::resetData()
{
    CC_SAFE_DELETE_ARRAY(vertex);
    CC_SAFE_DELETE_ARRAY(indices);
    CC_SAFE_DELETE_ARRAY(attribs);
    vertexSizeInFloat = 0;
    numIndex = 0;
    attribCount = 0;
}

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
    meshdata->vertex = new float[meshdata->vertexSizeInFloat];
    float vert[] = {0.f,50.f,0.f,  0.f,0.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
                    0.f,0.f,50.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
                    50.f,0.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f,
                   -50.f,0.f,0.f,  1.f,1.f,  0.f,0.f,0.f,0.f,   1.f,0.f,0.f,0.f};
    //float vert[] = {0.f,50.f,0.f,  0.f,0.f,50.f, 50.f,0.f,0.f, -50.f,0.f,0.f};
    memcpy(meshdata->vertex, vert, meshdata->vertexSizeInFloat * sizeof(float));
    
    meshdata->numIndex = 4 * 3;
    //meshdata->numIndex = 3;
    meshdata->indices = new unsigned short[meshdata->numIndex];
    unsigned short index[] = {0,1,2, 0,3,1, 0,2,3, 3,2,1};
    //unsigned short index[] = {0,3,2};
    //unsigned short index[] = {0,1,2};
    memcpy(meshdata->indices, index, meshdata->numIndex * sizeof(unsigned short));
    
    meshdata->attribCount = 4;
    meshdata->attribs = new MeshVertexAttrib[meshdata->attribCount];
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
    auto animation = animationdata->animation;
    animation->_duration = 3.0f;
    for (auto it : animation->_boneCurves) {
        CC_SAFE_DELETE(it.second);
    }
    animation->_boneCurves.clear();
    auto curve = new Animation3D::Curve();
    float keytime[] = {0.f, 1.f};
    float pos[] = {0.f, 0.f, 0.f, 20.f, 0.f, 0.f};
    //curve->translateCurve = Animation3D::Curve::AnimationCurveVec3::create(keytime, pos, 2);
    //curve->translateCurve->retain();
    
    float keytime1[] = {0.f, 0.333f, 0.667f, 1.f};
    float rot[4 * 4];
    Quaternion quat;
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), 0, &quat);
    rot[0] = quat.x, rot[1] = quat.y, rot[2] = quat.z, rot[3] = quat.w;
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(90), &quat);
    rot[4] = quat.x, rot[5] = quat.y, rot[6] = quat.z, rot[7] = quat.w;
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(180), &quat);
    rot[8] = quat.x, rot[9] = quat.y, rot[10] = quat.z, rot[11] = quat.w;
    Quaternion::createFromAxisAngle(Vec3(1.f, 0.f, 0.f), MATH_DEG_TO_RAD(270), &quat);
    rot[12] = quat.x, rot[13] = quat.y, rot[14] = quat.z, rot[15] = quat.w;
    curve->rotCurve = Animation3D::Curve::AnimationCurveQuat::create(keytime1, rot, 4);
    curve->rotCurve->retain();
    
    animation->_boneCurves["root"] = curve;
    
    return true;
}

Bundle3D::Bundle3D()
{
    
}
Bundle3D::~Bundle3D()
{
    
}



NS_CC_END

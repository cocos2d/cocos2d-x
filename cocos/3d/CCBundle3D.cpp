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

#include "CCBundle3DData.h"

NS_CC_BEGIN


void getChildMap(const SkinData* skinData, std::map<int, std::vector<int> >& map, const rapidjson::Value& val)
{
    if (!skinData)
        return;

    if (val.HasMember("children"))
    {
        int parent_name_index = skinData->getBoneNameIndex(val["id"].GetString());
        const rapidjson::Value& children = val["children"];
        for (rapidjson::SizeType i = 0; i < children.Size(); i++)
        {
            const rapidjson::Value& child = children[i];
            std::string child_name = child["id"].GetString();

            int child_name_index = skinData->getBoneNameIndex(child_name);
            if (child_name_index < 0)
                continue;

            map[parent_name_index].push_back(child_name_index);

            getChildMap(skinData, map, child);
        }
    }
}


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
    //unsigned char* buffer_data = FileUtils::getInstance()->getFileData(path, "rb", &size);
    std::string strFileString = FileUtils::getInstance()->getStringFromFile(path);
    ssize_t size = strFileString.length();

    CC_SAFE_DELETE_ARRAY(_documentBuffer);
    _documentBuffer = new char[size + 1];
    memcpy(_documentBuffer, strFileString.c_str(), size);
    _documentBuffer[size] = '\0';
    if (document.ParseInsitu<0>(_documentBuffer).HasParseError())
        return false;

    return true;
}

/**
 * load mesh data from bundle
 * @param id The ID of the mesh, load the first Mesh in the bundle if it is empty
 */
bool Bundle3D::loadMeshData(const std::string& id, MeshData* meshdata)
{
    meshdata->resetData();
    /*meshdata->vertexSizeInFloat = 13 * 4;
    meshdata->vertex = new float[meshdata->vertexSizeInFloat];
    float vert[] = {0.f,50.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,
        0.f,0.f,50.f,1.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,
        50.f,0.f,0.f,1.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,
        -50.f,0.f,0.f,1.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f};
    memcpy(meshdata->vertex, vert, meshdata->vertexSizeInFloat * sizeof(float));

    meshdata->numIndex = 4 * 3;
    meshdata->indices = new unsigned short[meshdata->numIndex];
    unsigned short index[] = {0,1,2, 0,3,1, 0,2,3, 3,2,1};
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
    meshdata->attribs[3].vertexAttrib = GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;*/
    
    const rapidjson::Value& mash_data_val_array = document["mesh_data"];
    assert(mash_data_val_array.IsArray());

    const rapidjson::Value& mash_data_val = mash_data_val_array[(rapidjson::SizeType)0];
    assert(mash_data_val.IsObject());
   
    /*assert(mash_data_val.HasMember("version"));
    assert(mash_data_val["version"].IsString());
    printf("version = %s\n", mash_data_val["version"].GetString());*/

    assert(mash_data_val.HasMember("body"));
    const rapidjson::Value& mesh_data_body_array = mash_data_val["body"];
    
    assert(mesh_data_body_array.IsArray());
    const rapidjson::Value& mesh_data_body_val = mesh_data_body_array[(rapidjson::SizeType)0];
    
    // vertex_size
    assert(mesh_data_body_val.HasMember("vertex_size"));
    meshdata->vertexSizeInFloat = mesh_data_body_val["vertex_size"].GetInt();

    // vertices
    meshdata->vertex = new float[meshdata->vertexSizeInFloat];
    const rapidjson::Value& mesh_data_body_vertex_val = mesh_data_body_val["vertices"];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_vertex_val.Size(); i++)
        meshdata->vertex[i] = mesh_data_body_vertex_val[i].GetDouble();

    // index_number
    meshdata->numIndex = mesh_data_body_val["index_number"].GetUint();

    // indices
    meshdata->indices = new unsigned short[meshdata->numIndex];
    const rapidjson::Value& mesh_data_body_indices_val = mesh_data_body_val["indices"];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_indices_val.Size(); i++)
        meshdata->indices[i] = (unsigned short)mesh_data_body_indices_val[i].GetUint();

    // mesh_vertex_attribute
    const rapidjson::Value& mesh_vertex_attribute = mesh_data_body_val["mesh_vertex_attribute"];
    meshdata->attribCount = mesh_vertex_attribute.Size();
    meshdata->attribs = new MeshVertexAttrib[meshdata->attribCount];
    for (rapidjson::SizeType i = 0; i < mesh_vertex_attribute.Size(); i++)
    {
        const rapidjson::Value& mesh_vertex_attribute_val = mesh_vertex_attribute[i];

        meshdata->attribs[i].size = mesh_vertex_attribute_val["size"].GetUint();
        meshdata->attribs[i].attribSizeBytes = meshdata->attribs[i].size * parseGLTypeSize(mesh_vertex_attribute_val["type"].GetString());
        meshdata->attribs[i].type = parseGLType(mesh_vertex_attribute_val["type"].GetString());
        //assignGLTypeByString(meshdata->attribs[i].type, mesh_vertex_attribute_val["type"].GetString());
        meshdata->attribs[i].vertexAttrib = parseGLProgramAttribute(mesh_vertex_attribute_val["vertex_attribute"].GetString());
    }

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
    /*skindata->boneNames.push_back("root");
    skindata->inverseBindPoseMatrices.push_back(Mat4::IDENTITY);
    skindata->rootBoneIndex = 0;*/

    //assert(document.HasMember("skin_data"));
    if (!document.HasMember("skin_data")) return false;

    const rapidjson::Value& skin_data_array = document["skin_data"];
    assert(skin_data_array.IsArray());
    
    const rapidjson::Value& skin_data_array_val_0 = skin_data_array[(rapidjson::SizeType)0];
    //skindata->boneNames.push_back("root");
    //skindata->inverseBindPoseMatrices.push_back(Mat4::IDENTITY);
    skindata->rootBoneIndex = 1;

    const rapidjson::Value& skin_data_bind_shape = skin_data_array_val_0["bind_shape"];
    assert(skin_data_bind_shape.Size() == 16);
    for (rapidjson::SizeType i = 0; i < skin_data_bind_shape.Size(); i++)
    {
        skindata->bindShape.m[i] = skin_data_bind_shape[i].GetDouble();
    }

    const rapidjson::Value& skin_data_bones = skin_data_array_val_0["bones"];
    for (rapidjson::SizeType i = 0; i < skin_data_bones.Size(); i++)
    {
        const rapidjson::Value& skin_data_bone = skin_data_bones[i];
        std::string name = skin_data_bone["node"].GetString();
        skindata->boneNames.push_back(name);
        const rapidjson::Value& bind_pos = skin_data_bone["bind_pos"];
        Mat4 mat_bind_pos;
        for (rapidjson::SizeType j = 0; j < bind_pos.Size(); j++)
        {
            mat_bind_pos.m[j] = bind_pos[j].GetDouble();
        }
        skindata->inverseBindPoseMatrices.push_back(mat_bind_pos);
    }

    const rapidjson::Value& skin_data_array_val_1 = skin_data_array[1];
    const rapidjson::Value& bone_val_0 = skin_data_array_val_1["children"][(rapidjson::SizeType)0];
    getChildMap(skindata, skindata->boneChild, /*skin_data_array_val_1*/bone_val_0);

    return true;
}

//
/**
 * load material data from bundle
 * @param id The ID of the material, load the first Material in the bundle if it is empty
 */
bool Bundle3D::loadMaterialData(const std::string& id, MaterialData* materialdata)
{
    //assert(document.HasMember("material_data"));
    if (!document.HasMember("material_data")) return false;

    const rapidjson::Value& material_data_array_val = document["material_data"];
    assert(material_data_array_val.IsArray());

    const rapidjson::Value& material_data_array_val_0 = material_data_array_val[(rapidjson::SizeType)0];
    materialdata->texturePath = material_data_array_val_0["filename"].GetString();
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
    //assert(document.HasMember("animation_data"));
    if (!document.HasMember("animation_data")) return false;

    animationdata->_totalTime = 3;

    //auto animation = animationdata->animation;
    //animation->_duration = 3.0f;
   /* for (auto it : animation->_boneCurves) {
        CC_SAFE_DELETE(it.second);
    }
    animation->_boneCurves.clear();*/
    /*auto curve = new Animation3D::Curve();
    float keytime[] = {0.f, 1.f};
    float pos[] = {0.f, 0.f, 0.f, 20.f, 0.f, 0.f};
    
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
    
    animation->_boneCurves["root"] = curve;*/

    const rapidjson::Value& animation_data_array_val =  document["animation_data"];
    const rapidjson::Value& animation_data_array_val_0 = animation_data_array_val[(rapidjson::SizeType)0];

    const rapidjson::Value&  bones =  animation_data_array_val_0["bones"];
    for (rapidjson::SizeType i = 0; i <  bones.Size(); i++)
    {
        const rapidjson::Value&  bone =  bones[i];
        std::string bone_name =  bone["id"].GetString();

        if ( bone.HasMember("keyframes"))
        {
            const rapidjson::Value& bone_keyframes =  bone["keyframes"];
            for (rapidjson::SizeType j = 0; j < bone_keyframes.Size(); j++)
            {
                //auto curve = new Animation3D::Curve();
                const rapidjson::Value&  bone_keyframe =  bone_keyframes[j];
                if ( bone_keyframe.HasMember("position"))
                {
                    const rapidjson::Value&  bone_keyframe_position =  bone_keyframe["position"];

                    for (rapidjson::SizeType k = 0; k <  bone_keyframe_position.Size(); k++)
                    {
                        const rapidjson::Value&  bone_keyframe_position_obj =  bone_keyframe_position[k];
                        float keytime =  bone_keyframe_position_obj["keytime"].GetDouble();

                        const rapidjson::Value&  bone_keyframe_position_values =  bone_keyframe_position_obj["value"];
                        Vec3 val = Vec3(bone_keyframe_position_values[(rapidjson::SizeType)0].GetDouble(),bone_keyframe_position_values[1].GetDouble(),bone_keyframe_position_values[2].GetDouble());
                        animationdata->_translationKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                    }
                }

                if ( bone_keyframe.HasMember("rotation"))
                {
                    const rapidjson::Value&  bone_keyframe_position =  bone_keyframe["rotation"];

                    for (rapidjson::SizeType k = 0; k <  bone_keyframe_position.Size(); k++)
                    {
                        const rapidjson::Value&  bone_keyframe_position_obj =  bone_keyframe_position[k];
                        float keytime =  bone_keyframe_position_obj["keytime"].GetDouble();

                        const rapidjson::Value&  bone_keyframe_position_values =  bone_keyframe_position_obj["value"];
                        Quaternion val = Quaternion(bone_keyframe_position_values[(rapidjson::SizeType)0].GetDouble(),bone_keyframe_position_values[1].GetDouble(),bone_keyframe_position_values[2].GetDouble(),bone_keyframe_position_values[3].GetDouble());
                        animationdata->_rotationKeys[bone_name].push_back(Animation3DData::QuatKey(keytime,val));
                    }
                }

                if ( bone_keyframe.HasMember("scale"))
                {
                    const rapidjson::Value&  bone_keyframe_position =  bone_keyframe["scale"];
                    
                    for (rapidjson::SizeType k = 0; k <  bone_keyframe_position.Size(); k++)
                    {
                        const rapidjson::Value&  bone_keyframe_position_obj =  bone_keyframe_position[k];
                        float keytime =  bone_keyframe_position_obj["keytime"].GetDouble();

                        const rapidjson::Value&  bone_keyframe_position_values =  bone_keyframe_position_obj["value"];
                        Vec3 val = Vec3(bone_keyframe_position_values[(rapidjson::SizeType)0].GetDouble(),bone_keyframe_position_values[1].GetDouble(),bone_keyframe_position_values[2].GetDouble());
                        animationdata->_scaleKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                    }
                }

                //animation->_boneCurves[bone_name] = curve;
            }
        }
    }
    return true;
}

//void Bundle3D::assignGLTypeByString(GLenum& type, std::string str)
//{
//    if (str == "GL_FLOAT")
//    {
//        type = GL_FLOAT;
//    }
//    else if (str == "GL_UNSIGNED_INT")
//    {
//        type = GL_UNSIGNED_INT;
//    }
//    else
//    {
//        assert(0);
//    }
//}

GLenum Bundle3D::parseGLType(const std::string& str)
{
    if (str == "GL_FLOAT")
    {
        return GL_FLOAT;
    }
    else if (str == "GL_UNSIGNED_INT")
    {
        return GL_UNSIGNED_INT;
    }
    else
    {
        assert(0);
        return 0;
    }
}

unsigned int Bundle3D::parseGLTypeSize(const std::string& str)
{
    if (str == "GL_FLOAT")
    {
        return sizeof(float);
    }
    else if (str == "GL_UNSIGNED_INT")
    {
        return sizeof(unsigned int);
    }
    else
    {
        assert(0);
        return -1;
    }
}

unsigned int Bundle3D::parseGLProgramAttribute(const std::string& str)
{
    if (str == "VERTEX_ATTRIB_POSITION")
    {
        return GLProgram::VERTEX_ATTRIB_POSITION;
    }
    else if (str == "VERTEX_ATTRIB_COLOR")
    {
        return GLProgram::VERTEX_ATTRIB_COLOR;
    }
    else if (str == "VERTEX_ATTRIB_TEX_COORD")
    {
        return GLProgram::VERTEX_ATTRIB_TEX_COORD;
    }
    else if (str == "VERTEX_ATTRIB_NORMAL")
    {
        return GLProgram::VERTEX_ATTRIB_NORMAL;
    }
    else if (str == "VERTEX_ATTRIB_BLEND_WEIGHT")
    {
        return GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT;
    }
    else if (str == "VERTEX_ATTRIB_BLEND_INDEX")
    {
        return GLProgram::VERTEX_ATTRIB_BLEND_INDEX;
    }
    else
    {
        assert(0);
        return -1;
    }
}

Bundle3D::Bundle3D()
:_isBinary(false),_documentBuffer(NULL)
{

}
Bundle3D::~Bundle3D()
{
    CC_SAFE_DELETE_ARRAY(_documentBuffer);
}



NS_CC_END

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

#include "3d/CCBundle3D.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCGLProgram.h"


NS_CC_BEGIN

void getChildMap(std::map<int, std::vector<int> >& map, SkinData* skinData, const rapidjson::Value& val)
{
    if (!skinData)
        return;

    if (!val.HasMember("children"))
        return;

    std::string parent_name = val["id"].GetString();
    int parent_name_index = skinData->getBoneNameIndex(parent_name);

    const rapidjson::Value& children = val["children"];
    for (rapidjson::SizeType i = 0; i < children.Size(); i++)
    {
        const rapidjson::Value& child = children[i];
        std::string child_name = child["id"].GetString();

        int child_name_index = skinData->getBoneNameIndex(child_name);
        if (child_name_index >= 0)
        {
            map[parent_name_index].push_back(child_name_index);

            getChildMap(map, skinData, child);
        }
    }
}

void getChildMapT(std::map<std::string, std::vector<std::string> >& map, const SkinData* skinData, const rapidjson::Value& val)
{
    if (!skinData)
        return;

    if (!val.HasMember("children"))
        return;

    std::string parent_name = val["id"].GetString();
    const rapidjson::Value& children = val["children"];
    for (rapidjson::SizeType i = 0; i < children.Size(); i++)
    {
        const rapidjson::Value& child = children[i];
        std::string child_name = child["id"].GetString();

        map[parent_name].push_back(child_name);

       getChildMapT(map, skinData, child);
    }
}

Bundle3D* Bundle3D::_instance = nullptr;

Bundle3D* Bundle3D::getInstance()
{
    if (_instance == nullptr)
        _instance = new Bundle3D();
    return _instance;
}

void Bundle3D::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
}

bool Bundle3D::load(const std::string& path)
{
    if (_path == path)
        return true;

    getModelPath(path);
    std::string strFileString = FileUtils::getInstance()->getStringFromFile(path);
    ssize_t size = strFileString.length();
    CC_SAFE_DELETE_ARRAY(_documentBuffer);
    _documentBuffer = new char[size + 1];
    memcpy(_documentBuffer, strFileString.c_str(), size);
    _documentBuffer[size] = '\0';
    if (_document.ParseInsitu<0>(_documentBuffer).HasParseError())
    {
         assert(0);
         CC_SAFE_DELETE_ARRAY(_documentBuffer);
         _path = "";
         return false;
    }
    _path = path;
    return true;
}

bool Bundle3D::loadMeshData(const std::string& id, MeshData* meshdata)
{
    meshdata->resetData();
    
    assert(_document.HasMember("mesh"));
    const rapidjson::Value& mash_data_array = _document["mesh"];
    
    assert(mash_data_array.IsArray());
    const rapidjson::Value& mash_data_val = mash_data_array[(rapidjson::SizeType)0];

    assert(mash_data_val.HasMember("body"));
    const rapidjson::Value& mesh_data_body_array = mash_data_val["body"];
    
    assert(mesh_data_body_array.IsArray());
    const rapidjson::Value& mesh_data_body_array_0 = mesh_data_body_array[(rapidjson::SizeType)0];
    
    // vertex_size
    assert(mesh_data_body_array_0.HasMember("vertexsize"));
    meshdata->vertexSizeInFloat = mesh_data_body_array_0["vertexsize"].GetInt();

    // vertices
    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    const rapidjson::Value& mesh_data_body_vertices = mesh_data_body_array_0["vertices"];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_vertices.Size(); i++)
        meshdata->vertex[i] = mesh_data_body_vertices[i].GetDouble();

    // index_number
    meshdata->numIndex = mesh_data_body_array_0["indexnum"].GetUint();

    // indices
    meshdata->indices.resize(meshdata->numIndex);
    const rapidjson::Value& mesh_data_body_indices_val = mesh_data_body_array_0["indices"];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_indices_val.Size(); i++)
        meshdata->indices[i] = (unsigned short)mesh_data_body_indices_val[i].GetUint();

    // mesh_vertex_attribute
    const rapidjson::Value& mesh_vertex_attribute = mash_data_val["attributes"];
    meshdata->attribCount = mesh_vertex_attribute.Size();
    meshdata->attribs.resize(meshdata->attribCount);
    for (rapidjson::SizeType i = 0; i < mesh_vertex_attribute.Size(); i++)
    {
        const rapidjson::Value& mesh_vertex_attribute_val = mesh_vertex_attribute[i];

        meshdata->attribs[i].size = mesh_vertex_attribute_val["size"].GetUint();
        meshdata->attribs[i].attribSizeBytes = meshdata->attribs[i].size * parseGLTypeSize(mesh_vertex_attribute_val["type"].GetString());
        meshdata->attribs[i].type = parseGLType(mesh_vertex_attribute_val["type"].GetString());
        meshdata->attribs[i].vertexAttrib = parseGLProgramAttribute(mesh_vertex_attribute_val["attribute"].GetString());
    }

    return true;
}

bool Bundle3D::loadSkinData(const std::string& id, SkinData* skindata)
{
    if (!_document.HasMember("skin")) return false;

    skindata->resetData();

    const rapidjson::Value& skin_data_array = _document["skin"];

    assert(skin_data_array.IsArray());
    const rapidjson::Value& skin_data_array_val_0 = skin_data_array[(rapidjson::SizeType)0];

    if (!skin_data_array_val_0.HasMember("bones"))
        return false;

    const rapidjson::Value& skin_data_bones = skin_data_array_val_0["bones"];
    for (rapidjson::SizeType i = 0; i < skin_data_bones.Size(); i++)
    {
        const rapidjson::Value& skin_data_bone = skin_data_bones[i];
        std::string name = skin_data_bone["node"].GetString();
        skindata->boneNames.push_back(name);
        
        Mat4 mat_bind_pos;
        const rapidjson::Value& bind_pos = skin_data_bone["bindshape"];
        for (rapidjson::SizeType j = 0; j < bind_pos.Size(); j++)
        {
            mat_bind_pos.m[j] = bind_pos[j].GetDouble();
        }
        skindata->inverseBindPoseMatrices.push_back(mat_bind_pos);
    }

    const rapidjson::Value& skin_data_1 = skin_data_array[1];
    const rapidjson::Value& bone_array_0 = skin_data_1["children"][(rapidjson::SizeType)0];
    skindata->rootBoneIndex = skindata->getBoneNameIndex(bone_array_0["id"].GetString());
    getChildMap(skindata->boneChild, skindata, bone_array_0);
    return true;
}

bool Bundle3D::loadMaterialData(const std::string& id, MaterialData* materialdata)
{
    if (!_document.HasMember("material")) 
        return false;

    const rapidjson::Value& material_data_array = _document["material"];

    const rapidjson::Value& material_data_array_0 = material_data_array[(rapidjson::SizeType)0];

    const rapidjson::Value& material_data_base_array = material_data_array_0["base"];

    const rapidjson::Value& material_data_base_array_0 = material_data_base_array[(rapidjson::SizeType)0];

    materialdata->texturePath = _modelRelativePath + material_data_base_array_0["filename"].GetString();

    return true;
}

bool Bundle3D::loadAnimationData(const std::string& id, Animation3DData* animationdata)
{
    if (!_document.HasMember("animation")) return false;

    animationdata->_rotationKeys.clear();
    animationdata->_scaleKeys.clear();
    animationdata->_translationKeys.clear();

    const rapidjson::Value& animation_data_array =  _document["animation"];
    if (animation_data_array.Size()==0) return false;

    const rapidjson::Value& animation_data_array_val_0 = animation_data_array[(rapidjson::SizeType)0];

    animationdata->_totalTime = animation_data_array_val_0["length"].GetDouble();

    const rapidjson::Value&  bones =  animation_data_array_val_0["bones"];
    for (rapidjson::SizeType i = 0; i <  bones.Size(); i++)
    {
        const rapidjson::Value&  bone =  bones[i];
        std::string bone_name =  bone["boneId"].GetString();

        if ( bone.HasMember("keyframes"))
        {
            const rapidjson::Value& bone_keyframes =  bone["keyframes"];
            rapidjson::SizeType keyframe_size = bone_keyframes.Size();
            for (rapidjson::SizeType j = 0; j < bone_keyframes.Size(); j++)
            {
                const rapidjson::Value&  bone_keyframe =  bone_keyframes[j];

                if ( bone_keyframe.HasMember("translation"))
                {
                    const rapidjson::Value&  bone_keyframe_translation =  bone_keyframe["translation"];
                    float keytime =  bone_keyframe["keytime"].GetDouble();
                    Vec3 val = Vec3(bone_keyframe_translation[(rapidjson::SizeType)0].GetDouble(), bone_keyframe_translation[1].GetDouble(), bone_keyframe_translation[2].GetDouble());
                    animationdata->_translationKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                }

                if ( bone_keyframe.HasMember("rotation"))
                {
                    const rapidjson::Value&  bone_keyframe_rotation =  bone_keyframe["rotation"];
                    float keytime =  bone_keyframe["keytime"].GetDouble();
                    Quaternion val = Quaternion(bone_keyframe_rotation[(rapidjson::SizeType)0].GetDouble(),bone_keyframe_rotation[1].GetDouble(),bone_keyframe_rotation[2].GetDouble(),bone_keyframe_rotation[3].GetDouble());
                    animationdata->_rotationKeys[bone_name].push_back(Animation3DData::QuatKey(keytime,val));
                }

                if ( bone_keyframe.HasMember("scale"))
                {
                    const rapidjson::Value&  bone_keyframe_scale =  bone_keyframe["scale"];
                    float keytime =  bone_keyframe["keytime"].GetDouble();
                    Vec3 val = Vec3(bone_keyframe_scale[(rapidjson::SizeType)0].GetDouble(), bone_keyframe_scale[1].GetDouble(), bone_keyframe_scale[2].GetDouble());
                    animationdata->_scaleKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                }
            }
        }
    }
    
    return true;
}

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

void Bundle3D::getModelPath(const std::string& path)
{
    int index = path.find_last_of('/');
    std::string fullModelPath;
    fullModelPath = path.substr(0, index + 1);

    auto list = FileUtils::getInstance()->getSearchPaths();
    for( const auto &item : list )
    {
        if ( fullModelPath.find(item) != std::string::npos )
        {
            _modelRelativePath = fullModelPath.substr(item.length(), fullModelPath.length() + 1);
            break;
        }
    } 
}

Bundle3D::Bundle3D()
:_isBinary(false)
,_modelRelativePath("")
,_documentBuffer(nullptr)
,_path("")
{

}
Bundle3D::~Bundle3D()
{
    CC_SAFE_DELETE_ARRAY(_documentBuffer);
}



NS_CC_END

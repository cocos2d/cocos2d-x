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
#include "CCBundleReader.h"
#include "base/CCData.h"
#include "json/document.h"


#define BUNDLE_TYPE_SCENE               1
#define BUNDLE_TYPE_NODE                2
#define BUNDLE_TYPE_ANIMATIONS          3
#define BUNDLE_TYPE_ANIMATION           4
#define BUNDLE_TYPE_ANIMATION_CHANNEL   5
#define BUNDLE_TYPE_MODEL               10
#define BUNDLE_TYPE_MATERIAL            16
#define BUNDLE_TYPE_EFFECT              18
#define BUNDLE_TYPE_CAMERA              32
#define BUNDLE_TYPE_LIGHT               33
#define BUNDLE_TYPE_MESH                34
#define BUNDLE_TYPE_MESHPART            35
#define BUNDLE_TYPE_MESHSKIN            36

static const char* ID = "id";

static const char* MESHDATA_MESH = "mesh";
static const char* MESHDATA_DEFAULTPART = "body";
static const char* MESHDATA_VERTEXSIZE = "vertexsize";
static const char* MESHDATA_VERTICES = "vertices";
static const char* MESHDATA_INDEXNUM = "indexnum";
static const char* MESHDATA_INDICES = "indices";
static const char* MESHDATA_ATTRIBUTES = "attributes";
static const char* MESHDATA_SIZE = "size";
static const char* MESHDATA_TYPE = "type";
static const char* MESHDATA_ATTRIBUTE = "attribute";

static const char* SKINDATA_SKIN = "skin";
static const char* SKINDATA_BONES = "bones";
static const char* SKINDATA_NODE = "node";
static const char* SKINDATA_BINDSHAPE = "bindshape";
static const char* SKINDATA_CHILDREN = "children";
static const char* SKINDATA_TRANSFORM = "tansform";

static const char* MATERIALDATA_MATERIAL = "material";
static const char* MATERIALDATA_BASE = "base";
static const char* MATERIALDATA_FILENAME = "filename";

static const char* ANIMATIONDATA_ANIMATION = "animation";
static const char* ANIMATIONDATA_LENGTH =   "length";
static const char* ANIMATIONDATA_BONES  = "bones";
static const char* ANIMATIONDATA_BONEID  = "boneId";
static const char* ANIMATIONDATA_KEYFRAMES  = "keyframes";
static const char* ANIMATIONDATA_TRANSLATION =  "translation";
static const char* ANIMATIONDATA_ROTATION =  "rotation";
static const char* ANIMATIONDATA_SCALE =  "scale";
static const char* ANIMATIONDATA_KEYTIME =  "keytime";

NS_CC_BEGIN

void getChildMap(std::map<int, std::vector<int> >& map, SkinData* skinData, const rapidjson::Value& val)
{
    if (!skinData)
        return;
    
    // get transform matrix
    Mat4 transform;
    const rapidjson::Value& parent_tranform = val[SKINDATA_TRANSFORM];
    for (rapidjson::SizeType j = 0; j < parent_tranform.Size(); j++)
    {
        transform.m[j] = parent_tranform[j].GetDouble();
    }
    
    // set origin matrices
    std::string parent_name = val[ID].GetString();
    int parent_name_index = skinData->getSkinBoneNameIndex(parent_name);
    if (parent_name_index < 0)
    {
        skinData->addNodeBoneNames(parent_name);
        skinData->nodeBoneOriginMatrices.push_back(transform);
        parent_name_index = skinData->getBoneNameIndex(parent_name);
    }
    else if (parent_name_index < skinData->skinBoneNames.size())
    {
        skinData->skinBoneOriginMatrices[parent_name_index] = (transform);
    }
    
    // set root bone index
    if(skinData->rootBoneIndex < 0)
        skinData->rootBoneIndex = parent_name_index;
    
    if (!val.HasMember(SKINDATA_CHILDREN))
        return;
    
    const rapidjson::Value& children = val[SKINDATA_CHILDREN];
    for (rapidjson::SizeType i = 0; i < children.Size(); i++)
    {
        // get child bone name
        const rapidjson::Value& child = children[i];
        
        std::string child_name = child[ID].GetString();
        int child_name_index = skinData->getSkinBoneNameIndex(child_name);
        if (child_name_index < 0)
        {
            skinData->addNodeBoneNames(child_name);
            child_name_index = skinData->getBoneNameIndex(child_name);
            
        }
        
        map[parent_name_index].push_back(child_name_index);
        
        getChildMap(map, skinData, child);
        
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

void Bundle3D::clear()
{
    if (_isBinary)
    {
        CC_SAFE_DELETE(_binaryBuffer);
        CC_SAFE_DELETE_ARRAY(_references);
    }
    else
    {
        CC_SAFE_DELETE_ARRAY(_jsonBuffer);
    }
}

bool Bundle3D::load(const std::string& path)
{
    if (_path == path)
        return true;

    getModelRelativePath(path);

    bool ret = false;
    std::string ext = path.substr(path.length() - 4, 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
    if (ext == ".c3t")
    {
        _isBinary = false;
        ret = loadJson(path);
    }
    else if (ext == ".c3b")
    {
        _isBinary = true;
        ret = loadBinary(path);
    }
    else 
    {
        CCLOGINFO("%s is invalid file formate", path);
    }

    ret?(_path = path):(_path = "");
        
    return ret;
}
    
bool Bundle3D::loadMeshData(const std::string& id, MeshData* meshdata)
{
    if (_isBinary)
    {
        return loadMeshDataBinary(meshdata);
    }
    else
    {
        return loadMeshDataJson(meshdata);
    }
}
    
bool Bundle3D::loadSkinData(const std::string& id, SkinData* skindata)
{
    if (_isBinary)
    {
        return loadSkinDataBinary(skindata);
    }
    else
    {
        return loadSkinDataJson(skindata);
    }
}
    
bool Bundle3D::loadMaterialData(const std::string& id, MaterialData* materialdata)
{
    if (_isBinary)
    {
        return loadMaterialDataBinary(materialdata);
    }
    else
    {
        return loadMaterialDataJson(materialdata);
    }
}
    
bool Bundle3D::loadAnimationData(const std::string& id, Animation3DData* animationdata)
{
    if (_isBinary)
    {
        return loadAnimationDataBinary(animationdata);
    }
    else
    {
        return loadAnimationDataJson(animationdata);
    }
}

bool Bundle3D::loadJson(const std::string& path)
{
    clear();
    
    Data data = FileUtils::getInstance()->getDataFromFile(path);
    ssize_t size = data.getSize();
    
    // json need null-terminated string.
    _jsonBuffer = new char[size + 1];
    memcpy(_jsonBuffer, data.getBytes(), size);
    _jsonBuffer[size] = '\0';
    if (_jsonReader.ParseInsitu<0>(_jsonBuffer).HasParseError())
    {
         assert(0);
         clear();
         return false;
    }
    return true;
}

bool Bundle3D::loadMeshDataJson(MeshData* meshdata)
{
    meshdata->resetData();
    
    assert(_jsonReader.HasMember(MESHDATA_MESH));
    const rapidjson::Value& mash_data_array = _jsonReader[MESHDATA_MESH];
    
    assert(mash_data_array.IsArray());
    const rapidjson::Value& mash_data_val = mash_data_array[(rapidjson::SizeType)0];

    assert(mash_data_val.HasMember(MESHDATA_DEFAULTPART));
    const rapidjson::Value& mesh_data_body_array = mash_data_val[MESHDATA_DEFAULTPART];
    
    assert(mesh_data_body_array.IsArray());
    const rapidjson::Value& mesh_data_body_array_0 = mesh_data_body_array[(rapidjson::SizeType)0];
    
    // vertex_size
    assert(mesh_data_body_array_0.HasMember(MESHDATA_VERTEXSIZE));
    meshdata->vertexSizeInFloat = mesh_data_body_array_0[MESHDATA_VERTEXSIZE].GetInt();

    // vertices
    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    const rapidjson::Value& mesh_data_body_vertices = mesh_data_body_array_0[MESHDATA_VERTICES];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_vertices.Size(); i++)
        meshdata->vertex[i] = mesh_data_body_vertices[i].GetDouble();

    // index_number
    meshdata->numIndex = mesh_data_body_array_0[MESHDATA_INDEXNUM].GetUint();

    // indices
    meshdata->indices.resize(meshdata->numIndex);
    const rapidjson::Value& mesh_data_body_indices_val = mesh_data_body_array_0[MESHDATA_INDICES];
    for (rapidjson::SizeType i = 0; i < mesh_data_body_indices_val.Size(); i++)
        meshdata->indices[i] = (unsigned short)mesh_data_body_indices_val[i].GetUint();

    // mesh_vertex_attribute
    const rapidjson::Value& mesh_vertex_attribute = mash_data_val[MESHDATA_ATTRIBUTES];
    meshdata->attribCount = mesh_vertex_attribute.Size();
    meshdata->attribs.resize(meshdata->attribCount);
    for (rapidjson::SizeType i = 0; i < mesh_vertex_attribute.Size(); i++)
    {
        const rapidjson::Value& mesh_vertex_attribute_val = mesh_vertex_attribute[i];

        meshdata->attribs[i].size = mesh_vertex_attribute_val[MESHDATA_SIZE].GetUint();
        meshdata->attribs[i].attribSizeBytes = meshdata->attribs[i].size * 4;
        meshdata->attribs[i].type = parseGLType(mesh_vertex_attribute_val[MESHDATA_TYPE].GetString());
        meshdata->attribs[i].vertexAttrib = parseGLProgramAttribute(mesh_vertex_attribute_val[MESHDATA_ATTRIBUTE].GetString());
    }
    
    return true;
}

bool Bundle3D::loadSkinDataJson(SkinData* skindata)
{
    if (!_jsonReader.HasMember(SKINDATA_SKIN )) return false;
    
    skindata->resetData();
    
    const rapidjson::Value& skin_data_array = _jsonReader[SKINDATA_SKIN ];
    
    assert(skin_data_array.IsArray());
    const rapidjson::Value& skin_data_array_val_0 = skin_data_array[(rapidjson::SizeType)0];
    
    if (!skin_data_array_val_0.HasMember(SKINDATA_BONES))
        return false;
    
    const rapidjson::Value& skin_data_bones = skin_data_array_val_0[SKINDATA_BONES];
    for (rapidjson::SizeType i = 0; i < skin_data_bones.Size(); i++)
    {
        const rapidjson::Value& skin_data_bone = skin_data_bones[i];
        std::string name = skin_data_bone[SKINDATA_NODE].GetString();
        skindata->addSkinBoneNames(name);
        
        Mat4 mat_bind_pos;
        const rapidjson::Value& bind_pos = skin_data_bone[SKINDATA_BINDSHAPE];
        for (rapidjson::SizeType j = 0; j < bind_pos.Size(); j++)
        {
            mat_bind_pos.m[j] = bind_pos[j].GetDouble();
        }
        skindata->inverseBindPoseMatrices.push_back(mat_bind_pos);
    }
    
    // set root bone infomation
    const rapidjson::Value& skin_data_1 = skin_data_array[1];
    
    // parent and child relationship map
    skindata->skinBoneOriginMatrices.resize(skindata->skinBoneNames.size());
    //skindata->nodeBoneOriginMatrices.resize(skindata->nodeBoneNames.size());
    getChildMap(skindata->boneChild, skindata, skin_data_1);
    return true;
}

bool Bundle3D::loadMaterialDataJson(MaterialData* materialdata)
{
    if (!_jsonReader.HasMember(MATERIALDATA_MATERIAL))
        return false;

    const rapidjson::Value& material_data_array = _jsonReader[MATERIALDATA_MATERIAL];

    const rapidjson::Value& material_data_array_0 = material_data_array[(rapidjson::SizeType)0];

    const rapidjson::Value& material_data_base_array = material_data_array_0[MATERIALDATA_BASE];

    const rapidjson::Value& material_data_base_array_0 = material_data_base_array[(rapidjson::SizeType)0];

    materialdata->texturePath = _modelRelativePath + material_data_base_array_0[MATERIALDATA_FILENAME].GetString();

    return true;
}

bool Bundle3D::loadAnimationDataJson(Animation3DData* animationdata)
{
    if (!_jsonReader.HasMember(ANIMATIONDATA_ANIMATION)) return false;

    animationdata->_rotationKeys.clear();
    animationdata->_scaleKeys.clear();
    animationdata->_translationKeys.clear();

    const rapidjson::Value& animation_data_array =  _jsonReader[ANIMATIONDATA_ANIMATION];
    if (animation_data_array.Size()==0) return false;

    const rapidjson::Value& animation_data_array_val_0 = animation_data_array[(rapidjson::SizeType)0];

    animationdata->_totalTime = animation_data_array_val_0[ANIMATIONDATA_LENGTH].GetDouble();

    const rapidjson::Value&  bones =  animation_data_array_val_0[ANIMATIONDATA_BONES];
    for (rapidjson::SizeType i = 0; i <  bones.Size(); i++)
    {
        const rapidjson::Value&  bone =  bones[i];
        std::string bone_name =  bone[ANIMATIONDATA_BONEID].GetString();

        if ( bone.HasMember(ANIMATIONDATA_KEYFRAMES))
        {
            const rapidjson::Value& bone_keyframes =  bone[ANIMATIONDATA_KEYFRAMES];
            rapidjson::SizeType keyframe_size = bone_keyframes.Size();
            for (rapidjson::SizeType j = 0; j < keyframe_size; j++)
            {
                const rapidjson::Value&  bone_keyframe =  bone_keyframes[j];

                if ( bone_keyframe.HasMember(ANIMATIONDATA_TRANSLATION))
                {
                    const rapidjson::Value&  bone_keyframe_translation =  bone_keyframe[ANIMATIONDATA_TRANSLATION];
                    float keytime =  bone_keyframe[ANIMATIONDATA_KEYTIME].GetDouble();
                    Vec3 val = Vec3(bone_keyframe_translation[(rapidjson::SizeType)0].GetDouble(), bone_keyframe_translation[1].GetDouble(), bone_keyframe_translation[2].GetDouble());
                    animationdata->_translationKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                }

                if ( bone_keyframe.HasMember(ANIMATIONDATA_ROTATION))
                {
                    const rapidjson::Value&  bone_keyframe_rotation =  bone_keyframe[ANIMATIONDATA_ROTATION];
                    float keytime =  bone_keyframe[ANIMATIONDATA_KEYTIME].GetDouble();
                    Quaternion val = Quaternion(bone_keyframe_rotation[(rapidjson::SizeType)0].GetDouble(),bone_keyframe_rotation[1].GetDouble(),bone_keyframe_rotation[2].GetDouble(),bone_keyframe_rotation[3].GetDouble());
                    animationdata->_rotationKeys[bone_name].push_back(Animation3DData::QuatKey(keytime,val));
                }

                if ( bone_keyframe.HasMember(ANIMATIONDATA_SCALE))
                {
                    const rapidjson::Value&  bone_keyframe_scale =  bone_keyframe[ANIMATIONDATA_SCALE];
                    float keytime =  bone_keyframe[ANIMATIONDATA_KEYTIME].GetDouble();
                    Vec3 val = Vec3(bone_keyframe_scale[(rapidjson::SizeType)0].GetDouble(), bone_keyframe_scale[1].GetDouble(), bone_keyframe_scale[2].GetDouble());
                    animationdata->_scaleKeys[bone_name].push_back(Animation3DData::Vec3Key(keytime,val));
                }
            }
        }
    }
    
    return true;
}

bool Bundle3D::loadBinary(const std::string& path)
{
    clear();
    
    // get file data
    CC_SAFE_DELETE(_binaryBuffer);
    _binaryBuffer = new Data();
    *_binaryBuffer = FileUtils::getInstance()->getDataFromFile(path);
    if (_binaryBuffer->isNull()) 
    {
        clear();
        CCLOGINFO(false, "Failed to read file: %s", path.c_str());
        return false;
    }

    // Create bundle reader
    //CC_SAFE_DELETE(_bundleReader);
    _binaryReader.init( (char*)_binaryBuffer->getBytes(),  _binaryBuffer->getSize() );

    // Read identifier info
    char identifier[] = { 'C', '3', 'B', '\0'};
    char sig[4];
    if (_binaryReader.read(sig, 1, 4) != 4 || memcmp(sig, identifier, 4) != 0)
    {
        clear();
        CCLOGINFO(false, "Invalid identifier: %s", path.c_str());
        return false;
    }

    // Read version
    unsigned char ver[2];
    if (_binaryReader.read(ver, 1, 2) == 2)
    {
        if (ver[0] != 0) {
            clear();
            CCLOGINFO(false, "Unsupported version: (%d, %d)", ver[0], ver[1]);
            return false;
        }
        
        if (ver[1] <= 0 || ver[1] > 2) {
            clear();
            CCLOGINFO(false, "Unsupported version: (%d, %d)", ver[0], ver[1]);
            return false;
        }
    }

    // Read ref table size
    if (_binaryReader.read(&_referenceCount, 4, 1) != 1)
    {
        clear();
        CCLOGINFO("Failed to read ref table size '%s'.", path.c_str());
        return false;
    }

    // Read all refs
    CC_SAFE_DELETE_ARRAY(_references);
    _references = new Reference[_referenceCount];
    for (ssize_t i = 0; i < _referenceCount; ++i)
    {
        if ((_references[i].id = _binaryReader.readString()).empty() ||
            _binaryReader.read(&_references[i].type, 4, 1) != 1 ||
            _binaryReader.read(&_references[i].offset, 4, 1) != 1)
        {
            clear();
            CCLOGINFO("Failed to read ref number %d for bundle '%s'.", i, path.c_str());
            CC_SAFE_DELETE_ARRAY(_references);
            return false;
        }
    }

    return true;
}

bool Bundle3D::loadMeshDataBinary(MeshData* meshdata)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESH))
        return false;
    
    meshdata->resetData();

    // read mesh data
    if (_binaryReader.read(&meshdata->attribCount, 4, 1) != 1 || meshdata->attribCount < 1)
    {
        CCLOGINFO("Failed to read meshdata: attribCount '%s'.", _path.c_str());
        return false;
    }

    meshdata->attribs.resize(meshdata->attribCount);
    for (ssize_t i = 0; i < meshdata->attribCount; i++)
    {
        unsigned int vUsage, vSize;
        if (_binaryReader.read(&vUsage, 4, 1) != 1 || _binaryReader.read(&vSize, 4, 1) != 1)
        {
            CCLOGINFO("Failed to read meshdata: usage or size '%s'.", _path.c_str());
            return false;
        }

        meshdata->attribs[i].size = vSize;
        meshdata->attribs[i].attribSizeBytes = meshdata->attribs[i].size * 4;
        meshdata->attribs[i].type = GL_FLOAT;
        meshdata->attribs[i].vertexAttrib = vUsage;
    }

    // Read vertex data
    if (_binaryReader.read(&meshdata->vertexSizeInFloat, 4, 1) != 1 || meshdata->vertexSizeInFloat == 0)
    {
        CCLOGINFO("Failed to read meshdata: vertexSizeInFloat '%s'.", _path.c_str());
        return false;
    }

    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    if (_binaryReader.read(&meshdata->vertex[0], 4, meshdata->vertexSizeInFloat) != meshdata->vertexSizeInFloat)
    {
        CCLOGINFO("Failed to read meshdata: vertex element '%s'.", _path.c_str());
        return false;
    }

    // Read index data
    unsigned int meshPartCount = 1;
    //_binaryReader.read(&meshPartCount, 4, 1);

    for (unsigned int i = 0; i < meshPartCount; ++i)
    {
        unsigned int nIndexCount;
        if (_binaryReader.read(&nIndexCount, 4, 1) != 1)
        {
            CCLOGINFO("Failed to read meshdata: nIndexCount '%s'.", _path.c_str());
            return false;
        }

        meshdata->numIndex = nIndexCount;
        meshdata->indices.resize(meshdata->numIndex);
        if (_binaryReader.read(&meshdata->indices[0], 2, meshdata->numIndex) != nIndexCount)
        {
            CCLOGINFO("Failed to read meshdata: indices '%s'.", _path.c_str());
            return false;
        }
    }

    return true;
}

bool Bundle3D::loadSkinDataBinary(SkinData* skindata)
{
    if (!seekToFirstType(BUNDLE_TYPE_MESHSKIN))
        return false;
    
    skindata->resetData();
    
    std::string boneName = _binaryReader.readString();
    
    // transform
    float bindShape[16];
    if (!_binaryReader.readMatrix(bindShape))
    {
        CCLOGINFO("Failed to read SkinData: bindShape matrix  '%s'.", _path.c_str());
        return false;
    }
    
    // bone count
    unsigned int boneNum;
    if (!_binaryReader.read(&boneNum))
    {
        CCLOGINFO("Failed to read SkinData: boneNum  '%s'.", _path.c_str());
        return false;
    }
    
    // bone names and bind pos
    float bindpos[16];
    for (unsigned int i = 0; i < boneNum; i++)
    {
        std::string skinBoneName = _binaryReader.readString();
        skindata->skinBoneNames.push_back(skinBoneName);
        if (!_binaryReader.readMatrix(bindpos))
        {
            CCLOGINFO("Failed to load SkinData: bindpos '%s'.", _path.c_str());
            return false;
        }
        skindata->inverseBindPoseMatrices.push_back(bindpos);
    }
    
    skindata->skinBoneOriginMatrices.resize(boneNum);
    
    boneName = _binaryReader.readString();
    
    // bind shape
    _binaryReader.readMatrix(bindShape);
    int rootIndex = skindata->getSkinBoneNameIndex(boneName);
    if(rootIndex < 0)
    {
        skindata->addNodeBoneNames(boneName);
        rootIndex = skindata->getBoneNameIndex(boneName);
        skindata->nodeBoneOriginMatrices.push_back(bindShape);
    }
    else
    {
        skindata->skinBoneOriginMatrices[rootIndex] = bindShape;
    }
    
    // set root bone index
    skindata->rootBoneIndex = rootIndex;
    
    // read parent and child relationship map
    float transform[16];
    unsigned int linkNum;
    _binaryReader.read(&linkNum);
    for (unsigned int i = 0; i < linkNum; ++i)
    {
        std::string id = _binaryReader.readString();
        int index = skindata->getSkinBoneNameIndex(id);

        
        std::string parentid = _binaryReader.readString();
        
        if (!_binaryReader.readMatrix(transform))
        {
            CCLOGINFO("Failed to load SkinData: transform '%s'.", _path.c_str());
            return false;
        }
        
        if(index < 0)
        {
            skindata->addNodeBoneNames(id);
            index = skindata->getBoneNameIndex(id);
            skindata->nodeBoneOriginMatrices.push_back(transform);
        }
        else
        {
            skindata->skinBoneOriginMatrices[index] = transform;
        }
        
        int parentIndex = skindata->getSkinBoneNameIndex(parentid);
        if(parentIndex < 0)
        {
            skindata->addNodeBoneNames(parentid);
            parentIndex = skindata->getBoneNameIndex(parentid);
        }
      
        skindata->boneChild[parentIndex].push_back(index);
        
    }

    return true;
}

bool Bundle3D::loadMaterialDataBinary(MaterialData* materialdata)
{
    if (!seekToFirstType(BUNDLE_TYPE_MATERIAL))
        return false;

    std::string texturePath = _binaryReader.readString();
    if (texturePath.empty())
    {
        CCLOGINFO("Failed to read Materialdata: texturePath is empty '%s'.", _path.c_str());
        return false;
    }

    materialdata->texturePath = _modelRelativePath + texturePath;
    return true;
}

bool Bundle3D::loadAnimationDataBinary(Animation3DData* animationdata)
{
    if (!seekToFirstType(BUNDLE_TYPE_ANIMATIONS))
        return false;

    animationdata->_rotationKeys.clear();
    animationdata->_scaleKeys.clear();
    animationdata->_translationKeys.clear();

    _binaryReader.readString();

    if (!_binaryReader.read(&animationdata->_totalTime))
    {
        CCLOGINFO("Failed to read AnimationData: totalTime '%s'.", _path.c_str());
        return false;
    }

    unsigned int animNum;
    if (!_binaryReader.read(&animNum))
    {
        CCLOGINFO("Failed to read AnimationData: animNum '%s'.", _path.c_str());
        return false;
    }

    for (unsigned int i = 0; i < animNum; ++i)
    {
        std::string boneName = _binaryReader.readString();
        unsigned int keyframeNum;
        if (!_binaryReader.read(&keyframeNum))
        {
            CCLOGINFO("Failed to read AnimationData: keyframeNum '%s'.", _path.c_str());
            return false;
        }

        for (unsigned int j = 0; j < keyframeNum; ++j)
        {
            float keytime;
            if (!_binaryReader.read(&keytime))
            {
                CCLOGINFO("Failed to read AnimationData: keytime '%s'.", _path.c_str());
                return false;
            }

            Quaternion  rotate;
            if (_binaryReader.read(&rotate, 4, 4) != 4)
            {
                CCLOGINFO("Failed to read AnimationData: rotate '%s'.", _path.c_str());
                return false;
            }
            animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime, rotate));

            Vec3 scale;
            if (_binaryReader.read(&scale, 4, 3) != 3)
            {
                CCLOGINFO("Failed to read AnimationData: scale '%s'.", _path.c_str());
                return false;
            }
            animationdata->_scaleKeys[boneName].push_back(Animation3DData::Vec3Key(keytime, scale));

            Vec3 position;
            if (_binaryReader.read(&position, 4, 3) != 3)
            {
                CCLOGINFO("Failed to read AnimationData: position '%s'.", _path.c_str());
                return false;
            }
            animationdata->_translationKeys[boneName].push_back(Animation3DData::Vec3Key(keytime, position));
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

void Bundle3D::getModelRelativePath(const std::string& path)
{
    ssize_t index = path.find_last_of('/');
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

Reference* Bundle3D::seekToFirstType(unsigned int type)
{
    // for each Reference
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        Reference* ref = &_references[i];
        if (ref->type == type)
        {
            // Found a match
            if (_binaryReader.seek(ref->offset, SEEK_SET) == false)
            {
                CCLOGINFO("Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
                return nullptr;
            }
            return ref;
        }
    }
    return nullptr;
}

Bundle3D::Bundle3D()
:_isBinary(false),
_modelRelativePath(""),
_path(""),
_jsonBuffer(nullptr),
_binaryBuffer(nullptr),
_referenceCount(0),
_references(nullptr)
{

}
Bundle3D::~Bundle3D()
{
    clear();
    
}

NS_CC_END

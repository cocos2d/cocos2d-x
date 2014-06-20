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

void Bundle3D::clearBuffer()
{
    CC_SAFE_DELETE_ARRAY(_jsonBuffer);
    CC_SAFE_DELETE(_binaryBuffer);
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
    std::string strFileString = FileUtils::getInstance()->getStringFromFile(path);
    ssize_t size = strFileString.length();
    CC_SAFE_DELETE_ARRAY(_jsonBuffer);
    _jsonBuffer = new char[size + 1];
    memcpy(_jsonBuffer, strFileString.c_str(), size);
    _jsonBuffer[size] = '\0';
    if (_document.ParseInsitu<0>(_jsonBuffer).HasParseError())
    {
         assert(0);
         CC_SAFE_DELETE_ARRAY(_jsonBuffer);
         return false;
    }
    return true;
}

bool Bundle3D::loadMeshDataJson(MeshData* meshdata)
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
        meshdata->attribs[i].attribSizeBytes = meshdata->attribs[i].size * 4;
        meshdata->attribs[i].type = parseGLType(mesh_vertex_attribute_val["type"].GetString());
        meshdata->attribs[i].vertexAttrib = parseGLProgramAttribute(mesh_vertex_attribute_val["attribute"].GetString());
    }
    
    return true;
}

bool Bundle3D::loadSkinDataJson(SkinData* skindata)
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
        skindata->skinBoneNames.push_back(name);
        
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

bool Bundle3D::loadMaterialDataJson(MaterialData* materialdata)
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

bool Bundle3D::loadAnimationDataJson(Animation3DData* animationdata)
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

bool Bundle3D::loadBinary(const std::string& path)
{
    // get file data
    CC_SAFE_DELETE(_binaryBuffer);
    _binaryBuffer = new Data();
    *_binaryBuffer = FileUtils::getInstance()->getDataFromFile(path);
    if (_binaryBuffer->isNull()) 
    {
        CCLOGINFO(false, "Failed to read file: %s", path.c_str());
        return false;
    }

    // Create bundle reader
    CC_SAFE_DELETE(_bundleReader);
    _bundleReader = BundleReader::create((char*)_binaryBuffer->getBytes(), _binaryBuffer->getSize());

    // Read identifier info
    char identifier[] = { 'C', '3', 'B', '\0'};
    char sig[4];
    if (_bundleReader->read(sig, 1, 4) != 4 || memcmp(sig, identifier, 4) != 0)
    {
        CCLOGINFO(false, "Invalid identifier: %s", path.c_str());
        return false;
    }

    // Read version
    unsigned char ver[2];
    if (_bundleReader->read(ver, 1, 2) != 2 || ver[0] != 0 || ver[1] != 1)
    {
        CCLOGINFO(false, "Unsupported version: (%d, %d)", ver[0], ver[1]);
        return false;
    }

    // Read ref table size
    if (_bundleReader->read(&_referenceCount, 4, 1) != 1)
    {
        CCLOGINFO("Failed to read ref table size '%s'.", path.c_str());
        return false;
    }

    // Read all refs
    CC_SAFE_DELETE_ARRAY(_references);
    _references = new Reference[_referenceCount];
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        if ((_references[i].id = _bundleReader->readString()).empty() ||
            _bundleReader->read(&_references[i].type, 4, 1) != 1 ||
            _bundleReader->read(&_references[i].offset, 4, 1) != 1)
        {
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
    if (_bundleReader->read(&meshdata->attribCount, 4, 1) != 1 || meshdata->attribCount < 1)
    {
        CCLOGINFO("Failed to read meshdata: attribCount '%s'.", _path.c_str());
        return false;
    }

    meshdata->attribs.resize(meshdata->attribCount);
    for (ssize_t i = 0; i < meshdata->attribCount; i++)
    {
        unsigned int vUsage, vSize;
        if (_bundleReader->read(&vUsage, 4, 1) != 1 || _bundleReader->read(&vSize, 4, 1) != 1)
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
    if (_bundleReader->read(&meshdata->vertexSizeInFloat, 4, 1) != 1 || meshdata->vertexSizeInFloat == 0)
    {
        CCLOGINFO("Failed to read meshdata: vertexSizeInFloat '%s'.", _path.c_str());
        return false;
    }

    meshdata->vertex.resize(meshdata->vertexSizeInFloat);
    if (_bundleReader->read(&meshdata->vertex[0], 4, meshdata->vertexSizeInFloat) != meshdata->vertexSizeInFloat)
    {
        CCLOGINFO("Failed to read meshdata: vertex element '%s'.", _path.c_str());
        return false;
    }

    // Read index data
    unsigned int meshPartCount = 1;
    //_bundleReader->read(&meshPartCount, 4, 1);

    for (unsigned int i = 0; i < meshPartCount; ++i)
    {
        unsigned int nIndexCount;
        if (_bundleReader->read(&nIndexCount, 4, 1) != 1)
        {
            CCLOGINFO("Failed to read meshdata: nIndexCount '%s'.", _path.c_str());
            return false;
        }

        meshdata->numIndex = nIndexCount;
        meshdata->indices.resize(meshdata->numIndex);
        if (_bundleReader->read(&meshdata->indices[0], 2, meshdata->numIndex) != nIndexCount)
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

    // transform
    float bindShape[16];
    if (!_bundleReader->readMatrix(bindShape))
    {
        CCLOGINFO("Failed to read SkinData: bindShape matrix  '%s'.", _path.c_str());
        return false;
    }

    // bone count 
    unsigned int boneNum;
    if (!_bundleReader->read(&boneNum))
    {
        CCLOGINFO("Failed to read SkinData: boneNum  '%s'.", _path.c_str());
        return false;
    }
    
    // bone names and bind pos
    float bindpos[16];
    for (unsigned int i = 0; i < boneNum; i++)
    {
        skindata->boneNames.push_back(_bundleReader->readString());
        if (!_bundleReader->readMatrix(bindpos))
        {
            CCLOGINFO("Failed to load SkinData: bindpos '%s'.", _path.c_str());
            return NULL;
        }
        skindata->inverseBindPoseMatrices.push_back(bindpos);
    }

    // bind shape
    bindShape[16];
    _bundleReader->readMatrix(bindShape);

    // read parent and child relationship map
    float transform[16];
    unsigned int linkNum;
    _bundleReader->read(&linkNum);
    for (unsigned int i = 0; i < linkNum; ++i)
    {
        std::string id = _bundleReader->readString();
        int index = skindata->getBoneNameIndex(id);

        if (index >= 0 && skindata->rootBoneIndex < 0)
            skindata->rootBoneIndex = index;

        std::string parentid = _bundleReader->readString();
        int parentIndex = skindata->getBoneNameIndex(parentid);
        
        if (!_bundleReader->readMatrix(transform))
        {
            CCLOGINFO("Failed to load SkinData: transform '%s'.", _path.c_str());
            return NULL;
        }

        if (parentIndex < 0 || index < 0)
            continue;

        skindata->boneChild[parentIndex].push_back(index);
    }

    return true;
}

bool Bundle3D::loadMaterialDataBinary(MaterialData* materialdata)
{
    if (!seekToFirstType(BUNDLE_TYPE_MATERIAL))
        return false;

    std::string texturePath = _bundleReader->readString();
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

    std::string id = _bundleReader->readString();

    if (!_bundleReader->read(&animationdata->_totalTime))
    {
        CCLOGINFO("Failed to read AnimationData: totalTime '%s'.", _path.c_str());
        return false;
    }

    unsigned int animNum;
    if (!_bundleReader->read(&animNum))
    {
        CCLOGINFO("Failed to read AnimationData: animNum '%s'.", _path.c_str());
        return false;
    }

    for (unsigned int i = 0; i < animNum; ++i)
    {
        std::string boneName = _bundleReader->readString();
        unsigned int keyframeNum;
        if (!_bundleReader->read(&keyframeNum))
        {
            CCLOGINFO("Failed to read AnimationData: keyframeNum '%s'.", _path.c_str());
            return false;
        }

        for (unsigned int j = 0; j < keyframeNum; ++j)
        {
            float keytime;
            if (!_bundleReader->read(&keytime))
            {
                CCLOGINFO("Failed to read AnimationData: keytime '%s'.", _path.c_str());
                return false;
            }

            Quaternion  rotate;
            if (_bundleReader->read(&rotate, 4, 4) != 4)
            {
                CCLOGINFO("Failed to read AnimationData: rotate '%s'.", _path.c_str());
                return false;
            }
            animationdata->_rotationKeys[boneName].push_back(Animation3DData::QuatKey(keytime, rotate));

            Vec3 scale;
            if (_bundleReader->read(&scale, 4, 3) != 3)
            {
                CCLOGINFO("Failed to read AnimationData: scale '%s'.", _path.c_str());
                return false;
            }
            animationdata->_scaleKeys[boneName].push_back(Animation3DData::Vec3Key(keytime, scale));

            Vec3 position;
            if (_bundleReader->read(&position, 4, 3) != 3)
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

Reference* Bundle3D::seekToFirstType(unsigned int type)
{
    // for each Reference
    for (unsigned int i = 0; i < _referenceCount; ++i)
    {
        Reference* ref = &_references[i];
        if (ref->type == type)
        {
            // Found a match
            if (_bundleReader->seek(ref->offset, SEEK_SET) == false)
            {
                CCLOGINFO("Failed to seek to object '%s' in bundle '%s'.", ref->id.c_str(), _path.c_str());
                return NULL;
            }
            return ref;
        }
    }
    return NULL;
}

Bundle3D::Bundle3D()
:_isBinary(false),
_modelRelativePath(""),
_jsonBuffer(NULL),
_path(""),
_referenceCount(0),
_bundleReader(NULL),
_references(NULL),
_binaryBuffer(NULL)
{

}
Bundle3D::~Bundle3D()
{
    CC_SAFE_DELETE_ARRAY(_jsonBuffer);
    CC_SAFE_DELETE_ARRAY(_bundleReader);
    CC_SAFE_DELETE_ARRAY(_references);
    CC_SAFE_DELETE(_binaryBuffer);
}

NS_CC_END

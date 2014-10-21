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

#ifndef __CCBUNDLE3D_H__
#define __CCBUNDLE3D_H__

#include "3d/CCBundle3DData.h"
#include "3d/CCBundleReader.h"
#include "json/document.h"

NS_CC_BEGIN
class Animation3D;
class Data;

/**
 * Defines a bundle file that contains a collection of assets. Mesh, Material, MeshSkin, Animation
 * There are two types of bundle files, c3t and c3b.
 * c3t text file
 * c3b binary file
 */
class CC_DLL Bundle3D
{
public:
    /**you can define yourself bundle and set it, use default bundle otherwise*/
    static void setBundleInstance(Bundle3D* bundleInstance);
    
    static Bundle3D* getInstance();
    
    static void destroyInstance();
    
	virtual void clear();

    /**
     * load a file. You must load a file first, then call loadMeshData, loadSkinData, and so on
     * @param path File to be loaded
     * @return result of load
     */
    virtual bool load(const std::string& path);
    
    /**
     * load skin data from bundle
     * @param id The ID of the skin, load the first Skin in the bundle if it is empty
     */
    virtual bool loadSkinData(const std::string& id, SkinData* skindata);
    
    /**
     * load material data from bundle
     * @param id The ID of the animation, load the first animation in the bundle if it is empty
     */
    virtual bool loadAnimationData(const std::string& id, Animation3DData* animationdata);
    
    //since 3.3, to support reskin
    virtual bool loadMeshDatas(MeshDatas& meshdatas);
    //since 3.3, to support reskin
    virtual bool loadNodes(NodeDatas& nodedatas);
    //since 3.3, to support reskin
    virtual bool loadMaterials(MaterialDatas& materialdatas);
    
    //load .obj file
    static bool loadObj(MeshDatas& meshdatas, MaterialDatas& materialdatas, NodeDatas& nodedatas, const std::string& fullPath, const char* mtl_basepath = nullptr);
  
protected:

    bool loadJson(const std::string& path);
    bool loadBinary(const std::string& path);
    bool loadMeshDatasJson(MeshDatas& meshdatas);
    bool loadMeshDataJson_0_1(MeshDatas& meshdatas);
    bool loadMeshDataJson_0_2(MeshDatas& meshdatas);
    bool loadMeshDatasBinary(MeshDatas& meshdatas);
    bool loadMeshDatasBinary_0_1(MeshDatas& meshdatas);
    bool loadMeshDatasBinary_0_2(MeshDatas& meshdatas);
    bool loadMaterialsJson(MaterialDatas& materialdatas);
    bool loadMaterialDataJson_0_1(MaterialDatas& materialdatas);
    bool loadMaterialDataJson_0_2(MaterialDatas& materialdatas);
    bool loadMaterialsBinary(MaterialDatas& materialdatas);
    bool loadMaterialsBinary_0_1(MaterialDatas& materialdatas);
    bool loadMaterialsBinary_0_2(MaterialDatas& materialdatas);
    bool loadMeshDataJson(MeshData* meshdata){return true;}
    bool loadMeshDataJson_0_1(MeshData* meshdata){return true;}
    bool loadMeshDataJson_0_2(MeshData* meshdata){return true;}
    bool loadSkinDataJson(SkinData* skindata);
    bool loadSkinDataBinary(SkinData* skindata);
    bool loadMaterialDataJson(MaterialData* materialdata){return true;}
    bool loadMaterialDataJson_0_1(MaterialData* materialdata){return true;}
    bool loadMaterialDataJson_0_2(MaterialData* materialdata){return true;}
    bool loadAnimationDataJson(const std::string& id,Animation3DData* animationdata);
    bool loadAnimationDataBinary(const std::string& id,Animation3DData* animationdata);

    /**
     * load nodes of json
     */
    bool loadNodesJson(NodeDatas& nodedatas);
    NodeData* parseNodesRecursivelyJson(const rapidjson::Value& jvalue);

    /**
     * load nodes of binary
     */
    bool loadNodesBinary(NodeDatas& nodedatas);
    NodeData* parseNodesRecursivelyBinary(bool& skeleton);

    /**
     * get define data type
     * @param str The type in string
     */
    GLenum parseGLType(const std::string& str);

     /**
     * get define data type
     * @param str The type in string
     */
    NTextureData::Usage parseGLTextureType(const std::string& str);

    /**
     * get vertex attribute type
     * @param str The type in string
     */
    unsigned int parseGLProgramAttribute(const std::string& str);

    /*
     * get model path
     * @param str Full path of model file
     */
    void getModelRelativePath(const std::string& path);

    /*
    * set the read position in buffer to the target type
    * @param The data type
    */
    Reference* seekToFirstType(unsigned int type);

CC_CONSTRUCTOR_ACCESS:
    Bundle3D();
    virtual ~Bundle3D();
    
protected:
    static Bundle3D* _instance;
    std::string _modelPath;
    std::string _path;
    std::string _version;// the c3b or c3t version
    
    // for json reading
    char* _jsonBuffer;
    rapidjson::Document _jsonReader;

    // for binary reading
    Data* _binaryBuffer;
    BundleReader _binaryReader;
    unsigned int _referenceCount;
    Reference* _references;
    bool  _isBinary;
};

NS_CC_END

#endif // __CCBUNDLE3D_H__

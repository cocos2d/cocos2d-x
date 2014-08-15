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

#include <map>

#include "3d/CCBundle3DData.h"

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"

#include "json/document.h"
#include "CCBundleReader.h"

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
     * load mesh data from bundle
     * @param id The ID of the mesh, load the first Mesh in the bundle if it is empty
     */
    virtual bool loadMeshData(const std::string& id, MeshData* meshdata);
    
    /**
     * load skin data from bundle
     * @param id The ID of the skin, load the first Skin in the bundle if it is empty
     */
    virtual bool loadSkinData(const std::string& id, SkinData* skindata);
    
    /**
     * load material data from bundle
     * @param id The ID of the material, load the first Material in the bundle if it is empty
     */
    virtual bool loadMaterialData(const std::string& id, MaterialData* materialdata);
    
    /**
     * load material data from bundle
     * @param id The ID of the animation, load the first animation in the bundle if it is empty
     */
    virtual bool loadAnimationData(const std::string& id, Animation3DData* animationdata);
    
    /**
     * load skeleton data from bundle
     *
     */
    virtual bool loadSkeletonData(const std::string& id, Skeleton3DData* skeletondata);

protected:

    bool loadJson(const std::string& path);
    
    bool loadMeshDataJson(MeshData* meshdata);
    bool loadMeshDataJson_0_1(MeshData* meshdata);
    bool loadMeshDataJson_0_2(MeshData* meshdata);
    
    bool loadSkinDataJson(SkinData* skindata);
    
    bool loadMaterialDataJson(MaterialData* materialdata);
    bool loadMaterialDataJson_0_1(MaterialData* materialdata);
    bool loadMaterialDataJson_0_2(MaterialData* materialdata);
    
    bool loadAnimationDataJson(Animation3DData* animationdata);

    /**
     * load data in binary
     * @param path The c3b file path
     */
    bool loadBinary(const std::string& path);

    /**
     * load mesh data in binary
     * @param meshdata The mesh data pointer
     */
    bool loadMeshDataBinary(MeshData* meshdata);
    bool loadMeshDataBinary_0_1(MeshData* meshdata);
    bool loadMeshDataBinary_0_2(MeshData* meshdata);

    /**
     * load skin data in binary
     * @param skindata The skin data pointer
     */
    bool loadSkinDataBinary(SkinData* skindata);

    /**
     * load material data in binary
     * @param materialdata The material pointer 
     */
    bool loadMaterialDataBinary(MaterialData* materialdata);

    /**
     * load animation data in binary
     * @param animationdata The animation data pointer
     */
    bool loadAnimationDataBinary(Animation3DData* animationdata);

    /**
     * get define data type
     * @param str The type in string
     */
    GLenum parseGLType(const std::string& str);

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

protected:
CC_CONSTRUCTOR_ACCESS:
    Bundle3D();
    ~Bundle3D();
    
protected:
    
    static Bundle3D* _instance;
    
    std::string _modelRelativePath;
    std::string         _path;
    
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

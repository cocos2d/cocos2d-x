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

/**
 * @addtogroup _3d
 * @{
 */

class Animation3D;
class Data;

/**
 * @class Bundle3D
 * @brief @~english Defines a bundle file that contains a collection of assets. Mesh, Material, MeshSkin, Animation
 * There are two types of bundle files, c3t and c3b.
 * c3t text file
 * c3b binary file
 * @~chinese Bundle3D 类，所谓Bundle3D类包含了一系列的资源，诸如网格，材质，网格蒙皮信息，以及动画等的文件格式。共有两种类型的Bundle 文件，一种是
 * 文本形式的c3t文件，一种是二进制形式的c3b文件
 * @js NA
 * @lua NA
 */
class CC_DLL Bundle3D
{
public:
    /**
     * @~english Create a new bundle, destroy it when finish using it
     * @~chinese 创建一个新的Bundle3D对象，将在使用后销毁
     * @return @~english The Bundle3D object
     * @~chinese 被创建的Bundle3D对象
     */
    static Bundle3D* createBundle();
    
    /**
     * @~english Destroy the specified Bundle3D object.
     * @~chinese 销毁指定的Bundle3D对象
     * @param bundle the Bundle3D object.
     * @~chinese 指定的Bundl3D对象
     */
    static void destroyBundle(Bundle3D* bundle);
    
    /**
     * @~english Clear the Bundle3D object's buffer
     * @~chinese 清空指定Bundle3D对象的缓冲区
     **/
	virtual void clear();

    /**
     * @~english Load a file. You must load a file first, then call loadMeshData, loadSkinData, and so on
     * @~chinese 载入一个文件，你必须在载入文件完成之后在调用loadMeshData与loadSkinData等方法
     * @param path @~english File to be loaded
     * @~chinese 被载入的文件路径
     * @return @~english result of load
     * @~chinese 载入结果
     */
    virtual bool load(const std::string& path);
    
    /**
     * @~english load skin data from bundle.
     * @~chinese 读取Bundle3D中的蒙皮信息
     * @param id @~english The ID of the skin, load the first Skin in the bundle if it is empty.
     * @~chinese 蒙皮的索引，如果蒙蔽索引为空，则将会读取该bundle中的第一个蒙皮信息
     * @param skindata @~english the SkinData which you need.
     * @~chinese 获取的SkinData对象
     * @return @~english Result of the load.
     * @~chinese 载入结果
     */
    virtual bool loadSkinData(const std::string& id, SkinData* skindata);
    
    /**
     * @~english Load animation data from bundle
     * @~chinese 读取bundle中的动画数据
     * @param id @~english The ID of the animation, load the first animation in the bundle if it is empty
     * @~chinese 动画的索引，如果索引为空，则读取bundle中的第一个动画
     * @param animationdata @~english The Animation3DData which you need.
     * @~chinese 得到的Animation3DData对象
     * @return @~english Result of the load
     * @~chinese 载入结果
     */
    virtual bool loadAnimationData(const std::string& id, Animation3DData* animationdata);
    
    //since 3.3, to support reskin
    virtual bool loadMeshDatas(MeshDatas& meshdatas);
    //since 3.3, to support reskin
    virtual bool loadNodes(NodeDatas& nodedatas);
    //since 3.3, to support reskin
    virtual bool loadMaterials(MaterialDatas& materialdatas);
    
    /**
     * @~english Load triangle list
     * @~chinese 读取网格的三角列表
     * @param path @~english The file path to load.
     * @~chinese bundle文件路径
     * @return @~english The std::vector which contatin triangles.
     * @~chinese 三角形列表的std::vector对象
     */
    static std::vector<Vec3> getTrianglesList(const std::string& path);
    
    /**
     * @~english Load .obj format. 
     * @~chinese 读取.ojb格式文件
     * @param meshdatas @~english The mesh datas.
     * @~chinese 读取后获得的网格数据
     * @param materialdatas @~english The materialdatas.
     * @~chinese 读取后获得的材质数据
     * @param nodedatas @~english The node data.
     * @~chinese 读取后获得的节点数据
     * @param fullPath @~english The .obj file path.
     * @~chinese .obj文件的路径
     * @param mtl_basepath @~english The material base path.
     * @~chinese 材质文件的搜索父路径
     * @return @~english The result of the load.
     * @~chinese 读取的结果
     **/
    static bool loadObj(MeshDatas& meshdatas, MaterialDatas& materialdatas, NodeDatas& nodedatas, const std::string& fullPath, const char* mtl_basepath = nullptr);
    
    /**
     * @~english Calculate the AABB.
     * @~chinese 计算AABB
     * @param vertex @~english Vertices list.
     * @~chinese  顶点数组
     * @param stride @~english The stride of the element.
     * @~chinese 顶点数组中每个元素之间的跨距
     * @param index @~english The indices list.
     * @~chinese 索引数组
     **/
    static AABB calculateAABB(const std::vector<float>& vertex, int stride, const std::vector<unsigned short>& index);
  
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
    NodeData* parseNodesRecursivelyJson(const rapidjson::Value& jvalue, bool singleSprite);

    /**
     * load nodes of binary
     */
    bool loadNodesBinary(NodeDatas& nodedatas);
    NodeData* parseNodesRecursivelyBinary(bool& skeleton, bool singleSprite);

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
     * @param The data id
     */
    Reference* seekToFirstType(unsigned int type, const std::string& id = "");

CC_CONSTRUCTOR_ACCESS:
    Bundle3D();
    virtual ~Bundle3D();
    
protected:
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

// end of 3d group
/// @}

NS_CC_END

#endif // __CCBUNDLE3D_H__

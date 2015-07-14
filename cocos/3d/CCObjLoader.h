//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD liecense.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _TINY_OBJ_LOADER_H
#define _TINY_OBJ_LOADER_H

#include <string>
#include <vector>
#include <map>

/**
 * @addtogroup _3d
 * @{
 */

namespace tinyobj {
    
    /**
     * @~english Model's material struct
     * @~chinese .obj模型材质结构体
     **/
    typedef struct {
        std::string name;
        
        float ambient[3];
        float diffuse[3];
        float specular[3];
        float transmittance[3];
        float emission[3];
        float shininess;
        float ior;      // index of refraction
        float dissolve; // 1 == opaque; 0 == fully transparent
        // illumination model (see http://www.fileformat.info/format/material/)
        int illum;
        
        std::string ambient_texname;
        std::string diffuse_texname;
        std::string specular_texname;
        std::string normal_texname;
        std::map<std::string, std::string> unknown_parameter;
    } material_t;
    
    /**
     * @~english Model's mesh struct
     * @~chinese .obj模型mesh结构体
     **/
    typedef struct {
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> texcoords;
        std::vector<unsigned short> indices;
        std::vector<int> material_ids; // per-mesh material ID
    } mesh_t;
    
    /**
     * @~english Model's shape struct
     * @~chinese .obj模型形状结构体
     **/
    typedef struct {
        std::string name;
        mesh_t mesh;
    } shape_t;
    
    /**
     * @brief @~english Material reader
     * @~chinese 材质读取类
     * @js NA
     * @lua NA
     **/
    class MaterialReader {
    public:
        MaterialReader() {}
        virtual ~MaterialReader() {}
        
        virtual std::string operator()(const std::string &matId,
                                       std::vector<material_t> &materials,
                                       std::map<std::string, int> &matMap) = 0;
    };
    
    class MaterialFileReader : public MaterialReader {
    public:
        MaterialFileReader(const std::string &mtl_basepath)
        : m_mtlBasePath(mtl_basepath) {}
        virtual ~MaterialFileReader() {}
        virtual std::string operator()(const std::string &matId,
                                       std::vector<material_t> &materials,
                                       std::map<std::string, int> &matMap);
        
    private:
        std::string m_mtlBasePath;
    };

    /** @~english Loads .obj from a file.
     * shapes will be filled with parsed shape data
     * The function returns error string.
     * Returns empty string when loading .obj success.
     * mtl_basepath is optional, and used for base path for .mtl file.
     * @~chinese 通过.obj文件读取模型，shapes用读取到的模型形状数据填满。函数返回出错字符串，当模型读取成功时返回空字符串。
     * @param shapes @~english Model shapes which will be filled by parsed data.
     * @~chinese 模型形状，将被读取的模型数据填充。
     * @param filename @~english The .obj file path.
     * @~chinese .obj文件路径
     * @param mtl_basepath @~english It's optional, it is the base path of .mtl file
     * @~chinese 材质文件路径，可选参数。
     * @return @~english The function returns error string, return empty string when loading .obj succeed.
     * @~chinese 当模型读取成功，返回空字符串，反之返回带有错误信息的字符串
     */
    std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                        std::vector<material_t> &materials, // [output]
                        const char *filename, const char *mtl_basepath = NULL);
    
    /** @~english Loads object from a std::istream and material reader object.
     * @~chinese 从流和材质读取对象中读取obj文件。
     * @param shapes @~english Model shapes which will be filled by parsed data.
     * @~chinese 模型形状，将被读取的模型数据填充。
     * @param materials @~english Materials filled by parased data.
     * @~chinese 读取的材质对象
     * @param inStream @~english Stream used to read .obj file.
     * @~chinese 用来读取obj文件的数据流。
     * @param readMatFn @~english Object used to read material.
     * @~chinese 材质对象。
     * @return @~english Error string, empty string when loading .obj success.
     * @~chinese 返回错误信息，当读取成功时为空字符串。
     */
    std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                        std::vector<material_t> &materials, // [output]
                        std::istream &inStream, MaterialReader &readMatFn);
    
    /** @~english Loads materials from stream.
     * @~chinese 从数据流中加载材质。
     * @param material_map @~english Used to store material name its index. @~chinese 材质映射用来存储材质名称和其索引。
     * @param materials @~english Materials filled by parased data. @~chinese 材质对象。
     * @param inStream @~english Stream used to read material. @~chinese 用来读取材质对象的数据流。
     * @return @~english An empty string if successful, error string other wise. @~chinese 如果成功返回空字符串，否则返回错误信息。
     */
    std::string LoadMtl(std::map<std::string, int> &material_map,
                        std::vector<material_t> &materials, std::istream &inStream);
}

// end of 3d group
/// @}

#endif // _TINY_OBJ_LOADER_H

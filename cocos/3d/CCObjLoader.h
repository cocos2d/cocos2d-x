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
     * @~english Model's indices struct
     * @~chinese .obj模型顶点结构体
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
     * @brief @~english 
     * @~chinese 
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

    /** Loads .obj from a file.
     * 'shapes' will be filled with parsed shape data
     * The function returns error string.
     * Returns empty string when loading .obj success.
     * 'mtl_basepath' is optional, and used for base path for .mtl file.
     *
     * @~chinese 通过.obj文件读取模型
     * @param shapes @~english will be filled with parsed shape data
     * @~chinese 输出的.obj信息
     * @param filename @~english The .obj file path .
     * @~chinese .obj文件路径
     * @param mtl_basepath @~english It's optional, and used for base path for .mtl file
     * @~chinese 可选的材质基路径，将在此基础上查询材质文件
     * @return @~english The function returns error string, return empty string when loading .obj success.
     * @~chinese 当模型读取成功，返回空字符串，反之返回带有错误信息的字符串
     */
    std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                        std::vector<material_t> &materials, // [output]
                        const char *filename, const char *mtl_basepath = NULL);
    
    /// Loads object from a std::istream, uses GetMtlIStreamFn to retrieve
    /// std::istream for materials.
    /// Returns empty string when loading .obj success.
    std::string LoadObj(std::vector<shape_t> &shapes,       // [output]
                        std::vector<material_t> &materials, // [output]
                        std::istream &inStream, MaterialReader &readMatFn);
    
    /// Loads materials into std::map
    /// Returns an empty string if successful
    std::string LoadMtl(std::map<std::string, int> &material_map,
                        std::vector<material_t> &materials, std::istream &inStream);
}

// end of 3d group
/// @}

#endif // _TINY_OBJ_LOADER_H

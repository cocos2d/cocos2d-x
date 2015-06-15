//
// Copyright 2012-2013, Syoyo Fujita.
//
// Licensed under 2-clause BSD liecense.
//
// copied from Syoyo Fujita
// https://github.com/syoyo/tinyobjloader

#ifndef __CCOBJLOADER_H__
#define __CCOBJLOADER_H__

#include <string>
#include <vector>
#include <map>
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @brief @~english .obj file Loader
 * @~chinese .obj文件读取器
 * @js NA
 * @lua NA
 **/
class ObjLoader
{
public:

    /**
     * @~english Model's material struct
     * @~chinese .obj模型材质结构体
     **/
    typedef struct
    {
        std::string name;
        
        float ambient[3];
        float diffuse[3];
        float specular[3];
        float transmittance[3];
        float emission[3];
        float shininess;
        float ior;                // index of refraction
        float dissolve;           // 1 == opaque; 0 == fully transparent
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
    typedef struct
    {
        std::vector<unsigned short>   indices;
    } mesh_t;
    
    /**
     * @~english Model's shape struct
     * @~chinese .obj模型形状结构体
     **/
    typedef struct
    {
        std::string  name;
        material_t   material;
        mesh_t       mesh;
    } shape_t;
    
    /**
     * @~english model's shapes struct
     * @~chinese .obj模型形状数组结构体
     **/
    typedef struct
    {
        std::vector<float>          positions;
        std::vector<float>          normals;
        std::vector<float>          texcoords;
        
        std::vector<shape_t>  shapes;
        
        void reset()
        {
            positions.clear();
            normals.clear();
            texcoords.clear();
            shapes.clear();
        }
    }shapes_t;
    
    /**
     * @~english Loads .obj from a file.
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
    static std::string LoadObj(
                        shapes_t& shapes,   // [output]
                        const char* filename,
                        const char* mtl_basepath = NULL);

};

// end of 3d group
/// @}

NS_CC_END

#endif  // _TINY_OBJ_LOADER_H

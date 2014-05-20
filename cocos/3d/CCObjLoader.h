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

class ObjLoader
{
public:
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
    
    typedef struct
    {
        std::vector<unsigned short>   indices;
    } mesh_t;
    
    typedef struct
    {
        std::string  name;
        material_t   material;
        mesh_t       mesh;
    } shape_t;
    
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
    
    /// Loads .obj from a file.
    /// 'shapes' will be filled with parsed shape data
    /// The function returns error string.
    /// Returns empty string when loading .obj success.
    /// 'mtl_basepath' is optional, and used for base path for .mtl file.
    static std::string LoadObj(
                        shapes_t& shapes,   // [output]
                        const char* filename,
                        const char* mtl_basepath = NULL);

};

NS_CC_END

#endif  // _TINY_OBJ_LOADER_H

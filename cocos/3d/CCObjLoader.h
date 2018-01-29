/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef _TINY_OBJ_LOADER_H
#define _TINY_OBJ_LOADER_H

#include <string>
#include <vector>
#include <map>

namespace tinyobj {
    
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
    
    typedef struct {
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> texcoords;
        std::vector<unsigned short> indices;
        std::vector<int> material_ids; // per-mesh material ID
    } mesh_t;
    
    typedef struct {
        std::string name;
        mesh_t mesh;
    } shape_t;
    
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
    
    /// Loads .obj from a file.
    /// 'shapes' will be filled with parsed shape data
    /// The function returns error string.
    /// Returns empty string when loading .obj success.
    /// 'mtl_basepath' is optional, and used for base path for .mtl file.
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

#endif // _TINY_OBJ_LOADER_H

//
// Copyright 2012-2013, Syoyo Fujita.
//
// Licensed under 2-clause BSD liecense.
//

//
// version 0.9.6: Support Ni(index of refraction) mtl parameter.
//                Parse transmittance material parameter correctly.
// version 0.9.5: Parse multiple group name.
//                Add support of specifying the base path to load material file.
// version 0.9.4: Initial suupport of group tag(g)
// version 0.9.3: Fix parsing triple 'x/y/z'
// version 0.9.2: Add more .mtl load support
// version 0.9.1: Add initial .mtl load support
// version 0.9.0: Initial
//

#include <cstdlib>
#include <cstring>
#include <cassert>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "CCObjLoader.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

struct vertex_index 
{
    int v_idx, vt_idx, vn_idx;
    vertex_index() {};
    vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) {};
    vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) {};
    
};
// for std::map
static inline bool operator<(const vertex_index& a, const vertex_index& b)
{
    if (a.v_idx != b.v_idx) return (a.v_idx < b.v_idx);
    if (a.vn_idx != b.vn_idx) return (a.vn_idx < b.vn_idx);
    if (a.vt_idx != b.vt_idx) return (a.vt_idx < b.vt_idx);
    return false;
}

struct obj_shape 
{
    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;
};

static inline bool isSpace(const char c) 
{
    return (c == ' ') || (c == '\t');
}

static inline bool isNewLine(const char c) 
{
    return (c == '\r') || (c == '\n') || (c == '\0');
}

// Make index zero-base, and also support relative index.
static inline int fixIndex(int idx, int n)
{
    int i;
    
    if (idx > 0) {
        i = idx - 1;
    } else if (idx == 0) {
        i = 0;
    } else { // negative value = relative
        i = n + idx;
    }
    return i;
}

static inline std::string parseString(const char*& token)
{
    std::string s;
    auto b = strspn(token, " \t");
    auto e = strcspn(token, " \t\r");
    s = std::string(&token[b], &token[e]);
    
    token += (e - b);
    return s;
}

static inline int parseInt(const char*& token)
{
    token += strspn(token, " \t");
    int i = atoi(token);
    token += strcspn(token, " \t\r");
    return i;
}

static inline float parseFloat(const char*& token)
{
    token += strspn(token, " \t");
    float f = (float)atof(token);
    token += strcspn(token, " \t\r");
    return f;
}

static inline void parseFloat2(float& x, float& y, const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
}

static inline void parseFloat3(float& x, float& y, float& z, const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
    z = parseFloat(token);
}

// Parse triples: i, i/j/k, i//k, i/j
static vertex_index parseTriple(const char* &token, int vsize, int vnsize, int vtsize)
{
    vertex_index vi(-1);
    
    vi.v_idx = fixIndex(atoi(token), vsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }
    token++;
    
    // i//k
    if (token[0] == '/') {
        token++;
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }
    
    // i/j/k or i/j
    vi.vt_idx = fixIndex(atoi(token), vtsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }
    
    // i/j/k
    token++;  // skip '/'
    vi.vn_idx = fixIndex(atoi(token), vnsize);
    token += strcspn(token, "/ \t\r");
    return vi;
}

static ssize_t updateVertex( std::map<vertex_index, ssize_t>& vertexCache, std::vector<float>& positions, std::vector<float>& normals,
             std::vector<float>& texcoords, const std::vector<float>& in_positions, const std::vector<float>& in_normals, const std::vector<float>& in_texcoords,
             const vertex_index& i)
{
    const auto it = vertexCache.find(i);
    
    if (it != vertexCache.end()) 
    {
        // found cache
        return it->second;
    }
    
    assert(in_positions.size() > (3*i.v_idx+2));
    
    positions.push_back(in_positions[3*i.v_idx+0]);
    positions.push_back(in_positions[3*i.v_idx+1]);
    positions.push_back(in_positions[3*i.v_idx+2]);
    
    if (i.vn_idx >= 0) 
    {
        normals.push_back(in_normals[3*i.vn_idx+0]);
        normals.push_back(in_normals[3*i.vn_idx+1]);
        normals.push_back(in_normals[3*i.vn_idx+2]);
    }
    
    if (i.vt_idx >= 0) 
    {
        texcoords.push_back(in_texcoords[2*i.vt_idx+0]);
        texcoords.push_back(in_texcoords[2*i.vt_idx+1]);
    }
    
    auto idx = positions.size() / 3 - 1;
    vertexCache[i] = idx;
    
    return idx;
}

static bool exportFaceGroupToShape( std::map<vertex_index, ssize_t>& vertexCache, ObjLoader::shapes_t& shapes, const std::vector<float> &in_positions,
                       const std::vector<float> &in_normals, const std::vector<float> &in_texcoords, const std::vector<std::vector<vertex_index> >& faceGroup,
                       const ObjLoader::material_t &material, const std::string &name)
{
    if (faceGroup.empty()) 
    {
        return false;
    }
    
    // Flattened version of vertex data
    std::vector<float>& positions = shapes.positions;
    std::vector<float>& normals = shapes.normals;
    std::vector<float>& texcoords = shapes.texcoords;
    std::vector<unsigned short> indices;
    
    // Flatten vertices and indices
    for (size_t i = 0; i < faceGroup.size(); i++) 
    {
        const std::vector<vertex_index>& face = faceGroup[i];
        
        vertex_index i0 = face[0];
        vertex_index i1(-1);
        vertex_index i2 = face[1];
        
        size_t npolys = face.size();
        
        // Polygon -> triangle fan conversion
        for (size_t k = 2; k < npolys; k++) 
        {
            i1 = i2;
            i2 = face[k];
            
            unsigned short v0 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i0);
            unsigned short v1 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i1);
            unsigned short v2 = updateVertex(vertexCache, positions, normals, texcoords, in_positions, in_normals, in_texcoords, i2);
            
            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v2);
        }
    }
    
    ObjLoader::shape_t shape;
    shape.name = name;
    shape.material = material;
    shape.mesh.indices.swap(indices);
    
    shapes.shapes.push_back(shape);
    return true;
    
}

std::string trim(const std::string& str)
{
    if (str.empty())
        return str;
    auto len = str.length();
    char c = str[len - 1];
    while (c == '\r' || c == '\n') 
    {
        len--;
        c = str[len - 1];
    }
    return str.substr(0, len);
}

void InitMaterial(ObjLoader::material_t& material) 
{
    material.name = "";
    material.ambient_texname = "";
    material.diffuse_texname = "";
    material.specular_texname = "";
    material.normal_texname = "";
    for (int i = 0; i < 3; i ++) 
    {
        material.ambient[i] = 0.f;
        material.diffuse[i] = 0.f;
        material.specular[i] = 0.f;
        material.transmittance[i] = 0.f;
        material.emission[i] = 0.f;
    }
    material.illum = 0;
    material.dissolve = 1.f;
    material.shininess = 1.f;
    material.unknown_parameter.clear();
}

std::string LoadMtl ( std::map<std::string, ObjLoader::material_t>& material_map, const char* filename, const char* mtl_basepath)
{
    material_map.clear();
    std::stringstream err;
    
    std::string filepath;
    
    if (mtl_basepath) 
    {
        filepath = std::string(mtl_basepath) + std::string(filename);
    }
    else 
    {
        filepath = std::string(filename);
    }
    
    std::ifstream ifs(filepath.c_str());
    if (!ifs) 
    {
        err << "Cannot open file [" << filepath << "]" << std::endl;
        return err.str();
    }
    
    ObjLoader::material_t material;
    
    int maxchars = 8192;  // Alloc enough size.
    std::vector<char> buf(maxchars);  // Alloc enough size.
    while (ifs.peek() != -1) 
    {
        ifs.getline(&buf[0], maxchars);
        
        std::string linebuf(&buf[0]);
        
        // Trim newline '\r\n' or '\r'
        if (linebuf.size() > 0) 
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        if (linebuf.size() > 0)
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        
        // Skip if empty line.
        if (linebuf.empty())
        {
            continue;
        }
        
        // Skip leading space.
        const char* token = linebuf.c_str();
        token += strspn(token, " \t");
        
        assert(token);
        if (token[0] == '\0') continue; // empty line
        
        if (token[0] == '#') continue;  // comment line
        
        // new mtl
        if ((0 == strncmp(token, "newmtl", 6)) && isSpace((token[6])))
        {
            // flush previous material.
            material_map.insert(std::pair<std::string, ObjLoader::material_t>(material.name, material));
            
            // initial temporary material
            InitMaterial(material);
            
            // set new mtl name
            char namebuf[4096];
            token += 7;
            sscanf(token, "%s", namebuf);
            material.name = namebuf;
            continue;
        }
        
        // ambient
        if (token[0] == 'K' && token[1] == 'a' && isSpace((token[2])))
        {
            token += 2;
            float r, g, b;
            parseFloat3(r, g, b, token);
            material.ambient[0] = r;
            material.ambient[1] = g;
            material.ambient[2] = b;
            continue;
        }
        
        // diffuse
        if (token[0] == 'K' && token[1] == 'd' && isSpace((token[2])))
        {
            token += 2;
            float r, g, b;
            parseFloat3(r, g, b, token);
            material.diffuse[0] = r;
            material.diffuse[1] = g;
            material.diffuse[2] = b;
            continue;
        }
        
        // specular
        if (token[0] == 'K' && token[1] == 's' && isSpace((token[2])))
        {
            token += 2;
            float r, g, b;
            parseFloat3(r, g, b, token);
            material.specular[0] = r;
            material.specular[1] = g;
            material.specular[2] = b;
            continue;
        }
        
        // transmittance
        if (token[0] == 'K' && token[1] == 't' && isSpace((token[2])))
        {
            token += 2;
            float r, g, b;
            parseFloat3(r, g, b, token);
            material.transmittance[0] = r;
            material.transmittance[1] = g;
            material.transmittance[2] = b;
            continue;
        }
        
        // ior(index of refraction)
        if (token[0] == 'N' && token[1] == 'i' && isSpace((token[2])))
        {
            token += 2;
            material.ior = parseFloat(token);
            continue;
        }
        
        // emission
        if(token[0] == 'K' && token[1] == 'e' && isSpace(token[2]))
        {
            token += 2;
            float r, g, b;
            parseFloat3(r, g, b, token);
            material.emission[0] = r;
            material.emission[1] = g;
            material.emission[2] = b;
            continue;
        }
        
        // shininess
        if(token[0] == 'N' && token[1] == 's' && isSpace(token[2]))
        {
            token += 2;
            material.shininess = parseFloat(token);
            continue;
        }
        
        // illum model
        if (0 == strncmp(token, "illum", 5) && isSpace(token[5]))
        {
            token += 6;
            material.illum = parseInt(token);
            continue;
        }
        
        // dissolve
        if ((token[0] == 'd' && isSpace(token[1])))
        {
            token += 1;
            material.dissolve = parseFloat(token);
            continue;
        }
        if (token[0] == 'T' && token[1] == 'r' && isSpace(token[2]))
        {
            token += 2;
            material.dissolve = parseFloat(token);
            continue;
        }
        
        // ambient texture
        if ((0 == strncmp(token, "map_Ka", 6)) && isSpace(token[6]))
        {
            token += 7;
            material.ambient_texname = trim(token);
            continue;
        }
        
        // diffuse texture
        if ((0 == strncmp(token, "map_Kd", 6)) && isSpace(token[6]))
        {
            token += 7;
            material.diffuse_texname = trim(token);
            continue;
        }
        
        // specular texture
        if ((0 == strncmp(token, "map_Ks", 6)) && isSpace(token[6]))
        {
            token += 7;
            material.specular_texname = trim(token);
            continue;
        }
        
        // normal texture
        if ((0 == strncmp(token, "map_Ns", 6)) && isSpace(token[6]))
        {
            token += 7;
            material.normal_texname = trim(token);
            continue;
        }
        
        // unknown parameter
        const char* _space = strchr(token, ' ');
        if(!_space)
        {
            _space = strchr(token, '\t');
        }
        if(_space)
        {
            auto len = _space - token;
            std::string key(token, len);
            std::string value = _space + 1;
            material.unknown_parameter.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    // flush last material.
    material_map.insert(std::pair<std::string, ObjLoader::material_t>(material.name, material));
    return err.str();
}

std::string ObjLoader::LoadObj(shapes_t& shapes, const char* filename, const char* mtl_basepath)
{
    shapes.reset();
    
    std::stringstream err;
    std::istringstream ifs(FileUtils::getInstance()->getStringFromFile(filename));
    std::map<vertex_index, ssize_t> vertexCache;
    //std::ifstream ifs(filename);
    
    if (!ifs)
    {
        err << "Cannot open file [" << filename << "]" << std::endl;
        return err.str();
    }
    
    std::vector<float> v;
    std::vector<float> vn;
    std::vector<float> vt;
    std::vector<std::vector<vertex_index> > faceGroup;
    std::string name;
    
    // material
    std::map<std::string, material_t> material_map;
    material_t material;
    
    int maxchars = 8192;  // Alloc enough size.
    std::vector<char> buf(maxchars);  // Alloc enough size.
    while (ifs.peek() != -1)
    {
        ifs.getline(&buf[0], maxchars);
        
        std::string linebuf(&buf[0]);
        
        // Trim newline '\r\n' or '\r'
        if (linebuf.size() > 0)
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        if (linebuf.size() > 0)
        {
            if (linebuf[linebuf.size()-1] == '\n') linebuf.erase(linebuf.size()-1);
        }
        
        // Skip if empty line.
        if (linebuf.empty())
        {
            continue;
        }
        
        // Skip leading space.
        const char* token = linebuf.c_str();
        token += strspn(token, " \t");
        
        assert(token);
        if (token[0] == '\0') continue; // empty line
        
        if (token[0] == '#') continue;  // comment line
        
        // vertex
        if (token[0] == 'v' && isSpace((token[1])))
        {
            token += 2;
            float x, y, z;
            parseFloat3(x, y, z, token);
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            continue;
        }
        
        // normal
        if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2])))
        {
            token += 3;
            float x, y, z;
            parseFloat3(x, y, z, token);
            vn.push_back(x);
            vn.push_back(y);
            vn.push_back(z);
            continue;
        }
        
        // texcoord
        if (token[0] == 'v' && token[1] == 't' && isSpace((token[2])))
        {
            token += 3;
            float x, y;
            parseFloat2(x, y, token);
            vt.push_back(x);
            vt.push_back(y);
            continue;
        }
        
        // face
        if (token[0] == 'f' && isSpace((token[1])))
        {
            token += 2;
            token += strspn(token, " \t");
            
            std::vector<vertex_index> face;
            while (!isNewLine(token[0])) {
                vertex_index vi = parseTriple(token, v.size() / 3, vn.size() / 3, vt.size() / 2);
                face.push_back(vi);
                auto n = strspn(token, " \t\r");
                token += n;
            }
            
            faceGroup.push_back(face);
            
            continue;
        }
        
        // use mtl
        if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6])))
        {
            
            char namebuf[4096];
            token += 7;
            sscanf(token, "%s", namebuf);
            
            if (material_map.find(namebuf) != material_map.end())
            {
                material = material_map[namebuf];
            }
            else
            {
                // { error!! material not found }
                InitMaterial(material);
            }
            continue;
            
        }
        
        // load mtl
        if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6])))
        {
            char namebuf[4096];
            token += 7;
            sscanf(token, "%s", namebuf);
            
            std::string err_mtl = LoadMtl(material_map, namebuf, mtl_basepath);
            if (!err_mtl.empty())
            {
                faceGroup.clear();  // for safety
                //return err_mtl;
            }
            continue;
        }
        
        // group name
        if (token[0] == 'g' && isSpace((token[1])))
        {
            // flush previous face group.
            shape_t shape;
            exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
            
            faceGroup.clear();
            
            std::vector<std::string> names;
            while (!isNewLine(token[0]))
            {
                std::string str = parseString(token);
                names.push_back(str);
                token += strspn(token, " \t\r"); // skip tag
            }
            
            assert(names.size() > 0);
            
            // names[0] must be 'g', so skipt 0th element.
            if (names.size() > 1)
            {
                name = names[1];
            }
            else
            {
                name = "";
            }
            
            continue;
        }
        
        // object name
        if (token[0] == 'o' && isSpace((token[1])))
        {
            // flush previous face group.
            shape_t shape;
            exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
            
            faceGroup.clear();
            
            // @todo { multiple object name? }
            char namebuf[4096];
            token += 2;
            sscanf(token, "%s", namebuf);
            name = std::string(namebuf);
            
            continue;
        }
        
        // Ignore unknown command.
    }
    
    shape_t shape;
    exportFaceGroupToShape(vertexCache, shapes, v, vn, vt, faceGroup, material, name);
    faceGroup.clear();  // for safety
    
    return err.str();
}

NS_CC_END

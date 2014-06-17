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

NS_CC_BEGIN

class Animation3D;
class Bundle3D
{
public:
    
    static Bundle3D* getInstance();
    
    static void destroyInstance();
    
    bool load(const std::string& path);
    
    /**
     * load mesh data from bundle
     * @param id The ID of the mesh, load the first Mesh in the bundle if it is empty
     */
    bool loadMeshData(const std::string& id, MeshData* meshdata);
    
    /**
     * load skin data from bundle
     * @param id The ID of the skin, load the first Skin in the bundle if it is empty
     */
    bool loadSkinData(const std::string& id, SkinData* skindata);
    
    /**
     * load material data from bundle
     * @param id The ID of the material, load the first Material in the bundle if it is empty
     */
    bool loadMaterialData(const std::string& id, MaterialData* materialdata);
    
    /**
     * load material data from bundle
     * @param id The ID of the animation, load the first animation in the bundle if it is empty
     */
    bool loadAnimationData(const std::string& id, Animation3DData* animationdata);
    
protected:
    GLenum parseGLType(const std::string& str);

    unsigned int parseGLTypeSize(const std::string& str);

    unsigned int parseGLProgramAttribute(const std::string& str);

    // get model path
    void getModelPath(const std::string& path);

CC_CONSTRUCTOR_ACCESS:
    Bundle3D();
    ~Bundle3D();
    
protected:
    
    static Bundle3D* _instance;
    
    std::string _modelRelativePath;

    char* _documentBuffer;
    std::string         _path;

    rapidjson::Document _document;

    bool  _isBinary;
};

NS_CC_END

#endif // __CCANIMATE3D_H__

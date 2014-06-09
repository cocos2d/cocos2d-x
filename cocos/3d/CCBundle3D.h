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

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"

#include "3d/CCMesh.h"

NS_CC_BEGIN

class Animation3D;

class Bundle3D
{
public:
    struct MeshData
    {
        float* vertex;
        int vertexSizeInFloat;
        unsigned short* indices;
        int numIndex;
        MeshVertexAttrib* attribs;
        int attribCount;
        void resetData();
        MeshData();
        ~MeshData();
    };
    struct SkinData
    {
        Mat4                     bindShape;
        std::vector<std::string> boneNames;
        std::vector<Mat4>        inverseBindPoseMatrices; //bind pose of bone
        
        std::map<int, std::vector<int> > boneChild;//key parent, value child
        int                              rootBoneIndex;
        void resetData()
        {
            bindShape.setIdentity();
            boneNames.clear();
            inverseBindPoseMatrices.clear();
            boneChild.clear();
            rootBoneIndex = -1;
        }
    };
    struct MaterialData
    {
        std::string texturePath;
    };
    struct Animation3DData
    {
        Animation3D* animation;
    };
    
    static Bundle3D* getInstance();
    
    static void purgeBundle3D();
    
    bool load(const std::string& path);
    
    //
    /**
     * load mesh data from bundle
     * @param id The ID of the mesh, load the first Mesh in the bundle if it is empty
     */
    bool loadMeshData(const std::string& id, MeshData* meshdata);
    
    //
    /**
     * load skin data from bundle
     * @param id The ID of the skin, load the first Skin in the bundle if it is empty
     */
    bool loadSkinData(const std::string& id, SkinData* skindata);
    
    //
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
    Bundle3D();
    ~Bundle3D();
    
    static Bundle3D* _instance;
    
    bool  _isBinary;
};

NS_CC_END

#endif // __CCANIMATE3D_H__

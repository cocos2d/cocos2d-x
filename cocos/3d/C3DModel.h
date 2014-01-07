#ifndef C3DMODEL_H_
#define C3DMODEL_H_

#include "C3DNode.h"
#include "cocos2d.h"

namespace cocos2d
{

class C3DResourceLoader;
class C3DMeshSkin;
class C3DModelNode;
class C3DMorph;
class C3DMaterial;
class C3DMesh;
class C3DLightFilter;
class C3DPass;
class C3DModel;


class C3DModel : public cocos2d::CCObject
{
    friend class C3DModelNode;
    friend class C3DMesh;
    friend class C3DResourceLoader;
    friend class C3DPostProcess;
    friend class ModelPartDrawItem;
public:

    C3DModel(C3DMesh* mesh);

    virtual ~C3DModel();

    static C3DModel* create(C3DMesh* mesh);

    C3DMesh* getMesh() const;

    unsigned int getMeshPartCount() const;

    C3DMaterial* getMaterial(int partIndex = -1);

    /**
     * Sets a material to be used for drawing this C3DModel.
     *
     * The specified C3DMaterial is applied for the MeshPart at the given index in
     * this Model's C3DMesh. A partIndex of -1 sets a shared C3DMaterial for
     * all mesh parts, whereas a value of 0 or greater sets the C3DMaterial for the
     * specified mesh part only.
     *
     * C3DMesh parts will use an explicitly set part material, if set; otherwise they
     * will use the globally set material.
     *
     * @param material The new material.
     * @param partIndex The index of the mesh part to set the material for (-1 for shared material).
     */
    void setMaterial(C3DMaterial* material, int partIndex = -1);


    C3DMaterial* setMaterial(const char* vshPath, const char* fshPath, const char* defines = NULL, int partIndex = -1);


    C3DMaterial* setMaterial(const char* materialPath, int partIndex = -1);

    void setDefaultMaterialName(const std::string& matName);
    C3DMaterial* setDefaultMaterial(const std::string& path,int partIndex = -1);

    /** 
    * remove material 
    * @param partIndex The index of the mesh part
    */
    bool removeMaterial(int partIndex = -1);

    bool hasMaterial(unsigned int partIndex) const;    

    C3DNode* getNode() const;

    /**
     * Draws this mesh instance.
     *
     * This method binds the vertex buffer and index buffers for the C3DMesh and
     * all of its MeshParts and draws the mesh geometry. Any other state
     * neccessary to render the C3DMesh, such as rendering states, shader state,
     * and so on, should be set up before calling this method.
     *
     */
    virtual void draw();

    

    C3DMorph* getMorph();
    
    
    void pushMorph(int morphTargetIndex,float weight);
    void popMorph(int morphTargetIndex);
    void changeMorph(int morphTargetIndex,float weight);
    
    

    /**
     * get or set light filter
     * subclass C3DLightFilter to determine wether light validate for this model 
     */
    static void setLightFilter(C3DLightFilter* lightFilter) { s_lightFilter = lightFilter; }
    static C3DLightFilter* getLightFilter() { return s_lightFilter; }
    
    virtual C3DModel* clone(C3DNode::CloneContext& context) const;

    void showWireframe(bool show){_wireframe = show;}

    void setNode(C3DNode* node);

protected:
    virtual void copyFrom(const C3DModel* other); 

    
    
    void applyShadowMap(C3DPass* pass);

    float distanceToCamera(void);

    void channelDrawPart( int partIndex );
private:    
    /**
     * Sets the specified materia's node binding to this model's node.
     */
    void setMaterialNodeBinding(C3DMaterial *m);

    void validatePartCount();

    unsigned int _partCount;
    C3DMaterial** _partMaterials;
    C3DNode* _node;   

    C3DMorph* _morph;
    
    static C3DLightFilter* s_lightFilter;

protected:    
    bool _wireframe;

public:
    
    C3DMesh* _mesh;
    C3DMaterial* _material;


    std::string _defaultMaterialName;
};

}

#endif

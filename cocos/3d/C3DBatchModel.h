#ifndef BATCHMODEL_H_
#define BATCHMODEL_H_

namespace cocos3d
{

class C3DMaterial;
class C3DBatchMesh;
class C3DNode;

/**
 * Defines a C3DBatchModel which contain a C3DBatchMesh and a material.
 */
class C3DBatchModel
{
   
    friend class C3DBatchMesh;

public:

	C3DBatchModel(C3DNode* node);

    virtual ~C3DBatchModel();

	static C3DBatchModel* createDebugModel(C3DNode* node);   

    C3DBatchMesh* getMesh() const;
	void setMesh(C3DBatchMesh* mesh);

    C3DMaterial* getMaterial();
	void setMaterialNodeBinding(C3DMaterial *material);
    void setMaterial(C3DMaterial* material);    

    void begin();

	void end();

	void draw();	 

private:
	C3DNode* _node;
public:
	C3DBatchMesh* _mesh;
    C3DMaterial* _material;
};


}

#endif

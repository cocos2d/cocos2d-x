#ifndef COMPOUNDMODEL_H_
#define COMPOUNDMODEL_H_

#include <map>
#include <string>
#include "EnumDef.h"

#include "C3DMatrix.h"
#include "C3DVector3.h"

#include "C3DNode.h"
#include "cocos2d.h"

#include "C3DOBB.h"
#include "C3DBone.h"

#include "C3DCollitionBox.h"
using namespace std;
namespace cocos3d
{


class C3DScene;
class C3DNode;
class C3DBatchMesh;
class C3DAABB;
class C3DMaterial;
class C3DRay;
class AttachNode;
class C3DResourceLoader;
/**
*Defines the bass class for all scene objects which includes static object,dynamic object,and so on.
*/
class  C3DRenderNode : public C3DNode
{
	friend class C3DScene; 
	friend class C3DStaticObj;	
	friend class C3DSprite;

public:
	
	C3DRenderNode(const char* id);

    ~C3DRenderNode();    

	// create sprite and add it to autorelease pool
    static C3DRenderNode* create(const char* id,const char* fileName);
	
	/**
    * load sprite from file. 
    *
    * @param fileName sprite filename.
    */
	virtual bool loadFromFile(const char* fileName,bool isLoadAll=false) = 0;
	virtual bool load(bool isLoadAll=false) = 0;
	/**
    * Render for handling rendering routines.   
    */
	virtual void draw();
	
	virtual void drawDebug();
	/**
     * Update routine
     */
    virtual void update(long elapsedTime);

	AttachNode * attachNode( const std::string & nodeName );
	void attach(const char* nodeName,C3DNode* attachment);
	void detach(const char* nodeName,C3DNode* attachment);

    // compute aabb
	virtual void calculateBoundingBox();
    // compute obb, init obb from aabb by default, may import obb from model or mesh latter
    virtual void calculateOrientedBoundingBox();
	
	// just comput aabb
	virtual void calculateBoundingBox_() = 0;

	// build obb from aabb
	virtual void calculateOrientedBoundingBox_();
	
	// recomput aabb 
	virtual void reCalculateBoundingBox();
	// recomput obb 
	virtual void reCalculateOrientedBoundingBox();

	void drawAABB();
    
    void drawOBB();

	void drawColitionBox(); 

	void transformChanged();

	C3DAABB* getAABB();
	void showAABB(bool show);
	bool showAABB();
	    
    C3DOBB* getOBB();
    void showOBB(bool show);
	bool showOBB();

	void showColitionBox(bool show);
	bool showColitionBox();

	void showWireFrame(bool _show);

	void showSkeleton(bool _show){ _showSkeleton = _show;}
	bool showSkeleton(){return _showSkeleton;}

	virtual C3DMaterial* getMaterial(const std::string& meshName);
	virtual void setMaterial(const std::string& modelName, const std::string& matName);
    virtual void setMaterial(const std::string& matName);

	void setDefaultMaterial(const std::string& path);

	virtual void removeMaterial(const std::string& modelName, const std::string& matName);
	virtual void removeMaterial(const std::string& matName);

	void getAllModel(std::list<C3DNode*>& models);

    unsigned int getTriangleCount() const;

	unsigned int addColitionBox(const std::string& strBone, const C3DVector3& offset = C3DVector3::zero(), float fRadius = 1.f);
	void removeColitionBox(C3DCollitionBox* bb);
	const std::vector<C3DCollitionBox*>& getColitionBoxs()const;
	C3DCollitionBox* pickColitionBox(const C3DRay *ray);
	bool saveColitionBox(const std::string& fileName)const;
	bool loadColitionBox(const std::string& fileName);



protected:
	
	virtual void copyFrom(const C3DTransform* other, C3DNode::CloneContext& context);

	AttachNode* accessNode( C3DNode* pNode);

protected:	
	int _changeFlag;	

	std::vector<AttachNode*> _attachNodes;
	
	C3DAABB* _bb;
    C3DAABB* _bbOrigin; // original bounding box
	
    C3DOBB _obb;
    C3DOBB _obbOrigin;// original obb

	std::vector<C3DCollitionBox*> m_colitionBoxs;// collision box list

    bool _showAABB;
	bool _showOBB;
    bool _showSkeleton;
	bool _showColitionBox;
    bool _castShadowMap;

	std::string _fileName;	
	C3DResourceLoader* _loader;

};


}

#endif

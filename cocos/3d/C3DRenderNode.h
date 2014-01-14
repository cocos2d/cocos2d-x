#ifndef COMPOUNDMODEL_H_
#define COMPOUNDMODEL_H_

#include <map>
#include <string>

#include "C3DMatrix.h"
#include "Vector3.h"

#include "C3DNode.h"
#include "cocos2d.h"

#include "C3DOBB.h"
#include "C3DBone.h"

using namespace std;

NS_CC_BEGIN

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

    /**
    * Render for handling rendering routines.   
    */
    virtual void draw();

    /**
    * Update routine
    */
    virtual void update(long elapsedTime);

    AttachNode * attachNode( const std::string & nodeName );
    void attach(const char* nodeName,C3DNode* attachment);
    void detach(const char* nodeName,C3DNode* attachment);


    void transformChanged();


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

protected:

    virtual void copyFrom(const Transform* other, C3DNode::CloneContext& context);

    AttachNode* accessNode( C3DNode* pNode);

protected:        

    std::vector<AttachNode*> _attachNodes;

    bool _showSkeleton;
    bool _showCollitionBox;
    bool _castShadowMap;

    std::string _fileName;    
};

NS_CC_END

#endif // COMPOUNDMODEL_H_

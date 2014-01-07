#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <list>
#include "C3DNode.h"
#include <vector>

NS_CC_BEGIN

class C3DCamera;
class C3DRenderNode;
class Vector3;
class RenderChannelManager;
class C3DLight;

class C3DSprite;
class C3DStaticObj;
class C3DBatchMesh;
class C3DParticleSystem;
class C3DShadowMap;
class C3DLayer;
class C3DPostProcess;
class C3DGeoWireRender;

class C3DOctree;


/**
*Defines the scene node,which includes all the scene object,for example,light,camera,sprite,and so on.
*/
class  C3DScene : public C3DNode
{
friend class C3DNode;
public:
    
    static C3DScene* createScene(C3DLayer* layer);
    
    void setLayer(C3DLayer* layer);
    C3DLayer* getLayer() const;

    C3DNode* findNode(const char* strId);
    
    void removeAllNode();
    
    
    C3DCamera* getActiveCamera() const;
    
    //set active camera by index
    bool setActiveCamera(int index);
    //get number of cameras in the scene
    int getCameraCount() const;
    
    

    
    /**
     *  set default depth, used when z is not provided during function call C3DNode::setScreenPos()
     */
    void setDefDepthZ(float defDepth)  { _defDepthZ = defDepth; }
    
    /**
     *  get default depth
     */
    float getDefDepthZ() { return _defDepthZ; }
    

    void setViewAspectRatio(float aspectRatio);

    const Vector3* getAmbientColor() const;

    void setAmbientColor(float red, float green, float blue);

    void draw();
    
    void drawDebug();
    void showBoundingBox(bool show);

        
    // update routine
    virtual void update(long elapsedTime);
    

    C3DScene(const char* strId = NULL);
    
    virtual ~C3DScene();
    
    //void EnalbeFrustumCull(bool bEnable, bool )
    
    virtual Type getType() const;
    
    const Matrix& getViewProjectionMatrix() const;
       

    bool isInShadowPass() const { return _inShadowPass; }
        
    
    virtual void addChild(C3DNode* child);

    virtual void removeChild(C3DNode* child);
    

    void addNodeToRenderList(C3DNode* node);
    void removeNodeFromRenderList(C3DNode* node);

protected:
    virtual void onChildChanged(ChangeEvent eventType, C3DNode* child);

private:
        
    Vector3* _ambientColor;    
   
    std::vector<C3DCamera*> _cameras;   
    
    std::vector<C3DNode*> _postDrawNode;

    bool _showBoundingBox;
       

    float _defDepthZ;//default depth z. 

    bool _inShadowPass;

    C3DCamera* _activeCamera;
        
    C3DLayer* _layer;    
    
    
};


NS_CC_END

#endif // SCENE_H_

#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <list>
#include "C3DNode.h"
#include <vector>



namespace cocos3d
{

class C3DCamera;
class C3DRenderNode;
class C3DVector3;
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
    
    
   // get light count
    int getLightCount() const { return (int)_lights.size(); }
    // get light by index
    C3DLight* getLight(int index);
    
    /**
     *  set default depth, used when z is not provided during function call C3DNode::setScreenPos()
     */
    void setDefDepthZ(float defDepth)  { _defDepthZ = defDepth; }
    
    /**
     *  get default depth
     */
    float getDefDepthZ() { return _defDepthZ; }
	

	void setViewAspectRatio(float aspectRatio);

	const C3DVector3* getAmbientColor() const;

    void setAmbientColor(float red, float green, float blue);

    void draw();
	void preDraw();
	void postDraw();
	void drawDebug();
	void showBoundingBox(bool show);

	// draw light position
	void showLight(bool show);
	void drawLights();

    //draw camera and light object
    void drawCameraAndLight();
    
    // update routine
    virtual void update(long elapsedTime);
    

    C3DScene(const char* strId = NULL);
    
    virtual ~C3DScene();
    
    //void EnalbeFrustumCull(bool bEnable, bool )
	
	virtual Type getType() const;
	
    const C3DMatrix& getViewProjectionMatrix() const;

    C3DShadowMap* getActiveShadowMap() const;
    C3DShadowMap* setActiveShadowMap(int index);
    int GetShadowMapCount() const;

    bool isInShadowPass() const { return _inShadowPass; }

	C3DPostProcess* getActivePostProcess() const;
    C3DPostProcess* setActivePostProcess(int index);

	C3DGeoWireRender* getGeoWireRender();

protected:
	void addNodeToRenderList(C3DNode* node);
	void removeNodeFromRenderList(C3DNode* node);
	virtual void onChildChanged(ChangeEvent eventType, C3DNode* child);

	
private:
	    
    C3DVector3* _ambientColor;
    
    std::vector<C3DLight*> _lights;
    std::vector<C3DCamera*> _cameras;
    std::vector<C3DShadowMap*> _shadowMaps;
	std::vector<C3DPostProcess*> _postProcesss;

	bool _showBoundingBox;
	bool _showLightPos;
	   

    float _defDepthZ;//default depth z. 

    bool _inShadowPass;

	C3DCamera* _activeCamera;
	
	C3DLight* _activeLight;

    C3DShadowMap* _activeShadowMap;

	C3DPostProcess* _activePostProcess;
    C3DLayer* _layer;	

	C3DGeoWireRender* _geoWireRender;
};


}

#endif

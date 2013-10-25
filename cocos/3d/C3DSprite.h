#ifndef C3DSprite_H_
#define C3DSprite_H_
#include <list>
#include <vector>
#include <map>
#include <string>
#include "EnumDef.h"

#include "C3DNode.h"

#include <string>
#include "cocos2d.h"
#include "C3DRenderNode.h"


namespace cocos3d
{	

class C3DVector2;
class C3DVector3;
class FacialAnimManager;
class C3DScene;
class AttachNode;
class C3DNode;
class C3DActionListener;
class C3DBatchMesh;

class C3DAnimation;
class C3DAnimationClip;
class C3DCamera;
class C3DMaterial;
class C3DScene;
class C3DNode;
class C3DSprite;
class C3DSkeleton;
class C3DBone;

class C3DActionListener;

/**
*Defines this dynamic object of the scene,which can play animation,change material.
*/
class  C3DSprite : public C3DRenderNode
{
	friend class C3DScene;
	friend class C3DResourceLoader;

public:

	C3DSprite(const char* id);

    ~C3DSprite(void);	

	C3DNode::Type getType() const;

	 // create sprite and add it to autorelease pool
    static C3DSprite* create(const char* id);

	virtual bool loadFromFile(const char* fileName,bool isLoadAll=false);	
	virtual bool load(bool isLoadAll=false);

	void loadNode(const std::string& nodeName);
	void loadNodes(std::list<std::string>* models);
	
	
	/**
    * Update for handling update routines.
    *    
    * @param elapsedTime The elapsed game time.
    */	
	void update(long elapsedTime);	
	
	/**
	* draw debug info
	*/
	virtual void drawDebug();
    
	/**
    * draw skeleton line.
    */
	void drawSkeleton();

	/**
    * load the model animation of the avatar.    
    */
	C3DAnimation* createAnimation();

	/**
    * create the facial anim of the avatar model.     
    */
	void createFacialAnim();

	/**
    * add clip info of anim. 
    *
    * @param name The clip name.
	* @param startFrame The startFrame.
	* @param endFrame The endFrame.
	* @param repeatCount The play counter.
	* @param speed The play speed.
    */
	C3DAnimationClip* addAnimationClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed);

	// for editor
	bool replaceAnimationClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed);

	/**
    * play this avatar model's action by the given name   
    *
    * @param animName The action name.
    */	
	void playAnimationClip(const char* name);
	void stopAnimationClip(const char* name);	 
    void pauseAnimationClip(const char* name);  
    void resumeAnimationClip(const char* name);    
    bool isAnimationClipPlaying(const char* name);
						
	bool loadMesh(const char* meshName);
					
		
	void calculateBoundingBox_();

	void setSkeleton(C3DBone* joint);

	// 获取跟骨骼 lvlong
	C3DBone* getSkeletonRootBone()const;

	// 根据名字获得骨骼 lvlong
	C3DBone* getBone(const char* name)const;
    
    C3DAnimationClip* getAnimationClip(const char* strClip);
    C3DAnimationClip* getCurAnimationClip();
    
    //unsigned int getTriangleCount() const;

	// 获取动画总帧数 lvlong
	int getAnimationFrameCount();

	virtual C3DNode* clone(CloneContext& context) const;

	void stopAllAnimationClip();

	
	FacialAnimManager* getFacialAnimManager();


protected:
	virtual void copyFrom(const C3DTransform* other, C3DNode::CloneContext& context);
		

private:	
	
	FacialAnimManager * _facialAnimManager;

	
		 	
	C3DSkeleton* _skeleton;
	C3DAnimation* _animation;
  

};


}

#endif

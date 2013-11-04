#ifndef NODE_H_
#define NODE_H_
#include "C3DMatrix.h"
#include "C3DTransform.h"
#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"


namespace cocos3d
{

	// C3DNode dirty flags
#define NODE_DIRTY_WORLD 1
#define NODE_DIRTY_BOUNDS 2
#define NODE_DIRTY_ALL (NODE_DIRTY_WORLD | NODE_DIRTY_BOUNDS)

class C3DScene;
class C3DAnimation;
class C3DLight;
class C3DModel;
class C3DCamera;
class C3DViewport;
class C3DMeshSkin;
class C3DPositionAxis;
class C3DScaleAxis;

/**
 * Defines a basic hierachial structure of transformation spaces.
 */
class C3DNode : public C3DTransform, public cocos2d::CCObject
{
	friend class C3DStaticObj;
	friend class C3DRenderNode;
    friend class C3DScene;   
    friend class C3DMeshSkin;
	friend class C3DSkeleton;
	friend class C3DParticleSystem;
    

public:
	C3DNode();
	C3DNode(const char* id);

    virtual ~C3DNode();

    /**
     * Defines the types of nodes.
     */
	enum Type
	{
		NodeType_Model = 1,
		NodeType_SuperModel = 2,
		NodeType_SceneModel = 3,
		NodeType_Camera = 4,
		NodeType_Light = 5,		
		NodeType_Bone = 6,		
		NodeType_Normal = 7,
		NodeType_ParticleSystem = 8,
        NodeType_ShadowMap = 9,
		NodeType_PostProcess = 10,
		NodeType_Scene = 100,
	};

	struct CloneContext
	{
		bool cloneChildren;											// clone all child nodes
		std::map<const C3DNode*, C3DNode*> cloneMap;				// record all cloned nodes to avoid duplicate clone
		std::string idSuffix;										// suffix to avoid id conflict
        std::map<const C3DAnimation*, C3DAnimation*> clonedAnim;     // cloned animation
        std::map<const C3DMeshSkin*, C3DMeshSkin*> clonedMeshSkin;   // cloned mesh skin
	};

    /**
     * Creates a new node with the specified ID.
     *
     * @param id The ID for the new node.
     */
    static C3DNode* create(const char* id = NULL);

	/**
     * Sets C3DScene.
     */
	void setScene(C3DScene* scene);

	/**
     * Gets C3DScene.
     */
	C3DScene* getScene();

    /**
     * Gets the identifier for the node.
     *
     * @return The node identifier.
     */
    const char* getId();

    /**
     * Sets the identifier for the node.
     *
     * @param id The identifier to set for the node.
     */
    void setId(const char* id);

    /**
     * Returns the type of the node.
     */
    virtual Type getType() const;

    /**
     * Adds a child node.
     *
     * @param child The child to add.
     */
    virtual void addChild(C3DNode* child);

    /**
     * Removes a child node.
     *
     * @param child The child to remove.
     */
    virtual void removeChild(C3DNode* child);

    /**
     * Removes all child nodes.
     */
    virtual void removeAllChildren();
    
    /**
     * Update routine
     */
    virtual void update(long elapsedTime);

	virtual void draw();

	/**
	* draw debug info, override this
	*/
	virtual void drawDebug(){}

	virtual unsigned int getTriangleCount() const;
 
    /**
     * Returns the parent of this node.
     *
     * @return The parent.
     */
    C3DNode* getParent();
	
	/**
     * Find the C3DNode by the specified id.
     */
    C3DNode* findNode(const char* id, bool recursive = true);

	/**
     * Gets root node.
     */
    C3DNode* getRootNode();

    /**
     * Gets the world matrix corresponding to this node.
     *
     * @return The world matrix of this node.
     */
    virtual const C3DMatrix& getWorldMatrix();

    /**
     * Gets the world view matrix corresponding to this node.
     *
     * @return The world view matrix of this node.
     */
    const C3DMatrix& getWorldViewMatrix();

    /**
     * Gets the inverse transpose world matrix corresponding to this node.
     *
     * This matrix is typically used to transform normal vectors into world space.
     *
     * @return The inverse world matrix of this node.
     */
    const C3DMatrix& getInverseTransposeWorldMatrix();

    /**
     * Gets the inverse transpose world view matrix corresponding to this node.
     *
     * This matrix is typically used to transform normal vectors into view space.
     *
     * @return The inverse world view matrix of this node.
     */
    const C3DMatrix& getInverseTransposeWorldViewMatrix();

    /**
     * Gets the view matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The view matrix of this node.
     */
    const C3DMatrix& getViewMatrix();

    /**
     * Gets the inverse view matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The inverse view matrix of this node.
     */
    const C3DMatrix& getInverseViewMatrix();

    /**
     * Gets the projection matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The projection matrix of this node.
     */
    const C3DMatrix& getProjectionMatrix();

    /**
     * Gets the view * projection matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The view * projection matrix of this node.
     */
    const C3DMatrix& getViewProjectionMatrix();

    /**
     * Gets the inverse view * projection matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The inverse view * projection matrix of this node.
     */
    const C3DMatrix& getInverseViewProjectionMatrix();

    /**
     * Gets the world * view * projection matrix corresponding to this node based
     * on the scene's active camera.
     *
     * @return The world * view * projection matrix of this node.
     */
    const C3DMatrix& getWorldViewProjectionMatrix();

    /**
     * Gets the translation vector (or position) of this C3DNode in world space.
     *
     * @return The world translation vector.
     */
    C3DVector3 getTranslationWorld();

    /**
     * Gets the translation vector (or position) of this C3DNode in view space.
     *
     * @return The view space translation vector.
     */
    C3DVector3 getTranslationView();

    /**
     * Returns the forward vector of the C3DNode in world space.
     */
    C3DVector3 getRightVectorWorld();

    /**
     *  Returns the forward vector of the C3DNode in view space.
     */
    C3DVector3 getRightVectorView();

	    /**
     * Returns the up vector of the C3DNode in world space.
     */
    C3DVector3 getUpVectorWorld();

    /**
     *  Returns the up vector of the C3DNode in view space.
     */
    C3DVector3 getUpVectorView();

	    /**
     * Returns the forward vector of the C3DNode in world space.
     */
    C3DVector3 getForwardVectorWorld();

    /**
     *  Returns the forward vector of the C3DNode in view space.
     */
    C3DVector3 getForwardVectorView();

    void setForwardVectorWorld(C3DVector3& forwardVector);

    /**
     * Returns the translation vector of the currently active camera for this node's scene.
     *
     * @return The translation vector of the scene's active camera.
     */
    const C3DVector3& getActiveCameraTranslationWorld();

    /**
     * Returns the view-space translation vector of the currently active camera for this node's scene.
     *
     * @return The translation vector of the scene's active camera, in view-space.
     */
    const C3DVector3& getActiveCameraTranslationView();	

    /**
     * Called when this Node's transform changes.
     */
    void transformChanged();

    /**
     * Called when this Node's hierarchy changes.
     */
    void hierarchyChanged();

    /**
     * Marks the bounding volume of the node as dirty.
     */
    void setBoundsDirty();

    /**
     *  Set screen position, screen coordinate(x, y)
     *  depth 0-1, 0 near plane, 1 far plane
     *  
     */
    void setScreenPos(int x, int y, float depthZ);
    
    /**
     *  Set screen position, screen coordinate(x, y)
     *  use default depthZ of scene
     *
     */
    void setScreenPos(int x, int y);

	/**
     *  Set active
     */
	virtual void active(bool active);

	/**
     *  Checks active
     */
	virtual bool active();
	
	/**
     *  Gets child list
     */
	std::vector< C3DNode * >& getChildrenList(){return _children;}

	/**
	 * clone this node
	 * @return New node
	 */
	virtual C3DNode* clone(CloneContext& context) const;
	
	/**
	 * clone this node
	 * @return New node
	 */
    C3DNode* clone(const char* idSuffix) const;	

	void showPosAxis(bool show);
	bool showPosAxis();

	void showScaleAxis(bool show);
	bool showScaleAxis();

	C3DPositionAxis* getPositionAxis(){return m_pPositionAxis;}
	C3DScaleAxis* getScaleAxis(){return m_pScaleAxis;}

	void setParent(C3DNode* parent)
	{
		_parent = parent;
	}

protected:
	/**
	 * clone from other
	 */
	virtual void copyFrom(const C3DTransform* other, CloneContext& context);
	
	/**
	 * Change event type
	 */
	enum ChangeEvent
	{
		ADD, REMOVE
	};

	/**
	 * notify when child node changed
	 * @return New node
	 */
	virtual void onChildChanged(ChangeEvent eventType, C3DNode* child);

	
protected:
    C3DScene* _scene;

    std::string _id;

    C3DNode* _parent;

	std::vector< C3DNode * >  _children;  // Child nodes	
		        
    /**
     * World C3DMatrix representation of the C3DNode.
     */
    mutable C3DMatrix _world;

    /**
     * Dirty bits flag for the C3DNode.
     */
    mutable int _dirtyBits;
    
    /**
     * A flag indicating if the Node's hierarchy has changed.
     */ 
    bool _notifyHierarchyChanged;
	bool _active;

	bool _showPosAxis;
	bool _showScaleAxis;
	C3DPositionAxis* m_pPositionAxis;
	C3DScaleAxis* m_pScaleAxis;

	
};


}

#endif

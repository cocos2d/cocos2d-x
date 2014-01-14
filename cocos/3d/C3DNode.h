#ifndef NODE_H_
#define NODE_H_
#include "C3DMatrix.h"
#include "Transform.h"
#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "C3DOBB.h"
#include "C3DAABB.h"

NS_CC_BEGIN

// TODO: replace below macro to class's const static member.
// C3DNode dirty flags
#define NODE_DIRTY_WORLD 1
#define NODE_DIRTY_BOUNDS_AABB 2
#define NODE_DIRTY_BOUNDS_OBB 4
#define NODE_DIRTY_ALL (NODE_DIRTY_WORLD | NODE_DIRTY_BOUNDS_AABB | NODE_DIRTY_BOUNDS_OBB)

class C3DScene;
class C3DAnimation;
class C3DLight;
class C3DModel;
class C3DCamera;
class C3DViewport;
class C3DMeshSkin;
class C3DAABB;
class C3DOBB;

// TODO: It is better not use multiple inheritance, use composition instead.
/**
* Defines a basic hierachial structure of transformation spaces.
*/
class C3DNode : public Transform, public virtual cocos2d::CCObject
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
    * Listener interface for Transform events.
    */
    class  Listener
    {
    public:

        virtual ~Listener() { }

        /**
        * Handles when an transform has changed.
        *
        * @param transform The Transform object that was changed.
        * @param cookie Cookie value that was specified when the listener was registered.
        */
        virtual void transformChanged(Transform* transform) = 0;
    };

    // TODO: Use enum class instead later
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
        NodeType_EditorNode = 101
    };

    struct CloneContext
    {
        bool cloneChildren;                                          // clone all child nodes
        std::map<const C3DNode*, C3DNode*> cloneMap;                 // record all cloned nodes to avoid duplicate clone
        std::string idSuffix;                                        // suffix to avoid id conflict
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
    * Adds a transform listener.
    *
    * @param listener The listener to add.
    * @param cookie An optional long value that is passed to the specified listener when it is called.
    */
    void addListener(C3DNode::Listener* listener);

    /**
    * Removes a transform listener.
    */
    void removeListener(C3DNode::Listener* listener);

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
    virtual void drawDebug();

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
    virtual const Matrix& getWorldMatrix();

    /**
    * Gets the world view matrix corresponding to this node.
    *
    * @return The world view matrix of this node.
    */
    const Matrix& getWorldViewMatrix();

    /**
    * Gets the inverse transpose world matrix corresponding to this node.
    *
    * This matrix is typically used to transform normal vectors into world space.
    *
    * @return The inverse world matrix of this node.
    */
    const Matrix& getInverseTransposeWorldMatrix();

    /**
    * Gets the inverse transpose world view matrix corresponding to this node.
    *
    * This matrix is typically used to transform normal vectors into view space.
    *
    * @return The inverse world view matrix of this node.
    */
    const Matrix& getInverseTransposeWorldViewMatrix();

    /**
    * Gets the view matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The view matrix of this node.
    */
    const Matrix& getViewMatrix();

    /**
    * Gets the inverse view matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The inverse view matrix of this node.
    */
    const Matrix& getInverseViewMatrix();

    /**
    * Gets the projection matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The projection matrix of this node.
    */
    const Matrix& getProjectionMatrix();

    /**
    * Gets the view * projection matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The view * projection matrix of this node.
    */
    const Matrix& getViewProjectionMatrix();

    /**
    * Gets the inverse view * projection matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The inverse view * projection matrix of this node.
    */
    const Matrix& getInverseViewProjectionMatrix();

    /**
    * Gets the world * view * projection matrix corresponding to this node based
    * on the scene's active camera.
    *
    * @return The world * view * projection matrix of this node.
    */
    const Matrix& getWorldViewProjectionMatrix();

    /**
    * Gets the translation vector (or position) of this C3DNode in world space.
    *
    * @return The world translation vector.
    */
    Vector3 getTranslationWorld();

    /**
    * Gets the translation vector (or position) of this C3DNode in view space.
    *
    * @return The view space translation vector.
    */
    Vector3 getTranslationView();

    const Quaternion getRotationWorld();

    /**
    * Returns the forward vector of the C3DNode in world space.
    */
    Vector3 getRightVectorWorld();

    /**
    *  Returns the forward vector of the C3DNode in view space.
    */
    Vector3 getRightVectorView();

    /**
    * Returns the up vector of the C3DNode in world space.
    */
    Vector3 getUpVectorWorld();

    /**
    *  Returns the up vector of the C3DNode in view space.
    */
    Vector3 getUpVectorView();

    /**
    * Returns the forward vector of the C3DNode in world space.
    */
    Vector3 getForwardVectorWorld();

    /**
    *  Returns the forward vector of the C3DNode in view space.
    */
    Vector3 getForwardVectorView();

    void setForwardVectorWorld(    Vector3& forwardVector);

    /**
    * Returns the translation vector of the currently active camera for this node's scene.
    *
    * @return The translation vector of the scene's active camera.
    */
    const     Vector3& getActiveCameraTranslationWorld();

    /**
    * Returns the view-space translation vector of the currently active camera for this node's scene.
    *
    * @return The translation vector of the scene's active camera, in view-space.
    */
    const     Vector3& getActiveCameraTranslationView();    

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

    // compute aabb
    virtual void calculateBoundingBox();
    // compute obb, init obb from aabb by default, may import obb from model or mesh latter
    virtual void calculateOrientedBoundingBox();

    // just comput aabb
    virtual void calculateBoundingBox_();

    // build obb from aabb
    virtual void calculateOrientedBoundingBox_();

    virtual C3DAABB* getAABB();



    void setParent(C3DNode* parent)
    {
        _parent = parent;
    }


protected:
    /**
    * clone from other
    */
    virtual void copyFrom(const Transform* other, CloneContext& context);

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
    * List of TransformListener's on the Transform.
    */
    std::list<Listener*>* _listeners;

    /**
    * World Matrix representation of the C3DNode.
    */
    mutable Matrix _world;

    /**
    * Dirty bits flag for the C3DNode.
    */
    mutable int _dirtyBits;

    /**
    * A flag indicating if the Node's hierarchy has changed.
    */ 
    bool _notifyHierarchyChanged;
    bool _active;

    C3DAABB* _bb;
    C3DAABB* _bbOrigin; // original bounding box

    C3DOBB _obb;
    C3DOBB _obbOrigin;// original obb

    bool _showAABB;
    bool _showOBB;
};


NS_CC_END

#endif // NODE_H_

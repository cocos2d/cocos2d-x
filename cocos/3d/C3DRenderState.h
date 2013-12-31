#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include "Base.h"

#include "cocos2d.h"
#include "C3DRenderBlock.h"

NS_CC_BEGIN

// Render state override bits
enum
{
	RS_BLEND = 1,
	RS_BLEND_FUNC = 2,
	RS_CULL_FACE = 4,
	RS_DEPTH_TEST = 8,
	RS_DEPTH_WRITE = 16
};

class C3DNode;
class C3DPass;

/**
* Defines the render state of the graphics device.
*/
class MaterialParameter;
class C3DElementNode;
class C3DStateBlock;

/**
* Defines a renderState for an model to be rendered.
*
* This class includes all the parameters to apply a shader at runtime.
*/
class C3DRenderState : virtual public cocos2d::CCObject
{
	friend class C3DRenderSystem;
	friend class C3DMaterial;
	friend class C3DTechnique;
	friend class C3DPass;
	friend class C3DModel;
	friend class C3DBatchModel;
	friend class C3DParticleRender;

public:

	/**
	* Built-in auto-bind targets for material parameters.
	*/
	enum AutoBinding
	{
		NONE = 0,

		/**
		* Binds a node's World matrix.
		*/
		WORLD_MATRIX,

		/**
		* Binds the View matrix of the active camera for the node's scene.
		*/
		VIEW_MATRIX,

		/**
		* Binds the Projection matrix of the active camera for the node's scene.
		*/
		PROJECTION_MATRIX,

		/**
		* Binds a node's WorldView matrix.
		*/
		WORLD_VIEW_MATRIX,

		/**
		* Binds the ViewProjection matrix of the active camera for the node's scene.
		*/
		VIEW_PROJECTION_MATRIX,

		/**
		* Binds a node's WorldViewProjection matrix.
		*/
		WORLD_VIEW_PROJECTION_MATRIX,

		/**
		* Binds a node's InverseTransposeWorl matrix.
		*/
		INVERSE_TRANSPOSE_WORLD_MATRIX,

		/**
		* Binds a node's InverseTransposeWorldView matrix.
		*/
		INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX,

		/**
		* Binds the position (C3DVector3) of the active camera for the node's scene.
		*/
		CAMERA_WORLD_POSITION,

		/**
		* Binds the view-space position (C3DVector3) of the active camera for the node's scene.
		*/
		CAMERA_VIEW_POSITION,

		/**
		* Binds the matrix palette of C3DMeshSkin attached to a node's model.
		*/
		MATRIX_PALETTE,


		// Number of auto-binding types
		AUTO_BINDING_NUM
	};


	MaterialParameter* getParameter(const char* name) const;

	MaterialParameter* findParameter(const char* name, bool findParent) const;

	const std::list<MaterialParameter*>& getParameterList()const{return _parameters;}
	/**
	* Sets a material parameter auto-binding.
	*
	* @param name The name of the material parameter to store an auto-binding for.
	* @param autoBinding A valid AutoBinding value.
	*/
	void setParameterAutoBinding(const char* name, AutoBinding autoBinding);

	/**
	* Sets a material parameter auto-binding.
	*
	* This method parses the passed in autoBinding string and attempts to convert it
	* to an AutoBinding enumeration value, which is then stored in this render state.
	*
	* @param name The name of the material parameter to store an auto-binding for.
	* @param autoBinding A string matching one of the built-in AutoBinding enum constants.
	*/
	void setParameterAutoBinding(const char* name, const char* autoBinding);

	/**
	* Sets the fixed-function render state of this object to the state contained
	* in the specified StateBlock.
	*
	* The passed in StateBlock is stored in this C3DRenderState object with an 
	* increased reference count and released when either a different StateBlock
	* is assigned, or when this C3DRenderState object is destroyed.
	*
	* @param state The state block to set.
	*/
	void setStateBlock(C3DStateBlock* state);

	/**
	* Gets the fixed-function StateBlock for this C3DRenderState object.
	*
	* The returned StateBlock is referenced by this C3DRenderState and therefore
	* should not be released by the user. To release a StateBlock for a
	* C3DRenderState, the setState(StateBlock*) method should be called, passing
	* nullptr. This removes the StateBlock and resets the fixed-function render
	* state to the default state.
	*
	* It is legal to pass the returned StateBlock to another C3DRenderState object.
	* In this case, the StateBlock will be referenced by both C3DRenderState objects
	* and any changes to the StateBlock will be refelcted in all objects
	* that reference it.
	*
	* @return The StateBlock for this C3DRenderState.
	*/
	C3DStateBlock* getStateBlock() const;

	virtual void copyFrom(const C3DRenderState* other);

	static void activeTexture(GLenum textrue);

	AutoBinding getAutoBinding(const char* name) const;
	static const char* getAutoBindingVariable(AutoBinding b);
	static AutoBinding getAutoBindingOfVariable(const char* name);

	/**
	* load info from the elementnode
	*
	* @param nodes elementnode which contains the renderstate info.	 
	*      
	*/
	virtual bool load(C3DElementNode* nodes);

	/**
	* save the renderstate info into the elementnode
	*
	* @param nodes elementnode which contains the renderstate info.	 
	*      
	*/
	virtual bool save(C3DElementNode* node);

	static const char* getAutoBindingName(AutoBinding autoBinding);

	C3DRenderState* getParent();

protected:

	/**
	* Constructor.
	*/
	C3DRenderState();

	/**
	* Destructor.
	*/
	virtual ~C3DRenderState();

	/**
	* Sets the node that this render state is bound to.
	*
	* The specified node is used to apply auto-bindings for the render state.
	* This is typically set to the node of the model that a material is 
	* applied to.
	*
	* @param node The node to use for applying auto-bindings.
	*/
	void setNodeAutoBinding(C3DNode* node);

	/**
	* Applies the specified auto-binding.
	*/
	void applyNodeAutoBinding(const char* uniformName, AutoBinding binding);

	/**
	* Binds the render state for this C3DRenderState and any of its parents, top-down, 
	* for the given pass.
	*/
	void bind(C3DPass* pass);

	void setParamMethonAutoUniform(C3DPass* pass);

	/**
	* Returns the topmost C3DRenderState in the hierarchy below the given C3DRenderState.
	*/
	C3DRenderState* getTopmost(C3DRenderState* below);

private:

	/**
	* Hidden copy constructor.
	*/
	C3DRenderState(const C3DRenderState& copy);

	/**
	* Hidden copy assignment operator.
	*/
	C3DRenderState& operator=(const C3DRenderState&);
protected:

	/**
	* Collection of MaterialParameter's to be applied to the gamplay::C3DEffect.
	*/
	mutable std::list<MaterialParameter*> _parameters;

	/**
	* Map of IDs to AutoBindings.
	*/
	std::map<std::string, AutoBinding> _autoBindings;

	/**
	* The C3DNode bound to the C3DRenderState.
	*/
	C3DNode* _nodeBinding;

	/**
	* The StateBlock of fixed-function render states that can be applied to the C3DRenderState.
	*/
	mutable C3DStateBlock* _stateBlock;

	/**
	* The RenderState's parent.
	*/
	C3DRenderState* _parent;

	static GLint _activeTexture;// GL_TEXTURE0....
};

NS_CC_END


#endif // RENDERSTATE_H_

# ifndef MATERIAL_H_
# define MATERIAL_H_

#include "C3DRenderState.h"
#include "C3DResource.h"

NS_CC_BEGIN

class ElementNode;
class C3DTechnique;
class C3DEffect;

/**
* Defines a material for an model to be rendered.
*
* one material contains several techniques for render an model.
* when multiple techniques are loaded using a material file,
* the current technique can be set at runtime.
*/
class C3DMaterial : public C3DRenderState,public C3DResource
{
	friend class C3DTechnique;
	friend class C3DPass;
	friend class C3DRenderState;
	friend class C3DNode;

public:
	enum TechniqueUsage
	{
		// render to screen
		TECH_USAGE_SCREEN,
		// render depth to shadow map
		TECH_USAGE_SHADOWMAP,

		// Number of this enumeration
		TECH_USAGE_NUM,
	};

public:

	C3DMaterial(const std::string& name);

	virtual ~C3DMaterial();	

	/**
	* create a material from the file.
	*
	* @param vshSource The vertex shader source code.
	* @param fshSource The fragment shader source code.
	* @param defines A new-line delimited list of preprocessor defines. May be nullptr.
	* 
	* @return The created material.
	*/
	static C3DMaterial* create(const char* fileName);


	/**
	* create a material from the material info of an elementnode.
	*
	* @param materialNodes the elementnode which contain the material info
	* 
	* @return The created material.
	*/
	static C3DMaterial* create(ElementNode* materialNodes);

	/**
	* create a material from the given vertex and fragment shader source code.
	*
	* @param vshSource The vertex shader source code.
	* @param fshSource The fragment shader source code.
	* @param defines A new-line delimited list of preprocessor defines. May be nullptr.
	* 
	* @return The created material.
	*/
	static C3DMaterial* create(const char* vshPath, const char* fshPath, const char* defines = nullptr);

	//  static C3DMaterial* create(C3DEffect* effect);

	unsigned int getTechniqueCount() const;

	/**
	* get the specified technique.
	*
	* @param index the index of the specified technqiue.
	* 
	* @return The created material.
	*/
	C3DTechnique* getTechnique(unsigned int index) const;

	C3DTechnique* getTechnique(const char* id) const;

	C3DTechnique* getTechnique(TechniqueUsage usage) const;

	C3DTechnique* getTechnique() const;

	/**
	* set the specified technique to specified technique channel.
	*
	* @param usage the usage of the specified technique channel.
	* @param index the index of the specified technqiue.
	* 
	* @return The created material.
	*/
	bool setTechnique(TechniqueUsage usage, unsigned int index);

	bool setTechnique(TechniqueUsage usage, const char* id);


	/**
	* clone a material from current material.
	*/
	virtual C3DMaterial* clone() const;

	//virtual void copyFrom(const C3DResource* other);

	/**
	* load info from the elementnode
	*
	* @param nodes elementnode which contains the renderstate info.	 
	*      
	*/
	virtual bool load(ElementNode* nodes);

	/**
	* save the material info into the elementnode
	*
	* @param nodes elementnode which contains the renderstate info.	 
	*      
	*/
	virtual bool save(ElementNode* nodes);

private:

	std::vector<C3DTechnique*> _techniques;

	C3DTechnique* _techniqueChannel[TECH_USAGE_NUM];
};

NS_CC_END

#endif // MATERIAL_H_

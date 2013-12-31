#include "Base.h"
#include "C3DRenderState.h"
#include "C3DNode.h"
#include "C3DPass.h"
#include "C3DTechnique.h"
#include "C3DNode.h"
#include "MaterialParameter.h"
#include "C3DMeshSkin.h"
#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DSkinModel.h"
#include "C3DElementNode.h"
#include "EnumDef_GL.h"
#include "C3DSampler.h"

NS_CC_BEGIN

static bool isMaterialKeyword(const char* str)
{
#define MATERIAL_KEYWORD_COUNT 3
	static const char* reservedKeywords[MATERIAL_KEYWORD_COUNT] =
	{
		"vertexShader",
		"fragmentShader",
		"defines"
	};
	for (unsigned int i = 0; i < MATERIAL_KEYWORD_COUNT; ++i)
	{
		if (strcmp(reservedKeywords[i], str) == 0)
		{
			return true;
		}
	}
	return false;
}


static const char* AUTO_BINDING_VARIABLES[C3DRenderState::AUTO_BINDING_NUM] =
{
	"",

	"u_worldMatrix",

	"u_viewMatrix",

	"u_projectionMatrix",

	"u_worldViewMatrix",

	"u_viewProjectionMatrix",

	"u_worldViewProjectionMatrix",

	"u_inverseTransposeWorldMatrix",

	"u_inverseTransposeWorldViewMatrix",

	"u_cameraWorldPosition",

	"u_cameraViewPosition",

	"u_matrixPalette",

};

GLint C3DRenderState::_activeTexture = 0;

C3DRenderState::C3DRenderState()
	: _nodeBinding(nullptr), _stateBlock(nullptr), _parent(nullptr)
{
}

C3DRenderState::~C3DRenderState()
{
	SAFE_RELEASE(_stateBlock);

	// Destroy all the material parameters
	for (std::list<MaterialParameter*>::iterator iter = _parameters.begin();iter != _parameters.end();++iter)
		// for (unsigned int i = 0, count = _parameters.size(); i < count; ++i)
	{
		MaterialParameter* parameter = *iter;
		if (parameter)
		{
			SAFE_RELEASE(parameter);
		}
	}
	_parameters.clear();
}


MaterialParameter* C3DRenderState::getParameter(const char* name) const
{
	assert(name);

	MaterialParameter* param = findParameter(name, false);
	if (param)
		return param;

	// Create a new parameter and store it in our list
	param = new MaterialParameter(name);
	_parameters.push_back(param);

	return param;
}

void C3DRenderState::setParameterAutoBinding(const char* name, AutoBinding autoBinding)
{
	// Store the auto-binding
	if (autoBinding == NONE)
	{
		// Clear current auto binding
		std::map<std::string, AutoBinding>::iterator itr = _autoBindings.find(name);
		if (itr != _autoBindings.end())
		{
			_autoBindings.erase(itr);
		}
	}
	else
	{
		// Set new auto binding
		_autoBindings[name] = autoBinding;
	}

	// If we have a currently set node binding, apply the auto binding immediately
	if (_nodeBinding)
	{
		applyNodeAutoBinding(name, autoBinding);
	}
}

void C3DRenderState::setParameterAutoBinding(const char* name, const char* autoBinding)
{
	AutoBinding value = NONE;

	// Parse the passed in autoBinding string
	if (strcmp(autoBinding, "WORLD_MATRIX") == 0)
	{
		value = WORLD_MATRIX;
	}
	else if (strcmp(autoBinding, "VIEW_MATRIX") == 0)
	{
		value = VIEW_MATRIX;
	}
	else if (strcmp(autoBinding, "PROJECTION_MATRIX") == 0)
	{
		value = PROJECTION_MATRIX;
	}
	else if (strcmp(autoBinding, "WORLD_VIEW_MATRIX") == 0)
	{
		value = WORLD_VIEW_MATRIX;
	}
	else if (strcmp(autoBinding, "VIEW_PROJECTION_MATRIX") == 0)
	{
		value = VIEW_PROJECTION_MATRIX;
	}
	else if (strcmp(autoBinding, "WORLD_VIEW_PROJECTION_MATRIX") == 0)
	{
		value = WORLD_VIEW_PROJECTION_MATRIX;
	}
	else if (strcmp(autoBinding, "INVERSE_TRANSPOSE_WORLD_MATRIX") == 0)
	{
		value = INVERSE_TRANSPOSE_WORLD_MATRIX;
	}
	else if (strcmp(autoBinding, "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX") == 0)
	{
		value = INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX;
	}
	else if (strcmp(autoBinding, "CAMERA_WORLD_POSITION") == 0)
	{
		value = CAMERA_WORLD_POSITION;
	}
	else if (strcmp(autoBinding, "CAMERA_VIEW_POSITION") == 0)
	{
		value = CAMERA_VIEW_POSITION;
	}
	else if (strcmp(autoBinding, "MATRIX_PALETTE") == 0)
	{
		value = MATRIX_PALETTE;
	}

	if (value != NONE)
	{
		setParameterAutoBinding(name, value);
	}
}

void C3DRenderState::setStateBlock(C3DStateBlock* state)
{
	if (_stateBlock != state)
	{
		SAFE_RELEASE(_stateBlock);

		_stateBlock = state;

		if (_stateBlock)
		{
			_stateBlock->retain();
		}
	}
}

C3DStateBlock* C3DRenderState::getStateBlock() const
{
	if (_stateBlock == nullptr)
	{
		_stateBlock = C3DStateBlock::create();
	}

	return _stateBlock;
}

void C3DRenderState::setNodeAutoBinding(C3DNode* node)
{
	_nodeBinding = node;

	if (_nodeBinding)
	{
		// Apply all existing auto-bindings using this node
		std::map<std::string, AutoBinding>::const_iterator itr = _autoBindings.begin();
		while (itr != _autoBindings.end())
		{
			applyNodeAutoBinding(itr->first.c_str(), itr->second);
			itr++;
		}
	}
}

void C3DRenderState::applyNodeAutoBinding(const char* uniformName, AutoBinding autoBinding)
{
	switch (autoBinding)
	{
	case WORLD_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getWorldMatrix);
		break;

	case VIEW_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getViewMatrix);
		break;

	case PROJECTION_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getProjectionMatrix);
		break;

	case WORLD_VIEW_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getWorldViewMatrix);
		break;

	case VIEW_PROJECTION_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getViewProjectionMatrix);
		break;

	case WORLD_VIEW_PROJECTION_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getWorldViewProjectionMatrix);
		break;

	case INVERSE_TRANSPOSE_WORLD_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getInverseTransposeWorldMatrix);
		break;

	case INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getInverseTransposeWorldViewMatrix);
		break;

	case CAMERA_WORLD_POSITION:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getActiveCameraTranslationWorld);
		break;

	case CAMERA_VIEW_POSITION:
		getParameter(uniformName)->setValue(_nodeBinding, &C3DNode::getActiveCameraTranslationView);
		break;

	case MATRIX_PALETTE:
		{

			C3DSkinModel* model =  static_cast<C3DSkinModel*>(static_cast<C3DModelNode*>(_nodeBinding)->getModel());
			C3DMeshSkin* skin = model ? model->getSkin() : nullptr;
			if (skin)
			{
				getParameter(uniformName)->setValue(skin, &C3DMeshSkin::getMatrixPalette, &C3DMeshSkin::getMatrixPaletteSize, &C3DMeshSkin::getBonePartIndex);
			}
		}
		break;
	}
}

const char* C3DRenderState::getAutoBindingName(AutoBinding autoBinding)
{
	switch (autoBinding)
	{
	case WORLD_MATRIX:
		return "WORLD_MATRIX";

	case VIEW_MATRIX:
		return "VIEW_MATRIX";

	case PROJECTION_MATRIX:
		return "PROJECTION_MATRIX";

	case WORLD_VIEW_MATRIX:
		return "WORLD_VIEW_MATRIX";

	case VIEW_PROJECTION_MATRIX:
		return "VIEW_PROJECTION_MATRIX";

	case WORLD_VIEW_PROJECTION_MATRIX:
		return "WORLD_VIEW_PROJECTION_MATRIX";

	case INVERSE_TRANSPOSE_WORLD_MATRIX:
		return "INVERSE_TRANSPOSE_WORLD_MATRIX";

	case INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX:
		return "INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX";

	case CAMERA_WORLD_POSITION:
		return "CAMERA_WORLD_POSITION";

	case CAMERA_VIEW_POSITION:
		return "CAMERA_VIEW_POSITION";

	case MATRIX_PALETTE:
		return "MATRIX_PALETTE";
	default:
		CCAssert(false, "Unknown auto binding type");
	}

	return "";
}


void C3DRenderState::bind(C3DPass* pass)
{
	// Get the combined modified state bits for our C3DRenderState hierarchy.
	long stateOverrideBits = _stateBlock ? _stateBlock->_bits : 0;
	C3DRenderState* rs = _parent;
	while (rs)
	{
		if (rs->_stateBlock)
		{
			stateOverrideBits |= rs->_stateBlock->_bits;
		}
		rs = rs->_parent;
	}

	// Restore renderer state to its default, except for explicitly specified states
	C3DStateBlock::restore(stateOverrideBits);

	// Apply parameter bindings and renderer state for the entire hierarchy, top-down.
	rs = nullptr;
	C3DEffect* effect = pass->getEffect();
	while (rs = getTopmost(rs))
	{
		for (std::list<MaterialParameter*>::iterator iter = rs->_parameters.begin();iter != rs->_parameters.end();++iter)
		{
			(*iter)->bind(effect);
		}
		/* for (unsigned int i = 0, count = rs->_parameters.size(); i < count; ++i)
		{
		rs->_parameters[i]->bind(effect);
		}*/

		if (rs->_stateBlock)
		{
			rs->_stateBlock->bindNoRestore();
		}
	}
}

void C3DRenderState::setParamMethonAutoUniform(C3DPass* pass)
{
	C3DRenderState* rs = nullptr;
	C3DEffect* effect = pass->getEffect();
	while (rs = getTopmost(rs))
	{
		for (std::list<MaterialParameter*>::iterator iter = rs->_parameters.begin();iter != rs->_parameters.end();++iter)
			// for (unsigned int i = 0, count = rs->_parameters.size(); i < count; ++i)
		{
			(*iter)->setParamMethonAutoUniform(effect);
		}


	}

}

C3DRenderState* C3DRenderState::getTopmost(C3DRenderState* below)
{
	C3DRenderState* rs = this;
	if (rs == below)
	{
		// Nothing below ourself
		return nullptr;
	}

	while (rs)
	{
		if (rs->_parent == below || rs->_parent == nullptr)
		{
			// Stop traversing up here
			return rs;
		}
		rs = rs->_parent;
	}

	return nullptr;
}


void C3DRenderState::activeTexture(GLenum textrue)
{
	if (_activeTexture != textrue)
	{
		GL_ASSERT(glActiveTexture(textrue));
		_activeTexture = textrue;
	}
}

void C3DRenderState::copyFrom(const C3DRenderState* other)
{
	_nodeBinding = other->_nodeBinding;
	SAFE_RELEASE(_stateBlock);
	if (other->_stateBlock)
	{
		_stateBlock = new C3DStateBlock(*other->_stateBlock);
	}

	_parameters.clear();
	for (std::list<MaterialParameter*>::iterator iter = other->_parameters.begin();iter != other->_parameters.end();++iter)
		//for (size_t i = 0; i < other->_parameters.size(); i++)
	{
		_parameters.push_back((*iter)->clone());
	}

	_autoBindings = other->_autoBindings;
}

MaterialParameter* C3DRenderState::findParameter(const char* name, bool findParent) const
{
	MaterialParameter* param;

	// Search for an existing parameter with this name
	for (std::list<MaterialParameter*>::iterator iter = _parameters.begin();iter != _parameters.end();++iter)
		//for (unsigned int i = 0, count = _parameters.size(); i < count; ++i)
	{
		param = *iter;
		if (strcmp(param->getName(), name) == 0)
		{
			return param;
		}
	}

	if (findParent && _parent)
		return _parent->findParameter(name, true);

	return nullptr;
}

C3DRenderState::AutoBinding C3DRenderState::getAutoBinding(const char* name) const
{
	std::map<std::string, AutoBinding>::const_iterator itr = _autoBindings.find(name);
	if (itr != _autoBindings.end())
		return itr->second;

	if (_parent)
		return _parent->getAutoBinding(name);

	return NONE;
}

const char* C3DRenderState::getAutoBindingVariable(C3DRenderState::AutoBinding b) 
{
	return AUTO_BINDING_VARIABLES[b];
}

C3DRenderState::AutoBinding C3DRenderState::getAutoBindingOfVariable(const char* name)
{
	for (int i = NONE + 1; i < AUTO_BINDING_NUM; i++)
	{
		if (strcmp(name, AUTO_BINDING_VARIABLES[i]) == 0)
		{
			return (AutoBinding) i;
		}
	}

	return NONE;
}

bool C3DRenderState::load(C3DElementNode* nodes)
{
	// Rewind the properties to start reading from the start
	nodes->rewind();

	const char* name;
	while (name = nodes->getNextElement())
	{
		if (isMaterialKeyword(name))
			continue; // keyword - skip

		switch (nodes->getElementType())
		{
		case C3DElementNode::NUMBER:
			float value;
			this->getParameter(name)->setValue(nodes->getElement(nullptr,&value));
			break;
		case C3DElementNode::VECTOR2:
			{
				C3DVector2 vector2;
				nodes->getElement(nullptr, &vector2);
				this->getParameter(name)->setValue(vector2);
			}
			break;
		case C3DElementNode::VECTOR3:
			{
				C3DVector3 vector3;
				nodes->getElement(nullptr, &vector3);
				this->getParameter(name)->setValue(vector3);
			}
			break;
		case C3DElementNode::VECTOR4:
			{
				C3DVector4 vector4;
				nodes->getElement(nullptr, &vector4);
				this->getParameter(name)->setValue(vector4);
			}
			break;
		case C3DElementNode::MATRIX:
			{
				C3DMatrix matrix;
				nodes->getElement(nullptr, &matrix);
				this->getParameter(name)->setValue(matrix);
			}
			break;
		default:
			{
				// Assume this is a parameter auto-binding
				//       renderState->setParameterAutoBinding(name, nodes->getElement());
			}
			break;
		}
	}

	// Iterate through all child namespaces searching for samplers and render state blocks
	C3DElementNode* ns;
	while (ns = nodes->getNextChild())
	{
		if (strcmp(ns->getNodeType(), "sampler") == 0)
		{
			//// Read the texture uniform name
			name = ns->getNodeName();
			if (strlen(name) == 0)
				continue; // missing texture uniform name

			C3DSampler* sampler = new C3DSampler();
			if(sampler->load(ns) == true)
			{
				this->getParameter(name)->setValue(sampler);
				sampler->release();
			}
			else
			{
				SAFE_RELEASE(sampler);
				continue;
			}
		}		
		else if (strcmp(ns->getNodeType(), "renderState") == 0)
		{
			C3DStateBlock* stateBlock = new C3DStateBlock();
			if(stateBlock->load(ns) == true)
			{
				_stateBlock = stateBlock;
			}
			else
			{
				SAFE_DELETE(stateBlock);
				continue;
			}

		}
	}

	return true;
}

bool C3DRenderState::save(C3DElementNode* node)
{   
	for (std::list<MaterialParameter*>::iterator iter = _parameters.begin();iter != _parameters.end();++iter)
		// for (size_t i = 0; i < this->_parameters.size(); i++)
	{
		MaterialParameter* parameter = *iter;
		std::string value;

		switch (parameter->_type)
		{
		case MaterialParameter::FLOAT:
			node->setElement(parameter->_name.c_str(), &parameter->_value.floatValue);
			break;
		case MaterialParameter::INT:
			node->setElement(parameter->_name.c_str(), &parameter->_value.intValue);
			break;
		case MaterialParameter::VECTOR2:
			node->setElement(parameter->_name.c_str(), reinterpret_cast<C3DVector2*>(parameter->_value.floatPtrValue));
			break;
		case MaterialParameter::VECTOR3:
			node->setElement(parameter->_name.c_str(), reinterpret_cast<C3DVector3*>(parameter->_value.floatPtrValue));
			break;
		case MaterialParameter::VECTOR4:
			node->setElement(parameter->_name.c_str(), reinterpret_cast<C3DVector4*>(parameter->_value.floatPtrValue));
			break;
		case MaterialParameter::SAMPLER:
			{
				C3DSampler* sampler = const_cast<C3DSampler*>(parameter->_value.samplerValue);
				if(sampler != nullptr)
				{
					C3DElementNode* samplerNode = C3DElementNode::createEmptyNode(parameter->_name.c_str(), "sampler");
					if(sampler->save(samplerNode) == true)
					{
						node->addChildNode(samplerNode);
					}
					else
					{
						SAFE_DELETE(samplerNode);
						return false;
					}
				}              

			}
			break;       
		default:
			{
			}
			break;
		}

	}

	if(_stateBlock != nullptr)
	{
		C3DElementNode* stateNode = C3DElementNode::createEmptyNode("", "renderState");
		if(_stateBlock->save(stateNode) == true)
		{
			node->addChildNode(stateNode);
		}
		else
		{
			SAFE_DELETE(stateNode);
			return false;
		}
	}

	return true;
}

C3DRenderState* C3DRenderState::getParent()
{
	return _parent;
}

NS_CC_END

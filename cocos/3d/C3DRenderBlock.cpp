#include "Base.h"
#include "C3DRenderBlock.h"

#include "ElementNode.h"


// Render state override bits
#define RS_BLEND 1
#define RS_BLEND_FUNC 2
#define RS_CULL_FACE 4
#define RS_DEPTH_TEST 8
#define RS_DEPTH_WRITE 16

NS_CC_BEGIN

C3DStateBlock* C3DStateBlock::_defaultState = nullptr;


C3DStateBlock::C3DStateBlock()
	: _blendEnabled(false), _cullFaceEnabled(false), _depthTestEnabled(false), _depthWriteEnabled(false),
	_srcBlend(C3DStateBlock::BLEND_ONE), _dstBlend(C3DStateBlock::BLEND_ONE), _bits(0L)
{
}


C3DStateBlock::~C3DStateBlock()
{
}

void C3DStateBlock::initialize()
{
	if (_defaultState == nullptr)
	{
		_defaultState = new C3DStateBlock();
	}
}

void C3DStateBlock::finalize()
{
	SAFE_RELEASE(_defaultState);
}

C3DStateBlock* C3DStateBlock::create()
{
	return new C3DStateBlock();
}

void C3DStateBlock::bind()
{
	// When the public bind() is called with no C3DRenderState object passed in,
	// we assume we are being called to bind the state of a single StateBlock,
	// irrespective of whether it belongs to a hierarchy of RenderStates.
	// Therefore, we call restore() here with only this StateBlock's override
	// bits to restore state before applying the new state.
	C3DStateBlock::restore(_bits);

	bindNoRestore();
}

void C3DStateBlock::bindNoRestore()
{
	// Update any state that differs from _defaultState and flip _defaultState bits
	if ((_bits & RS_BLEND) &&  !(_defaultState->_bits & RS_BLEND))
	{
		glEnable(GL_BLEND);
		_defaultState->_bits |= RS_BLEND;
		_defaultState->_blendEnabled = _blendEnabled;
	}
	if ((_bits & RS_BLEND_FUNC) && (_srcBlend != _defaultState->_srcBlend || _dstBlend != _defaultState->_dstBlend))
	{
		glBlendFunc((GLenum)_srcBlend, (GLenum)_dstBlend);
		_defaultState->_srcBlend = _srcBlend;
		_defaultState->_dstBlend = _dstBlend;
	}
	if ((_bits & RS_CULL_FACE) && !(_defaultState->_bits & RS_CULL_FACE))
	{
		glEnable(GL_CULL_FACE);
		_defaultState->_bits |= RS_CULL_FACE;
		_defaultState->_cullFaceEnabled = _cullFaceEnabled;
	}
	if ((_bits & RS_DEPTH_TEST) && !(_defaultState->_bits & RS_DEPTH_TEST))
	{
		glEnable(GL_DEPTH_TEST);
		_defaultState->_bits |= RS_DEPTH_TEST;
		_defaultState->_depthTestEnabled = _depthTestEnabled;
	}
	if ((_bits & RS_DEPTH_WRITE) && !(_defaultState->_bits & RS_DEPTH_WRITE))
	{
		glDepthMask(GL_TRUE);
		_defaultState->_bits |= RS_DEPTH_WRITE;
		_defaultState->_depthWriteEnabled = _depthWriteEnabled;
	}

	_defaultState->_bits |= _bits;
}

void C3DStateBlock::restore(long stateOverrideBits)
{
	// If there is no state to restore (i.e. no non-default state), do nothing
	if (_defaultState->_bits == 0)
	{
		return;
	}

	// Restore any state that is not overridden and is not default
	if (!(stateOverrideBits & RS_BLEND) && (_defaultState->_bits & RS_BLEND))
	{
		glDisable(GL_BLEND);
		_defaultState->_bits &= ~RS_BLEND;
		_defaultState->_blendEnabled = false;
	}
	if (!(stateOverrideBits & RS_BLEND_FUNC) && (_defaultState->_bits & RS_BLEND_FUNC))
	{
		glBlendFunc(GL_ONE, GL_ONE);
		_defaultState->_bits &= ~RS_BLEND_FUNC;
		_defaultState->_srcBlend = C3DStateBlock::BLEND_ONE;
		_defaultState->_dstBlend = C3DStateBlock::BLEND_ONE;
	}
	if (!(stateOverrideBits & RS_CULL_FACE) && (_defaultState->_bits & RS_CULL_FACE))
	{
		glDisable(GL_CULL_FACE);
		_defaultState->_bits &= ~RS_CULL_FACE;
		_defaultState->_cullFaceEnabled = false;
	}
	if (!(stateOverrideBits & RS_DEPTH_TEST) && (_defaultState->_bits & RS_DEPTH_TEST))
	{
		glDisable(GL_DEPTH_TEST);
		_defaultState->_bits &= ~RS_DEPTH_TEST;
		_defaultState->_depthTestEnabled = false;
	}
	if (!(stateOverrideBits & RS_DEPTH_WRITE) && (_defaultState->_bits & RS_DEPTH_WRITE))
	{
		glDepthMask(GL_FALSE);
		_defaultState->_bits &= ~RS_DEPTH_WRITE;
		_defaultState->_depthWriteEnabled = false;
	}

}

void C3DStateBlock::enableDepthWrite()
{
	// Internal method used by RenderSystem::clear() to restore depth writing before a
	// clear operation. This is neccessary if the last code to draw before the
	// next frame leaves depth writing disabled.
	if (!_defaultState->_depthWriteEnabled)
	{
		glDepthMask(GL_TRUE);
		_defaultState->_bits &= ~RS_DEPTH_WRITE;
		_defaultState->_depthWriteEnabled = true;
	}
}

bool parseBoolean(const char* value)
{
	if (strlen(value) == 4)
	{
		return (
			tolower(value[0]) == 't' &&
			tolower(value[1]) == 'r' &&
			tolower(value[2]) == 'u' &&
			tolower(value[3]) == 'e' );
	}

	return false;
}

C3DStateBlock::Blend parseBlend(const char* value)
{
	// Conver the string to uppercase for comparison
	std::string upper(value);
	std::transform(upper.begin(), upper.end(), upper.begin(), (int(*)(int))toupper);
	if (upper == "ZERO")
		return C3DStateBlock::BLEND_ZERO;
	if (upper == "ONE")
		return C3DStateBlock::BLEND_ONE;
	if (upper == "SRC_ALPHA")
		return C3DStateBlock::BLEND_SRC_ALPHA;
	if (upper == "ONE_MINUS_SRC_ALPHA")
		return C3DStateBlock::BLEND_ONE_MINUS_SRC_ALPHA;
	if (upper == "DST_ALPHA")
		return C3DStateBlock::BLEND_DST_ALPHA;
	if (upper == "ONE_MINUS_DST_ALPHA")
		return C3DStateBlock::BLEND_ONE_MINUS_DST_ALPHA;
	if (upper == "CONSTANT_ALPHA")
		return C3DStateBlock::BLEND_CONSTANT_ALPHA;
	if (upper == "ONE_MINUS_CONSTANT_ALPHA")
		return C3DStateBlock::BLEND_ONE_MINUS_CONSTANT_ALPHA;
	if (upper == "SRC_ALPHA_SATURATE")
		return C3DStateBlock::BLEND_SRC_ALPHA_SATURATE;

	WARN_VARG("Warning: Unrecognized blend value (%s), defaulting to BLEND_ONE.", value);
	return C3DStateBlock::BLEND_ONE;
}

const char* blendToString(C3DStateBlock::Blend blend)
{
	switch (blend)
	{
	case C3DStateBlock::BLEND_ZERO:
		return "ZERO";
	case C3DStateBlock::BLEND_ONE:
		return "ONE";
	case C3DStateBlock::BLEND_SRC_ALPHA:
		return "SRC_ALPHA";
	case C3DStateBlock::BLEND_ONE_MINUS_SRC_ALPHA:
		return "ONE_MINUS_SRC_ALPHA";
	case C3DStateBlock::BLEND_DST_ALPHA:
		return "DST_ALPHA";
	case C3DStateBlock::BLEND_ONE_MINUS_DST_ALPHA:
		return "ONE_MINUS_DST_ALPHA";
	case C3DStateBlock::BLEND_CONSTANT_ALPHA:
		return "CONSTANT_ALPHA";
	case C3DStateBlock::BLEND_ONE_MINUS_CONSTANT_ALPHA:
		return "ONE_MINUS_CONSTANT_ALPHA";
	case C3DStateBlock::BLEND_SRC_ALPHA_SATURATE:
		return "SRC_ALPHA_SATURATE";
	}
	return "ONE";
}

void C3DStateBlock::setState(const char* name, const char* value)
{
	assert(name && value);

	if (strcmp(name, "blend") == 0)
	{
		setBlend(parseBoolean(value));
	}
	else if (strcmp(name, "srcBlend") == 0)
	{
		setBlendSrc(parseBlend(value));
	}
	else if (strcmp(name, "dstBlend") == 0)
	{
		setBlendDst(parseBlend(value));
	}
	else if (strcmp(name, "cullFace") == 0)
	{
		setCullFace(parseBoolean(value));
	}
	else if (strcmp(name, "depthTest") == 0)
	{
		setDepthTest(parseBoolean(value));
	}
	else if (strcmp(name, "depthWrite") == 0)
	{
		setDepthWrite(parseBoolean(value));
	}
	else
	{
		WARN_VARG("Warning: Invalid render state: %s", name);
	}
}

void C3DStateBlock::backUpGLState()
{
	// States
	_blendEnabled = glIsEnabled(GL_BLEND);

	_cullFaceEnabled = glIsEnabled(GL_CULL_FACE);
	_depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
	GLint writemask;
	glGetIntegerv(GL_DEPTH_WRITEMASK, &writemask);
	_depthWriteEnabled = writemask;

	GLint blend;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &blend);
	_srcBlend = (Blend)blend;
	glGetIntegerv(GL_BLEND_DST_ALPHA, &blend);
	_dstBlend = (Blend)blend;

	_bits = 0L;

	if (_blendEnabled)
		_bits |= RS_BLEND;

	if (_cullFaceEnabled)
		_bits |= RS_CULL_FACE;

	if (_depthTestEnabled)
		_bits |= RS_DEPTH_TEST;


	if (_depthWriteEnabled)
		_bits |= RS_DEPTH_WRITE;

	if (_srcBlend == BLEND_ONE || _dstBlend != BLEND_ONE)
		_bits |= RS_BLEND_FUNC;

	//update current opengl state
	*_defaultState = *this;
}

void C3DStateBlock::restoreGLState(bool bforce)
{
	if (bforce)
	{
		if (_blendEnabled)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
		if (_cullFaceEnabled)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
		if (_depthTestEnabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);


		if (_depthWriteEnabled)
			glDepthMask(GL_TRUE);
		else
			glDepthMask(GL_FALSE);

		glBlendFunc(_srcBlend, _dstBlend);

	}
	else
	{
		if (_blendEnabled != _defaultState->_blendEnabled )
		{
			if (_blendEnabled)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}
		if (_cullFaceEnabled != _defaultState->_cullFaceEnabled)
		{
			if (_cullFaceEnabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
		if (_depthTestEnabled != _defaultState->_depthTestEnabled)
		{
			if (_depthTestEnabled)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		if (_depthWriteEnabled != _defaultState->_depthWriteEnabled)
		{
			if (_depthWriteEnabled)
				glDepthMask(GL_TRUE);
			else
				glDepthMask(GL_FALSE);
		}
		if (_srcBlend != _defaultState->_srcBlend || _dstBlend != _defaultState->_dstBlend)
		{
			glBlendFunc(_srcBlend, _dstBlend);
		}
	}

	_bits = 0L;

	if (_blendEnabled)
		_bits |= RS_BLEND;

	if (_cullFaceEnabled)
		_bits |= RS_CULL_FACE;

	if (_depthTestEnabled)
		_bits |= RS_DEPTH_TEST;


	if (_depthWriteEnabled)
		_bits |= RS_DEPTH_WRITE;

	if (_srcBlend == BLEND_ONE || _dstBlend != BLEND_ONE)
		_bits |= RS_BLEND_FUNC;

	*_defaultState = *this;
}

void C3DStateBlock::setBlend(bool enabled)
{
	_blendEnabled = enabled;
	if (!enabled)
	{
		_bits &= ~RS_BLEND;
	}
	else
	{
		_bits |= RS_BLEND;
	}
}

void C3DStateBlock::setBlendSrc(Blend blend)
{
	_srcBlend = blend;
	if (_srcBlend == BLEND_ONE && _dstBlend == BLEND_ONE)
	{
		_bits &= ~RS_BLEND_FUNC;
	}
	else
	{
		_bits |= RS_BLEND_FUNC;
	}
}

void C3DStateBlock::setBlendDst(Blend blend)
{
	_dstBlend = blend;
	if (_srcBlend == BLEND_ONE && _dstBlend == BLEND_ONE)
	{
		_bits &= ~RS_BLEND_FUNC;
	}
	else
	{
		_bits |= RS_BLEND_FUNC;
	}
}

void C3DStateBlock::setCullFace(bool enabled)
{
	_cullFaceEnabled = enabled;
	if (!enabled)
	{
		_bits &= ~RS_CULL_FACE;
	}
	else
	{
		_bits |= RS_CULL_FACE;
	}
}

void C3DStateBlock::setDepthTest(bool enabled)
{
	_depthTestEnabled = enabled;
	if (!enabled)
	{
		_bits &= ~RS_DEPTH_TEST;
	}
	else
	{
		_bits |= RS_DEPTH_TEST;
	}
}

void C3DStateBlock::setDepthWrite(bool enabled)
{
	_depthWriteEnabled = enabled;
	if (!enabled)
	{
		_bits &= ~RS_DEPTH_WRITE;
	}
	else
	{
		_bits |= RS_DEPTH_WRITE;
	}
}

bool C3DStateBlock::load(ElementNode* node)
{  
	node->rewind();
	const char* name;
	while (name = node->getNextElement())
	{
		this->setState(name, node->getElement());
	}

	return true;
}

bool C3DStateBlock::save(ElementNode* node)
{   
	if (_bits & RS_BLEND)
		node->setElement("blend", &_blendEnabled);
	if (_bits & RS_BLEND_FUNC)
	{
		node->setElement("srcBlend", blendToString(_srcBlend));
		node->setElement("dstBlend", blendToString(_dstBlend));
	}
	if (_bits & RS_CULL_FACE)
		node->setElement("cullFace", &_cullFaceEnabled);
	if (_bits & RS_DEPTH_TEST)
		node->setElement("depthTest", &_depthTestEnabled);
	if (_bits & RS_DEPTH_WRITE)
		node->setElement("depthWrite", &_depthWriteEnabled);

	return true;
}

NS_CC_END

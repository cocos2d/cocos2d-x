#include "C3DPass.h"
#include "C3DTechnique.h"
#include "C3DVertexDeclaration.h"
#include "C3DEffect.h"
#include "MaterialParameter.h"
#include "ElementNode.h"
#include "C3DSampler.h"
#include "C3DRenderBlock.h"

#include "C3DEffectManager.h"

NS_CC_BEGIN

C3DPass::C3DPass() :
_id("")
,_technique(nullptr)
,_effect(nullptr)
,_vaBinding(nullptr)
,_nMaxDirLight(0)
,_nMaxPointLight(0)
,_nMaxSpotLight(0)
,_nMaxShadowMap(0)
{
    _id = "";
}


C3DPass::C3DPass(const char* id, C3DTechnique* technique, C3DEffect* effect)
:_id(id ? id : "")
,_technique(technique)
,_effect(effect)
,_vaBinding(nullptr)
,_nMaxDirLight(0)
,_nMaxPointLight(0)
,_nMaxSpotLight(0)
,_nMaxShadowMap(0)
{
    assert(technique);
    C3DRenderState::_parent = _technique;
}

C3DPass::~C3DPass()
{
    SAFE_RELEASE(_effect);
    SAFE_RELEASE(_vaBinding);
}

const char* C3DPass::getId() const
{
    return _id.c_str();
}

C3DEffect* C3DPass::getEffect() const
{
    return _effect;
}

void C3DPass::setVertexAttributeBinding(C3DVertexDeclaration* binding)
{
    SAFE_RELEASE(_vaBinding);

    if (binding)
    {
        _vaBinding = binding;
        binding->retain();
    }
}

void C3DPass::bind()
{
    // Bind our effect
    _effect->bind();

    // Bind our render state
    C3DRenderState::bind(this);

    // If we have a vertex attribute binding, bind it
    if (_vaBinding)
    {
        _vaBinding->bind();
    }
}

void C3DPass::setParamMethonAutoUniform()
{
    C3DRenderState::setParamMethonAutoUniform(this);
}

void C3DPass::unbind()
{
    // If we have a vertex attribute binding, unbind it
    if (_vaBinding)
    {
        _vaBinding->unbind();
    }

    GL_ASSERT( glUseProgram(0) );
}

C3DPass* C3DPass::clone() const
{
    C3DPass* other = new C3DPass(_id.c_str(), _technique, _effect);
    if (_effect)
        _effect->retain();

    other->copyFrom(this);
    other->_nMaxAnimLight = _nMaxAnimLight;
    other->_nMaxDirLight = _nMaxDirLight;
    other->_nMaxPointLight = _nMaxPointLight;
    other->_nMaxSpotLight = _nMaxSpotLight;
    other->_nMaxShadowMap = _nMaxShadowMap;
    other->autorelease();
    return other;
}

void C3DPass::setupParametersFromEffect()
{
    static int zeros[4] = {0};

    for ( unsigned int i = 0; i < _effect->getUniformCount(); i++)
    {
        Uniform* uniform = _effect->getUniform(i);
        MaterialParameter* parameter = findParameter(uniform->getName().c_str(), true);
        // already in material script, skip
        if (parameter)
        {            
            continue;
        }

        /* if (getAutoBinding(uniform->getName()))
        continue;*/

        C3DRenderState::AutoBinding binding = C3DRenderState::getAutoBindingOfVariable(uniform->getName().c_str());

        if (binding)
        {
            setParameterAutoBinding(uniform->getName().c_str(), binding);
        }
        else
        {
            // add parameter in shader but not in material script
            parameter = new MaterialParameter(uniform->getName().c_str());
            _parameters.push_back(parameter);

            // set default value
            switch (uniform->getType())
            {
            case GL_FLOAT:
                parameter->setValue(0.0f);
                break;
            case GL_FLOAT_VEC2:
                parameter->setValue(Vector2(1.0f, 1.0f));
                break;
            case GL_FLOAT_VEC3:
                parameter->setValue(Vector3(1.0f, 1.0f, 1.0f));
                break;
            case GL_FLOAT_VEC4:
                parameter->setValue(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
                break;
            case GL_FLOAT_MAT4:
                parameter->setValue(Matrix::identity());
                break;
            case GL_INT:
                parameter->setValue((int)0);
                break;
            case GL_INT_VEC2:
                parameter->setValue(zeros, 2);
                break;
            case GL_INT_VEC3:
                parameter->setValue(zeros, 3);
                break;
            case GL_INT_VEC4:
                parameter->setValue(zeros, 4);
                break;
            case GL_SAMPLER_2D:
                {
                    C3DSampler* sampler = new C3DSampler();
                    parameter->setValue(sampler);
                    sampler->release();
                }

                break;
            }
        }
    }

    //..


    for (std::list<MaterialParameter*>::iterator iter = _parameters.begin();iter != _parameters.end();iter)
    {
        if(_effect->getUniform((*iter)->getName()) == nullptr)
        {
            MaterialParameter* parameter = *iter;       

            SAFE_RELEASE(parameter);

            iter = _parameters.erase(iter);

        }
        else
        {
            ++iter;
        }
    }
}

bool C3DPass::load(ElementNode* node)
{
    this->_id = node->getNodeName();
    // Fetch shader info required to create the effect of this technique.
    const char* m = node->getElement("vertexShader");
    std::string vshPath = m==nullptr ? "" : m;
    assert(vshPath.c_str());

    m = node->getElement("fragmentShader");
    std::string fshPath = m==nullptr ? "" : m;    
    assert(fshPath.c_str());

    m = node->getElement("defines");
    std::string defines;
    if(m != nullptr)
        defines = m;

    std::string uniqueId = C3DEffectManager::generateID(vshPath,fshPath,defines);

    C3DEffect* effect = static_cast<C3DEffect*>(C3DEffectManager::getInstance()->getResource(uniqueId));

    assert(effect);   

    this->_effect = effect;

    this->_vshPath = vshPath;
    this->_fshPath = fshPath;    
    this->_defines = defines;

    if (_defines.c_str())
    {
        const char* ptr = strstr(_defines.c_str(), "MAXDIRLIGHT");
        if (ptr)
        {
            this->_nMaxDirLight = atoi(ptr + 11);
        }
        ptr = strstr(_defines.c_str(), "MAXPOINTLIGHT");
        if (ptr)
        {
            this->_nMaxPointLight = atoi(ptr + 13);
        }
        ptr = strstr(_defines.c_str(), "MAXSPOTLIGHT");
        if (ptr)
        {
            this->_nMaxSpotLight = atoi(ptr + 12);
        }
        ptr = strstr(_defines.c_str(), "MAXANIMLIGHT");
        if (ptr)
        {
            this->_nMaxAnimLight = atoi(ptr + 12);
        }
        ptr = strstr(_defines.c_str(), "SHADOWMAP");
        if (ptr)
        {
            this->_nMaxShadowMap = 1;
        }
    }   

    // Load render state
    C3DRenderState::load(node);

    if(_stateBlock == nullptr)
        _stateBlock = C3DStateBlock::create();

    return true;
}

bool C3DPass::save(ElementNode* node)
{  
    node->setElement("vertexShader", &this->_vshPath);
    node->setElement("fragmentShader", &this->_fshPath);
    if (this->_defines.length() > 0)
        node->setElement("defines", &this->_defines);

    C3DRenderState::save(node);

    return node;
}

NS_CC_END

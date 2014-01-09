#include "C3DMaterial.h"
#include "Stream.h"
#include "C3DPass.h"
#include "ElementNode.h"
#include "C3DTexture.h"
#include "C3DTechnique.h"
#include "C3DSampler.h"
#include "MaterialParameter.h"
#include "C3DEffect.h"
#include "Vector3.h"
#include "Vector4.h"


NS_CC_BEGIN

C3DMaterial::C3DMaterial(const std::string& name)
:C3DResource(name)
{
    memset(_techniqueChannel, 0, sizeof(_techniqueChannel));
}

C3DMaterial::~C3DMaterial()
{
    // Destroy all the techniques.
    for (unsigned int i = 0, count = _techniques.size(); i < count; ++i)
    {
        C3DTechnique* technique = _techniques[i];
        if (technique)
        {
            SAFE_RELEASE(technique);
        }
    }
    memset(_techniqueChannel, 0, sizeof(_techniqueChannel));
}

C3DMaterial* C3DMaterial::create(const char* fileName)
{
    assert(fileName);    

    // Load the material properties from file
    ElementNode* nodes = ElementNode::create(fileName);
    assert(nodes);
    if (nodes == nullptr)
    {
        return nullptr;
    }   

    ElementNode* materialNodes = (strlen(nodes->getNodeType()) > 0) ? nodes : nodes->getNextChild();
    if (!materialNodes || !(strcmp(materialNodes->getNodeType(), "material") == 0))
    {
        return nullptr;
    }
    C3DMaterial* material = C3DMaterial::create(materialNodes);

    //material->setName(fileName);
    SAFE_DELETE(nodes);

    return material;
}

C3DMaterial* C3DMaterial::create(ElementNode* materialNodes)
{
    // Check if the Properties is valid and has a valid namespace.
    assert(materialNodes);
    if (!materialNodes || !(strcmp(materialNodes->getNodeType(), "material") == 0))
    {
        return nullptr;
    }

    // Create new material from the file passed in.

    C3DMaterial* material = new C3DMaterial("");
    if(material->load(materialNodes) == false)
    {
        SAFE_RELEASE(material);
        return nullptr;
    }

    material->autorelease();
    return material;


}

C3DMaterial* C3DMaterial::create(const char* vshPath, const char* fshPath, const char* defines)
{
    // Create a new material with a single technique and pass for the given effect
    C3DMaterial* material = new C3DMaterial("");

    ElementNode* tpMatNode = cocos2d::ElementNode::createEmptyNode("0", "material");
    if (!tpMatNode)
        return false;

    cocos2d::ElementNode* tpNodeTechnique = cocos2d::ElementNode::createEmptyNode("0", "technique");
    tpMatNode->addChildNode(tpNodeTechnique);

    cocos2d::ElementNode* tpNodePass = cocos2d::ElementNode::createEmptyNode("0", "pass");
    tpNodeTechnique->addChildNode(tpNodePass);
    tpNodePass->setElement("vertexShader", (vshPath == nullptr) ? "" : vshPath);
    tpNodePass->setElement("fragmentShader", (fshPath == nullptr) ? "" : fshPath);
    if(defines != nullptr)
        tpNodePass->setElement("defines", defines);

    material->load(tpMatNode);
    material->autorelease();

    SAFE_DELETE(tpMatNode);

    return material;
}

unsigned int C3DMaterial::getTechniqueCount() const
{
    return _techniques.size();
}

C3DTechnique* C3DMaterial::getTechnique(unsigned int index) const
{
    assert(index < _techniques.size());

    return _techniques[index];
}

C3DTechnique* C3DMaterial::getTechnique(const char* id) const
{
    for (unsigned int i = 0, count = _techniques.size(); i < count; ++i)
    {
        C3DTechnique* t = _techniques[i];
        if (strcmp(t->getId(), id) == 0)
        {
            return t;
        }
    }

    return nullptr;
}

C3DTechnique* C3DMaterial::getTechnique() const
{
    return _techniqueChannel[TECH_USAGE_SCREEN];
}

C3DTechnique* C3DMaterial::getTechnique(TechniqueUsage usage) const
{
    CCAssert(usage >= 0 && usage < TECH_USAGE_NUM, "index out of range");
    return _techniqueChannel[usage];
}

bool C3DMaterial::setTechnique(TechniqueUsage usage, const char* id)
{
    CCAssert(usage >= 0 && usage < TECH_USAGE_NUM, "index out of range");
    C3DTechnique* t = getTechnique(id);
    if (t)
    {
        _techniqueChannel[usage] = t;
    }
    return t != nullptr;    
}

bool C3DMaterial::setTechnique(TechniqueUsage usage, unsigned int index)
{
    CCAssert(usage >= 0 && usage < TECH_USAGE_NUM, "index out of range");
    C3DTechnique* t = getTechnique(index);
    if (t)
    {
        _techniqueChannel[usage] = t;
    }
    return t != nullptr;    
}

bool C3DMaterial::save(ElementNode* nodes)
{
    C3DRenderState::save(nodes);

    for (size_t i = 0; i < this->_techniques.size(); i++)
    {
        C3DTechnique* technique = this->_techniques[i];
        ElementNode* techNode = ElementNode::createEmptyNode(technique->getId(), "technique");

        if (technique->save(techNode) == true)
        {
            nodes->addChildNode(techNode);
        }
        else
        {
            SAFE_DELETE(techNode);
            return false;
        }
    }

    return true;

}

C3DMaterial* C3DMaterial::clone() const
{
    C3DMaterial* other = new C3DMaterial("");
    ((C3DRenderState*)other)->copyFrom(this);

    ((C3DResource*)other)->copyFrom(this);

    for (size_t i = 0; i < _techniques.size(); i++)
    {
        other->_techniques.push_back(_techniques[i]->clone());
        other->_techniques[i]->retain();
        other->_techniques[i]->_parent = other;
        other->_techniques[i]->_material = other;

        for (int iUsage = 0; iUsage < TECH_USAGE_NUM; iUsage++)
        {
            if (_techniqueChannel[iUsage] == _techniques[i])
                other->_techniqueChannel[iUsage] = other->_techniques[i];
        }
    }

    other->autorelease();
    return other;
}

bool C3DMaterial::load(ElementNode* materialNodes)
{    
    // Go through all the material properties and create techniques under this material.
    materialNodes->rewind();
    ElementNode* techniqueNodes = nullptr;
    while ((techniqueNodes = materialNodes->getNextChild()))
    {
        if (strcmp(techniqueNodes->getNodeType(), "technique") == 0)
        {
            C3DTechnique* technique = new C3DTechnique();
            if (technique->load(techniqueNodes) == false)
            {
                SAFE_RELEASE(technique);                
                return false;
            }
            else
            {
                technique->_material = this;
                technique->_parent = this;
                this->_techniques.push_back(technique);

            }
        }
    }

    // Load uniform value parameters for this material
    C3DRenderState::load(materialNodes);

    // setup parameter from effect
    for (unsigned int i = 0, count = this->_techniques.size(); i < count; ++i)
    {
        C3DTechnique* technique = this->_techniques[i];
        if (technique)
        {
            for (unsigned int j = 0; j < technique->_passes.size(); ++j)
            {
                technique->_passes[j]->setupParametersFromEffect();
            }

        }
    }

    // Set the current technique to the first found technique
    if (this->getTechniqueCount() > 0)
    {
        this->setTechnique(TECH_USAGE_SCREEN, 0u);
        this->setTechnique(TECH_USAGE_SHADOWMAP, "_castshadow");
    }

    return true;
}

NS_CC_END

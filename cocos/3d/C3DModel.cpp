#include "Base.h"
#include "C3DModel.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DMeshSkin.h"
#include "C3DScene.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DNode.h"

#include "C3DMaterial.h"

#include "BonePart.h"
#include "Morph.h"
#include "C3DVertexDeclaration.h"

#include "C3DLightFilter.h"
#include "MaterialParameter.h"

#include "C3DStat.h"
#include "C3DAnimatedLight.h"
#include "C3DShadowMap.h"
#include "C3DMaterialManager.h"

namespace cocos3d
{
C3DLightFilter* C3DModel::s_lightFilter = NULL;
    

C3DModel::C3DModel(C3DMesh* mesh) :
    _mesh(mesh), _material(NULL), _partCount(0), _partMaterials(NULL), _node(NULL), _wireframe(false)
{
	 mesh->retain();
	_morph = NULL;
    _partCount = mesh->getPartCount();
        
}

C3DModel::~C3DModel()
{
    SAFE_RELEASE(_material);

    if (_partMaterials)
    {
        for (unsigned int i = 0; i < _partCount; ++i)
        {
            SAFE_RELEASE(_partMaterials[i]);
        }
        SAFE_DELETE_ARRAY(_partMaterials);
    }

    SAFE_RELEASE(_mesh);   

	SAFE_DELETE(_morph);


}

C3DModel* C3DModel::create(C3DMesh* mesh)
{   
    return new C3DModel(mesh);
}

C3DMesh* C3DModel::getMesh() const
{
    return _mesh;
}

unsigned int C3DModel::getMeshPartCount() const
{
    return _mesh->getPartCount();
}

C3DMaterial* C3DModel::getMaterial(int partIndex)
{
    assert(partIndex == -1 || (partIndex >= 0 && partIndex < (int)getMeshPartCount()));

    C3DMaterial* m = NULL;

    if (partIndex >= 0 && partIndex < (int)_partCount)
    {
        // Look up explicitly specified part material.
        if (_partMaterials)
        {
            m = _partMaterials[partIndex];
        }
    }

    if (m == NULL)
    {
        // Return the shared material.
         m = _material;
    }

    return m;
}

void C3DModel::setMaterial(C3DMaterial* material, int partIndex)
{
    assert(partIndex == -1 || (partIndex >= 0 && partIndex < (int)getMeshPartCount()));

    C3DMaterial* oldMaterial = NULL;

    if (partIndex == -1)
    {
        oldMaterial = _material;

        // Set new shared material.
        if (material)
        {
            _material = material;
            _material->retain();
        }
    }
    else if (partIndex >= 0 && partIndex < (int)getMeshPartCount())
    {
        // Ensure mesh part count is up-to-date.
        validatePartCount();

        // Release existing part material and part binding.
        if (_partMaterials)
        {
            oldMaterial = _partMaterials[partIndex];
        }
        else
        {
            // Allocate part arrays for the first time.
            if (_partMaterials == NULL)
            {
                _partMaterials = new C3DMaterial*[_partCount];
                memset(_partMaterials, 0, sizeof(C3DMaterial*) * _partCount);
            }
        }

        // Set new part material.
        if (material)
        {
            _partMaterials[partIndex] = material;
            material->retain();
        }
    }

    // Release existing material and binding.
    if (oldMaterial)
    {
       for (unsigned int i = 0, tCount = oldMaterial->getTechniqueCount(); i < tCount; ++i)
        {
            C3DTechnique* t = oldMaterial->getTechnique(i);
            for (unsigned int j = 0, pCount = t->getPassCount(); j < pCount; ++j)
            {
                t->getPass(j)->setVertexAttributeBinding(NULL);
            }
        }
        SAFE_RELEASE(oldMaterial);
    }

    if (material)
    {
        // Hookup vertex attribute bindings for all passes in the new material.
        for (unsigned int i = 0, tCount = material->getTechniqueCount(); i < tCount; ++i)
        {
            C3DTechnique* t = material->getTechnique(i);
            for (unsigned int j = 0, pCount = t->getPassCount(); j < pCount; ++j)
            {
                C3DPass* p = t->getPass(j);
                C3DVertexDeclaration* b = C3DVertexDeclaration::create(_mesh, p->getEffect());
                p->setVertexAttributeBinding(b);
                SAFE_RELEASE(b);
            }
        }

        // Apply node binding for the new material.
        if (_node)
        {
            setMaterialNodeBinding(material);
        }
    }
}

C3DMaterial* C3DModel::setMaterial(const char* vshPath, const char* fshPath, const char* defines, int partIndex)
{
    // Try to create a C3DMaterial with the given parameters.
    C3DMaterial* material = C3DMaterial::create(vshPath, fshPath, defines);
    if (material == NULL)
    {
        return NULL;
    }

    // Assign the material to us.
    setMaterial(material, partIndex);

    // Release the material since we now have a reference to it.
    //material->release();

    return material;
}

C3DMaterial* C3DModel::setMaterial(const char* materialPath, int partIndex)
{
    // Try to create a C3DMaterial from the specified material file.
	C3DMaterial* material = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->getResource(materialPath));
	if(material == NULL)
	{
		material = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->createResource(materialPath));			
	}	

    if (material == NULL)
    {
        return NULL;
    }

    // Assign the material to us
    setMaterial(material, partIndex);


    // Release the material since we now have a reference to it
    // material->release();

    return material;
}

C3DMaterial* C3DModel::setDefaultMaterial(const std::string& path,int partIndex)
{
    // Try to create a C3DMaterial from the specified material file.
	std::string materialPath = path + "material"+ "/" + _defaultMaterialName;
	C3DMaterial* material = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->getResource(materialPath));
	if(material == NULL)
	{
		material = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->createResource(materialPath));			
	}	

    if (material == NULL)
    {
        return NULL;
    }

    // Assign the material to us
    setMaterial(material, partIndex);


    // Release the material since we now have a reference to it
    // material->release();

    return material;
}

bool C3DModel::removeMaterial(int partIndex)
{
	assert(partIndex == -1 || (partIndex >= 0 && partIndex < (int)getMeshPartCount()));

	if (partIndex == -1)
	{
		SAFE_RELEASE(_material);
		return true;
	}
	else if (partIndex >= 0 && partIndex < (int)getMeshPartCount())
	{
		validatePartCount();

		if (_partMaterials)
		{
			SAFE_RELEASE(_partMaterials[partIndex]);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool C3DModel::hasMaterial(unsigned int partIndex) const
{
    return (partIndex < _partCount && _partMaterials && _partMaterials[partIndex]);
}

void C3DModel::draw()
{
	unsigned int partCount = _mesh->getPartCount();
    bool bStatEnable = C3DStat::getInstance()->isStatEnable();
    
    C3DMaterial::TechniqueUsage techUsage = 
        _node->getScene()->isInShadowPass() ? C3DMaterial::TECH_USAGE_SHADOWMAP : C3DMaterial::TECH_USAGE_SCREEN;

    if (partCount == 0)
    {
        // No mesh parts (index buffers).
        if (_material)
        {
            C3DTechnique* technique = _material->getTechnique(techUsage);
            unsigned int passCount = technique->getPassCount();
            if (bStatEnable)
                C3DStat::getInstance()->incDrawCall(passCount);
            for (unsigned int i = 0; i < passCount; ++i)
            {
                if (bStatEnable)
                    C3DStat::getInstance()->incTriangleDraw(_mesh->getTriangleCount());
                
                C3DPass* pass = technique->getPass(i);
                //applyLightParam(pass);
                //applyShadowMap(pass);
				applyInternalParam(pass);
                pass->bind();
                GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );  
				if (_wireframe && (_mesh->getPrimitiveType() == GL_TRIANGLES || _mesh->getPrimitiveType() == GL_TRIANGLE_STRIP))
				{
					unsigned int vertexCount = _mesh->getVertexCount();
					for (unsigned int j = 0; j < vertexCount; j += 3)
					{
						GL_ASSERT( glDrawArrays(GL_LINE_LOOP, j, 3) );
					}
				}
				else
				{
					GL_ASSERT( glDrawArrays(_mesh->getPrimitiveType(), 0, _mesh->getVertexCount()) );
				}
                
                pass->unbind();
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < partCount; ++i)
        {
            MeshPart* meshPart = _mesh->getPart(i);

            // Get the material for this mesh part.
            C3DMaterial* material = getMaterial(i);
            if (material)
            {
                C3DTechnique* technique = material->getTechnique(techUsage);
                unsigned int passCount = technique->getPassCount();
                if (bStatEnable)
                    C3DStat::getInstance()->incDrawCall(passCount);
                
                for (unsigned int j = 0; j < passCount; ++j)
                {
                    if (bStatEnable)
                        C3DStat::getInstance()->incTriangleDraw(meshPart->getTriangleCount());
                    
                    C3DPass* pass = technique->getPass(j);
                    //applyLightParam(pass);
                    //applyShadowMap(pass);
					applyInternalParam(pass);
                    pass->bind();
                    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->_indexBuffer) );                    
                    
                    GL_ASSERT( glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0) );
                    
                    pass->unbind();
                }
            }
        }
    }

}

Morph* C3DModel::getMorph()
{
	return _morph;
}

void C3DModel::setMorph(Morph* morph)
{
	if(_morph != morph)
	{
		SAFE_DELETE(_morph);

		_morph = morph;
	}
}


void C3DModel::pushMorph(int morphTargetIndex,float weight)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		_mesh->pushMorph(_morph,morphTargetIndex,weight);
	}
}

void C3DModel::popMorph(int morphTargetIndex)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		_mesh->popMorph(_morph,morphTargetIndex);
	}
}

void C3DModel::changeMorph(int morphTargetIndex,float weight)
{
	if(_mesh!=NULL && _morph!=NULL)
	{
		_mesh->changeMorph(_morph,morphTargetIndex,weight);
	}

}

C3DNode* C3DModel::getNode() const
{
    return _node;
}

void C3DModel::setNode(C3DNode* node)
{
    _node = node;

    // Re-bind node related material parameters
    if (node)
    {
        if (_material)
        {
           setMaterialNodeBinding(_material);
        }
        if (_partMaterials)
        {
            for (unsigned int i = 0; i < _partCount; ++i)
            {
                if (_partMaterials[i])
                {
                    setMaterialNodeBinding(_partMaterials[i]);
                }
            }
        }
    }
}


void C3DModel::validatePartCount()
{
    unsigned int partCount = _mesh->getPartCount();

    if (_partCount != partCount)
    {
        // Allocate new arrays and copy old items to them.
        if (_partMaterials)
        {
            C3DMaterial** oldArray = _partMaterials;
            _partMaterials = new C3DMaterial*[partCount];
            memset(_partMaterials, 0, sizeof(C3DMaterial*) * partCount);
            for (unsigned int i = 0; i < _partCount; ++i)
            {
                _partMaterials[i] = oldArray[i];
            }
            SAFE_DELETE_ARRAY(oldArray);
        }

        // Update local part count.
        _partCount = _mesh->getPartCount();
    }
}



void C3DModel::setMaterialNodeBinding(C3DMaterial *material)
{
    if (_node)
    {
        material->setNodeAutoBinding(_node);

        unsigned int techniqueCount = material->getTechniqueCount();
        for (unsigned int i = 0; i < techniqueCount; ++i)
        {
            C3DTechnique* technique = material->getTechnique(i);
            
            technique->setNodeAutoBinding(_node);

            unsigned int passCount = technique->getPassCount();
            for (unsigned int j = 0; j < passCount; ++j)
            {
                C3DPass* pass = technique->getPass(j);

                pass->setNodeAutoBinding(_node);
            }
        }
    }
}

void C3DModel::applyInternalParam(C3DPass* pass)
{
	applyLightParam(pass);
	applyShadowMap(pass);
	applyFogParam(pass);
}

void C3DModel::applyFogParam(C3DPass* pass)
{
	if (_node == NULL || _node->getScene() == NULL)
		return;

	const C3DEnvConf& env = _node->getScene()->getLayer()->getEnvConf();
	pass->getParameter("u_fogcolor")->setValue(env._fogColor);
	C3DVector4 fogparam(env._fogDensity, env._fogStart, env._fogEnd, (float)((int)env._fogType));
	pass->getParameter("u_fogparam")->setValue(fogparam);
}
    
void C3DModel::applyLightParam(C3DPass* pass)
{
    if (_node == NULL)
        return;
    
    int nDirlight = 0, nPointlight = 0, nSpotlight = 0, nAnimlight = 0;
    int nMaxDirLight = pass->getMaxDirLight();
    int nMaxPointLight = pass->getMaxPointLight();
    int nMaxSpotLight = pass->getMaxSpotLight();
	int nMaxAnimLight = pass->getMaxAnimLight();

    char paraName[128];
    int i;
    for (i = 0; i < _node->getScene()->getLightCount(); i++) {
        C3DLight* light = _node->getScene()->getLight(i);
		if (!light->isLightEnable())
			continue;
		C3DLightComponent* lightComp = light->getComponent();
		if (!lightComp)
			continue;

        if (s_lightFilter == NULL || (s_lightFilter && s_lightFilter->isLightValidate(this, light)))
        {
            C3DLight::Type type = light->getLightType();
            C3DPointLight* pPointLight = NULL;
			C3DDirectionalLight* pDirLight = NULL;
			C3DSpotLight* pSpotLight = NULL;
			C3DAnimatedLight* pAnimLight = NULL;
			C3DVector3 upVector, rightVector;
			C3DVector3 posVector;

			switch (type) {
                case C3DLight::DIRECTIONAL:
                    if (nDirlight >= nMaxDirLight)
                        break;
					pDirLight = static_cast<C3DDirectionalLight*> (lightComp);
                    sprintf(paraName, "u_dirlight[%d].dir", nDirlight);
                    pass->getParameter(paraName)->setValue(light->getForwardVectorWorld());
                    sprintf(paraName, "u_dirlight[%d].color", nDirlight);
                    pass->getParameter(paraName)->setValue(pDirLight->getColor());
                    nDirlight++;
                    break;
                    
                case C3DLight::POINT:
                    if (nPointlight >= nMaxPointLight)
                        break;
					pPointLight = static_cast<C3DPointLight*> (lightComp);

                    sprintf(paraName, "u_pointlight[%d].position", nPointlight);                    
                    //pass->getParameter(paraName)->setValue(light->getTranslationView());
					pass->getParameter(paraName)->setValue(light->getTranslationWorld());
                    sprintf(paraName, "u_pointlight[%d].color", nPointlight);
                    pass->getParameter(paraName)->setValue(pPointLight->getColor());
                    sprintf(paraName, "u_pointlight[%d].rangeInverse", nPointlight);
                    pass->getParameter(paraName)->setValue(pPointLight->getRangeInverse());
                    nPointlight++;

                    break;
                    
                case C3DLight::SPOT:
                    if (nSpotlight >= nMaxSpotLight)
                        break;
					pSpotLight = static_cast<C3DSpotLight*> (lightComp);

                    sprintf(paraName, "u_spotlight[%d].position", nSpotlight);
                    pass->getParameter(paraName)->setValue(light->getTranslationView());
                    sprintf(paraName, "u_spotlight[%d].color", nSpotlight);
                    pass->getParameter(paraName)->setValue(pSpotLight->getColor());
                    sprintf(paraName, "u_spotlight[%d].rangeInverse", nSpotlight);
                    pass->getParameter(paraName)->setValue(pSpotLight->getRangeInverse());
                    sprintf(paraName, "u_spotlight[%d].dir", nSpotlight);
                    pass->getParameter(paraName)->setValue(light->getForwardVectorView());
                    sprintf(paraName, "u_spotlight[%d].innerAngleCos", nSpotlight);
                    pass->getParameter(paraName)->setValue(pSpotLight->getInnerAngleCos());
                    sprintf(paraName, "u_spotlight[%d].outerAngleCos", nSpotlight);
                    pass->getParameter(paraName)->setValue(pSpotLight->getOuterAngleCos());
                    nSpotlight++;

                    break;

				case C3DLight::ANIMATE:
					if (nAnimlight >= min(nMaxAnimLight, 1)) // no more than one animated light allowed
						break;
					pAnimLight = static_cast<C3DAnimatedLight*> (lightComp);

					light->getWorldMatrix().getRightVector(&rightVector);
					light->getWorldMatrix().getUpVector(&upVector);
					light->getWorldMatrix().getPosition(&posVector);

					sprintf(paraName, "u_animLightAxisU");
					pass->getParameter(paraName)->setValue(rightVector);
					sprintf(paraName, "u_animLightAxisV");
					pass->getParameter(paraName)->setValue(upVector);
					sprintf(paraName, "u_animLightPos");
					pass->getParameter(paraName)->setValue(posVector);

					sprintf(paraName, "u_animLightTexOffset");
					pass->getParameter(paraName)->setValue(pAnimLight->getUVOffset());
					sprintf(paraName, "u_animLightTexRotScale1");
					pass->getParameter(paraName)->setValue(pAnimLight->getUV1RotScale());
					sprintf(paraName, "u_animLightTexRotScale2");
					pass->getParameter(paraName)->setValue(pAnimLight->getUV2RotScale());
					
					sprintf(paraName, "u_animLightIntensity");
					pass->getParameter(paraName)->setValue(pAnimLight->getIntensity());
					sprintf(paraName, "u_lightTexture");
					pass->getParameter(paraName)->setValue(pAnimLight->getSampler());

					nAnimlight++;

					break;
                    
                default:
                    break;
            }
        }
    }
    
    if (nMaxDirLight > 0)
        pass->getParameter("u_ndirlight")->setValue(nDirlight);
    if (nMaxPointLight > 0)
        pass->getParameter("u_npointlight")->setValue(nPointlight);
    if (nMaxSpotLight > 0)
        pass->getParameter("u_nspotlight")->setValue(nSpotlight);
	if (nMaxAnimLight > 0)
		pass->getParameter("u_nanimlight")->setValue(nAnimlight);
}

void C3DModel::applyShadowMap(C3DPass* pass)
{
    if (_node == NULL)
        return;

    int nMaxShadowMap = pass->getMaxShadowMap();

    if (nMaxShadowMap <= 0)
        return;

    C3DShadowMap* shadowMap = _node->getScene()->getActiveShadowMap();
    if (!shadowMap || !shadowMap->active())
        return;

    pass->getParameter("u_shadowMatrix")->setValue(shadowMap->getTextureMatrix());
    pass->getParameter("u_shadowTexture")->setValue(shadowMap->getSampler());
}

void C3DModel::copyFrom(const C3DModel* other)
{
	//other->_mesh->retain();
	//SAFE_RELEASE(_mesh);
	//_mesh = other->_mesh;
	_partCount = other->_partCount;

	//C3DMaterial* newMaterial = other->_material ? other->_material->clone() : NULL;
	
	C3DMaterial* newMaterial = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->getResource(other->_material->getName()));
		

	setMaterial(newMaterial, -1);

	if (other->_partMaterials)
	{
		for (unsigned int i = 0; i < _partCount; i++)
		{
			newMaterial = other->_partMaterials[i] ? other->_partMaterials[i]->clone() : NULL;
			setMaterial(newMaterial, i);
		}
	}
	
	setMorph(other->_morph);
	setNode(other->_node);
	
}

C3DModel* C3DModel::clone(C3DNode::CloneContext& context) const
{
	C3DModel* other = new C3DModel(_mesh);
	other->copyFrom(this);
	return other;
}

void C3DModel::setDefaultMaterialName(const std::string& matName)
{
	_defaultMaterialName = matName;
}

}

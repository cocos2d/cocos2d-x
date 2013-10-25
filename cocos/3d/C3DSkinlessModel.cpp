#include "C3DSkinlessModel.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DMaterial.h"
#include "C3DStat.h"

namespace cocos3d
{

C3DSkinlessModel::C3DSkinlessModel(C3DMesh* mesh) :C3DModel(mesh)   
{
	
}

C3DSkinlessModel::~C3DSkinlessModel()
{ 


}

C3DModel* C3DSkinlessModel::create(C3DMesh* mesh)
{   
    return new C3DSkinlessModel(mesh);
}

void C3DSkinlessModel::draw()
{
    unsigned int partCount = _mesh->getPartCount();
    bool bStatEnable = C3DStat::getInstance()->isStatEnable();
    
    C3DMaterial::TechniqueUsage techUsage = 
        getNode()->getScene()->isInShadowPass() ? C3DMaterial::TECH_USAGE_SHADOWMAP : C3DMaterial::TECH_USAGE_SCREEN;

    if (partCount == 0)
    {
        // No mesh parts (index buffers).
        if (_material)
        {
            C3DTechnique* technique = _material->getTechnique(techUsage);
            
            if (!technique)
                return;
            
            unsigned int passCount = technique->getPassCount();
            if (bStatEnable)
                C3DStat::getInstance()->incDrawCall(passCount);
            
            for (unsigned int i = 0; i < passCount; ++i)
            {
                if (bStatEnable)
                    C3DStat::getInstance()->incTriangleDraw(_mesh->getTriangleCount());
                
                C3DPass* pass = technique->getPass(i);
                //applyLightParam(pass);
				applyInternalParam(pass);
                pass->bind();
                GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );               
                
                GL_ASSERT( glDrawArrays(_mesh->getPrimitiveType(), 0, _mesh->getVertexCount()) );
                
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
                C3DTechnique* technique = _material->getTechnique(techUsage);
                
                if (!technique)
                    continue;
                unsigned int passCount = technique->getPassCount();
                
                if (bStatEnable)
                    C3DStat::getInstance()->incDrawCall(passCount);
                
                for (unsigned int j = 0; j < passCount; ++j)
                {
                    if (bStatEnable)
                        C3DStat::getInstance()->incTriangleDraw(meshPart->getTriangleCount());
                    
                    C3DPass* pass = technique->getPass(j);
					applyInternalParam(pass);
                    //applyLightParam(pass);
                    //applyShadowMap(pass);

                    pass->bind();
                    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->_indexBuffer) );                    
                    
                    GL_ASSERT( glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0) );
                    
                    pass->unbind();
                }
            }
        }
    }
}

C3DModel* C3DSkinlessModel::clone(C3DNode::CloneContext& context) const
{
	C3DSkinlessModel* other = new C3DSkinlessModel(_mesh);
	other->copyFrom(this);
	other->autorelease();
	return other;
}






}

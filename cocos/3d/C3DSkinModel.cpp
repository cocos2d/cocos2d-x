#include "C3DSkinModel.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DMeshSkin.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DMaterial.h"
#include "BonePart.h"
#include "C3DRenderSystem.h"

namespace cocos2d
{

C3DSkinModel::C3DSkinModel(C3DMesh* mesh) :C3DModel(mesh),_skin(nullptr)
{
    
}


C3DSkinModel::~C3DSkinModel()
{
    SAFE_DELETE(_skin);
}

C3DModel* C3DSkinModel::create(C3DMesh* mesh)
{
    return new C3DSkinModel(mesh);
}

C3DMeshSkin* C3DSkinModel::getSkin()
{
    return _skin;
}

void C3DSkinModel::setSkin(C3DMeshSkin* skin)
{
    if (_skin != skin)
    {
        // Free the old skin
        SAFE_DELETE(_skin);

        // Assign the new skin
        _skin = skin;
        if (_skin)
            _skin->_model = this;
    }
}





void C3DSkinModel::draw()
{
     
    unsigned int partCount = _mesh->getPartCount();
    if (partCount == 0)
    {
        // No mesh parts (index buffers).
        if (_material)
        {
            C3DTechnique* technique = _material->getTechnique();
            
            if (!technique)
                return;
            
            
            unsigned int passCount = technique->getPassCount();
           
            for (unsigned int i = 0; i < passCount; ++i)
            {               
                
                C3DPass* pass = technique->getPass(i);
                //applyLightParam(pass);
                //applyShadowMap(pass);

                pass->bind();
                GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );

                if (_wireframe && (_mesh->getPrimitiveType() == PrimitiveType_TRIANGLES || _mesh->getPrimitiveType() == PrimitiveType_TRIANGLE_STRIP))
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
                C3DTechnique* technique = material->getTechnique();
                
                if (!technique)
                    continue;
                                
                unsigned int passCount = technique->getPassCount();
                
                for (unsigned int j = 0; j < passCount; ++j)
                {                   
                    
                    C3DPass* pass = technique->getPass(j);
                    //applyLightParam(pass);
                    //applyShadowMap(pass);

                    pass->bind();
                    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->_indexBuffer) );
                    
                    C3DMeshSkin * skin = this->getSkin();
                    if(skin != NULL)
                    {
                        BonePart** parts = skin->_parts;                                                                                                                                                                                                                                                                                                                                                                           
                       
                        for (unsigned int iBonePart=0; iBonePart < skin->_partCount; iBonePart++)
                        {
                            BonePart* bonePart = parts[iBonePart];
                            skin->setBonePartIndex(iBonePart);
                            pass->setParamMethonAutoUniform();

                            if (_wireframe && (_mesh->getPrimitiveType() == PrimitiveType_TRIANGLES || _mesh->getPrimitiveType() == PrimitiveType_TRIANGLE_STRIP))
                            {
                                unsigned int indexCount = bonePart->_numVertexIndex;
                                unsigned int indexSize = 0;
                                switch (meshPart->getIndexFormat())
                                {
                                case IndexFormat_INDEX8:
                                    indexSize = 1;
                                    break;
                                case IndexFormat_INDEX16:
                                    indexSize = 2;
                                    break;
                                case IndexFormat_INDEX32:
                                    indexSize = 4;
                                    break;
                                }

                                for (unsigned int k = 0; k < indexCount; k += 3)
                                {
                                    GL_ASSERT( glDrawElements(GL_LINE_LOOP, 3, meshPart->getIndexFormat(), ((const GLvoid*)(k*indexSize))) );
                                }
                            }
                            else
                            {
                                GL_ASSERT( glDrawElements(meshPart->getPrimitiveType(),bonePart->_numVertexIndex , meshPart->getIndexFormat(), &((const GLushort*)0)[bonePart->_offsetVertexIndex]));
                            }
                            
                        }

                    }                   
                    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
                    pass->unbind();
                }
            }
        }
    }
}


C3DSkinModel* C3DSkinModel::clone(C3DNode::CloneContext& context) const
{
    C3DSkinModel* model = new C3DSkinModel(getMesh());
    
    model->copyFrom(this);
    
    C3DMeshSkin *skin = new C3DMeshSkin();
    
    skin->copyFrom(_skin, context);
    
    model->setSkin(skin);
    
    model->autorelease();
    
    return model;
}

}

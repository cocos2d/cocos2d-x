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

#include "C3DVertexDeclaration.h"

#include "MaterialParameter.h"

#include "C3DMaterialManager.h"
#include "C3DRenderSystem.h"

namespace cocos2d
{

C3DModel::C3DModel(C3DMesh* mesh) :
    _mesh(mesh), _material(nullptr), _partCount(0), _partMaterials(nullptr), _node(nullptr), _wireframe(false)
{
     mesh->retain();
    _morph = nullptr;
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

    C3DMaterial* m = nullptr;

    if (partIndex >= 0 && partIndex < (int)_partCount)
    {
        // Look up explicitly specified part material.
        if (_partMaterials)
        {
            m = _partMaterials[partIndex];
        }
    }

    if (m == nullptr)
    {
        // Return the shared material.
         m = _material;
    }

    return m;
}

void C3DModel::setMaterial(C3DMaterial* material, int partIndex)
{
    assert(partIndex == -1 || (partIndex >= 0 && partIndex < (int)getMeshPartCount()));

    C3DMaterial* oldMaterial = nullptr;

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
            if (_partMaterials == nullptr)
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
                t->getPass(j)->setVertexAttributeBinding(nullptr);
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
    if (material == nullptr)
    {
        return nullptr;
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
    
    if (material == nullptr)
    {
        return nullptr;
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
    
    if (material == nullptr)
    {
        return nullptr;
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
        

    if ( partCount == 0 )
    {
        // No mesh parts (index buffers).
        if (_material)
        {
            C3DTechnique* technique = _material->getTechnique();
    
            unsigned int passCount = technique->getPassCount();
            
            for (unsigned int i = 0; i < passCount; ++i)
            {                

                C3DPass* pass = technique->getPass(i);
                
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
        for ( int i = 0; i < partCount; ++i )
        {
            //channelDrawPart( i );            

            C3DMaterial* material = getMaterial(i);
            MeshPart* meshPart = _mesh->getPart(i);

            if (material)
            {
                C3DTechnique* technique = material->getTechnique();
                unsigned int passCount = technique->getPassCount();


                for (unsigned int j = 0; j < passCount; ++j)
                {
                    C3DPass* pass = technique->getPass(j);            

                    pass->bind();
                    GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshPart->getIndexBuffer()) );                    

                    GL_ASSERT( glDrawElements(meshPart->getPrimitiveType(), meshPart->getIndexCount(), meshPart->getIndexFormat(), 0) );

                    pass->unbind();
                }
            }
        }
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


void C3DModel::copyFrom(const C3DModel* other)
{    
    _partCount = other->_partCount;    
    
    C3DMaterial* newMaterial = static_cast<C3DMaterial*>(C3DMaterialManager::getInstance()->getResource(other->_material->getID()));
        

    setMaterial(newMaterial, -1);

    if (other->_partMaterials)
    {
        for (unsigned int i = 0; i < _partCount; i++)
        {
            newMaterial = other->_partMaterials[i] ? other->_partMaterials[i]->clone() : NULL;
            setMaterial(newMaterial, i);
        }
    }
    

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

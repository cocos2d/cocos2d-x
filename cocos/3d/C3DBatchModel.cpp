#include "Base.h"
#include "C3DBatchModel.h"
#include "C3DBatchMesh.h"

#include "C3DScene.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "C3DMaterial.h"
#include "C3DVertexFormat.h"

#include "C3DVertexDeclaration.h"
#include "C3DNode.h"

namespace cocos3d
{

C3DMaterial* createBBMaterial()
{
    // Vertex shader for drawing colored lines.
    const char* vs_str = 
    {
        "uniform mat4 u_viewProjectionMatrix;\n"
        "attribute vec4 a_position;\n"
        "attribute vec4 a_color;\n"
        "varying vec4 v_color;\n"
        "void main(void) {\n"
        "    v_color = a_color;\n"
        "    gl_Position = u_viewProjectionMatrix * a_position;\n"
        "}"
    };

    // Fragment shader for drawing colored lines.
    const char* fs_str = 
    {
    #ifdef OPENGL_ES
        "precision highp float;\n"
    #endif
        "varying vec4 v_color;\n"
        "void main(void) {\n"
        "   gl_FragColor = v_color;\n"
        "}"
    };

	
    C3DMaterial* material = C3DMaterial::create("shaders/debug.vsh", "shaders/debug.fsh");

    material->getStateBlock()->setDepthTest(true);
	
    return material;
}

C3DBatchModel* C3DBatchModel::createDebugModel(C3DNode* node)
{
	C3DBatchModel* model = new C3DBatchModel(node);
			
	C3DVertexElement elements[] =
	{
		C3DVertexElement(Vertex_Usage_POSITION, 3),
		C3DVertexElement(Vertex_Usage_COLOR, 4)
    };
    C3DVertexFormat v = C3DVertexFormat(elements, 2);
    C3DBatchMesh* mesh = new C3DBatchMesh(&v, PrimitiveType_LINES);
		
    model->_mesh = mesh;
	C3DMaterial* material = C3DMaterial::create("shaders/debug.vsh", "shaders/debug.fsh");
	model->setMaterial(material);

	
	
	return model;
		
}

C3DBatchModel::C3DBatchModel(C3DNode* node)   
{
   /* C3DVertexElement elements[] =
    {
        C3DVertexElement(Vertex_Usage_POSITION, 3),
        C3DVertexElement(Vertex_Usage_COLOR, 4)
    };
    C3DVertexFormat v = C3DVertexFormat(elements, 2);
    _mesh = new C3DBatchMesh(&v, PrimitiveType_LINES);
	this->setMaterial(createBBMaterial());    */
	_material = NULL;
	_mesh = NULL;

	_node = node;


}

C3DBatchModel::~C3DBatchModel()
{
    SAFE_RELEASE(_material);
	   
    SAFE_DELETE(_mesh); 
	_node = NULL;

}


C3DBatchMesh* C3DBatchModel::getMesh() const
{
    return _mesh;
}

void C3DBatchModel::setMesh(C3DBatchMesh* mesh)
{
	_mesh = mesh;
}

C3DMaterial* C3DBatchModel::getMaterial()
{  
    return _material;
}

void C3DBatchModel::setMaterialNodeBinding(C3DMaterial *material)
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

void C3DBatchModel::setMaterial(C3DMaterial* material)
{
	if (material != _material)
	{
		SAFE_RELEASE(_material);
		if (material)
		{
			_material = material;
			material->retain();
		}
	}
	if (_material)
	{
		for (unsigned int i = 0, tCount = material->getTechniqueCount(); i < tCount; ++i)
		{
			C3DTechnique* t = material->getTechnique(i);
			for (unsigned int j = 0, pCount = t->getPassCount(); j < pCount; ++j)
			{
				C3DPass* p = t->getPass(j);
				C3DVertexDeclaration* b = C3DVertexDeclaration::create(_mesh->_vertexFormat,_mesh->_vertices, p->getEffect());
				p->setVertexAttributeBinding(b);
				SAFE_RELEASE(b);
			}
		}
	}

	// Apply node binding for the new material.
	if (_node)
	{
		setMaterialNodeBinding(_material);
	}
}

void C3DBatchModel::begin()
{
	_mesh->begin();
}

void C3DBatchModel::end()
{
	_mesh->end();
}


void C3DBatchModel::draw()
{
    if ( _mesh->_vertexCount == 0 )
        return;    

    // Bind the material
    C3DTechnique* technique = _material->getTechnique(C3DMaterial::TECH_USAGE_SCREEN);
    unsigned int passCount = technique->getPassCount();
    for (unsigned int i = 0; i < passCount; ++i)
    {
        C3DPass* pass = technique->getPass(i);
        pass->bind();

			//GLint currentTextureId;
      //  glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTextureId);  

	   // glDisable(GL_DEPTH_TEST);
		//glEnable(GL_BLEND);
	   // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 ) );
        if (_mesh->_bUseIndex)
        {
            GL_ASSERT( glDrawElements(_mesh->_primitiveType, _mesh->_indexCount, GL_UNSIGNED_SHORT, _mesh->_indices));
        }
        else
        {
            GL_ASSERT( glDrawArrays(_mesh->_primitiveType, 0, _mesh->_vertexCount) );
        }

        pass->unbind();
    }
}

}

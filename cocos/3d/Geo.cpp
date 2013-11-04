#include "Base.h"
#include "Geo.h"
#include "C3DMesh.h"
#include "C3DVector4.h"

#include "C3DVertexFormat.h"
#include "Vertex.h"
namespace cocos3d
{



C3DMesh* Geo::createBoard(float x, float y, float width, float height)
{
    float x2 = x + width;
    float y2 = y + height;

	float vertices[] =
    {
        x, y,   0,  0, 0, 1,  0, 1,//lb
        x, y2,  0,  0, 0, 1,  0, 0,//lt
        x2, y,  0,  0, 0, 1,  1, 1,//rb
        x2, y2, 0,  0, 0, 1,  1, 0 //rt
    };

    C3DVertexElement elements[] =
    {
        C3DVertexElement(Vertex_Usage_POSITION, 3),
        C3DVertexElement(Vertex_Usage_NORMAL, 3),
        C3DVertexElement(Vertex_Usage_TEXCOORD0, 2)
    };
	C3DVertexFormat vf(elements, 3);
    C3DMesh* mesh = C3DMesh::createMesh(&vf, 4, false);
    if (mesh == NULL)
    {
        return NULL;
    }

    mesh->_primitiveType = PrimitiveType_TRIANGLE_STRIP;
    mesh->setVertexData(vertices, 0, 4);

    return mesh;
}


C3DMesh* Geo::createQuadFullscreen()
{
	float x = -1.0f;
	float y = -1.0f;
	float x2 = 1.0f;
	float y2 = 1.0f;
        
	float vertices[] =
	{
		x, y2,   0, 1,
		x, y,    0, 0,
		x2, y2,  1, 1,
		x2, y,   1, 0
	};
        
	C3DVertexElement elements[] =
	{
		C3DVertexElement(Vertex_Usage_POSITION, 2),
		C3DVertexElement(Vertex_Usage_TEXCOORD0, 2)
	};
	C3DVertexFormat vertformat(elements, 2);
        
	C3DMesh* mesh = C3DMesh::createMesh(&vertformat, 4);
	mesh->setPrimitiveType(PrimitiveType_TRIANGLE_STRIP);
	mesh->setVertexData(vertices, 0, 4);

    return mesh;
}

bool Geo::CreateSphere(float radius, std::vector< BBVertex > &ppVertices, std::vector< unsigned short > &ppIndices, const C3DVector4& color, int stacks, int slices)
{
	//*ppVertices = NULL;
	//*ppIndices = NULL;

	int base = ppVertices.size();

	int num_vertices = (stacks+1)*(slices+1);
	int num_triangles = stacks*slices*2;

	/*Vertex_VC *pVertices = new Vertex_VC[num_vertices];
	if ( pVertices==NULL )
		return false;

	unsigned short *pIndices = new unsigned short[num_triangles*3];
	if ( pIndices==NULL )
	{
		delete [] pVertices;
		return false;
	}

	*ppVertices = pVertices;
	*ppIndices = pIndices;

	g_iNumSphereVertices = num_vertices;
	g_iNumSphereTriangles = num_triangles;
	g_iNumSphereIndices = num_triangles * 3;*/

	//float default_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//C3DVector4 default_color(1.0f, 1.0f, 1.0f, 1.0f);
	//if ( color==NULL )
	//	color = default_color;

	const float theta_start_degree = 0.0f;
	const float theta_end_degree = 360.0f;
	const float phi_start_degree = -90.0f;
	const float phi_end_degree = 90.0f;

	float ts = /*FastMath::DegreeToRadian*/CC_DEGREES_TO_RADIANS(theta_start_degree);
	float te = /*FastMath::DegreeToRadian*/CC_DEGREES_TO_RADIANS(theta_end_degree);
	float ps = /*FastMath::DegreeToRadian*/CC_DEGREES_TO_RADIANS(phi_start_degree);
	float pe = /*FastMath::DegreeToRadian*/CC_DEGREES_TO_RADIANS(phi_end_degree);

	float theta_total = te - ts;
	float phi_total = pe - ps;
	float theta_inc = theta_total/stacks;
	float phi_inc = phi_total/slices;

	int i,j;
	float theta = ts;

	float sin_theta, cos_theta;
	float sin_phi, cos_phi;

 	BBVertex pVertices;
	for ( i=0; i<=stacks; i++ )
	{
		float phi = ps;
		/*FastMath::*///SinCos(theta, sin_theta, cos_theta);
		//C3DUtility::getInstance().sincos(theta, &sin_theta, &cos_theta);
		sin_theta = sin(theta);
		cos_theta = cos(theta);
		for ( j=0; j<=slices; j++ )
		{
			sin_phi = sin(phi);
			cos_phi = cos(phi);
			/*FastMath::*///SinCos(phi, sin_phi, cos_phi);
			//C3DUtility::getInstance().sincos(phi, &sin_phi, &cos_phi);
			
			// vertex
			//pVertices[index].m_Position[0] = radius * cos_phi * cos_theta;
			//pVertices[index].m_Position[1] = radius * sin_phi;
			//pVertices[index].m_Position[2] = radius * cos_phi * sin_theta;
			pVertices.position.x = radius * cos_phi * cos_theta;
			pVertices.position.y = radius * sin_phi;
			pVertices.position.z = radius * cos_phi * sin_theta;

			// Color
			//float shading = (float) j / (float) slices;
			////float shading = 1.0f;
			//pVertices[index].m_RGBA[0] = 255 * color[0] * shading;
			//pVertices[index].m_RGBA[1] = 255 * color[1] * shading;
			//pVertices[index].m_RGBA[2] = 255 * color[2] * shading;
			//pVertices[index].m_RGBA[3] = 255 * color[3] * shading;

			pVertices.color = color;
			ppVertices.push_back(pVertices);

			// inc phi
			phi += phi_inc;
		}
		// inc theta
		theta += theta_inc;
	}

	// triangle list
	for ( i=0; i<stacks; i++ )
	{
		for ( j=0; j<slices; j++ )
		{
			/*pIndices[index++] = base;
			pIndices[index++] = base+1;
			pIndices[index++] = base+slices+1;

			pIndices[index++] = base+1;
			pIndices[index++] = base+slices+2;
			pIndices[index++] = base+slices+1;*/
			ppIndices.push_back(base);
			ppIndices.push_back(base + 1);
			ppIndices.push_back(base+slices+1);

			ppIndices.push_back(base+1);
			ppIndices.push_back(base+slices+2);
			ppIndices.push_back(base+slices+1);
			base++;
		}
		base++;
	}

	return true;
}


}
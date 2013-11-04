#ifndef VERTEX_H_
#define VERTEX_H_

#include "C3DVector3.h"
#include "C3DVector4.h"

namespace cocos3d
{

class BBVertex
{  
public:
	C3DVector3 position;
	C3DVector4 color; 

	BBVertex()
	{
		color.x = 1.0f;    
		color.y = 0.0f;
		color.z = 0.0f;
		color.w = 1.0f;
	}
};
    
//vertex with color and u, v
struct VertexColorCoord1
{
    C3DVector3 position;
    C3DVector4 color;
    
    float u;
    float v;
    VertexColorCoord1():color(1.0f, 1.0f, 1.0f, 1.0f), u(0.0f), v(0.0f)
    {
        
    }
};

}



#endif

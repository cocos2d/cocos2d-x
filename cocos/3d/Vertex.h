#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace cocos2d
{

class BBVertex
{  
public:
    Vector3 position;
    Vector4 color; 

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
    Vector3 position;
    Vector4 color;
    
    float u;
    float v;
    VertexColorCoord1():color(1.0f, 1.0f, 1.0f, 1.0f), u(0.0f), v(0.0f)
    {
        
    }
};

struct VertexPositionUV
{
    Vector3 position;
    Vector2 uv;
    VertexPositionUV(void):position(Vector3::zero()), uv(Vector2::zero())
    {
    }
};

struct VertexPosition2UV
{
    Vector2 position;
    Vector2 uv;

    VertexPosition2UV():position(Vector2::zero()),uv(Vector2::zero())
    {

    }
};



}



#endif

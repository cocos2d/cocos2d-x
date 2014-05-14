
static const char* baseVertexShader = STRINGIFY(

attribute vec4 a_position;
attribute vec2 a_texCoord;

uniform vec3 DiffuseMaterial;
uniform mat3 NormalMatrix;

varying vec2 TextureCoordOut;

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    TextureCoordOut = a_texCoord;
    TextureCoordOut.y = 1.0 - TextureCoordOut.y;
}
);


// pure black vert shader
static const char* outLineShader = STRINGIFY(
                                                
attribute vec4 a_position;
attribute vec3 a_normal;
uniform float OutlineWidth;

void main(void)
{
    vec4 pos = a_position;
    vec3 normal = a_normal;
    pos.xyz += a_normal * OutlineWidth;
    gl_Position = CC_MVPMatrix * pos;
}
);
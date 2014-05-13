
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


// test my sprite
static const char* myspritevs = STRINGIFY(
                                             
attribute vec3 a_position;
attribute vec3 a_color;
attribute float a_transparent;
uniform vec4 u_diffcolor;
varying vec4 v_color;
                                             
void main(void)
{
    vec4 pos = vec4(a_position, 1);
    gl_Position = CC_MVPMatrix * pos;
    v_color = vec4(a_color, a_transparent) * u_diffcolor;
}
);

static const char* myspritefs = STRINGIFY(
                                          
#ifdef GL_ES
varying mediump vec4 v_color;
#else
varying vec4 v_color;
#endif
                                          
void main(void)
{
    gl_FragColor = v_color;
}
);

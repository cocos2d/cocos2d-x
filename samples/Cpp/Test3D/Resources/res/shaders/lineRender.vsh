// Attributes
attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

// Uniforms
uniform mat4 u_viewProjectionMatrix;

// Varyings
varying vec2 v_texCoord;
varying vec4 v_color;


void main()
{
    gl_Position = u_viewProjectionMatrix * vec4(a_position, 1);
    v_texCoord = a_texCoord;
    v_color = a_color;
}

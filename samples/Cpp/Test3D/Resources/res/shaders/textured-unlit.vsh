// Attributes
attribute vec4 a_position;									// Vertex Position							(x, y, z, w)
attribute vec2 a_texCoord0;									// Vertex Texture Coordinate				(u, v)



// Uniforms
uniform mat4 u_worldViewProjectionMatrix;					// Matrix to transform a position to clip space


// Varyings
varying vec2 v_texCoord0;									// Texture Coordinate





void main()
{
    // Get the vertex position
    vec4 position = a_position;

    // Transform position to clip space.
    gl_Position = u_worldViewProjectionMatrix * position;

    // Texture transformation.
    v_texCoord0 = a_texCoord0;
  
}

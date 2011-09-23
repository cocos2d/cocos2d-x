

// Attributes
attribute vec4 a_position;
attribute vec2 a_texCoord;

// Varyings
varying vec2 v_texCoord;

void main() 
{
	gl_Position = u_modelViewProjectionMatrix * a_position;
	v_texCoord = a_texCoord;	
}
// Uniforms
uniform mat4 u_worldViewProjectionMatrix;       // Matrix to transform a position to clip space.
uniform float u_time;

// Inputs
attribute vec4 a_position;                      // Vertex Position (x, y, z, w).
attribute vec2 a_texCoord;                      // Vertex Texture Coordinate (u, v).

// Outputs
varying vec2 v_texCoord;                        // Texture coordinate (u, v).
varying vec4 v_color;

void main()
{
    vec4 position = a_position;
	position.x += 0.015 * cos(u_time + (position.z / 0.1));  
	position.y += 0.015 * sin(u_time + (position.z / 0.1));  
	
	float zscale = 1.0 / (max(0.6 - position.z , 0.00001) * 3.0);
	position.x *= zscale;
	position.y *= zscale;

	float ao = position.z / 0.6;
	//float ao1 = 1.0 - smoothstep(0.3, 0.8, position.z);
	//ao = min(ao, ao1);
	v_color = vec4(ao, ao, ao, 1.0);	
	
    // Transform position to clip space.
    gl_Position = u_worldViewProjectionMatrix * position;
    // Pass on texture coordinate to fragment shader.
    v_texCoord.x = a_texCoord.x * 4.0 - u_time * 0.4;
    v_texCoord.y = a_texCoord.y * 4.0 + u_time * 0.4;
}

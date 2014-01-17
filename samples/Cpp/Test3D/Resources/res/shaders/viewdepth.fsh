#ifdef OPENGL_ES
precision highp float;
#endif

uniform sampler2D u_diffuseTexture;     // Diffuse texture

// Inputs
varying vec2 v_texCoord;                // Texture coordinate (u, v).

void main()
{
    vec4 basecolor = texture2D(u_diffuseTexture, vec2(v_texCoord.x, 1.0 - v_texCoord.y));
		
	float f= 1000.0;
	float n = 1.0;
	float z = basecolor.x;// (2.0 * n) / (f + n - basecolor.x * (f - n));
	
	gl_FragColor = vec4(z, z, z, 1.0);
}

#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_texture;

uniform vec3 u_rate;                      // Light color

// Inputs
varying vec2 v_texCoord;

void main()
{
    // Sample the diffuse texture for base color
    float gray = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299, 0.587, 0.114));
    		
    // Play with these rgb weightings to get different tones, but rgb weightings should add up to 1.0 so you won't lighten or darken the image.
	gl_FragColor = vec4(gray * u_rate, 1.0);
}
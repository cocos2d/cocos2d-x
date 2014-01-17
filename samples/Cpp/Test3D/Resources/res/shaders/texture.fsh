#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform vec3 u_ambientColor;                    // Ambient color
uniform sampler2D u_diffuseTexture;             // Diffuse texture.
#if defined(GLOBAL_ALPHA)
uniform float u_globalAlpha;                    // Global alpha value
#endif

// Inputs
varying vec2 v_texCoord;                        // Texture coordinate (u, v).


// Global variables
vec4 _baseColor;                                // Base color
vec3 _ambientColor;                             // Ambient Color


void main()
{
    // Fetch diffuse color from texture.
    _baseColor = texture2D(u_diffuseTexture, v_texCoord);
	   
    // Ambient
    _ambientColor = _baseColor.rgb * u_ambientColor;
              
    // Light the pixel
    gl_FragColor.a = _baseColor.a;
    
    gl_FragColor.rgb = _ambientColor ;

#if defined(GLOBAL_ALPHA)
    gl_FragColor.a *= u_globalAlpha;
#endif
}

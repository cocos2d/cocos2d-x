#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_diffuseTexture;     	// Diffuse texture


// Varyings
varying vec2 v_texCoord0;                	// Texture coordinate(u, v)


void main()
{
    // Sample the texture for the color
    gl_FragColor = texture2D(u_diffuseTexture, v_texCoord0);
   
}

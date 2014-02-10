#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_diffuseTexture;     // Diffuse texture

varying vec2 v_texCoord;                 // Texture coordinate (u, v).
varying vec4 v_color;

void main()
{
    vec4 basecolor = texture2D(u_diffuseTexture, v_texCoord);
    //vec3 illum = pow(basecolor.rgb, vec3(10.0)) * 5.0;
    //basecolor.rgb += illum;
	gl_FragColor = basecolor * v_color;
}

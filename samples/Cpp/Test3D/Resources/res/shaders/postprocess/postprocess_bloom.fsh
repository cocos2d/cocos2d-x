#ifdef OPENGL_ES
precision mediump float;
#endif

// Uniforms
uniform sampler2D u_texture;
uniform sampler2D u_bloomTexture;


// Inputs
varying vec2 v_texCoord;

void main()
{
 
    vec4 bloomcolor = texture2D(u_bloomTexture, v_texCoord);
    vec4 basecolor = texture2D(u_texture, v_texCoord);
    
    basecolor *= (1.0 - bloomcolor);
    
 
    gl_FragColor = basecolor + bloomcolor;
   
}
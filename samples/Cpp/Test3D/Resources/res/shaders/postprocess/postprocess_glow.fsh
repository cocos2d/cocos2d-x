#ifdef OPENGL_ES
precision mediump float;
#endif

// Uniforms
uniform sampler2D u_texture;
uniform sampler2D u_glowTexture;
uniform vec4 u_tintColor;

// Inputs
varying vec2 v_texCoord;

void main()
{
 
    vec4 src = texture2D(u_glowTexture, v_texCoord) * u_tintColor;
    vec4 dst = texture2D(u_texture, v_texCoord);
 
    gl_FragColor = clamp((src + dst) - (src * dst), 0.0, 1.0);
		gl_FragColor.w = 1.0;
   
}
#ifdef OPENGL_ES
precision highp float;
#endif

#ifdef USE_TEXTURE
// Uniforms
uniform sampler2D u_texture;
#endif

// Varyings
varying vec2 v_texCoord;
varying vec4 v_color;


void main()
{
#ifdef USE_TEXTURE
    gl_FragColor = v_color * texture2D(u_texture, v_texCoord);
#else
  gl_FragColor = v_color;

  
#endif
}
#ifdef OPENGL_ES
precision mediump float;
#endif

// Uniforms
uniform sampler2D u_texture;
uniform float u_w;
uniform float u_h;

// Inputs
varying vec2 v_texCoord;

void main() 
{
     
      vec4 n[9];
      n[0] = texture2D(u_texture, v_texCoord + vec2( -u_w, -u_h));
      n[1] = texture2D(u_texture, v_texCoord + vec2(0.0, -u_h));
      n[2] = texture2D(u_texture, v_texCoord + vec2(  u_w, -u_h));
      n[3] = texture2D(u_texture, v_texCoord + vec2( -u_w, 0.0));
      n[4] = texture2D(u_texture, v_texCoord);
      n[5] = texture2D(u_texture, v_texCoord + vec2(  u_w, 0.0));
      n[6] = texture2D(u_texture, v_texCoord + vec2( -u_w, u_h));
      n[7] = texture2D(u_texture, v_texCoord + vec2(0.0, u_h));
      n[8] = texture2D(u_texture, v_texCoord + vec2(  u_w,u_h));
      
      // Sobel Edge
      vec4 sobel_horizEdge = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
      vec4 sobel_vertEdge  = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
      vec3 sobel = sqrt((sobel_horizEdge.rgb * sobel_horizEdge.rgb) + (sobel_vertEdge.rgb * sobel_vertEdge.rgb));
      
      gl_FragColor = vec4( sobel, 1.0 );
}
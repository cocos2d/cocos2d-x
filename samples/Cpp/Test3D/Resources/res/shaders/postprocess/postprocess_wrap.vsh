
uniform vec2 g_vPixelSize;// = float2(1.f / 800.f, 1.f / 600.f);
uniform float g_fTime;
uniform float g_fWarpSpeed;

attribute vec2 a_position;
attribute vec2 a_texCoord;

varying vec4 v_position;
varying vec2 v_texcoord;
varying vec2 v_pertubeTC;


void main()
{
  gl_Position = vec4(a_position, 0, 1);
  gl_Position.x -= g_vPixelSize.x;
  gl_Position.y += g_vPixelSize.y;
  
  v_texcoord = a_texCoord;
  v_pertubeTC = a_texCoord;
  v_pertubeTC.x *= 2.0;
  v_pertubeTC.y *= 2.0;
  
  float yd = g_fTime * 0.5 * g_fWarpSpeed;
  if (yd > 1.0)
      yd -= 1.0;
      
  v_pertubeTC.y += yd;
  //v_pertubeTC.x += yd;
}
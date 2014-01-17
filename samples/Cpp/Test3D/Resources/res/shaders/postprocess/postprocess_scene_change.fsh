#ifdef OPENGL_ES
precision highp float;
#endif


uniform sampler2D u_texture; 

uniform float radius;
uniform float angle;

// Inputs
varying vec2 v_texCoord;                // Texture coordinate (u, v).

vec3 PostFX( vec2 uv )
{
  vec2 texSize = vec2(1.0, 1.0);


  vec2 tc = uv * texSize;



  tc -= vec2(0.5, 0.5);
  float dist = length(tc);
	float percent = (radius - dist) / radius;
  if ( percent < 1.0 && percent >= 0.0) 
  {
    float theta = percent * percent * angle * 8.0;
    float s = sin(theta);
    float c = cos(theta);
    tc = vec2(dot(tc, vec2(c, -s)), dot(tc, vec2(s, c)));
  }
  tc += vec2(0.5, 0.5);


  
  return vec3( tc/texSize, percent );
}

void main (void)
{
	vec3 uvw = PostFX( v_texCoord );
	gl_FragColor = texture2D(u_texture, uvw.xy);

	gl_FragColor.a = clamp(uvw.z, 0.0, 1.0);

}

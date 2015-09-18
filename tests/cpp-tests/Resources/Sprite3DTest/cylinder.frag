#ifdef GL_ES
varying mediump vec2 v_texture_coord;
#else
varying vec2 v_texture_coord;
#endif

uniform vec4 u_color;
uniform float offset;
uniform float duration;
uniform sampler2D u_sampler0; 
uniform sampler2D u_sampler1; 
void main(void)
{
    vec4 color = duration*vec4(0,0.8,0.4,1.0);
    //blend two texture
    gl_FragColor = u_color*texture2D(u_sampler0, vec2(v_texture_coord.x- 2.0 * offset,v_texture_coord.y)) * vec4(0.3,0.3,0.3,1)+texture2D(u_sampler1,vec2(v_texture_coord.x-offset,v_texture_coord.y)).r*color;
}
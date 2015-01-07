#ifdef GL_ES
varying mediump vec2 v_texture_coord;
#else
varying vec2 v_texture_coord;
#endif
varying float v_fogFactor;

uniform vec4 u_fogColor;

void main (void)
{
    vec4 finalColor = texture2D(CC_Texture0, v_texture_coord);
    gl_FragColor     = mix(u_fogColor, finalColor, v_fogFactor );        //out put finalColor
}

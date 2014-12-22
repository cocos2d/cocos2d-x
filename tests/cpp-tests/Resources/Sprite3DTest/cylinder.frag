#ifdef GL_ES
varying mediump vec2 TextureCoordOut;
#else
varying vec2 TextureCoordOut;
#endif

uniform vec4 u_color;
uniform float offset;
uniform float duration;
uniform sampler2D caustics; 
void main(void)
{
    vec4 golden = duration*vec4(0,0.8,0.4,1.0);
    //blend two texture
    gl_FragColor = texture2D(CC_Texture0, vec2(TextureCoordOut.x- 2.0 * offset,TextureCoordOut.y)) * vec4(0.3,0.3,0.3,1)+texture2D(caustics,vec2(TextureCoordOut.x-offset,TextureCoordOut.y)).r*golden;
}
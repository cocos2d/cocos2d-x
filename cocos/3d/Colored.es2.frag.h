static const char* baseColoredFrag = STRINGIFY(

#ifdef GL_ES
varying lowp vec4 DestinationColor;
#else
varying vec4 DestinationColor;
#endif
uniform vec4 u_color;

//varying mediump vec2 TextureCoordOut;

//uniform sampler2D Sampler;

void main(void)
{
    //gl_FragColor =  DestinationColor;
    //gl_FragColor.a = 1.0;
    gl_FragColor = u_color;
}
);


// pure black frag shader
static const char* blackFrag = STRINGIFY(
uniform vec3 OutLineColor;
uniform vec4 u_color;

void main(void)
{
    gl_FragColor =  vec4(OutLineColor,1.0) * u_color;
}
);

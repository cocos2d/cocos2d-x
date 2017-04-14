
const char* ccCameraClearFrag = R"(

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec3 v_color;
#else
varying vec2 v_texCoord;
varying vec3 v_color;
#endif
void main()
{
    gl_FragColor = vec4(v_color, 1.0);
}
)";

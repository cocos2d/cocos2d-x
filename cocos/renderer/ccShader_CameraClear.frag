
const char* ccCameraClearFrag = STRINGIFY(

\n#ifdef GL_ES\n
varying mediump vec2 v_texCoord;
varying mediump vec3 v_color;
\n#else\n
varying vec2 v_texCoord;
varying vec3 v_color;
\n#endif\n
void main()
{
    gl_FragColor = vec4(v_color, 1.0);
}
);

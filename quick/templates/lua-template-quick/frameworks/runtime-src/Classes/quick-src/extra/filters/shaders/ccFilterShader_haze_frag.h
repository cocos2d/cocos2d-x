"#ifdef GL_ES\n\
precision mediump float;\n\
uniform lowp float u_hazeDistance;\n\
uniform highp float u_slope;\n\
#else\n\
uniform float u_hazeDistance;\n\
uniform float u_slope;\n\
#endif\n\
varying vec2 v_texCoord;\n\
\n\
void main()\n\
{\n\
   //todo reconsider precision modifiers	 \n\
#ifdef GL_ES\n\
    highp vec4 color = vec4(1.0);//todo reimplement as a parameter\n\
    highp float  d = v_texCoord.y * u_slope  +  u_hazeDistance;\n\
    highp vec4 c = texture2D(CC_Texture0, v_texCoord) ; // consider using unpremultiply\n\
#else\n\
    vec4 color = vec4(1.0);//todo reimplement as a parameter\n\
    float  d = v_texCoord.y * u_slope  +  u_hazeDistance;\n\
    vec4 c = texture2D(CC_Texture0, v_texCoord) ; // consider using unpremultiply\n\
#endif\n\
    c = (c - d * color) / (1.0 -d);\n\
    \n\
    gl_FragColor = c; //consider using premultiply(c);\n\
}";

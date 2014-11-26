"#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
 varying vec2 v_texCoord;\n\
 \n\
 \n\
 uniform float u_redAdj;\n\
 uniform float u_greenAdj;\n\
 uniform float u_blueAdj;\n\
 \n\
 void main()\n\
 {\n\
     vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
     gl_FragColor = vec4(textureColor.r * u_redAdj, textureColor.g * u_greenAdj, textureColor.b * u_blueAdj, textureColor.a);\n\
 }";

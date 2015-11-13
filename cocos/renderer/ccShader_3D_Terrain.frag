
const char* cc3D_Terrain_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision mediump float;
\n#endif\n
uniform vec3 u_color;\n
varying vec2 v_texCoord;\n
varying vec3 v_normal;\n
\n#ifdef GL_ES\n
uniform lowp int u_has_alpha;\n
uniform lowp int u_has_light_map;\n
\n#else\n
uniform int u_has_alpha;\n
uniform int u_has_light_map;\n
\n#endif\n
uniform sampler2D u_alphaMap;\n
uniform sampler2D u_texture0;\n
uniform sampler2D u_texture1;\n
uniform sampler2D u_texture2;\n
uniform sampler2D u_texture3;\n
uniform sampler2D u_lightMap;\n
uniform float u_detailSize[4];\n
uniform vec3 u_lightDir;\n
void main()\n
{\n
vec4 lightColor;\n
if(u_has_light_map<=0)\n
{\n
    lightColor = vec4(1.0,1.0,1.0,1.0);\n
}else\n
{\n
    lightColor = texture2D(u_lightMap,v_texCoord);\n
}
float lightFactor = dot(-u_lightDir,v_normal);\n
if(u_has_alpha<=0)\n
{\n
    gl_FragColor = texture2D(u_texture0, v_texCoord)*lightColor*lightFactor;\n
}else\n
{\n
    vec4 blendFactor =texture2D(u_alphaMap,v_texCoord);\n
    vec4 color = vec4(0.0,0.0,0.0,0.0);\n
    color = texture2D(u_texture0, v_texCoord*u_detailSize[0])*blendFactor.r +
    texture2D(u_texture1, v_texCoord*u_detailSize[1])*blendFactor.g + texture2D(u_texture2, v_texCoord*u_detailSize[2])*blendFactor.b
        + texture2D(u_texture3, v_texCoord*u_detailSize[3])*(1.0 - blendFactor.a);
    gl_FragColor = vec4(color.rgb*lightColor.rgb*lightFactor, 1.0);
}
}
);

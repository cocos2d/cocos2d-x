
const char* cc3D_Terrain_frag = R"(
#ifdef GL_ES
precision mediump float;
#endif
uniform vec3 u_color;
varying vec2 v_texCoord;
varying vec3 v_normal;
#ifdef GL_ES
uniform lowp int u_has_alpha;
uniform lowp int u_has_light_map;
#else
uniform int u_has_alpha;
uniform int u_has_light_map;
#endif
uniform sampler2D u_alphaMap;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform sampler2D u_lightMap;
uniform float u_detailSize[4];
uniform vec3 u_lightDir;
void main()
{
vec4 lightColor;
if(u_has_light_map<=0)
{
    lightColor = vec4(1.0,1.0,1.0,1.0);
}else
{
    lightColor = texture2D(u_lightMap,v_texCoord);
}
float lightFactor = dot(-u_lightDir,v_normal);
if(u_has_alpha<=0)
{
    gl_FragColor = texture2D(u_texture0, v_texCoord)*lightColor*lightFactor;
}else
{
    vec4 blendFactor =texture2D(u_alphaMap,v_texCoord);
    vec4 color = vec4(0.0,0.0,0.0,0.0);
    color = texture2D(u_texture0, v_texCoord*u_detailSize[0])*blendFactor.r +
    texture2D(u_texture1, v_texCoord*u_detailSize[1])*blendFactor.g + texture2D(u_texture2, v_texCoord*u_detailSize[2])*blendFactor.b
        + texture2D(u_texture3, v_texCoord*u_detailSize[3])*(1.0 - blendFactor.a);
    gl_FragColor = vec4(color.rgb*lightColor.rgb*lightFactor, 1.0);
}
}
)";

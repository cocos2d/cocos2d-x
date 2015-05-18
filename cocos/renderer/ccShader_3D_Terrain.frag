
const char* cc3D_Terrain_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision lowp float;
\n#endif\n
uniform vec3 u_color;
varying vec2 v_texCoord;
varying vec3 v_normal;
uniform int u_has_alpha;
uniform sampler2D u_alphaMap;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float u_detailSize[4];
void main()
{
vec3 light_direction = vec3(-1,-1,0);
float lightFactor = dot(-light_direction,v_normal);
if(u_has_alpha<=0)
{
    gl_FragColor =  texture2D(u_texture0, v_texCoord)*lightFactor;
}else
{
    vec4 blendFactor =texture2D(u_alphaMap,v_texCoord);
    vec4 color = vec4(0,0,0,0);
    color = texture2D(u_texture0, v_texCoord*u_detailSize[0])*blendFactor.r +
    texture2D(u_texture1, v_texCoord*u_detailSize[1])*blendFactor.g + texture2D(u_texture2, v_texCoord*u_detailSize[2])*blendFactor.b;\n
    float grayFactor =dot(blendFactor.rgb, vec3(1, 1, 1));
    color +=texture2D(u_texture3, v_texCoord*u_detailSize[3])*(1.0-grayFactor);
    gl_FragColor = color*lightFactor;
}
}
);

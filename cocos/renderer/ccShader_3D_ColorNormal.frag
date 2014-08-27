
const char* cc3D_ColorNormal_frag = STRINGIFY(

\n#ifdef GL_ES\n

varying mediump vec2 TextureCoordOut;
\n#if CC_MAX_POINT_LIGHT_NUM\n
varying mediump vec3 v_vertexToPointLightDirection[CC_MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if CC_MAX_SPOT_LIGHT_NUM\n
varying mediump vec3 v_vertexToSpotLightDirection[CC_MAX_SPOT_LIGHT_NUM];
\n#endif\n
varying mediump vec3 v_normal;

\n#else\n

varying vec2 TextureCoordOut;
\n#if CC_MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[CC_MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if CC_MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[CC_MAX_SPOT_LIGHT_NUM];
\n#endif\n
varying vec3 v_normal;

\n#endif\n

uniform vec4 u_color;

\n#if CC_MAX_POINT_LIGHT_NUM\n
void PointLight(int n, vec3 normal, inout vec4 intensity)
{
    vec3 dir = v_vertexToPointLightDirection[n];
    vec3 ldir = dir * CC_PointLightSource[n].position.w;
    float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
    intensity.xyz += CC_PointLightSource[n].color * max(0.0, dot(normalize(dir), normal)) * attenuation;	
    intensity.w = 1.0;
}
\n#endif\n

\n#if CC_MAX_DIRECTIONAL_LIGHT_NUM\n
void DirectionalLight(int n, vec3 normal, inout vec4 intensity)
{
    intensity.xyz += CC_DirLightSource[n].color * max(0.0, dot(-CC_DirLightSource[n].direction, normal));
    intensity.w = 1.0;
}
\n#endif\n

\n#if CC_MAX_SPOT_LIGHT_NUM\n
void SpotLight(int n, vec3 normal, inout vec4 intensity)
{
    vec3 dir = v_vertexToPointLightDirection[n];
    vec3 ldir = dir * CC_SpotLightSource[n].position.z;
    float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
    float spotDot = dot(normalize(dir), -CC_SpotLightSource[n].direction);
    float innerCos = CC_SpotLightSource[n].params.x;
    float outerCos = CC_SpotLightSource[n].params.y;
    float factor = smoothstep(outerCos, innerCos, spotDot);
    intensity.xyz += CC_SpotLightSource[n].color * max(0.0, dot(normalize(dir), normal)) * factor * attenuation;	
    intensity.w = 1.0;
}
\n#endif\n

void main(void)
{
    vec4 intensity = vec4(0.0);
\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM || CC_MAX_POINT_LIGHT_NUM || CC_MAX_SPOT_LIGHT_NUM)\n
    vec3 normal  = normalize(v_normal);
\n#endif\n

\n#if CC_MAX_DIRECTIONAL_LIGHT_NUM\n
    
    for (int i = 0; i < CC_MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
        DirectionalLight(i, normal, intensity);
    }

\n#endif\n

\n#if CC_MAX_POINT_LIGHT_NUM\n

    for (int i = 0; i < CC_MAX_POINT_LIGHT_NUM; ++i)
    {
        PointLight(i, normal, intensity);
    }

\n#endif\n

\n#if CC_MAX_SPOT_LIGHT_NUM\n

    for (int i = 0; i < CC_MAX_SPOT_LIGHT_NUM; ++i)
    {
        SpotLight(i, normal, intensity);
    }

\n#endif\n

\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM || CC_MAX_POINT_LIGHT_NUM || CC_MAX_SPOT_LIGHT_NUM)\n
    gl_FragColor = u_color * (CC_AmbientColor + intensity);
\n#else\n
     gl_FragColor = u_color;
\n#endif\n

}
);

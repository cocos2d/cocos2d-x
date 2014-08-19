
const char* cc3D_ColorTex_frag = STRINGIFY(

\n#ifdef GL_ES\n
varying mediump vec2 TextureCoordOut;
varying mediump vec4 ePosition;
varying mediump vec3 eNormal;
\n#else\n
varying vec2 TextureCoordOut;
varying vec4 ePosition;
varying vec3 eNormal;
\n#endif\n
uniform vec4 u_color;

\n#if CC_MAX_POINT_LIGHT_NUM\n
void PointLight(int n, vec4 ePosition, vec3 eNormal, inout vec4 intensity)
{
    if (distance(CC_PointLightSource[n].position, ePosition.xyz) < CC_PointLightSource[n].range)
    {
        vec3 lightDir = CC_PointLightSource[n].position - ePosition.xyz;
        lightDir = normalize(lightDir);
        intensity.xyz += CC_PointLightSource[n].color * max(0.0, dot(lightDir, eNormal));	
    }
    intensity.w = 1.0;
}
\n#endif\n

\n#if CC_MAX_DIRECTIONAL_LIGHT_NUM\n
void DirectionalLight(int n, vec3 eNormal, inout vec4 intensity)
{
    intensity.xyz += CC_DirLightSource[n].color * max(0.0, dot(normalize(-CC_DirLightSource[n].direction), eNormal));
    intensity.w = 1.0;
}
\n#endif\n

\n#if CC_MAX_SPOT_LIGHT_NUM\n
void SpotLight(int n, vec4 ePosition, vec3 eNormal, inout vec4 intensity)
{
    if (distance(CC_SpotLightSource[n].position, ePosition.xyz) < CC_SpotLightSource[n].range)
    {
        vec3 lightDir = CC_SpotLightSource[n].position - ePosition.xyz;
        lightDir = normalize(lightDir);
        float spotDot = dot(lightDir, normalize(-CC_SpotLightSource[n].direction));
        float innerCos = cos(CC_SpotLightSource[n].innerAngle);
        float outerCos = cos(CC_SpotLightSource[n].outerAngle);
        float factor = smoothstep(outerCos, innerCos, spotDot);
        intensity.xyz += CC_SpotLightSource[n].color * max(0.0, dot(lightDir, eNormal)) * factor;	
    }
    intensity.w = 1.0;
}
\n#endif\n


void main(void)
{	
    vec3 normal = normalize(eNormal);
    vec4 intensity = vec4(0.0);

\n#if CC_MAX_DIRECTIONAL_LIGHT_NUM\n

    for (int i = 0; i < CC_EnabledDirLightNum; ++i)
    {
        DirectionalLight(i, normal, intensity);
    }

\n#endif\n

\n#if CC_MAX_POINT_LIGHT_NUM\n

    for (int i = 0; i < CC_EnabledPointLightNum; ++i)
    {
        PointLight(i, ePosition, normal, intensity);
    }

\n#endif\n

\n#if CC_MAX_SPOT_LIGHT_NUM\n

    for (int i = 0; i < CC_EnabledSpotLightNum; ++i)
    {
        SpotLight(i, ePosition, normal, intensity);
    }

\n#endif\n

    if (intensity.w == 0.0)
        gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color;
    else
        gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color * (CC_AmbientColor + intensity);
}
);

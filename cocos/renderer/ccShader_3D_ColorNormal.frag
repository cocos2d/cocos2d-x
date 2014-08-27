
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

void main(void)
{
    vec4 intensity = vec4(0.0, 0.0, 0.0, 1.0);
\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM || CC_MAX_POINT_LIGHT_NUM || CC_MAX_SPOT_LIGHT_NUM)\n
    vec3 normal  = normalize(v_normal);
\n#endif\n

\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
    
    for (int n = 0; n < CC_MAX_DIRECTIONAL_LIGHT_NUM; ++n)
    {
        intensity.xyz += CC_DirLightSourceColor[n] * max(0.0, dot(-CC_DirLightSourceDirection[n], normal));
    }

\n#endif\n

\n#if (CC_MAX_POINT_LIGHT_NUM > 0)\n

    for (int n = 0; n < CC_MAX_POINT_LIGHT_NUM; ++n)
    {
        vec3 dir = v_vertexToPointLightDirection[n];
        vec3 ldir = dir * CC_PointLightSourceColor[n].w;
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        intensity.xyz += CC_PointLightSourceColor[n] * max(0.0, dot(normalize(dir), normal)) * attenuation;	
    }

\n#endif\n

\n#if (CC_MAX_SPOT_LIGHT_NUM > 0)\n

    for (int n = 0; n < CC_MAX_SPOT_LIGHT_NUM; ++n)
    {
        vec3 dir = v_vertexToSpotLightDirection[n];
        vec3 ldir = dir * CC_SpotLightSourceParams[n].z;
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        dir = normalize(dir);
        float spotDot = dot(normalize(dir), -CC_SpotLightSourceDirection[n]);
        float innerCos = CC_SpotLightSourceParams[n].x;
        float outerCos = CC_SpotLightSourceParams[n].y;
        float factor = smoothstep(outerCos, innerCos, spotDot);
        intensity.xyz += CC_SpotLightSourceColor[n] * max(0.0, dot(normalize(dir), normal)) * factor * attenuation;
    }

\n#endif\n

\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM || CC_MAX_POINT_LIGHT_NUM || CC_MAX_SPOT_LIGHT_NUM)\n
    gl_FragColor = u_color * (CC_AmbientColor + intensity);
\n#else\n
     gl_FragColor = u_color;
\n#endif\n

}
);

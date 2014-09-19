
const char* cc3D_ColorNormal_frag = STRINGIFY(

\n#ifdef GL_ES\n

varying mediump vec2 TextureCoordOut;
\n#if CC_MAX_POINT_LIGHT_NUM\n
varying mediump vec3 v_vertexToPointLightDirection[CC_MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if CC_MAX_SPOT_LIGHT_NUM\n
varying mediump vec3 v_vertexToSpotLightDirection[CC_MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#if ((CC_MAX_DIRECTIONAL_LIGHT_NUM > 0) || (CC_MAX_POINT_LIGHT_NUM > 0) || (CC_MAX_SPOT_LIGHT_NUM > 0))\n
varying mediump vec3 v_normal;
\n#endif\n

\n#else\n

varying vec2 TextureCoordOut;
\n#if CC_MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[CC_MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if CC_MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[CC_MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#if ((CC_MAX_DIRECTIONAL_LIGHT_NUM > 0) || (CC_MAX_POINT_LIGHT_NUM > 0) || (CC_MAX_SPOT_LIGHT_NUM > 0))\n
varying vec3 v_normal;
\n#endif\n

\n#endif\n

uniform vec4 u_color;

vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation)
{
    float diffuse = max(dot(normalVector, lightDirection), 0.0);
    vec3 diffuseColor = lightColor  * diffuse * attenuation;
    
    return diffuseColor;
}

void main(void)
{
\n#if ((CC_MAX_DIRECTIONAL_LIGHT_NUM > 0) || (CC_MAX_POINT_LIGHT_NUM > 0) || (CC_MAX_SPOT_LIGHT_NUM > 0))\n
    vec3 normal  = normalize(v_normal);
\n#endif\n

    vec4 combinedColor = vec4(0.0, 0.0, 0.0, 1.0);

    // Directional light contribution
\n#if (CC_MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
    for (int i = 0; i < CC_MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
        vec3 lightDirection = normalize(CC_DirLightSourceDirection[i] * 2.0);
        combinedColor.xyz += computeLighting(normal, -lightDirection, CC_DirLightSourceColor[i] * CC_DirLightSourceIntensity[i], 1.0);
    }
\n#endif\n

    // Point light contribution
\n#if (CC_MAX_POINT_LIGHT_NUM > 0)\n
    for (int i = 0; i < CC_MAX_POINT_LIGHT_NUM; ++i)
    {
        vec3 ldir = v_vertexToPointLightDirection[i] * CC_PointLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), CC_PointLightSourceColor[i] * CC_PointLightSourceIntensity[i], attenuation);
    }
\n#endif\n

    // Spot light contribution
\n#if (CC_MAX_SPOT_LIGHT_NUM > 0)\n
    for (int i = 0; i < CC_MAX_SPOT_LIGHT_NUM; ++i)
    {
        // Compute range attenuation
        vec3 ldir = v_vertexToSpotLightDirection[i] * CC_SpotLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]);

        vec3 spotLightDirection = normalize(CC_SpotLightSourceDirection[i] * 2.0);

        // "-lightDirection" is used because light direction points in opposite direction to spot direction.
        float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection);

        // Apply spot attenuation
        attenuation *= smoothstep(CC_SpotLightSourceOuterAngleCos[i], CC_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos);
        combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, CC_SpotLightSourceColor[i] * CC_SpotLightSourceIntensity[i], attenuation);
    }
\n#endif\n

\n#if (CC_MAX_AMBIENT_LIGHT_NUM > 0)\n
    for (int i = 0; i < CC_MAX_AMBIENT_LIGHT_NUM; ++i)
    {
        combinedColor.xyz += CC_AmbientLightSourceColor[i] * CC_AmbientLightSourceIntensity[i];
    }
\n#endif\n

\n#if ((CC_MAX_DIRECTIONAL_LIGHT_NUM > 0) || (CC_MAX_POINT_LIGHT_NUM > 0) || (CC_MAX_SPOT_LIGHT_NUM > 0) || (CC_MAX_AMBIENT_LIGHT_NUM > 0))\n
    gl_FragColor = u_color * combinedColor;
\n#else\n
    gl_FragColor = u_color;
\n#endif\n

}
);

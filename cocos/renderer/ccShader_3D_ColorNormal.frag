
const char* cc3D_ColorNormal_frag = STRINGIFY(

\n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM];
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
\n#endif\n
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM];
uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM];
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM]; 
uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
\n#endif\n
uniform vec3 u_AmbientLightSourceColor;

\n#ifdef GL_ES\n
varying mediump vec2 TextureCoordOut;
\n#if MAX_POINT_LIGHT_NUM\n
varying mediump vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying mediump vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
varying mediump vec3 v_normal;
\n#endif\n

\n#else\n

varying vec2 TextureCoordOut;
\n#if MAX_POINT_LIGHT_NUM\n
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
\n#endif\n
\n#if MAX_SPOT_LIGHT_NUM\n
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
\n#endif\n
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
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
\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    vec3 normal  = normalize(v_normal);
\n#endif\n

    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);

    // Directional light contribution
\n#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
        vec3 lightDirection = normalize(u_DirLightSourceDirection[i] * 2.0);
        combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0);
    }
\n#endif\n

    // Point light contribution
\n#if (MAX_POINT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation);
    }
\n#endif\n

    // Spot light contribution
\n#if (MAX_SPOT_LIGHT_NUM > 0)\n
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        // Compute range attenuation
        vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]);

        vec3 spotLightDirection = normalize(u_SpotLightSourceDirection[i] * 2.0);

        // "-lightDirection" is used because light direction points in opposite direction to spot direction.
        float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection);

        // Apply spot attenuation
        attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos);
        attenuation = clamp(attenuation, 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation);
    }
\n#endif\n

\n#if ((MAX_DIRECTIONAL_LIGHT_NUM > 0) || (MAX_POINT_LIGHT_NUM > 0) || (MAX_SPOT_LIGHT_NUM > 0))\n
    gl_FragColor = u_color * combinedColor;
\n#else\n
    gl_FragColor = u_color;
\n#endif\n

}
);

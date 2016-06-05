precision mediump float;
precision mediump int;
#define MAX_DIRECTIONAL_LIGHT_NUM 1
#define MAX_POINT_LIGHT_NUM 1
#define MAX_SPOT_LIGHT_NUM 1

#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
uniform vec3 u_DirLightSourceColor[MAX_DIRECTIONAL_LIGHT_NUM];
uniform vec3 u_DirLightSourceDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
uniform vec3 u_PointLightSourceColor[MAX_POINT_LIGHT_NUM];
uniform float u_PointLightSourceRangeInverse[MAX_POINT_LIGHT_NUM];
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
uniform vec3 u_SpotLightSourceColor[MAX_SPOT_LIGHT_NUM];
uniform vec3 u_SpotLightSourceDirection[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceInnerAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceOuterAngleCos[MAX_SPOT_LIGHT_NUM];
uniform float u_SpotLightSourceRangeInverse[MAX_SPOT_LIGHT_NUM];
#endif

uniform vec3 u_AmbientLightSourceColor;

varying vec2 TextureCoordOut;
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
varying vec3 v_dirLightDirection[MAX_DIRECTIONAL_LIGHT_NUM];
varying vec3 v_dirLightReflectDirection[MAX_DIRECTIONAL_LIGHT_NUM];
#endif
#if (MAX_POINT_LIGHT_NUM > 0)
varying vec3 v_vertexToPointLightDirection[MAX_POINT_LIGHT_NUM];
#endif
#if (MAX_SPOT_LIGHT_NUM > 0)
varying vec3 v_vertexToSpotLightDirection[MAX_SPOT_LIGHT_NUM];
varying vec3 v_spotLightDirection[MAX_SPOT_LIGHT_NUM];
#endif

uniform vec4 u_specularColor;
uniform float u_shininess;
uniform vec4 u_color;
uniform sampler2D u_normalTex;
vec3 computeLighting(vec3 normalVector, vec3 lightDirection, vec3 lightColor, float attenuation)
{
    float diffuse = max(dot(normalVector, lightDirection), 0.0);
    vec3 diffuseColor = lightColor * diffuse * attenuation; return diffuseColor;
}

void main(void)
{
    vec3 normal = 2.0 * texture2D(u_normalTex, TextureCoordOut).xyz - 1.0;
    vec4 combinedColor = vec4(u_AmbientLightSourceColor, 1.0);
    vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);
#if (MAX_DIRECTIONAL_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_DIRECTIONAL_LIGHT_NUM; ++i)
    {
        vec3 lightDirection = normalize(v_dirLightDirection[i]);
        combinedColor.xyz += computeLighting(normal, -lightDirection, u_DirLightSourceColor[i], 1.0);
        vec3 reflectDirection = normalize(v_dirLightReflectDirection[i]);
        float specular = max(dot(normal, -reflectDirection), 0.0);
        specularColor.xyz += u_DirLightSourceColor[i] * pow(specular, u_shininess);
    }
#endif

#if (MAX_POINT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_POINT_LIGHT_NUM; ++i)
    {
        vec3 ldir = v_vertexToPointLightDirection[i] * u_PointLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, normalize(v_vertexToPointLightDirection[i]), u_PointLightSourceColor[i], attenuation);
    }
#endif

#if (MAX_SPOT_LIGHT_NUM > 0)
    for (int i = 0; i < MAX_SPOT_LIGHT_NUM; ++i)
    {
        vec3 ldir = v_vertexToSpotLightDirection[i] * u_SpotLightSourceRangeInverse[i];
        float attenuation = clamp(1.0 - dot(ldir, ldir), 0.0, 1.0);
        vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]);
        vec3 spotLightDirection = normalize(v_spotLightDirection[i] * 2.0);
        float spotCurrentAngleCos = dot(spotLightDirection, -vertexToSpotLightDirection);
        attenuation *= smoothstep(u_SpotLightSourceOuterAngleCos[i], u_SpotLightSourceInnerAngleCos[i], spotCurrentAngleCos);
        attenuation = clamp(attenuation, 0.0, 1.0);
        combinedColor.xyz += computeLighting(normal, vertexToSpotLightDirection, u_SpotLightSourceColor[i], attenuation);
    }
#endif

    gl_FragColor = texture2D(CC_Texture0, TextureCoordOut) * u_color * combinedColor + u_specularColor * specularColor;
}

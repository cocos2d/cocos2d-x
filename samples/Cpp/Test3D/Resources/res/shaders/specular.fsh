#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform vec3 u_lightColor;                      // Light color
uniform vec3 u_ambientColor;                    // Ambient color
uniform float u_specularExponent;               // Specular exponent or shininess property.
uniform sampler2D u_diffuseTexture;             // Diffuse texture.
#if defined(GLOBAL_ALPHA)
uniform float u_globalAlpha;                    // Global alpha value
#endif

// Inputs
varying vec3 v_normalVector;                    // NormalVector in view space.
varying vec2 v_texCoord;                        // Texture coordinate (u, v).
varying vec3 v_cameraDirection;                 // Camera direction

// Global variables
vec4 _baseColor;                                // Base color
vec3 _ambientColor;                             // Ambient Color
vec3 _diffuseColor;                             // Diffuse Color
vec3 _specularColor;                            // Specular color

#ifdef MAXDIRLIGHT
struct DirectionLight
{
    vec3 dir;
    vec3 color;
};
#endif

#ifdef MAXPOINTLIGHT
struct PointLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
};
#endif

#ifdef MAXSPOTLIGHT
struct SpotLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
    vec3 dir;
    float innerAngleCos;
    float outerAngleCos;
};
#endif

#ifdef MAXDIRLIGHT
uniform DirectionLight u_dirlight[MAXDIRLIGHT];
#endif
#ifdef MAXPOINTLIGHT
uniform PointLight u_pointlight[MAXPOINTLIGHT];
#endif
#ifdef MAXSPOTLIGHT
uniform SpotLight u_spotlight[MAXSPOTLIGHT];
#endif

#ifdef OPENGL_ES
uniform lowp int u_ndirlight;
uniform lowp int u_npointlight;
uniform lowp int u_nspotlight;
#else
uniform int u_ndirlight;
uniform int u_npointlight;
uniform int u_nspotlight;
#endif

#ifdef MAXPOINTLIGHT
varying vec4 v_vertexToPointLightDirection[MAXPOINTLIGHT];

#endif
#ifdef MAXSPOTLIGHT
varying vec3 v_vertexToSpotLightDirection[MAXSPOTLIGHT];              // Light direction w.r.t current vertex.
varying float v_spotLightAttenuation[MAXSPOTLIGHT];                   // Attenuation of spot light.
#endif

vec3 diffuselight(vec3 lightcolor, vec3 normalVector, vec3 lightDirection, float attenuation)
{
    // Diffuse
    float ddot = dot(normalVector, lightDirection);
    float diffuseIntensity = attenuation * ddot;
    diffuseIntensity = max(0.0, diffuseIntensity);
    return lightcolor * _baseColor.rgb * diffuseIntensity;
}

vec3 specularlight(vec3 lightcolor, vec3 normalVector, vec3 halfVector, float attenuation)
{
    // Specular
    //vec3 halfVector = normalize(lightDirection + cameraDirection);
    float specularIntensity = attenuation * max(0.0, pow(dot(normalVector, halfVector), u_specularExponent));
    specularIntensity = max(0.0, specularIntensity);
    return lightcolor * _baseColor.rgb * specularIntensity;
}

#ifdef MAXPOINTLIGHT
void applyPointLight()
{
    // Normalize the vectors.
    vec3 normalVector = normalize(v_normalVector);
    vec3 cameraDirection = normalize(v_cameraDirection);
    
    
    
    for (int i = 0; i < u_npointlight; i++)
	{
        vec3 vertexToPointLightDirection = normalize(v_vertexToPointLightDirection[i].xyz);
        
        // Fetch point light attenuation.
        float pointLightAttenuation = v_vertexToPointLightDirection[i].w;
        
        _diffuseColor += diffuselight(u_pointlight[i].color, normalVector, vertexToPointLightDirection, pointLightAttenuation);
        
        vec3 halfVector = normalize(vertexToPointLightDirection + cameraDirection);
        
        _specularColor += specularlight(u_pointlight[i].color, normalVector, halfVector, pointLightAttenuation);
        
    }
    
}
#endif


float lerpstep( float lower, float upper, float s)
{
    return clamp( ( s - lower ) / ( upper - lower ), 0.0, 1.0 );
}

#ifdef MAXSPOTLIGHT
void applySpotLight()
{
    // Normalize the vectors.
    vec3 normalVector = normalize(v_normalVector);
    vec3 cameraDirection = normalize(v_cameraDirection);
    
    for(int i = 0; i < u_nspotlight; i++)
    {
        vec3 spotLightDirection = u_spotlight[i].dir;
        vec3 vertexToSpotLightDirection = normalize(v_vertexToSpotLightDirection[i]);
        
        // "-lightDirection" is used because light direction points in opposite direction to
        // to spot direction.
        // Calculate spot light effect.
        float spotCurrentAngleCos = max(0.0, dot(spotLightDirection, -vertexToSpotLightDirection));
        
        // Intensity of spot depends on the spot light attenuation and the
        // part of the cone vertexToSpotLightDirection points to (inner or outer).
        float spotLightAttenuation = clamp(v_spotLightAttenuation[i], 0.0, 1.0);
        spotLightAttenuation *= lerpstep(u_spotlight[i].outerAngleCos, u_spotlight[i].innerAngleCos, spotCurrentAngleCos);
        
        _diffuseColor += diffuselight(u_spotlight[i].color, normalVector, vertexToSpotLightDirection, spotLightAttenuation);
        
        vec3 halfVector = normalize(vertexToSpotLightDirection + cameraDirection);
        
        _specularColor += specularlight(u_spotlight[i].color, normalVector, halfVector, spotLightAttenuation);
        
        //lighting(normalVector, cameraDirection, vertexToSpotLightDirection, spotLightAttenuation);
    }
    
}
#endif

#ifdef MAXDIRLIGHT
void applyDirLight()
{
    // Normalize the vectors.
    vec3 normalVector = normalize(v_normalVector);
    vec3 cameraDirection = normalize(v_cameraDirection);
    
    for(int i = 0; i < u_ndirlight; i++)
    {
        vec3 lightDirection = u_dirlight[i].dir;
        
        _diffuseColor += diffuselight(u_dirlight[i].color, normalVector, -lightDirection, 1.0);
        
        vec3 halfVector = normalize(-lightDirection + cameraDirection);
        
        _specularColor += specularlight(u_dirlight[i].color, normalVector, halfVector, 1.0);
    }
    
}
#endif

void main()
{
    // Fetch diffuse color from texture.
    _baseColor = texture2D(u_diffuseTexture, v_texCoord);

    // Apply light
    _specularColor = vec3(0.0, 0.0, 0.0);
    _diffuseColor = vec3(0.0, 0.0, 0.0);

    // Ambient
    _ambientColor = _baseColor.rgb * u_ambientColor;
    
    #ifdef MAXDIRLIGHT
    if (u_ndirlight > 0)
        applyDirLight();
    #endif
    
    #ifdef MAXSPOTLIGHT
    if (u_nspotlight > 0)
        applySpotLight();
    #endif
    
    #ifdef MAXPOINTLIGHT
    if (u_npointlight > 0)
        applyPointLight();
    #endif
    
    // Light the pixel
    gl_FragColor.a = _baseColor.a;
    
    gl_FragColor.rgb = _ambientColor + _diffuseColor + _specularColor;

#if defined(GLOBAL_ALPHA)
    gl_FragColor.a *= u_globalAlpha;
#endif
}

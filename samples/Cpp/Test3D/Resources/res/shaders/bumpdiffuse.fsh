#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform vec3 u_lightColor;                  // Light color.
uniform vec3 u_ambientColor;                // Ambient color.
uniform float u_specularExponent;           // Specular exponent or shininess property.
uniform sampler2D u_diffuseTexture;         // Diffuse texture.
uniform sampler2D u_normalMapTexture;       // Normal map texture.
#if defined(GLOBAL_ALPHA)
uniform float u_globalAlpha;                    // Global alpha value
#endif

// Inputs
varying vec2 v_texCoord;                    // Texture Coordinate.
varying vec3 v_cameraDirection;             // Direction the camera is looking at in tangent space.

// Global variables
vec4 _baseColor;                            // Base color
vec3 _ambientColor;                         // Ambient Color
vec3 _diffuseColor;                         // Diffuse Color
vec3 _specularColor;                        // Specular color


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
varying vec4 v_positionWorldViewSpace;
#endif
#ifdef MAXSPOTLIGHT
uniform SpotLight u_spotlight[MAXSPOTLIGHT];
#endif

//uniform vec3 u_nlight; // light number, u_nlight.x directional light, u_nlight.y point light, u_nlight.z spot light
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
varying vec3 v_spotLightDirection[MAXSPOTLIGHT]; 
#endif
#ifdef MAXDIRLIGHT
varying vec3 v_dirlightDirection[MAXDIRLIGHT];
#endif

vec3 diffuselight(vec3 lightcolor, vec3 normalVector, vec3 lightDirection, float attenuation)
{
    // Diffuse
    float ddot = dot(normalVector, lightDirection);
    float diffuseIntensity = attenuation * ddot;
    diffuseIntensity = max(0.0, diffuseIntensity);
    return lightcolor * _baseColor.rgb * diffuseIntensity;
}


#ifdef MAXPOINTLIGHT
void applyPointLight()
{
    // Normalize the vectors.
    // Fetch normals from the normal map.
    vec3 normalVector = normalize(texture2D(u_normalMapTexture, v_texCoord).rgb * 2.0 - 1.0);
       
    for (int i = 0; i < u_npointlight; i++) {
        vec3 vertexToPointLightDirection = normalize(v_vertexToPointLightDirection[i].xyz);
        
         vec3 lightDirection = u_pointlight[i].position - v_positionWorldViewSpace.xyz;
        
        // Attenuation
        float pointLightAttenuation = 1.0 - dot(lightDirection * u_pointlight[i].rangeInverse, lightDirection * u_pointlight[i].rangeInverse);
        //float pointLightAttenuation = clamp(v_vertexToPointLightDirection[i].w, 0.0, 1.0);
        
        _diffuseColor += diffuselight(u_pointlight[i].color, normalVector, vertexToPointLightDirection, pointLightAttenuation);
               
    }
}
#endif


#ifdef MAXSPOTLIGHT
float lerpstep( float lower, float upper, float s)
{
    return clamp( ( s - lower ) / ( upper - lower ), 0.0, 1.0 );
}

void applySpotLight()
{
    // Fetch normals from the normal map.
    vec3 normalVector = normalize(texture2D(u_normalMapTexture, v_texCoord).rgb * 2.0 - 1.0);
    vec3 cameraDirection = normalize(v_cameraDirection);
    
    for (int i = 0; i < u_nspotlight; i++) {
        vec3 spotLightDirection = normalize(v_spotLightDirection[i]);
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
               
    }
}

#endif


#ifdef MAXDIRLIGHT
void applyDirLight()
{
    // Fetch normals from the normal map
   vec3 normalVector = normalize(texture2D(u_normalMapTexture, v_texCoord).rgb * 2.0 - 1.0);
     
    
    for (int i = 0; i < u_ndirlight; i++) 
	{
        vec3 lightDirection = normalize(v_dirlightDirection[i]);
        
        _diffuseColor += diffuselight(u_dirlight[i].color, normalVector, -lightDirection, 1.0);
               
    }
}
#endif

void main()
{
    // Fetch diffuse color from texture.
    _baseColor = texture2D(u_diffuseTexture, v_texCoord);
    
    _ambientColor = _baseColor.rgb * u_ambientColor;
	   
    _diffuseColor = vec3(0.0, 0.0, 0.0);

    // Apply light
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

   gl_FragColor.rgb = _ambientColor + _diffuseColor;

#if defined(GLOBAL_ALPHA)
 //   gl_FragColor.a *= u_globalAlpha;
#endif
}

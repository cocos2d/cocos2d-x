#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_diffuseTexture;     // Diffuse texture
uniform vec4 u_diffuseColor;// = vec4(1.0,1.0,1.0,1.0);            // Diffuse color/tint
uniform float u_shadowPass;

#ifdef MAXPOINTLIGHT
#define PIXELLIGHT
#endif

//#ifdef FOG
uniform vec4 u_fogcolor;
uniform vec4 u_fogparam; // .x, .y, .z, .w stand for fog density, fog start, fog end, fog type. fog type 0, no fog, fog type 1 linear fog, fog type 2 exp fog, fog type 3 exp2 fog
varying float v_fogFactor;              //fog factor
//#endif

#ifdef SPECULAR
uniform vec4 u_specularPower;
#define PIXELLIGHT
#endif

#ifdef NORMALMAP
#define TANGENT
#define PIXELLIGHT
uniform sampler2D u_normalTexture;
#endif

#ifdef GLOBAL_ALPHA
uniform float u_globalAlpha;            // Global alpha value
#endif

// Inputs
varying vec2 v_texCoord;                // Texture coordinate (u, v).

#ifdef MAXANIMLIGHT
uniform sampler2D u_lightTexture;     // Diffuse texture
uniform vec4 u_animLightIntensity;// = vec4(1.0,0.0,0.0,0.0);
varying vec2 v_texCoordLight;             // Texture coordinate (u, v).
varying vec2 v_texCoordLight2;             // Texture coordinate (u, v).

#ifdef MASKLAYER
uniform sampler2D u_maskTexture;
#endif

#endif

//#ifdef MAXDIRLIGHT
	#ifdef PIXELLIGHT
		varying vec3 v_normal;
		varying vec3 v_lightDir;
		varying vec3 v_cameraDir;
	#endif
	
	varying vec4 v_lightColor;
//#endif

#ifdef SHADOWMAP
uniform sampler2D u_shadowTexture;
varying vec4 v_texCoordShadow;
#endif

#ifdef TRANSMISSION
uniform vec3 u_transColor;
#endif

vec4 basecolor;
#ifdef MAXPOINTLIGHT
struct PointLight
{
    vec3 position;
    vec3 color;
    float rangeInverse;
};
uniform PointLight u_pointlight[MAXPOINTLIGHT];
#ifdef OPENGL_ES
uniform lowp int u_npointlight;
#else
uniform int u_npointlight;
#endif
varying vec4 v_vertexToPointLightDirection[MAXPOINTLIGHT];
vec3 diffuselight(vec3 lightcolor, vec3 normalVector, vec3 lightDirection, float attenuation)
{
    // Diffuse
    float ddot = dot(normalVector, lightDirection);
    ddot = max(0.0, ddot);
    float diffuseIntensity = attenuation * ddot;
    diffuseIntensity = ddot;//max(0.0, diffuseIntensity);
    return lightcolor * basecolor.rgb * diffuseIntensity;
}
#ifdef SPECULAR
vec3 specularlight(vec3 lightcolor, vec3 normalVector, vec3 halfVector, float attenuation)
{
    // Specular
    //vec3 halfVector = normalize(lightDirection + cameraDirection);
    float specularIntensity = attenuation * max(0.0, pow(dot(normalVector, halfVector), u_specularPower.a));
    specularIntensity = max(0.0, specularIntensity);
    return lightcolor * u_specularPower.rgb * specularIntensity;
}
#endif
vec3 applyPointLight()
{
    // Normalize the vectors.
    vec3 normalVector = normalize(v_normal);
    vec3 cameraDirection = normalize(v_cameraDir);
    
    
    vec3 color = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < u_npointlight; i++) {
        vec3 vertexToPointLightDirection = normalize(v_vertexToPointLightDirection[i].xyz);
        
        // Fetch point light attenuation.
        float pointLightAttenuation = v_vertexToPointLightDirection[i].w;
        
        color += diffuselight(u_pointlight[i].color, normalVector, vertexToPointLightDirection, pointLightAttenuation);
        
        #ifdef SPECULAR 
        vec3 halfVector = normalize(vertexToPointLightDirection + cameraDirection);
        color += specularlight(u_pointlight[i].color, normalVector, halfVector, pointLightAttenuation);
        #endif
    }
    return color;
}
#endif



void main()
{
    basecolor = texture2D(u_diffuseTexture, v_texCoord);
#ifdef ALPHAREF
    if (basecolor.a < float(ALPHAREF) / 255.0)
        discard;
#endif

	float shadow = 1.0;

    vec4 color = basecolor * u_diffuseColor;
#ifdef SHADOWMAP

#ifdef SOFTSHADOW
	const vec2 offset = vec2(1.0 / 512.0, 1.0 / 512.0);
	vec2 centerUV = floor(v_texCoordShadow.xy * 512.0 + 0.5) / 512.0;
	
    float depth0 = texture2D(u_shadowTexture, centerUV + vec2(0.0, 0.0)).x;
    float depth1 = texture2D(u_shadowTexture, centerUV + vec2(0.0, offset.y)).x;
    float depth2 = texture2D(u_shadowTexture, centerUV + vec2(offset.x, 0.0)).x;
    float depth3 = texture2D(u_shadowTexture, centerUV + vec2(offset.x, offset.y)).x;
	vec2 s = fract(v_texCoordShadow.xy * 512.0 + 0.5);
    float shadow0 = step(v_texCoordShadow.z, depth0 + 0.01);
    float shadow1 = step(v_texCoordShadow.z, depth1 + 0.01);
    float shadow2 = step(v_texCoordShadow.z, depth2 + 0.01);
    float shadow3 = step(v_texCoordShadow.z, depth3 + 0.01);
	
	float shadow01 = mix(shadow0, shadow1, s.y);
	float shadow23 = mix(shadow2, shadow3, s.y);
	shadow = (shadow0 + shadow1 + shadow2 + shadow3) * 0.25;
	shadow *= mix(shadow01, shadow23, s.x);

#else
    float depth = texture2D(u_shadowTexture, v_texCoordShadow.xy).x;
    shadow = step(v_texCoordShadow.z, depth + 0.01);
#endif

	//gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);//vec4(v_texCoordShadow.z, v_texCoordShadow.z, v_texCoordShadow.z, 1.0);
	//return;
#endif

#ifdef MAXDIRLIGHT

#ifdef PIXELLIGHT

	vec3 lightDir = normalize(v_lightDir);
	vec3 cameraDir = normalize(v_cameraDir);

#ifdef TANGENT
#ifdef NORMALMAP
	vec3 normal = texture2D(u_normalTexture, v_texCoord).xyz;
	
	//gl_FragColor = vec4(normal, 1.0);
	//return;
	normal = normal * 2.0 - 1.0;
	normal.z *= 0.5;
	normal = normalize(normal);
#else
	vec3 normal = vec3(0, 0, 1);
#endif	
#else
	vec3 normal = normalize(v_normal);
#endif	
	
	float nd = dot(normal, lightDir);

#ifdef TRANSMISSION
	float ndd = (nd + 1.0) * 0.5;
#else
	float ndd = max(nd, 0.0);
#endif
	
	float diffuse = min(shadow, ndd);
	color.rgb *= diffuse * v_lightColor.rgb;
#ifdef TRANSMISSION
	color.rgb += u_transColor * max((-nd + 1.0) * 0.5, 0.0);
#endif

#ifdef SPECULAR
	vec3 reflectDir = reflect(-cameraDir, normal);
	float nd2 = dot(reflectDir, lightDir);
	vec3 spec = pow(max(nd2, 0.0), float(u_specularPower.a)) * u_specularPower.rgb;
	color.rgb += spec;
#endif

#else
	float nd = v_lightColor.a;

#ifdef TRANSMISSION
	float ndd = (nd + 1.0) * 0.5;
#else
	float ndd = max(nd, 0.0);
#endif
	
	float diffuse = min(shadow, ndd);
	color.rgb *= diffuse * v_lightColor.rgb;

#ifdef TRANSMISSION
	color.rgb += u_transColor * max((-nd + 1.0) * 0.5, 0.0);
#endif
	
#endif

#else
	color.rgb *= shadow;
#endif
	
#ifdef MAXANIMLIGHT
	float lightEffect = 1.0;
#ifdef MASKLAYER
    vec4 maskcolor = texture2D(u_maskTexture, v_texCoord);
	lightEffect = 1.0 - maskcolor.a;
#endif

    vec4 lightcolor1 = texture2D(u_lightTexture, v_texCoordLight);
    vec4 lightcolor2 = texture2D(u_lightTexture, v_texCoordLight2);
	vec3 light = + u_animLightIntensity.y * lightcolor1.rgb
				+ u_animLightIntensity.z * lightcolor2.rgb
				+ u_animLightIntensity.w * lightcolor1.rgb * lightcolor2.rgb;
	color.rgb *= (1.0 + light * lightEffect);
    
    //basecolor = vec4(v_texCoordLight, 0.0, 1.0);
#endif

	gl_FragColor = color;
#ifdef GLOBAL_ALPHA
    gl_FragColor.a *= u_globalAlpha;
#endif

#ifdef MAXPOINTLIGHT
   if (u_npointlight > 0)
        gl_FragColor.rgb += applyPointLight();
#endif

	if (u_fogparam.w != 0.0)
	gl_FragColor.rgb = mix(u_fogcolor.rgb, gl_FragColor.rgb, v_fogFactor);

}


#if !defined(LIGHT0_ENABLED)
	#define LIGHT0_ENABLED -1
#endif

#if !defined(LIGHT1_ENABLED)
	#define LIGHT1_ENABLED -1
#endif

#if !defined(LIGHT2_ENABLED)
	#define LIGHT2_ENABLED -1
#endif

// Structs
struct Light {
	// all lights
	vec4 position; // if directional light, this must be normalized (so that we dont have to normalize it here)
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	
	// point light & spotlight
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	// spotlight
	vec3 spotDirection;
	float spotExponent;
	float spotCutoffAngleCos;
};

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

// Uniforms
uniform bool u_light0Enabled;
uniform bool u_light1Enabled;
uniform bool u_light2Enabled;
uniform Light u_light0;
uniform Light u_light1;
uniform Light u_light2;
uniform Material u_material;

// Varyings
varying vec3 v_normal;
varying vec4 v_ambientAndEmission;
varying vec3 v_light0Vector;
varying vec3 v_light0HalfVector;
varying vec3 v_light1Vector;
varying vec3 v_light1HalfVector;
varying vec3 v_light2Vector;
varying vec3 v_light2HalfVector;

// Functions
vec4 calcDirectionalLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector);
vec4 calcPointLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector);
vec4 calcSpotLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector);
vec4 calcLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector);


vec4 calcPerFragmentLighting()
{
	vec4 color = v_ambientAndEmission;
#if LIGHT_MODEL_TWO_SIDE_ENABLED == 1
	vec3 normal = normalize(v_normal) * (gl_FrontFacing ? 1.0 : -1.0);
#elif LIGHT_MODEL_TWO_SIDE_ENABLED == 0
	vec3 normal = normalize(v_normal);
#else
	vec3 normal;
	if (u_lightModelTwoSideEnabled) {
		normal = normalize(v_normal) * (gl_FrontFacing ? 1.0 : -1.0);
	} else {
		normal = normalize(v_normal);
	}
#endif
	
	
#if LIGHT0_ENABLED == 1
	color += calcLight(u_light0, u_material, normal, v_light0Vector, v_light0HalfVector);
#elif LIGHT0_ENABLED == -1
	if (u_light0Enabled) {
		color += calcLight(u_light0, u_material, normal, v_light0Vector, v_light0HalfVector);
	}
#endif
	
#if LIGHT1_ENABLED == 1
	color += calcLight(u_light1, u_material, normal, v_light1Vector, v_light1HalfVector);
#elif LIGHT1_ENABLED == -1
	if (u_light1Enabled) {
		color += calcLight(u_light1, u_material, normal, v_light1Vector, v_light1HalfVector);
	}
#endif
	
#if LIGHT2_ENABLED == 1
	color += calcLight(u_light2, u_material, normal, v_light2Vector, v_light2HalfVector);
#elif LIGHT2_ENABLED == -1
	if (u_light2Enabled) {
		color += calcLight(u_light2, u_material, normal, v_light2Vector, v_light2HalfVector);
	}
#endif
	
	color.a = u_material.diffuse.a;
	
	return clamp(color, c_zerof, c_onef);
}

vec4 calcLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector) 
{
	vec4 color;
	if (light.position.w != c_zerof) {
		if (light.spotCutoffAngleCos > -c_onef) {
			color = calcSpotLight(light, material, normal, lightVector, halfVector);
		} else {
			color = calcPointLight(light, material, normal, lightVector, halfVector);
		}
	} else {
		color = calcDirectionalLight(light, material, normal, lightVector, halfVector);
	}
	
	return color;
}

float calcBasicAttenuationFactor(Light light, vec3 lightVector) 
{
	vec3 attenuationDistance;
	attenuationDistance.x = c_onef;
	attenuationDistance.z = dot(lightVector, lightVector);
	attenuationDistance.y = sqrt(attenuationDistance.z);
	return c_onef / dot(attenuationDistance, vec3(light.constantAttenuation, light.linearAttenuation, light.quadraticAttenuation));
}

float calcSpotFactor(Light light, vec3 lightVector)
{
	float spotFactor = dot(normalize(-lightVector), normalize(light.spotDirection));
	if (spotFactor >= light.spotCutoffAngleCos) {
		return pow(spotFactor, light.spotExponent);
	} else {
		return c_zerof;
	}
}

vec4 calcDirectionalLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector)
{
	float cosL = max(c_zerof, dot(normal, normalize(lightVector)));
	float cosH = dot(normal, normalize(halfVector));
	
	vec4 color = (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	return color;
}

vec4 calcPointLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector)
{
	// if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	
	float cosL = max(c_zerof, dot(normal, normalize(lightVector)));
	float cosH = dot(normal, normalize(halfVector));
	
	vec4 color = (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}

vec4 calcSpotLight(Light light, Material material, vec3 normal, vec3 lightVector, vec3 halfVector)
{
	// if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	attenuationFactor *= calcSpotFactor(light, lightVector);
	
	float cosL = max(c_zerof, dot(normal, normalize(lightVector)));
	float cosH = dot(normal, normalize(halfVector));

	vec4 color = (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}

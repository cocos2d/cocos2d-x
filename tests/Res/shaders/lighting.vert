#if !defined(LIGHT0_ENABLED)
	#define LIGHT0_ENABLED -1
#endif
#if !defined(LIGHT1_ENABLED)
	#define LIGHT1_ENABLED -1
#endif
#if !defined(LIGHT2_ENABLED)
	#define LIGHT2_ENABLED -1
#endif
#if !defined(LIGHTING_HINT)
	#define LIGHTING_HINT -1
#endif
#if !defined(LIGHT_MODEL_TWO_SIDE_ENABLED)
	#define LIGHT_MODEL_TWO_SIDE_ENABLED -1
#endif
struct Light {
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
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
uniform bool u_light0Enabled;
uniform bool u_light1Enabled;
uniform bool u_light2Enabled;
uniform Light u_light0;
uniform Light u_light1;
uniform Light u_light2;
uniform Material u_material;
uniform bool u_lightModelLocalViewerEnabled;
uniform bool u_lightModelTwoSideEnabled;
uniform vec4 u_globalAmbientColor;
uniform int u_lightingAccuracy;
void calcLightingVaryingsForFragmentShader();
vec4 calcPerVertexLighting();
void calcLighting()
{
#if LIGHT_MODEL_TWO_SIDE_ENABLED == 1 || LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	#if LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	if (u_lightModelTwoSideEnabled) {
	#endif
		#if LIGHTING_HINT == OGL_FASTEST
		v_frontColor = calcPerVertexLighting();
		normal = -normal;
		v_backColor = calcPerVertexLighting();
		#elif LIGHTING_HINT == OGL_NICEST
		calcLightingVaryingsForFragmentShader();
		#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			v_frontColor = calcPerVertexLighting();
			normal = -normal;
			v_backColor = calcPerVertexLighting();
		} else {
			calcLightingVaryingsForFragmentShader();
		}
		#endif
	#if LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	} else {
		#if LIGHTING_HINT == OGL_FASTEST
		v_frontColor = calcPerVertexLighting();
		#elif LIGHTING_HINT == OGL_NICEST
		calcLightingVaryingsForFragmentShader();
		#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			v_frontColor = calcPerVertexLighting();
		} else {
			calcLightingVaryingsForFragmentShader();
		}
		#endif
	}
	#endif
#else 
	#if LIGHTING_HINT == OGL_FASTEST
		v_frontColor = calcPerVertexLighting();
	#elif LIGHTING_HINT == OGL_NICEST
		calcLightingVaryingsForFragmentShader();
	#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			v_frontColor = calcPerVertexLighting();
		} else {
			calcLightingVaryingsForFragmentShader();
		}
	#endif
#endif
}

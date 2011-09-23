
// Varyings
varying vec4 v_ambientAndEmission;
varying vec3 v_normal;
varying vec3 v_light0Vector;
varying vec3 v_light0HalfVector;
varying vec3 v_light1Vector;
varying vec3 v_light1HalfVector;
varying vec3 v_light2Vector;
varying vec3 v_light2HalfVector;

// Functions
void calcLightVaryingsForFragmentShader(Light light, vec3 eyeVector, out vec3 lightVector, out vec3 halfVector);


void calcLightingVaryingsForFragmentShader()
{
	v_normal = normal;
	
	vec3 eyeVector;
	#if LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 1
	eyeVector = normalize(-vertexPositionInEye.xyz);
	#elif LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 0
	eyeVector = vec3(c_zerof, c_zerof, c_onef);
	#else
	if (u_lightModelLocalViewerEnabled) {
		eyeVector = normalize(-vertexPositionInEye.xyz);
	} else {
		eyeVector = vec3(c_zerof, c_zerof, c_onef);
	}
	#endif
	
	v_ambientAndEmission = u_material.ambient * u_globalAmbientColor;
	v_ambientAndEmission += u_material.emission;
	
	#if LIGHT0_ENABLED == 1
	calcLightVaryingsForFragmentShader(u_light0, eyeVector, v_light0Vector, v_light0HalfVector);
	#elif LIGHT0_ENABLED == -1
	if (u_light0Enabled) {
		calcLightVaryingsForFragmentShader(u_light0, eyeVector, v_light0Vector, v_light0HalfVector);
	}
	#endif
	
	#if LIGHT1_ENABLED == 1
	calcLightVaryingsForFragmentShader(u_light1, eyeVector, v_light1Vector, v_light1HalfVector);
	#elif LIGHT1_ENABLED == -1
	if (u_light1Enabled) {
		calcLightVaryingsForFragmentShader(u_light1, eyeVector, v_light1Vector, v_light1HalfVector);
	}
	#endif
	
	#if LIGHT2_ENABLED == 1
	calcLightVaryingsForFragmentShader(u_light2, eyeVector, v_light2Vector, v_light2HalfVector);
	#elif LIGHT2_ENABLED == -1
	if (u_light2Enabled) {
		calcLightVaryingsForFragmentShader(u_light2, eyeVector, v_light2Vector, v_light2HalfVector);
	}
	#endif
	
}

void calcLightVaryingsForFragmentShader(Light light, vec3 eyeVector, out vec3 lightVector, out vec3 halfVector)
{
	v_ambientAndEmission += light.ambient * u_material.ambient;
	if (light.position.w != c_zerof) {
		lightVector = light.position.xyz - vertexPositionInEye.xyz;
	} else {
		lightVector = light.position.xyz;
	}
	halfVector = normalize(eyeVector + lightVector);
}

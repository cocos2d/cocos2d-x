
// Functions
vec4 calcDirectionalLight(Light light);
vec4 calcDirectionalLightWithLocalViewer(Light light);
vec4 calcPointLight(Light light);
vec4 calcPointLightWithLocalViewer(Light light);
vec4 calcSpotLight(Light light);
vec4 calcSpotLightWithLocalViewer(Light light);
float calcBasicAttenuationFactor(Light light, vec3 lightVector);
float calcSpotFactor(Light light, vec3 lightVector);
vec4 calcLight(Light light);


vec4 calcPerVertexLighting()
{	
	// TODO: Test if faster with vec3 because alpha is just u_material.diffuse.a
	vec4 color = u_material.ambient * u_globalAmbientColor;
	color += u_material.emission;
	
	#if LIGHT0_ENABLED == 1
	color += calcLight(u_light0);
	#elif LIGHT0_ENABLED == -1
	if (u_light0Enabled) {
		color += calcLight(u_light0);
	}
	#endif
	
	#if LIGHT1_ENABLED == 1
	color += calcLight(u_light1);
	#elif LIGHT1_ENABLED == -1
	if (u_light1Enabled) {
		color += calcLight(u_light1);
	}
	#endif
	
	#if LIGHT2_ENABLED == 1
	color += calcLight(u_light2);
	#elif LIGHT2_ENABLED == -1
	if (u_light2Enabled) {
		color += calcLight(u_light2);
	}
	#endif	
	
	color.a = u_material.diffuse.a;
	
	return clamp(color, c_zerof, c_onef);
}

vec4 calcLight(Light light) 
{
	vec4 color;
#if LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 1
	#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1
	if (light.position.w != c_zerof) {
		if (light.spotCutoffAngleCos > -c_onef) {
			color = calcSpotLightWithLocalViewer(light);
		} else {
			color = calcPointLightWithLocalViewer(light);
		}
	} else {
		color = calcDirectionalLightWithLocalViewer(light);
	}
	#else
	color = calcDirectionalLightWithLocalViewer(light);
	#endif
#elif LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 0
	#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1
	if (light.position.w != c_zerof) {
		if (light.spotCutoffAngleCos > -c_onef) {
			color = calcSpotLight(light);
		} else {
			color = calcPointLight(light);
		}
	} else {
		color = calcDirectionalLight(light);
	}
	#else
	color = calcDirectionalLight(light);
	#endif
#else 
	if (u_lightModelLocalViewerEnabled) {
		#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1
		if (light.position.w != c_zerof) {
			if (light.spotCutoffAngleCos > -c_onef) {
				color = calcSpotLightWithLocalViewer(light);
			} else {
				color = calcPointLightWithLocalViewer(light);
			}
		} else {
			color = calcDirectionalLightWithLocalViewer(light);
		}
		#else
		color = calcDirectionalLightWithLocalViewer(light);
		#endif
	} else {
		#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1
		if (light.position.w != c_zerof) {
			if (light.spotCutoffAngleCos > -c_onef) {
				color = calcSpotLight(light);
			} else {
				color = calcPointLight(light);
			}
		} else {
			color = calcDirectionalLight(light);
		}
		#else
		color = calcDirectionalLight(light);
		#endif
	}
#endif
	
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

vec4 calcDirectionalLight(Light light)
{
	vec3 lightVector = light.position.xyz;
	vec3 eyeVector = vec3(c_zerof, c_zerof, c_onef);
	
	vec3 halfVector = normalize(eyeVector + lightVector); // TODO: This could be precomputed
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	return color;
}

vec4 calcDirectionalLightWithLocalViewer(Light light)
{
	vec3 lightVector = light.position.xyz;
	vec3 eyeVector = normalize(-vertexPositionInEye.xyz);
	
	vec3 halfVector = normalize(eyeVector + lightVector);
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	return color;
}

vec4 calcPointLight(Light light)
{
	vec3 lightVector = light.position.xyz - vertexPositionInEye.xyz;
	
	// TODO: if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	
	lightVector = normalize(lightVector);
	
	vec3 eyeVector = vec3(c_zerof, c_zerof, c_onef);
	
	vec3 halfVector = normalize(eyeVector + lightVector);
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}


vec4 calcPointLightWithLocalViewer(Light light)
{
	vec3 lightVector = light.position.xyz - vertexPositionInEye.xyz;
	
	// TODO: if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	
	lightVector = normalize(lightVector);
	
	vec3 eyeVector = normalize(-vertexPositionInEye.xyz);
	
	vec3 halfVector = normalize(eyeVector + lightVector);
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}

vec4 calcSpotLight(Light light)
{
	vec3 lightVector = light.position.xyz - vertexPositionInEye.xyz;
	
	// TODO: if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	attenuationFactor *= calcSpotFactor(light, lightVector);
	
	lightVector = normalize(lightVector);
	
	vec3 eyeVector = vec3(c_zerof, c_zerof, c_onef);
	
	vec3 halfVector = normalize(eyeVector + lightVector);
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}

vec4 calcSpotLightWithLocalViewer(Light light)
{
	vec3 lightVector = light.position.xyz - vertexPositionInEye.xyz;
	
	// TODO: if clause here because of heavy computation?
	float attenuationFactor = calcBasicAttenuationFactor(light, lightVector);
	attenuationFactor *= calcSpotFactor(light, lightVector);
	
	lightVector = normalize(lightVector);
	
	vec3 eyeVector = normalize(-vertexPositionInEye.xyz);
	
	vec3 halfVector = normalize(eyeVector + lightVector);
	float cosL = max(c_zerof, dot(normal, lightVector));
	float cosH = dot(normal, halfVector);
	
	vec4 color = (light.ambient * u_material.ambient);
	color += (light.diffuse * u_material.diffuse) * cosL;
	if (cosH > c_zerof) {
		color += (u_material.specular * light.specular) * pow(cosH, u_material.shininess);
	}
	
	color *= attenuationFactor;
	
	return color;
}

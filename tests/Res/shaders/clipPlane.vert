
// Uniforms
uniform bool u_clipPlane0Enabled;
uniform bool u_clipPlane1Enabled;
uniform bool u_clipPlane2Enabled;
uniform bool u_clipPlane3Enabled;
uniform bool u_clipPlane4Enabled;
uniform bool u_clipPlane5Enabled;
uniform vec4 u_clipPlane0Equation;
uniform vec4 u_clipPlane1Equation;
uniform vec4 u_clipPlane2Equation;
uniform vec4 u_clipPlane3Equation;
uniform vec4 u_clipPlane4Equation;
uniform vec4 u_clipPlane5Equation;

// Varyings
varying float v_clipPlane0Distance;
varying float v_clipPlane1Distance;
varying float v_clipPlane2Distance;
varying float v_clipPlane3Distance;
varying float v_clipPlane4Distance;
varying float v_clipPlane5Distance;

void calcClipPlanes() 
{
	#if CLIP_PLANE0_ENABLED == 1 || CLIP_PLANE0_ENABLED == -1
	#if CLIP_PLANE0_ENABLED == -1
	if (u_clipPlane0Enabled) {
		#endif
		v_clipPlane0Distance = dot(vertexPositionInEye, u_clipPlane0Equation);
		#if CLIP_PLANE0_ENABLED == -1
	}	
	#endif
	#endif
	
	#if CLIP_PLANE1_ENABLED == 1 || CLIP_PLANE1_ENABLED == -1
	#if CLIP_PLANE1_ENABLED == -1
	if (u_clipPlane1Enabled) {
		#endif
		v_clipPlane1Distance = dot(vertexPositionInEye, u_clipPlane1Equation);
		#if CLIP_PLANE1_ENABLED == -1
	}	
	#endif
	#endif
	
	#if CLIP_PLANE2_ENABLED == 1 || CLIP_PLANE2_ENABLED == -1
	#if CLIP_PLANE2_ENABLED == -1
	if (u_clipPlane2Enabled) {
		#endif
		v_clipPlane2Distance = dot(vertexPositionInEye, u_clipPlane2Equation);
		#if CLIP_PLANE2_ENABLED == -1
	}	
	#endif
	#endif
	
	#if CLIP_PLANE3_ENABLED == 1 || CLIP_PLANE3_ENABLED == -1
	#if CLIP_PLANE3_ENABLED == -1
	if (u_clipPlane3Enabled) {
		#endif
		v_clipPlane3Distance = dot(vertexPositionInEye, u_clipPlane3Equation);
		#if CLIP_PLANE3_ENABLED == -1
	}	
	#endif
	#endif
	
	#if CLIP_PLANE4_ENABLED == 1 || CLIP_PLANE4_ENABLED == -1
	#if CLIP_PLANE4_ENABLED == -1
	if (u_clipPlane4Enabled) {
		#endif
		v_clipPlane4Distance = dot(vertexPositionInEye, u_clipPlane4Equation);
		#if CLIP_PLANE4_ENABLED == -1
	}	
	#endif
	#endif
	
	#if CLIP_PLANE5_ENABLED == 1 || CLIP_PLANE5_ENABLED == -1
	#if CLIP_PLANE5_ENABLED == -1
	if (u_clipPlane5Enabled) {
		#endif
		v_clipPlane5Distance = dot(vertexPositionInEye, u_clipPlane5Equation);
		#if CLIP_PLANE5_ENABLED == -1
	}	
	#endif
	#endif
}

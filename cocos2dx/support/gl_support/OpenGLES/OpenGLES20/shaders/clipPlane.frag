
// Uniforms
uniform bool u_clipPlane0Enabled;
uniform bool u_clipPlane1Enabled;
uniform bool u_clipPlane2Enabled;
uniform bool u_clipPlane3Enabled;
uniform bool u_clipPlane4Enabled;
uniform bool u_clipPlane5Enabled;

// Varyings
varying float v_clipPlane0Distance;
varying float v_clipPlane1Distance;
varying float v_clipPlane2Distance;
varying float v_clipPlane3Distance;
varying float v_clipPlane4Distance;
varying float v_clipPlane5Distance;

void clipPlanesTest() 
{
#if CLIP_PLANE0_ENABLED == 1 || CLIP_PLANE0_ENABLED == -1
	#if CLIP_PLANE0_ENABLED == -1
	if (u_clipPlane0Enabled) {
	#endif
		if (v_clipPlane0Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE0_ENABLED == -1
	}	
	#endif
#endif
	
#if CLIP_PLANE1_ENABLED == 1 || CLIP_PLANE1_ENABLED == -1
	#if CLIP_PLANE1_ENABLED == -1
	if (u_clipPlane1Enabled) {
	#endif
		if (v_clipPlane1Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE1_ENABLED == -1
	}	
	#endif
#endif
	
#if CLIP_PLANE2_ENABLED == 1 || CLIP_PLANE2_ENABLED == -1
	#if CLIP_PLANE2_ENABLED == -1
	if (u_clipPlane2Enabled) {
	#endif
		if (v_clipPlane2Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE2_ENABLED == -1
	}	
	#endif
#endif
	
#if CLIP_PLANE3_ENABLED == 1 || CLIP_PLANE3_ENABLED == -1
	#if CLIP_PLANE3_ENABLED == -1
	if (u_clipPlane3Enabled) {
	#endif
		if (v_clipPlane3Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE3_ENABLED == -1
	}	
	#endif
#endif
	
#if CLIP_PLANE4_ENABLED == 1 || CLIP_PLANE4_ENABLED == -1
	#if CLIP_PLANE4_ENABLED == -1
	if (u_clipPlane4Enabled) {
	#endif
		if (v_clipPlane4Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE4_ENABLED == -1
	}	
	#endif
#endif
	
#if CLIP_PLANE5_ENABLED == 1 || CLIP_PLANE5_ENABLED == -1
	#if CLIP_PLANE5_ENABLED == -1
	if (u_clipPlane5Enabled) {
	#endif
		if (v_clipPlane5Distance < 0.0) {
			discard;
		}
	#if CLIP_PLANE5_ENABLED == -1
	}	
	#endif
#endif
}

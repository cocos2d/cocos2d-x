#if !defined(LIGHTING_HINT)
	#define LIGHTING_HINT -1
#endif
#if !defined(LIGHT_MODEL_TWO_SIDE_ENABLED)
	#define LIGHT_MODEL_TWO_SIDE_ENABLED -1
#endif
uniform int u_lightingHint;
uniform bool u_lightModelTwoSideEnabled;
uniform int u_lightingAccuracy;
varying vec4 v_backColor;
vec4 calcPerFragmentLighting();
void calcLighting(out vec4 color)
{
#if LIGHT_MODEL_TWO_SIDE_ENABLED == 1 ||  LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	#if LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	if (u_lightModelTwoSideEnabled) {
	#endif
	if (gl_FrontFacing) {
		#if LIGHTING_HINT == OGL_FASTEST
		color = v_frontColor;
		#elif LIGHTING_HINT == OGL_NICEST
		color = calcPerFragmentLighting();
		#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			color = v_frontColor;
		} else if (u_lightingAccuracy == OGL_NICEST) {
			color = calcPerFragmentLighting();
		}
		#endif
	} else {
		#if LIGHTING_HINT == OGL_FASTEST
		color = v_backColor;
		#elif LIGHTING_HINT == OGL_NICEST
		color = calcPerFragmentLighting();
		#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			color = v_backColor;
		} else if (u_lightingAccuracy == OGL_NICEST) {
			color = calcPerFragmentLighting();
		}
		#endif
	}
	#if LIGHT_MODEL_TWO_SIDE_ENABLED == -1
	} else {
		#if LIGHTING_HINT == OGL_FASTEST
		color = v_frontColor;
		#elif LIGHTING_HINT == OGL_NICEST
		color = calcPerFragmentLighting();
		#elif LIGHTING_HINT == -1
		if (u_lightingAccuracy == OGL_FASTEST) {
			color = v_frontColor;
		} else if (u_lightingAccuracy == OGL_NICEST) {
			color = calcPerFragmentLighting();
		}
		#endif
	}
	#endif
#elif LIGHT_MODEL_TWO_SIDE_ENABLED == 0
	#if LIGHTING_HINT == OGL_FASTEST
	color = v_frontColor;
	#elif LIGHTING_HINT == OGL_NICEST
	color = calcPerFragmentLighting();
	#elif LIGHTING_HINT == -1
	if (u_lightingAccuracy == OGL_FASTEST) {
		color = v_frontColor;
		} else if (u_lightingAccuracy == OGL_NICEST) {
	color = calcPerFragmentLighting();
	}
	#endif
#endif
}

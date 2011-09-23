
#ifdef GL_FRAGMENT_PRECISION_HIGH
	precision highp float;
#else
	precision mediump float;
#endif

#define GL_FASTEST 0x1101
#define GL_NICEST 0x1102

#if !defined(TEXTURE0_ENABLED)
	#define TEXTURE0_ENABLED -1
#endif

#if !defined(TEXTURE1_ENABLED)
	#define TEXTURE1_ENABLED -1
#endif

#if !defined(TEXTURE2_ENABLED)
	#define TEXTURE2_ENABLED -1
#endif

#if !defined(FOG_ENABLED)
	#define FOG_ENABLED -1
#endif

#if !defined(FOG_HINT)
	#define FOG_HINT -1
#endif

#if !defined(LIGHTING_ENABLED)
	#define LIGHTING_ENABLED -1
#endif

#if !defined(ALPHA_TEST_ENABLED)
	#define ALPHA_TEST_ENABLED -1
#endif

#if !defined(CLIP_PLANE0_ENABLED)
	#define CLIP_PLANE0_ENABLED -1
#endif

#if !defined(CLIP_PLANE1_ENABLED)
	#define CLIP_PLANE1_ENABLED -1
#endif

#if !defined(CLIP_PLANE2_ENABLED)
	#define CLIP_PLANE2_ENABLED -1
#endif

#if !defined(CLIP_PLANE3_ENABLED)
	#define CLIP_PLANE3_ENABLED -1
#endif

#if !defined(CLIP_PLANE4_ENABLED)
	#define CLIP_PLANE4_ENABLED -1
#endif

#if !defined(CLIP_PLANE5_ENABLED)
	#define CLIP_PLANE5_ENABLED -1
#endif

// Uniforms
uniform bool u_fogEnabled;
uniform vec3 u_fogColor;
uniform int u_fogHint;
uniform bool u_alphaTestEnabled;
uniform bool u_lightingEnabled;

// Varyings
varying vec4 v_frontColor;
varying float v_fogFactor;
varying float v_eyeDistance;

// Shader constants
const int c_zero = 0;
const int c_one = 1;
const float c_zerof = 0.0;
const float c_onef = 1.0;

// Funtions
float calcFogFactor(float distanceToEye);
void calcLighting(out vec4 color);
void clipPlanesTest();
void alphaTest(float alpha);
void calcTextureColorContribution(inout vec4 color);


void main() 
{
#if CLIP_PLANE0_ENABLED != 0 || CLIP_PLANE1_ENABLED != 0 || CLIP_PLANE2_ENABLED != 0 || CLIP_PLANE3_ENABLED != 0 || CLIP_PLANE4_ENABLED != 0 || CLIP_PLANE5_ENABLED != 0
	clipPlanesTest();
#endif
	
	vec4 color;
#if LIGHTING_ENABLED == 1
	calcLighting(color);
#elif LIGHTING_ENABLED == 0
	color = v_frontColor;
#else
	if (u_lightingEnabled) {
		calcLighting(color);
	} else {
		color = v_frontColor;
	}
#endif
	
#if TEXTURE0_ENABLED != 0 || TEXTURE1_ENABLED != 0 || TEXTURE2_ENABLED != 0
	calcTextureColorContribution(color);
#endif
	
#if ALPHA_TEST_ENABLED == 1 || ALPHA_TEST_ENABLED == -1
	#if ALPHA_TEST_ENABLED == -1
	if (u_alphaTestEnabled) {
	#endif
	alphaTest(color.a);
	#if ALPHA_TEST_ENABLED == -1
	}
	#endif
#endif
	
#if FOG_ENABLED == 1 || FOG_ENABLED == -1
	#if FOG_ENABLED == -1
	if (u_fogEnabled) {
	#endif
		
	float fogFactor;
	#if FOG_HINT == GL_FASTEST
		fogFactor = v_fogFactor;
	#elif FOG_HINT == GL_NICEST
		fogFactor = calcFogFactor(v_eyeDistance);
	#elif FOG_HINT == -1
		if (u_fogHint == GL_FASTEST) {
			fogFactor = v_fogFactor;
		} else {
			fogFactor = calcFogFactor(v_eyeDistance);
		}
	#endif
	color.rgb = mix(u_fogColor, color.rgb, fogFactor);
	
	#if FOG_ENABLED == -1
	}
	#endif
#endif
	
	gl_FragColor = color;
}

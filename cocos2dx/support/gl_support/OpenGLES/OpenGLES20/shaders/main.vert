#define GL_FASTEST 0x1101
#define GL_NICEST 0x1102

#if !defined(LIGHTING_ENABLED)
	#define LIGHTING_ENABLED -1
#endif

#if !defined(FOG_ENABLED)
	#define FOG_ENABLED -1
#endif

#if !defined(POSITION_ENABLED)
	#define POSITION_ENABLED -1
#endif

#if !defined(NORMAL_ENABLED)
	#define NORMAL_ENABLED -1
#endif

#if !defined(COLOR_ENABLED)
	#define COLOR_ENABLED -1
#endif

#if !defined(NORMALIZE_ENABLED)
	#define NORMALIZE_ENABLED -1
#endif

#if !defined(RESCALE_NORMAL_ENABLED)
	#define RESCALE_NORMAL_ENABLED -1
#endif

#if !defined(FOG_HINT)
	#define FOG_HINT -1
#endif

#if !defined(TEXCOORD0_ENABLED)
	#define TEXCOORD0_ENABLED -1
#endif

#if !defined(TEXCOORD1_ENABLED)
	#define TEXCOORD1_ENABLED -1
#endif

#if !defined(TEXCOORD2_ENABLED)
	#define TEXCOORD2_ENABLED -1
#endif

#if !defined(TEXTURE0_ENABLED)
	#define TEXTURE0_ENABLED -1
#endif

#if !defined(TEXTURE1_ENABLED)
	#define TEXTURE1_ENABLED -1
#endif

#if !defined(TEXTURE2_ENABLED)
	#define TEXTURE2_ENABLED -1
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

#if !defined(NON_DIRECTIONAL_LIGHT_ENABLED)
	#define NON_DIRECTIONAL_LIGHT_ENABLED -1
#endif

#if !defined(LIGHT_MODEL_LOCAL_VIEWER_ENABLED)
	#define LIGHT_MODEL_LOCAL_VIEWER_ENABLED -1
#endif

precision highp float;
precision highp int;

// Attributes
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec3 a_normal;

// Uniforms
uniform bool u_positionEnabled;
uniform bool u_normalEnabled;
uniform bool u_colorEnabled;
uniform mat4 u_modelViewMatrix;
uniform mat4 u_modelViewProjectionMatrix;
uniform mat3 u_transposeAdjointModelViewMatrix;
uniform bool u_lightingEnabled;
uniform bool u_normalizeEnabled;
uniform bool u_rescaleNormalEnabled;
uniform float u_rescaleNormalFactor;
uniform bool u_fogEnabled;
uniform int u_fogHint;
uniform int u_lightingHint;

// Varyings
varying vec4 v_frontColor;
varying vec4 v_backColor;
varying float v_fogFactor;
varying float v_eyeDistance;

// Shader constants
const int c_zero = 0;
const int c_one = 1;
const float c_zerof = 0.0;
const float c_onef = 1.0;

// Shader variables
vec3 normal;
vec4 vertexPositionInEye;

// Functions
void calcLighting();
float calcFogFactor(float distanceToEye);
void calcClipPlanes();
void calcTextureCoordinates();

void main() 
{
#if POSITION_ENABLED == 1
	gl_Position = u_modelViewProjectionMatrix * a_position;
#elif POSITION_ENABLED == -1
	if (u_positionEnabled) {
		gl_Position = u_modelViewProjectionMatrix * a_position;
	}
#endif
	
#if (TEXTURE0_ENABLED != 0 && TEXCOORD0_ENABLED != 0) || (TEXTURE1_ENABLED != 0 && TEXCOORD1_ENABLED != 0) || (TEXTURE2_ENABLED != 0 && TEXCOORD2_ENABLED != 0)
	calcTextureCoordinates();
#endif
	
#if NORMAL_ENABLED == 1
	normal = u_transposeAdjointModelViewMatrix * a_normal;
	#if RESCALE_NORMAL_ENABLED == 1
		normal = normal * u_rescaleNormalFactor;
	#elif RESCALE_NORMAL_ENABLED == -1
		if (u_rescaleNormalEnabled) {
			normal = normal * u_rescaleNormalFactor;
		}
	#endif
	#if NORMALIZE_ENABLED == 1
		normal = normalize(normal);
	#elif NORMALIZE_ENABLED == -1
		if (u_normalizeEnabled) {
			normal = normalize(normal);
		}
	#endif
#elif NORMAL_ENABLED == 0
	normal = vec3(c_zerof, c_zerof, c_onef);
#elif NORMAL_ENABLED == -1
	if (u_normalEnabled) {
		normal = u_transposeAdjointModelViewMatrix * a_normal;
		#if RESCALE_NORMAL_ENABLED == 1
			normal = normal * u_rescaleNormalFactor;
		#elif RESCALE_NORMAL_ENABLED == -1
			if (u_rescaleNormalEnabled) {
				normal = normal * u_rescaleNormalFactor;
			}
		#endif
		#if NORMALIZE_ENABLED == 1
			normal = normalize(normal);
		#elif NORMALIZE_ENABLED == -1
			if (u_normalizeEnabled) {
				normal = normalize(normal);
			}
		#endif
	} else {
		normal = vec3(c_zerof, c_zerof, c_onef);
	}
#endif
	
	vec4 color;
#if COLOR_ENABLED == 1
	color = vec4(a_color.r / 255.0, a_color.g / 255.0, a_color.b / 255.0, a_color.a / 255.0);
#elif COLOR_ENABLED == 0
	color = vec4(c_onef, c_onef, c_onef, c_onef);
#elif COLOR_ENABLED == -1
	color = u_colorEnabled ? a_color : vec4(c_onef, c_onef, c_onef, c_onef);
#endif
	
#if FOG_ENABLED == 1 || (LIGHTING_ENABLED == 1 && (NON_DIRECTIONAL_LIGHT_ENABLED != 0 || LIGHT_MODEL_LOCAL_VIEWER_ENABLED != 0)) || CLIP_PLANE0_ENABLED != 0 || CLIP_PLANE1_ENABLED != 0 || CLIP_PLANE2_ENABLED != 0 || CLIP_PLANE3_ENABLED !=0 || CLIP_PLANE4_ENABLED != 0 || CLIP_PLANE5_ENABLED != 0
	vertexPositionInEye = u_modelViewMatrix * a_position;
#elif FOG_ENABLED == -1 && LIGHTING_ENABLED == -1
	if (u_fogEnabled) {
		vertexPositionInEye = u_modelViewMatrix * a_position;
	} else if (u_lightingEnabled) {
		#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1 || LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 1 || LIGHT_MODEL_LOCAL_VIEWER_ENABLED == -1
		vertexPositionInEye = u_modelViewMatrix * a_position;
		#endif
	}
#elif FOG_ENABLED == -1
	if (u_fogEnabled) {
		vertexPositionInEye = u_modelViewMatrix * a_position;
	}
#elif LIGHTING_ENABLED == -1
	if (u_lightingEnabled) {
		#if NON_DIRECTIONAL_LIGHT_ENABLED == 1 || NON_DIRECTIONAL_LIGHT_ENABLED == -1 || LIGHT_MODEL_LOCAL_VIEWER_ENABLED == 1 || LIGHT_MODEL_LOCAL_VIEWER_ENABLED == -1
		vertexPositionInEye = u_modelViewMatrix * a_position;
		#endif
	}
#endif

#if LIGHTING_ENABLED == 1
	calcLighting();
#elif LIGHTING_ENABLED == 0
	v_frontColor = color;
#else
	if (u_lightingEnabled) {
		calcLighting();
	} else {
		v_frontColor = color;
	}
#endif
	
#if FOG_ENABLED == 1 || FOG_ENABLED == -1
	#if FOG_ENABLED == -1
	if (u_fogEnabled) {
	#endif
		
	#if FOG_HINT == GL_FASTEST
		v_fogFactor = calcFogFactor(-vertexPositionInEye.z);
	#elif FOG_HINT == GL_NICEST
		v_eyeDistance = -vertexPositionInEye.z;
	#elif FOG_HINT == -1
		if (u_fogHint == GL_FASTEST) {
			v_fogFactor = calcFogFactor(-vertexPositionInEye.z);
		} else {
			v_eyeDistance = -vertexPositionInEye.z;
		}
	#endif
		
	#if FOG_ENABLED == -1
	}
	#endif
#endif
	
#if CLIP_PLANE0_ENABLED != 0 || CLIP_PLANE1_ENABLED != 0 || CLIP_PLANE2_ENABLED != 0 || CLIP_PLANE3_ENABLED !=0 || CLIP_PLANE4_ENABLED != 0 || CLIP_PLANE5_ENABLED != 0
	calcClipPlanes();
#endif
}

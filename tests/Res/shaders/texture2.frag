

#if !defined(TEXCOORD2_ENABLED)
	#define TEXCOORD2_ENABLED -1
#endif

#if !defined(TEXTURE2_FORMAT)
	#define TEXTURE2_FORMAT -1
#endif

#if !defined(TEXTURE2_ENV_MODE)
	#define TEXTURE2_ENV_MODE -1
#endif

#if !defined(TEXTURE2_ENV_COMBINE_RGB)
	#define TEXTURE2_ENV_COMBINE_RGB -1
#endif

#if !defined(TEXTURE2_ENV_COMBINE_ALPHA)
	#define TEXTURE2_ENV_COMBINE_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_SRC0_RGB)
	#define TEXTURE2_ENV_SRC0_RGB -1
#endif

#if !defined(TEXTURE2_ENV_SRC1_RGB)
	#define TEXTURE2_ENV_SRC1_RGB -1
#endif

#if !defined(TEXTURE2_ENV_SRC2_RGB)
	#define TEXTURE2_ENV_SRC2_RGB -1
#endif

#if !defined(TEXTURE2_ENV_SRC0_ALPHA)
	#define TEXTURE2_ENV_SRC0_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_SRC1_ALPHA)
	#define TEXTURE2_ENV_SRC1_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_SRC2_ALPHA)
	#define TEXTURE2_ENV_SRC2_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND0_RGB)
	#define TEXTURE2_ENV_OPERAND0_RGB -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND1_RGB)
	#define TEXTURE2_ENV_OPERAND1_RGB -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND2_RGB)
	#define TEXTURE2_ENV_OPERAND2_RGB -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND0_ALPHA)
	#define TEXTURE2_ENV_OPERAND0_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND1_ALPHA)
	#define TEXTURE2_ENV_OPERAND1_ALPHA -1
#endif

#if !defined(TEXTURE2_ENV_OPERAND2_ALPHA)
	#define TEXTURE2_ENV_OPERAND2_ALPHA -1
#endif

uniform sampler2D u_texture2Sampler;
uniform int u_texture2Format;
uniform bool u_texCoord2Enabled;
uniform int u_texture2EnvMode;
uniform vec4 u_texture2EnvColor;
uniform int u_texture2EnvCombineRGB;
uniform int u_texture2EnvCombineAlpha;
uniform float u_texture2EnvRGBScale;
uniform float u_texture2EnvAlphaScale;
uniform float u_texture2EnvBlurAmount;

varying vec4 v_texCoord2;


void fetchTexture2Color()
{
	vec4 texCoord2;
#if TEXCOORD2_ENABLED == 1
	texCoord2 = v_texCoord2;
#elif TEXCOORD2_ENABLED == 0
	texCoord2 = vec4(c_zerof, c_zerof, c_zerof, c_zerof);
#elif TEXCOORD2_ENABLED == -1
	if (u_texCoord2Enabled) {
		texCoord2 = v_texCoord2;
	} else {
		texCoord2 = vec4(c_zerof, c_zerof, c_zerof, c_zerof);
	}
#endif

#if TEXTURE2_ENABLED == 1 || TEXTURE2_ENABLED == -1
	#if TEXTURE2_ENABLED == -1
	if (u_texture2Enabled) {
	#endif
		texture2Color = texture2D(u_texture2Sampler, texCoord2.st);
	#if TEXTURE2_ENABLED == -1
	}
	#endif
#endif
}

void calcTexture2Environment(inout vec4 color)
{	
#if TEXTURE2_ENV_MODE == OGL_MODULATE
	#if TEXTURE2_FORMAT == OGL_ALPHA
		color.a = color.a * texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE
		color.rgb = color.rgb * texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE_ALPHA
		color = color * texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_RGB
		color.rgb = color.rgb * texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_RGBA
		color = color * texture2Color;
	#endif
#elif TEXTURE2_ENV_MODE == OGL_ADD
	#if TEXTURE2_FORMAT == OGL_ALPHA
		color.a = color.a * texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE
		color.rgb = color.rgb + texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE_ALPHA
		color.rgb = color.rgb + texture2Color.rgb;
		color.a = color.a * texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_RGB
		color.rgb = color.rgb + texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_RGBA
		color.rgb = color.rgb + texture2Color.rgb;
		color.a = color.a * texture2Color.a;
	#endif
#elif TEXTURE2_ENV_MODE == OGL_DECAL
	#if TEXTURE2_FORMAT == OGL_ALPHA
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE_ALPHA
	#elif TEXTURE2_FORMAT == OGL_RGB
		color.rgb = texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_RGBA
		color.rgb = mix(color.rgb, texture2Color.rgb, texture2Color.a);
	#endif
#elif TEXTURE2_ENV_MODE == OGL_BLEND
	#if TEXTURE2_FORMAT == OGL_ALPHA
		color.a = color.a * texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE
		color.rgb = mix(color.rgb, u_texture2EnvColor.rgb, texture2Color.rgb);
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE_ALPHA
		color.rgb = mix(color.rgb, u_texture2EnvColor.rgb, texture2Color.rgb);
		color.a = color.a * texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_RGB
		color.rgb = mix(color.rgb, u_texture2EnvColor.rgb, texture2Color.rgb);
	#elif TEXTURE2_FORMAT == OGL_RGBA
		color.rgb = mix(color.rgb, u_texture2EnvColor.rgb, texture2Color.rgb);
		color.a = color.a * texture2Color.a;
	#endif
#elif TEXTURE2_ENV_MODE == OGL_REPLACE
	#if TEXTURE2_FORMAT == OGL_ALPHA
		color.a = texture2Color.a;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE
		color.rgb = texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_LUMINANCE_ALPHA
		color = texture2Color;
	#elif TEXTURE2_FORMAT == OGL_RGB
		color.rgb = texture2Color.rgb;
	#elif TEXTURE2_FORMAT == OGL_RGBA
		color = texture2Color;
	#endif
#elif TEXTURE2_ENV_MODE == OGL_BLUR
	vec4 sample0 = texture2Color;
	vec4 sample1 = texture2D(u_texture2Sampler, vec2(v_texCoord2.s - u_texture2EnvBlurAmount, v_texCoord2.t - u_texture2EnvBlurAmount));
	vec4 sample2 = texture2D(u_texture2Sampler, vec2(v_texCoord2.s + u_texture2EnvBlurAmount, v_texCoord2.t + u_texture2EnvBlurAmount));
	vec4 sample3 = texture2D(u_texture2Sampler, vec2(v_texCoord2.s - u_texture2EnvBlurAmount, v_texCoord2.t + u_texture2EnvBlurAmount));
	vec4 sample4 = texture2D(u_texture2Sampler, vec2(v_texCoord2.s + u_texture2EnvBlurAmount, v_texCoord2.t - u_texture2EnvBlurAmount));
	color = (sample0 + sample1 + sample2 + sample3 + sample4) / 5.0;
#elif TEXTURE2_ENV_MODE == OGL_COMBINE
	vec4 arg0;
	vec4 arg1;
	vec4 arg2;

	#if TEXTURE2_ENV_SRC0_RGB == 0
		arg0.rgb = texture0Color.rgb;
	#elif TEXTURE2_ENV_SRC0_RGB == 1
		arg0.rgb = texture1Color.rgb;
	#elif TEXTURE2_ENV_SRC0_RGB == 2
		arg0.rgb = texture2Color.rgb;
	#elif TEXTURE2_ENV_SRC0_RGB == OGL_CONSTANT
		arg0.rgb = u_texture2EnvColor.rgb;
	#elif TEXTURE2_ENV_SRC0_RGB == OGL_PRIMARY_COLOR
		arg0.rgb = v_frontColor.rgb;
	#elif TEXTURE2_ENV_SRC0_RGB == OGL_PREVIOUS
		arg0.rgb = color.rgb;
	#endif

	#if TEXTURE2_ENV_OPERAND0_RGB == OGL_ONE_MINUS_SRC_COLOR
		arg0.rgb = 1.0 - arg0.rgb;
	#endif
		
	#if TEXTURE2_ENV_SRC1_RGB == 0
		arg1.rgb = texture0Color.rgb;
	#elif TEXTURE2_ENV_SRC1_RGB == 1
		arg1.rgb = texture1Color.rgb;
	#elif TEXTURE2_ENV_SRC1_RGB == 2
		arg1.rgb = texture2Color.rgb;
	#elif TEXTURE2_ENV_SRC1_RGB == OGL_CONSTANT
		arg1.rgb = u_texture2EnvColor.rgb;
	#elif TEXTURE2_ENV_SRC1_RGB == OGL_PRIMARY_COLOR
		arg1.rgb = v_frontColor.rgb;
	#elif TEXTURE2_ENV_SRC1_RGB == OGL_PREVIOUS
		arg1.rgb = color.rgb;
	#endif
	
	#if TEXTURE2_ENV_OPERAND0_RGB == OGL_ONE_MINUS_SRC_COLOR
		arg1.rgb = 1.0 - arg1.rgb;
	#endif

	#if TEXTURE2_ENV_SRC2_RGB == 0
		arg2.rgb = texture0Color.rgb;
	#elif TEXTURE2_ENV_SRC2_RGB == 1
		arg2.rgb = texture1Color.rgb;
	#elif TEXTURE2_ENV_SRC2_RGB == 2
		arg2.rgb = texture2Color.rgb;
	#elif TEXTURE2_ENV_SRC2_RGB == OGL_CONSTANT
		arg2.rgb = u_texture2EnvColor.rgb;
	#elif TEXTURE2_ENV_SRC2_RGB == OGL_PRIMARY_COLOR
		arg2.rgb = v_frontColor.rgb;
	#elif TEXTURE2_ENV_SRC2_RGB == OGL_PREVIOUS
		arg2.rgb = color.rgb;
	#endif
		
	#if TEXTURE2_ENV_OPERAND2_RGB == OGL_ONE_MINUS_SRC_COLOR
		arg2.rgb = 1.0 - arg2.rgb;
	#endif
		
	#if TEXTURE2_ENV_SRC0_ALPHA == 0
		arg0.a = texture0Color.a;
	#elif TEXTURE2_ENV_SRC0_ALPHA == 1
		arg0.a = texture1Color.a;
	#elif TEXTURE2_ENV_SRC0_ALPHA == 2
		arg0.a = texture2Color.a;
	#elif TEXTURE2_ENV_SRC0_ALPHA == OGL_CONSTANT
		arg0.a = u_texture2EnvColor.a;
	#elif TEXTURE2_ENV_SRC0_ALPHA == OGL_PRIMARY_COLOR
		arg0.a = v_frontColor.a;
	#elif TEXTURE2_ENV_SRC0_ALPHA == OGL_PREVIOUS
		arg0.a = color.a;
	#endif
		
	#if TEXTURE2_ENV_OPERAND0_ALPHA == OGL_ONE_MINUS_SRC_ALPHA
		arg0.a = 1.0 - arg0.a;
	#endif
		
	#if TEXTURE2_ENV_SRC1_ALPHA == 0
		arg1.a = texture0Color.a;
	#elif TEXTURE2_ENV_SRC1_ALPHA == 1
		arg1.a = texture1Color.a;
	#elif TEXTURE2_ENV_SRC1_ALPHA == 2
		arg1.a = texture2Color.a;
	#elif TEXTURE2_ENV_SRC1_ALPHA == OGL_CONSTANT
		arg1.a = u_texture2EnvColor.a;
	#elif TEXTURE2_ENV_SRC1_ALPHA == OGL_PRIMARY_COLOR
		arg1.a = v_frontColor.a;
	#elif TEXTURE2_ENV_SRC1_ALPHA == OGL_PREVIOUS
		arg1.a = color.a;
	#endif
		
	#if TEXTURE2_ENV_OPERAND0_ALPHA == OGL_ONE_MINUS_SRC_ALPHA
		arg1.a = 1.0 - arg1.a;
	#endif
		
	#if TEXTURE2_ENV_SRC2_ALPHA == 0
		arg2.a = texture0Color.a;
	#elif TEXTURE2_ENV_SRC2_ALPHA == 1
		arg2.a = texture1Color.a;
	#elif TEXTURE2_ENV_SRC2_ALPHA == 2
		arg2.a = texture2Color.a;
	#elif TEXTURE2_ENV_SRC2_ALPHA == OGL_CONSTANT
		arg2.a = u_texture2EnvColor.a;
	#elif TEXTURE2_ENV_SRC2_ALPHA == OGL_PRIMARY_COLOR
		arg2.a = v_frontColor.a;
	#elif TEXTURE2_ENV_SRC2_ALPHA == OGL_PREVIOUS
		arg2.a = color.a;
	#endif
		
	#if TEXTURE2_ENV_OPERAND2_ALPHA == OGL_ONE_MINUS_SRC_ALPHA
		arg2.a = 1.0 - arg2.a;
	#endif
		
	#if TEXTURE2_ENV_COMBINE_RGB == OGL_REPLACE
		color.rgb = arg0.rgb;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_MODULATE
		color.rgb = arg0.rgb * arg1.rgb;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_ADD
		color.rgb = arg0.rgb + arg1.rgb;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_ADD_SIGNED
		color.rgb = arg0.rgb + arg1.rgb - 0.5;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_INTERPOLATE
		color.rgb = mix(arg1.rgb, arg0.rgb, arg2.rgb);
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_SUBTRACT
		color.rgb = arg0.rgb - arg1.rgb;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_DOT3_RGB
		color.r = 4.0*((arg0.r - 0.5)*(arg1.r - 0.5) + (arg0.g - 0.5)*(arg1.g - 0.5) + (arg0.b - 0.5)*(arg1.b - 0.5));
		color.g = color.r;
		color.b = color.r;
	#elif TEXTURE2_ENV_COMBINE_RGB == OGL_DOT3_RGBA
		color.r = 4.0*((arg0.r - 0.5)*(arg1.r - 0.5) + (arg0.g - 0.5)*(arg1.g - 0.5) + (arg0.b - 0.5)*(arg1.b - 0.5));
		color.g = color.r;
		color.b = color.r;
		color.a = color.r;
	#endif

	#if TEXTURE2_ENV_COMBINE_ALPHA == OGL_REPLACE
		color.a = arg0.a;
	#elif TEXTURE2_ENV_COMBINE_ALPHA == OGL_MODULATE
		color.a = arg0.a * arg1.a;
	#elif TEXTURE2_ENV_COMBINE_ALPHA == OGL_ADD
		color.a = arg0.a + arg1.a;
	#elif TEXTURE2_ENV_COMBINE_ALPHA == OGL_ADD_SIGNED
		color.a = arg0.a + arg1.a - 0.5;
	#elif TEXTURE2_ENV_COMBINE_ALPHA == OGL_INTERPOLATE
		color.a = mix(arg1.a, arg0.a, arg2.a);
	#elif TEXTURE2_ENV_COMBINE_ALPHA == OGL_SUBTRACT
		color.a = arg0.a - arg1.a;
	#endif
#endif
		
	color.rgb = color.rgb * u_texture2EnvRGBScale;
	color.a = color.a * u_texture2EnvAlphaScale;
	color = clamp(color, c_zerof, c_onef);
}

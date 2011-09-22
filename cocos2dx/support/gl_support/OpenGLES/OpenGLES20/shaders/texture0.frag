

#if !defined(TEXCOORD0_ENABLED)
	#define TEXCOORD0_ENABLED -1
#endif

#if !defined(TEXTURE0_FORMAT)
	#define TEXTURE0_FORMAT -1
#endif

#if !defined(TEXTURE0_ENV_MODE)
	#define TEXTURE0_ENV_MODE -1
#endif

#if !defined(TEXTURE0_ENV_COMBINE_RGB)
	#define TEXTURE0_ENV_COMBINE_RGB -1
#endif

#if !defined(TEXTURE0_ENV_COMBINE_ALPHA)
	#define TEXTURE0_ENV_COMBINE_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_SRC0_RGB)
	#define TEXTURE0_ENV_SRC0_RGB -1
#endif

#if !defined(TEXTURE0_ENV_SRC1_RGB)
	#define TEXTURE0_ENV_SRC1_RGB -1
#endif

#if !defined(TEXTURE0_ENV_SRC2_RGB)
	#define TEXTURE0_ENV_SRC2_RGB -1
#endif

#if !defined(TEXTURE0_ENV_SRC0_ALPHA)
	#define TEXTURE0_ENV_SRC0_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_SRC1_ALPHA)
	#define TEXTURE0_ENV_SRC1_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_SRC2_ALPHA)
	#define TEXTURE0_ENV_SRC2_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND0_RGB)
	#define TEXTURE0_ENV_OPERAND0_RGB -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND1_RGB)
	#define TEXTURE0_ENV_OPERAND1_RGB -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND2_RGB)
	#define TEXTURE0_ENV_OPERAND2_RGB -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND0_ALPHA)
	#define TEXTURE0_ENV_OPERAND0_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND1_ALPHA)
	#define TEXTURE0_ENV_OPERAND1_ALPHA -1
#endif

#if !defined(TEXTURE0_ENV_OPERAND2_ALPHA)
	#define TEXTURE0_ENV_OPERAND2_ALPHA -1
#endif

// Uniforms
uniform sampler2D u_texture0Sampler;
uniform int u_texture0Format;
uniform bool u_texCoord0Enabled;
uniform int u_texture0EnvMode;
uniform vec4 u_texture0EnvColor;
uniform int u_texture0EnvCombineRGB;
uniform int u_texture0EnvCombineAlpha;
uniform float u_texture0EnvRGBScale;
uniform float u_texture0EnvAlphaScale;
uniform float u_texture0EnvBlurAmount;

// Varyings
varying vec4 v_texCoord0;

void fetchTexture0Color()
{
	vec4 texCoord0;
#if TEXCOORD0_ENABLED == 1
	texCoord0 = v_texCoord0;
#elif TEXCOORD0_ENABLED == 0
	texCoord0 = vec4(c_zerof, c_zerof, c_zerof, c_zerof);
#elif TEXCOORD0_ENABLED == -1
	if (u_texCoord0Enabled) {
		texCoord0 = v_texCoord0;
	} else {
		texCoord0 = vec4(c_zerof, c_zerof, c_zerof, c_zerof);
	}
#endif

#if TEXTURE0_ENABLED == 1 || TEXTURE0_ENABLED == -1
	#if TEXTURE0_ENABLED == -1
	if (u_texture0Enabled) {
	#endif
		texture0Color = texture2D(u_texture0Sampler, texCoord0.st);
	#if TEXTURE0_ENABLED == -1
	}
	#endif
#endif
}

void calcTexture0Environment(inout vec4 color)
{	
#if TEXTURE0_ENV_MODE == GL_MODULATE
	#if TEXTURE0_FORMAT == GL_ALPHA
		color.a = color.a * texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE
		color.rgb = color.rgb * texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE_ALPHA
		color = color * texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_RGB
		color.rgb = color.rgb * texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_RGBA
		color = color * texture0Color;
	#endif
#elif TEXTURE0_ENV_MODE == GL_ADD
	#if TEXTURE0_FORMAT == GL_ALPHA
		color.a = color.a * texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE
		color.rgb = color.rgb + texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE_ALPHA
		color.rgb = color.rgb + texture0Color.rgb;
		color.a = color.a * texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_RGB
		color.rgb = color.rgb + texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_RGBA
		color.rgb = color.rgb + texture0Color.rgb;
		color.a = color.a * texture0Color.a;
	#endif
#elif TEXTURE0_ENV_MODE == GL_DECAL
	#if TEXTURE0_FORMAT == GL_ALPHA
		// undefined
	#elif TEXTURE0_FORMAT == GL_LUMINANCE
		// undefined
	#elif TEXTURE0_FORMAT == GL_LUMINANCE_ALPHA
		// undefined
	#elif TEXTURE0_FORMAT == GL_RGB
		color.rgb = texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_RGBA
		color.rgb = mix(color.rgb, texture0Color.rgb, texture0Color.a);
	#endif
#elif TEXTURE0_ENV_MODE == GL_BLEND
	#if TEXTURE0_FORMAT == GL_ALPHA
		color.a = color.a * texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE
		color.rgb = mix(color.rgb, u_texture0EnvColor.rgb, texture0Color.rgb);
	#elif TEXTURE0_FORMAT == GL_LUMINANCE_ALPHA
		color.rgb = mix(color.rgb, u_texture0EnvColor.rgb, texture0Color.rgb);
		color.a = color.a * texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_RGB
		color.rgb = mix(color.rgb, u_texture0EnvColor.rgb, texture0Color.rgb);
	#elif TEXTURE0_FORMAT == GL_RGBA
		color.rgb = mix(color.rgb, u_texture0EnvColor.rgb, texture0Color.rgb);
		color.a = color.a * texture0Color.a;
	#endif
#elif TEXTURE0_ENV_MODE == GL_REPLACE
	#if TEXTURE0_FORMAT == GL_ALPHA
		color.a = texture0Color.a;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE
		color.rgb = texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_LUMINANCE_ALPHA
		color = texture0Color;
	#elif TEXTURE0_FORMAT == GL_RGB
		color.rgb = texture0Color.rgb;
	#elif TEXTURE0_FORMAT == GL_RGBA
		color = texture0Color;
	#endif
#elif TEXTURE0_ENV_MODE == GL_BLUR
	vec4 sample0 = texture0Color;
	vec4 sample1 = texture2D(u_texture0Sampler, vec2(v_texCoord0.s - u_texture0EnvBlurAmount, v_texCoord0.t - u_texture0EnvBlurAmount));
	vec4 sample2 = texture2D(u_texture0Sampler, vec2(v_texCoord0.s + u_texture0EnvBlurAmount, v_texCoord0.t + u_texture0EnvBlurAmount));
	vec4 sample3 = texture2D(u_texture0Sampler, vec2(v_texCoord0.s - u_texture0EnvBlurAmount, v_texCoord0.t + u_texture0EnvBlurAmount));
	vec4 sample4 = texture2D(u_texture0Sampler, vec2(v_texCoord0.s + u_texture0EnvBlurAmount, v_texCoord0.t - u_texture0EnvBlurAmount));
	color = (sample0 + sample1 + sample2 + sample3 + sample4) / 5.0;
#elif TEXTURE0_ENV_MODE == GL_COMBINE
	vec4 arg0;
	vec4 arg1;
	vec4 arg2;

	// SRC RGB
	#if TEXTURE0_ENV_SRC0_RGB == 0
		arg0.rgb = texture0Color.rgb;
	#elif TEXTURE0_ENV_SRC0_RGB == 1
		arg0.rgb = texture1Color.rgb;
	#elif TEXTURE0_ENV_SRC0_RGB == 2
		arg0.rgb = texture2Color.rgb;
	#elif TEXTURE0_ENV_SRC0_RGB == GL_CONSTANT
		arg0.rgb = u_texture0EnvColor.rgb;
	#elif TEXTURE0_ENV_SRC0_RGB == GL_PRIMARY_COLOR
		arg0.rgb = v_frontColor.rgb;
	#elif TEXTURE0_ENV_SRC0_RGB == GL_PREVIOUS
		arg0.rgb = color.rgb;
	#endif

	// TODO: GL_SRC_ALPHA & GL_ONE_MINUS_SRC_ALPHA exists in SDK but no idea what they are supposed to do in this context..
	#if TEXTURE0_ENV_OPERAND0_RGB == GL_ONE_MINUS_SRC_COLOR
		arg0.rgb = 1.0 - arg0.rgb;
	#endif
		
	#if TEXTURE0_ENV_SRC1_RGB == 0
		arg1.rgb = texture0Color.rgb;
	#elif TEXTURE0_ENV_SRC1_RGB == 1
		arg1.rgb = texture1Color.rgb;
	#elif TEXTURE0_ENV_SRC1_RGB == 2
		arg1.rgb = texture2Color.rgb;
	#elif TEXTURE0_ENV_SRC1_RGB == GL_CONSTANT
		arg1.rgb = u_texture0EnvColor.rgb;
	#elif TEXTURE0_ENV_SRC1_RGB == GL_PRIMARY_COLOR
		arg1.rgb = v_frontColor.rgb;
	#elif TEXTURE0_ENV_SRC1_RGB == GL_PREVIOUS
		arg1.rgb = color.rgb;
	#endif
	
	#if TEXTURE0_ENV_OPERAND0_RGB == GL_ONE_MINUS_SRC_COLOR
		arg1.rgb = 1.0 - arg1.rgb;
	#endif

	#if TEXTURE0_ENV_SRC2_RGB == 0
		arg2.rgb = texture0Color.rgb;
	#elif TEXTURE0_ENV_SRC2_RGB == 1
		arg2.rgb = texture1Color.rgb;
	#elif TEXTURE0_ENV_SRC2_RGB == 2
		arg2.rgb = texture2Color.rgb;
	#elif TEXTURE0_ENV_SRC2_RGB == GL_CONSTANT
		arg2.rgb = u_texture0EnvColor.rgb;
	#elif TEXTURE0_ENV_SRC2_RGB == GL_PRIMARY_COLOR
		arg2.rgb = v_frontColor.rgb;
	#elif TEXTURE0_ENV_SRC2_RGB == GL_PREVIOUS
		arg2.rgb = color.rgb;
	#endif
		
	#if TEXTURE0_ENV_OPERAND2_RGB == GL_ONE_MINUS_SRC_COLOR
		arg2.rgb = 1.0 - arg2.rgb;
	#endif
		
	// SRC ALPHA
	#if TEXTURE0_ENV_SRC0_ALPHA == 0
		arg0.a = texture0Color.a;
	#elif TEXTURE0_ENV_SRC0_ALPHA == 1
		arg0.a = texture1Color.a;
	#elif TEXTURE0_ENV_SRC0_ALPHA == 2
		arg0.a = texture2Color.a;
	#elif TEXTURE0_ENV_SRC0_ALPHA == GL_CONSTANT
		arg0.a = u_texture0EnvColor.a;
	#elif TEXTURE0_ENV_SRC0_ALPHA == GL_PRIMARY_COLOR
		arg0.a = v_frontColor.a;
	#elif TEXTURE0_ENV_SRC0_ALPHA == GL_PREVIOUS
		arg0.a = color.a;
	#endif
		
	#if TEXTURE0_ENV_OPERAND0_ALPHA == GL_ONE_MINUS_SRC_ALPHA
		arg0.a = 1.0 - arg0.a;
	#endif
		
	#if TEXTURE0_ENV_SRC1_ALPHA == 0
		arg1.a = texture0Color.a;
	#elif TEXTURE0_ENV_SRC1_ALPHA == 1
		arg1.a = texture1Color.a;
	#elif TEXTURE0_ENV_SRC1_ALPHA == 2
		arg1.a = texture2Color.a;
	#elif TEXTURE0_ENV_SRC1_ALPHA == GL_CONSTANT
		arg1.a = u_texture0EnvColor.a;
	#elif TEXTURE0_ENV_SRC1_ALPHA == GL_PRIMARY_COLOR
		arg1.a = v_frontColor.a;
	#elif TEXTURE0_ENV_SRC1_ALPHA == GL_PREVIOUS
		arg1.a = color.a;
	#endif
		
	#if TEXTURE0_ENV_OPERAND0_ALPHA == GL_ONE_MINUS_SRC_ALPHA
		arg1.a = 1.0 - arg1.a;
	#endif
		
	#if TEXTURE0_ENV_SRC2_ALPHA == 0
		arg2.a = texture0Color.a;
	#elif TEXTURE0_ENV_SRC2_ALPHA == 1
		arg2.a = texture1Color.a;
	#elif TEXTURE0_ENV_SRC2_ALPHA == 2
		arg2.a = texture2Color.a;
	#elif TEXTURE0_ENV_SRC2_ALPHA == GL_CONSTANT
		arg2.a = u_texture0EnvColor.a;
	#elif TEXTURE0_ENV_SRC2_ALPHA == GL_PRIMARY_COLOR
		arg2.a = v_frontColor.a;
	#elif TEXTURE0_ENV_SRC2_ALPHA == GL_PREVIOUS
		arg2.a = color.a;
	#endif
		
	#if TEXTURE0_ENV_OPERAND2_ALPHA == GL_ONE_MINUS_SRC_ALPHA
		arg2.a = 1.0 - arg2.a;
	#endif
		
	// COMBINE_RGB
	#if TEXTURE0_ENV_COMBINE_RGB == GL_REPLACE
		color.rgb = arg0.rgb;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_MODULATE
		color.rgb = arg0.rgb * arg1.rgb;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_ADD
		color.rgb = arg0.rgb + arg1.rgb;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_ADD_SIGNED
		color.rgb = arg0.rgb + arg1.rgb - 0.5;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_INTERPOLATE
		color.rgb = mix(arg1.rgb, arg0.rgb, arg2.rgb);
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_SUBTRACT
		color.rgb = arg0.rgb - arg1.rgb;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_DOT3_RGB
		color.r = 4.0*((arg0.r - 0.5)*(arg1.r - 0.5) + (arg0.g - 0.5)*(arg1.g - 0.5) + (arg0.b - 0.5)*(arg1.b - 0.5));
		color.g = color.r;
		color.b = color.r;
	#elif TEXTURE0_ENV_COMBINE_RGB == GL_DOT3_RGBA
		color.r = 4.0*((arg0.r - 0.5)*(arg1.r - 0.5) + (arg0.g - 0.5)*(arg1.g - 0.5) + (arg0.b - 0.5)*(arg1.b - 0.5));
		color.g = color.r;
		color.b = color.r;
		color.a = color.r;
	#endif

	// COMBINE_ALPHA
	#if TEXTURE0_ENV_COMBINE_ALPHA == GL_REPLACE
		color.a = arg0.a;
	#elif TEXTURE0_ENV_COMBINE_ALPHA == GL_MODULATE
		color.a = arg0.a * arg1.a;
	#elif TEXTURE0_ENV_COMBINE_ALPHA == GL_ADD
		color.a = arg0.a + arg1.a;
	#elif TEXTURE0_ENV_COMBINE_ALPHA == GL_ADD_SIGNED
		color.a = arg0.a + arg1.a - 0.5;
	#elif TEXTURE0_ENV_COMBINE_ALPHA == GL_INTERPOLATE
		color.a = mix(arg1.a, arg0.a, arg2.a);
	#elif TEXTURE0_ENV_COMBINE_ALPHA == GL_SUBTRACT
		color.a = arg0.a - arg1.a;
	#endif
#endif
		
	color.rgb = color.rgb * u_texture0EnvRGBScale;
	color.a = color.a * u_texture0EnvAlphaScale;
	color = clamp(color, c_zerof, c_onef);
}

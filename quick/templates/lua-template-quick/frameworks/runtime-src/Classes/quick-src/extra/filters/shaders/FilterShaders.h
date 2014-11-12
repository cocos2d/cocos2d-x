#ifndef __CC_FILTER_SHADER_H__
#define __CC_FILTER_SHADER_H__

#include "cocos2dx_extra.h"

NS_CC_EXTRA_BEGIN

extern CC_DLL const GLchar * FilterShader_bloom_frag;
extern CC_DLL const GLchar * FilterShader_blur_frag;
extern CC_DLL const GLchar * FilterShader_celshading_frag;
extern CC_DLL const GLchar * FilterShader_edgedetection_frag;
extern CC_DLL const GLchar * FilterShader_greyscale_frag;
extern CC_DLL const GLchar * FilterShader_lensflare_frag;
extern CC_DLL const GLchar * FilterShader_noisy_frag;
extern CC_DLL const GLchar * FilterShader_outline_frag;
extern CC_DLL const GLchar * FilterShader_sepia_frag;


extern CC_DLL const GLchar * ccFilterShader_gray_frag;

extern CC_DLL const GLchar * ccFilterShader_hblur_vert;
extern CC_DLL const GLchar * ccFilterShader_vblur_vert;
extern CC_DLL const GLchar * ccFilterShader_blur_frag;

extern CC_DLL const GLchar * ccFilterShader_sharpen_vert;
extern CC_DLL const GLchar * ccFilterShader_sharpen_frag;

extern CC_DLL const GLchar * ccFilterShader_rgb_frag;

extern CC_DLL const GLchar * ccFilterShader_brightness_frag;

extern CC_DLL const GLchar * ccFilterShader_exposure_frag;

extern CC_DLL const GLchar * ccFilterShader_contrast_frag;

extern CC_DLL const GLchar * ccFilterShader_saturation_frag;

extern CC_DLL const GLchar * ccFilterShader_gamma_frag;

extern CC_DLL const GLchar * ccFilterShader_hue_frag;

extern CC_DLL const GLchar * ccFilterShader_haze_frag;

extern CC_DLL const GLchar * ccFilterShader_zoom_blur_frag;

extern CC_DLL const GLchar * ccFilterShader_motion_blur_vert;
extern CC_DLL const GLchar * ccFilterShader_motion_blur_frag;

extern CC_DLL const GLchar * ccFilterShader_drop_shadow_vert;
extern CC_DLL const GLchar * ccFilterShader_drop_shadow_frag;

extern CC_DLL const GLchar * ccFilterShader_sepia_frag;

extern CC_DLL const GLchar * ccFilterShader_gaussian_hblur_frag;
extern CC_DLL const GLchar * ccFilterShader_gaussian_vblur_frag;

extern CC_DLL const GLchar * ccFilterShader_test_vert;
extern CC_DLL const GLchar * ccFilterShader_test_frag;

//==============================

extern CC_DLL const GLchar * ccFilterShader_colorramp_frag;

extern CC_DLL const GLchar * ccFilterShader_emboss_frag;

extern CC_DLL const GLchar * ccFilterShader_embossmov_frag;

extern CC_DLL const GLchar * ccFilterShader_grass_frag;


NS_CC_EXTRA_END

#endif /* __CC_FILTER_SHADER_H__ */

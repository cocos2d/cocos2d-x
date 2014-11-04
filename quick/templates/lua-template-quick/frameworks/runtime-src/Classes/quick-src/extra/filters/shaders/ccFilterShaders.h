#ifndef __CC_FILTER_SHADER_H__
#define __CC_FILTER_SHADER_H__

#include "cocos2dx_extra.h"
//#include "CCGL.h"
//#include "platform/CCPlatformMacros.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

#define kCCFilterShader_gray	"ccFilterShader_gray"
#define kCCFilterShader_hblur	"ccFilterShader_hblur"
#define kCCFilterShader_vblur	"ccFilterShader_vblur"
#define kCCFilterShader_gaussian_hblur	"ccFilterShader_gaussian_hblur"
#define kCCFilterShader_gaussian_vblur	"ccFilterShader_gaussian_vblur"
#define kCCFilterShader_sharpen	"ccFilterShader_sharpen"
#define kCCFilterShader_rgb	"ccFilterShader_rgb"
#define kCCFilterShader_brightness	"ccFilterShader_brightness"
#define kCCFilterShader_exposure	"ccFilterShader_exposure"
#define kCCFilterShader_contrast	"ccFilterShader_contrast"
#define kCCFilterShader_saturation	"ccFilterShader_saturation"
#define kCCFilterShader_gamma	"ccFilterShader_gamma"
#define kCCFilterShader_hue	"ccFilterShader_hue"
#define kCCFilterShader_haze	"ccFilterShader_haze"
#define kCCFilterShader_zoom_blur	"ccFilterShader_zoom_blur"
#define kCCFilterShader_motion_blur	"ccFilterShader_motion_blur"
#define kCCFilterShader_drop_shadow	"ccFilterShader_drop_shadow"
#define kCCFilterShader_sepia	"ccFilterShader_sepia"
#define kCCFilterShader_test	"ccFilterShader_test"

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


NS_CC_EXT_END

#endif /* __CC_FILTER_SHADER_H__ */

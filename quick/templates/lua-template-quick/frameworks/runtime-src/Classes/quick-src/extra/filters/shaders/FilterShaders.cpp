#include "FilterShaders.h"

#define STRINGIFY(A)  #A

NS_CC_EXTRA_BEGIN

//const GLchar * FilterShader_bloom_frag =
#include "example_bloom.fsh"

//const GLchar * FilterShader_blur_frag =
#include "example_Blur.fsh"

//const GLchar * FilterShader_celshading_frag =
#include "example_celShading.fsh"

//const GLchar * FilterShader_edgedetection_frag =
#include "example_edgeDetection.fsh"

//const GLchar * FilterShader_greyscale_frag =
#include "example_greyScale.fsh"

//const GLchar * FilterShader_lensflare_frag =
#include "example_lensFlare.fsh"

//const GLchar * FilterShader_noisy_frag =
#include "example_Noisy.fsh"

//const GLchar * FilterShader_outline_frag =
#include "example_outline.fsh"

//const GLchar * FilterShader_sepia_frag =
#include "example_sepia.fsh"


const GLchar * ccFilterShader_gray_frag =
#include "ccFilterShader_gray_frag.h"

const GLchar * ccFilterShader_hblur_vert =
#include "ccFilterShader_hblur_vert.h"
const GLchar * ccFilterShader_vblur_vert =
#include "ccFilterShader_vblur_vert.h"
const GLchar * ccFilterShader_blur_frag =
#include "ccFilterShader_blur_frag.h"

const GLchar * ccFilterShader_sharpen_vert =
#include "ccFilterShader_sharpen_vert.h"
const GLchar * ccFilterShader_sharpen_frag =
#include "ccFilterShader_sharpen_frag.h"

const GLchar * ccFilterShader_rgb_frag =
#include "ccFilterShader_rgb_frag.h"

const GLchar * ccFilterShader_brightness_frag =
#include "ccFilterShader_brightness_frag.h"

const GLchar * ccFilterShader_exposure_frag =
#include "ccFilterShader_exposure_frag.h"

const GLchar * ccFilterShader_contrast_frag =
#include "ccFilterShader_contrast_frag.h"

const GLchar * ccFilterShader_saturation_frag =
#include "ccFilterShader_saturation_frag.h"

const GLchar * ccFilterShader_gamma_frag =
#include "ccFilterShader_gamma_frag.h"

const GLchar * ccFilterShader_hue_frag =
#include "ccFilterShader_hue_frag.h"

const GLchar * ccFilterShader_haze_frag =
#include "ccFilterShader_haze_frag.h"

const GLchar * ccFilterShader_zoom_blur_frag =
#include "ccFilterShader_zoom_blur_frag.h"

const GLchar * ccFilterShader_motion_blur_vert =
#include "ccFilterShader_motion_blur_vert.h"
const GLchar * ccFilterShader_motion_blur_frag =
#include "ccFilterShader_motion_blur_frag.h"

const GLchar * ccFilterShader_drop_shadow_vert =
#include "ccFilterShader_drop_shadow_vert.h"
const GLchar * ccFilterShader_drop_shadow_frag =
#include "ccFilterShader_drop_shadow_frag.h"

const GLchar * ccFilterShader_sepia_frag =
#include "ccFilterShader_sepia_frag.h"

const GLchar * ccFilterShader_test_vert =
#include "ccFilterShader_test_vert.h"
const GLchar * ccFilterShader_test_frag =
#include "ccFilterShader_test_frag.h"

//==============================
//
const GLchar * ccFilterShader_gaussian_hblur_frag =
#include "ccFilterShader_gaussian_hblur_frag.h"
const GLchar * ccFilterShader_gaussian_vblur_frag =
#include "ccFilterShader_gaussian_vblur_frag.h"

const GLchar * ccFilterShader_colorramp_frag =
#include "ccFilterShader_colorramp_frag.h"

const GLchar * ccFilterShader_emboss_frag =
#include "ccFilterShader_emboss_frag.h"

const GLchar * ccFilterShader_embossmov_frag =
#include "ccFilterShader_embossmov_frag.h"

const GLchar * ccFilterShader_grass_frag =
#include "ccFilterShader_grass_frag.h"


NS_CC_EXTRA_END

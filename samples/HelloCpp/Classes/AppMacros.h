#ifndef __APPMACROS_H__
#define __APPMACROS_H__


#define kDesignResolution_480x320    0
#define kDesignResolution_1024x768   1
#define kDesignResolution_2048x1536  2

#define kTargetDesignResolutionSize  kDesignResolution_2048x1536

#if (kTargetDesignResolutionSize == kDesignResolution_480x320)
#define kDesignResolutionSize_width   480.0f
#define kDesignResolutionSize_height  320.0f


#elif (kTargetDesignResolutionSize == kDesignResolution_1024x768)
#define kDesignResolutionSize_width   1024.0f
#define kDesignResolutionSize_height  768.0f

#elif (kTargetDesignResolutionSize == kDesignResolution_2048x1536)
#define kDesignResolutionSize_width   2048.0f
#define kDesignResolutionSize_height  1536.0f

#else
#error unknown target design resolution!
#endif

#define kTitleFontSize            (kDesignResolutionSize_width / 480.0f * 24)

#endif /* __APPMACROS_H__ */

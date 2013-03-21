#include "platform/CCDevice.h"
#include "CCEGLView.h"
#include "CCCommon.h"
#include <screen/screen.h>
#include <math.h>

NS_CC_BEGIN

int CCDevice::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        screen_display_t screen_disp = CCEGLView::sharedOpenGLView()->getScreenDisplay();
#ifdef BLACKBERRY10
        // Dev Alpha: 1280x768, 4.2", 356DPI, 0.6f scale
        
        screen_get_display_property_iv(screen_disp, SCREEN_PROPERTY_DPI, &dpi);
#else
        // Playbook: 1024x600, 7", 170DPI, 1.25f scale
        int screen_phys_size[2];

        screen_get_display_property_iv(screen_disp, SCREEN_PROPERTY_PHYSICAL_SIZE, screen_phys_size);
        //CCLog("screen_phys_size[%d,%d]", screen_phys_size[0], screen_phys_size[1]);

        int screen_resolution[2];
        screen_get_display_property_iv(screen_disp, SCREEN_PROPERTY_SIZE, screen_resolution);
        //CCLog("screen_resolution[%d,%d]", screen_resolution[0], screen_resolution[1]);
        double diagonal_pixels = sqrt((double)(screen_resolution[0] * screen_resolution[0] + screen_resolution[1] * screen_resolution[1]));
        // 1 millimeter = 0.0393700787 inches
        double diagonal_inches = 0.0393700787 * sqrt((double)(screen_phys_size[0] * screen_phys_size[0] + screen_phys_size[1] * screen_phys_size[1]));
        dpi = (int)(diagonal_pixels / diagonal_inches + 0.5);
        //CCLog("dpi = %d, pixel = %lf, inches = %lf", dpi, diagonal_pixels, diagonal_inches );
#endif
    }
    //CCLog("dpi = %d", dpi);
    return dpi;
}

NS_CC_END
